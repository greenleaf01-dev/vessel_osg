#ifndef LIB_FRAMEBASEMENTCONTROLLER_GLOBAL_H
#define LIB_FRAMEBASEMENTCONTROLLER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FRAMEBASEMENTCONTROLLER_LIBRARY)
#  define FRAMEBASEMENTCONTROLLERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FRAMEBASEMENTCONTROLLERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIB_FRAMEBASEMENTCONTROLLER_GLOBAL_H
