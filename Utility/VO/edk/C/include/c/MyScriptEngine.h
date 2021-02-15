#ifndef C_MYSCRIPTENGINE_H
#define C_MYSCRIPTENGINE_H 0x06010000
/**
 * @file c/MyScriptEngine.h
 * Native interface to the MyScript engine. This is the interface through which
 * MyScript services expose their own interfaces.
 */

#ifndef __cplusplus
  #include <c/std/stdbool.h>
#endif
#include <stddef.h>
#include <c/std/stdint.h>


// -----------------------------------------------------------------------------

#define VO_MAKE_VERSION(major, minor, revision) (((major) << 24) | ((minor) << 16) | (revision))
#define VO_VERSION(major, minor, revision)      VO_MAKE_VERSION(major##U, minor##U, revision##U)

/**
 * The version to be passed to the `voCreateEngine()` function.
 */
#define VO_MSE_VER C_MYSCRIPTENGINE_H

#ifndef VO_MSE_IMPORT
  #ifndef _WIN32
    #ifndef __cplusplus
      /** Declares an external symbol to be imported into the code. */
      #define VO_MSE_IMPORT extern
    #else
      #define VO_MSE_IMPORT extern "C"
    #endif
  #else
    #ifndef __cplusplus
      /** Declares an external symbol to be imported into the code. */
      #define VO_MSE_IMPORT __declspec(dllimport)
    #else
      #define VO_MSE_IMPORT extern "C" __declspec(dllimport)
    #endif
  #endif
#endif

#ifndef VO_MSE_EXPORT
  #ifndef _WIN32
    #ifndef __cplusplus
      /** Declares an external symbol to be exported from the code. */
      #define VO_MSE_EXPORT
    #else
      #define VO_MSE_EXPORT extern "C"
    #endif
  #else
    #ifndef __cplusplus
      /** Declares an external symbol to be exported from the code. */
      #define VO_MSE_EXPORT __declspec(dllexport)
    #else
      #define VO_MSE_EXPORT extern "C" __declspec(dllexport)
    #endif
  #endif
#endif

#ifndef VO_MSE_CALL
  #ifdef _WIN32
    #define VO_MSE_CALL __cdecl
  #else
    /** Defines the calling convention of a function or function type. */
    #define VO_MSE_CALL
  #endif
#endif

#ifndef VO_MSE_FUNC
  #ifndef VO_MSE_IMPL
    #ifndef VO_MSE_FUNC_THROUGH_POINTERS
      /** Declares a function as part of the MyScript Engine native interface. */
      #define VO_MSE_FUNC(type,name,params) VO_MSE_IMPORT type VO_MSE_CALL name params
    #else
      #ifndef __cplusplus
        #define VO_MSE_FUNC(type,name,params) extern type (VO_MSE_CALL *name) params
      #else
        #define VO_MSE_FUNC(type,name,params) extern "C" type (VO_MSE_CALL *name) params
      #endif
    #endif
  #else
    #define VO_MSE_FUNC(type,name,params) VO_MSE_EXPORT type VO_MSE_CALL name params
  #endif
#endif

/** Declares an inline function. */
#ifndef VO_INLINE
  #if defined(_MSC_VER)
    #define VO_INLINE static __inline
  #elif defined(__GNUC__)
    #define VO_INLINE static __inline__
  #else
    #define VO_INLINE static
  #endif
#endif

#ifndef VO_USE_PRAGMA_PUSH_MACRO
  #if defined(_MSC_VER) && _MSC_VER >= 1310
    #define VO_USE_PRAGMA_PUSH_MACRO 1
  #elif defined(__GNUC__) && __GNUC__ >= 4 && __GNUC_MINOR__ >= 3
    #define VO_USE_PRAGMA_PUSH_MACRO 1
  #elif defined(__clang__)
    #define VO_USE_PRAGMA_PUSH_MACRO 1
  #else
    #define VO_USE_PRAGMA_PUSH_MACRO 0
  #endif
#endif

#ifndef VO_FUNCTIONS_ONLY


// -- basic types and constants -----------------------------------------------

/**
 * Invalid size value, returned by some functions to indicate an error.
 */
#define VO_INVALID_SIZE_T ((size_t)-1)

/**
 * Abstract identifier.
 */
typedef int32_t voId;

/**
 * Type identifier.
 */
typedef voId voTypeId;

/**
 * Property identifier.
 */
typedef voId voPropId;

#ifndef VO_YES_NO_TYPE
#define VO_YES_NO_TYPE

/**
 * Return type of functions that provide a binary response but need a third
 * value to notify a possible failure.
 */
typedef enum _voYesNo
{
  /**
   * The function failed.
   */
  VO_ERR = -1,

  /**
   * The response is "no".
   */
  VO_NO = 0,
  /**
   * The response is "yes".
   */
  VO_YES = 1
}
voYesNo;

#endif // end of: #ifndef VO_YES_NO_TYPE

#ifndef VO_CERTIFICATE_TYPE
#define VO_CERTIFICATE_TYPE

/**
 * Certificate.
 */
typedef struct _voCertificate
{
  /**
   * Pointer to the bytes composing the certificate.
   */
  const char* bytes;

  /**
   * Length of the certificate.
   */
  size_t length;
}
voCertificate;

#endif // end of: #ifndef VO_CERTIFICATE_TYPE

struct _voReference;
/**
 * Reference to a MyScript internal object.
 */
typedef struct _voReference* voReference;

/**
 * Invalid reference value. When a function returns a reference to a MyScript
 * internal object, in the case `NULL` is a valid return value,
 * `VO_INVALID_REFERENCE` is used to indicate a failure.
 */
#define VO_INVALID_REFERENCE ((voReference)-1)

/**
 * Lists the storing option flags.
 *
 * @par deprecated as of 6.0.0
 */
enum VO_STORING_OPTION_FLAG
{
  /**
   * Store using the big endian byte order (lowest order byte first).
   */
  VO_BIG_ENDIAN = 1,
  /**
   * Store using the little endian byte order (highest order byte first).
   */
  VO_LITTLE_ENDIAN = 2
};


/**
 * Defines an application supplied function that performs read operations
 * triggered by the `voLoadObject` function.
 *
 * @param buffer Pointer to the destination/source buffer.
 * @param bufferLength Length of the buffer in bytes.
 * @param userParam User defined parameter.
 *
 * @return The number of bytes actually read, or `VO_INVALID_SIZE_T`
 * on failure.
 *
 * @note When your implementation of the read function returns `0` on
 *   failure instead of the magic `VO_INVALID_SIZE_T` value, the
 *   `voGetError` function will report the
 *   `VO_PREMATURE_END_OF_DATA` error instead of the
 *   `VO_IO_FAILURE` error.
 *
 * @see voLoadObject
 */
typedef size_t (VO_MSE_CALL *voReadFunc)(void* buffer, size_t bufferLength, void* userParam);

/**
 * Defines an application supplied function that performs write operations
 * triggered by the `voStoreObject` function.
 *
 * @param buffer Pointer to the destination/source buffer.
 * @param bufferLength Length of the buffer in bytes.
 * @param userParam User defined parameter.
 *
 * @return The number of bytes actually written.
 *
 * @see voStoreObject
 */
typedef size_t (VO_MSE_CALL *voWriteFunc)(const void* buffer, size_t bufferLength, void* userParam);

/**
 * Defines an application supplied function that will receive progress
 * notifications from a time consuming task.
 *
 * @param amountDone Amount of work done since the beginning of the task.
 * @param amountTodo Total amount of work to do in order to complete the task.
 * @param userParam User defined parameter.
 *
 * @return `true` to continue the task, `false` to request
 *   its cancelation.
 *
 * @note a particular operation may not be cancelable or cancelable only up till
 *   some point in the progress, in which case it will continue as if you
 *   returned `true`.
 */
typedef bool (VO_MSE_CALL * voNotifyProgressFunc)(uint32_t amountDone, uint32_t amountTodo, void* userParam);


// -- error codes --------------------------------------------------------------

/**
 * Lists the MyScript Engine errors.
 */
enum VO_ENGINE_ERR
{
  /**
   * No error occurred. This is the value returned by `voGetError`
   * when there is no error to report.
   */
  VO_NO_ERROR,

  /**
   * The argument is invalid.
   */
  VO_INVALID_ARGUMENT = 1 << 24,
  /**
   * The requested operation is not implemented for the target object.
   */
  VO_INVALID_OPERATION = 2 << 24,
  /**
   * The requested operation cannot be performed within the current state.
   */
  VO_INVALID_STATE = 3 << 24,
  /**
   * Runtime error.
   */
  VO_RUNTIME_ERROR = 4 << 24,

  /**
   * The reference is invalid.
   */
  VO_NO_SUCH_REFERENCE = VO_INVALID_ARGUMENT | (1 << 16),
  /**
   * The `engine` reference is invalid.
   */
  VO_NO_SUCH_ENGINE,
  /**
   * The `object` reference is invalid.
   */
  VO_NO_SUCH_OBJECT,

  /**
   * Invalid version.
   */
  VO_INVALID_VERSION = VO_INVALID_ARGUMENT | (2 << 16),
  /**
   * Invalid certificate.
   */
  VO_INVALID_CERTIFICATE,
  /**
   * The index is out of bounds.
   */
  VO_INDEX_OUT_OF_BOUNDS,
  /**
   * The object is invalid for the requested operation.
   */
  VO_INVALID_OBJECT,
  /**
   * The option is invalid for the requested operation.
   */
  VO_INVALID_OPTION,
  /**
   * The given value does not have the right size.
   */
  VO_INVALID_SIZE,
  /**
   * The iteration has no such element.
   */
  VO_NO_SUCH_ELEMENT,
  /**
   * The `TrainingSet` is invalid for the requested operation.
   */
  VO_INVALID_TRAINING_SET,

  /**
   * A user supplied buffer is either unreadable or unwritable by the engine
   * process.
   */
  VO_INVALID_USER_BUFFER = VO_INVALID_ARGUMENT | (3 << 16),
  /**
   * A user supplied function crashed.
   */
  VO_INVALID_CALLBACK,

  /**
   * The specified type does not exist.
   */
  VO_NO_SUCH_TYPE = VO_INVALID_ARGUMENT | (4 << 16),
  /**
   * The specified type is not concrete. It is either an abstract type or an
   * interface type. This means instantiation is not allowed.
   */
  VO_TYPE_NOT_CONCRETE,
  /**
   * The specified type does not have a constructor with the specified
   * initializer.
   */
  VO_NO_SUCH_CONSTRUCTOR,
  /**
   * The specified interface does not exist.
   */
  VO_NO_SUCH_INTERFACE,
  /**
   * The specified property does not exist.
   */
  VO_NO_SUCH_PROPERTY,
  /**
   * The specified property is read-only.
   */
  VO_READ_ONLY_PROPERTY,
  /**
   * The specified object does not support serialization.
   */
  VO_UNSUPPORTED_SERIALIZATION,

