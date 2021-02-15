#ifndef HHSUBJECTSCONTROLLERACTIONSFACTORY_H
#define HHSUBJECTSCONTROLLERACTIONSFACTORY_H
#include "hhscenariocontrolactions_global.h"
#include <QObject>

class IHHAction;
class IHHScenario;
class IHHFramePluginsController;

class HHSCENARIOCONTROLACTIONSSHARED_EXPORT HHSubjectsControllerActionsFactory
{
public:
    static IHHAction *getSubjectsAction(IHHScenario *&pCurScenario,IHHFramePluginsController *pluginsCtrl, QObject *parent = nullptr);
};

#endif // HHSUBJECTSCONTROLLERACTIONSFACTORY_H
