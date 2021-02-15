#ifndef HHSIMPLECANVAS_H
#define HHSIMPLECANVAS_H

#include "lib_global.h"
#include <QGraphicsView>
#include "ihhcanvas.h"

class HHSlide;
class HHPresentation;
class HHDispatcher;
class HHGesture;
class IHHPrimitiveItem;
class QCloseEvent;

class LIB_EXPORT HHSimpleCanvas : public QGraphicsView, public IHHCanvas
{
    Q_OBJECT
    Q_INTERFACES( IHHCanvas )

public:
    HHSimpleCanvas( QWidget *parent = 0 );
    virtual ~HHSimpleCanvas();

public:
	//暂时添加 是否是备课模式 true 备课  false 授课
	virtual bool isPrepareMode();
	virtual void setPrepareMode(bool flag);
    virtual void clearScene();
    virtual IHHSlide* getActiveSlide();
    virtual void setActiveSlide( IHHSlide* slide, bool bCmd = false );
    virtual IHHDispatcher* getDispatcher();
    virtual IHHGestureOperator* getGestureOperator();
    virtual int                 setTransparentEnble( bool bTransparent, bool bThrought = false );
    virtual QObject* getObject();
    virtual IHHPresentation * getPresentation();
    virtual void bindPresentation( IHHPresentation *pre );
    virtual void switchSlide( IHHSlide *current, IHHSlide *target );
    virtual void drawSlide( QPainter *painter, IHHSlide *slide, QRectF target, QString strRange );

    virtual int setAssistantLine( IHHAssistantLine *AssistantLine);
    virtual IHHAssistantLine* getAssistantLine();
    virtual int setParamtersLine( IHHParamtersLine *ParamtersLine );
    virtual IHHParamtersLine* getParamtersLine();

    virtual IHHEventFillter*    getEventFilter();
    virtual int setEventFillter( IHHEventFillter *eventfillter );
    virtual int onMousePressEventAfterFilter(QMouseEvent * event, HHTouchPoint& point);
    virtual int onMouseMoveEventAfterFilter(QMouseEvent * event, HHTouchPoint& point);
    virtual void setCursorWhenMouseMove( QMouseEvent * event );
    virtual int onMouseReleaseEventAfterFilter(QMouseEvent * event, HHTouchPoint& point);
    virtual int onTouchEventAfterFilter(QTouchEvent *event, HHTouchPoint& point);

    virtual IHHEventCache *getEventCache();
    virtual int setEventCache( IHHEventCache *eventcache );
    virtual int onTouchEventAfterCache(QTouchEvent *touchEvent,HHTouchPoint& point);
    virtual bool isPopupLongPressMenu( HHTouchPoint& point );
    virtual int onLongPressPopupMenu(QTouchEvent *touchEvent, HHTouchPoint& point);

    virtual int setItemAnimationCanvasManager( IHHItemAnimationCanvasManager *manager );
    virtual IHHItemAnimationCanvasManager* getItemAnimationCanvasManager();

    virtual void viewMousePressEvent(QMouseEvent *event) ;
    virtual void viewMouseMoveEvent(QMouseEvent *event) ;
    virtual void viewMouseReleaseEvent(QMouseEvent *event) ;
    virtual bool viewViewPortEvent(QEvent *event);
    virtual void viewSetCursor(const QCursor &cursor);
    virtual QCursor viewGetCursor();

    virtual QMatrix fitWorkArea(float marginRate, bool bSet, QRectF rectWork);
    virtual void setGeometryRect( QRect rect );
    virtual float               getScaleRate();
    virtual void                setScaleRate( float rate );
    virtual void                setSlideMatrix(QMatrix matrix);
    virtual QMatrix             getSlideMatrix();
    virtual QMatrix             getWholeMatrix();
    virtual QMatrix             getCanvasMatrix();
    virtual void                setCanvasMatrix( QMatrix canvasMatrix );
	//获取boundRect大小
	virtual	QRect				getBoundingBox();
    virtual bool                isPassEventToQItem( QPoint pt );
    virtual void                changeRoveType( QString strType );

public:
    virtual void initCanvas();
    virtual bool viewportPaintEvent( QEvent *event );

Q_SIGNALS:

public Q_SLOTS:
    virtual void sltPreActiveSlide( IHHSlide *slide );

protected:
    bool viewportEvent(QEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void closeEvent(QCloseEvent *event);

    void wheelEvent(QWheelEvent *event);

public:
	HHPresentation                  *m_pPre;    
	HHSlide                         *m_pSlide;
    friend class HHDispatcher;
    friend class HHGesture;
    QMatrix                         m_matrixCanvas;
    QMatrix                         m_matrixWhole;

protected:
    bool isNeedCache();

protected:
    HHGesture                       *m_pGesture;
    HHDispatcher                    *m_pDispatcher;

    IHHParamtersLine                *m_pParamtersLine; //参考线
    IHHAssistantLine                *m_pAssistantLine; //辅助线
    IHHEventCache                   *m_pEventCache;//事件缓存
    IHHEventFillter                 *m_pEventFillter;//事件过滤
    IHHItemAnimationCanvasManager   *m_pItemAnimationCanvasManager;
    bool                            m_bTransparent;
    bool                            m_bThroughtFlag; // 用于透明时穿透标识
	bool							m_bParpreModeFlag;
    QString                         m_strRov;
};

#endif // HHSIMPLECANVAS_H
