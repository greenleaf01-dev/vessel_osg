#ifndef HHDELETEPIXELACTION_H
#define HHDELETEPIXELACTION_H

#include <QObject>
#include "HHBaseCustomAction.h"
#include "lib_hhcontrolleraction_global.h"

class IHHSwitchModuleController;
class IHHModule;

class HHCONTROLLERACTIONSHARED_EXPORT HHDeletePixelAction : public HHBaseCustomAction
{
    Q_OBJECT
    Q_PROPERTY(int Width READ width WRITE setWidth)

public:
    explicit HHDeletePixelAction(
            IHHSwitchModuleController *pController,
            QObject *parent = nullptr);

    int width();
    void setWidth(int nWidth);

    virtual void setPropertyInfo(const QJsonObject &info);

signals:
    void signalDelPixelChangeWidth(int nWidth);

public slots:

private slots:
    void slotTriggered(bool);

private:
    void iniDefaultInfo();
    void updateModuleData();

private:
    int                                 m_nWidth;

    IHHSwitchModuleController           *m_pIHHController;
    IHHModule                           *m_pIHHModule;
};

#endif // HHDELETEPIXELACTION_H
