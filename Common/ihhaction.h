#pragma once

#include <QObject>
#include <QAction>

class IHHTestAutoUI;
class IHHScenario;
class QAction;
class IHHCanvas;

class IHHAction{
public:
    ~IHHAction() {}

    virtual QObject *getObject() = 0;
    virtual QAction *getAction() = 0;

    virtual void setID(const QString &sID) = 0;
    virtual void setCanvas(IHHCanvas *pIHHCanvas) = 0;

    virtual void setPropertyInfo(const QJsonObject &info) = 0;
    virtual QJsonObject propertyInfo() = 0;

    virtual void triggerAction() = 0;
    virtual void triggerAction(const QJsonObject &info) = 0;

    virtual void bindingUI(IHHTestAutoUI *pTestUI) = 0;
    virtual void unBindingUI(IHHTestAutoUI *pTestUI) = 0;

    virtual bool isSucceed(QJsonObject &info) = 0;

    virtual void notifyErrorInfo(const QJsonObject &info) = 0;
    virtual void notifySucceeInfo(const QJsonObject &info) = 0;

    virtual void setScenario(IHHScenario *&pIHHScenario) = 0;

    virtual void bingingStatisticsAction(IHHAction *pIHHAction) = 0;
};

Q_DECLARE_INTERFACE( IHHAction, "com.hht.qtWhiteBoard.IHHAction/1.0" )
Q_DECLARE_METATYPE( IHHAction* )
