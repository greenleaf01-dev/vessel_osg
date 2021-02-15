#ifndef IHHITEMANIMATIONCONTROLLER_H
#define IHHITEMANIMATIONCONTROLLER_H

#include <QObject>
#include "itemanimationstruct.h"
#include "ihhslide.h"

class IHHPrimitiveItem;
class IHHCanvas;
class IHHFrameUserActionController;

class IHHItemAnimationController
{
public:
    ~IHHItemAnimationController() {}
    virtual QObject* getObject() = 0;

    //元素界面修改特效数据
    virtual void setItemAnimation(QVariantMap& params,bool isNeedPreview) = 0;
    //预览
    virtual void previewAnimation(QString strAnimationID) = 0;
    //停止预览
    virtual void stopPreviewAnimation() = 0;
    //授课下点击向下翻页键播放特效
    virtual bool playAnimationByPageDown() = 0;
    //授课下点击向上翻页键
    virtual bool playAnimationByPageUp() = 0;
    //通过上箭头修改顺序
    virtual void modifyOrderByUp(QVariantMap oldParams,QVariantMap newParams) = 0;
    //通过上箭头修改顺序
    virtual void modifyOrderByDown(QVariantMap oldParams,QVariantMap newParams) = 0;
    //获取当前页的触发源信息
    virtual QList<QStringList> getAllTriggerSource() = 0;
    //获取当前页的所有特效信息
    virtual QList<TriggerSource> getAllAnimations(IHHSlide* slide = NULL) = 0;
    //itemanimationcanvasmanager调用：通知界面选中特效
    virtual void setAnimationsSelectedFromCanvas(QStringList animationIds) = 0;
    //列表界面调用：通知itemanimationcanvasmanager高亮显示触发源
    virtual void setTriggerSourcePreview(QString itemID) = 0;
    //对象特效界面调用：通知itemanimationcanvasmanager选中特效高亮显示
    virtual void setAnimationSelectedFromUi(QString itemID,QString animationID) = 0;
    //对象特效界面调用：设置特效number的visible
    virtual void setAnimationNumberVisible(bool visible) = 0;
    //对象特效界面调用：设置itemNumber的visible
    virtual void setItemNumberVisible(bool visible) = 0;
    //列表界面修改对象特效数据
    virtual void setItemAnimationById(QStringList animationIDs,QString key,QString value) = 0;
    //授课点击触发源播放特效
    virtual bool playAnimationByTriggerSource(QString strTriggerSource) = 0;
    //特效数据发生变化时刷新界面以及itemanimationcanvasmanager
    virtual void updateByAnimationDataChanged() = 0;
    //获取当前选中的特效ID
    virtual QStringList getSelectedAnimationsID() = 0;

    //设置页面特效
    virtual void setSlideAnimation(Effect params,bool isGlobal) = 0;
    //停止播放页面特效
    virtual void stopSlideAnimation() = 0;

    //获取当前页items
    virtual QVector<IHHPrimitiveItem*> getSelItems() = 0;
    //
    virtual void switchModeToTeaching(bool playSlideAniation = true) = 0;

    virtual void playSlideAnimationAfterShow() = 0;

    virtual void switchModeToPre() = 0;
    //获取当前页由翻页键触发的对象特效count
    virtual int getAnimationByPageDownSize(int & playIndex) = 0;
    //新建或打开课件时，清空动画指针
//    virtual void presentionChanged() = 0;
	// Canvas 比例变化刷新特效编号.
    virtual void canvasMatrixChanged(float rate) = 0;
    //设置用户行为统计接口
    virtual void setUserActionController(IHHFrameUserActionController* userAction)  = 0;
    virtual void presentionChanged() = 0;

    virtual void resetItemAnimations(IHHSlide* slide) = 0;

};

Q_DECLARE_INTERFACE( IHHItemAnimationController, "com.hht.qtWhiteBoard.IHHItemAnimationController/1.0" )
Q_DECLARE_METATYPE( IHHItemAnimationController* )

#endif // IHHITEMANIMATIONCONTROLLER_H
