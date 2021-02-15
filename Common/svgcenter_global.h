#ifndef SVGCENTER_GLOBAL_H
#define SVGCENTER_GLOBAL_H

#include <QtCore/qglobal.h>


#ifdef LIB_STATIC_SVGCENTER
    #define SVGCENTERSHARED_EXPORT
#else
    /**
     * When building a DLL with MSVC, QUAZIP_BUILD must be defined.
     * qglobal.h takes care of defining Q_DECL_* correctly for msvc/gcc.
     */
    #if defined(SVGCENTER_LIBRARY)
        #define SVGCENTERSHARED_EXPORT Q_DECL_EXPORT
    #else
        #define SVGCENTERSHARED_EXPORT Q_DECL_IMPORT
    #endif
#endif // LIB_STATIC_GESTURE




#endif // SVGCENTER_GLOBAL_H
