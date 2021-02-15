#ifndef LIB_3DTOOLS_H
#define LIB_3DTOOLS_H

#include <QtCore/qglobal.h>

#ifdef LIB_STATIC_3DTOOLS
    #define LIB_EXPORT_3DTOOLS
#else
    #if defined(LIB_BUILD_3DTOOLS)
        #define LIB_EXPORT_3DTOOLS Q_DECL_EXPORT
    #else
        #define LIB_EXPORT_3DTOOLS Q_DECL_IMPORT
    #endif
#endif // LIB_STATIC_UIFACTORY


#endif // LIB_3DTOOL_H
