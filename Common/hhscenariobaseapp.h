#ifndef HHSCENARIOBASEAPP_H
#define HHSCENARIOBASEAPP_H

#include "lib_global.h"
#include <QJsonObject>

class IHHScenarioApplication;
class IHHScenarioManager;

class LIB_EXPORT HHScenarioBaseApp
{
public:
    HHScenarioBaseApp();
    virtual ~HHScenarioBaseApp();
    virtual void initialization(IHHScenarioManager *scenarioManager);// IHHFrame *frame
    IHHScenarioApplication* getApplication();//
    void setRunOnScreen(bool runOnScreen);
protected:
    IHHScenarioApplication              *m_pApp;//

public:
    QJsonObject                 m_params;
    QJsonObject     processArguments(QStringList param );
    QJsonObject     processArguments(QString param,bool isSendMessage);
    QString processParam(QStringList paramList);
    QVariantMap getHotKeyInfo( QString hotkey );
    bool m_runOnScreen;
};

#endif // HHSCENARIOBASEAPP_H
