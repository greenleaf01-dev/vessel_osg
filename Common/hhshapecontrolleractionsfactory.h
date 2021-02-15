#ifndef HHSHAPECONTROLLERACTIONSFACTORY_H
#define HHSHAPECONTROLLERACTIONSFACTORY_H
#include "hhscenariocontrolactions_global.h"
#include <QObject>

class IHHAction;
class IHHScenario;
class IHHPopupWindowController;
class IHHShapePreProcessController;
class IHHShapeTeachingProcessController;
class IHHShapeController;
class IHHSwitchModuleController;
class IHHShapeHelper;
class IHHFileOperate;
class IHHPlugin;
class IHHCanvas;

class HHSCENARIOCONTROLACTIONSSHARED_EXPORT HHShapeControllerActionsFactory
{
public:
    // controller.
    static IHHShapeController *getPreController(IHHCanvas *pIHHCanvas);
    static IHHShapeController *getTeachingController(IHHCanvas *pIHHCanvas);

    // helper.
    static IHHShapeHelper *getShapeHelper(IHHScenario *&curScenario, IHHPlugin *plugin, QObject *parent);

    // action.
    static IHHAction *getShapeWidgetAction(IHHPopupWindowController *popupCtrl, QObject *parent);
    static IHHAction *getShapeAction(IHHScenario *&curScenario,IHHSwitchModuleController *pController,
                                     IHHPlugin *plugin ,QObject *parent);

    static IHHAction* getFreeItemLinearChangeAction(IHHScenario *&curScenario, QObject *parent = nullptr);
    static IHHAction* getFreeItemDelChangeAction(IHHScenario *&curScenario, QObject *parent = nullptr);
    static IHHAction* getFreeItemCurveChangeAction(IHHScenario *&curScenario, QObject *parent = nullptr);
};

#endif // HHSHAPECONTROLLERACTIONSFACTORY_H
