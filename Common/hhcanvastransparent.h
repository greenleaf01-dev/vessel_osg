#ifndef HHCANVASTRANSPARENT_H
#define HHCANVASTRANSPARENT_H

#include "lib_FoundationTransparent.h"
#include "hhcanvas.h"

class LIB_FoundationTransparent_EXPORT HHCanvasTransparent : public HHCanvas
{
    Q_OBJECT
    Q_INTERFACES( IHHCanvas )

public:
    HHCanvasTransparent( QWidget *parent = 0 );
    virtual ~HHCanvasTransparent();

public:
    QColor              m_changeColor;
    QRect               m_rectDirty;
    virtual void changeEnvironment( QColor changeColor );
    virtual void directChangeContent( QString reason, QRectF changeRect, QVariant param, bool bUpdateThumnail = false );

    virtual void setParameters( QString type, QVariant value );
    virtual QVariant getParameters( QString type );

protected:
    bool viewportEvent(QEvent *event) Q_DECL_OVERRIDE;
};

#endif // HHCANVASTRANSPARENT_H
