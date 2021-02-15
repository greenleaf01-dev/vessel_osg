#ifndef HHACTIONMANAGER_H
#define HHACTIONMANAGER_H

#include "ihhactionsmanager.h"
#include "lib_hhcontrolleraction_global.h"
#include <QList>

class QAction;
class IHHFrameUserActionsController;
class QString;
class IHHAction;

class HHCONTROLLERACTIONSHARED_EXPORT HHActionManager : public QObject, public IHHActionsManager
{
    Q_OBJECT
    Q_INTERFACES(IHHActionsManager)

public:
    HHActionManager(IHHFrameUserActionsController *pIHHActionController,
                    QObject *pObj = nullptr);
    ~HHActionManager();

    virtual IHHAction* getAction( QString strID);// 得到Action
    virtual void addAction( IHHAction *pIAction );// 增加Action

private:
    QMap<QString, IHHAction*>        m_id2ActionMap;
    IHHFrameUserActionsController    *m_pIHHUserAction;
};

#endif // HHACTIONMANAGER_H
