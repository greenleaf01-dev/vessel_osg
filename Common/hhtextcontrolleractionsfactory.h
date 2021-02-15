#ifndef HHTEXTCONTROLLERACTIONSFACTORY_H
#define HHTEXTCONTROLLERACTIONSFACTORY_H
#include "hhscenariocontrolactions_global.h"
#include <QObject>

class IHHAction;
class IHHScenario;
class IHHPopupWindowController;
class IHHTextPreProcessController;
class IHHTextTeachingProcessController;
class IHHTextController;
class IHHSwitchModuleController;
class IHHTextHelper;
class IHHFileOperate;
class IHHPlugin;
class IHHCanvas;
class IHHFramePluginsController;

class HHSCENARIOCONTROLACTIONSSHARED_EXPORT HHTextControllerActionsFactory
{
public:
    // controller.
    static IHHTextController *getPreController(IHHCanvas *pIHHCanvas);
    static IHHTextController *getTeachingController();

    // helper.
    static IHHTextHelper *getTextHelper(IHHScenario *&curScenario, IHHFramePluginsController *plugin, QObject *parent);

    // action.
    static IHHAction *getTextAction(IHHScenario *&curScenario,IHHSwitchModuleController *pController,
                                     IHHPlugin *plugin ,QObject *parent);
};
#endif // HHTEXTCONTROLLERACTIONSFACTORY_H
