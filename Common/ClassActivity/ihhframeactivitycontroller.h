#pragma once

#include <QObject>

class IHHCanvas;
class IHHPrimitiveItem;
class IHHActivitySoundEffectController;

class IHHFrameActivityController{
public:

    ~IHHFrameActivityController() {}

    virtual QObject *getObject() = 0;

    virtual int controllerActiveSlide(IHHCanvas *pIHHCanvas) = 0;
    virtual int controllerDeactiveSlide(IHHCanvas *pIHHCanvas) = 0;

    virtual int down( QPointF point, IHHPrimitiveItem *pIHHItem) = 0;
    virtual void move( QPointF point, IHHPrimitiveItem *pIHHItem) = 0;
    virtual int up( QPointF point, IHHPrimitiveItem *pIHHItem) = 0;

    virtual IHHPrimitiveItem* getContainerMatchingItem(const QString &sItemID) = 0;
    virtual QRectF getMaterialItemRect(const QString &sItemID) = 0;
    virtual void setContainerMatching(const QString &sContainerItemID,
                                      const QString sMaterialItemID) = 0;
    virtual IHHPrimitiveItem *getMaterialItem(const QString &sItemID) = 0;
    virtual void setMaterialItemOrder(const QStringList &lOrder,
                                      const QMap<QString, QRectF> &id2RectMap) = 0;

    virtual void resetActvityStatus()= 0;
    virtual void checkActivityStatus() = 0;
    virtual void viewActivityAnswerInfo() = 0;
	virtual void clearInitData(bool isOpenFile) = 0;
};

Q_DECLARE_INTERFACE( IHHFrameActivityController,
                     "com.hht.qtWhiteBoard.IHHFrameActivityController/1.0" )
Q_DECLARE_METATYPE( IHHFrameActivityController* )
