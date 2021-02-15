#pragma once

#include <QObject>
#include "hhtouchpoint.h"

class IHHModule;

class IHHDispatcher {
public:
    virtual ~IHHDispatcher(){}
    virtual void switchModule( IHHModule* pModule ) = 0;
    virtual QVector< IHHModule* > getBrotherModules( IHHModule *pModule ) = 0;
    virtual void onHHTDeviceEvent( QString type, HHTouchPoint point, SpecifiedPenType penType ) = 0;
    virtual void setParameters( QString type, QVariant value ) = 0;
    virtual QVariant getParameters( QString type ) = 0;
    virtual IHHModule* getCurrentModule() = 0;
    virtual void setSupportPenNumber(int nNum) = 0;
    virtual int getSupportPenNumber() = 0;
};

Q_DECLARE_INTERFACE( IHHDispatcher, "com.hht.qtWhiteBoard.IHHDispatcher/1.0" )
Q_DECLARE_METATYPE( IHHDispatcher* )
