#ifndef HHROAMINGACTION_H
#define HHROAMINGACTION_H

#include <QObject>
#include "HHBaseCustomAction.h"
#include "lib_hhcontrolleraction_global.h"

class IHHSwitchModuleController;
class IHHModule;

class HHCONTROLLERACTIONSHARED_EXPORT HHRoamingAction : public HHBaseCustomAction
{
    Q_OBJECT

public:
    explicit HHRoamingAction(
            IHHSwitchModuleController *pController,
            QObject *parent = nullptr);

    virtual void setPropertyInfo(const QJsonObject &info);
    virtual QJsonObject propertyInfo();

    virtual void triggerAction(const QJsonObject &info);

public slots:
    void slotChangePropertyInfo(const QJsonObject &info);

private slots:
    void slotTriggered(bool);

private:
    void updateModuleData();

private:
    IHHSwitchModuleController           *m_pIHHController;
    IHHModule                           *m_pIHHModule;

    QString                             m_strRoamingType;
};

#endif // HHROAMINGACTION_H
