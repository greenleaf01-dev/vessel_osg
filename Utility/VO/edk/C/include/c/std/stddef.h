#ifndef C_STD_STDDEF_H
#define C_STD_STDDEF_H 0x01000000
/**
 * @file c/std/stddef.h
 * Common definitions.
 * This file provides C99 Common definitions (7.17) content support.
 * 
 * @note If the <code>HAVE_STDDEF_H</code> macro is defined prior to include
 * this file then <code>&lt;stddef.h&gt;</code> is assumed to be provided by
 * the compiler and will be included.
 */

#ifdef HAVE_STDDEF_H
#include <stddef.h>
#else /* else of: #ifdef HAVE_STDDEF_H */


#ifdef _PTRDIFF_T
  #define C_STD_PTRDIFF_T
#endif

#ifdef _PTRDIFF_T_DEFINED
  #define C_STD_PTRDIFF_T
#endif

#ifndef C_STD_PTRDIFF_T
  #define _PTRDIFF_T
  #define _PTRDIFF_T_DEFINED
  #ifdef __PTRDIFF_TYPE__
    typedef __PTRDIFF_TYPE__ ptrdiff_t;
  #else
    typedef int ptrdiff_t;
  #endif
#else
  #undef C_STD_PTRDIFF_T
#endif

#ifdef _SIZE_T
  #define C_STD_SIZE_T
#endif

#ifdef _SIZE_T_DEFINED
  #define C_STD_SIZE_T
#endif

#ifndef C_STD_SIZE_T
  #define _SIZE_T
  #define _SIZE_T_DEFINED
  #ifdef __SIZE_TYPE__
    typedef __SIZE_TYPE__ size_t;
  #else
    typedef unsigned int size_t;
  #endif
#else
  #undef C_STD_SIZE_T
#endif

#ifdef _WCHAR_T
  #define C_STD_WCHAR_T
#endif

#ifdef _WCHAR_T_DEFINED
  #define C_STD_WCHAR_T
#endif

#ifndef C_STD_WCHAR_T
  #define _WCHAR_T
  #define _WCHAR_T_DEFINED
  #ifdef __WCHAR_TYPE__
    typedef __WCHAR_TYPE__ wchar_t;
  #else
    typedef unsigned short wchar_t;
  #endif
#else
  #undef C_STD_WCHAR_T
#endif

#ifndef NULL
  #ifdef __cplusplus
    #define NULL 0
  #else
    #define NULL ((void *)0)
  #endif
#endif

#ifndef offsetof
  #define offsetof(type, member_designator) ((size_t)&((type *)0)->member_designator)
#endif


#endif /* end of else of: #ifdef HAVE_STDDEF_H */


#endif /* end of: #ifndef C_STD_STDDEF_H */
