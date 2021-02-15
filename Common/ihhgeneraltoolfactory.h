#pragma once

#include <QObject>

class IHHPrimitiveItem;
class IHHApplication;

class IHHGeneralToolFactory {
public:
    virtual ~IHHGeneralToolFactory(){}
    virtual int initialization( IHHApplication *app ) = 0;
    virtual QObject* getObject() = 0;
    virtual void getItem( QString itemID, QJsonObject reason, IHHPrimitiveItem*& item ) = 0;
    virtual QVariantList getQActionListFromPluginID( QString pluginID ) = 0;
    virtual QVariant processCommand( QString strID, QVariantMap param ) = 0;
};

Q_DECLARE_INTERFACE( IHHGeneralToolFactory, "com.hht.qtWhiteBoard.IHHGeneralToolFactory/1.0" )
Q_DECLARE_METATYPE( IHHGeneralToolFactory* )
