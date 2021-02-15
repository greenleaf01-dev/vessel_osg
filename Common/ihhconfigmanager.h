#ifndef IHHCONFIGMANAGER_H
#define IHHCONFIGMANAGER_H

#include <QObject>

class IHHConfigManager {
public:
    ~IHHConfigManager(){}
    virtual void finish() = 0;
    virtual void reset() = 0;
        virtual QObject *getObject() = 0;
    virtual QVariant getParameters(QString settingType) = 0;
    virtual void setParameters(QString type, QVariant value) = 0;
    virtual void setParameters(QString type, QVariantMap parameters) = 0;
    virtual void setParameters(QString type, QList<QVariantMap> &parameters) = 0;
};

Q_DECLARE_INTERFACE( IHHConfigManager, "com.hht.qtWhiteBoard.IHHConfigManager/1.0" )
Q_DECLARE_METATYPE( IHHConfigManager* )

#endif // IHHCOMMAND_H
