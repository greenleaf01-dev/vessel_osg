#ifndef HHDELETEPIXELIMPL_H
#define HHDELETEPIXELIMPL_H

#include <QVector>
#include <QRectF>
#include <QPainterPath>
#include <QMatrix>

#include "ihhdeletepixel.h"


class HHPixelDeleteInfo
{
public:
    IHHPrimitiveItem                    *m_pDeleteingItem;
    QString                             m_uPixelDeleteNetID;
    QMatrix                             m_thenTransform;
//    QRegion                             m_regionClip;
    QPainterPath                        m_pathPixel;
    QPainterPath                        m_pathPixel1;
    int                                 m_nWidth;

public:
    HHPixelDeleteInfo();
    HHPixelDeleteInfo( QString uPixelDeleteNetID, QMatrix thenTransform );
    HHPixelDeleteInfo( IHHPrimitiveItem *pDeleteingItem, QMatrix thenTransform, bool bStep );
    QPainterPath getPixelStrokePath( IHHPrimitiveItem *pixelStroke, QMatrix matrix, bool bStep );
    virtual ~HHPixelDeleteInfo();
};

class QRegion;
class HHDeletePixelImpl : public IHHDeletePixel
{
public:
    HHDeletePixelImpl();
    virtual ~HHDeletePixelImpl();

protected:
    QVector< HHPixelDeleteInfo* >       m_vPixelDeleteInfos;
    int                                 m_clipChainsMark;
    QPainterPath                        m_clipPath;
//    QRegion                             m_regionClip;
    bool                                m_bFirstPixelDelete;

protected:
    QMatrix getItemWholeMatrix( IHHPrimitiveItem *item );

public:
    virtual void initClipRegion( IHHPrimitiveItem *item );
    virtual void performPixelDelete( IHHPrimitiveItem *pixelStroke, IHHPrimitiveItem *item );
    virtual void performUndoPixelDelete( IHHPrimitiveItem *item );
    virtual void performRedoPixelDelete( IHHPrimitiveItem *item );
    virtual bool isNeedRestore();
    virtual void restorePixelStroke( QVector< IHHPrimitiveItem* > pixels );
    virtual bool isActionPixelDeleteStroke( IHHPrimitiveItem *pixelStroke );
    virtual void getJSONObj( QJsonObject& jsonObj );
    virtual void fromJSONObj( QJsonObject& jsonObj );

    virtual void fromJSONObj( QVector< IHHPrimitiveItem* > rubbers, IHHPrimitiveItem *item, QJsonObject& jsonObj );

	//
    virtual bool performPixelDeleteStart( QPointF currentPoint, int width );
    virtual bool performPixelDeleteing( QPointF prePoint, QPointF currentPoint, int width );
    virtual bool performPixelDeleteEnd( QPointF currentPoint, int width );
    virtual bool performPixelDelete( QPointF prePoint, QPointF currentPoint, int width );
    virtual QVector< IHHPrimitiveItem* > getPixelDeleteItems();
};

#endif // HHDELETEPIXELIMPL_H
