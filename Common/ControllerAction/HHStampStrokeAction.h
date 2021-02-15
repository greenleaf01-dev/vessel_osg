#ifndef HHSTAMPSTROKEACTION_H
#define HHSTAMPSTROKEACTION_H

#include "HHBaseCustomAction.h"
#include "lib_hhcontrolleraction_global.h"

class IHHSwitchModuleController;
class IHHModule;

class HHCONTROLLERACTIONSHARED_EXPORT HHStampStrokeAction : public HHBaseCustomAction
{
    Q_OBJECT
    Q_PROPERTY(int Width READ width WRITE setWidth)
    Q_PROPERTY(QColor Color READ color WRITE setColor)
    Q_PROPERTY(QString Resource READ resource WRITE setResource)

public:
    HHStampStrokeAction(IHHSwitchModuleController *pController,
                        QObject *parent = nullptr);

    int width();
    void setWidth(int nWidth);

    QColor color();
    void setColor(const QColor &color);

    QString resource();
    void setResource(const QString &resource);

    virtual void setPropertyInfo(const QJsonObject &info);
    virtual QJsonObject propertyInfo();

    virtual void triggerAction(const QJsonObject &info);

signals:
    void signalStrokeChangWidth(int nWidth);
    void signalStrokeChangColor(const QColor &color);
    void signalStrokeChangResource(const QString &resource);
    void signalStrokePropertyChange(QJsonObject);

private slots:
    void slotTriggered(bool);

private:
    void loadDefaultInfo();
    void updateModuleData();

private:
    IHHSwitchModuleController            *m_pIHHController;

    int                                  m_nWidth;
    QColor                               m_color;
    QString                              m_sResource;
    QString                              m_strIconPath;

    IHHModule                            *m_pIHHModule;
};

#endif // HHSTAMPSTROKEACTION_H
