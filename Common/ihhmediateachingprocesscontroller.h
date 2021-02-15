#ifndef IHHMEDIATEACHINGPROCESSCONTROLLER_H
#define IHHMEDIATEACHINGPROCESSCONTROLLER_H

#include <QObject>

class IHHMediaHelper;
class IHHMediaTeachingProcessController
{
public:
    virtual QObject* getObject() = 0;
    virtual void checkIn() = 0;
    virtual void checkOut() = 0;
    virtual void presentionChanged() = 0;
	virtual void setMediaHelper(IHHMediaHelper*) = 0;

};
Q_DECLARE_INTERFACE(IHHMediaTeachingProcessController, "com.hht.qtWhiteBoard.IHHMediaTeachingProcessController/1.0")
Q_DECLARE_METATYPE(IHHMediaTeachingProcessController*)

#endif // IHHMEDIATEACHINGPROCESSCONTROLLER_H
