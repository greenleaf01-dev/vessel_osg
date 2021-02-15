#ifndef HHNEXTSLIDEACTION_H
#define HHNEXTSLIDEACTION_H

#include "HHBaseCustomAction.h"

class HHCONTROLLERACTIONSHARED_EXPORT HHNextSlideAction : public HHBaseCustomAction
{
    Q_OBJECT
public:
    explicit HHNextSlideAction(IHHScenario *&pIHHScenario, QObject *parent = nullptr);
    explicit HHNextSlideAction(QObject *parent = nullptr);

signals:
    void signalSlideChanged();

private slots:
    void slotTriggered(bool);
};

#endif // HHNEXTSLIDEACTION_H
