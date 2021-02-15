#ifndef LIB_DATAPROVIDER_H
#define LIB_DATAPROVIDER_H

#include <QtCore/qglobal.h>

#ifdef LIB_STATIC_DATAPROVIDER
    #define LIB_DATAPROVIDER_EXPORT
#else
    #if defined(LIB_DATAPROVIDER_BUILD)
        #define LIB_DATAPROVIDER_EXPORT Q_DECL_EXPORT
    #else
        #define LIB_DATAPROVIDER_EXPORT Q_DECL_IMPORT
    #endif
#endif // LIB_STATIC

#endif // LIB_DATAPROVIDER_H