  /**
   * The requested operation cannot be performed because it would exceed the
   * limit fixed as a programming guard.
   */
  VO_LIMIT_EXCEEDED = VO_INVALID_STATE | (1 << 16),
  /**
   * The object implements `ICompilable` and needs to be compiled
   * prior to performing the requested operation.
   */
  VO_NOT_COMPILED,
  /**
   * The object cannot be modified because it is in use by another object.
   */
  VO_MODIFICATION_ACCESS_DENIED,
  /**
   * The `endInputUnit()` call does not match any prior
   * `startInputUnit()` call.
   */
  VO_UNMATCHED_INPUT_UNIT,

  /**
   * The engine ran out of memory.
   */
  VO_OUT_OF_MEMORY = VO_RUNTIME_ERROR | 1,
  /**
   * An Input/Output operation failed.
   */
  VO_IO_FAILURE,
  /**
   * End of input has been reached while more data was needed.
   */
  VO_PREMATURE_END_OF_DATA,
  /**
   * The engine crashed.
   */
  VO_INTERNAL_ERROR,

  /**
   * The operation was canceled by the progress notification function.
   */
  VO_CANCELED,

  /**
   * The file is missing.
   */
  VO_NO_SUCH_FILE
};


// -- types and interfaces -----------------------------------------------------

/**
 * Lists the MyScript Engine types.
 */
enum VO_ENGINE_T
{
  /**
   * `Engine` type.
   * @see voEngine
   */
  VO_Engine,
  /**
   * `EngineObject` type.
   * @see voEngineObject
   */
  VO_EngineObject = 4,
  /**
   * `Iterator` type.
   * @see voIterator
   */
  VO_Iterator = 8,

  /**
   * `Charset` type.
   * @see voCharset
   * @see voCreateCharset
   */
  VO_Charset = 101,
  /**
   * `Input` type.
   * @see voInput
   */
  VO_Input,
  /**
   * `StructuredInput` type.
   * @see voStructuredInput
   */
  VO_StructuredInput = 107,
  /**
   * `FloatStructuredInput` type.
   * @see voFloatStructuredInput
   */
  VO_FloatStructuredInput,
  /**
   * `InputCharacter` type.
   * @see voInputCharacter
   */
  VO_InputCharacter = 111,

  /**
   * `voHistoryManager` type.
   * @see voHistoryManager
   */
  VO_HistoryManager,

  /**
   * `voUserObject` type.
   * @see voUserObject
   */
  VO_UserObject,
};


/**
 * Lists the MyScript Engine interfaces.
 */
enum VO_ENGINE_I
{
  /**
   * `IIterator` interface type.
   * @see voIIterator
   */
  VO_IIterator = 150,
  /**
   * `ICharset` interface type.
   * @see voICharset
   */
  VO_ICharset,

  /**
   * `IAttachTarget` interface type.
   * @see voIAttachTarget
   */
  VO_IAttachTarget,
  /**
   * `ICompilable` interface type.
   * @see voICompilable
   */
  VO_ICompilable,

  /**
   * `IInput` interface type.
   * @see voIInput
   */
  VO_IInput,

  /**
   * `IStructuredInput` interface type.
   * @see voIStructuredInput
   */
  VO_IStructuredInput = 159,
  /**
   * `IFloatStructuredInput` interface type.
   * @see voIFloatStructuredInput
   */
  VO_IFloatStructuredInput,

  /**
   * `IInputConsumer` interface type.
   * @see voIInputConsumer
   */
  VO_IInputConsumer = 163,

  /**
   * `IRunnable` interface type.
   * @see voIRunnable
   */
  VO_IRunnable,

  /**
   * `IInkTransmitter` interface type.
   * @see voIInkTransmitter
   */
  VO_IInkTransmitter,

  /**
   * `IInputCharacter` interface type.
   * @see voIInputCharacter
   */
  VO_IInputCharacter,

  /**
   * `voIHistoryManager` interface type.
   * @see voIHistoryManager
   */
  VO_IHistoryManager,

  /**
   * `voIVersionable` interface type.
   * @see voIVersionable
   */
  VO_IVersionable,

  /**
   * `voIUserObject` interface type.
   * @see voIUserObject
   */
  VO_IUserObject,
};


// -- Engine -------------------------------------------------------------------

/**
 * Reference to an instance of the `Engine` type. The
 * `Engine` type represents an instance of the MyScript runtime
 * execution environment. Such an instance is created by the
 * `voCreateEngine` function and destroyed by the
 * `voDestroyEngine` function.
 *
 * {@typeProperties VO_ENGINE_TPROP}
 *
 * @note The `Engine` type differs from the `EngineObject`
 * type and as a consequence will cause a `VO_NO_SUCH_OBJECT` error
 * if you try to use an instance of the `Engine` type as an instance
 * of the `EngineObject` type.
 *
 * @see voCreateEngine, voDestroyEngine
 */
typedef voReference voEngine;

/**
 * {@typePropertySet Engine}
 */
enum VO_ENGINE_TPROP
{
  /**
   * Represents the maximum number of `Engine` instances that can
   * exist at the same time in a MyScript enabled application. The special value
   * zero means no limit. Other values are adjusted to the next multiple of 16.
   * A value under the current count is permitted and will constrain future
   * creations.
   *
   * {@property uint32_t}
   *
   * @note The engine parameter of `vo[Get|Set]TypeProperty()` must
   *   be set to NULL.
   */
  VO_ENGINE_LIMIT,
  /**
   * Gives the number of `Engine` instances that currently exist in a
   * MyScript enabled application.
   *
   * {@property read-only uint32_t}
   *
   * @note The engine parameter of `voGetTypeProperty()` must
   *   be set to NULL.
   */
  VO_ENGINE_COUNT,
  /**
   * Gives the specification version of the `Engine`.
   *
   * {@property read-only uint32_t}
   *
   * @par deprecated as of 6.0.0
   *
   * @note The engine parameter of `voGetTypeProperty()` can be set
   *   to `NULL`.
   */
  VO_SPEC_VERSION,
  /**
   * Gives the implementation version of the `Engine`.
   *
   * {@property read-only uint32_t}
   *
   * @par deprecated as of 6.0.0
   *
   * @note The engine parameter of `voGetTypeProperty()` can be set
   *   to `NULL`.
   */
  VO_IMPL_VERSION,
  /**
   * Gives statistics about memory allocated by an `Engine` instance.
   *
   * {@property read-only voMemoryStatistics}
   *
   * @note The engine parameter of `voGetTypeProperty()` can be set
   *   to `NULL` in order to retrieve memory statistics from the
   *   engine factory, which is unique for the whole application.
   */
  VO_MEM_STATS,
  /**
   * Holds a default `Charset` object. This property enables you to
   * specify a default `Charset` object once and for all: when done,
   * you are allowed to pass `NULL` to every function that takes a
   * parameter that is a reference to a `Charset`. Since version 5.0
   * `voCreateEngine()` initialize this with a UTF-8 charset, while
   * previous versions did not set any default charset.
   *
   * {@property voCharset}
   */
  VO_DEFAULT_CHARSET
};

/**
 * A set of memory management functions that may be given to
 * `voCreateEngine()`.
 * @see voCreateEngine
 */
typedef struct _voMemoryFunctions
{
  /**
   * The version of this struct: must be `1`.
   */
  int structVersion;

  /**
   * Pointer to a function that allocates space for an array of
   * `nmemb` objects of size `size`, initialized to all
   * bits zero; in comformance with C89-7.10.3.1 / C99-7.20.3.1.
   */
  void* (VO_MSE_CALL *ptr_calloc)(size_t nmemb, size_t size);

  /**
   * Pointer to a function that deallocates the space pointed to by
   * `ptr`; in conformance with C89-7.10.3.2 / C99-7.20.3.2.
   */
  void (VO_MSE_CALL *ptr_free)(void* ptr);

  /**
   * Pointer to a function that allocates space for `size` bytes; in
   * conformance with C89-7.10.3.3 / C99-7.20.3.3.
   */
  void* (VO_MSE_CALL *ptr_malloc)(size_t size);

  /**
   * Pointer to a function that resizes the space pointed to by
   * `ptr` to `size`; in conformance with
   * C89-7.10.3.4 / C99 7.20.3.4.
   */
  void* (VO_MSE_CALL *ptr_realloc)(void* ptr, size_t size);

  /**
   * Pointer to an optional function that returns the size available in the
   * space pointed to by `ptr`. If `NULL`, memory
   * statistics will count only requested not actual memory usage.
   */
  size_t (VO_MSE_CALL *ptr_msize)(void* ptr);
}
voMemoryFunctions;

/**
 * The `MemoryStatistics` type models statistics about memory usage.
 */
typedef struct _voMemoryStatistics
{
  /**
   * Current memory usage.
   */
  size_t curMemoryUsage;
  /**
   * Maximum memory usage.
   */
  size_t maxMemoryUsage;
  /**
   * Current number of allocated memory blocks.
   */
  size_t curAllocCount;
  /**
   * Total number of allocated memory blocks.
   */
  size_t totalAllocCount;
}
voMemoryStatistics;


// -- EngineObject -------------------------------------------------------------

/**
 * Reference to an instance of the `EngineObject` type.
 * The `EngineObject` type is the abstract base type of all the
 * types that expose the different aspects of the MyScript technologies.
 *
 * <p>Each `EngineObject` is associated with a specific
 * `Engine`, which can be viewed as its parent.</p>
 *
 * <p>Remember that when you destroy a parent `Engine`, all its
 * children are released.</p>
 *
 * {@typeProperties VO_ENGINEOBJECT_TPROP}
 * {@properties VO_ENGINEOBJECT_PROP}
 */
typedef voReference voEngineObject;

/**
 * {@typePropertySet EngineObject}
 */
enum VO_ENGINEOBJECT_TPROP
{
  /**
   * Represents the maximum number of `EngineObject` instances that
   * can exist at the same time in the user side of a MyScript enabled
   * application. The special value zero means no limit. Other values are
   * adjusted to the next multiple of 16. A value under the current count is
   * permitted and will constrain future creations.
   *
   * {@property uint32_t}
   *
   * @note This applies only to types that do not define their own user limit
   *   property.
   *
   * @see voHwCtx, voResource.
   */
  VO_USER_OBJ_LIMIT,
  /**
   * Gives the number of `EngineObject` instances that currently
   * exist in the user side of a MyScript enabled application.
   *
   * {@property read-only uint32_t}
   *
   * @note This applies only to types that do not define their own user limit
   *   property.
   *
   * @see voHandwritingContext, voResource.
   */
  VO_USER_OBJ_COUNT
};

/**
 * {@propertySet EngineObject}
 */
