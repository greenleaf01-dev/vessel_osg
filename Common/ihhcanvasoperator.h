#ifndef IHHCANVASOPERATOR_H
#define IHHCANVASOPERATOR_H

#include <QObject>

class IHHCanvas;
class IHHSlide;
class IHHPresentation;
class IHHCanvasOperator {
public:
    virtual int showNextSlide(IHHCanvas *canvas, IHHPresentation *pre, IHHSlide *current) = 0;
    virtual int showPreSlide(IHHCanvas *canvas, IHHPresentation *pre, IHHSlide *current) = 0;
    virtual int showSlide(IHHCanvas *canvas, IHHPresentation *pre, IHHSlide *target) = 0;
};
Q_DECLARE_INTERFACE( IHHCanvasOperator, "com.hht.qtWhiteBoard.IHHCanvasOperator/1.0" )
Q_DECLARE_METATYPE( IHHCanvasOperator* )

#endif // IHHCANVASOPERATOR_H
