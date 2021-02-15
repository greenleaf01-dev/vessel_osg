#pragma once

#include <QObject>

class QString;
class QVariant;

class IHHMagnifiertTool
{
public:
    ~IHHMagnifiertTool() {}

    virtual QObject *getObject() = 0;

    virtual void setParameters(QString  type ,QVariant  val) = 0;
    virtual QVariant getParameters(QString  type) = 0;

};

Q_DECLARE_INTERFACE(IHHMagnifiertTool, "com.hht.qtWhiteBoard.IHHMagnifiertTool/1.0")
Q_DECLARE_METATYPE(IHHMagnifiertTool*)