enum VO_ENGINEOBJECT_PROP
{
  /**
   * Gives the number of user references to the `EngineObject`.
   *
   * {@property read-only uint32_t}
   */
  VO_USER_REFERENCE_COUNT = (VO_EngineObject << 16),
  /**
   * Gives the number of attach references to the `EngineObject`.
   *
   * {@property read-only uint32_t}
   */
  VO_ATTACH_REFERENCE_COUNT,
  /**
   * Gives the memory usage of the `EngineObject`, in bytes.
   *
   * {@property read-only size_t}
   *
   * @note This property is available only for some types of objects,
   *   typically serializable objects. If the object does not provide the
   *   information, `VO_INVALID_OPERATION` is thrown.
   */
  VO_MEMORY_USAGE
};


#endif // end of: #ifndef VO_FUNCTIONS_ONLY


#ifndef VO_NO_FUNCTIONS

// -- library entry points -----------------------------------------------------

/**
 * Creates a MyScript `Engine` instance.
 *
 * @param version The version used to develop the application: must be
 *   `VO_MSE_VER`.
 * @param certificate Certificate that identifies you as a legitimate MyScript
 *   engine user.
 * @param memoryFunctions Optional memory functions.
 *
 * @return The reference to the newly created `Engine` instance on
 *   success, otherwise `NULL`.
 *
 * @throws VO_INVALID_VERSION The requested specification version is not
 *   supported by the engine.
 * @throws VO_INVALID_CERTIFICATE The certificate is invalid.
 * @throws VO_INVALID_OPTION One or more of the given option(s) is/are
 *   not supported.
 * @throws VO_INVALID_USER_BUFFER Either the `certificate` or its
 *   `bytes` member is `NULL`.
 * @throws VO_LIMIT_EXCEEDED Creating the reference to the
 *   `Engine` would cause the `VO_ENGINE_COUNT` value to
 *   exceed the `VO_ENGINE_LIMIT` value.
 *
 * @see voDestroyEngine
 */
VO_MSE_FUNC(voEngine,voCreateEngine,(uint32_t version, const voCertificate* certificate, const voMemoryFunctions* memoryFunctions));

/**
 * Destroys a MyScript `Engine` instance and releases all the
 * `EngineObject` intances created with it.
 *
 * @param engine Reference to the `Engine` instance to be destroyed.
 *
 * @return `true` on success, otherwise `false`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 */
VO_MSE_FUNC(bool,voDestroyEngine,(voEngine engine));

/**
 * Returns the error thrown by the last function call in the current running
 * thread, or `VO_NO_ERROR` if no error occurred.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 *
 * @note In order to get error information about errors that have occurred in
 *   the `voCreateEngine()` or `voDestroyEngine()`
 *   functions, you have to pass `NULL` for the `engine`
 *   parameter of this function.
 *
 * @see voCreateEngine, voDestroyEngine.
 */
VO_MSE_FUNC(int,voGetError,(voEngine engine));

/**
 * Explicitly sets an error for the specified `Engine` instance so
 * that its code can be retrieved via `voGetError()`.
 *
 * @param engine Reference to an `Engine` instance.
 * @param code Error code.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 */
VO_MSE_FUNC(void,voSetError,(voEngine engine, int code));

/**
 * Returns the functions of the specified interface.
 *
 * @param engine Reference to an `Engine` instance.
 * @param iface Identifier of the interface to be retrieved.
 *
 * @return A pointer to the corresponding interface function structure or
 *   `NULL` on failure.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_NO_SUCH_INTERFACE The specified interface does not exist.
 * @throws VO_INVALID_OPERATION The specified interface does not have
 *   functions.
 *
 * @note This function is not supposed to be used directly, please use the
 *   `VO_IFACE()` helper macro instead.
 *
 * @note Invoking an interface function with an object of a type that does not
 *   implement this interface throws `VO_INVALID_OPERATION`.
 *
 * @see VO_IFACE, voImplements
 */
VO_MSE_FUNC(const void*,voGetInterface,(voEngine engine, voTypeId iface));

/**
 * Helper macro that makes the use of interface functions easier by performing
 * the correct cast on the result of `voGetInterface()`.
 *
 * @param engine Reference to an `Engine` instance.
 * @param IName Name of the interface without prefix, so that prepending
 *   `VO_` gives the identifier and prepending `vo`
 *   gives the function structure type.
 *
 * @example
 * <pre>
 * VO_IFACE(engine, IAttachTarget)->attach(engine, archive, resource);
 * </pre>
 *
 * @note Invoking an interface function with an object of a type that does not
 *   implement this interface throws `VO_INVALID_OPERATION`.
 *
 * @see voGetInterface, VO_IAttachTarget, voIAttachTarget, voImplements.
 */
#define VO_IFACE(engine, IName) ((const vo##IName*)voGetInterface(engine, VO_##IName))

/**
 * Answers the question: does the specified `type` implement the
 * specified interface `iface`?
 *
 * @param engine Reference to an `Engine` instance.
 * @param type Identifier of the type to be tested.
 * @param iface Identifier of the interface.
 *
 * @return `VO_YES` or `VO_NO` on success, otherwise
 *   `VO_ERR` on failure.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_NO_SUCH_TYPE The specified type does not exist.
 * @throws VO_NO_SUCH_INTERFACE The specified interface does not exist.
 */
VO_MSE_FUNC(voYesNo,voImplements,(voEngine engine, voTypeId type, voTypeId iface));

/**
 * Answers the question: is the type `type1` compatible with the
 * type `type2`? A type is said to be compatible with another type if
 * it is either the same or it extends the second type.
 *
 * @param engine Reference to an `Engine` instance.
 * @param type1 Identifier of the type to be tested.
 * @param type2 Identifier of the reference type.
 *
 * @return `VO_YES` or `VO_NO` on success, otherwise
 *   `VO_ERR` on failure.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_NO_SUCH_TYPE One or both of the specified types do not exist.
 */
VO_MSE_FUNC(voYesNo,voIsCompatible,(voEngine engine, voTypeId type1, voTypeId type2));

/**
 * Returns the value of the specified type property.
 *
 * @param engine Reference to an `Engine` instance.
 * @param type Identifier of the type (e.g.: `VO_Engine`).
 * @param property Identifier of the property (e.g.: `VO_MEM_STATS`).
 * @param value Pointer to the recipient that holds the value to be read.
 * @param sizeOfValue Size of the recipient you are using to hold the value of
 *   the property, in bytes. This parameter is used by the engine to ensure that
 *   the recipient you are using has the proper type.
 *
 * @return `true` on success, otherwise `false`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_NO_SUCH_TYPE The specified type does not exist.
 * @throws VO_NO_SUCH_PROPERTY The specified property does not exist
 *   within the specified type.
 * @throws VO_INVALID_SIZE The type of the given value does not have the right
 *   size.
 * @throws VO_INVALID_USER_BUFFER The given recipient is not writable.
 */
VO_MSE_FUNC(bool,voGetTypeProperty,(voEngine engine, voTypeId type, voPropId property, void* value, size_t sizeOfValue));

/**
 * Sets or resets the value of the specified type property.
 *
 * @param engine Reference to an `Engine` instance.
 * @param type Identifier of the type
 *   (e.g.: `VO_ENG_T__HANDWRITING_CONTEXT`).
 * @param property Identifier of the property
 *   (e.g.: `VO_HWCTX_LIMIT`).
 * @param value Pointer to the recipient that holds the value to be set, or
 *   `NULL` when you want to reset the property to its default value.
 * @param sizeOfValue Size of the recipient you are using to hold the value of
 *   the property, in bytes. This parameter is used by the engine to ensure that
 *   the recipient you are using has the proper type.
 *
 * @return `true` on success, otherwise `false`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_NO_SUCH_TYPE The specified type does not exist.
 * @throws VO_NO_SUCH_PROPERTY The specified property does not exist
 *   within the specified type.
 * @throws VO_READ_ONLY_PROPERTY The property is read-only.
 * @throws VO_INVALID_SIZE The type of the given value does not have the right
 *   size.
 * @throws VO_INVALID_USER_BUFFER The given value is not readable.
 * @throws VO_INVALID_ARGUMENT The given value is invalid.
 */
VO_MSE_FUNC(bool,voSetTypeProperty,(voEngine engine, voTypeId type, voPropId property, const void* value, size_t sizeOfValue));

/**
 * Creates a new `EngineObject` instance of the specified type.
 *
 * @param engine Reference to an `Engine` instance.
 * @param type Object type identifier.
 *
 * @return A reference to the created object or `NULL` on failure.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_NO_SUCH_TYPE Invalid type.
 * @throws VO_TYPE_NOT_CONCRETE The specified type is not concrete. It
 *   may be an abstract type of an interface.
 * @throws VO_NO_SUCH_CONSTRUCTOR The specified type does not have a
 *   default constructor.
 * @throws VO_LIMIT_EXCEEDED The number of `EngineObject` instances
 *   of the specified type would exceed the allowed limit (please remember that
 *   the limit can be shared by several types and that some types can override
 *   the property and define their own limit).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 *
 * @see voCreateObjectEx
 */
VO_MSE_FUNC(voEngineObject,voCreateObject,(voEngine engine, voTypeId type));

/**
 * Creates a new `EngineObject` instance of the specified type,
 * initialized with the specified initializer.
 *
 * @param engine Reference to an `Engine` instance.
 * @param type Object type identifier.
 * @param initializer Pointer to the initializer.
 * @param sizeOfInitializer Size of the initializer in bytes.
 *
 * @return A reference to the created object, or `NULL` on failure.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_NO_SUCH_TYPE Invalid type.
 * @throws VO_TYPE_NOT_CONCRETE The specified type is not concrete. It
 *   may be an abstract type or an interface.
 * @throws VO_NO_SUCH_CONSTRUCTOR The specified type does not have a
 *   constructor with the given initializer.
 * @throws VO_INVALID_USER_BUFFER The given initializer points to an unreadable
 *   memory location.
 * @throws VO_INVALID_SIZE The type of the given initializer does not have the
 *   right size.
 * @throws VO_LIMIT_EXCEEDED The number of `EngineObject` instances
 *   of the specified type would exceed the allowed limit (please remember that
 *   the limit can be shared by several types and that some types can override
 *   the property and define their own limit).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 *
 * @see voCreateObject
 */
VO_MSE_FUNC(voEngineObject,voCreateObjectEx,(voEngine engine, voTypeId type, const void* initializer, size_t sizeOfInitializer));

