#ifndef HHMEDIACONTROLLERACTIONSFACTORY_H
#define HHMEDIACONTROLLERACTIONSFACTORY_H

#include "hhscenariocontrolactions_global.h"
#include <QObject>

class IHHAction;
class IHHScenario;
class IHHPopupWindowController;
class IHHMediaPreProcessController;
class IHHMediaTeachingProcessController;
class IHHSwitchModuleController;
class IHHMediaHelper;
class IHHFileOperate;
class IHHPlugin;
class IHHCanvas;
class IHHPresentationData;
class IHHControllerManager;

class HHSCENARIOCONTROLACTIONSSHARED_EXPORT HHMediaControllerActionsFactory
{
public:
    // controller.
    static IHHMediaPreProcessController* getPreController(IHHControllerManager *ctrlManager, IHHPresentationData * preData, IHHCanvas *pIHHCanvas);
    static IHHMediaTeachingProcessController *getTeachingController(IHHControllerManager *ctrlManager, IHHCanvas *pIHHCanvas);

    // helper.
    static IHHMediaHelper *getMediaHelper(IHHScenario *&curScenario,IHHFileOperate *fileOpt, IHHPlugin *plugin, IHHSwitchModuleController *moduleCtrl, QObject *parent = nullptr);

    // action.
    static IHHAction* getShowMediaWidgetAction(IHHPopupWindowController *popupCtrl, QObject *parent = nullptr);

    static IHHAction* getInsertMediaAction(QString sID, IHHScenario *&curScenario, IHHFileOperate *fileOpt, IHHMediaHelper *helper, QObject *parent = nullptr);
    static IHHAction* getExportMediaAction(QString sID, IHHScenario *&curScenario, IHHFileOperate *fileOpt, QObject *parent = nullptr);
    static IHHAction* getReplaceMediaAction(QString sID, IHHScenario *&curScenario, IHHFileOperate *fileOpt, QObject *parent = nullptr);
};

#endif // HHMEDIACONTROLLERACTIONSFACTORY_H
