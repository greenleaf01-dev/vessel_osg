#ifndef LIB_FoundationPreAndTeaching_GLOBAL_H
#define LIB_FoundationPreAndTeaching_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LIB_STATIC
    #define LIB_FoundationPreAndTeaching_EXPORT
#else
    #if defined(LIB_FoundationPreAndTeaching_BUILD)
        #define LIB_FoundationPreAndTeaching_EXPORT Q_DECL_EXPORT
    #else
        #define LIB_FoundationPreAndTeaching_EXPORT Q_DECL_IMPORT
    #endif
#endif // LIB_STATIC

#endif // LIB_FoundationPreAndTeaching_GLOBAL_H
