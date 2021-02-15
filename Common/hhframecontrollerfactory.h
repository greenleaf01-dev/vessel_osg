#ifndef HHFRAMECONTROLLERFACTORY_H
#define HHFRAMECONTROLLERFACTORY_H

#include "lib_framecontroller_global.h"
#include <QObject>

class IHHCanvas;
class IHHPresentation;
class IHHFrameStrokeController;
class IHHFrameGeneralToolController;
class IHHFrameCanvasController;
class IHHFrameDeletePixelController;
class IHHFramePluginsController;
class IHHActionManager;
class IHHFrameUserActionController;
class IHHUserActionManager;
class IHHFrameDeviceController;
class ICallApplicationSDK;

class FRAMECONTROLLERSHARED_EXPORT HHFrameControllerFactory : public QObject
{
    Q_OBJECT
private:
    static IHHFramePluginsController    *m_pPluginsController;

public:
    static IHHFrameStrokeController* getFrameControllerStroke(
            IHHCanvas *pIHHCanvas, IHHFrameGeneralToolController *pIHHToolController,
            IHHFrameCanvasController *pIHHCanvasController, IHHFramePluginsController *pIHHPluginsController, QObject *pObj = nullptr);

    static IHHFrameDeletePixelController* getFrameControllerDeletePixel(
            IHHCanvas *pIHHCanvas, IHHFramePluginsController *pIHHPluginsController,
            QObject *pObj = nullptr);

    static IHHFrameCanvasController* getFrameControllerCanvas(
            IHHCanvas *pIHHCanvas, IHHFramePluginsController *pIHHPluginsController,
            QObject *pObj = nullptr);

    static IHHFramePluginsController* getFramePluginsController(QObject *pObj = nullptr);

    static IHHActionManager *getActionManger(IHHFrameUserActionController *pIHHFrameUserActController,
                                             QObject *pObj = nullptr);
    static IHHFrameUserActionController *getFrameUserActionController(IHHUserActionManager *pIHHUserActManger,
                                                                      QObject *pObj = nullptr);
    static IHHFrameDeviceController *getFrameDeviceController(QObject *pObj = nullptr);
};

#endif //HHFRAMECONTROLLERFACTORY_H
