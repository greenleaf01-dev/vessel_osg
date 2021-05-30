#include "viewerwidget.h"
#include <osgViewer/ViewerEventHandlers>

#include <osgGA/MultiTouchTrackballManipulator>

#include <osgDB/ReadFile>

#include <osgQt/GraphicsWindowQt>
#include <QOpenGLContext>
#include <QVBoxLayout>
#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>
#include <osg/Material>
#include "osgspheresegment.h"
#include "vesselnode.h"

static float s_fLength = 15.0; 
static std::wstring s_strX = L"X";
static std::wstring s_strY = L"Y";
static std::wstring s_strZ = L"Z";

osg::Vec3 convertPtnFromViewPortToWorld(osg::Vec3& ptnViewPort, osgViewer::Viewer& viewer)
{
	osg::Camera *camera = viewer.getCamera();
	osg::Matrix MVPW = camera->getViewMatrix() * camera->getProjectionMatrix() * camera->getViewport()->computeWindowMatrix();
	osg::Matrix inverseMVPW = osg::Matrix::inverse(MVPW);
	osg::Vec3 mouseWorld = ptnViewPort * inverseMVPW;
	return mouseWorld;
}

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

class CDrawLineHandler :public osgGA::GUIEventHandler
{
public:
	CDrawLineHandler(osgViewer::Viewer *viewer) :mViewer(viewer)
	{
		m_centerRef = mViewer->getSceneData()->getBound().center();
	}
	virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
	{
		switch (ea.getEventType())
		{
		case osgGA::GUIEventAdapter::PUSH:
		{
			if (ea.getButtonMask() & osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
			{
				if (m_bExecuteRotate)
				{
					return false;
				}

				if (m_bFirstClick)
				{
					m_bFirstClick = false;
					if (m_pLineGeometry.valid())
					{
						m_pLineGeometry = nullptr;
						m_bLeftButtonPress = false;
						upDateViewMatrix();
						if (m_pCareraManipulator.valid())
						{
							mViewer->setCameraManipulator(m_pCareraManipulator, false);
						}
						m_bLeftButtonPress = false;
					}
					else
					{
						m_bLeftButtonPress = true;
					}
				}
				else
				{
					m_bLeftButtonPress = true;
				}
				return true;
			}
			break;
		}
		case osgGA::GUIEventAdapter::MOVE:
		{
			if (m_pLineGeometry.valid() && m_bFirstClick)
			{
				auto ptnMove = convertPtnFromViewPortToWorld(osg::Vec3(ea.getX(), ea.getY(), 0.5), *mViewer);
				changeLineGeometry(ptnMove);
				return true;
			}
			break;
		}
		case osgGA::GUIEventAdapter::DRAG:
		{
			if (m_pLineGeometry.valid() && m_bFirstClick && m_bExecuteRotate)
			{
				auto ptnMove = convertPtnFromViewPortToWorld(osg::Vec3(ea.getX(), ea.getY(), 0.5), *mViewer);
				changeLineGeometry(ptnMove);
				return false;
			}
			break;
		}
		case osgGA::GUIEventAdapter::RELEASE:
		{
			if (m_bLeftButtonPress)
			{
				if (m_bExecuteRotate)
				{
					return false;
				}

				if (!m_bFirstClick)
				{
					m_bFirstClick = true;
					if (m_pCareraManipulator.get() != mViewer->getCameraManipulator())
					{
						m_pCareraManipulator = mViewer->getCameraManipulator();
					}

					mViewer->setCameraManipulator(nullptr, false);

					auto ptnBegin = convertPtnFromViewPortToWorld(osg::Vec3(ea.getX(), ea.getY(), 0.5), *mViewer);
					createLineGeometry(ptnBegin);
					upDateViewMatrix();
					if (!m_pLineGeometry.valid())
					{
						break;
					}
				}
				else
				{
					m_bFirstClick = false;
				}
				return true;
			}
			break;
		}
		case osgGA::GUIEventAdapter::KEYUP:
		{
			if (ea.getKey() == 'c')
			{
				if (m_pCareraManipulator.valid())
				{
					mViewer->setCameraManipulator(m_pCareraManipulator, false);
					m_pCareraManipulator = nullptr;
					m_bExecuteRotate = true;
				}
				else
				{
					m_pCareraManipulator = mViewer->getCameraManipulator();
					mViewer->setCameraManipulator(nullptr, false);
					m_bExecuteRotate = false;
				}
				return true;
			}
		}
		}
		return false;
	}
protected:
	void createLineGeometry(const osg::Vec3& ptnBegin);
	void changeLineGeometry(const osg::Vec3& ptnMove);
	void upDateViewMatrix();
protected:
	osgViewer::Viewer *mViewer;
	bool m_bLeftButtonPress = false;
	osg::ref_ptr<osgGA::CameraManipulator> m_pCareraManipulator;
	osg::ref_ptr<osg::Geometry>  m_pLineGeometry;
	osg::Vec3d m_centerRef;

	bool m_bFirstClick = false;
	bool m_bExecuteRotate = false;
};


void CDrawLineHandler::upDateViewMatrix()
{
	/*
	这个是调整视图矩阵，让点击创建的所有item全部都在视景体里面。
	方法是 不改变视点方向和向上的坐标，仅仅是改变视点，让其离参考点更远些。
	*/
	if (nullptr == mViewer || nullptr == mViewer->getCamera() || nullptr == mViewer->getSceneData())
	{
		return;
	}

	auto boundingSphere = mViewer->getSceneData()->getBound();
	auto ptnCenter = boundingSphere.center();

	osg::Vec3d eye;
	osg::Vec3d centerRef;
	osg::Vec3d up;
	mViewer->getCamera()->getViewMatrixAsLookAt(eye, centerRef, up);

	auto fRadius = boundingSphere.radius();
	auto lenEyeToCenNew1 = (m_centerRef - eye).length();

	auto lenCenOldToNew = (ptnCenter - m_centerRef).length();
	auto lenEyeToCenNew = fRadius; //(ptnCenter - eye).length();


	std::wostringstream  os;
	os << L"the radius is " << lenEyeToCenNew << L"\n" << std::endl;
	std::wstring strBuf = os.str();
	OutputDebugString(strBuf.c_str());

	//根据三角形两边之和必然大于第三边，算出半径 必然在当前的新球体之外
	auto dist = (lenCenOldToNew + lenEyeToCenNew) * 3.5;
	auto  vecCenOldToEye = eye - centerRef;
	vecCenOldToEye.normalize();
	eye = m_centerRef + vecCenOldToEye * dist;
	// mViewer->getCamera()->setViewMatrixAsLookAt(eye, centerRef, up);
}

void CDrawLineHandler::createLineGeometry(const osg::Vec3& ptnBegin)
{
	m_pLineGeometry = new osg::Geometry();
	osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array;
	coords->push_back(ptnBegin);
	//coords->push_back(ptnBegin + osg::Vec3(10.f, 5.f, 5.f));

	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(0.3f, 0.8f, 0.5f, 1.0f));

