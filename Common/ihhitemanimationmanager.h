#ifndef IHHITEMANIMATIONMANAGER_H
#define IHHITEMANIMATIONMANAGER_H

#include <QObject>
#include <QPainter>
#include <QList>
#include <QRectF>

class IHHPrimitiveItem;
class IHHItemAnimationManager
{
public:
    // controller 使用.
	virtual void initAnimations() = 0;
    virtual void setAnimation(QVariantMap data) = 0;
    virtual void setAnimationNumber(QString animationId, int num) = 0;
    virtual const QVariantMap getAnimationByType(QString type) = 0;
    virtual const QVariantMap getAnimationById(QString animationId) = 0;
    virtual QString getAnimationIdByNumber(int num) = 0;
    virtual const QMap<QString, QVariantMap> getAnimations() = 0;
    virtual QStringList getAnimationsID() = 0;

    // command 使用(增量更新).
    virtual const QVariantMap getAnimationOldData(const QVariantMap& newVM) = 0;
    virtual const QString getAnimationById(QString animationId, QString key) = 0;
    virtual const void setAnimationById(QString animationId, QString key, QString value) = 0;

    // IHHPrimitiveItem 使用.
	virtual IHHItemAnimationManager* clone(IHHPrimitiveItem* newItem) = 0;
    virtual void getJSONObj(QJsonObject& jsonObj) = 0;
    virtual void fromJSONObj(QJsonObject& jsonObj) = 0;
    virtual void updatePaintData() = 0;	// setBoundingBox时.
	virtual QList<QRectF> getPaintRectF() = 0; // boundingRect中

    // canvasManager 使用.
    // IHHPrimitiveItem 中被调用(更新包围盒外部特效标识区域).
	virtual QMap<QString, QRectF> getAnimationsNumberRect() = 0; // 连续4个rect.
	virtual QRectF getRefreshRect() = 0; // 获取刷新区域.删除后刷新原来区域.
	virtual QStringList getAllTriggerSource() = 0;
	virtual void setTrigger(bool t) = 0; // 触发其它特效.
	virtual void showANumber(bool show) = 0;
};

Q_DECLARE_INTERFACE( IHHItemAnimationManager, "com.hht.qtWhiteBoard.IHHItemAnimationManager/1.0" )
Q_DECLARE_METATYPE( IHHItemAnimationManager* )

#endif // IHHITEMANIMATIONMANAGER_H
