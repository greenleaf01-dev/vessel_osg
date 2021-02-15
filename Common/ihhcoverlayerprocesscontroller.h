#ifndef IHHCOVERLAYERPROCESSCONTROLLER_H
#define IHHCOVERLAYERPROCESSCONTROLLER_H

#include <QObject>

class IHHCoverLayerProcessController
{
public:
    virtual QObject* getObject() = 0;
    virtual void checkIn() = 0;
    virtual void checkOut() = 0;
};
Q_DECLARE_INTERFACE(IHHCoverLayerProcessController, "com.hht.qtWhiteBoard.IHHCoverLayerProcessController/1.0")
Q_DECLARE_METATYPE(IHHCoverLayerProcessController*)

#endif // IHHCOVERLAYERPROCESSCONTROLLER_H