	m_pLineGeometry->setVertexArray(coords);
	m_pLineGeometry->setColorArray(colors, osg::Array::BIND_OVERALL);

	osg::ref_ptr<osg::DrawElementsUShort> pPrimitivesDown = new osg::DrawElementsUShort(GL_LINE_STRIP);
	pPrimitivesDown->push_back(0);
	//pPrimitivesDown->push_back(1);
	m_pLineGeometry->addPrimitiveSet(pPrimitivesDown.get());

	osg::ref_ptr<osg::Geode> pGeoNode = new osg::Geode();
	m_pLineGeometry->setUseVertexBufferObjects(true);
	m_pLineGeometry->setUseDisplayList(false);
	pGeoNode->addDrawable(m_pLineGeometry);

	auto pRoot = mViewer->getSceneData();
	if (nullptr != dynamic_cast<osg::Group*>(pRoot))
	{
		dynamic_cast<osg::Group*>(pRoot)->addChild(pGeoNode);
	}
}

void CDrawLineHandler::changeLineGeometry(const osg::Vec3& ptnMove)
{
	if (!m_pLineGeometry.valid())
	{
		return;
	}

	auto coords = dynamic_cast<osg::Vec3Array*>(m_pLineGeometry->getVertexArray());
	if (nullptr == coords)
	{
		return;
	}

	if (coords->size() == 0)
	{
		return;
	}

	if (coords->size() == 1)
	{
		coords->push_back(ptnMove);
	}
	else if (coords->size() == 2)
	{
		(*coords)[1] = ptnMove;
	}

	auto primitiveList = m_pLineGeometry->getPrimitiveSetList();
	if (primitiveList.size() == 0)
	{
		return;
	}

	auto pDrawElement = dynamic_cast<osg::DrawElementsUShort*>(primitiveList.at(0).get());
	if (nullptr == pDrawElement)
	{
		return;
	}

	if (pDrawElement->size() < 2)
	{
		pDrawElement->push_back(coords->size() - 1);
	}

	coords->dirty();
	m_pLineGeometry->dirtyBound();
	pDrawElement->dirty();
	mViewer->getSceneData()->dirtyBound();
	mViewer->requestRedraw();
}

