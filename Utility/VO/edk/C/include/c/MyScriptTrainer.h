#ifndef C_MYSCRIPTTRAINER_H
#define C_MYSCRIPTTRAINER_H 0x06010000
/**
 * @file c/MyScriptTrainer.h
 * Native interface to the MyScript Trainer service.
 */

#include "MyScriptEngine.h"
#include "MyScriptHWR.h"


// -- types and interfaces -----------------------------------------------------

/**
 * Lists the MyScript Trainer types.
 */
enum VO_TRAINER_T
{
  /**
   * `TrainingSet` type.
   *
   * @see voTrainingSet.
   */
  VO_TrainingSet = 1500,
  /**
   * `TrainingSetExtractor` type.
   *
   * @see voTrainingSetExtractor.
   */
  VO_TrainingSetExtractor,
  /**
   * `TrainingInformationSet` type.
   *
   * @see voTrainingInformationSet.
   */
  VO_TrainingInformationSet,
  /**
   * `AdvancedTrainer` type.
   *
   * @see voAdvancedTrainer.
   */
  VO_AdvancedTrainer,
};

/**
 * Lists the MyScript Trainer interfaces.
 */
enum VO_TRAINER_I
{
  /**
   * `ITrainingResultProvider` interface type.
   *
   * @see voITrainingResultProvider.
   */
  VO_ITrainingResultProvider = 402,

  /**
   * `ITrainingSet` interface type.
   *
   * @see voITrainingSet.
   */
  VO_ITrainingSet = 1520,
  /**
   * `ITrainingSetExtractor` interface type.
   *
   * @see voITrainingSetExtractor
   */
  VO_ITrainingSetExtractor,
};


/**
 * Reference to an instance of the `TrainingSet` type. Instances of
 * the `TrainingSet` type are serializable.
 *
 * {@extends voEngineObject}
 * {@implements voITrainingSet}
 *
 * @see voStoreObject, voLoadObject.
 */
