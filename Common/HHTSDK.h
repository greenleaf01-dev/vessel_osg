#ifndef LIB_CONTROLCENTER_H
#define LIB_CONTROLCENTER_H

#include <QtCore/qglobal.h>

#ifdef LIB_STATIC_CONTROLCENTER
    #define LIB_CONTROLCENTER_EXPORT
#else
    #if defined(LIB_HHTSDK_BUILD)
        #define LIB_HHTSDK_EXPORT Q_DECL_EXPORT
    #else
        #define LIB_HHTSDK_EXPORT Q_DECL_IMPORT
    #endif
#endif // LIB_STATIC



//gdef 

#endif // LIB_CONTROLCENTER_H