class LoacalTrackingManipulator : public osgGA::TrackballManipulator
{
public:
	LoacalTrackingManipulator() {}
	~LoacalTrackingManipulator() {}
	virtual void computeHomePosition(const osg::Camera *camera = NULL, bool useBoundingBox = false);

protected:
	virtual bool handleMouseRelease(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us);
};


bool LoacalTrackingManipulator::handleMouseRelease(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us)
{
	flushMouseEventStack();
	addMouseEvent(ea);
	if (performMovement())
		us.requestRedraw();
	us.requestContinuousUpdate(false);
	_thrown = false;
	return true;
}

void LoacalTrackingManipulator::computeHomePosition(const osg::Camera *camera, bool useBoundingBox)
{
	if (getNode())
	{
		osg::BoundingSphere boundingSphere = getNode()->getBound();

		// set dist to default
		double dist = 3.5f * boundingSphere.radius();

		setHomePosition(boundingSphere.center() + osg::Vec3d(0.0, -dist, 0.0f),
			boundingSphere.center(),
			osg::Vec3d(0.0f, 0.0f, 1.0f),
			_autoComputeHomePosition);
	}
}


class CameraCorCallback : public osg::NodeCallback
{
public:
	CameraCorCallback(osg::Camera* pTrans) :m_CameraCoodinate(pTrans) {}
	~CameraCorCallback() {}

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		if (nullptr == node || nullptr == nv || !m_CameraCoodinate.valid())
		{
			traverse(node, nv);
			return;
		}

		osgUtil::CullVisitor* cv = dynamic_cast<osgUtil::CullVisitor*>(nv);
		if (nullptr == cv)
		{
			traverse(node, nv);
			return;
		}

		osg::Vec3d traslation;
		osg::Vec3d scale;
		osg::Quat rotation;
		osg::Quat so;

		osg::Camera* pCamera = dynamic_cast<osg::Camera*>(node);
		if (nullptr != pCamera)
		{
			pCamera->getViewMatrix().decompose(traslation, rotation, scale, so);
		}
		else
		{
			cv->getModelViewMatrix()->decompose(traslation, rotation, scale, so);
		}

		osg::Matrix mat(rotation);

		osg::Vec3d traslation1;
		osg::Vec3d scale1;
		osg::Quat rotation1;
		osg::Quat so1;

		auto matCamera = m_CameraCoodinate->getViewMatrix();
		matCamera.decompose(traslation1, rotation1, scale1, so1);

		osg::Matrix matScale = osg::Matrix::scale(scale1);
		osg::Matrix matRotate = osg::Matrix::rotate(rotation);
		osg::Matrix matTans = osg::Matrix::translate(traslation1);

		osg::Matrix matNewCamera = matScale * matRotate * matTans;
		m_CameraCoodinate->setViewMatrix(matNewCamera);
		traverse(node, nv);
	}

protected:
	osg::observer_ptr<osg::Camera>  m_CameraCoodinate;
};


void updateSubCamera(osg::Camera* pCoornidateCamera, osg::Node* pNode)
{
	if (nullptr == pCoornidateCamera || nullptr == pNode)
	{
		return;
	}

	auto pShereBound = pNode->getBound();
	auto fRadius = pShereBound.radius();

	osg::Vec4 clearColour = { 0.2f,0.2f,0.2f,1.0f };
	pCoornidateCamera->setClearColor(clearColour);
	pCoornidateCamera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	pCoornidateCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);

	auto fExtent = fRadius * 2 + 5;
	pCoornidateCamera->setProjectionMatrixAsOrtho(-fExtent, fExtent, -fExtent, fExtent, 0, 1000);
}


