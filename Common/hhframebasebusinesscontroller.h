#ifndef HHFRAMEBASEBUSINESSCONTROLLER_H
#define HHFRAMEBASEBUSINESSCONTROLLER_H

#include "lib_framecontroller_global.h"
#include "ihhframebusinesscontroller.h"

class FRAMECONTROLLERSHARED_EXPORT HHFrameBaseBusinessController : public QObject, public IHHFrameBusinessController
{
    Q_OBJECT
    Q_INTERFACES( IHHFrameBusinessController )

public:
    explicit HHFrameBaseBusinessController(QObject *parent = nullptr);

    virtual QObject *getObject();

    virtual int tryTask(const QString &sTaskID);

    virtual void exitApp();
    virtual void callNotifyInfo(const QString &sNotifyID,
                                const QJsonObject &info);

signals:
    void signalExitApp();
public slots:

private:

};

#endif // HHFRAMEBASEBUSINESSCONTROLLER_H
