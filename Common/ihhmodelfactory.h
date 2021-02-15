#pragma once
#include "ihhmodel.h"
#include "hhglobaldefine.h"
#include <QObject>

class IHHApplication;
class IHHModelFactory {
public:
	virtual ~IHHModelFactory() {}
        virtual IHHModel* getModel(HHGlobalDefine::PresentationType modeType) = 0;
	virtual int initialization(IHHApplication *app) = 0;
	virtual QObject* getObject() = 0;
};
Q_DECLARE_INTERFACE( IHHModelFactory, "com.hht.qtWhiteBoard.IHHModelFactory/1.0" )
Q_DECLARE_METATYPE( IHHModelFactory* )
