#ifndef VIEWERWIDGET_H
#define VIEWERWIDGET_H

#include <QWidget>
#include <QThread>
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
protected:
    osgViewer::Viewer m_viewer;
    RenderThread  m_thread;

public:
	static QWidget* getOsgWiget();
};

#endif // VIEWERWIDGET_H
