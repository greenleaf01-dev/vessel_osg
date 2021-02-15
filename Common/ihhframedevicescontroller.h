#ifndef _IHHFRAME_DEVICESCONTROL_H_
#define _IHHFRAME_DEVICESCONTROL_H_

#include <QObject>

class IHHActionsManager;
class IHHFrameBusinessController;
class ICallApplicationSDK;

// 界面Device控制
class IHHFrameDevicesController{
public:
    virtual ~IHHFrameDevicesController(){}

    virtual QObject *getObject() = 0;

    virtual void initActionManger(IHHActionsManager *pIHHActionManger) = 0;
    virtual void initIHHFrameBusinessController(IHHFrameBusinessController *pBusinessController) = 0;
    virtual void initICallApplicationSDK(ICallApplicationSDK *pCallAppSDK) = 0;

    // 尝试可用与否
    // 0:可调用，非0不可
    virtual int tryTask(const QString &sID, const QVariantMap &info) = 0;
    // 快捷键调用
    virtual int notifyShortCutKey(const QString &sKey, const QVariantMap &info) = 0;
    // 圆盘调用
    virtual int notifyDiscKey(const QString &sKey, const QVariantMap &info) = 0;
    // 其他
    virtual int iceCallNotifyInfo(const QString &sKey, const QVariantMap &info) = 0;

    virtual int setDeviceLinked(bool bLinked) = 0;

};


Q_DECLARE_INTERFACE( IHHFrameDevicesController, "com.hht.qtWhiteBoard.IHHFrameDevicesController/1.0" )
Q_DECLARE_METATYPE( IHHFrameDevicesController* )

#endif //_IHHFRAME_DEVICESCONTROL_H_

