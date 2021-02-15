#pragma once

#include <QObject>

class ICallApplicationSDK;

class IHHFrameBusinessController{
public:
    ~IHHFrameBusinessController() {}

    virtual QObject *getObject() = 0;

    virtual int tryTask(const QString &sTaskID) = 0;

    virtual void exitApp() = 0;
    virtual void callNotifyInfo(const QString &sNotifyID,
                                const QJsonObject &info) = 0;
};

Q_DECLARE_INTERFACE( IHHFrameBusinessController, "com.hht.qtWhiteBoard.IHHFrameBusinessController/1.0" )
Q_DECLARE_METATYPE( IHHFrameBusinessController* )
