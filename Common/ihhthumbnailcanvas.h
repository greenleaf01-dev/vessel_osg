#ifndef IHHTHUMBNAILCANVAS_H
#define IHHTHUMBNAILCANVAS_H

#include <QObject>

class QGraphicsScene;
class IHHThumbnailCanvas {
public:
    virtual ~IHHThumbnailCanvas(){}
    virtual void attachScene( QGraphicsScene *scene ) = 0;
    virtual void setGeometryRect( QRect geometry ) = 0;
    virtual void setDrawRange( QRectF range ) = 0;
    virtual void changeRoveType( QString strType ) = 0;
};

Q_DECLARE_INTERFACE( IHHThumbnailCanvas, "com.hht.qtWhiteBoard.IHHThumbnailCanvas/1.0" )
Q_DECLARE_METATYPE( IHHThumbnailCanvas* )

#endif // IHHTHUMBNAILCANVAS_H
