#ifndef HHSLIDENEWPAGEACTION_H
#define HHSLIDENEWPAGEACTION_H

#include "HHBaseCustomAction.h"

class IHHScenario;

class HHCONTROLLERACTIONSHARED_EXPORT HHNewSlideAction : public HHBaseCustomAction
{
    Q_OBJECT
public:
    explicit HHNewSlideAction(IHHScenario *&scenario,QObject *parent = nullptr);
    explicit HHNewSlideAction(QObject *parent = nullptr);

signals:
    void signalSlideChanged();

private slots:
    void slotTriggered(bool);
};

#endif // HHSLIDENEWPAGEACTION_H
