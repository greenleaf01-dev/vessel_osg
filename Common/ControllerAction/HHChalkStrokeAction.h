#ifndef HHCHALKSTROKEACTION_H
#define HHCHALKSTROKEACTION_H

#include <QObject>
#include "HHBaseCustomAction.h"
#include "lib_hhcontrolleraction_global.h"

class IHHSwitchModuleController;
class IHHModule;

class HHCONTROLLERACTIONSHARED_EXPORT HHChalkStrokeAction : public HHBaseCustomAction
{
    Q_OBJECT
    Q_PROPERTY(int Width READ width WRITE setWidth)
    Q_PROPERTY(QColor Color READ color WRITE setColor)
    Q_PROPERTY(QString DashStyle READ dashStyle WRITE setDashStyle)

public:
    explicit HHChalkStrokeAction(
            IHHSwitchModuleController *pController,
            QObject *parent = nullptr);

    int width();
    void setWidth(int value);

    QColor color();
    void setColor(const QColor &color);

    QString dashStyle();
    void setDashStyle(const QString &style);

    virtual void setPropertyInfo(const QJsonObject &info);
    virtual QJsonObject propertyInfo();

    virtual void triggerAction(const QJsonObject &info);

signals:
    void signalStrokeChangColor(const QColor &color);
    void signalStrokeChangWidth(int nWidth);
    void signalStrokeChangDashStyle(const QString &style);
    void signalStrokePropertyChange(QJsonObject);

public slots:
    void slotChangePropertyInfo(const QJsonObject &info);

private slots:
    void slotTriggered(bool);

private:
    void initSystemScale();
    void initDefaultInfo();
    void updateModuleData();

private:
    int                                 m_nWidth;
    QColor                              m_color;
    QString                             m_sPenDashStyle;

    IHHSwitchModuleController           *m_pIHHController;
    IHHModule                           *m_pIHHModule;

    int                                 m_nDrawLineShape;
};
#endif // HHCHALKSTROKEACTION_H
