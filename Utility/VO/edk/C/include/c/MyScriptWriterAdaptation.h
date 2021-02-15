#ifndef C_MYSCRIPTWRITERADAPTATION_H
#define C_MYSCRIPTWRITERADAPTATION_H 0x06010000
/**
 * @file c/MyScriptWriterAdaptation.h
 * Native interface to the MyScriptWriterAdaptation service.
 */

#include "MyScriptEngine.h"
#include "MyScriptHWR.h"


// -- types and interfaces -----------------------------------------------------

/**
 * Lists the MyScriptWriterAdaptation types.
 */
enum VO_WRITERADAPTATION_T
{
  /**
   * Identifier of the `WriterAdaptationCollector` type.
   * @see voWriterAdaptationCollector.
   */
  VO_WriterAdaptationCollector = 7000,

  /**
   * Identifier of the `WriterAdaptationProfile` type.
   * @see voWriterAdaptationProfile.
   */
  VO_WriterAdaptationProfile,

  /**
   * Identifier of the `WriterAdaptationTrainer` type.
   * @see voWriterAdaptationTrainer.
   */
  VO_WriterAdaptationTrainer,
};

/**
 * Lists the MyScriptWriterAdaptation interfaces.
 */
enum VO_WRITERADAPTATION_I
{
  /**
   * Identifier of the `IWriterAdaptationCollector` interface.
   * @see voIWriterAdaptationProfile.
   */
  VO_IWriterAdaptationCollector = 7005,
};


/**
 * Reference to an instance of the `WriterAdaptationCollector` type.
 *
 * {@extends voEngineObject}
 * {@implements voIAttachTarget}
 *
 * @see voStoreObject, voLoadObject.
 */
typedef voEngineObject voWriterAdaptationCollector;

/**
 * Functions composing the `IWriterAdaptationCollector` interface. This
 * interface exposes the public methods of the `WriterAdaptationCollector` type.
 *
 * {@implementingTypes voWriterAdaptationCollector}
 * @see VO_IWriterAdaptationCollector, VO_WriterAdaptationCollector.
 */
typedef struct _voIWriterAdaptationCollector
{
  /**
   * Commits the samples collected during the last recognition to the attached
   * profile.
   *
   * @param engine the engine.
   * @param target the target writer adaptation collector.
   *
   * @return `true`on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `WriterAdaptationCollector` instance.
   * @throws VO_INVALID_STATE The target writer adaptation collector has no
   *   attached profile.
   */
  bool (VO_MSE_CALL *commit)(voEngine engine, voWriterAdaptationCollector target);
}
voIWriterAdaptationCollector;

/**
 * Reference to an instance of the `WriterAdaptationProfile` type.
 * Instances of the `WriterAdaptationProfile` type are serializable.
 *
 * {@extends voEngineObject}
 *
 * @see voStoreObject, voLoadObject.
 */
typedef voEngineObject voWriterAdaptationProfile;

/**
 * Reference to an instance of the `WriterAdaptationTrainer` type.
 *
 * {@extends voEngineObject}
 * {@implements voIAttachTarget}
 * {@implements voIRunnable}
 *
 * @see voStoreObject, voLoadObject.
 */
typedef voEngineObject voWriterAdaptationTrainer;


#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `WriterAdaptationProfile` type.
 *
 * @param engine the engine.
 *
 * @return A reference to the newly created `WriterAdaptationProfile` object
 *   on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `WriterAdaptationProfile`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voWriterAdaptationProfile voCreateWriterAdaptationProfile(voEngine engine)
{
  return voCreateObject(engine, VO_WriterAdaptationProfile);
}

/**
 * Creates an instance of the `WriterAdaptationCollector` type.
 *
 * @param engine the engine.
 *
 * @return A reference to the newly created `WriterAdaptationCollector` object
 *   on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `WriterAdaptationCollector`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voWriterAdaptationCollector voCreateWriterAdaptationCollector(voEngine engine)
{
  return voCreateObject(engine, VO_WriterAdaptationCollector);
}

/**
 * Creates an instance of the `WriterAdaptationTrainer` type.
 *
 * @param engine the engine.
 *
 * @return A reference to the newly created `WriterAdaptationTrainer` object
 *   on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `WriterAdaptationTrainer`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voWriterAdaptationTrainer voCreateWriterAdaptationTrainer(voEngine engine)
{
  return voCreateObject(engine, VO_WriterAdaptationTrainer);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS

#endif // end of: #ifndef C_MYSCRIPTWRITERADAPTATION_H