osg::ref_ptr<osg::MatrixTransform> createCylinder(const osg::Vec3 &from, const osg::Vec3 &to, float radius)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();
	osg::ref_ptr<osg::ShapeDrawable> cylinder = new osg::ShapeDrawable();
	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints();

	hints->setDetailRatio(0.8f);
	osg::Vec3 cylCenter = (to + from) / 2;		//�õ�����
	float height = (to - from).length();		//�õ�����
	cylinder = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0.0, 0.0, 0.0), radius, height), hints.get());
	cylinder->setColor(osg::Vec4(1.0, 0.0, 0.0, 1.0f));
	//¹ƤЬɫ
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



osg::ref_ptr<osg::MatrixTransform> createCoordinateCylinder_local(const osg::Vec3 &from, const osg::Vec3 &to, double radius, osg::Vec4& vecColor)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();
	osg::ref_ptr<osg::ShapeDrawable> cylinder = new osg::ShapeDrawable();
	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints();

	hints->setDetailRatio(0.8f);
	osg::Vec3 cylCenter = (to + from) / 2;		//得到柱心
	double height = (to - from).length();		//得到长度
	cylinder = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0.0, 0.0, 0.0), radius, height), hints.get());
	cylinder->setColor(vecColor);
	//鹿皮鞋色
	geode->setDataVariance(osg::Object::DYNAMIC);
	cylinder->setDataVariance(osg::Object::DYNAMIC);

	geode->addDrawable(cylinder.get());
	osg::Matrix mRotate, mTrans;
	mRotate.makeRotate(osg::Vec3f(0.0f, 0.0f, 1.0f), to - from);
	mTrans.makeTranslate(cylCenter);
	mt->setMatrix(mRotate*mTrans);
	mt->addChild(geode.get());
	mt->setDataVariance(osg::Object::DYNAMIC);
	return mt.get();
}

osg::ref_ptr<osg::MatrixTransform> createCone_local(const osg::Vec3 &from, const osg::Vec3 &to, double radius, osg::Vec4& vecColor)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();
	osg::ref_ptr<osg::ShapeDrawable> cone = new osg::ShapeDrawable();
	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints();

	hints->setDetailRatio(0.8f);
	osg::Vec3 cylCenter = (to + from) / 2;		//得到柱心
	double height = (to - from).length();		//得到长度
	cone = new osg::ShapeDrawable(new osg::Cone(osg::Vec3(0.0, 0.0, 0.0), radius, height), hints.get());
	cone->setColor(vecColor);
	//鹿皮鞋色
	geode->setDataVariance(osg::Object::DYNAMIC);
	cone->setDataVariance(osg::Object::DYNAMIC);

	geode->addDrawable(cone.get());
	osg::Matrix mRotate, mTrans;
	mRotate.makeRotate(osg::Vec3f(0.0f, 0.0f, 1.0f), to - from);
	mTrans.makeTranslate(cylCenter);
	mt->setMatrix(mRotate*mTrans);
	mt->addChild(geode.get());
	mt->setDataVariance(osg::Object::DYNAMIC);
	return mt.get();
}

osg::Geode* createCornidateText_local(const osg::Vec3& pos, const std::wstring& content, double size, const osg::Vec4& vecColor)
{
	osg::ref_ptr<osgText::Text> text = new osgText::Text;
	text->setCharacterSize(size);
	text->setAxisAlignment(osgText::TextBase::SCREEN);
	text->setPosition(pos);
	text->setText(content.c_str());
	text->setColor(vecColor);

	osg::ref_ptr<osgText::Font> font = osgText::readRefFontFile("fonts/arial.ttf");
	text->setFont(font);

	text->setDataVariance(osg::Object::DYNAMIC);
	text->setBackdropType(osgText::Text::OUTLINE);
	text->setBackdropImplementation(osgText::Text::POLYGON_OFFSET);
	text->setBackdropOffset(0.05f);
	text->setBackdropColor(osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));

	osg::ref_ptr<osg::Geode>  geode = new osg::Geode();
	geode->addDrawable(text);

	return geode.release();
}

