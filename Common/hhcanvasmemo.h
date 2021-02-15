#ifndef HHCANVASMEMO_H
#define HHCANVASMEMO_H

#include "lib_FoundationPreAndTeaching.h"
#include "hhcanvas.h"

class LIB_FoundationPreAndTeaching_EXPORT HHCanvasMemo : public HHCanvas
{
    Q_OBJECT
    Q_INTERFACES( IHHCanvas )

public:
    HHCanvasMemo( QWidget *parent = 0 );
    virtual ~HHCanvasMemo();

public:
    QColor              m_changeColor;
    virtual void changeEnvironment( QColor changeColor );
    virtual void directChangeContent( QString reason, QRectF changeRect, QVariant param, bool bUpdateThumnail = false );
    virtual void indirectChangeContent( QRectF changeRect = QRectF(), bool bUpdateThumnail = false, QString reason = "" );
    //virtual void addItem( IHHPrimitiveItem *item, QVariantMap param );
    virtual void setParameters( QString type, QVariant value );
    virtual QVariant getParameters( QString type );
/*
    virtual void drawItems(QPainter *painter, int numItems,
                           QGraphicsItem *items[],
                           const QStyleOptionGraphicsItem options[]);
                           */
    virtual void slotStateChanged( QString strState, QVariant strSource, QVariant strNew );

	void  setActiveSlide(IHHSlide* slide);
protected:
    bool viewportEvent(QEvent *event) Q_DECL_OVERRIDE;
};

#endif // HHCANVASMEMO_H
