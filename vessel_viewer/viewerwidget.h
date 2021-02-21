#ifndef VIEWERWIDGET_H
#define VIEWERWIDGET_H

#include <QWidget>
#include <QThread>
#include <QTimer>
#include <osgViewer/Viewer>

class RenderThread : public QThread
{
public:
	RenderThread() : QThread(), viewerPtr(nullptr) {}
	virtual ~RenderThread()
	{
		if (viewerPtr)
		{
			viewerPtr->setDone(true);
		}
		wait();
	}
	osgViewer::Viewer* viewerPtr;
protected:
	virtual void run()
	{
		if (viewerPtr)
		{
			viewerPtr->run();
			int a = 0;
		}
	}
};




class ViewerWidget : public QWidget
{
    Q_OBJECT
public:
    ViewerWidget(QWidget* pParent = nullptr);
	void closeLocalEvent(QCloseEvent *event);
protected:
    virtual void closeEvent(QCloseEvent *event);
//	virtual void paintEvent(QPaintEvent* event);
protected:

	class CLocalView:public osgViewer::Viewer
	{
	public:
		CLocalView() {}
		virtual ~CLocalView() {}

		virtual void setUpThreading() 
		{
			//Contexts contexts;
			//getContexts(contexts);

			//if (_threadingModel == SingleThreaded)
			//{
			//	if (_threadsRunning) stopThreading();
			//	else
			//	{
			//		// we'll set processor affinity here to help single threaded apps
			//		// with multiple processor cores, and using the database pager.
			//		int numProcessors = OpenThreads::GetNumberOfProcessors();
			//		bool affinity = numProcessors>1;
			//		if (affinity)
			//		{
			//			OpenThreads::SetProcessorAffinityOfCurrentThread(0);

			//			Scenes scenes;
			//			getScenes(scenes);

			//			for (Scenes::iterator scitr = scenes.begin();
			//				scitr != scenes.end();
			//				++scitr)
			//			{
			//				if ((*scitr)->getSceneData())
			//				{
			//					// update the scene graph so that it has enough GL object buffer memory for the graphics contexts that will be using it.
			//					(*scitr)->getSceneData()->resizeGLObjectBuffers(osg::DisplaySettings::instance()->getMaxNumberOfGraphicsContexts());
			//				}
			//			}
			//		}
			//	}
			//}
			//else
			//{
			//	if (!_threadsRunning) startThreading();
			//}
		}
	};

    CLocalView m_viewer;
    RenderThread  m_thread;
	QTimer m_timer; 

public:
	static QWidget* getOsgWiget();
};

#endif // VIEWERWIDGET_H
