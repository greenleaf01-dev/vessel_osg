#ifndef IHHITEMCONTROLLER_H
#define IHHITEMCONTROLLER_H

#include <QObject>
#include <QVector>

class IHHSlide;
class IHHPrimitiveItem;
class IHHItemController
{
public:
    virtual ~IHHItemController(){}
    virtual int copyItem(IHHSlide *pIHHSlide) = 0;                                                                  //Item操作：复制
    virtual int pasteItem(IHHSlide *pIHHSlide,QVector<IHHPrimitiveItem*> &items) = 0;                               //Item操作：粘贴
    virtual int pasteItemByMenu(IHHSlide *pIHHSlide,int xPos,int yPos,QVector<IHHPrimitiveItem*> &items) = 0;       //Item操作：通过右键菜单粘贴
    virtual int cutItem(IHHSlide *pIHHSlide) = 0;                               //Item操作：剪切
    virtual int deleteItem(IHHSlide *pIHHSlide) = 0;                            //Item操作：删除
    virtual int moveItems(IHHSlide *pIHHSlide,QString strType) = 0;             //Item操作：移动
    virtual int selectAllItem(IHHSlide *pIHHSlide) = 0;                         //Item操作：全选
    virtual int deleteAllItem(IHHSlide *pIHHSlide) = 0;                         //Item操作：删除全部

    virtual int mirrorItems(IHHSlide *pIHHSlide,QString strType) = 0;           //Item操作：镜像

    virtual int flipItems(IHHSlide *pIHHSlide,QString strType) = 0;             //Item操作：翻转

    virtual int lockItem(IHHSlide *pIHHSlide) = 0;                              //Item操作：锁定
    virtual int unlockItem(IHHSlide *pIHHSlide) = 0;                            //Item操作：解锁

    virtual int zorderItems(IHHSlide *pIHHSlide,QString strType) = 0;           //Item操作：z-order

    virtual int groupItem(IHHSlide *pIHHSlide) = 0;                             //Item操作：组合
    virtual int cancelGroupItem(IHHSlide *pIHHSlide) = 0;                       //Item操作：取消组合

    virtual int alignItems(IHHSlide *pIHHSlide,QString strType) = 0;            //Item操作：对齐

    virtual int rotateItems(IHHSlide *pIHHSlide,float fAngle) = 0;           //Item操作：旋转

    virtual void updatePrimitiveItems(IHHSlide *pIHHSlide, QVariantMap param) = 0;//更新Items
    virtual QObject* getObject() = 0;
};
Q_DECLARE_INTERFACE( IHHItemController, "com.hht.qtWhiteBoard.IHHItemController/1.0" )
Q_DECLARE_METATYPE( IHHItemController* )

#endif // IHHITEMCONTROLLER_H
