#ifndef HHSWITCHSELECTMODULEACTION_H
#define HHSWITCHSELECTMODULEACTION_H

#include <QObject>
#include "HHBaseCustomAction.h"
#include "lib_hhcontrolleraction_global.h"

class IHHSwitchModuleController;

class HHCONTROLLERACTIONSHARED_EXPORT HHSwitchSelectModuleAction : public HHBaseCustomAction
{
    Q_OBJECT
    Q_PROPERTY(bool IsHolderModule READ IsHolderModule WRITE setIsHolderModule)

public:
    explicit HHSwitchSelectModuleAction(
            IHHSwitchModuleController *pController,
            QObject *parent = nullptr);

    bool IsHolderModule();
    void setIsHolderModule(bool bIsHolderModule);

signals:

public slots:

private slots:
    void slotTriggered(bool);

private:
    IHHSwitchModuleController        *m_pIHHController;

    bool                            m_bIsHolderModule;
};

#endif // HHSWITCHSELECTMODULEACTION_H
