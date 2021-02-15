#pragma once

#include <QObject>

class IHHSlide;
class QGraphicsItem;

class IHHCurtainItem {
public:
    virtual ~IHHCurtainItem(){}
    virtual void setParameters( QString type, QVariant value ) = 0;// 设置参数
    virtual QVariant getParameters( QString type ) = 0;// 得到参数
    virtual void getJSONObj( QJsonObject& jsonObj ) = 0;// 得到JSON对象
    virtual void fromJSONObj( QJsonObject& jsonObj ) = 0;// 从JSON对象获取数据
    virtual QGraphicsItem* getItem() = 0;                    //获取Item
    virtual void setSlide(IHHSlide *pSlide) = 0;             //设置Slide
    virtual void setScale(float fOld, float fNew) = 0;
    virtual void setItemMatrix(float rate) = 0;
    virtual void  translate(float xOffset, float yOffset) = 0;
    virtual void  scale(QPointF ptnRef, float fScaleX, float fScaleY) = 0;
};

Q_DECLARE_INTERFACE( IHHCurtainItem, "com.hht.qtWhiteBoard.IHHCurtainItem/1.0" )
Q_DECLARE_METATYPE( IHHCurtainItem * )
