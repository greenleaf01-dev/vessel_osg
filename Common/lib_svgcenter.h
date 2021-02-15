#ifndef LIB_SVGCENTER_H
#define LIB_SVGCENTER_H

#include <QtCore/qglobal.h>

#ifdef LIB_STATIC_SVGCENTER
    #define LIB_EXPORT_SVGCENTER
#else
    #if defined(LIB_BUILD_SVGCENTER)
        #define LIB_EXPORT_SVGCENTER Q_DECL_EXPORT
    #else
        #define LIB_EXPORT_SVGCENTER Q_DECL_IMPORT
    #endif
#endif // LIB_STATIC_SVGCENTER

#endif // LIB_SVGCENTER_H
