#ifndef IHHFRAMEPLUGINSCONTROLLER_H
#define IHHFRAMEPLUGINSCONTROLLER_H

#include <QString>
#include <QJsonObject>
#include <QObject>
#include <QVariant>
#include "ihhplugin.h"

class IHHModule;
class IHHPrimitiveItem;
class IHHFramePluginsController {
public:
    virtual ~IHHFramePluginsController(){}
    virtual QObject *getObject() = 0;
    virtual IHHPlugin* getPlugin( QString strID ) = 0;
    virtual void getItem( QString itemID, QJsonObject reason, IHHPrimitiveItem*& item ) = 0;
    virtual IHHModule* getModule( QString moduleID ) = 0;
    virtual QString getModuleIDFromItemID( QString itemID ) = 0;
    virtual void addPlugin( IHHPlugin *plugin ) = 0;
    virtual void loadPlugins() = 0;

    // add by fanhongjie start
    virtual void loadPlugins(const QStringList &lPluginPath) = 0;
    virtual void loadPlugin(const QString &sPluginPath) = 0;
    // add by fanhonghie end

    virtual QVariantList getQActionListFromPluginID( QString pluginID ) = 0;
};

Q_DECLARE_INTERFACE( IHHFramePluginsController, "com.hht.qtWhiteBoard.IHHFramePluginsController/1.0" )
Q_DECLARE_METATYPE( IHHFramePluginsController* )

#endif
