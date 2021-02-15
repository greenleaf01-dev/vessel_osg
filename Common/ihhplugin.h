#ifndef IHHPLUGIN_H
#define IHHPLUGIN_H
#include <QObject>
#include <QMap>
#include <functional>

class IHHApplication;
class IHHPrimitiveItem;
class IHHModule;

typedef std::function< IHHPrimitiveItem* (QJsonObject reason) >   funItemCreator ;
//typedef IHHPrimitiveItem*(*funItemCreator)(QJsonObject reason);

typedef QMap< QString, funItemCreator > HHMapItemCreator;

class IHHPlugin {
public:
    virtual ~IHHPlugin(){}
    virtual void initialization( IHHApplication *app ) = 0;
    virtual void getItem( QString itemID, QJsonObject reason, IHHPrimitiveItem*& item ) = 0;
    virtual IHHModule* getModule( QString moduleID ) = 0;
    virtual QString getModuleIDFromItemID( QString itemID ) = 0;
    virtual QVariantList getQActionListFromPluginID( QString pluginID ) = 0;
    virtual QVariant processCommand( QString strID, QVariantMap param ) = 0;
    virtual QString getID() = 0;
    virtual QObject *getObject() = 0;
    virtual void fillCreatorInfo( HHMapItemCreator &maps ) = 0;
};

Q_DECLARE_INTERFACE( IHHPlugin, "com.hht.qtWhiteBoard.IHHPlugin/1.0" )
Q_DECLARE_METATYPE( IHHPlugin* )

#endif // IHHPLUGIN_H
