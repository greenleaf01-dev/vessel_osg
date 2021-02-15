#ifndef HHMINDMAPCONTROLLERACTIONSFACTORY_H
#define HHMINDMAPCONTROLLERACTIONSFACTORY_H

#include "hhscenariocontrolactions_global.h"
#include <QObject>
#include <QMenu>
class IHHAction;
class IHHScenario;
class IHHPlugin;
class IHHCanvas;
class IHHFramePluginsController;
class IHHMindMapHelper;
class IHHPopupWindowController;
class IHHFileOperate;
class IHHSwitchModuleController;

class HHSCENARIOCONTROLACTIONSSHARED_EXPORT HHMindMapControllerActionsFactory
{
public:
    // action.
    static IHHAction* getCreateMindMapAction(IHHFramePluginsController *PluginsCtrl, IHHSwitchModuleController* ctrl,QObject *parent = nullptr);
    static IHHAction* getMindMapPropertyAction(IHHScenario *&curScenario, QObject *parent = nullptr);
    static IHHAction *getMindmapWidgetAction(IHHPopupWindowController *popupCtrl, QObject *parent);
    static IHHAction* getMindMapAddStampAction(QMenu *subMenu, QObject *parent);
    static IHHAction* getMindMapAddSmileAction(IHHScenario *&curScenario, QObject *parent = nullptr);
    static IHHAction* getMindMapAddFlagAction(IHHScenario *&curScenario, QObject *parent = nullptr);
    static IHHAction* getMindMapAddStarAction(IHHScenario *&curScenario, QObject *parent = nullptr);
    static IHHAction* getMindMapDeleteStampAction(IHHScenario *&curScenario, QObject *parent = nullptr);
    static IHHAction* getMindMapAddShadeAction(IHHScenario *&curScenario, QObject *parent = nullptr);
    static IHHAction* getMindMapDeleteShadeAction(IHHScenario *&curScenario, QObject *parent = nullptr);
    static IHHAction* getMindMapAddEnclosureAction(QMenu *subMenu, QObject *parent = nullptr);
    static IHHAction* getMindMapAddAudioAction(IHHFileOperate *fileoper, IHHScenario *&curScenario, QObject *parent = nullptr);
    static IHHAction* getMindMapAddVideoAction(IHHFileOperate* fileoper,IHHScenario *&curScenario, QObject *parent = nullptr);
    static IHHAction* getMindMapAddImageAction(IHHFileOperate* fileoper,IHHScenario *&curScenario, QObject *parent = nullptr);
    static IHHAction* getMindMapAddDocAction(IHHFileOperate* fileoper,IHHScenario *&curScenario, QObject *parent = nullptr);
    static IHHAction* getMindMapExportAction(IHHFileOperate *fileoper,IHHScenario *&curScenario, QObject *parent = nullptr);

    // helper
    static IHHMindMapHelper *getMindMapHelper(IHHScenario *&curScenario, QObject *parent = nullptr);
};

#endif // HHMEDIACONTROLLERACTIONSFACTORY_H