/**
 * Loads an `EngineObject` instance from an application supplied
 * binary data stream.
 *
 * @param engine Reference to an `Engine` instance.
 * @param readFunc Pointer to an application defined function that
 *   actually reads bytes from the binary data stream.
 * @param userParam Parameter passed through the `readFunc` function.
 *
 * @return A reference to the loaded `EngineObject` instance, or
 *   `NULL` on failure.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_INVALID_CALLBACK The `readFunc` is invalid or
 *   crashed.
 * @throws VO_PREMATURE_END_OF_DATA when the binary data stream does not
 *   contain enough data.
 * @throws VO_IO_FAILURE The binary data stream is invalid or corrupted.
 * @throws VO_LIMIT_EXCEEDED The number of `EngineObject` instances
 *   of the type being loaded would exceed the allowed limit (please remember
 *   that the limit can be shared by several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_MSE_FUNC(voEngineObject,voLoadObject,(voEngine engine, voReadFunc readFunc, void* userParam));

/**
 * Stores an `EngineObject` instance to an application supplied
 * binary data stream.
 *
 * @param engine Reference to an `Engine` instance.
 * @param object Reference to the `EngineObject` to be stored.
 * @param writeFunc Pointer to an application defined function that
 *   actually writes bytes to the binary data stream.
 * @param userParam Parameter for the `writeFunc` function.
 * @param storingOptions Storing options.
 *
 * @return `true` on success, otherwise `false`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_NO_SUCH_OBJECT The `object` reference is invalid.
 * @throws VO_NOT_COMPILED The object implements the `ICompilable`
 *   interface and has to be compiled prior to being stored.
 * @throws VO_INVALID_CALLBACK The `writeFunc` is invalid or crashed.
 * @throws VO_IO_FAILURE The `writeFunc` did not write the requested
 *   number of bytes.
 * @throws VO_INVALID_OPTION One or more of the given option(s) is/are not
 *   supported.
 * @throws VO_UNSUPPORTED_SERIALIZATION The `object` is not
 *   serializable.
 */
VO_MSE_FUNC(bool,voStoreObject,(voEngine engine, voEngineObject object, voWriteFunc writeFunc, void* userParam, uint32_t storingOptions));

/**
 * Returns a new reference to the specified `EngineObject` instance.
 * This function is useful in some object oriented languages like C++ where you
 * need to be able to design copiable objects.
 *
 * @example
 * <pre>
 * class EngineObject
 * {
 * public:
 *   EngineObject(voEngine engine, voTypeId type) : e(engine), o(voCreateObject(engine, type)) {}
 *   EngineObject(EngineObject const& other) : e(other.e), o(voAcquireObject(other.e, other.o)) {}
 *
 *   ...
 *
 *   ~EngineObject() { voReleaseObject(e, o); }
 * private:
 *   voEngine e;
 *   voEngineObject o;
 * };
 * </pre>
 *
 * @param engine Reference to an `Engine` instance.
 * @param object Reference to an `EngineObject` instance.
 *
 * @return a new reference to the specified `EngineObject` instance
 *   on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_NO_SUCH_OBJECT The `object` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of user references to the
 *   `EngineObject` would exceed `65535`.
 *
 * @see voReleaseObject
 */
VO_MSE_FUNC(voEngineObject,voAcquireObject,(voEngine engine, voEngineObject object));

/**
 * Clones the specified `EngineObject` instance.
 *
 * @param engine Reference to an `Engine` instance.
 * @param object Reference to an `EngineObject` instance.
 *
 * @return a new reference to the specified `EngineObject` instance
 *   on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_NO_SUCH_OBJECT The `object` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of instances would exceed the allowed
 *   limit (please remember that the limit can be shared by several types and
 *   that some types can override the property and define their own limit).
 * @throws VO_INVALID_OPERATION When `object` does not support
 *   cloning.
 */
VO_MSE_FUNC(voEngineObject,voCloneObject,(voEngine engine, voEngineObject object));

/**
 * Releases a reference to the specified `EngineObject` instance.
 *
 * @param engine Reference to an `Engine` instance.
 * @param object Reference to an `EngineObject` instance.
 *
 * @return `true` on success, otherwise `false`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_NO_SUCH_OBJECT The `object` reference is invalid.
 */
VO_MSE_FUNC(bool,voReleaseObject,(voEngine engine, voEngineObject object));

/**
 * Answers the question: do the two references have the same referee?
 *
 * @param engine Reference to an `Engine` instance.
 * @param object1 Reference to the first `EngineObject` instance.
 * @param object2 Reference to the second `EngineObject` instance.

 * @return `VO_YES` or `VO_NO` on success, otherwise
 *   `VO_ERR` on failure.

 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_NO_SUCH_OBJECT The `object1` reference is invalid.
 * @throws VO_NO_SUCH_OBJECT The `object2` reference is invalid.
 */
VO_MSE_FUNC(voYesNo,voIsSame,(voEngine engine, voEngineObject object1, voEngineObject object2));

/**
 * Returns the type of the specified `EngineObject` instance.
 *
 * @param engine Reference to an `Engine` instance.
 * @param object Reference to an `EngineObject` instance.
 *
 * @return The type of `object`, or `-1` on failure.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_NO_SUCH_OBJECT The `object` reference is invalid.
 */
VO_MSE_FUNC(voTypeId,voGetType,(voEngine engine, voEngineObject object));

/**
 * Returns the value of the specified object property.
 *
 * @param engine Reference to an `Engine` instance.
 * @param object Reference to an `EngineObject` instance.
 * @param property Identifier of the object property.
 * @param value Recipient for the property value.
 * @param sizeOfValue Size of the recipient you are using to hold the value of
 *   the property, in bytes. This parameter is used by the engine to ensure that
 *   the recipient you are using has the proper type.
 *
 * @return `true` on success, otherwise `false`.

 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_NO_SUCH_OBJECT The `object` reference is invalid.
 * @throws VO_NO_SUCH_PROPERTY Invalid property identifier.
 * @throws VO_INVALID_SIZE The type of the given value does not have the right
 *   size.
 * @throws VO_INVALID_USER_BUFFER The given recipient is not writable.
 */
VO_MSE_FUNC(bool,voGetProperty,(voEngine engine, voEngineObject object, voPropId property, void* value, size_t sizeOfValue));

/**
 * Sets or resets the value of the specified object property.
 *
 * @param engine Reference to an `Engine` instance.
 * @param object Reference to an `EngineObject` instance.
 * @param property Identifier of the engine property.
 * @param value Value to be set, or NULL in order to reset the property to its
 *   default value.
 * @param sizeOfValue Size of the recipient you are using to hold the value of
 *   the property, in bytes. This parameter is used by the engine to ensure that
 *   the recipient you are using has the proper type.
 *
 * @return `true` on success, otherwise `false`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_NO_SUCH_OBJECT The `object` reference is invalid.
 * @throws VO_NO_SUCH_PROPERTY Invalid property identifier.
 * @throws VO_READ_ONLY_PROPERTY The property is read-only.
 * @throws VO_INVALID_SIZE The type of the given value does not have the right
 *   size.
 * @throws VO_INVALID_USER_BUFFER The given value is not readable.
 * @throws VO_INVALID_ARGUMENT The given value is invalid.
 */
VO_MSE_FUNC(bool,voSetProperty,(voEngine engine, voEngineObject object, voPropId property, const void* value, size_t sizeOfValue));

#endif // end of: #ifndef VO_NO_FUNCTIONS
#ifndef VO_FUNCTIONS_ONLY


// -- Iterator -----------------------------------------------------------------

/**
 * Reference to an instance of the `Iterator` type.
 *
 * {@extends voEngineObject}
 * {@implements voIIterator}
 */
typedef voEngineObject voIterator;

/**
 * Functions composing the `IIterator` interface. This interface
 * exposes the public methods of the `Iterator` type.
 *
 * {@implementingTypes voIterator}
 * @see VO_IIterator, VO_Iterator.
 */
typedef struct _voIIterator
{
  /**
   * Tells if this iterator is positioned at the end of the iteration.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   *
   * @return `VO_YES` or `VO_NO` on success, otherwise
   *   `VO_ERR` on failure.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The target object does not implement this
   *   interface.
   */
  voYesNo (VO_MSE_CALL *isAtEnd)(voEngine engine, voIterator target);

  /**
   * Positions this iterator on the next element of the iteration.
   *
   * @param engine Reference an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The target object does not implement this
   *   interface.
   * @throws VO_NO_SUCH_ELEMENT The iterator is positioned at the end of the
   *   iteration.
   */
  bool (VO_MSE_CALL *next)(voEngine engine, voIterator target);
}
voIIterator;


// -- Charset ------------------------------------------------------------------

/**
 * Reference to an instance of the `Charset` type. A charset is
 * responsible for the conversion of digital text to and from MyScript
 * technologies.
 *
 * {@extends voEngineObject}
 * {@implements voICharset}
 */
typedef voEngineObject voCharset;

/**
 * To be used in place of `VoString.bytecount` when the string is
 *   zero ended.
 */
#define VO_ZERO_ENDED ((size_t)-1)

/**
 * The `String` type models a digital text string.
 */
typedef struct _voString
{
  /**
   * Pointer to the bytes of the string.
   */
  char* bytes;
  /**
   * Number of bytes.
   */
  size_t byteCount;
}
voString;

#ifndef voString_INITIALIZER
/**
 * Initializes a `voString` variable from a zero-ended string.
 * Usage:
 * <pre>
 *   voString s = voString_INITIALIZER("Hello world");
 * </pre>
 */
#define voString_INITIALIZER(string) { (char*)string, VO_ZERO_ENDED }
#endif

/**
 * Functions composing the `ICharset` interface. This interface
 * exposes the public methods of the `Charset` type.
 *
 * {@implementingTypes voCharset}
 * @see VO_ICharset, VO_Charset.
 */
