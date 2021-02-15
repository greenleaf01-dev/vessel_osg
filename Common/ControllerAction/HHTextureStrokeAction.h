#ifndef HHTEXTURESTROKEACTION_H
#define HHTEXTURESTROKEACTION_H

#include "HHBaseCustomAction.h"
#include "lib_hhcontrolleraction_global.h"

class IHHSwitchModuleController;
class IHHModule;

class HHCONTROLLERACTIONSHARED_EXPORT HHTextureStrokeAction : public HHBaseCustomAction
{
    Q_OBJECT
    Q_PROPERTY(int Width READ width WRITE setWidth)
    Q_PROPERTY(QString Resource READ resource WRITE setResource)

public:
    HHTextureStrokeAction(IHHSwitchModuleController *pController,
                        QObject *parent = nullptr);

    int width();
    void setWidth(int nWidth);

    QString resource();
    void setResource(const QString &resource);

    virtual void setPropertyInfo(const QJsonObject &info);
    virtual QJsonObject propertyInfo();

    virtual void triggerAction(const QJsonObject &info);

signals:
    void signalStrokeChangWidth(int nWidth);
    void signalStrokeChangResource(const QString &resource);
    void signalStrokePropertyChange(QJsonObject);

public slots:
    void slotChangePropertyInfo(const QJsonObject &info);

private slots:
    void slotTriggered(bool);

private:
    void initSystemScale();
    void loadDefaultInfo();
    void updateModuleData();

private:
    IHHSwitchModuleController            *m_pIHHController;
    IHHModule                            *m_pIHHModule;

    int                                  m_nWidth;
    QString                              m_sResource;
    QString                              m_strIconPath;
    int                                  m_nDrawLineShape;
};

#endif // HHTEXTURESTROKEACTION_H