typedef voEngineObject voTrainingSet;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `TrainingSet` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `TrainingSet`
 *   object on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `TrainingSet`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voTrainingSet voCreateTrainingSet(voEngine engine)
{
  return voCreateObject(engine, VO_TrainingSet);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS

/**
 * Functions composing the `ITrainingSet` interface. This interface
 * exposes the public methods of the `TrainingSet` type.
 *
 * {@implementingTypes voTrainingSet}
 * @see VO_ITrainingSet, VO_TrainingSet.
 */
typedef struct _voITrainingSet
{
  /**
   * Returns the number of samples within the target `TrainingSet`
   * instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `TrainingSet` instance.
   *
   * @return The number of samples on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `TrainingSet` instance.
   */
  int64_t (VO_MSE_CALL *getSampleCount)(voEngine engine, voTrainingSet target);

  /**
   * Adds a sample to the target `TrainingSet` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `TrainingSet` instance.
   * @param sampleInk Reference to the `Input` instance that
   *   contains the ink of the sample.
   * @param charset Reference to the `Charset` instance to be used
   *   when decoding the label.
   * @param label Label of the sample.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `TrainingSet` instance.
   * @throws VO_NO_SUCH_OBJECT The `sampleInk` reference is
   *   invalid.
   * @throws VO_INVALID_OPERATION The `sampleInk` reference is not
   *   a reference to an `Input` instance.
   * @throws VO_INVALID_USER_BUFFER The `label` string is not
   *   readable.
   * @throws VO_INVALID_USER_BUFFER The `label->bytes` member is
   *   not readable.
   * @throws VO_INVALID_ARGUMENT The `label` is empty. The
   *   trainer needs you to provide the expected recognition result. You
   *   can't tell it: "I want you not to recognize this input ink".
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is
   *   `NULL` and no default charset was set.
   * @throws VO_INVALID_OPERATION The `charset` reference is not a
   *   reference to a `Charset` instance.
   */
  bool (VO_MSE_CALL *addSample)(voEngine engine, voTrainingSet target, voInput sampleInk, voCharset charset, const voString* label);

  /**
   * Removes a sample from the target `TrainingSet` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `TrainingSet` instance.
   * @param sampleIndex Index of the sample to be removed.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `TrainingSet` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `sampleIndex` value is out
   *   of bounds.
   */
  bool (VO_MSE_CALL *removeSample)(voEngine engine, voTrainingSet target, int64_t sampleIndex);

  /**
   * Returns the ink of the sample at the specified index as an object that
   * implements the `voIInkTransmitter` interface.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `TrainingSet` instance.
   * @param sampleIndex Index of the sample to remove.
   *
   * @return An object that can emit the ink of the sample on success,
   *   otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `TrainingSet` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `sampleIndex` value is out
   *   of bounds.
   * @throws VO_LIMIT_EXCEEDED The number of `EngineObject`
   *   instances would exceed the allowed limit (please remember that the
   *   limit can be shared by multiple types).
   *
   * @see voIInkTransmitter.
   */
  voEngineObject (VO_MSE_CALL *getSampleInk)(voEngine engine, voTrainingSet target, int64_t sampleIndex);

  /**
   * Returns the label of the sample at the specified index.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `TrainingSet` instance.
   * @param sampleIndex Index of the sample to be removed.
   * @param charset Reference to a `Charset` instance to be used
   *   when encoding of the label.
   * @param label String recipient for the label.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `TrainingSet` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `sampleIndex` value is out
   *   of bounds.
   * @throws VO_INVALID_USER_BUFFER The string recipient is not readable or
   *   writable.
   * @throws VO_INVALID_USER_BUFFER The `bytes` member of the
   *   string recipient is not writable.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is
   *   `NULL` and no default charset was set.
   * @throws VO_INVALID_OPERATION The `charset` reference is not a
   *   reference to a `Charset` instance.
   */
  bool (VO_MSE_CALL *getSampleLabel)(voEngine engine, voTrainingSet target, int64_t sampleIndex, voCharset charset, voString* label);
}
voITrainingSet;


/**
 * Reference to an instance of the `TrainingSetExtractor` type.
 * A `TrainingSetExtractor` matches the source ink against a sequence
 * of characters and/or a set of sentences to produce a
 * `TrainingSet`.
 *
 * <p>Instances of the TrainingSetExtractor type are serializable, however
 * only the set of characters and set of sentences are serialized.</p>
 *
 * <p>Usage:<ul><li>Set up the `TrainingSetExtractor` by either
 * loading it from an external storage or by creating with the help of the
 * `voCreateTrainingSetExtractor()` function</li><li>Define the
 * characters and sentences you want to collect with the help of the
 * `addSentence` and `insertCharacter` functions</li><li>
 * Attach an `AlphabetKnowledge` resource using the
 * `attach()` function from the `IAttachTarget` interface
 * </li><li>Set the input source ink via `setSource()` from the
 * `IInputConsumer` interface</li><li>Run the process via
 * `run()` from the `IRunnable` interface</li></ul>After
 * this, the resulting `TrainingSet` will be available via the
 * `getTrainingSet()` function.</p>
 *
 * <p>Note that the input can be separated into blocks by using a
 * `StructuredInput` object in which each block corresponds to a
 * separate `VO_MULTI_LINE_TEXT` input unit. Usually, each page will
 * be sent in a separate block which can save a significant amount of memory and
 * time. However, please note that the sequence of characters or a sentence
 * can't be matched if it overlaps two subsequent blocks.</p>
 *
 * {@extends voEngineObject}
 * {@implements voITrainingSetExtractor, voIAttachTarget, voIInputConsumer, voIRunnable}
 *
 * @see voStoreObject, voLoadObject, voCreateTrainingSetExtractor, voAlphabetKnowledge, voStructuredInput.
 */
typedef voEngineObject voTrainingSetExtractor;

/**
 * Lists the possible values of the `type` member of the
 * `voCharacterMatchingModel` structure.
 *
 * @see voCharacterMatchingModel.
 */
enum VO_CHARACTER_MATCHING_MODEL_TYPE
{
  /**
   * Type of `CharacterMatchingModel` where the set of characters
   * will be matched as an alphabet, which means the user has to write them all
   * and in the same order as defined. For this model the parameter
   * `n` represents the maximum allowed number of consecutive
   * missing characters in the input. The parameter `n` must be
   * between 0 and 10, inclusive.

   * @see voCharacterMatchingModel.
   */
  VO_MATCHING_MODEL_ALPHABET,
  /**
   * @see voCharacterMatchingModel.
   */
  VO_MATCHING_MODEL_CHARACTER
};

/**
 * Represents the matching model for characters in the set of characters
 * defined in a `voTrainingSetExtractor`.
 */
typedef struct _voCharacterMatchingModel
{
  /**
   * Type of this matching model, either
   * `VO_MATCHING_MODEL_ALPHABET` or
   * `VO_MATCHING_MODEL_CHARACTER`.
   *
   * @see voCharacterMatchingModelType
   */
  voId type;

  /**
   * Parameter of this matching model: entirely depends on the
   * `type` of matching model.
   *
   * @see voCharacterMatchingModelType
   */
  uint32_t n;
}
voCharacterMatchingModel;

/**
 * {@propertySet TrainingSetExtractor}
 */
enum VO_TRAININGSETEXTRACTOR_PROP
{
  /**
   * Represents the matching model for the characters in the set of characters
   * of the target `voTrainingSetExtractor`.
   *
   * {@property voCharacterMatchingModel}
   */
  VO_CHARACTER_MATCHING_MODEL
};

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `TrainingSetExtractor` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `TrainingSetExtractor`
 *   object on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `TrainingSetExtractor`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voTrainingSetExtractor voCreateTrainingSetExtractor(voEngine engine)
{
  return voCreateObject(engine, VO_TrainingSetExtractor);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS

/**
 * Statistics for the `TrainingSetExtractor`.
 */
typedef struct _voTrainingSetExtractorStats
{
  /**
   * Version of this structure, must be 1.
   */
  uint32_t structVersion;

  /**
   * The rate of matched characters against the defined sequence of
   * characters.
   */
  float matchedCharacterRate;

  /**
   * The rate of matched sentences against the defined set of sentences.
   */
  float matchedSentenceRate;
}
voTrainingSetExtractorStats;

/**
 * Statistics for matches in the `voTrainingSetExtractor`.
 */
typedef struct _voTrainingSetExtractorMatchStats
{
  /**
   * Version of this structure, must be 1.
   */
  uint32_t structVersion;

  /**
   * The match score.
   */
  float matchScore;

  /**
   * The index of the first sample extracted from this match inside the
   * resulting `TrainingSet`.
   */
  int64_t firstExtractedSample;

  /**
   * The number of samples extracted from this match inside the resulting
   * `TrainingSet`.
   */
  int32_t extractedSampleCount;
}
voTrainingSetExtractorMatchStats;

/**
 * Functions composing the `ITrainingSetExtractor` interface. This
 * interface exposes the public methods of the `TrainingSetExtractor`
 * type.
 *
 * {@implementingTypes voTrainingSetExtractor}
 * @see VO_ITrainingSetExtractor, VO_TrainingSetExtractor.
 */
typedef struct _voITrainingSetExtractor
{
  /**
   * Returns the number of characters in the set of characters that will be
   * matched.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `TrainingSetExtractor` instance.
   *
   * @return The number of characters on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `TrainingSetExtractor` instance.
   */
  int32_t (VO_MSE_CALL *getCharacterCount)(voEngine engine, voTrainingSetExtractor target);

  /**
   * Returns the character at the specified index.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `TrainingSetExtractor` instance.
   * @param index Index of the character to be retrieved.
   * @param charset Reference to the `Charset` instance to be used
   *   when encoding the character string.
   * @param character String recipient for the character string.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `TrainingSetExtractor` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_INVALID_USER_BUFFER The string recipient is not readable or
   *   writable.
   * @throws VO_INVALID_USER_BUFFER The `bytes` member of the
   *   string recipient is not writable.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is
   *   `NULL` and no default charset was set.
   * @throws VO_INVALID_OPERATION The `charset` reference is not a
   *   reference to a `Charset` instance.
   */
  bool (VO_MSE_CALL *getCharacter)(voEngine engine, voTrainingSetExtractor target, int32_t index, voCharset charset, voString* character);

  /**
   * Inserts a new character at the specified index.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `TrainingSetExtractor` instance.
   * @param index Index at which the new character will be inserted. Any
   *   existing characters from this index to the end are shifted up.
   * @param charset Reference to the `Charset` instance to be used
   *   when decoding the character string.
   * @param character The character string.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `TrainingSetExtractor` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is
   *   `NULL` and no default charset was set.
   * @throws VO_INVALID_OPERATION The `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER The string recipient is not readable.
   * @throws VO_INVALID_USER_BUFFER The `bytes` member of the
   *   string recipient is not readable.
   * @throws VO_INVALID_ARGUMENT The string recipient is empty.
   * @throws VO_INVALID_STATE The `character` has already been
   *   inserted in the target `TrainingSetExtractor`.
   */
  bool (VO_MSE_CALL *insertCharacter)(voEngine engine, voTrainingSetExtractor target, int32_t index, voCharset charset, const voString* character);

  /**
   * Removes the character at the specified index.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `TrainingSetExtractor` instance.
   * @param index Index of the character to remove. Characters after it are
   *   shifted down.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `TrainingSetExtractor` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  bool (VO_MSE_CALL *removeCharacter)(voEngine engine, voTrainingSetExtractor target, int32_t index);

  /**
   * Returns the number of sentences.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `TrainingSetExtractor` instance.
   *
   * @return The number of sentences on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `TrainingSetExtractor` instance.
   */
  int32_t (VO_MSE_CALL *getSentenceCount)(voEngine engine, voTrainingSetExtractor target);

  /**
   * Returns the sentence at the specified index.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `TrainingSetExtractor` instance.
   * @param index Index of the sentence to be retrieved.
   * @param charset Reference to the `Charset` instance to be used
   *   when encoding the sentence string.
   * @param character String recipient for the sentence string.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `TrainingSetExtractor` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_INVALID_USER_BUFFER The string recipient is not readable or
   *   writable.
   * @throws VO_INVALID_USER_BUFFER The `bytes` member of the
   *   string recipient is not writable.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is
   *   `NULL` and no default charset was set.
   * @throws VO_INVALID_OPERATION The `charset` reference is not a
   *   reference to a `Charset` instance.
   */
  bool (VO_MSE_CALL *getSentence)(voEngine engine, voTrainingSetExtractor target, int32_t index, voCharset charset, voString* sentence);

  /**
   * Adds a sentence.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `TrainingSetExtractor` instance.
   * @param charset Reference to the `Charset` instance to be used
   *   when decoding the sentence string.
   * @param sentence The sentence string.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `TrainingSetExtractor` instance.
   * @throws VO_INVALID_USER_BUFFER The string recipient is not readable.
   * @throws VO_INVALID_USER_BUFFER The `bytes` member of the
   *   string recipient is not readable.
   * @throws VO_INVALID_ARGUMENT The string recipient is empty.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is
   *   `NULL` and no default charset was set.
   * @throws VO_INVALID_OPERATION The `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_OUT_OF_MEMORY Not enough memory to add the new sentence.
   */
  bool (VO_MSE_CALL *addSentence)(voEngine engine, voTrainingSetExtractor target, voCharset charset, const voString* sentence);

  /**
   * Removes the sentence at the specified index.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `TrainingSetExtractor` instance.
   * @param index Index of the sentence to be removed. Sentences after it are
   *   shifted down.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `TrainingSetExtractor` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  bool (VO_MSE_CALL *removeSentence)(voEngine engine, voTrainingSetExtractor target, int32_t index);

  /**
   * Returns the resulting TrainingSet.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `TrainingSetExtractor` instance.
   *
   * @return A `TrainingSet` instance on success, otherwise
   *   `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `TrainingSetExtractor` instance.
   * @throws VO_INVALID_STATE No call to `run()` has been
   *   completed successfully.
   * @throws VO_LIMIT_EXCEEDED The number of `TrainingSet`
   *   instances would exceed the allowed limit (please remember that the
   *   limit can be shared among several types).
   */
  voTrainingSet (VO_MSE_CALL *getTrainingSet)(voEngine engine, voTrainingSetExtractor target);

  /**
   * Returns global statistics about the extraction process.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `TrainingSetExtractor` instance.
   * @param statistics Recipient for the statistics
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `TrainingSetExtractor` instance.
   * @throws VO_INVALID_USER_BUFFER The `statistics` recipient is
   *   not writable.
   * @throws VO_INVALID_ARGUMENT The `structVersion` member of the
   *   `statistics` recipient is not recognized.
   * @throws VO_INVALID_STATE The `target`
   *   `TrainingSetExtractor` has not been run successfully.
   */
  bool (VO_MSE_CALL *getStatistics)(voEngine engine, voTrainingSetExtractor target, voTrainingSetExtractorStats* statistics);

  /**
   * Returns the number of matches that have been performed by the extraction
   * process.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `TrainingSetExtractor` instance.
   *
   * @return The number of matches on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `TrainingSetExtractor` instance.
   * @throws VO_INVALID_STATE The `target`
   *   `TrainingSetExtractor` has not been run successfully.
   */
  int32_t (VO_MSE_CALL *getMatchCount)(voEngine engine, voTrainingSetExtractor target);

  /**
   * Returns statistics about one specific match from the extraction process.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `TrainingSetExtractor` instance.
   * @param matchIndex Index of the match. Must be between `0` and
   *   `getMatchCount() - 1`.
   * @param matchStatistics Recipient for the match statistics.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `TrainingSetExtractor` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `matchIndex` is out of
   *   bounds.
   * @throws VO_INVALID_USER_BUFFER The `matchStatistics` recipient
   *   is not writable.
   * @throws VO_INVALID_ARGUMENT The `structVersion` member of the
   *   `matchStatistics` recipient is not recognized.
   * @throws VO_INVALID_STATE The `target`
   *   `TrainingSetExtractor` has not been run successfully.
   */
  bool (VO_MSE_CALL *getMatchStatistics)(voEngine engine, voTrainingSetExtractor target, int32_t matchIndex, voTrainingSetExtractorMatchStats* matchStatistics);
}
voITrainingSetExtractor;


/**
 * A `TrainingInformationSet` is actually a special type of resource
 * that contains specific linguistic information that the
 * `AdvancedTrainer` needs to have in order to perform accurate
 * training. Therefore, training cannot be carried out without it.
 *
 * {@extends voResource}
 *
 * @see voAdvancedTrainer
 */
typedef voResource voTrainingInformationSet;


/**
 * Reference to an instance of the `AdvancedTrainer` type. The
 * `AdvancedTrainer` is a runnable object that can perform a training
 * process: by this, we mean it takes as input the samples the writer has
 * written and the labels of the characters/words/sentences presented as the
 * text to be copied, and it then processes that information to modify an
 * existing `AlphabetKnowledge` resource. This resource is then used
 * to recognize ink from that writer with greater accuracy.
 *
 * <p>In order to get the `AdvancedTrainer` ready to perform
 * handwriting adaptation to a specific writer you first have to attach the
 * following objects to it: the `TrainingSet` that describes the
 * handwriting profile of your writer; the `AlphabetKnowledge` that
 * you want to adapt; the `TrainingInformationSet` of the target
 * language. Moreover, when adapting a `CursiveAlphabetKnowledge`,
 * you should also attach `LinguisticKnowledge` resources that best
 * define your application's linguistic context (use the lk-text.res resource for
 * the corresponding language if you don't know).</p>
 *
 * <p>Finally, call `run()` to perform the training process
 * and then `getResult()` to get the adapted
 * `AlphabetKnowledge`.</p>
 *
 * {@extends voEngineObject}
 * {@implements voIAttachTarget, voIRunnable, voITrainingResultProvider}
 *
 * @see voTrainingSet, voAlphabetKnowledge, voTrainingInformationSet, voLinguisticKnowledge
 */
typedef voEngineObject voAdvancedTrainer;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `AdvancedTrainer` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `AdvancedTrainer`
 *   object on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `AdvancedTrainer`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voAdvancedTrainer voCreateAdvancedTrainer(voEngine engine)
{
  return voCreateObject(engine, VO_AdvancedTrainer);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -------------------------- ITrainingResultProvider --------------------------

/**
 * Functions composing the `ITrainingResultProvider` interface.
 *
 * {@implementingTypes voAdvancedTrainer}
 */
typedef struct _voITrainingResultProvider
{
  /**
   * Returns the training result associated with the target object.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   *
   * @return The trained resource on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement the `ITrainingResultProvider` interface.
   * @throws VO_INVALID_STATE The object is not in a state where the
   *   result is available.
   * @throws VO_LIMIT_EXCEEDED The number of `Resource` instances
   *   would exceed the allowed limit.
   */
  voResource (VO_MSE_CALL *getResult)(voEngine engine, voAdvancedTrainer target);
}
voITrainingResultProvider;

#endif // end of: #ifndef C_MYSCRIPTTRAINER_H
