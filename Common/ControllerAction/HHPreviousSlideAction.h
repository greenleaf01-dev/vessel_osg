#ifndef HHPREVIOUSSLIDEACTION_H
#define HHPREVIOUSSLIDEACTION_H

#include "HHBaseCustomAction.h"

class HHCONTROLLERACTIONSHARED_EXPORT HHPreviousSlideAction : public HHBaseCustomAction
{
    Q_OBJECT
public:
    explicit HHPreviousSlideAction(IHHScenario *&scenario,QObject *parent = nullptr);
    explicit HHPreviousSlideAction(QObject *parent = nullptr);

signals:
    void signalSlideChanged();

private slots:
    void slotTriggered(bool);
};

#endif // HHPREVIOUSSLIDEACTION_H
