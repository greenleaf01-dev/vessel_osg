#ifndef LIB_STROKES_H
#define LIB_STROKES_H

#include <QtCore/qglobal.h>

#ifdef LIB_STATIC_STROKES
    #define LIB_EXPORT_STROKES
#else
    #if defined(LIB_BUILD_STROKES)
        #define LIB_EXPORT_STROKES Q_DECL_EXPORT
    #else
        #define LIB_EXPORT_STROKES Q_DECL_IMPORT
    #endif
#endif // LIB_STATIC_STROKES

#endif // LIB_STROKES_H
