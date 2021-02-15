#ifndef IHHTEXTCONTROLLER_H
#define IHHTEXTCONTROLLER_H
#include <QObject>

class IHHTextController
{
public:
    virtual QObject* getObject() = 0;
    virtual void checkIn() = 0;
    virtual void checkOut() = 0;
    virtual void presentionChanged() = 0;

};
Q_DECLARE_INTERFACE(IHHTextController, "com.hht.qtWhiteBoard.IHHTextController/1.0")
Q_DECLARE_METATYPE(IHHTextController*)
#endif // IHHTEXTCONTROLLER_H
