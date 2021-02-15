//手势笔
#ifndef HHGESTURESTROKEACTION_H
#define HHGESTURESTROKEACTION_H

#include "HHBaseCustomAction.h"
#include "lib_hhcontrolleraction_global.h"

class IHHSwitchModuleController;
class IHHModule;

class HHCONTROLLERACTIONSHARED_EXPORT HHGestureStrokeAction : public HHBaseCustomAction
{
    Q_OBJECT
public:
    explicit HHGestureStrokeAction(
            IHHSwitchModuleController *pIHHController,
            QObject *parent = nullptr);

    virtual void setPropertyInfo(const QJsonObject &info);
    virtual QJsonObject propertyInfo();

    virtual void triggerAction(const QJsonObject &info);

private slots:
    void slotTriggered(bool);

private:
    IHHSwitchModuleController        *m_pIHHController;
    IHHModule                        *m_pIHHModule;
};

#endif // HHGESTURESTROKEACTION_H
