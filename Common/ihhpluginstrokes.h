#ifndef IHHPLUGINSTROKES_H
#define IHHPLUGINSTROKES_H

#include <QString>
#include <QJsonObject>
#include <QObject>

class IHHFrameGeneralToolController;
class IHHFrameCanvasController;
class IHHModule;
class IHHActionsManager;

class IHHPluginStrokes {
public:
    virtual ~IHHPluginStrokes(){}
    virtual IHHModule* getGestureRecognitionModule( IHHFrameGeneralToolController *pToolController,
                                                   IHHFrameCanvasController *pCanvasController ) = 0;
    virtual IHHModule* getModuleFromItemID( QString itemID ) = 0;
    virtual IHHModule* getGestureRecognitionModule( IHHActionsManager *pIHHActionsMgr ) = 0;
};
Q_DECLARE_INTERFACE( IHHPluginStrokes, "com.hht.qtWhiteBoard.IHHPluginStrokes/1.0" )
Q_DECLARE_METATYPE( IHHPluginStrokes* )

#endif
