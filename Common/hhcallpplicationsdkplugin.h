#ifndef HHCALLAPPLICATIONSDKPLUGIN_H
#define HHCALLAPPLICATIONSDKPLUGIN_H

#include <QObject>
#include "lib_callapplicationsdk.h"

class ICallApplicationSDK;
class IHHFrameDevicesController;

class LIB_CALLHHTSDK_EXPORT HHCallApplicationSDKPlugin
{
public:
    HHCallApplicationSDKPlugin();
    static ICallApplicationSDK* createApplicationSDK(IHHFrameDevicesController * pFrameDeviceControl, int appid);
};

#endif // HHCALLAPPLICATIONSDKPLUGIN_H
