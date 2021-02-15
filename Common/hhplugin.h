#ifndef HHPLUGIN_H
#define HHPLUGIN_H

#include "lib_global.h"
#include <QDomDocument>
#include "ihhplugin.h"

class IHHApplication;
class LIB_EXPORT HHPlugin : public QObject, public IHHPlugin {
    Q_OBJECT
    Q_INTERFACES( IHHPlugin )

public:
    HHPlugin();
    virtual ~HHPlugin();

public:
    static IHHApplication *m_pApp;

protected:
    QString             m_strSVGName;
    QDomElement         m_pDisciplineXML;
    QString             m_strID;
    HHMapItemCreator    m_vItemPluginCreator;

public:
    virtual void initialization( IHHApplication *app );
    virtual void getItem( QString itemID, QJsonObject reason, IHHPrimitiveItem*& item );
    virtual IHHModule* getModule( QString moduleID );
    virtual QString getModuleIDFromItemID( QString itemID );
    virtual QVariantList getQActionListFromPluginID( QString pluginID );
    virtual QVariant processCommand( QString strID, QVariantMap param );
    virtual QString getID();
    virtual QObject *getObject();
    virtual void fillCreatorInfo( HHMapItemCreator &maps );
};

#endif
