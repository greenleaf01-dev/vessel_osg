#ifndef HHUNDOACTION_H
#define HHUNDOACTION_H

#include <QObject>
#include "HHBaseCustomAction.h"
#include "lib_hhcontrolleraction_global.h"

class IHHCanvas;

class HHCONTROLLERACTIONSHARED_EXPORT HHUndoAction : public HHBaseCustomAction
{
    Q_OBJECT

public:
    explicit HHUndoAction(IHHCanvas *pIHHCanvas, QObject *parent = nullptr);

signals:

public slots:

private slots:
    void slotTriggered(bool);

private:
};

#endif // HHUNDOACTION_H
