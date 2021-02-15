#ifndef IHHCONTROLLERMANAGER_H
#define IHHCONTROLLERMANAGER_H

#include <QObject>

class IHHFramePluginsController;
class IHHFrameCanvasController;
class IHHFrameTextBoxController;
class IHHFrameDeletePixelController;
class IHHFrameShapeController;
class IHHFrameStrokeController;
class IHHSwitchModuleController;
class IHHItemAnimationController;
class IHHItemAnimationCanvasManager;
class IHHFileOperate;
class IHHMediaPreProcessController;
class IHHMediaTeachingProcessController;
class IHHClassActivityPrepareController;
class IHHClassActivityTeachingController;
class IHHMediaHelper;
class IHHClassActivityHelper;
class IHHCoverLayerProcessController;

class IHHShapeController;
class IHHShapeHelper;

class IHHTextController;
class IHHTextHelper;

class IHHMindMapHelper;

class IHHSlideDataOperate;
class IHHPopupWindowController;
class IHHTeachingPopWindowController;

class IHHDataController;

class IHHControllerManager{
public:
    ~IHHControllerManager() {}

    virtual void setPrePopWindowCtrl(IHHPopupWindowController* ctrl) = 0;
    virtual IHHPopupWindowController* getPrePopWindowCtrl() = 0;

    virtual void setTeachingPopWindowCtrl(IHHTeachingPopWindowController* ctrl) = 0;
    virtual IHHTeachingPopWindowController* getTeachingPopWindowCtrl() = 0;

    virtual void setPluginsCtrl(IHHFramePluginsController *ctrl) = 0;
    virtual IHHFramePluginsController* getPluginsCtrl() = 0;

    virtual void setCanvasCtrl(IHHFrameCanvasController *ctrl) = 0;
    virtual IHHFrameCanvasController* getCanvasCtrl() = 0;

    virtual void setTextboxCtrl(IHHFrameTextBoxController *ctrl) = 0;
    virtual IHHFrameTextBoxController* getTextboxCtrl() = 0;

    virtual void setDeletePixelCtrl(IHHFrameDeletePixelController *ctrl) = 0;
    virtual IHHFrameDeletePixelController* getDeletePixelCtrl() = 0;


    virtual void setStrokeCtrl(IHHFrameStrokeController *ctrl) = 0;
    virtual IHHFrameStrokeController* getStrokeCtrl() = 0;

    virtual void setSwitchModuleCtrl(IHHSwitchModuleController *ctrl) = 0;
    virtual IHHSwitchModuleController* getSwitchModuleCtrl() = 0;

    virtual void setItemAnimationCtrl(IHHItemAnimationController *ctrl) = 0;
    virtual IHHItemAnimationController* getItemAnimationCtrl() = 0;

    virtual void setItemAnimationCanvasManager(IHHItemAnimationCanvasManager *ctrl) = 0;
    virtual IHHItemAnimationCanvasManager* getItemAnimationCanvasManager() = 0;

    virtual void setFileOperate(IHHFileOperate *pFileOperate) = 0;
    virtual IHHFileOperate* getFileOperate() = 0;

    virtual void setMediaPreCtrl(IHHMediaPreProcessController *ctrl) = 0;
    virtual IHHMediaPreProcessController* getMediaPreCtrl() = 0;

    virtual void setMediaTeachCtrl(IHHMediaTeachingProcessController *ctrl) = 0;
    virtual IHHMediaTeachingProcessController* getMediaTeachCtrl() = 0;

    virtual void setActivityPreCtrl(IHHClassActivityPrepareController *pIHHCtrl) = 0;
    virtual IHHClassActivityPrepareController *getActivityPreCtrl() = 0;

    virtual void setActivityTeachingCtrl(IHHClassActivityTeachingController *pIHHCtrl) = 0;
    virtual IHHClassActivityTeachingController *getAcvitityTeachingCtrl() = 0;

    virtual void setMediaHelper(IHHMediaHelper *pIHHCtrl) = 0;
    virtual IHHMediaHelper *getMediaHelper() = 0;

    virtual void setActivityHelper(IHHClassActivityHelper *pIHHActivityHelper) = 0;
    virtual IHHClassActivityHelper *getActivityHelper() = 0;

    virtual void setCoverLayerPreCtrl(IHHCoverLayerProcessController *pIHHCoverLayerProcessController) = 0;
    virtual IHHCoverLayerProcessController *getCoverLayerPreCtrl() = 0;

    virtual void setCoverLayerTeachCtrl(IHHCoverLayerProcessController *pIHHCoverLayerProcessController) = 0;
    virtual IHHCoverLayerProcessController *getCoverLayerTeachCtrl() = 0;

    virtual void setShapePreCtrl(IHHShapeController *ctrl) = 0;
    virtual IHHShapeController * getShapePreCtrl() = 0;
    virtual void setShapeTeachingCtrl(IHHShapeController *ctrl) = 0;
    virtual IHHShapeController *getShapeTeachingController() = 0;
    virtual void setShapeHelper(IHHShapeHelper *helper) = 0;
    virtual IHHShapeHelper* getShapeHelper() = 0;

    virtual void setTextPreCtrl(IHHTextController *ctrl) = 0;
    virtual IHHTextController * getTextPreCtrl() = 0;
    virtual void setTextTeachingCtrl(IHHTextController *ctrl) = 0;
    virtual IHHTextController *getTextTeachingController() = 0;
    virtual void setTextHelper(IHHTextHelper *helper) = 0;
    virtual IHHTextHelper* getTextHelper() = 0;

    virtual void setMindMapHelper(IHHMindMapHelper *helper) = 0;
    virtual IHHMindMapHelper * getMindMapHelper() = 0;

    virtual void setSlideDataOperate(IHHSlideDataOperate* operate) = 0;
    virtual IHHSlideDataOperate* getSlideDataOperate() = 0;

    virtual void setDataController(IHHDataController* ctrl) = 0;
    virtual IHHDataController* getDataController() = 0;

};
Q_DECLARE_INTERFACE( IHHControllerManager, "com.hht.qtWhiteBoard.IHHControllerManager/1.0" )
Q_DECLARE_METATYPE( IHHControllerManager* )

#endif // IHHCONTROLLERMANAGER_H
