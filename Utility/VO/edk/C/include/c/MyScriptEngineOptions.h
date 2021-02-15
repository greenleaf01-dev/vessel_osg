#ifndef C_MYSCRIPTENGINEOPTIONS_H
#define C_MYSCRIPTENGINEOPTIONS_H 0x01000001
/**
 * @file c/MyScriptEngineOptions.h
 * Defines the <code>voEngineOption</code> structure that can be passed to the
 * <code>voCreateEngine()</code> function.
 * Unless, you are doing very specific things you will not use this with the
 * standard edition.
 */

#include "MyScriptEngine.h"


// -- system functions ---------------------------------------------------------

/**
 * Basic functions.
 */
typedef struct _voBasicFunctions
{
  /**
   * Pointer to a function that deallocates the space pointed to by
   * <code>ptr</code>, in conformance with C89-7.10.3.2 / C99-7.20.3.2.
   */
  void (VO_MSE_CALL *ptr_free)(void* ptr);

  /**
   * Pointer to a function that allocates space for <code>size</code> bytes, in
   * conformance with C89-7.10.3.3 / C99-7.20.3.3.
   */
  void* (VO_MSE_CALL *ptr_malloc)(size_t size);

  /**
   * Pointer to a function that resizes the space pointed to by
   * <code>ptr</code> to <code>size</code>, in conformance with
   * C89-7.10.3.4 / C99 7.20.3.4.
   */
  void* (VO_MSE_CALL *ptr_realloc)(void* ptr, size_t size);

  /**
   * Pointer to an optional function that returns the size available in the
   * space pointed to by <code>ptr</code> that was previously allocated by
   * <code>malloc</code> or <code>realloc</code>. If NULL, memory statistics
   * will count only requested not actual memory usage.
   */
  size_t (VO_MSE_CALL *ptr_msize)(void* ptr);

  /**
   * Pointer to a function that copies <code>count</code> bytes from
   * <code>src</code> to <code>dest</code> non-overlapping space, in
   * conformance with C89-7.11.2.1 / C99-7.21.2.1.
   */
  void* (VO_MSE_CALL *ptr_memcpy)(void* dest, void const* src, size_t count);

  /**
   * Pointer to a function that copies <code>count</code> bytes from
   * <code>src</code> to <code>dest</code>, in conformance with
   * C89-7.11.2.2 / C99-7.21.2.2.
   */
  void* (VO_MSE_CALL *ptr_memmove)(void* dest, void const* src, size_t count);
  
  /**
   * Pointer to a function that copies the value <code>val</code> into each of
   * the first <code>count</code> bytes of the space pointed to by
   * <code>dest</code>, in conformance with C89-7.11.6.1 / C99-7.21.6.1.
   */
  void* (VO_MSE_CALL *ptr_memset)(void* dest, int val, size_t count);

  /**
   * Pointer to a function that tells if the memory space pointed to by
   * <code>ptr</code> is readable over <code>size</code> bytes. You can set this
   * to <code>NULL</code>, in which case the  engine will throw
   * <code>VO_INTERNAL_ERROR</code> instead of
   * <code>VO_INVALID_USER_BUFFER</code> when a user supplied buffer is
   * unreadable.
   */
  bool (VO_MSE_CALL *ptr_isReadable)(volatile void const* ptr, size_t size);
  
  /**
   * Pointer to a function that tells if the memory space pointed to by
   * <code>ptr</code> is writable over <code>size</code> bytes. You can set this
   * to <code>NULL</code>, in which case the  engine will throw
   * <code>VO_INTERNAL_ERROR</code> instead of
   * <code>VO_INVALID_USER_BUFFER</code> when a user supplied buffer is
   * unwritable.
   */
  bool (VO_MSE_CALL *ptr_isWritable)(volatile void* ptr, size_t size);
}
voBasicFunctions;

/**
 * Mathematics functions.
 */
