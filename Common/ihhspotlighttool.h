#pragma once

#include <QObject>

class QString;
class QVariant;

class IHHSpotLightTool
{
public:
    ~IHHSpotLightTool() {}

    virtual QObject *getObject() = 0;

    virtual void setParameters(QString  type ,QVariant  val) = 0;
    virtual QVariant getParameters(QString  type) = 0;

};

Q_DECLARE_INTERFACE(IHHSpotLightTool, "com.hht.qtWhiteBoard.IHHSpotLightTool/1.0")
Q_DECLARE_METATYPE(IHHSpotLightTool*)
