#ifndef HHBASEBUSINESSCONTROLLER_H
#define HHBASEBUSINESSCONTROLLER_H

#include "lib_framebasementcontroller_global.h"
#include "ihhframebusinesscontroller.h"

class FRAMEBASEMENTCONTROLLERSHARED_EXPORT HHBaseBusinessController : public QObject, public IHHFrameBusinessController
{
    Q_OBJECT
    Q_INTERFACES( IHHFrameBusinessController )

public:
    explicit HHBaseBusinessController(QObject *parent = nullptr);

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

#endif // HHBASEBUSINESSCONTROLLER_H
