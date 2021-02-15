#include "viewerwidget.h"
#include <osgViewer/ViewerEventHandlers>

#include <osgGA/MultiTouchTrackballManipulator>

#include <osgDB/ReadFile>

#include <osgQt/GraphicsWindowQt>
#include <QOpenGLContext>
#include <QVBoxLayout>
#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>
#include "osgspheresegment.h"

class ShaderGeometry : public osg::Drawable
{
public:
	ShaderGeometry() { setUseDisplayList(false); }

	virtual ~ShaderGeometry() {}

	virtual void drawImplementation(osg::RenderInfo& renderInfo) const
	{
		int a = 0; 
	}
};


osg::ref_ptr<osg::MatrixTransform> createCylinder(const osg::Vec3 &from, const osg::Vec3 &to, float radius)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();
	osg::ref_ptr<osg::ShapeDrawable> cylinder = new osg::ShapeDrawable();
	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints();

	hints->setDetailRatio(0.8f);
	osg::Vec3 cylCenter = (to + from) / 2;		//得到柱心
	float height = (to - from).length();		//得到长度
	cylinder = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0.0, 0.0, 0.0), radius, height), hints.get());
	cylinder->setColor(osg::Vec4(1.0, 0.0, 0.0, 1.0f));
	//鹿皮鞋色
	geode->setDataVariance(osg::Object::DYNAMIC);
	cylinder->setDataVariance(osg::Object::DYNAMIC);

	geode->addDrawable(cylinder.get());
	osg::Matrix mRotate, mTrans;
	mRotate.makeRotate(osg::Vec3f(0.0f, 0.0f, 1.0f), to - from);
	mTrans.makeTranslate(cylCenter);
	mt->setMatrix(mRotate*mTrans);
	mt->addChild(geode.get());

	{
		osg::ref_ptr<ShaderGeometry> sg = new ShaderGeometry;
		osg::ref_ptr<osg::Geode> geode = new osg::Geode();
		geode->addDrawable(sg.get());
		mt->addChild(geode.get());
	}

	mt->setDataVariance(osg::Object::DYNAMIC);
	return mt.get();
}

static osg::Camera* createCamera(int x, int y, int w, int h)
{
    osg::ref_ptr<osg::GraphicsContext::Traits> traits =
        new osg::GraphicsContext::Traits;
    traits->windowDecoration = false;
    traits->x = x;
    traits->y = y;
    traits->width = w;
    traits->height = h;
    traits->doubleBuffer = true;
    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setGraphicsContext(
        new osgQt::GraphicsWindowQt(traits.get()));
    camera->setClearColor(osg::Vec4(0.8, 0.5, 0.1, 1.0));
    camera->setViewport(new osg::Viewport(
        0, 0, traits->width, traits->height));
    camera->setProjectionMatrixAsPerspective(
        30.0f, static_cast<double>(traits->width) /
        static_cast<double>(traits->height), 1.0f, 10000.0f);
    return camera.release();
}

ViewerWidget::ViewerWidget(QWidget* pParent):QWidget(pParent)
{
	m_viewer.setUpThreading();
  //  auto scene = osgDB::readNodeFile("F:\\development\\osgStudy\\data\\cow.osg");
//	auto scene = createCylinder(osg::Vec3(0, 0, 0), osg::Vec3(100, 0, 0), 10);

	auto scene = GetOsgSphereSegment();
	if(nullptr == scene)
    {
      return ;
    }

	scene->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    auto pCamera = createCamera(50, 50, 640, 480);
    if(nullptr == pCamera)
    {
      return ;
    }

    m_viewer.setCamera(pCamera);
    m_viewer.setSceneData(scene);
    m_viewer.addEventHandler(new osgViewer::StatsHandler);
    m_viewer.setCameraManipulator(
        new osgGA::TrackballManipulator);

    osgQt::GraphicsWindowQt* gw =
        dynamic_cast<osgQt::GraphicsWindowQt*>(
            pCamera->getGraphicsContext());
    if (nullptr != gw)
    {
        QVBoxLayout* layout = new QVBoxLayout;
        layout->addWidget(gw->getGLWidget());
        setLayout(layout);
    }

    m_viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);
    m_viewer.realize();
    m_thread.viewerPtr = &m_viewer;

    QOpenGLContext* qglcx = gw->getGLWidget()->context()->contextHandle();
    if (qglcx->thread() != &m_thread) {
        qglcx->doneCurrent();
        qglcx->moveToThread(&m_thread);
    }
    m_thread.start();
	this->setGeometry(100, 100, 800, 600);
}

void ViewerWidget::closeLocalEvent(QCloseEvent *event)
{
	closeEvent(event);
}

void ViewerWidget::closeEvent(QCloseEvent *event)
{
    m_thread.terminate();
    QWidget::closeEvent(event);
}


QWidget* ViewerWidget::getOsgWiget()
{
	static osgViewer::Viewer s_viewer;
	static RenderThread  s_thread;


	auto scene = createCylinder(osg::Vec3(0, 0, 0), osg::Vec3(100, 0, 0), 10);
	if (nullptr == scene)
	{
		return nullptr;
	}
	auto pCamera = createCamera(50, 50, 640, 480);
	if (nullptr == pCamera)
	{
		return nullptr;
	}

	s_viewer.setCamera(pCamera);
	s_viewer.setSceneData(scene);
	s_viewer.addEventHandler(new osgViewer::StatsHandler);
	s_viewer.setCameraManipulator(
		new osgGA::TrackballManipulator);

	osgQt::GraphicsWindowQt* gw =
		dynamic_cast<osgQt::GraphicsWindowQt*>(
			pCamera->getGraphicsContext());
	if (nullptr == gw)
	{
		return nullptr;
	}

	s_viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);
	s_viewer.realize();
	s_thread.viewerPtr = &s_viewer;

	QOpenGLContext* qglcx = gw->getGLWidget()->context()->contextHandle();
	if (qglcx->thread() != &s_thread) {
		qglcx->doneCurrent();
		qglcx->moveToThread(&s_thread);
	}
	s_thread.start();
	gw->getGLWidget()->setGeometry(100, 100, 800, 600);
	return gw->getGLWidget();
}