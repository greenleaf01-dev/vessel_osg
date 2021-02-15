#pragma once

#include <QObject>
#include <QJsonObject>

class IHHModule;
class IHHCanvas;
class IHHFramePluginsController;
class IHHActionsManager;

class IHHSwitchModuleController{
public:
    ~IHHSwitchModuleController() {}

    virtual QObject *getObject() = 0;

    virtual int switchModule(const QString &sModule, IHHCanvas *pCanvas,
                             const QJsonObject &info) = 0;
    virtual int switchModule(const QString &sItemID, IHHModule *pIHHModule,
                             IHHCanvas *pCanvas, const QJsonObject &info) = 0;

    virtual IHHModule *getModule(const QString &sModule) = 0;
    virtual IHHModule *getCurrentModule() = 0;

    virtual QString getCurModule() = 0;

    virtual int setModuleData(IHHCanvas *pIHHCavnas, IHHModule *pIHHModule,
                              const QJsonObject &info) = 0;

    virtual void setPluginsController(IHHFramePluginsController *pIHHPluginsCtrl) = 0;

    virtual void setActionsManager(IHHActionsManager *pIHHActionMgr) = 0;
};
Q_DECLARE_INTERFACE( IHHSwitchModuleController, "com.hht.qtWhiteBoard.IHHSwitchModuleController/1.0" )
Q_DECLARE_METATYPE( IHHSwitchModuleController* )
