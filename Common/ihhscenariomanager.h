#pragma once

#include <QObject>

class IHHScenario;              //场景接口
class IHHCloudManager;          //云盘管理接口
class IHHConfigManager;         //配置管理接口
class IHHAction;

//场景管理接口
class IHHScenarioManager
{
public:
    ~IHHScenarioManager(){}

    virtual QObject *getObject() = 0;
    virtual void addActions(IHHAction *pIHHAction) = 0;

    virtual void startScenario(QJsonObject param) = 0;                      //启动场景
    virtual void communicateWithScenario(QJsonObject param) = 0;            //场景通信
    virtual void switchScenario(QJsonObject param) = 0;                     //切换场景

    virtual void setCloudManager(IHHCloudManager *pIHHCloudManage) = 0;     //设置云盘管理接口
    virtual void setConfigManager(IHHConfigManager *pIHHConfigManage) = 0;  //设置配置管理接口
};

Q_DECLARE_INTERFACE(IHHScenarioManager, "com.hht.qtWhiteBoard.IHHScenarioManager/1.0")
Q_DECLARE_METATYPE(IHHScenarioManager* )

