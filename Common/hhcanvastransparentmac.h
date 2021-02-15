#ifndef HHCANVASTRANSPARENTMAC_H
#define HHCANVASTRANSPARENTMAC_H

#include "lib_FoundationTransparent.h"

class LIB_FoundationTransparent_EXPORT HHCanvasTransparentMac : public HHCanvasTransparent
{
    Q_OBJECT
    Q_INTERFACES( IHHCanvas )

public:
    HHCanvasTransparentMac( QWidget *parent = 0 );
    virtual ~HHCanvasTransparentMac();

public:
    virtual void changeEnvironment( QColor changeColor );
    virtual void indirectChangeContent( QRectF changeRect = QRectF(), bool bUpdateThumnail = false, QString reason = "" );

protected:
    bool viewportEvent(QEvent *event) Q_DECL_OVERRIDE;
};

#endif
