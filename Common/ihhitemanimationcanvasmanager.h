#ifndef IHHITEMANIMATIONCANVASMANAGER_H
#define IHHITEMANIMATIONCANVASMANAGER_H

#include <QObject>
#include <QPainter>

class IHHCanvas;
class IHHItemAnimationController;
class IHHPrimitiveItem;
class IHHScenario;

class IHHItemAnimationCanvasManager
{
public:
    // Canvas 使用.
    //
    // 遍历Item 取IHHItemAnimationManager数据绘制特效Number(1,2,3,*); 绘制 Item 编号("形状1"等)).
    // 触发源标志:每次修改触发源Order维护所有成为触发源的Item指针vector，直接get并绘制.
    virtual void paintNumber(QPainter* painter) = 0;

    // 判断并处理Canvas鼠标点击事件,通过Controller设置右侧面板列表选中状态
    // 根据Item特效个数计算序号rect判断点击位置(具体序号,Item本身,无).
	virtual int getClickType(QPointF point) = 0;
	virtual void mousePress(QPointF point) = 0;
	virtual void mouseMove(QPointF point) = 0;
	virtual void mouseReleas(QPointF point) = 0;
	
    // IHHItemAnimationController 使用.
    //
    virtual void setIHHItemAnimationController(IHHItemAnimationController *controller, IHHScenario *&pCurScenario) = 0;

    // 顺序列表设置具体特效选中状态(选中Item 高亮特效number).
    virtual void setItemAnimationSelected(QString itemId, QString animationId) = 0;

	// 预览特效时使用.
	virtual void setNumberVisible(bool visible = true) = 0;

    // 是否绘制特效编号(IHHItemAnimationManager获取).
    virtual void setAnimationNumberVisible(bool visible = true) = 0;

    // 更改触发源时Item高亮.(""取消高亮)
    virtual void setItemHighlight(QString itemId) = 0;

    // 切换到特效列表时获取当前选中的特效ID(被选中Item信号覆盖).
    virtual QStringList getSelectedAnimationsID() = 0;

    // 特效改变刷新显示.
    virtual void updateTriggerSource() = 0;
    virtual void updateAnimationNumber() = 0;

    // 页面比例变化刷新触发源标识.
	virtual void refreshTriggerRect() = 0;

	//通知授课模式
	virtual void notifyTeachingMode(const QString &sModule) = 0;
};

Q_DECLARE_INTERFACE( IHHItemAnimationCanvasManager, "com.hht.qtWhiteBoard.IHHItemAnimationCanvasManager/1.0" )
Q_DECLARE_METATYPE( IHHItemAnimationCanvasManager* )

#endif // IHHITEMANIMATIONCANVASMANAGER_H
