#ifndef LIB_FoundationTransparent_GLOBAL_H
#define LIB_FoundationTransparent_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LIB_STATIC_FoundationTransparent
    #define LIB_FoundationTransparent_EXPORT
#else
    #if defined(LIB_FoundationTransparent_BUILD)
        #define LIB_FoundationTransparent_EXPORT Q_DECL_EXPORT
    #else
        #define LIB_FoundationTransparent_EXPORT Q_DECL_IMPORT
    #endif
#endif // LIB_STATIC

#endif // LIB_FoundationTransparent_GLOBAL_H
