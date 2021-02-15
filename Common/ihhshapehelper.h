#ifndef IHHSHAPEHELPER_H
#define IHHSHAPEHELPER_H
#include <QObject>

class IHHPrimitiveItem;
class IHHShapeHelper
{
public:
    virtual QObject* getObject() = 0;
};
Q_DECLARE_INTERFACE(IHHShapeHelper, "com.hht.qtWhiteBoard.IHHShapeHelper/1.0")
Q_DECLARE_METATYPE(IHHShapeHelper*)

#endif // IHHSHAPEHELPER_H
