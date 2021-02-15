#ifndef LIB_TEXTBOX_H
#define LIB_TEXTBOX_H

#include <QtCore/qglobal.h>

#ifdef LIB_STATIC_TEXTBOX
    #define LIB_EXPORT_TEXTBOX
#else
    #if defined(LIB_BUILD_TEXTBOX)
        #define LIB_EXPORT_TEXTBOX Q_DECL_EXPORT
    #else
        #define LIB_EXPORT_TEXTBOX Q_DECL_IMPORT
    #endif
#endif // LIB_STATIC_TEXTBOX

#endif // LIB_TEXTBOX_H
