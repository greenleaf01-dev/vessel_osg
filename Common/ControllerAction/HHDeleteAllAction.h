#ifndef HHDELETEALLACTION_H
#define HHDELETEALLACTION_H

#include <QObject>
#include "HHBaseCustomAction.h"
#include "lib_hhcontrolleraction_global.h"

class IHHCanvas;

class HHCONTROLLERACTIONSHARED_EXPORT HHDeleteAllAction : public HHBaseCustomAction
{
    Q_OBJECT

public:
    HHDeleteAllAction(IHHCanvas *pIHHCanvas,
            QObject *parent = nullptr);

private slots:
    void slotTriggered(bool);

private:

};

#endif // HHDELETEALLACTION_H
