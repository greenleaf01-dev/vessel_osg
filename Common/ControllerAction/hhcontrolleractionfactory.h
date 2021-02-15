#ifndef HHCONTROLLERACTIONFACTORY_H
#define HHCONTROLLERACTIONFACTORY_H

#include "lib_hhcontrolleraction_global.h"

class HHBaseCustomAction;

class IHHCanvas;
class IHHFrameStrokeController;
class IHHFrameCanvasController;
class IHHFrameDeletePixelController;
class IHHSwitchModuleController;
class IHHAction;
class IHHScenario;
class IHHCloudManager;
class IHHActionsManager;

#include <QObject>

class HHCONTROLLERACTIONSHARED_EXPORT HHControllerActionFactory
{
public:
    static IHHAction* getSmoothStrokeAction(
            IHHSwitchModuleController *pController,
            QObject *parent = nullptr);

    static IHHAction* getChalkStrokeAction(
            IHHSwitchModuleController *pController,
            QObject *parent = nullptr);

    static IHHAction* getGeometryFreeHandAction(
            IHHSwitchModuleController *pController,
            QObject *parent = nullptr);

    static IHHAction* getFluorescentStrokeAction(
            IHHSwitchModuleController *pController,
            QObject *parent = nullptr);

    static IHHAction* getBrushStrokeAction(
            IHHSwitchModuleController *pController,
            QObject *parent = nullptr);

    static IHHAction* getTextureStrokeAction(
            IHHSwitchModuleController *pController,
            QObject *parent = nullptr);

    static IHHAction* getPaiStrokeAction(
            IHHSwitchModuleController *pController,
            QObject *parent = nullptr);

    static IHHAction* getStampStrokeAction(
            IHHSwitchModuleController *pController,
            QObject *parent = nullptr);

    static IHHAction* getLaserStrokeAction(
            IHHSwitchModuleController *pController,
            QObject *parent = nullptr);

    static IHHAction* getGestureStrokeAction(
            IHHSwitchModuleController *pController,
            QObject *parent = nullptr);

    static IHHAction *getSwitchSelectModuleAction(
            IHHSwitchModuleController *pController,
            QObject *parent = nullptr);

    static IHHAction *getDeleteAllAction(
            IHHCanvas *pIHHCanvas,
            QObject *parent = nullptr);

    static IHHAction *getUndoAction(
            IHHCanvas *pIHHCanvas, QObject *parent = nullptr);

    static IHHAction *getDeletePixelAction(
            IHHSwitchModuleController *pController,
            QObject *parent = nullptr);

    static IHHAction *getRoamingAction(
            IHHSwitchModuleController *pController,
            QObject *parent = nullptr);

    static IHHAction *getRoamingReduceAction(
            IHHSwitchModuleController *pController,
            QObject *parent = nullptr);

    static IHHAction *getNextSlideAction(IHHScenario *&pIHHScenario,
            QObject *parent = nullptr);

    static IHHAction *getNewSlideAction(IHHScenario *&scenario ,QObject *parent);

    static IHHAction *getPreviousSlideAction(IHHScenario *&scenario ,QObject *parent);
};

#endif // HHCONTROLLERACTIONFACTORY_H
