#ifndef LIB_UIFACTORY_H
#define LIB_UIFACTORY_H

#include <QtCore/qglobal.h>

#ifdef LIB_STATIC_UIFACTORY
    #define LIB_EXPORT_UIFACTORY
#else
    #if defined(LIB_BUILD_UIFACTORY)
        #define LIB_EXPORT_UIFACTORY Q_DECL_EXPORT
    #else
        #define LIB_EXPORT_UIFACTORY Q_DECL_IMPORT
    #endif
#endif // LIB_STATIC_UIFACTORY


#endif // LIB_UIFACTORY_H
