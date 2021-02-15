#pragma once

#include <QObject>
#include <QWidget>

class IHHSlideDataOperate
{
public:
    virtual ~IHHSlideDataOperate(){}
    virtual QObject *getObject() = 0;

};
Q_DECLARE_INTERFACE(IHHSlideDataOperate, "com.hht.qtWhiteBoard.IHHSlideDataOperate/1.0")
Q_DECLARE_METATYPE(IHHSlideDataOperate*)