typedef struct _voICharset
{
  /**
   * Returns the default character associated with this `Charset`
   * instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `Charset` instance.
   *
   * @return The default character on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_OPERATION The `target` charset has been
   *   created via `voCreateCharsetByName`.
   */
  int32_t (VO_MSE_CALL *getDefaultCharacter)(voEngine engine, voCharset target);

  /**
   * Sets the default character associated with this `Charset`
   * instance. This value is used at conversion time when no mapping is
   * available regarding the current `CodedCharacterSet` and
   * `CharacterEncodingScheme`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `Charset` instance.
   * @param character Value to be used as the default character.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_OPERATION The `target` charset has been
   *   created via `voCreateCharsetByName`.
   * @throws VO_INVALID_ARGUMENT The specified default character has no mapping
   *   in the current character encoding scheme (e.g.: a default character which
   *   value is over 255 with the `VO_CES_CHAR8` character encoding
   *   scheme).
   * @throws VO_MODIFICATION_ACCESS_DENIED if the `target` reference
   *   is in use by another object.
   */
  bool (VO_MSE_CALL *setDefaultCharacter_1)(voEngine engine, voCharset target, int32_t character);
  /** {@cloneDoc setDefaultCharacter_1} */
  bool (VO_MSE_CALL *setDefaultCharacter_2)(voEngine engine, voCharset target, unsigned short character);
  /** {@cloneDoc setDefaultCharacter_1} */
  bool (VO_MSE_CALL *setDefaultCharacter_3)(voEngine engine, voCharset target, char character);

  /**
   * Converts a character string from one representation to another.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the `Charset` instance that defines
   *   the input string representation.
   * @param inString Bytes composing the input string. Setting the
   *   `voString.byteCount` member to `-1` means that the
   *   input string is zero ended.
   * @param other Reference to the `Charset` instance that defines
   *   the output string representation.
   * @param outString Recipient for the bytes of the output string. On input the
   *   `voString.byteCount` member denotes the maximum number of
   *   bytes allowed (`-1` means infinite). On output the
   *   `voString.byteCount` value receives the actual number of bytes
   *   of the string. You can set the `voString.bytes` member to
   *   `NULL` to retrieve the number of bytes you need to allocate
   *   and make a second call with the allocated bytes.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_OBJECT The `other` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER The `inString` string or its
   *   bytes member is not readable.
   * @throws VO_INVALID_USER_BUFFER The `outString` is not readable.
   */
  bool (VO_MSE_CALL *convert)(voEngine engine, voCharset target, const voString* inString, voCharset other, voString* outString);
}
voICharset;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `Charset` type.
 *
 * @param engine the reference to an `Engine` instance.
 * @param name the name of the charset to create among "US-ASCII",
 *   "ISO-8859-1", "ISO-8859-15", "windows-1252", "UTF-8", "UTF-8Y", "UTF-16",
 *   "UTF-16BE", "UTF-16LE", "UTF-32", "UTF-32BE", "UTF-32LE". If NULL, "UTF-8"
 *   is selected.
 *
 * @return A reference to the newly created `Charset` instance on
 * success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_INVALID_ARGUMENT The specified `charset` is not
 *   supported.
 * @throws VO_LIMIT_EXCEEDED The number of `Charset` instances would
 *   exceed the allowed limit (please remember that the limit can be shared by
 *   several types and that some types can override the property and define
 *   their own limit).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voCharset voCreateCharset(voEngine engine, const char* name)
{
  return voCreateObjectEx(engine, VO_Charset, name, sizeof(const char*));
}

#endif // end of: #ifndef #ifndef VO_NO_FUNCTIONS

#endif // end of: #ifndef VO_FUNCTIONS_ONLY

#ifndef VO_NO_FUNCTIONS
/**
 * Loads an `EngineObject` instance from the specified file.
 *
 * @param engine a reference to an `Engine` instance.
 * @param charset the charset to be used to decode `fileName` and `mediaType`.
 * @param fileName the string value that represent the name of the file to load.
 * @param mediaType an optional string value that represent the media type to
 *   use. This is useful if the actual mime type can't be derived from the file
 *   itself.
 *
 * @return A reference to the loaded `EngineObject` instance, or
 *   `NULL` on failure.
 *
 * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
 * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
 * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL` and no default
 *   charset was set.
 * @throws VO_INVALID_OBJECT the `charset` reference is not a reference to a
 *   `Charset` instance.
 * @throws VO_INVALID_USER_BUFFER the `fileName` string is not readable.
 * @throws VO_INVALID_USER_BUFFER the `bytes` member of the `fileName` string is
 *   not readable.
 * @throws VO_INVALID_USER_BUFFER the `bytes` member of the `mediaType` string
 *   is not readable.
 * @throws VO_PREMATURE_END_OF_DATA when the binary data stream does not contain
 *   enough data.
 * @throws VO_IO_FAILURE the data stream is invalid or corrupted.
 * @throws VO_NO_SUCH_FILE the file is missing.
 * @throws VO_NO_SUCH_TYPE unsupported media type, this may be caused by a
 *   missing or unauthorized library.
 * @throws VO_LIMIT_EXCEEDED the number of `EngineObject` instances of the type
 *   being loaded would exceed the allowed limit (please remember that the limit
 *   can be shared by several types).
 * @throws VO_OUT_OF_MEMORY not enough memory to create the object.
 */
VO_MSE_FUNC(voEngineObject,voLoadObjectFromFile,(voEngine engine, voCharset charset, const voString* fileName, const voString* mediaType));

/**
 * Stores an `EngineObject` instance to the specified file.
 *
 * @param engine a reference to an `Engine` instance.
 * @param object a reference to the `EngineObject` to store.
 * @param charset the charset to be used to decode `fileName` and `mediaType`.
 * @param fileName the string value that represent the name of the file to load.
 * @param mediaType an optional string value that represent the media type to
 *   use. This is useful if the actual mime type can't be derived from the file
 *   itself.
 *
 * @return A reference to the loaded `EngineObject` instance, or
 *   `NULL` on failure.
 *
 * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
 * @throws VO_NO_SUCH_ENGINE the `object` reference is invalid.
 * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
 * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL` and no default
 *   charset was set.
 * @throws VO_INVALID_OBJECT the `charset` reference is not a reference to a
 *   `Charset` instance.
 * @throws VO_INVALID_USER_BUFFER the `fileName` string is not readable.
 * @throws VO_INVALID_USER_BUFFER the `bytes` member of the `fileName` string is
 *   not readable.
 * @throws VO_INVALID_USER_BUFFER the `bytes` member of the `mediaType` string
 *   is not readable.
 * @throws VO_NOT_COMPILED the object implements the `ICompilable` interface and
 *   has to be compiled prior to being stored.
 * @throws VO_UNSUPPORTED_SERIALIZATION the `object` is not serializable.
 * @throws VO_IO_FAILURE failed to write to file.
 */
VO_MSE_FUNC(bool,voStoreObjectToFile,(voEngine engine, voEngineObject object, voCharset charset, const voString* fileName, const voString* mediaType));
#endif // end of: #ifndef VO_NO_FUNCTIONS

#ifndef VO_FUNCTIONS_ONLY


// -- IAttachTarget ------------------------------------------------------------

/**
 * Functions composing the `IAttachTarget` interface.
 */
typedef struct _voIAttachTarget
{
  /**
   * Attaches another `EngineObject` instance to this attach target.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param other Reference to the `EngineObject` instance you want
   *   to attach.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `other` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement the `IAttachTarget` interface.
   * @throws VO_INVALID_OBJECT The `target` object does not accept
   *   the attachment of this type of object.
   * @throws VO_NOT_COMPILED The `other` object is a compilable
   *   object that was not compiled.
   * @throws VO_LIMIT_EXCEEDED The number of attach references to the target
   *   `EngineObject` would exceed `65535`.
   */
  bool (VO_MSE_CALL *attach)(voEngine engine, voEngineObject target, voEngineObject other);

  /**
   * Detaches an `EngineObject` instance from this attach target.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param other Reference to the `EngineObject` instance you want
   *   to detach.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `other` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement the `IAttachTarget` interface.
   * @throws VO_INVALID_OBJECT The `other` object is not attached.
   */
  bool (VO_MSE_CALL *detach)(voEngine engine, voEngineObject target, voEngineObject other);

  /**
   * Returns the number of `EngineObject` instances attached to this
   * attach target.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   *
   * @return The number of `EngineObject` instances attached to
   *   this attach `target` on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement the `IAttachTarget` interface.
   */
  uint32_t (VO_MSE_CALL *getAttachedCount)(voEngine engine, voEngineObject target);

  /**
   * Returns the `EngineObject` instance attached at the specified
   * index.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param index The index of the attached `EngineObject` to be
   *   returned.
   *
   * @return The reference to the `EngineObject` instance attached
   *   at the specified `index` on success, otherwise
   *   `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement the `IAttachTarget` interface.
   * @throws VO_INDEX_OUT_OF_BOUNDS The specified `index` parameter
   *   is not between `0` and `getAttachedCount - 1`.
   * @throws VO_LIMIT_EXCEEDED The number of `EngineObject` instances
   *   would exceed the allowed limit (please remember that the limit can be
   *   shared by several types and that some types can override the property and
   *   define their own limit).
   *
   * @note The order in which the objects are returned does not necessarily
   *   correspond to the order in which they were attached.
   */
  voEngineObject (VO_MSE_CALL *getAttachedAt)(voEngine engine, voEngineObject target, uint32_t index);
}
voIAttachTarget;


// -- ICompilable --------------------------------------------------------------

/**
 * Functions composing the `ICompilable` interface.
 */
typedef struct _voICompilable
{
  /**
   * Tells whether or not the target `EngineObject` instance is
   * compiled.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   *
   * @return `VO_YES` or `VO_NO` on success, otherwise
   *   `VO_ERR` on failure.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement the `ICompilable` interface.
   */
  voYesNo (VO_MSE_CALL *isCompiled)(voEngine engine, voEngineObject target);

  /**
   * Compiles the target `EngineObject` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param notifyProgressFunc Optional pointer to a
   *   `voNotifyProgressFunc` function that enables the user
   *   application to be notified of the compilation progress.
   * @param userParam Optional pointer to a user defined parameter that will be
   *   passed through `notifyProgressFunc`.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement the `ICompilable` interface.
   * @throws VO_INVALID_STATE The `target` object is not in a state
   *   where it can be compiled.
   * @throws VO_CANCELED The operation has been canceled.
   *
   * @see voNotifyProgressFunc.
   */
  bool (VO_MSE_CALL *compile)(voEngine engine, voEngineObject target, voNotifyProgressFunc notifyProgressFunc, void* userParam);

  /**
   * De-compiles the target `EngineObject` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param notifyProgressFunc Optional pointer to a
   *   `voNotifyProgressFunc` function that enables the user
   *   application to be notified of the compilation progress.
   * @param userParam Optional pointer to a user defined parameter that will be
   *   passed through `notifyProgressFunc`.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement the `ICompilable` interface.
   * @throws VO_INVALID_OPERATION The `target` object supports
   *   compilation but not de-compilation.
   * @throws VO_NOT_COMPILED The `target` object is not compiled.
   * @throws VO_MODIFICATION_ACCESS_DENIED The `target` object
   *   cannot be de-compiled because it is in use by another object
   *   (see \ref voIAttachTarget).
   * @throws VO_CANCELED The operation has been canceled.
   *
   * @see voNotifyProgressFunc.
   */
  bool (VO_MSE_CALL *decompile)(voEngine engine, voEngineObject target, voNotifyProgressFunc notifyProgressFunc, void* userParam);
}
voICompilable;


// -- Input --------------------------------------------------------------------

/**
 * Reference to an instance of the `Input` type.
 *
 * {@extends voEngineObject}
 * {@implements voIInput}
 * {@implementingTypes voFloatStructuredInput}
 */
typedef voEngineObject voInput;

/**
 * Functions composing the `IInput` interface. This interface exposes
 * the public methods of the `Input` type.
 *
 * {@implementingTypes voInput}
 * @see VO_IInput, VO_Input.
 */
