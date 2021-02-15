
#pragma once
#include <QObject>
#include <QJsonObject>

class IHHClassActivityPrepareController;

class IHHActivityUI
{
public:
    virtual QObject* getObject() = 0;
    virtual void init() = 0;
    virtual void setUserData(QJsonObject data) = 0;
    virtual void setActivityController(IHHClassActivityPrepareController *pIHHCtl) = 0;
};

Q_DECLARE_INTERFACE( IHHActivityUI, "com.hht.qtWhiteBoard.IHHActivityUI/1.0" )

Q_DECLARE_METATYPE( IHHActivityUI* )
