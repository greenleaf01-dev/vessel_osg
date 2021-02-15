#ifndef IHHPLUGINS_H
#define IHHPLUGINS_H
#include <QObject>

class IHHApplication;
class IHHPrimitiveItem;
class IHHModule;
class IHHPlugin;
class IHHPlugins {
public:
    virtual ~IHHPlugins(){}
    virtual void initialization( IHHApplication *app ) = 0;
    virtual void getItem( QString itemID, QJsonObject reason, IHHPrimitiveItem*& item ) = 0;
    virtual IHHModule* getModule( QString moduleID ) = 0;
    virtual QString getModuleIDFromItemID( QString itemID ) = 0;
    virtual QVariantList getQActionListFromPluginID( QString pluginID ) = 0;
    virtual QVariant processCommand( QString strID, QVariantMap param ) = 0;
    virtual void addPlugin( IHHPlugin *plugin ) = 0;// 增加Plugin
    virtual void loadPlugins() = 0;// 加载Plugin
};

Q_DECLARE_INTERFACE( IHHPlugins, "com.hht.qtWhiteBoard.IHHPlugins/1.0" )
Q_DECLARE_METATYPE( IHHPlugins* )

#endif // IHHPLUGINS_H