osg::Group* makeCoordinate_local()
{
	osg::Vec4 vecColorX = { 1.0,0.0,0.0,1.0 };
	auto nodeX = createCoordinateCylinder_local(osg::Vec3(0, 0, 0), osg::Vec3(s_fLength, 0, 0), s_fLength *0.05, vecColorX);
	auto nodeX1 = createCone_local(osg::Vec3(s_fLength, 0, 0), osg::Vec3(s_fLength  * 1.2, 0, 0), s_fLength *0.08, vecColorX);

	osg::ref_ptr<osg::Geode>  geoTextX = createCornidateText_local(osg::Vec3(s_fLength  * 1.2, 0, 0), s_strX, 1.5, vecColorX);

	osg::ref_ptr<osg::Group> node_x = new osg::Group();
	node_x->addChild(nodeX);
	node_x->addChild(nodeX1);
	node_x->addChild(geoTextX);

	osg::Vec4 vecColorY = { 0.0,1.0,0.0,1.0 };
	auto nodeY = createCoordinateCylinder_local(osg::Vec3(0, 0, 0), osg::Vec3(0.0, s_fLength, 0), s_fLength *0.05, vecColorY);
	auto nodeY1 = createCone_local(osg::Vec3(0.0, s_fLength, 0), osg::Vec3(0.0, s_fLength * 1.2, 0), s_fLength *0.08, vecColorY);
	osg::ref_ptr<osg::Geode>  geoTextY = createCornidateText_local(osg::Vec3(0.0, s_fLength * 1.2, 0), s_strY, 1.5, vecColorY);

	osg::ref_ptr<osg::Group> node_Y = new osg::Group();
	node_Y->addChild(nodeY);
	node_Y->addChild(nodeY1);
	node_Y->addChild(geoTextY);

	osg::Vec4 vecColorZ = { 0.0,0.0,1.0,1.0 };
	auto nodeZ = createCoordinateCylinder_local(osg::Vec3(0, 0, 0), osg::Vec3(0.0, 0.0, s_fLength), s_fLength *0.05, vecColorZ);
	auto nodeZ1 = createCone_local(osg::Vec3(0.0, 0.0, s_fLength), osg::Vec3(0.0, 0.0, s_fLength  * 1.2), s_fLength *0.08, vecColorZ);
	osg::ref_ptr<osg::Geode>  geoTextZ = createCornidateText_local(osg::Vec3(0.0, 0.0, s_fLength  * 1.2), s_strZ, 1.5, vecColorZ);

	osg::ref_ptr<osg::Group> node_Z = new osg::Group();
	node_Z->addChild(nodeZ);
	node_Z->addChild(nodeZ1);
	node_Z->addChild(geoTextZ);

	osg::ref_ptr<osg::Group> node_group = new osg::Group();
	node_group->addChild(node_x);
	node_group->addChild(node_Y);
	node_group->addChild(node_Z);

	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints();
	hints->setDetailRatio(1.0f);
	osg::ref_ptr<osg::ShapeDrawable> oneShape = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0, 0, 0), 5), hints.get());
	oneShape->setColor(osg::Vec4(0.5, 1.0, 0.2, 1.0));
	osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;
	pGeode->addDrawable(oneShape.get());
	return node_group.release();
}


