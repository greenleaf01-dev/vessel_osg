#ifndef LIB_OBJANIMATION_H
#define LIB_OBJANIMATION_H

#include <QtCore/qglobal.h>

#ifdef LIB_STATIC_OBJANIMATION
    #define LIB_EXPORT_OBJANIMATION
#else
    #if defined(LIB_BUILD_OBJANIMATION)
        #define LIB_EXPORT_OBJANIMATION Q_DECL_EXPORT
    #else
        #define LIB_EXPORT_OBJANIMATION Q_DECL_IMPORT
    #endif
#endif // LIB_STATIC_OBJANIMATION


#endif // LIB_OBJANIMATION_H