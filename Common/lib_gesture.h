#ifndef LIB_GESTURE_H
#define LIB_GESTURE_H

#include <QtCore/qglobal.h>

#ifdef LIB_STATIC_GESTURE
    #define LIB_EXPORT_GESTURE
#else
    #if defined(LIB_BUILD_GESTURE)
        #define LIB_EXPORT_GESTURE Q_DECL_EXPORT
    #else
        #define LIB_EXPORT_GESTURE Q_DECL_IMPORT
    #endif
#endif // LIB_STATIC_GESTURE

#endif // LIB_GESTURE_H
