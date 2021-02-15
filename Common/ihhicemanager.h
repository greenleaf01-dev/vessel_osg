#ifndef _IHHICEMANAGER_H
#define _IHHICEMANAGER_H

class IHHFrameStrokeController;
class IHHFrameCanvasController;
class IHHConfigManager;
class IHHFrameItemController;
class IHHFrameDeletePixelController;
class IHHFrameMediaController;
class IHHFramePreController;
class IHHFrameTextBoxController;
class IHHFrameGeneralToolController;

// 界面Ice管理控制
class IHHIceManager{
public:
    ~IHHIceManager() {}

    virtual QObject *getObject() = 0;
};

#endif//_IHHICEMANAGER_H