typedef struct _voMathematicsFunctions
{
  /**
   * Pointer to a function that computes the exponential function of
   * <code>x</code>, in conformance with C89-7.5.4.1 / C99-7.12.6.1.
   */
  double (VO_MSE_CALL *ptr_exp)(double x);

  /**
   * Pointer to a function that computes the natural logarithm of x, in
   * conformance with C89-7.5.4.4 / C99-7.12.6.7.
   */
  double (VO_MSE_CALL *ptr_log)(double x);
  
  /**
   * Pointer to a function that computes the nonnegative square root of x, in
   * conformance with C89-7.5.5.2 / C99-7.12.7.5.
   */
  double (VO_MSE_CALL *ptr_sqrt)(double x);
  
  /**
   * Pointer to a function that computes x raised to the power y, in
   * conformance with C89-7.5.5.1 / C99-7.12.7.4.
   */
  double (VO_MSE_CALL *ptr_pow)(double x, double y);
  
  /**
   * Pointer to a function that computes the floating-point remainder of
   * <code>x/y</code>, in conformance with C89-7.5.6.4 / C99-7.12.10.1.
   */
  double (VO_MSE_CALL *ptr_fmod)(double x, double y);
  
  /**
   * Pointer to a function that computes the principal value of the arc tangent
   * of <code>y/x</code> using the signs of both arguments to determine the
   * quadrant of the return value, in conformance with
   * C89-7.5.2.4 / C99-7.12.4.4.
   */
  double (VO_MSE_CALL *ptr_atan2)(double y, double x);
}
voMathematicsFunctions;

/**
 * Concurrent programming functions.
 */
typedef struct _voConcurrentProgrammingFunctions
{
  /**
   * Returns the size of a thread identifier.
   */
  size_t (VO_MSE_CALL *ptr_thread_sizeof)();
  
  /**
   * Returns the identifier of the running thread.
   */
  void (VO_MSE_CALL *ptr_thread_self)(void* thread);
  
  /**
   * Tells whether the two thread identifiers are equal.
   */
  bool (VO_MSE_CALL *ptr_thread_equals)(void* thread1, void* thread2);

  /**
   * Returns the size of a mutex.
   */
  size_t (VO_MSE_CALL *ptr_mutex_sizeof)();
  
  /**
   * Creates a mutex.
   */
  bool (VO_MSE_CALL *ptr_mutex_construct)(void* mutex);
  
  /**
   * Destroys a mutex.
   */
  void (VO_MSE_CALL *ptr_mutex_destruct)(void* mutex);
  
  /**
   * Acquires a lock on a mutex.
   */
  void (VO_MSE_CALL *ptr_mutex_acquire)(void* mutex);
  
  /**
   * Releases a lock on a mutex.
   */
  void (VO_MSE_CALL *ptr_mutex_release)(void* mutex);
}
voConcurrentProgrammingFunctions;

/**
 * Timing functions.
 */
typedef struct _voTimingFunctions
{
  /**
   * Optional pointer to a function that initializes the timing system.
   */
  void (VO_MSE_CALL *ptr_timing_initialize)();
  
  /**
   * Optional pointer to a function that finalizes the timing system.
   */
  void (VO_MSE_CALL *ptr_timing_finalize)();
  
  /**
   * Pointer to a function that returns the current time in milliseconds elapsed
   * since an arbitrary fixed reference time.
   */
  double (VO_MSE_CALL *ptr_timing_getTime)();
}
voTimingFunctions;

/**
 * System functions.
 */
typedef struct _voSystemFunctions
{
  /**
   * Pointers to basic functions.
   */
  voBasicFunctions* basic;
  
  /**
   * Pointers to math functions.
   */
  voMathematicsFunctions* math;
  
  /**
   * Optional pointer to concurrent programming functions. When
   * <code>NULL</code>, the engine assumes that the application is single
   * threaded.
   */
  voConcurrentProgrammingFunctions* concurrentProgramming;
  
  /**
   * Optional pointer to timing functions.
   */
  voTimingFunctions* timingFunctions;
}
voSystemFunctions;

/**
 * Engine Options.
 */
typedef struct _voEngineOptions
{
  /**
   * Optional pointer to the system functions you want the MyScript engine to
   * use.
   */
  voSystemFunctions const* systemFunctions;
}
voEngineOptions;


#endif // end of: #ifndef C_MYSCRIPTENGINEOPTIONS_H
