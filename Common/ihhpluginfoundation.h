#ifndef IHHPLUGINFOUNDATION_H
#define IHHPLUGINFOUNDATION_H

#include <QString>
#include <QJsonObject>
#include <QObject>

class IHHCanvas;
class IHHPresentation;
class IHHModule;
class IHHPluginFoundation {
public:
    virtual ~IHHPluginFoundation(){}
    virtual IHHModule*          getDeletePixelModule() = 0;
    virtual IHHModule*          getDeleteItemModule() = 0;
    virtual IHHModule*          getSelectItemPlaceHolderModule() = 0;
    virtual IHHModule*          getSelectItemWithOneSelectionModule() = 0;
    virtual IHHModule*          getSelectItemWithMultiSelectionsModule() = 0;
    virtual IHHModule*          getRoverModule() = 0;
    virtual IHHCanvas*          getCanvas() = 0;
    virtual IHHPresentation*    getPresentation() = 0;
    virtual IHHCanvas*          getCanvasWithHHTXPresentation() = 0;
};
Q_DECLARE_INTERFACE( IHHPluginFoundation, "com.hht.qtWhiteBoard.IHHPluginFoundation/1.0" )
Q_DECLARE_METATYPE( IHHPluginFoundation* )

#endif
