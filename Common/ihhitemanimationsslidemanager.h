#ifndef IHHITEMANIMATIONSSLIDEMANAGER_H
#define IHHITEMANIMATIONSSLIDEMANAGER_H

#include <QObject>

class IHHPrimitiveItem;
class IHHSlide;
class IHHItemAnimationController;

typedef struct itemAnimation_
{
    QString ID;
    IHHPrimitiveItem* item;
    bool    isDelete = false;
    QString triggerSource = "";

    bool operator==(const itemAnimation_ p)
    {
        return (p.ID==ID && p.item==item && p.isDelete == isDelete && p.triggerSource == triggerSource);
    }
}itemAnimation;

class IHHItemAnimationsSlideManager
{
public:
    virtual QStringList getAllTriggerSource() = 0;
    virtual QVector<itemAnimation> & getAllAnimations() = 0;
    virtual void setAnimations(const QVector<itemAnimation>& list) = 0;
    virtual void addAnimation(QString strAnimationId,IHHPrimitiveItem* item,bool isDeleted) = 0;
    virtual void deleteAnimation(QString strAnimationId) = 0;
    //删除item
    virtual void deleteItem(IHHPrimitiveItem* item) = 0;
    //增加item
    virtual void addItem(IHHPrimitiveItem* item,bool isDeleted) = 0;
    //粘贴item
    virtual void pasteItem(IHHPrimitiveItem* item,bool isDeleted = false) = 0;
    //复原item
    virtual void restoreItem(IHHPrimitiveItem* item) = 0;
    //调整特效顺序
    virtual void modifyOrder(int oldIndex,int newIndex,QString strModifyType) = 0;
    //通过特效id获得item
    virtual IHHPrimitiveItem* getItemByAnimationId(QString strAnimationId) = 0;
    //重置item的特效id
    virtual void setItemsAnimationNumber() = 0;
    //save to json
    virtual void getJSONObj(QJsonObject& jsonObj) = 0;
    //load from json
    virtual void fromJSONObj(QJsonObject& jsonObj) = 0;
    //设置controller
    virtual void setItemAnimationController(IHHItemAnimationController* ctrl) = 0;
    //获取controller
    virtual IHHItemAnimationController* getItemAnimationController() = 0;
    //items创建完成后，重置animationList数据
    virtual void initDataAfterItemsfromJson(bool isPaste) = 0;
    //克隆、镜像item时删除特效数据
    virtual void clearItemAnimationData(IHHPrimitiveItem* item) = 0;
    //粘贴页时，处理组合对象的子item数据
    virtual void pasteGroupSonItemData(IHHPrimitiveItem* item,bool isRootItem = true) = 0;
};

Q_DECLARE_INTERFACE( IHHItemAnimationsSlideManager, "com.hht.qtWhiteBoard.IHHItemAnimationsSlideManager/1.0" )
Q_DECLARE_METATYPE( IHHItemAnimationsSlideManager* )
Q_DECLARE_METATYPE( itemAnimation )

#endif // IHHITEMANIMATIONSSLIDEMANAGER_H
