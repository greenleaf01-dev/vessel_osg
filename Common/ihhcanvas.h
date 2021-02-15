#pragma once
#include <QObject>

class IHHPresentation;
class IHHDispatcher;
class IHHGestureOperator;
class IHHAssistantLine;
class IHHParamtersLine;
class IHHEventCache;
class IHHSlide;
class QTouchEvent;
class IHHEventFillter;
class IHHItemAnimationCanvasManager;
class QMouseEvent;
class QPainter;
class HHTouchPoint;

class IHHCanvas {
public:
    virtual ~IHHCanvas(){}
    virtual IHHDispatcher*      getDispatcher() = 0;
    virtual IHHGestureOperator* getGestureOperator() = 0;
    virtual QObject*            getObject() = 0;

    virtual int                 setAssistantLine( IHHAssistantLine *AssistantLine) = 0;
    virtual IHHAssistantLine*   getAssistantLine() = 0;
    virtual int                 setParamtersLine( IHHParamtersLine *ParamtersLine ) = 0;
    virtual IHHParamtersLine*   getParamtersLine() = 0;

    virtual IHHEventCache *     getEventCache() = 0;
    virtual int                 setEventCache( IHHEventCache *eventcache ) = 0;
    virtual int                 onTouchEventAfterCache(QTouchEvent *touchEvent,HHTouchPoint& point) = 0;
    virtual bool                isPopupLongPressMenu( HHTouchPoint& point ) = 0;
    virtual int                 onLongPressPopupMenu(QTouchEvent *touchEvent, HHTouchPoint& point) = 0;

    virtual IHHEventFillter*    getEventFilter() = 0;
    virtual int                 setEventFillter( IHHEventFillter *eventfillter) = 0;
    virtual int                 onMousePressEventAfterFilter(QMouseEvent * event, HHTouchPoint& point) = 0;
    virtual int                 onMouseMoveEventAfterFilter(QMouseEvent * event, HHTouchPoint& point) = 0;
    virtual void                setCursorWhenMouseMove( QMouseEvent * event ) = 0;
    virtual int                 onMouseReleaseEventAfterFilter(QMouseEvent * event, HHTouchPoint& point) = 0;
    virtual int                 onTouchEventAfterFilter(QTouchEvent *event, HHTouchPoint& point) = 0;

    virtual int                 setItemAnimationCanvasManager( IHHItemAnimationCanvasManager *manager ) = 0;
    virtual IHHItemAnimationCanvasManager* getItemAnimationCanvasManager() = 0;

    virtual void                viewMousePressEvent(QMouseEvent *event) = 0 ;
    virtual void                viewMouseMoveEvent(QMouseEvent *event) = 0 ;
    virtual void                viewMouseReleaseEvent(QMouseEvent *event) = 0 ;
    virtual bool                viewViewPortEvent(QEvent *event) = 0;
    virtual void                viewSetCursor(const QCursor &cursor) = 0;
    virtual QCursor             viewGetCursor() = 0;

    virtual IHHSlide*           getActiveSlide() = 0;
    virtual void                setActiveSlide( IHHSlide* slide, bool bCmd = false ) = 0;
    virtual void                switchSlide( IHHSlide *current, IHHSlide *target ) = 0;
    virtual void                clearScene() = 0;
    virtual void                bindPresentation( IHHPresentation *pre ) = 0;
    virtual IHHPresentation*    getPresentation() = 0;
    virtual int                 setTransparentEnble( bool bTransparent, bool bThrought = true ) = 0;
    virtual void                initCanvas() = 0;
    virtual void                drawSlide( QPainter *painter, IHHSlide *slide, QRectF target, QString strRange ) = 0;

    virtual QMatrix             fitWorkArea(float marginRate, bool bSet, QRectF rectWork) = 0;
    virtual void                setGeometryRect( QRect rect ) = 0;
    virtual void                setScaleRate( float rate ) = 0;
    virtual float               getScaleRate() = 0;
    virtual QMatrix             getWholeMatrix() = 0;
    virtual void                setSlideMatrix(QMatrix matrix) = 0;
    virtual QMatrix             getSlideMatrix() = 0;
    virtual QMatrix             getCanvasMatrix() = 0;
    virtual void                setCanvasMatrix( QMatrix canvasMatrix ) = 0;
    virtual bool                isPassEventToQItem( QPoint pt ) = 0;
	//暂时添加 是否是备课模式 true 备课  false 授课
	virtual bool                isPrepareMode( ) = 0;
	virtual void				setPrepareMode(bool flag) = 0;
	//获取boundRect大小
	virtual QRect				getBoundingBox() = 0;
    virtual void                changeRoveType( QString strType ) = 0;
};


#include <functional>
//2018-07-05 GJB  Immediate draw interface.
//implementation:
//HHCanvas:
// 1. HHCanvas::initCanvas setAttribute( Qt::WA_NoSystemBackground );
// 2. add paintEvent() to do immediate drawing.
// 3. add code  setImdDrawFunc clearImdDrawFunc


class IHHCanvasImdDraw
{
public:
    virtual ~IHHCanvasImdDraw(){};

    /* @brief  Immediate drawing on GraphicsView.
     * @param  rcUpdate  -- drawing bounding rect.
     * @param  fnDrawImp -- function which User provided to  do drawing.
    */
    virtual void drawImmediate( const QRectF& rcSceneUpdate,
         std::function< void (QPainter * p ) >  fnDrawImp ) = 0 ;
};

Q_DECLARE_INTERFACE( IHHCanvasImdDraw, "com.hht.qtWhiteBoard.IHHCanvasImdDraw/1.0" )
Q_DECLARE_METATYPE( IHHCanvasImdDraw* )




Q_DECLARE_INTERFACE( IHHCanvas, "com.hht.qtWhiteBoard.IHHCanvas/1.0" )
Q_DECLARE_METATYPE( IHHCanvas* )
