//荧光笔
#ifndef HHFLUORESCENTSTROKEACTION_H
#define HHFLUORESCENTSTROKEACTION_H

#include <QObject>
#include "HHBaseCustomAction.h"
#include "lib_hhcontrolleraction_global.h"

class IHHSwitchModuleController;
class IHHModule;

class HHCONTROLLERACTIONSHARED_EXPORT HHFluorescentStrokeAction : public HHBaseCustomAction
{
    Q_OBJECT
    Q_PROPERTY(int Width READ width WRITE setWidth)
    Q_PROPERTY(QColor Color READ color WRITE setColor)
    Q_PROPERTY(qreal Opacity READ opacity WRITE setOpacity)

public:
    explicit HHFluorescentStrokeAction(
            IHHSwitchModuleController *pIHHController,
            QObject *parent = nullptr);

    int width();
    void setWidth(int nWidth);

    QColor color();
    void setColor(const QColor &color);

    qreal opacity();
    void setOpacity(qreal opacity);

    virtual void setPropertyInfo(const QJsonObject &info);
    virtual QJsonObject propertyInfo();

    virtual void triggerAction(const QJsonObject &info);

signals:
    void signalStrokeChangColor(const QColor &color);
    void signalStrokeChangWidth(int nWidth);
    void signalStrokeChangOpacity(qreal opacity);
    void signalStrokePropertyChange(QJsonObject);

public slots:

private slots:
    void slotTriggered(bool);

private:
    void loadDefaultInfo();
    void updateModuleData();

private:
    IHHSwitchModuleController            *m_pIHHController;
    IHHModule                            *m_pIHHModule;

    int                                  m_nWidth;
    QColor                               m_color;
    qreal                                m_fOpacity;
};

#endif // HHFLUORESCENTSTROKEACTION_H
