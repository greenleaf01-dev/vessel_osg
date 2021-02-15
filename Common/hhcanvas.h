#ifndef HHCANVAS_H
#define HHCANVAS_H

#include "hhsimplecanvas.h"
#include <QVariantMap>

class HHSignalManager;
class HHEventManager;
class HHCursorManager;
class LIB_EXPORT HHCanvas : public HHSimpleCanvas, public IHHCanvasImdDraw
{
	Q_OBJECT
    Q_INTERFACES(IHHCanvas)

public:
	HHCanvas(QWidget *parent = 0);
	~HHCanvas();
	void initCanvas();

public:
    //设置画布的矩阵
    void setCanvasMatrix(QMatrix matrix);
	//清除页面选中项
    void clearSlideSelection();

	//获取Canvas的Matrix
    QMatrix getCanvasMatrix();
	//获取当前激活Slide
	HHSlide* getActiveHHSlide();
	//选中的对象和区域，转发对象选中菜单信号
	void ItemSelected(QVector< IHHPrimitiveItem* > items, QRectF anchorRect);
	//清除场景的内容
	void clearScene();
	//滚轮消息的缩放调用函数
	void zoomInOut(int delta);

    void setActiveSlide(IHHSlide* slide, bool bCmd = false);
	void switchSlide(IHHSlide *current, IHHSlide *target);
	bool isPassEventToQItem(QPoint pt);

	//event fillter
	int setEventFillter(IHHEventFillter *eventfillter);
	int onMousePressEventAfterFilter(QMouseEvent * event, HHTouchPoint& point);
	int onMouseMoveEventAfterFilter(QMouseEvent * event, HHTouchPoint& point);
	void setCursorWhenMouseMove(QMouseEvent * event);
	int onMouseReleaseEventAfterFilter(QMouseEvent * event, HHTouchPoint& point);
	int onTouchEventAfterFilter(QTouchEvent *event, HHTouchPoint& point);

	//用于参考线，辅助线等，直接在canvas上绘制
	void drawForeground(QPainter *painter, const QRectF &rect);
	void drawBackground(QPainter *painter, const QRectF &rect);

	//event cache
    virtual IHHEventCache *getEventCache();
	virtual int setEventCache(IHHEventCache *eventcache);
	virtual int onTouchEventAfterCache(QTouchEvent *touchEvent, HHTouchPoint& point);
	virtual bool isPopupLongPressMenu(HHTouchPoint& point);
	virtual int onLongPressPopupMenu(QTouchEvent *touchEvent, HHTouchPoint& point);
	virtual QMatrix fitWorkArea(float marginRate, bool bSet,QRectF rectWork);

public Q_SLOTS:
	// 响应Item选择变化时的信号,slide 发出来的信号对应的槽
	void slotSelectionChanged();
	// 响应文档类切换Slide的信号对应的槽函数,产生对应的激活等信号
    void sltActiveSlide(IHHSlide *slide);

Q_SIGNALS:
	//上一页卸载，即将加载下一页时发送信号
	void sigDeactiveSlide(IHHSlide *slide);
	//当前页加载完成，激活当前页的时候发送的信号
	void sigActiveSlide(IHHSlide *slide);
	//对象的菜单消息
	void signalShowItemsMenu(QVector< IHHPrimitiveItem* > items, QRectF anchorRect);
	//转发Slide当前选中的消息
	void signalItemsSelected(QVector< IHHPrimitiveItem* > items);
	//超链接发生的消息，外部直接通过指针发送
	void signalItemHyperlink(IHHPrimitiveItem* item);
	//当前画布矩阵发生变化的时候发送信号
	void signalCanvasMatrixChanged(float rate);

protected:
	bool viewportEvent(QEvent *event) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void wheelEvent(QWheelEvent *event) override;
    void scrollContentsBy(int dx, int dy);

private:
    int beforePopupMenu(QPointF pos);
	bool isRealPopupContextMenu(QPoint pt);
	bool isSatisfiedPopContext(QPoint pt);

private:
	HHEventManager	*m_eventManager;
    HHCursorManager	*m_cursorManager;


//2018-07-05 GJB  Immediate draw interface implementation
public:
    /* @brief  Immediate drawing on GraphicsView.
     * @param  rcUpdate  -- drawing bounding rect.
     * @param  fnDrawImp -- function which User provided to  do drawing.
    */
    virtual void drawImmediate( const QRectF& rcSceneUpdate, std::function< void (QPainter * p ) >  fn ) Q_DECL_OVERRIDE;
    virtual void paintEvent   ( QPaintEvent *event ) Q_DECL_OVERRIDE;

private:
    void setImdDrawFunc   ( std::function< void (QPainter * p ) >  fn )
    {
        m_fnImdDrawFunc = fn ;
    }
    void clearImdDrawFunc( )
    {
        m_fnImdDrawFunc = std::function< void (QPainter * p )> ();
    }
private:
    std::function< void (QPainter * p ) >    m_fnImdDrawFunc;

};

#endif // HHCANVAS_H