typedef struct _voIInput
{
  /**
   * Clears the input.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param keepMemory If `true`, tells the `target`
   *   object that it is allowed to keep its internal memory for later use.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement this interface.
   */
  bool (VO_MSE_CALL *clear)(voEngine engine, voEngineObject target, bool keepMemory);
}
voIInput;


// -- InputCharacter -----------------------------------------------------------

/**
 * Reference to an instance of the `InputCharacter` type.
 * This is a character with alternates and associated probabilities taking part
 * in the input to a recognizer.
 *
 * {@extends voEngineObject}
 * {@implements voIInputCharacter}
 */
typedef voEngineObject voInputCharacter;

/**
 * Functions composing the `IInputCharacter` interface. This
 * interface exposes the public methods of the `InputCharacter` type.
 *
 * {@implementingTypes voInputCharacter}
 * @see VO_IInputCharacter, VO_InputCharacter.
 */
typedef struct _voIInputCharacter
{
  /**
   * Clears the target `InputCharacter`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `InputCharacter`
   *   instance.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement this interface.
   */
  bool (VO_MSE_CALL *clear)(voEngine engine, voInputCharacter target);

  /**
   * Adds an alternate to the target `InputCharacter`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `InputCharacter`
   *   instance.
   * @param charset Reference to the `Charset` instance to be used
   *   for digital text conversion.
   * @param alternateString Pointer to the string data of the alternate.
   * @param alternateProbability Probability of the alternate.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement this interface.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is
   *   invalid.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is
   *   `NULL` and no default charset was set.
   * @throws VO_INVALID_OBJECT The `charset` object is not an
   *   instance of the `Charset` type.
   * @throws VO_INVALID_USER_BUFFER The `alternateString` or its
   *   bytes member is not readable.
   * @throws VO_INVALID_ARGUMENT The `alternateString` is empty.
   * @throws VO_INVALID_ARGUMENT The `alternateString` contains
   *   more than one Unicode Grapheme Cluster.
   * @throws VO_INVALID_ARGUMENT The `alternateProbability` is not
   *   in the valid interval: `[0, 1]`.
   * @throws VO_INVALID_STATE The `alternateString` contains a
   *   spacing character and the target `InputCharacter` is not
   *   empty.
   *
   * @see voString
   */
  bool (VO_MSE_CALL *addAlternate)(voEngine engine, voInputCharacter target, voCharset charset, const voString* alternateString, float alternateProbability);
}
voIInputCharacter;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `InputCharacter` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `InputCharacter` instance
 *   on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `InputCharacter` instances
 *   would exceed the allowed limit (please remember that the limit can be
 *   shared by several types and that some types can override the property and
 *   define their own limit).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voInputCharacter voCreateInputCharacter(voEngine engine)
{
  return voCreateObject(engine, VO_InputCharacter);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- StructuredInput ----------------------------------------------------------

/**
 * Lists the handwriting recommendation flags.
 *
 * @par deprecated as of 6.0.0
 */
enum VO_HANDWRITING_RECOMMENDATION_FLAG
{
  /**
   * Specifies that the users have been told to separate their letters. This
   * flag has to be used when you do not want to constrain the handwriting style
   * of the users, but you still want to emphasize the fact that you are
   * expecting them to separate their letters.
   */
  VO_SEPARATE_LETTERS = 1,
  /**
   * Specifies that the users have been told to write in capital letters. This
   * flag has to be used when you do not want to constrain the alphabet used by
   * the users by disallowing the use of lower case letters, but you still want
   * to emphasize the fact that you are expecting them to write in capital
   * letters.
   */
  VO_WRITE_IN_CAPITALS = 2
};

/**
 * Lists the input unit types.
 */
enum VO_INPUT_UNIT_TYPE
{
  /**
   * Character input unit.
   */
  VO_CHAR = 2 << 24,
  /**
   * Word input unit.
   */
  VO_WORD,
  /**
   * Single-line text input unit.
   */
  VO_SINGLE_LINE_TEXT,
  /**
   * Multi-line text input unit.
   */
  VO_MULTI_LINE_TEXT
};


/**
 * Reference to an instance of the `StructuredInput` type.
 *
 * {@extends voInput}
 * {@subTypes voFloatStructuredInput}
 * {@implements voIStructuredInput}
 */
typedef voInput voStructuredInput;

/**
 * Functions composing the `IStructuredInput` interface. This
 * interface exposes the public methods of the `StructuredInput`
 * type.
 *
 * {@extends voIInput}
 * {@implementingTypes voStructuredInput}
 * @see VO_IStructuredInput, VO_StructuredInput.
 *
 * @note As the C language does not provide any mechanism that could be used to
 *   simulate inheritance, inherited members are simply copied from the base
 *   structure.
 */
typedef struct _voIStructuredInput
{
  /** {@inheritDoc} */
  bool (VO_MSE_CALL *clear)(voEngine engine, voEngineObject target, bool keepMemory);

  /**
   * Sets the handwriting recommendations given to the writers.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param flags Combination of handwriting recommendation flags.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement this interface.
   * @throws VO_INVALID_STATE The `target` input is not empty.
   * @throws VO_INVALID_ARGUMENT The flag is not part of the set of known
   *   handwriting recommendation flags.
   *
   * @par deprecated as of 6.0.0
   *
   * @see VO_HANDWRITING_RECOMMENDATION_FLAG.
   */
  bool (VO_MSE_CALL *setHandwritingRecommendations)(voEngine engine, voEngineObject target, uint32_t flags);

  /**
   * Starts an input unit.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param inputUnitType Type of input unit (possible values are listed by the
   *   `VO_INPUT_UNIT_TYPE` enumeration).
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement this interface.
   * @throws VO_INVALID_ARGUMENT The type of input is invalid.
   *
   * @see VO_INPUT_UNIT_TYPE
   */
  bool (VO_MSE_CALL *startInputUnit)(voEngine engine, voEngineObject target, voId inputUnitType);

  /**
   * Ends an input unit.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param inputUnitType Type of input unit (possible values are listed by the
   *   `VO_INPUT_UNIT_TYPE` enumeration).
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement this interface.
   * @throws VO_INVALID_ARGUMENT The type of input is invalid.
   * @throws VO_UNMATCHED_INPUT_UNIT No matching start.
   *
   * @see VO_INPUT_UNIT_TYPE
   */
  bool (VO_MSE_CALL *endInputUnit)(voEngine engine, voEngineObject target, voId inputUnitType);

  /**
   * Adds a digital text string to the current input unit.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param charset Reference to the `Charset` instance to be used
   *   for digital text conversion.
   * @param string Pointer to the string data.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement this interface.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is
   *   `NULL` and no default charset was set.
   * @throws VO_INVALID_OBJECT The `charset` object is not an
   *   instance of the `Charset` type.
   * @throws VO_INVALID_USER_BUFFER The string or its bytes member is not
   *   readable.
   * @throws VO_INVALID_ARGUMENT The string is empty.
   * @throws VO_INVALID_STATE The current input unit is a character input unit
   *   and is not empty or the string to be added contains more than one
   *   character.
   *
   * @see voString
   */
  bool (VO_MSE_CALL *addString)(voEngine engine, voEngineObject target, voCharset charset, const voString* string);
}
voIStructuredInput;


/**
 * Reference to an instance of the `FloatStructuredInput` type.
 *
 * {@extends voStructuredInput}
 * {@implements voIFloatStructuredInput}
 */
typedef voStructuredInput voFloatStructuredInput;

/**
 * Functions composing the `IFloatStructuredInput` interface. This
 * interface exposes the public methods of the `FloatStructuredInput`
 * type.
 *
 * {@extends voIStructuredInput}
 * {@implementingTypes voFloatStructuredInput}
 * @see VO_IFloatStructuredInput, VO_FloatStructuredInput, voFloatStructuredInput.
 *
 * @note As the C language does not provide any mechanism that could be used to
 *   simulate inheritance, inherited members are simply copied from the base
 *   structure.
 */
typedef struct _voIFloatStructuredInput
{
  /** {@inheritDoc} */
  bool (VO_MSE_CALL *clear)(voEngine engine, voEngineObject target, bool keepMemory);
  /** {@inheritDoc} */
  bool (VO_MSE_CALL *setHandwritingRecommendations)(voEngine engine, voEngineObject target, uint32_t flags);
  /** {@inheritDoc} */
  bool (VO_MSE_CALL *startInputUnit)(voEngine engine, voEngineObject target, voId inputUnitType);
  /** {@inheritDoc} */
  bool (VO_MSE_CALL *endInputUnit)(voEngine engine, voEngineObject target, voId inputUnitType);
  /** {@inheritDoc} */
  bool (VO_MSE_CALL *addString)(voEngine engine, voEngineObject target, voCharset charset, const voString* string);

  /**
   * Sets the resolution of the coordinates in dpi. This is the resolution of
   * the grid of integer values in the chosen coordinate system. For example,
   * if you use floating-point pixel coordinates you must give the screen
   * resolution, no matter the resolution of the capturing device.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param resolution The coordinate resolution.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement this interface.
   * @throws VO_INVALID_ARGUMENT The coordinates `resolution` is not
   *   a strictly positive float value.
   */
  bool (VO_MSE_CALL *setCoordinateResolution)(voEngine engine, voEngineObject target, float resolution);

  /**
   * Defines a guide box for the current input unit.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param x Coordinate of the box origin (corner) along the x axis.
   * @param y Coordinate of the box origin (corner) along the y axis.
   * @param Width width of the guide box.
   * @param Height height of the guide box.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement this interface.
   * @throws VO_INVALID_ARGUMENT When `width <= 0`.
   * @throws VO_INVALID_ARGUMENT When `height <= 0`.
   */
  bool (VO_MSE_CALL *setGuideBox)(voEngine engine, voEngineObject target, float x, float y, float width, float height);

  /**
   * Defines guide lines with a single baseline for the current input unit.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param baselinePos Position of the baseline along the y axis.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement this interface.
   */
  bool (VO_MSE_CALL *setGuideLines_1)(voEngine engine, voEngineObject target, float baselinePos);

  /**
   * Defines guide lines with a baseline and a midline for the current input
   * unit.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param baselinePos Position of the baseline along the y axis.
   * @param toMidline Distance from the baseline to the midline.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement this interface.
   * @throws VO_INVALID_ARGUMENT When `toMidline <= 0`.
   */
  bool (VO_MSE_CALL *setGuideLines_2)(voEngine engine, voEngineObject target, float baselinePos, float toMidline);

  /**
   * Defines guide lines with baseline, midline, ascender and descender lines
   * for the current input unit.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param baselinePos Position of the baseline along the y axis.
   * @param toMidline Distance from the baseline to the midline.
   * @param toAscender Distance from the baseline to the ascender line.
   * @param toDescender Distance from the baseline to the descender line.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement this interface.
   * @throws VO_INVALID_ARGUMENT When `toMidline <= 0`.
   * @throws VO_INVALID_ARGUMENT When `toAscender <= toMidline`.
   * @throws VO_INVALID_ARGUMENT When `toDescender <= 0`.
   */
  bool (VO_MSE_CALL *setGuideLines_3)(voEngine engine, voEngineObject target, float baselinePos, float toMidline, float toAscender, float toDescender);

  /**
   * Defines multiple guides with only baselines for the current input unit.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param guideCount Number of guides.
   * @param firstBaselinePos Position of the baseline along the y axis.
   * @param gap Distance between two consecutive baselines.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement this interface.
   * @throws VO_INVALID_ARGUMENT When `count <= 1`.
   * @throws VO_INVALID_ARGUMENT When `gap <= 0`.
   */
  bool (VO_MSE_CALL *setMultipleGuideLines_1)(voEngine engine, voEngineObject target, uint32_t guideCount, float firstBaselinePos, float gap);

  /**
   * Defines guide lines with a baseline and a midline for the current input
   * unit.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param guideCount Number of guides.
   * @param firstBaselinePos Position of the baseline along the y axis.
   * @param gap Distance between two consecutive baselines.
   * @param toMidline Distance from the baseline to the midline.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement this interface.
   * @throws VO_INVALID_ARGUMENT When `count <= 1`.
   * @throws VO_INVALID_ARGUMENT When `gap <= 0`.
   * @throws VO_INVALID_ARGUMENT When `toMidline <= 0`.
   * @throws VO_INVALID_ARGUMENT When `toMidline >= gap`.
   */
  bool (VO_MSE_CALL *setMultipleGuideLines_2)(voEngine engine, voEngineObject target, uint32_t guideCount, float firstBaselinePos, float gap, float toMidline);

  /**
   * Defines guide lines with baseline, midline, ascender and descender lines
   * for the current input unit.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param guideCount Number of guides.
   * @param firstBaselinePos Position of the baseline along the y axis.
   * @param gap Distance between two consecutive baselines.
   * @param toMidline Distance from the baseline to the midline.
   * @param toAscender Distance from the baseline to the ascender line.
   * @param toDescender Distance from the baseline to the descender line.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement this interface.
   * @throws VO_INVALID_ARGUMENT When `count <= 1`.
   * @throws VO_INVALID_ARGUMENT When `gap <= 0`.
   * @throws VO_INVALID_ARGUMENT When `toMidline <= 0`.
   * @throws VO_INVALID_ARGUMENT When `toMidline >= gap`.
   * @throws VO_INVALID_ARGUMENT When `toAscender <= toMidline`.
   * @throws VO_INVALID_ARGUMENT When `toDescender <= 0`.
   * @throws VO_INVALID_ARGUMENT When
   *   `gap - toAscender <= toDescender`.
   */
  bool (VO_MSE_CALL *setMultipleGuideLines_3)(voEngine engine, voEngineObject target, uint32_t guideCount, float firstBaselinePos, float gap, float toMidline, float toAscender, float toDescender);

  /**
   * Adds a digital pen stroke to the current input unit.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param x Pointer to the first x value.
   * @param xByteStride Stride in bytes between each x value.
   * @param y Pointer to the first y value.
   * @param yByteStride Stride in bytes between each y value.
   * @param pointCount Number of points.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement this interface.
   * @throws VO_INVALID_STATE The current input unit is not a character, word,
   *   or text input unit.
   * @throws VO_INVALID_USER_BUFFER The combination of `x`,
   *   `xByteStride`, `y`, `yByteStride` and
   *   `pointCount` leads to invalid memory access.
   */
  bool (VO_MSE_CALL *addStroke)(voEngine engine, voEngineObject target, const float* x, size_t xByteStride, const float* y, size_t yByteStride, uint32_t pointCount);

  /**
   * Adds a digital pen stroke to the current input unit.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param x Pointer to the first x value.
   * @param xByteStride Stride in bytes between each x value.
   * @param y Pointer to the first y value.
   * @param yByteStride Stride in bytes between each y value.
   * @param pointCount Number of points.
   * @param strokeOrder An integer that indicates the real temporal order of the
   *   stroke in a sequence. The stroke order may be used only if you set it for
   *   all the strokes in the input.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement this interface.
   * @throws VO_INVALID_STATE The current input unit is not a character, word,
   *   or text input unit.
   * @throws VO_INVALID_ARGUMENT When `xByteStride == 0`
   * @throws VO_INVALID_ARGUMENT When `yByteStride == 0`
   * @throws VO_INVALID_ARGUMENT When `pointCount == 0`
   * @throws VO_INVALID_USER_BUFFER The combination of `x`,
   *   `xByteStride`, `y`, `yByteStride` and
   *   `pointCount` leads to invalid memory access.
   * @throws VO_INVALID_ARGUMENT if `strokeOrder` is not positive or
   *   zero.
   */
  bool (VO_MSE_CALL *addStroke2)(voEngine engine, voEngineObject target, const float* x, size_t xByteStride, const float* y, size_t yByteStride, uint32_t pointCount, int strokeOrder);

  /**
   * Adds a digital text character with respect to its position within the
   * current input unit. If the position of the character is unknown, the
   * `x`, `y`, `width`, and `height`
   * must all be set to `0`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param character Reference to the `InputCharacter` to be added.
   * @param x The x position of the enclosing rectangle of the character.
   * @param y The y position of the enclosing rectangle of the character.
   * @param width The width of the enclosing rectangle of the character.
   * @param height The height of the enclosing rectangle of the character.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement this interface.
   * @throws VO_NO_SUCH_OBJECT The `character` reference is invalid.
   * @throws VO_INVALID_OBJECT The `character` object is not an
   *   instance of the `InputCharacter` type.
   * @throws VO_INVALID_ARGUMENT When the `InputCharacter` contains
   *   no alternate.
   * @throws VO_INVALID_ARGUMENT When the `InputCharacter` contains
   *   a space alternate and the current input unit is a word input unit.
   * @throws VO_INVALID_ARGUMENT When the `InputCharacter` contains
   *   a line feed alternate and the current input unit is a word or single
   *   line text input unit.
   * @throws VO_INVALID_ARGUMENT When `width < 0`.
   * @throws VO_INVALID_ARGUMENT When `height < 0`.
   * @throws VO_INVALID_ARGUMENT When `width` or `height`
   *    is equal to `0` and when `x`, `y`,
   *    `width`, and `height` are not all equal to
   *    `0`.
   * @throws VO_INVALID_STATE The current input unit is a character input unit
   *   and is not empty.
   *
   * @since 4.5_4
   */
  bool (VO_MSE_CALL *addCharacter)(voEngine engine, voEngineObject target, voInputCharacter character, float x, float y, float width, float height);
}
voIFloatStructuredInput;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `FloatStructuredInput` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `FloatStructuredInput`
 *   instance on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `FloatStructuredInput`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared by several types and that some types can override the
 *   property and define their own limit).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voFloatStructuredInput voCreateFloatStructuredInput(voEngine engine)
{
  return voCreateObject(engine, VO_FloatStructuredInput);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// --- IInputConsumer ----------------------------------------------------------

/**
 * Functions composing the `IInputConsumer` interface. An input
 * consumer (an object that implements this interface) is a special input that
 * consumes another input to produce any desired result. As it is itself an
 * input, it can become the source of another consumer.
 *
 * {@extends voIInput}
 */
typedef struct _voIInputConsumer
{
  /**
   * Clears this input consumer, in other words clears any produced result.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param keepMemory When `true`, tells the `target`
   *   object that it is allowed to keep its internal memory for later use.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement the `IInputConsumer` interface.
   */
  bool (VO_MSE_CALL *clear)(voEngine engine, voEngineObject target, bool keepMemory);

  /**
   * Sets the source of this input consumer object.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param source Reference to the source `EngineObject` instance.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `source` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement the `IInputConsumer` interface.
   * @throws VO_INVALID_OBJECT The `source` object does not
   *   implement the `IInput` interface.
   *
   * @note You can detach the current source from the consumer by giving a
   *   `NULL` source to this function.
   */
  bool (VO_MSE_CALL *setSource)(voEngine engine, voEngineObject target, voEngineObject source);

  /**
   * Returns the source associated with this input consumer object.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   *
   * @return A reference to the source `EngineObject` instance,
   *   which can be `NULL` or `VO_INVALID_REFERENCE` on
   *   failure.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement the `IInputConsumer` interface.
   * @throws VO_LIMIT_EXCEEDED The number of `EngineObject`
   *   instances would exceed the allowed limit (please remember that the limit
   *   can be shared by several types and that some types can override the
   *   property and define their own limit).
   */
  voEngineObject (VO_MSE_CALL *getSource)(voEngine engine, voEngineObject target);
}
voIInputConsumer;


// -- IRunnable ----------------------------------------------------------------

/**
 * Functions composing the `IRunnable` interface.
 */
typedef struct _voIRunnable
{
  /**
   * Runs this object.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param notifyProgressFunc Optional pointer to a
   *   `voNotifyProgressFunc` function that will receive
   *   progress notification events.
   * @param userParam User defined parameter to be passed through
   *   `notifyProgressFunc`.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement the `IRunnable` interface.
   * @throws VO_INVALID_CALLBACK The notification callback crashed.
   * @throws VO_INVALID_STATE The `target` object is not in a state
   *   where the `run` function can be invoked.
   * @throws VO_CANCELED The operation has been canceled.
   */
  bool (VO_MSE_CALL *run)(voEngine engine, voEngineObject target, voNotifyProgressFunc notifyProgressFunc, void* userParam);
}
voIRunnable;


// -- IInkTransmitter ----------------------------------------------------------

#if VO_USE_PRAGMA_PUSH_MACRO
#pragma push_macro("emit")
#undef emit
#endif

/**
 * Functions composing the `IInkTransmitter` interface. Represents the
 * ability for an object to emit its ink content.
 *
 * @since 4.2_2
 */
typedef struct _voIInkTransmitter
{
  /**
   * Emits the ink content to the specified receiver.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param receiver Reference to the receiver `EngineObject`
   *   instance.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement the `IInkTransmitter` interface.
   * @throws VO_NO_SUCH_OBJECT The `receiver` reference is invalid.
   * @throws VO_INVALID_OBJECT The `receiver` is not an instance of
   *   the `Input` type.
   */
  bool (VO_MSE_CALL *emit)(voEngine engine, voEngineObject target, voEngineObject receiver);

  /**
   * Returns the number of strokes this ink transmitter object has to emit.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   *
   * @return the number of strokes this ink transmitter object has to emit on
   *   success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement the `IInkTransmitter` interface.
   */
  int32_t (VO_MSE_CALL *getStrokeCount)(voEngine engine, voEngineObject target);

  /**
   * Returns the number of points in the stroke at the specified index.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param strokeIndex Index of the stroke.
   *
   * @return The number of points on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement the `IInkTransmitter` interface.
   */
  int32_t (VO_MSE_CALL *getPointCount)(voEngine engine, voEngineObject target, int32_t strokeIndex);

  /**
   * Returns a sequence of values from the X channel.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param strokeIndex Index of the stroke.
   * @param valueOffset Offset of the first value to be retrieved.
   * @param valueCount Number of values to be retrieved.
   * @param values Destination value buffer.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement the `IInkTransmitter` interface.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `strokeIndex` is out of
   *   bounds.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `valueOffset` is out of
   *   bounds.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `valueOffset+valueCount`
   *   is out of bounds.
   * @throws VO_INVALID_USER_BUFFER The `values` buffer is not
   *   writable.
   */
  bool (VO_MSE_CALL *getXValuesAsFloat)(voEngine engine, voEngineObject target, int32_t strokeIndex, int32_t valueOffset, int32_t valueCount, float* values);

  /**
   * Returns a sequence of values from the Y channel.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param strokeIndex Index of the stroke.
   * @param valueOffset Offset of the first value to be retrieved.
   * @param valueCount Number of values to be retrieved.
   * @param values Destination value buffer.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement the `IInkTransmitter` interface.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `strokeIndex` is out of
   *   bounds.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `valueOffset` is out of
   *   bounds.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `valueOffset+valueCount`
   *   is out of bounds.
   * @throws VO_INVALID_USER_BUFFER The `values` buffer is not
   *   writable.
   */
  bool (VO_MSE_CALL *getYValuesAsFloat)(voEngine engine, voEngineObject target, int32_t strokeIndex, int32_t valueOffset, int32_t valueCount, float* values);
}
voIInkTransmitter;

#ifdef VO_USE_PRAGMA_PUSH_MACRO
#pragma pop_macro("emit")
#endif

// -- HistoryManager -----------------------------------------------------------


/**
 * Reference to an instance of the `HistoryManager` type.
 *
 * {@extends voEngineObject}
 * {@implements voIHistoryManager}
 */
typedef voEngineObject voHistoryManager;

/**
 * Functions composing the `IHistoryManager` interface. This
 * interface exposes the public methods of the `HistoryManager` type.
 */
typedef struct _voIHistoryManager
{
  /**
   * Retrieves whether one can call undo, or not.
   *
   * @param engine the engine.
   * @param target the target history manager.
   *
   * @return `VO_YES` if there is something to undo,
   *         `VO_NO` if there is nothing to undo,
   *         `VO_ERR` if an error occurred.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a `voHistoryManager`.
   */
  voYesNo (VO_MSE_CALL *canUndo)(voEngine engine, voEngineObject target);

  /**
   * Undo the last action.
   *
   * @param engine the engine.
   * @param target the target history manager.
   *
   * @return true on success, otherwise false.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a `voHistoryManager`.
   */
  bool (VO_MSE_CALL *undo)(voEngine engine, voEngineObject target);

  /**
   * Retrieves whether one can call redo, or not.
   *
   * @param engine the engine.
   * @param target the target history manager.
   *
   * @return `VO_YES` if there is something to redo,
   *         `VO_NO` if there is nothing to redo,
   *         `VO_ERR` if an error occurred.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a `voHistoryManager`.
   */
  voYesNo (VO_MSE_CALL *canRedo)(voEngine engine, voEngineObject target);

  /**
   * Redo the last action reverted by undo.
   *
   * @param engine the engine.
   * @param target the target history manager.
   *
   * @return true on success, otherwise false.
   *
   *@throws VO_INVALID_OPERATION if `target` is not a `voHistoryManager`.
   */
  bool (VO_MSE_CALL *redo)(voEngine engine, voEngineObject target);

  /**
   * Indicates the start of a transaction. When `undo()` or `redo()`
   * are called, a transaction is considered as one action only.
   * Call `commit()` to end the transaction.
   * If no transaction is ongoing, every action is considered as a transaction.
   *
   * @param engine the engine.
   * @param target the target history manager.
   *
   *@return true on success, otherwise false.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a `voHistoryManager`.
   * @throws VO_INVALID_STATE if a transaction is already ongoing.
   */
  bool (VO_MSE_CALL *startTransaction)(voEngine engine, voEngineObject target);

  /**
   * Indicates the end of a transaction. The actions performed since
   * `startTransaction` was called are considered as a single one, as
   * far as `undo` and `redo()` are concerned.
   *
   * @param engine the engine.
   * @param target the target history manager.
   *
   * @return true on success, otherwise false.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a `voHistoryManager`.
   * @throws VO_INVALID_STATE if no transaction is ongoing.
   */
  bool (VO_MSE_CALL *commit)(voEngine engine, voEngineObject target);

  /**
   * Cancels an ongoing transaction.
   * Undoes actions performed since `startTransaction()` was called.
   *
   * @param engine the engine.
   * @param target the target history manager.
   *
   * @return true on success, otherwise false.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a `voHistoryManager`.
   */
  bool (VO_MSE_CALL *rollback)(voEngine engine, voEngineObject target);

  /**
   * Retrieves the current undo stack depth.
   *
   * @return the undo stack depth.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a `voHistoryManager`.
   */
  int (VO_MSE_CALL *getUndoStackDepth)(voEngine engine, voEngineObject target);

  /**
   * Retrieves the maximum undo stack depth.
   *
   * @return the maximum undo stack depth.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a `voHistoryManager`.
   */
  int (VO_MSE_CALL *getMaximumUndoStackDepth)(voEngine engine, voEngineObject target);

  /**
   * Sets the maximum undo stack depth. `0` means unlimited, use with
   * care.
   *
   * @return true on success, otherwise false.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a `voHistoryManager`.
   */
  bool (VO_MSE_CALL *setMaximumUndoStackDepth)(voEngine engine, voEngineObject target, int value);

  /**
   * Retrieves the factor applied to maximum history depth that gives the
   * threshold above which automatic purge will be triggered.
   *
   * @return the auto purge factor.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a `voHistoryManager`.
   */
  float (VO_MSE_CALL *getAutoPurgeFactor)(voEngine engine, voEngineObject target);

  /**
   * Sets the factor applied to the maximum history depth that gives the
   * threshold above which automatic purge will be triggered.
   *
   * @return true on success, otherwise false.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a `voHistoryManager`.
   */
  bool (VO_MSE_CALL *setAutoPurgeFactor)(voEngine engine, voEngineObject target, float value);
}
voIHistoryManager;

/**
 * Functions composing the `IVersionable` interface. A versionable
 * object (an object that implement this interface) has an history manager that
 * records the history of changes and allows undo / redo.
 */
typedef struct _voIVersionable
{
  /**
   * Retrieves the history manager that controls the target object's history of
   * changes.
   *
   * @param engine the engine.
   * @param target the target object.
   *
   * @return the history manager.
   *
   * @throw VO_INVALID_OPERATION if `target` does not implement `voIVersionable`.
   */
  voHistoryManager (VO_MSE_CALL *getHistoryManager)(voEngine engine, voEngineObject target);
}
voIVersionable;


// -- UserObject ---------------------------------------------------------------

/**
 * Reference to an instance of the `UserObject` type.
 *
 * {@extends voEngineObject}
 * {@implements voIUserObject}
 */
typedef voEngineObject voUserObject;

/**
 * Callback called when a user object is about to be destroyed.
 *
 * @param engine the engine.
 * @param target the user object that is about to be destroyed.
 */
typedef void (VO_MSE_CALL *voUserObjectOnDestroyCallback)(voEngine engine, voUserObject target);

/**
 * Holds the parameters required to create an instance of the
 * `UserObject` type.
 */
typedef struct _voUserObjectInitializer
{
  /**
   * An application side pointer that will be made available via the
   * `voIUserObject::getUserParam()` method.
   */
  void* userParam;

  /**
   * An application side function that will be called when the user object is
   * about to be destroyed.
   *
   * @param engine the engine.
   * @param target the user object that is about to be destroyed.
   */
  void (VO_MSE_CALL *onDestroy)(voEngine engine, voUserObject target);
}
voUserObjectInitializer;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `UserObject` type.
 *
 * @param engine the engine.
 * @param userParam the userParam that will be provided as input to
 *   `callback` function.
 * @param callback the application side function that will be called when the
 *   user object isabout to be destroyed.
 *
 * @return A reference to the newly created `UserObject` object on success,
 *   otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `UserObject`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voUserObject voCreateUserObject(voEngine engine,
                                          void* userParam,
                                          voUserObjectOnDestroyCallback callback)
{
  voUserObjectInitializer initializer = { userParam, callback };
  return voCreateObjectEx(engine, VO_UserObject, &initializer, sizeof(initializer));
}
#endif // end of: #ifndef VO_NO_FUNCTIONS

/**
 * Functions composing the `IUserObject` interface. This interface
 * exposes the public methods of the `UserObject` type.
 *
 * {@implementingTypes voUserObject}
 * @see VO_IUserObject, VO_UserObject.
 */
typedef struct _voIUserObject
{
  /**
   * Retrieves the application side pointer.
   *
   * @param engine the engine.
   * @param target the target user object.
   *
   * @return the application side pointer.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a VO_UserObject.
   */
  void* (VO_MSE_CALL *getUserParam)(voEngine engine, voEngineObject target);

  /**
   * Sets the application side pointer.
   *
   * @param engine the engine.
   * @param target the target user object.
   * @param newUserParam the new application side pointer.
   *
   * @return the old application side pointer.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a VO_UserObject.
   */
  void* (VO_MSE_CALL *setUserParam)(voEngine engine, voEngineObject target, void* newUserParam);

  /**
   * Registers implementation of the specified interface.
   *
   * @param engine the engine.
   * @param target the target user object.
   * @param interfaceId the interface identifier.
   * @param interfaceFunctions the pointer to the interface function table.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a VO_UserObject.
   * @throws VO_NO_SUCH_INTERFACE if class corresponding to `interfaceId` is not an interface.
   * @throws VO_INVALID_ARGUMENT if `interfaceFunctions` is NULL.
   * @throws VO_INVALID_ARGUMENT if the interface is not implementable by user
   *          objects. The documentation of the interface should state it.
   */
  bool (VO_MSE_CALL *registerInterface)(voEngine engine, voEngineObject target,
                                        voTypeId interfaceId,
                                        const void* interfaceFunctions);
}
voIUserObject;


#endif // end of: #ifndef VO_FUNCTIONS_ONLY

#endif // end of: #ifndef C_MYSCRIPTENGINE_H
