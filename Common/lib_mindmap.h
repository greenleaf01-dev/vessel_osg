#ifndef LIB_TEXTBOX_H
#define LIB_TEXTBOX_H

#include <QtCore/qglobal.h>

#ifdef LIB_STATIC_MINDMAP
    #define LIB_EXPORT_MINDMAP
#else
    #if defined(LIB_BUILD_MINDMAP)
        #define LIB_EXPORT_MINDMAP Q_DECL_EXPORT
    #else
        #define LIB_EXPORT_MINDMAP Q_DECL_IMPORT
    #endif
#endif // LIB_STATIC_TEXTBOX

#endif // LIB_TEXTBOX_H