osg::Camera* createCoornidate(osg::Node* pNode, int tex_width = 100, int tex_height = 100)
{
	if (nullptr == pNode)
	{
		return nullptr;
	}
	osg::ref_ptr<osg::Node> pCoNode = makeCoordinate_local();
	osg::Vec4 clearColour = { 1.0f,0.2f,0.2f,1.0f };
	osg::Camera* pCoornidateCamera = new osg::Camera;
	pCoornidateCamera->setClearColor(clearColour);
	pCoornidateCamera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	pCoornidateCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	pCoornidateCamera->setViewport(-20, -20, tex_width, tex_height);
	pCoornidateCamera->addChild(pCoNode);
	pCoornidateCamera->setAllowEventFocus(false);
	pCoornidateCamera->setRenderOrder(osg::Camera::POST_RENDER);

	auto boundingSphere = pCoNode->getBound();
	auto dist = boundingSphere.radius() * 3.5f;
	pCoornidateCamera->setViewMatrixAsLookAt(osg::Vec3(0.0f, 0.0f, 0.0f) + osg::Vec3d(0.0, -dist, 0.0f),
		osg::Vec3(0.0f, 0.0f, 0.0f),
		osg::Vec3d(0.0f, 0.0f, 1.0f));

	updateSubCamera(pCoornidateCamera, pCoNode);
	return pCoornidateCamera;
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
	traits->samples = 4; 

    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setGraphicsContext(
        new osgQt::GraphicsWindowQt(traits.get()));
    camera->setClearColor(osg::Vec4(0.8, 0.5, 0.1, 1.0));
    camera->setViewport(new osg::Viewport(
        0, 0, traits->width, traits->height));
    camera->setProjectionMatrixAsPerspective(
        30.0f, static_cast<double>(traits->width) /
        static_cast<double>(traits->height), 1.0f, 10000.0f);
	camera->getOrCreateStateSet()->setGlobalDefaults();
    return camera.release();
}

void updateViewerCamera(osg::Camera* pCoornidateCamera, osg::Node* pNode)
{
	if (nullptr == pCoornidateCamera || nullptr == pNode)
	{
		return;
	}

	auto pShereBound = pNode->getBound();
	auto fRadius = pShereBound.radius();

	osg::Vec4 clearColour = { 0.2f,0.2f,0.2f,1.0f };
	pCoornidateCamera->setClearColor(clearColour);
	pCoornidateCamera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	pCoornidateCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);

	auto fExtent = fRadius + 5;
	pCoornidateCamera->setProjectionMatrixAsOrtho(-fRadius, fRadius, -fRadius, fRadius, 0, 1000);
}


ViewerWidget::ViewerWidget(QWidget* pParent):QWidget(pParent)
{
  //  auto scene = osgDB::readNodeFile("F:\\development\\osgStudy\\data\\cow.osg");
    //auto scene = createCylinder(osg::Vec3(0, 0, 0), osg::Vec3(100, 0, 0), 10);
   // auto scene = GetOsgSphereSegment();
    auto scene = SelfSkinVessel::getTheSelfSkinNode();
    if(nullptr == scene)
    {
      return ;
    }

	osg::ref_ptr<osg::Group> root = new osg::Group();
	osg::ref_ptr<osg::Camera> pCordinate = createCoornidate(scene, 100, 100);
	root->addChild(scene);
	root->addChild(pCordinate);

    auto pCamera = createCamera(50, 50, 640, 480);
    if(nullptr == pCamera)
    {
      return ;
    }

	pCamera->addCullCallback(new CameraCorCallback(pCordinate));
	updateViewerCamera(pCamera,root);
	m_viewer.setLightingMode(osg::View::NO_LIGHT);
    m_viewer.setCamera(pCamera);
    m_viewer.setSceneData(root);
    
    //m_viewer.addEventHandler(new osgViewer::StatsHandler);
	auto pDrawLine = new CDrawLineHandler(&m_viewer);
	m_viewer.addEventHandler(pDrawLine);
	
	m_viewer.setCameraManipulator(
		new LoacalTrackingManipulator);


    osgQt::GraphicsWindowQt* gw =
        dynamic_cast<osgQt::GraphicsWindowQt*>(
            pCamera->getGraphicsContext());
    if (nullptr != gw)
    { 
		//QGLFormat format = gw->getGLWidget()->format();
		//// format.setDepthBufferSize(0); //不使用深度缓存
		//// format.setStencilBufferSize(0);
		// //format.setSamples(4); //4重采样
		//gw->getGLWidget()->context()->setFormat(format);

        QVBoxLayout* layout = new QVBoxLayout;
        layout->addWidget(gw->getGLWidget());
        setLayout(layout);
    }

	//osg::ref_ptr< osg::DisplaySettings > displaySettings = new osg::DisplaySettings;
	//displaySettings->setNumMultiSamples(16);
	//m_viewer.setDisplaySettings(displaySettings.get());

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

