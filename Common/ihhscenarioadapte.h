#pragma once

#include <QObject>

class IHHScenario;

//场景管理接口
class IHHScenarioAdapte
{
public:
    ~IHHScenarioAdapte(){}

    virtual QObject *getObject() = 0;

    virtual void initScenario(int iType) = 0;                           //初始化场景
    virtual void showScenario(int iType,  QJsonObject param) = 0;       //显示场景
};

Q_DECLARE_INTERFACE(IHHScenarioAdapte, "com.hht.qtWhiteBoard.IHHScenarioAdapte/1.0")
Q_DECLARE_METATYPE(IHHScenarioAdapte* )

