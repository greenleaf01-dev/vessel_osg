#ifndef LIB_HHCONTROLLERACTION_GLOBAL_H
#define LIB_HHCONTROLLERACTION_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HHCONTROLLERACTION_LIBRARY)
#  define HHCONTROLLERACTIONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define HHCONTROLLERACTIONSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // HHCONTROLLERACTION_GLOBAL_H
