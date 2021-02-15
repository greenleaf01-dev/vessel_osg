//软笔
#ifndef HHBRUSHSTROKEACTION_H
#define HHBRUSHSTROKEACTION_H

#include "HHBaseCustomAction.h"
#include "lib_hhcontrolleraction_global.h"

class IHHSwitchModuleController;
class IHHModule;

class HHCONTROLLERACTIONSHARED_EXPORT HHBrushStrokeAction : public HHBaseCustomAction
{
    Q_OBJECT
    Q_PROPERTY(int Width READ width WRITE setWidth)
    Q_PROPERTY(QColor Color READ color WRITE setColor)

public:
    HHBrushStrokeAction(IHHSwitchModuleController *pController,
                        QObject *parent = nullptr);

    int width();
    void setWidth(int nWidth);

    QColor color();
    void setColor(const QColor &color);

    virtual void setPropertyInfo(const QJsonObject &info);
    virtual QJsonObject propertyInfo();

    virtual void triggerAction(const QJsonObject &info);

signals:
    void signalStrokeChangColor(const QColor &color);
    void signalStrokeChangWidth(int nWidth);
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

    QColor                               m_color;
    int                                  m_nWidth;

    int                                  m_nDrawLineShape;
};

#endif // HHBRUSHSTROKEACTION_H
