#ifndef HHCANVASTRANSPARENTLINUX_H
#define HHCANVASTRANSPARENTLINUX_H

#include "lib_FoundationTransparent.h"
#include "hhcanvastransparent.h"

class LIB_FoundationTransparent_EXPORT HHCanvasTransparentLinux : public HHCanvasTransparent
{
    Q_OBJECT
    Q_INTERFACES( IHHCanvas )

public:
    HHCanvasTransparentLinux( QWidget *parent = 0 );
    virtual ~HHCanvasTransparentLinux();

public:
    virtual void changeEnvironment( QColor changeColor );

protected:
    bool viewportEvent(QEvent *event) Q_DECL_OVERRIDE;
};

#endif
