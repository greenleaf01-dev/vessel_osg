#ifndef LIB_UIPreAndTeaching_H
#define LIB_UIPreAndTeaching_H

#include <QtCore/qglobal.h>

#ifdef LIB_STATIC_UIPreAndTeaching
    #define LIB_EXPORT_UIPreAndTeaching
#else
    #if defined(LIB_BUILD_UIPreAndTeaching)
        #define LIB_EXPORT_UIPreAndTeaching Q_DECL_EXPORT
    #else
        #define LIB_EXPORT_UIPreAndTeaching Q_DECL_IMPORT
    #endif
#endif // LIB_STATIC_UIPreAndTeaching


#endif // LIB_UIPreAndTeaching_H
