#ifndef LIB_CALLAPPLICATIONSDK_H
#define LIB_CALLAPPLICATIONSDK_H

#include <QtCore/qglobal.h>

#ifdef LIB_CALLAPPLICATIONSDK_EXPORT
    #define LIB_CALLAPPLICATIONSDK_EXPORT
#else
    #if defined(LIB_HHTSDK_BUILD)
        #define LIB_CALLHHTSDK_EXPORT Q_DECL_EXPORT
    #else
        #define LIB_CALLHHTSDK_EXPORT Q_DECL_IMPORT
    #endif
#endif // LIB_STATIC



//gdef 

#endif // LIB_CONTROLCENTER_H
