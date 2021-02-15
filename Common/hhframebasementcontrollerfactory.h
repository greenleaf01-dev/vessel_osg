#ifndef HHFRAMEBASEMENTCONTROLLERFACTORY_H
#define HHFRAMEBASEMENTCONTROLLERFACTORY_H

#include "lib_framebasementcontroller_global.h"
#include <QObject>

class IHHCanvas;
class IHHPresentation;
class IHHFramePluginsController;
class IHHFrameUserActionsController;
class IHHUserActionManager;
class IHHFrameDevicesController;
class ICallApplicationSDK;
class IHHSwitchModuleController;

class FRAMEBASEMENTCONTROLLERSHARED_EXPORT HHFrameBasementControllerFactory : public QObject
{
    Q_OBJECT
private:
    static IHHFramePluginsController    *m_pPluginsController;

public:
    static IHHFramePluginsController* getFramePluginsController(QObject *pObj = nullptr);

    static IHHFrameUserActionsController *getFrameUserActionController(IHHUserActionManager *pIHHUserActManger,
                                                                      QObject *pObj = nullptr);
    static IHHFrameDevicesController *getFrameDeviceController(QObject *pObj = nullptr);

    static IHHSwitchModuleController *getFrameSwitchModuleController(QObject *pObj = nullptr);
};

#endif //HHFRAMEBASEMENTCONTROLLERFACTORY_H
