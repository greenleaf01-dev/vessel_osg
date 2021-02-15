#ifndef LIB_BOOTH_H
#define LIB_BOOTH_H

#include <QtCore/qglobal.h>

#ifdef LIB_STATIC_BOOTH
    #define LIB_EXPORT_BOOTH
#else
    #if defined(LIB_BUILD_BOOTH)
        #define LIB_EXPORT_BOOTH Q_DECL_EXPORT
    #else
        #define LIB_EXPORT_BOOTH Q_DECL_IMPORT
    #endif
#endif // LIB_STATIC_BOOTH


#endif // LIB_BOOTH_H
