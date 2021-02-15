//激光笔
#ifndef HHLASERSTROKEACTION_H
#define HHLASERSTROKEACTION_H

#include <QObject>
#include "HHBaseCustomAction.h"
#include "lib_hhcontrolleraction_global.h"

class IHHSwitchModuleController;
class IHHModule;

class HHCONTROLLERACTIONSHARED_EXPORT HHLaserStrokeAction : public HHBaseCustomAction
{
    Q_OBJECT
    Q_PROPERTY(int Width READ width WRITE setWidth)
    Q_PROPERTY(QColor Color READ color WRITE setColor)
    Q_PROPERTY(qreal BlinkTime READ blinkTime WRITE setBlinkTime)

public:
    explicit HHLaserStrokeAction(
            IHHSwitchModuleController *pIHHController,
            QObject *parent = nullptr);

    int width();
    void setWidth(int nWidth);

    QColor color();
    void setColor(const QColor &color);

    int blinkTime();
    void setBlinkTime(int nTime);

    virtual void setPropertyInfo(const QJsonObject &info);
    virtual QJsonObject propertyInfo();

    virtual void triggerAction(const QJsonObject &info);

signals:
    void signalStrokeChangColor(const QColor &color);
    void signalStrokeChangWidth(int nWidth);
    void signalStrokeChangBlinkTime(int nBlinkTime);

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
    int                                  m_nBlinkTime;
};

#endif // HHLASERSTROKEACTION_H
