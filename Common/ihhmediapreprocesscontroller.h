#ifndef IHHMEDIAPREPROCESSCONTROLLER_H
#define IHHMEDIAPREPROCESSCONTROLLER_H

#include <QObject>

class IHHMediaHelper;
class IHHMediaPreProcessController
{
public:
    virtual QObject* getObject() = 0;
    virtual void checkIn() = 0;
    virtual void checkOut() = 0;
    virtual void presentionChanged() = 0;
	virtual void setMediaHelper(IHHMediaHelper*) = 0;

};
Q_DECLARE_INTERFACE(IHHMediaPreProcessController, "com.hht.qtWhiteBoard.IHHMediaPreProcessController/1.0")
Q_DECLARE_METATYPE(IHHMediaPreProcessController*)

#endif // IHHMEDIAPREPROCESSCONTROLLER_H
