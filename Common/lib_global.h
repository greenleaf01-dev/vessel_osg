#ifndef LIB_GLOBAL_H
#define LIB_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LIB_STATIC
    #define LIB_EXPORT
#else
    #if defined(LIB_BUILD)
        #define LIB_EXPORT Q_DECL_EXPORT
    #else
        #define LIB_EXPORT Q_DECL_IMPORT
    #endif
#endif // LIB_STATIC

#endif // LIB_GLOBAL_H
