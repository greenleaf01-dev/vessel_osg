#ifndef IHHSHAPECONTROLLER_H
#define IHHSHAPECONTROLLER_H
#include <QObject>

class IHHShapeController
{
public:
    virtual QObject* getObject() = 0;
    virtual void checkIn() = 0;
    virtual void checkOut() = 0;
    virtual void presentionChanged() = 0;

};
Q_DECLARE_INTERFACE(IHHShapeController, "com.hht.qtWhiteBoard.IHHShapeController/1.0")
Q_DECLARE_METATYPE(IHHShapeController*)

#endif // IHHSHAPECONTROLLER_H
