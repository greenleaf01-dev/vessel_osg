#ifndef HHCOVERLAYERCONTROLLERACTIONSFACTORY_H
#define HHCOVERLAYERCONTROLLERACTIONSFACTORY_H

#include <QObject>
#include "hhscenariocontrolactions_global.h"

class IHHAction;
class IHHScenario;
class IHHCanvas;
class IHHCoverLayerProcessController;

class HHSCENARIOCONTROLACTIONSSHARED_EXPORT HHCoverLayerControllerActionsFactory
{
public:
    // controller.
    static IHHCoverLayerProcessController* getController(bool isTeachModel, IHHCanvas *pIHHCanvas);

    // action.
    static IHHAction* getAddCoverLayerAction(IHHScenario *&curScenario, QObject *parent = nullptr);
    static IHHAction* getDelCoverLayerAction(IHHScenario *&curScenario, QObject *parent = nullptr);
};

#endif // HHCOVERLAYERCONTROLLERACTIONSFACTORY_H
