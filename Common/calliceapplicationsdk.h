#ifndef _CALLAPPLICATION_SDK_H_
#define _CALLAPPLICATION_SDK_H_

#include <QObject>
#include <QVector>
#include <QString>

#include <QMap>
#include <QVariantMap>

class IDiscCtrl;
class IHHFrameDevicesController;

class ICallApplicationSDK
{
    public:
    /**
    *  release:释放对象指针
    *  @param
    *  @return int 0 成功  非0 失败
    */
    virtual void release() = 0;


    /**
    *  getDiscCtrl:获取圆盘操作指针
    *  @param pIDisc out 圆盘操作指针
    *  @return int 0 成功  非0 失败
    */
    virtual int getDiscCtrl(IDiscCtrl *& pIDisc) = 0;

    virtual void setFrameDeviceController(IHHFrameDevicesController *pIHHFrameDeviceController) = 0;

    // 快捷键调用
    virtual int notifyShortCutKey(const QString &sKey, const QVariantMap &info) = 0;
    // 圆盘调用
    virtual int notifyDiscKey(const QString &sKey, const QVariantMap &info) = 0;
    // App调用——其他
    virtual int notifyICEInfo(const QString &sKey, const QVariantMap &info) = 0;
};



#endif// _CALLAPPLICATION_SDK_H_
