#ifndef IHHDELETEPIXEL_H
#define IHHDELETEPIXEL_H
#include <QObject>

class IHHPrimitiveItem;
class QJsonObject;

class IHHDeletePixel {
public:
    virtual ~IHHDeletePixel(){}
    virtual void initClipRegion( IHHPrimitiveItem *item ) = 0;
    virtual void performPixelDelete( IHHPrimitiveItem *pixelStroke, IHHPrimitiveItem *item ) = 0;
    virtual void performUndoPixelDelete( IHHPrimitiveItem *item ) = 0;
    virtual void performRedoPixelDelete( IHHPrimitiveItem *item ) = 0;
    virtual bool isNeedRestore() = 0;
    virtual void restorePixelStroke( QVector< IHHPrimitiveItem* > pixels ) = 0;
    virtual bool isActionPixelDeleteStroke( IHHPrimitiveItem *pixelStroke ) = 0;
    virtual void getJSONObj( QJsonObject& jsonObj ) = 0;// 得到JSON对象
    virtual void fromJSONObj( QJsonObject& jsonObj ) = 0;// 从JSON对象获取数据

    virtual bool performPixelDeleteStart( QPointF currentPoint, int width ) = 0;
    virtual bool performPixelDeleteing( QPointF prePoint, QPointF currentPoint, int width ) = 0;
    virtual bool performPixelDeleteEnd( QPointF currentPoint, int width ) = 0;
	//
    virtual bool performPixelDelete( QPointF prePoint, QPointF currentPoint, int width ) = 0;
    virtual QVector< IHHPrimitiveItem* > getPixelDeleteItems() = 0;
};

Q_DECLARE_INTERFACE(IHHDeletePixel, "com.hht.qtWhiteBoard.IHHDeletePixel/1.0")
Q_DECLARE_METATYPE(IHHDeletePixel*)

#endif // IHHDELETEPIXEL_H
