#ifndef _IHHFRAME_DEVICECONTROL_H_
#define _IHHFRAME_DEVICECONTROL_H_

#include <QObject>

class IHHActionManager;
class IHHFrameBusinessController;
class ICallApplicationSDK;

// 界面Device控制
class IHHFrameDeviceController{
public:
    virtual ~IHHFrameDeviceController(){}

    virtual QObject *getObject() = 0;

    virtual void initActionManger(IHHActionManager *pIHHActionManger) = 0;
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


Q_DECLARE_INTERFACE( IHHFrameDeviceController, "com.hht.qtWhiteBoard.IHHFrameDeviceController/1.0" )
Q_DECLARE_METATYPE( IHHFrameDeviceController* )

#endif //_IHHFRAME_DEVICECONTROL_H_

