#ifndef C_MYSCRIPTHWR_H
#define C_MYSCRIPTHWR_H 0x06010000
/**
 * @file c/MyScriptHWR.h
 * Native interface to the MyScript HandWriting Recognition (HWR) service.
 */

#include "MyScriptEngine.h"


// -- error codes --------------------------------------------------------------

/**
 * Lists the MyScript HWR errors.
 */
enum VO_HWR_ERR
{
  /**
   * Unable to complete the requested operation because an
   * `AlphabetKnowledge` resource is missing. This does not
   * necessarily mean that no `AlphabetKnowledge` resource is
   * attached. For example, if you fill a `StructuredInput` with
   * `VO_MULTI_LINE_TEXT` input units and you attach only an
   * `IsolatedAlphabetKnowledge` you will get this error.
   *
   * @see voAlphabetKnowledge.
   */
  VO_MISSING_ALPHABET_KNOWLEDGE = VO_INVALID_STATE | (2 << 16),
  /**
   * Unable to complete the requested operation because the input consumer
   * source is missing.
   *
   * @see voIInputConsumer.
   */
  VO_MISSING_SOURCE,
  /**
   * One of the character input units within an input exceeds the stroke limit
   * fixed by the recognizer (please note that this limit may change from one
   * recognizer to another).
   */
  VO_CHAR_STROKE_LIMIT_EXCEEDED,
  /**
   * Parse error in a regular expression: sub-expression imbalance. This means
   * that the number of open and close parentheses does not match.
   *
   * @see voLexicalUnit.
   */
  VO_REGEX_SUBEXP_IMBALANCE = VO_INVALID_ARGUMENT | (5 << 16),
  /**
   * Parse error in a regular expression: unmatched open set. This means that
   * an open square bracket exists without the matching close square bracket.
   *
   * @see voLexicalUnit.
   */
  VO_REGEX_UNMATCHED_OPEN_SET,
  /**
   * Parse error in a regular expression: unmatched open reference. This means
   * that an open brace exists without the matching close brace.
   *
   * @see voLexicalUnit.
   */
  VO_REGEX_UNMATCHED_OPEN_REF,
  /**
   * Parse error in a regular expression: trailing escape. This means that a
   * back slash was found at the end of the expression (without the escaped
   * character).
   *
   * @see voLexicalUnit.
   */
  VO_REGEX_TRAILING_ESCAPE,
  /**
   * Parse error in a regular expression: invalid character. This means that an
   * invalid character was found (a character that has no mapping).
   *
   * @see voLexicalUnit.
   */
  VO_REGEX_INVALID_CHARACTER,
  /**
   * Parse error in a regular expression: invalid reference. This means that a
   * reference was found but the corresponding definition does not exist.
   *
   * @see voLexicalUnit.
   */
  VO_REGEX_INVALID_REFERENCE,
  /**
   * Parse error in a regular expression: unmatched close set. This means that a
   * close square bracket exists without the matching open square bracket.
   *
   * @see voLexicalUnit.
   *
   * @since 4.2_2
   */
  VO_REGEX_UNMATCHED_CLOSE_SET,
  /**
   * Parse error in a regular expression: unmatched close reference. This means
   * that a close brace exists without the matching open brace.
   *
   * @see voLexicalUnit.
   *
   * @since 4.2_2
   */
  VO_REGEX_UNMATCHED_CLOSE_REF,
  /**
   * Parse error in a regular expression: unescaped operator. This means that a
   * regular expression operator was found when a normal character was expected.
   * Escape it using the backslash character if you meant it literally.
   *
   * @see voLexicalUnit.
   *
   * @since 4.2_2
   */
  VO_REGEX_UNESCAPED_OPERATOR,

  /**
   * An input with too many strokes or too many input units was sent to the
   * target `HandwritingContext`.
   *
   * @see voHandwritingContext.
   *
   * @since 4.2_2
   */
  VO_INPUT_LIMIT_EXCEEDED
};


// -- types and interfaces -----------------------------------------------------

/**
 * Lists the MyScript HWR types.
 */
enum VO_HWR_T
{
  /**
   * `HandwritingContext` type.
   *
   * @see voHandwritingContext.
   */
  VO_HandwritingContext = 300,
  /**
   * `Recognizer` type.
   *
   * @see voRecognizer.
   */
  VO_Recognizer,
  /**
   * `StructuredInputRecognizer` type.
   *
   * @see voStructuredInputRecognizer.
   */
  VO_StructuredInputRecognizer = 303,

  /**
   * `TextRecognizer` type.
   *
   * @see voTextRecognizer.
   */
  VO_TextRecognizer,

  /**
   * `DigitalTextMatcher` type.
   *
   * @see voDigitalTextMatcher.
   */
  VO_DigitalTextMatcher = VO_TextRecognizer + 2,

  /**
   * `Resource` type.
   *
   * @see voResource.
   */
  VO_Resource,
  /**
   * `AlphabetKnowledge` type.
   *
   * @see voAlphabetKnowledge.
   */
  VO_AlphabetKnowledge,
  /**
   * `CursiveAlphabetKnowledge` type.
   *
   * @see voCursiveAlphabetKnowledge.
   */
  VO_CursiveAlphabetKnowledge,
  /**
   * `HandPrintedAlphabetKnowledge` type.
   *
   * @see voHandPrintedAlphabetKnowledge.
   */
  VO_HandPrintedAlphabetKnowledge,
  /**
   * `IsolatedAlphabetKnowledge` type.
   *
   * @see voIsolatedAlphabetKnowledge.
   */
  VO_IsolatedAlphabetKnowledge,
  /**
   * `LinguisticKnowledge` type.
   *
   * @see voLinguisticKnowledge.
   */
  VO_LinguisticKnowledge,
  /**
   * `Vocabulary` type.
   *
   * @see voVocabulary.
   */
  VO_Vocabulary,
  /**
   * `LexicalUnit` type.
   *
   * @see voLexicalUnit.
   */
  VO_LexicalUnit,
  /**
   * `Lexicon` type.
   *
   * @see voLexicon.
   */
  VO_Lexicon,
  /**
   * `Grammar` type.
   *
   * @see voGrammar.
   */
  VO_Grammar = 317,
  /**
   * `SubsetKnowledge` type.
   *
   * @see voSubsetKnowledge.
   */
  VO_SubsetKnowledge,
  /**
   * `Archive` type.
   *
   * @see voArchive.
   */
  VO_Archive,

  /**
   * `WordIterator` type.
   *
   * @see voWordIterator.
   */
  VO_WordIterator,

  /**
   * `RecognitionResult` type.
   *
   * @see voRecognitionResult.
   */
  VO_RecognitionResult,
  /**
   * `CandidateIterator` type.
   *
   * @see voCandidateIterator.
   */
  VO_CandidateIterator,
  /**
   * `SegmentIterator` type.
   *
   * @see voSegmentIterator.
   */
  VO_SegmentIterator,

  /**
   * `DigitalInkTagger` type.
   * @see voDigitalInkTagger
   * @since 4.4_4
   */
  VO_DigitalInkTagger,
  /**
   * `TagList` type.
   * @see voTagList
   * @since 4.4_4
   */
  VO_TagList,
  /**
   * `TagIterator` type.
   * @see voTagIterator
   * @since 4.4_4
   */
  VO_TagIterator
};


/**
 * Lists the MyScript HWR interfaces.
 */
enum VO_HWR_I
{
  /**
   * `ILexicalUnit` interface type.
   *
   * @see voILexicalUnit.
   */
  VO_ILexicalUnit = 350,
  /**
   * `ILexicon` interface type.
   *
   * @see voILexicon.
   */
  VO_ILexicon,
  /**
   * `ISubsetKnowledge` interface type.
   *
   * @see voISubsetKnowledge.
   */
  VO_ISubsetKnowledge,
  /**
   * `IWordIterator` interface type.
   *
   * @see voIWordIterator.
   */
  VO_IWordIterator,
  /**
   * `IRecognitionResult` interface type.
   *
   * @see voIRecognitionResult.
   */
  VO_IRecognitionResult,
  /**
   * `ICandidateIterator` interface type.
   *
   * @see voICandidateIterator.
   */
  VO_ICandidateIterator,
  /**
   * `ISegmentIterator` interface type.
   *
   * @see voISegmentIterator.
   */
  VO_ISegmentIterator,

  /**
   * `IDigitalTextMatcher` interface type.
   *
   * @see voIDigitalTextMatcher.
   */
  VO_IDigitalTextMatcher = VO_ISegmentIterator + 2,

  /**
   * `IAlphabet` interface type.
   *
   * @see voIAlphabet.
   */
  VO_IAlphabet = 400,

  /**
   * `IRecognitionResultProvider` interface type.
   *
   * @see voIRecognitionResultProvider.
   */
  VO_IRecognitionResultProvider,

  /**
   * `IDigitalInkTagger` interface type.
   * @see voIDigitalInkTagger
   * @since 4.4_4
   */
  VO_IDigitalInkTagger = VO_IRecognitionResultProvider + 2,
  /**
   * `ITagList` interface type.
   * @see voITagList
   * @since 4.4_4
   */
  VO_ITagList,
  /**
   * `ITagIterator` interface type.
   * @see voITagIterator
   * @since 4.4_4
   */
  VO_ITagIterator
};


// -- HanwritingContext --------------------------------------------------------

/**
 * Reference to an instance of the `HandwritingContext` type.
 *
 * {@extends voEngineObject}
 * {@subTypes voRecognizer, voTrainer}
 * {@implements voIAttachTarget, voIInputConsumer}
 * {@typeProperties VO_HANDWRITINGCONTEXT_TPROP}
 * {@properties VO_HANDWRITINGCONTEXT_PROP}
 *
 * @see VO_HandwritingContext, VO_HANDWRITINGCONTEXT_TPROP.
 * @see voRecognizer, voTrainer.
 */
typedef voEngineObject voHandwritingContext;

/**
 * {@typePropertySet HandwritingContext}
 */
enum VO_HANDWRITINGCONTEXT_TPROP
{
  /**
   * Represents the maximum number of `HandwritingContext` instances
   * that can exist at the same time in the user side of a MyScript enabled
   * application.
   * The special value zero means no limit. Other values are adjusted to the
   * next multiple of 16. A value under the current count is permitted and will
   * constrain future creations.
   *
   * {@property uint32_t}
   */
  VO_USER_HWCTX_LIMIT = VO_USER_OBJ_LIMIT,
  /**
   * Gives the number of `HandwritingContext` instances that
   * currently exist in the user side of a MyScript enabled application.
   *
   * {@property read-only uint32_t}
   */
  VO_USER_HWCTX_COUNT = VO_USER_OBJ_COUNT
};

/**
 * Lists the speed versus quality compromise special values
 */
enum VO_SPEED_QUALITY_COMPROMISE_VALUE
{
  /**
   * Maximize speed against quality.
   */
  VO_MAXIMIZE_SPEED = 0,
  /**
   * Maximize quality against speed.
   */
  VO_MAXIMIZE_QUALITY = 255
};

/**
 * {@propertySet HandwritingContext}
 */
enum VO_HANDWRITINGCONTEXT_PROP
{
  /**
   * Adjusts the treatment optimization compromise between speed and quality.
   *
   * {@property uint8_t}
   *
   * @note you can use `VO_MAXIMIZE_SPEED`,
   * `VO_MAXIMIZE_QUALITY`, or any value between 0 and 255.
   * However, there are less than 255 levels and the value will be adjusted to
   * the closest available value.
   */
  VO_SPEED_QUALITY_COMPROMISE = (VO_HandwritingContext << 16)
};


// -- Recognizer ---------------------------------------------------------------

/**
 * Reference to an instance of the `Recognizer` type.
 *
 * {@extends voHandwritingContext}
 * {@subTypes voStructuredInputRecognizer}
 * {@properties VO_RECOGNIZER_PROP}
 *
 * @see VO_Recognizer.
 * @see voStructuredInputRecognizer,
 *   voDigitalTextMatcher.
 */
typedef voHandwritingContext voRecognizer;

/**
 * Lists the casing scheme values.
 *
 * @since 4.5_5
 */
enum VO_CASING_SCHEME_VALUE
{
  /**
   * The recognition process applies conservative casing rules: only the strict
   * content of a `Vocabulary` can be recognized, without allowing
   * case variations.
   */
  VO_STRICT_CASE,
  /**
   * The recognition process applies Vision Object's legacy casing rules:
   * <pre>[Vocabulary entry] -> [What can be recognized]
   * hello              -> hello, Hello, HELLO
   * Hello              -> Hello, HELLO
   * HELLO              -> HELLO</pre>
   */
  VO_LEGACY_CASE,
  /**
   * The recognition process applies relaxed casing rules: any combination of
   * lowercase or uppercase letters is allowed in a `Vocabulary`
   * entry, <em>"lIkE THiS"</em>.
   */
  VO_LAX_CASE
};

/**
 * Lists the accentuation scheme values.
 *
 * @since 4.5_5
 */
enum VO_ACCENTUATION_SCHEME_VALUE
{
  /**
   * The recognition process applies conservative accentuation rules: only the
   * strict content of a `Vocabulary` can be recognized, without
   * allowing accentuation variations.
   */
  VO_STRICT_ACCENTUATION,
  /**
   * The recognition process applies relaxed accentuation rules: any letter in a
   * `Vocabulary` entry can be recognized with or without an accent.
   * However, a letter can be recognized in an accentuated form only if the
   * `AlphabetKnowledge` being used contains it.
   */
  VO_LAX_ACCENTUATION
};

/**
 * {@propertySet Recognizer}
 */
enum VO_RECOGNIZER_PROP
{
  /**
   * Specifies the size of the candidate lists that will be provided at the
   * character level in the recognition result. This value must be between 1
   * and 20.
   *
   * {@property uint32_t}
   */
  VO_CHAR_CANDIDATE_LIST_SIZE = (VO_Recognizer << 16) + 1,
  /**
   * Specifies the size of the candidate lists that will be provided at the word
   * level in the recognition result. This value must be between 1 and 20.
   *
   * {@property uint32_t}
   */
  VO_WORD_CANDIDATE_LIST_SIZE,
  /**
   * Specifies the size of the candidate lists that will be provided at the text
   * level in the recognition result. This value must be between 1 and 20.
   *
   * {@property uint32_t}
   */
  VO_TEXT_CANDIDATE_LIST_SIZE,
  /**
   * Tells the recognizer to detect the candidates that differ only in case and
   * return the best candidate of that lot.
   *
   * {@property bool}
   */
  VO_DISCARD_CASE_VARIATIONS,
  /**
   * Overrides the casing scheme specified by every
   * `Vocabulary` resource attached to the `Recognizer`.
   *
   * {@property voId}
   *
   * @see VO_CASING_SCHEME_VALUE
   *
   * @since 4.5_5
   */
  VO_OVERRIDE_CASING_SCHEME = 19726342,
  /**
   * Overrides the accentuation scheme specified by every
   * `Vocabulary` resource attached to the `Recognizer`.
   *
   * {@property voId}
   *
   * @see VO_ACCENTUATION_SCHEME_VALUE
   *
   * @since 4.5_5
   */
  VO_OVERRIDE_ACCENTUATION_SCHEME,
  /**
   * Tells the recognizer to detect the candidates that differ only in
   * accentuation and return the best candidate of that lot.
   *
   * {@property bool}
   *
   * @since 4.5_5
   */
  VO_DISCARD_ACCENTUATION_VARIATIONS,
  /**
   * Specifies the amount of glyph distortion. `0` means no
   * distortion. `255` means maximum supported distortion.
   *
   * {@property uint8_t}
   *
   * @since 4.5_5
   */
  VO_GLYPH_DISTORTION,
  /**
   * Specifies the amount of spelling distortion. `0` means no
   * distortion. `255` means maximum supported distortion.
   *
   * {@property uint8_t}
   *
   * @since 4.5_5
   */
  VO_SPELLING_DISTORTION,
  /**
   * Enables out of lexicon match.
   *
   * {@property bool}
   *
   * @since 4.5_5
   */
  VO_ENABLE_OUT_OF_LEXICON,
};


// -- StructuredInputRecognizer ------------------------------------------------

/**
 * Reference to an instance of the `StructuredInputRecognizer` type.
 *
 * {@extends voRecognizer}
 * {@implements voIRunnable, voIRecognitionResultProvider}
 * {@properties VO_RECOGNIZER_PROP}
 */
typedef voRecognizer voStructuredInputRecognizer;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `StructuredInputRecognizer` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created
 *   `StructuredInputRecognizer` object on success, otherwise
 *   `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of
 *   `StructuredInputRecognizer` instances would exceed the allowed
 *   limit (please remember that the limit can be shared among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voStructuredInputRecognizer voCreateStructuredInputRecognizer(voEngine engine)
{
  return voCreateObject(engine, VO_StructuredInputRecognizer);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- TextRecognizer -----------------------------------------------------------

/**
 * Reference to an instance of the `TextRecognizer` type.
 *
 * {@extends voEngineObject}
 * {@implements voIAttachTarget, voIContentFieldProcessor}
 */
typedef voEngineObject voTextRecognizer;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `TextRecognizer` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `TextRecognizer` object on success,
 *   otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `TextRecognizer` instances would
 *   exceed the allowed limit (please remember that the limit can be shared
 *   among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voTextRecognizer voCreateTextRecognizer(voEngine engine)
{
  return voCreateObject(engine, VO_TextRecognizer);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- DigitalTextMatcher -------------------------------------------------------

/**
 * Reference to an instance of the `DigitalTextMatcher` type.
 *
 * {@extends voEngineObject}
 * {@implements voIAttachTarget, voIDigitalTextMatcher}
 */
typedef voEngineObject voDigitalTextMatcher;

/**
 * Functions composing the `IDigitalTextMatcher` interface. This
 * interface exposes the public methods of the `DigitalTextMatcher`
 * type.
 *
 * {@implementingTypes voDigitalTextMatcher}
 * @see VO_IDigitalTextMatcher, VO_DigitalTextMatcher.
 */
typedef struct _voIDigitalTextMatcher
{
  /**
   * Answers the question: does the given string match the current resource
   * configuration?
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `DigitalTextMatcher` instance.
   * @param charset Reference to the `Charset` instance to be used to
   *   convert the string into its MyScript internal representation.
   * @param string Bytes composing the string to be tested.
   *
   * @return `VO_YES` if the string matches, `VO_NO` if
   *   the string doesn't match, or `VO_ERR` on failure.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `DigitalTextMatcher` instance.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is
   *   `NULL` and no default charset was set.
   * @throws VO_INVALID_OBJECT The `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER The `string` parameter or its
   *   `bytes` member points to unreadable memory.
   * @throws VO_INVALID_ARGUMENT The string is empty.
   */
  voYesNo (VO_MSE_CALL *matches)(voEngine engine, voDigitalTextMatcher target, voCharset charset, const voString* string);
}
voIDigitalTextMatcher;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `DigitalTextMatcher` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `DigitalTextMatcher`
 *   object on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `DigitalTextMatcher`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voDigitalTextMatcher voCreateDigitalTextMatcher(voEngine engine)
{
  return voCreateObject(engine, VO_DigitalTextMatcher);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- Resource -----------------------------------------------------------------

/**
 * Reference to an instance of the `Resource` type. The
 * `Resource` type is an abstract base type that models knowledge
 * about the various language elements you are recognizing.
 *
 * {@extends voEngineObject}
 * {@subTypes voAlphabetKnowledge, voLinguisticKnowledge, voSubsetKnowledge, voArchive}
 * {@typeProperties VO_RESOURCE_TPROP}
 * {@properties VO_RESOURCE_PROP}
 *
 * @see VO_Resource, VO_RES_TPROP.
 * @see voAlphabetKnowledge, voLinguisticKnowledge, voSubsetKnowledge,
 *   voArchive.
 */
typedef voEngineObject voResource;

/**
 * {@typePropertySet Resource}
 */
enum VO_RESOURCE_TPROP
{
  /**
   * Represents the maximum number of `Resource` instances that can
   * exist at the same time in the user side of a MyScript enabled application.
   * The special value zero means no limit. Other values are adjusted to the
   * next multiple of 16. A value under the current count is permitted and will
   * constrain future resource creations.
   *
   * {@property uint32_t}
   */
  VO_USER_RES_LIMIT = VO_USER_OBJ_LIMIT,
  /**
   * Gives the number of `Resource` instances that currently exist in
   * the user side of a MyScript enabled application.
   *
   * {@property read-only uint32_t}
   */
  VO_USER_RES_COUNT = VO_USER_OBJ_COUNT
};

/**
 * {@propertySet Resource}
 */
enum VO_RESOURCE_PROP
{
  /**
   * Represents the name of the `Resource` instance (encoded in
   * US-ASCII). This property is writable by the resource creator and readable
   * by any user. The value must be a sequence of at most 56 characters taken
   * from among the following:
   * `['a'...'z', 'A'...'Z', '0'...'9', '_', '+', '/', '-', '.']`.
   *
   * {@property voString}
   */
  VO_RESOURCE_NAME = (VO_Resource << 16),
  /**
   * Represents the content version of the `Resource` instance. This
   * property is writable by the resource creator and readable by any user. The
   * format of this number is specified by the `VO_VERSION()` macro.
   *
   * {@property uint32_t}
   */
  VO_RESOURCE_VERSION
};


// -- AlphabetKnowledge --------------------------------------------------------

/**
 * Reference to an instance of the `AlphabetKnowledge` type. The
 * `AlphabetKnowledge` type models knowledge of the alphabet and the
 * segmentation characteristics of a specific language.
 *
 * {@extends voResource}
 * {@implements voIAlphabet}
 */
typedef voResource voAlphabetKnowledge;


// -- CursiveAlphabetKnowledge -------------------------------------------------

/**
 * Reference to an instance of the `CursiveAlphabetKnowledge` type.
 *
 * {@extends voAlphabetKnowledge}
 */
typedef voAlphabetKnowledge voCursiveAlphabetKnowledge;


// -- HandPrintedAlphabetKnowledge ---------------------------------------------

/**
 * Reference to an instance of the `HandPrintedAlphabetKnowledge`
 * type.
 *
 * {@extends voAlphabetKnowledge}
 */
typedef voAlphabetKnowledge voHandPrintedAlphabetKnowledge;


// -- IsolatedAlphabetKnowledge ------------------------------------------------

/**
 * Reference to an instance of the `IsolatedAlphabetKnowledge` type.
 *
 * {@extends voAlphabetKnowledge}
 */
typedef voAlphabetKnowledge voIsolatedAlphabetKnowledge;


// -- LinguisticKnowledge ------------------------------------------------------

/**
 * Reference to an instance of the `LinguisticKnowledge` type.
 * The `LinguisticKnowledge` type is an abstract type that models
 * knowledge about the words, phrases or particular semantic units that may
 * exist in a specific language.
 *
 * {@extends voResource}
 * {@subTypes voVocabulary, voGrammar}
 */
typedef voResource voLinguisticKnowledge;


// -- Vocabulary ---------------------------------------------------------------

/**
 * Reference to an instance of the `Vocabulary` type.
 * The `Vocabulary` type is an abstract type that models vocabulary
 * level linguistic knowledge given to the recognizer.
 *
 * {@extends voLinguisticKnowledge}
 * {@subTypes voLexicalUnit, voLexicon}
 * {@properties VO_VOCABULARY_PROP}
 *
 * @see VO_Vocabulary
 * @see voLinguisticKnowledge
 * @see voLexicalUnit, voLexicon
 * @see VO_VOCABULARY_PROP
 */
typedef voLinguisticKnowledge voVocabulary;

/**
 * {@propertySet Vocabulary}
 */
enum VO_VOCABULARY_PROP
{
  /**
   * Scales the frequency values of a `Vocabulary` resource so that
   * their associated probabilities are given more or less importance against
   * other probabilities in the recognition process. The default value is 1.
   *
   * {@property float}
   */
  VO_FREQUENCY_SCALE = (VO_Vocabulary << 16),
  /**
   * Sets aside a certain percentage (expressed by a value between 0 and 1) of
   * the paths that the recognizer explores for one particular resource. By
   * doing this, the vocabulary resource can supply a recognition candidate even
   * if the scores from its paths are noticeably lower than the other scores.
   * For example you could use `VO_FREQUENCY_SCALE` in conjunction
   * with `VO_RESERVED_RECOGNITION_PATHS` to give precedence to a
   * resource but reserve some paths for another resource in order to provide a
   * safety net in case of a nil match with the first one.
   *
   * {@property float}
   */
  VO_RESERVED_RECOGNITION_PATHS,
  /**
   * Sets aside a maximum percentage (expressed as a value between 0 and 1) of
   * the paths that the recognizer explores for one particular resource. By
   * doing this, the vocabulary resource will not populate the whole recognition
   * path bandwidth. Using this property in conjunction with the
   * `VO_RESERVED_RECOGNITION_PATHS` property gives complete control
   * over the bandwidth for the vocabulary resource.
   *
   * {@property float}
   *
   * @since 4.0_1
   */
  VO_RECOGNITION_PATH_LIMIT = VO_RESERVED_RECOGNITION_PATHS + 2,
  /**
   * Controls the way character case variations are being handled by the
   * recognition process. By default, `Lexicon` and
   * `LexicalUnit` resources use legacy casing rules
   * (@see VO_LEGACY_CASE):
   * <pre>[Vocabulary entry] -> [What can be recognized]
   * hello              -> hello, Hello, HELLO
   * Hello              -> Hello, HELLO
   * HELLO              -> HELLO</pre>
   *
   * {@property voId}
   *
   * @since 4.5_5
   */
  VO_CASING_SCHEME,
  /**
   * Controls the way character accentuation variations are being handled by the
   * recognition process. By default, all `Vocabulary` resources use
   * strict accentuation rules (@see AccentuationScheme.STRICT_ACCENTUATION).
   *
   * {@property voId}
   *
   * @since 4.5_5
   */
  VO_ACCENTUATION_SCHEME
};


// -- LexicalUnit --------------------------------------------------------------

/**
 * Reference to an instance of the `LexicalUnit` type.
 *
 * {@extends voVocabulary}
 * {@implements voILexicalUnit, voICompilable}
 */
typedef voVocabulary voLexicalUnit;

/**
 * Functions composing the `ILexicalUnit` interface. This interface
 * exposes the public methods of the `LexicalUnit` type.
 *
 * {@implementingTypes voLexicalUnit}
 * @see VO_ILexicalUnit, VO_LexicalUnit.
 */
typedef struct _voILexicalUnit
{
  /**
   * Defines a named regular expression.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `LexicalUnit` instance.
   * @param reserved Reserved for later use.
   * @param charset Reference to the `Charset` instance to be used
   *   when decoding `name` and `regex`.
   * @param name Name of the regular expression (to be used when you want to
   *   reference it from another regular expression).
   * @param regex Regular expression.
   * @param frequency Frequency assigned to this regular expression. This value
   *   must be between -1 (meaning low frequency) and 1 (meaning high
   *   frequency).
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `LexicalUnit` instance.
   * @throws VO_MODIFICATION_ACCESS_DENIED The `target` reference
   *   is in use by another object.
   * @throws VO_INVALID_OBJECT The `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_ARGUMENT When `name` is the empty string.
   * @throws VO_INVALID_USER_BUFFER When `name` string or its
   *   bytes member is not readable.
   * @throws VO_INVALID_ARGUMENT When `regex` is the empty string.
   * @throws VO_INVALID_USER_BUFFER When `regex` string or its
   *   bytes member is not readable.
   * @throws VO_REGEX_INVALID_CHARACTER Invalid character in
   *   `name`.
   * @throws VO_REGEX_SUBEXP_IMBALANCE Sub-expression imbalance in
   *   `regex`.
   * @throws VO_REGEX_UNMATCHED_OPEN_SET Unmatched open set in
   *   `regex`.
   * @throws VO_REGEX_UNMATCHED_OPEN_REF Unmatched open reference in
   *   `regex`.
   * @throws VO_REGEX_TRAILING_ESCAPE Trailing escape character in
   *   `regex`.
   * @throws VO_REGEX_INVALID_CHARACTER Invalid character in
   *   `regex`.
   * @throws VO_REGEX_INVALID_REFERENCE `regex` refers to an
   *   undefined entity.
   * @throws VO_REGEX_UNMATCHED_CLOSE_SET Unmatched close set in
   *   `regex`.
   * @throws VO_REGEX_UNMATCHED_CLOSE_REF Unmatched close reference in
   *   `regex`.
   * @throws VO_REGEX_UNESCAPED_OPERATOR Unescaped operator in
   *   `regex`.
   * @throws VO_INVALID_ARGUMENT The frequency parameter is not between -1 and
   *   1.
   * @throws VO_INVALID_STATE The target `LexicalUnit` is compiled.
   */
  bool (VO_MSE_CALL *defineRegex)(voEngine engine, voLexicalUnit target, voEngineObject reserved, voCharset charset, const voString* name, const voString* regex, float frequency);

  /**
   * Defines the main regular expression.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `LexicalUnit` instance.
   * @param reserved Reserved for later use.
   * @param charset Reference to the `Charset` instance to be used
   *   when decoding `regex`.
   * @param regex Regular expression.
   * @param frequency Frequency assigned to this regular expression. This value
   *   must be between -1 (meaning low frequency) and 1 (meaning high
   *   frequency).
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `LexicalUnit` instance.
   * @throws VO_MODIFICATION_ACCESS_DENIED The `target` reference
   *   is in use by another object.
   * @throws VO_INVALID_OBJECT The `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_ARGUMENT When `regex` is the empty string.
   * @throws VO_INVALID_USER_BUFFER When `regex` string or its
   *   bytes member is not readable.
   * @throws VO_REGEX_SUBEXP_IMBALANCE Sub-expression imbalance in
   *   `regex`.
   * @throws VO_REGEX_UNMATCHED_OPEN_SET Unmatched open set in
   *   `regex`.
   * @throws VO_REGEX_UNMATCHED_OPEN_REF Unmatched open reference in
   *   `regex`.
   * @throws VO_REGEX_TRAILING_ESCAPE Trailing escape character in
   *   `regex`.
   * @throws VO_REGEX_INVALID_CHARACTER Invalid character in
   *   `regex`.
   * @throws VO_REGEX_INVALID_REFERENCE `regex` refers to an
   *   undefined entity.
   * @throws VO_REGEX_UNMATCHED_CLOSE_SET Unmatched close set in
   *   `regex`.
   * @throws VO_REGEX_UNMATCHED_CLOSE_REF Unmatched close reference in
   *   `regex`.
   * @throws VO_REGEX_UNESCAPED_OPERATOR Unescaped operator in
   *   `regex`.
   * @throws VO_INVALID_ARGUMENT The frequency parameter is not between -1
   *   and 1.
   * @throws VO_INVALID_STATE The target `LexicalUnit` is compiled.
   *
   * @note This is the regular expression that defines the
   *   `LexicalUnit` itself. This means that you will get
   *   `VO_INVALID_STATE` if you try to compile a
   *   `LexicalUnit` instance with only named regular expressions
   *   defined.
   */
  bool (VO_MSE_CALL *defineMainRegex)(voEngine engine, voLexicalUnit target, voEngineObject reserved, voCharset charset, const voString* regex, float frequency);

  /**
   * Imports a `Vocabulary` resource into this
   * `LexicaUnit`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `LexicalUnit` instance.
   * @param charset Reference to the `Charset` instance to be used
   *   when decoding `name`.
   * @param name Name of the entity (to be used when you want to reference it
   *   from another regular expression).
   * @param vocabulary Reference to a `Vocabulary` instance.
   * @param frequency Frequency assigned to this `Vocabulary`. This
   *   value must be between -1 (meaning low frequency) and 1 (meaning high
   *   frequency).
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `LexicalUnit` instance.
   * @throws VO_MODIFICATION_ACCESS_DENIED The `target` reference
   *   is in use by another object.
   * @throws VO_INVALID_OBJECT The `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_OBJECT The `vocabulary` reference is not a
   *   reference to a `Vocabulary` instance.
   * @throws VO_REGEX_INVALID_CHARACTER Invalid character in the identifier.
   * @throws VO_INVALID_ARGUMENT The frequency parameter is not between -1 and
   *   1.
   * @throws VO_INVALID_STATE The target `LexicalUnit` is compiled.
   */
  bool (VO_MSE_CALL *importVocabulary)(voEngine engine, voLexicalUnit target, voCharset charset, const voString* name, voVocabulary vocabulary, float frequency);
}
voILexicalUnit;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `LexicalUnit` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `LexicalUnit` object on
 *   success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `LexicalUnit` instances
 *   would exceed the allowed limit (please remember that the limit can be
 *   shared among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voLexicalUnit voCreateLexicalUnit(voEngine engine)
{
  return voCreateObject(engine, VO_LexicalUnit);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- Lexicon ------------------------------------------------------------------

/**
 * Reference to an instance of the `Lexicon` type.
 *
 * {@extends voVocabulary}
 * {@implements voILexicon, voICompilable}
 * {@properties VO_LEXICON_PROP}
 */
typedef voVocabulary voLexicon;

/**
 * {@propertySet Lexicon}
 */
enum VO_LEXICON_PROP
{
  /**
   * Gives the number of words in the `Lexicon`.
   * {@property read-only uint32_t}
   */
  VO_WORD_COUNT = (VO_Lexicon << 16),
  /**
   * Gives the maximum length of a word in the `Lexicon`.
   * {@property read-only uint32_t}
   */
  VO_MAX_WORD_LENGTH
};


/**
 * Reference to an instance of the `WordIterator` type.
 *
 * {@extends voIterator}
 * {@implements voIWordIterator}
 */
typedef voIterator voWordIterator;

/**
 * Functions composing the `IWordIterator` interface. This interface
 * exposes the public methods of the `WordIterator` type.
 *
 * {@extends voIIterator}
 * {@implementingTypes voWordIterator}
 * @see VO_IWordIterator, VO_IIterator, VO_WordIterator,
 */
typedef struct _voIWordIterator
{
  /** {@inheritDoc} */
  voYesNo (VO_MSE_CALL *isAtEnd)(voEngine engine, voWordIterator target);
  /** {@inheritDoc} */
  bool (VO_MSE_CALL *next)(voEngine engine, voWordIterator target);

  /**
   * Returns the current word as a string of characters.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `WordIterator` instance.
   * @param charset Reference to the `Charset` instance to be used
   *   when encoding the word.
   * @param string The string of the characters composing the word.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `WordIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT The `WordIterator` instance is
   *   positioned at the end of the iteration.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `WordIterator` instance.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_INVALID_OBJECT The `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER The string recipient is not readable or
   *   writable.
   * @throws VO_INVALID_USER_BUFFER The bytes member of the string recipient is
   *   not writable.
   */
  bool (VO_MSE_CALL *get)(voEngine engine, voWordIterator target, voCharset charset, voString* string);
}
voIWordIterator;


/**
 * Functions composing the `ILexicon` interface. This interface
 * exposes the public methods of the `Lexicon` type.
 *
 * {@implementingTypes voLexicon}
 * @see VO_ILexicon, VO_Lexicon.
 */
typedef struct _voILexicon
{
  /**
   * Adds a word to the `Lexicon`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `Lexicon` instance.
   * @param charset Reference to the `Charset` instance to be used
   *   when decoding the word.
   * @param string The string of the characters composing the word.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `Lexicon` instance.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_INVALID_OBJECT The `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER The string or its bytes member is not
   *   readable.
   * @throws VO_INVALID_ARGUMENT The string is empty.
   * @throws VO_INVALID_STATE The `Lexicon` instance is compiled.
   */
  bool (VO_MSE_CALL *addWord)(voEngine engine, voLexicon target, voCharset charset, const voString* string);

  /**
   * Returns a `WordIterator` over the words of the
   * `Lexicon`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `Lexicon` instance.
   *
   * @return A reference to a `WordIterator` instance on success,
   *   otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `Lexicon` instance.
   * @throws VO_INVALID_OPERATION Word retrieval has not been enabled when this
   *   `Lexicon` instance was compiled.
   * @throws VO_LIMIT_EXCEEDED The number of `WordIterator` instances
   *   would exceed the allowed limit (please remember that the limit can be
   *   shared among several types).
   */
  voWordIterator (VO_MSE_CALL *getWords)(voEngine engine, voLexicon target);
}
voILexicon;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `Lexicon`.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `Lexicon` object on
 *   success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `Lexicon` instances would
 *   exceed the allowed limit (please remember that the limit can be shared
 *   among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voLexicon voCreateLexicon(voEngine engine)
{
  return voCreateObject(engine, VO_Lexicon);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS

/**
 * Initializer to be used when creating an instance of the `Lexicon`
 * type using the `voCreateObjectEx` function.
 */
typedef struct _voLexiconInitializer
{
  /**
   * Enables later retrieval of the words contained in the
   * `Lexicon` after it has been compiled.
   */
  bool enableWordRetrieval;
}
voLexiconInitializer;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `Lexicon` type.
 *
 * @param engine Reference to an `Engine` instance.
 * @param enableWordRetrieval When true, enables later retrieval of the words
 * contained in the `Lexicon` after it has been compiled.
 *
 * @return A reference to the newly created `Lexicon` object on
 *   success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `Charset` instances would
 *   exceed the allowed limit (please remember that the limit can be shared
 *   among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voLexicon voCreateLexiconEx(voEngine engine, bool enableWordRetrieval)
{
  voLexiconInitializer initializer = { enableWordRetrieval };
  return voCreateObjectEx(engine, VO_Lexicon, &initializer, sizeof(initializer));
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- Grammar ------------------------------------------------------------------

/**
 * Reference to an instance of the `Grammar` type.
 * Grammars enable recognition of multiple words in the same field; a grammar
 * must be used to recognize several strings in the same place.
 *
 * {@extends voLinguisticKnowledge}
 *
 * @see VO_Grammar
 * @see voLinguisticKnowledge
 */
typedef voLinguisticKnowledge voGrammar;


// -- SubsetKnowledge ----------------------------------------------------------

/**
 * Reference to an instance of the `SubsetKnowledge` type.
 *
 * {@extends voResource}
 * {@implements voISubsetKnowledge}
 */
typedef voResource voSubsetKnowledge;

/**
 * Functions composing the `ISubsetKnowledge` interface. This
 * interface exposes the public methods of the `SubsetKnowledge`
 * type.
 *
 * {@implementingTypes voSubsetKnowledge}
 * @see VO_ISubsetKnowledge, VO_SubsetKnowledge.
 */
typedef struct _voISubsetKnowledge
{
  /**
   * Disables all the characters.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `SubsetKnowledge` instance.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `SubsetKnowledge` instance.
   */
  bool (VO_MSE_CALL *disableAllCharacters)(voEngine engine, voSubsetKnowledge target);
  /**
   * Enables all the characters.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `SubsetKnowledge` instance.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `SubsetKnowledge` instance.
   */
  bool (VO_MSE_CALL *enableAllCharacters)(voEngine engine, voSubsetKnowledge target);
  /**
   * Disables the specified characters.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `SubsetKnowledge` instance.
   * @param charset Reference to the `Charset` to be used to
   *   convert the `string` into MyScript internal characters.
   * @param string The string of the characters to be disabled.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `SubsetKnowledge` instance.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_INVALID_USER_BUFFER The string or its bytes member is not
   *   readable.
   * @throws VO_INVALID_ARGUMENT The string is empty.
   */
  bool (VO_MSE_CALL *disableCharacters)(voEngine engine, voSubsetKnowledge target, voCharset charset, const voString* string);
  /**
   * Enables the specified characters.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `SubsetKnowledge` instance.
   * @param charset Reference to the `Charset` to be used to
   *   convert the `string` into MyScript internal characters.
   * @param string The string of the characters to be enabled.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `SubsetKnowledge` instance.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_INVALID_USER_BUFFER The string or its bytes member is not
   *   readable.
   * @throws VO_INVALID_ARGUMENT The string is empty.
   */
  bool (VO_MSE_CALL *enableCharacters)(voEngine engine, voSubsetKnowledge target, voCharset charset, const voString* string);

  /**
   * Disables the specified character.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `SubsetKnowledge` instance.
   * @param charset Reference to the `Charset` to be used to
   *   convert the `string` into MyScript internal characters.
   * @param string The string of the character to be disabled.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `SubsetKnowledge` instance.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_INVALID_USER_BUFFER The string or its bytes member is not
   *   readable.
   * @throws VO_INVALID_ARGUMENT The string is empty.
   *
   * @since 4.5_6
   */
  bool (VO_MSE_CALL *disableCharacter)(voEngine engine, voSubsetKnowledge target, voCharset charset, const voString* string);

  /**
   * Enables the specified character.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `SubsetKnowledge` instance.
   * @param charset Reference to the `Charset` to be used to
   *   convert the `string` into MyScript internal characters.
   * @param string The string of the character to be enabled.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `SubsetKnowledge` instance.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_INVALID_USER_BUFFER The string or its bytes member is not
   *   readable.
   * @throws VO_INVALID_ARGUMENT The string is empty.
   *
   * @since 4.5_6
   */
  bool (VO_MSE_CALL *enableCharacter)(voEngine engine, voSubsetKnowledge target, voCharset charset, const voString* string);
}
voISubsetKnowledge;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `SubsetKnowledge` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `SubsetKnowledge` object
 *   on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `SubsetKnowledge`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voSubsetKnowledge voCreateSubsetKnowledge(voEngine engine)
{
  return voCreateObject(engine, VO_SubsetKnowledge);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- Archive ------------------------------------------------------------------

/**
 * Reference to an instance of the `Archive` type.
 *
 * {@extends voResource}
 * {@implements voIAttachTarget}
 */
typedef voResource voArchive;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `Archive` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `Archive` object on
 *   success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `Archive` instances would
 *   exceed the allowed limit (please remember that the limit can be shared
 *   among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voArchive voCreateArchive(voEngine engine)
{
  return voCreateObject(engine, VO_Archive);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- RecognitionResult --------------------------------------------------------

/**
 * Reference to an instance of the `RecognitionResult` type.
 *
 * {@extends voEngineObject}
 * {@implements voIRecognitionResult}
 */
typedef voEngineObject voRecognitionResult;

/**
 * Reference to an instance of the `CandidateIterator` type.
 *
 * {@extends voIterator}
 * {@implements voICandidateIterator}
 */
typedef voIterator voCandidateIterator;

/**
 * Reference to an instance of the `SegmentIterator` type.
 *
 * {@extends voIterator}
 * {@implements voISegmentIterator}
 */
typedef voIterator voSegmentIterator;


/**
 * Functions composing the `IRecognitionResult` interface. This
 * interface exposes the public methods of the `RecognitionResult`
 * type.
 *
 * {@implementingTypes voRecognitionResult}
 * @see VO_IRecognitionResult, VO_RecognitionResult.
 */
typedef struct _voIRecognitionResult
{
  /**
   * Returns the resemblance score of the best candidate.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `RecognitionResult` instance.
   *
   * @return The resemblance score of the best candidate on success, otherwise
   *   `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `RecognitionResult` instance.
   * @throws VO_INVALID_STATE There are no recognition candidates available.
 */
  float (VO_MSE_CALL *getResemblanceScore)(voEngine engine, voRecognitionResult target);

  /**
   * Returns an iterator over the different candidates.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `RecognitionResult` instance.
   *
   * @return A `CandidateIterator` instance on success, otherwise
   *   `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `RecognitionResult` instance.
   * @throws VO_LIMIT_EXCEEDED The number of `CandidateIterator`
   *   instances would exceed the allowed limit (please remember that the
   *   limit can be shared among several types).
   */
  voCandidateIterator (VO_MSE_CALL *getCandidates)(voEngine engine, voRecognitionResult target);
}
voIRecognitionResult;


/**
 * Lists recognition result candidate flags.
 *
 * @since 4.5_5
 */
enum VO_CANDIDATE_FLAG
{
  /**
   * The candidate contains at least one omitted character.
   * An omitted character is a character that was omitted by the user and has
   * been added by the spelling distortion match. Consequently, the input range
   * of the corresponding character level segment will be empty.
   */
  VO_CANDIDATE_FLAG_OMITTED = 1 << 0,
  /**
   * The candidate contains at least one superfluous character.
   * A superfluous character is a character that was superfluously added by the
   * user and has been discarded by the spelling distortion match. Consequently,
   * the label of the corresponding character level candidate will be empty.
   */
  VO_CANDIDATE_FLAG_SUPERFLUOUS = 1 << 1,
  /**
   * The candidate contains at least one substituted character.
   * A substituted character is a character which label has been substituted by
   * the spelling distortion match.
   */
  VO_CANDIDATE_FLAG_SUBSTITUTED = 1 << 2,
  /**
   * The candidate contains at least one unknown character.
   * An unknown character is a character that was considered unreadable by the
   * recognizer. Note that this character will not match normal vocabulary
   * entries which will be forced to transform it to a substituted character.
   * Consequently, only out of lexicon matches or unconstrained recognition may
   * output this.
   */
  VO_CANDIDATE_FLAG_UNKNOWN = 1 << 3,
  /**
   * The candidate contains at least one erased character.
   * An erased character is a character that has been detected has erased by an
   * attached digital ink tagger (using either a strikethrough or a double
   * strikethrough or a cross out or a scratch out gesture).
   */
  VO_CANDIDATE_FLAG_ERASED = 1 << 4,
  /**
   * The candidate contains at least one emphasized character.
   * An emphasized character is a character that has been detected has
   * emphasized by an attached digital ink tagger. Consequently, the resemblance
   * score of this character may not be accurate.
   */
  VO_CANDIDATE_FLAG_EMPHASIZED = 1 << 5,
  /**
   * The candidate was produced by an out of lexicon match.
   */
  VO_CANDIDATE_FLAG_OUT_OF_LEXICON = 1 << 6,
  /**
   * The candidate corresponds to a partial match.
   *
   * @since 4.9_8
   */
  VO_CANDIDATE_FLAG_PARTIAL = 1 << 7
};

/**
 * Functions composing the `ICandidateIterator` interface. This
 * interface exposes the public methods of the `CandidateIterator`
 * type.
 *
 * {@extends voIIterator}
 * {@implementingTypes voCandidateIterator}
 * @see VO_ICandidateIterator, VO_CandidateIterator.
 */
typedef struct _voICandidateIterator
{
  /** {@inheritDoc} */
  voYesNo (VO_MSE_CALL *isAtEnd)(voEngine engine, voIterator target);
  /** {@inheritDoc} */
  bool (VO_MSE_CALL *next)(voEngine engine, voIterator target);

  /**
   * Returns the label of this candidate.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `CandidateIterator` instance.
   * @param charset Reference to the `Charset` instance to be used
   *   to convert the MyScript internal characters into a character string.
   * @param string Recipient for the label.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `CandidateIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT The iterator is positioned at the end of the
   *   iteration.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_INVALID_OBJECT The `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER The `string` recipient is not
   *   readable or writable.
   * @throws VO_INVALID_USER_BUFFER The `bytes` member of the
   *   `string` recipient is not writable.
   */
  bool (VO_MSE_CALL *getLabel)(voEngine engine, voCandidateIterator target, voCharset charset, voString* string);

  /**
   * Returns the normalized recognition score of the current candidate.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `CandidateIterator` instance.
   *
   * @return The normalized recognition score of this candidate on success,
   *   otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `CandidateIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT The iterator is positioned at the end of the
   *   iteration.
   */
  float (VO_MSE_CALL *getNormalizedRecognitionScore)(voEngine engine, voCandidateIterator target);

  /**
   * Returns an iterator over the segments for the current candidate, which is
   * the set of pieces of input that make up this candidate's segmentation.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `CandidateIterator` instance.
   *
   * @return A `SegmentIterator` instance on success, otherwise
   *   `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `CandidateIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT The iterator is positioned at the end of the
   *   iteration.
   * @throws VO_LIMIT_EXCEEDED The number of `SegmentIterator`
   *   instances would exceed the allowed limit (please remember that the limit
   *   can be shared among several types).
   */
  voSegmentIterator (VO_MSE_CALL *getSegments)(voEngine engine, voCandidateIterator target);

  /**
   * Returns the resemblance score of the current candidate.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `CandidateIterator` instance.
   *
   * @return The resemblance score of the best candidate on success, otherwise
   *   `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `CandidateIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT The iterator is positioned at the end of the
   *   iteration.
   *
   * @since 4.5_5
   */
  float (VO_MSE_CALL *getResemblanceScore)(voEngine engine, voCandidateIterator target);

  /**
   * Returns the flags of the current candidate.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `CandidateIterator` instance.
   *
   * @return A binary or combination of `VO_CANDIDATE_FLAG`s on
   *   success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `CandidateIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT The iterator is positioned at the end of the
   *   iteration.
   *
   * @see VO_CANDIDATE_FLAG
   *
   * @since 4.5_5
   */
  int (VO_MSE_CALL *getFlags)(voEngine engine, voCandidateIterator target);

  /**
   * Returns the spelling distortion ratio of the current candidate.
   * This is the number of characters that are either omitted or superfluous
   * or substituted divided by the total number of characters.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `CandidateIterator` instance.
   *
   * @return A value between `0` and `1` on success,
   *   otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `CandidateIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT The iterator is positioned at the end of the
   *   iteration.
   *
   * @since 4.5_5
   */
  float (VO_MSE_CALL *getSpellingDistortionRatio)(voEngine engine, voCandidateIterator target);

  /**
   * Returns the `LinguisticKnowledge` used to generate the current word-level
   * candidate (can be `Vocabulary` or `Grammar`).
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `CandidateIterator` instance.
   *
   * @return A reference to an instance of the `LinguisticKnowledge` type on
   *   success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `CandidateIterator` instance.
   * @throws VO_INVALID_OPERATION The `target` iterator is not a word-level
   *   `CandidateIterator`.
   * @throws VO_INVALID_STATE The `target` comes from a detached
   *   `RecognitionResult`, in which case the `LinguisticKnowledge` source
   *   information is not available.
   * @throws VO_NO_SUCH_ELEMENT The iterator is positioned at the end of the
   *   iteration.
   *
   * @since 4.9_8
   */
  voLinguisticKnowledge (VO_MSE_CALL *getSourceLinguisticKnowledge)(voEngine engine, voCandidateIterator target);

  /**
   * Returns the name of the linguistic knowledge used to generate the current
   * word-level candidate.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `CandidateIterator` instance.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `CandidateIterator` instance.
   * @throws VO_INVALID_OPERATION The `target` iterator is not a word-level
   *   `CandidateIterator`.
   * @throws VO_INVALID_STATE The `target` comes from a detached
   *   `RecognitionResult`, in which case the `LinguisticKnowledge` source
   *   information is not available.
   * @throws VO_NO_SUCH_ELEMENT The iterator is positioned at the end of the
   *   iteration.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_INVALID_OBJECT The `charset` reference is not a reference to a
   *   `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER The `name` recipient is not readable or
   *   writable.
   * @throws VO_INVALID_USER_BUFFER The `bytes` member of the `name` recipient
   *   is not writable.
   *
   * @since 6.0
   */
  bool (VO_MSE_CALL *getSourceLinguisticKnowledgeName)(voEngine engine, voCandidateIterator target, voCharset charset, voString* name);
}
voICandidateIterator;


/**
 * The `InputItemLocator` type represents the location of an item in
 * the input. An input item is either a point within a stroke component, or a
 * character within a string component.
 * Then each component is located within an input unit.
 */
typedef struct _voInputItemLocator
{
  /**
   * Index of the input unit that contains the item.
   */
  short unitIndex;
  /**
   * Index of the stroke component or the string component that contains the
   * item, within its unit.
   */
  short componentIndex;
  /**
   * Index of the point or character item, within its component.
   */
  short itemIndex;
}
voInputItemLocator;

/**
 * The `InputRangeElement` type models a contiguous range in the
 * input delimited by its first and last enclosed items.
 */
typedef struct _voInputRangeElement
{
  /**
   * Location of the first item.
   */
  voInputItemLocator first;
  /**
   * Location of the last item.
   */
  voInputItemLocator last;
}
voInputRangeElement;

/**
 * The `InputRange` type models a discrete range in the input,
 * denoted by the list of the contiguous range elements that compose it.
 */
typedef struct _voInputRange
{
  /**
   * Pointer to the contiguous range elements.
   */
  voInputRangeElement* elements;
  /**
   * Number of contiguous range elements.
   */
  size_t count;
}
voInputRange;

/**
 * Functions composing the `ISegmentIterator` interface. This
 * interface exposes the public methods of the `SegmentIterator`
 * type.
 *
 * {@extends voIIterator}
 * {@implementingTypes voSegmentIterator}
 * @see VO_ISegmentIterator, VO_SegmentIterator.
 */
typedef struct _voISegmentIterator
{
  /** {@inheritDoc} */
  voYesNo (VO_MSE_CALL *isAtEnd)(voEngine engine, voIterator target);
  /** {@inheritDoc} */
  bool (VO_MSE_CALL *next)(voEngine engine, voIterator target);

  /**
   * Returns the range in the input that corresponds to this segment.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `SegmentIterator` instance.
   * @param range Recipient for the result.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `SegmentIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT The iterator is positioned at the end of the
   *   iteration.
   * @throws VO_INVALID_USER_BUFFER The `range` recipient is not
   *   readable or writable.
   * @throws VO_INVALID_USER_BUFFER The `elements` member of the
   *   `range` recipient is not writable.
   * @throws VO_INVALID_STATE The portion of a MyScript Document associated with
   *   this input has been modified, so the associated input range is not
   *   valid anymore.
   */
  bool (VO_MSE_CALL *getInputRange)(voEngine engine, voSegmentIterator target, voInputRange* range);

  /**
   * Returns the position of the best candidate from the current context
   * in this segment's top list (list of candidates).
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `SegmentIterator` instance.
   *
   * @return The position of the best candidate from the current context in
   *   this segment's top list on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `SegmentIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT The iterator is positioned at the end of the
   *   iteration.
   */
  int (VO_MSE_CALL *getSelectedCandidateIndex)(voEngine engine, voSegmentIterator target);

  /**
   * Returns the resemblance score of the best candidate for this segment.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `SegmentIterator` instance.
   *
   * @return The resemblance score of the best candidate for this segment on
   *   success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `SegmentIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT The iterator is positioned at the end of the
   *   iteration.
   */
  float (VO_MSE_CALL *getResemblanceScore)(voEngine engine, voSegmentIterator target);

  /**
   * Returns an iterator to the candidates of this segment.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `SegmentIterator` instance.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `SegmentIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT The iterator is positioned at the end of the
   *   iteration.
   * @throws VO_LIMIT_EXCEEDED The number of `CandidateIterator`
   *   instances would exceed the allowed limit (please remember that the limit
   *   can be shared among several types).
   */
  voCandidateIterator (VO_MSE_CALL *getCandidates)(voEngine engine, voSegmentIterator target);
}
voISegmentIterator;


// -- IAlphabet ----------------------------------------------------------------

/**
 * Functions composing the `IAlphabet` interface. The term "alphabet"
 * here denotes a finite set of symbols.

 * {@implementingTypes voAlphabetKnowledge}
 */
typedef struct _voIAlphabet
{
  /**
   * Returns the number of symbols in this alphabet.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   *
   * @return The number of symbols in this alphabet on success, otherwise
   *   `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement the `IAlphabet` interface.
   */
  uint32_t (VO_MSE_CALL *getSymbolCount)(voEngine engine, voEngineObject target);

  /**
   * Returns the symbol at the specified `index`, as a character
   * string.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param index Index of the requested symbol.
   * @param charset Reference to the `Charset` instance to be used
   *   to convert the MyScript internal symbol into a character string.
   * @param string Recipient for the symbol value.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement the `IAlphabet` interface.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_INVALID_USER_BUFFER The `string` recipient is not
   *   readable or writable.
   * @throws VO_INVALID_USER_BUFFER The `bytes` member of the
   *   `string` recipient is not writable.
   */
  bool (VO_MSE_CALL *getSymbolAt)(voEngine engine, voEngineObject target, uint32_t index, voCharset charset, voString* string);
}
voIAlphabet;


// -- IRecognitionResultProvider -----------------------------------------------

/**
 * Functions composing the `IRecognitionResultProvider` interface.
 *
 * {@implementingTypes voStructuredInputRecognizer}
 */
typedef struct _voIRecognitionResultProvider
{
  /**
   * Retrieves the recognition result associated with the target object.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   *
   * @return A `RecognitionResult` instance on success, otherwise
   *          `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement the `IRecognitionResultProvider` interface.
   * @throws VO_INVALID_STATE The object is not in a state where the
   *   result is available.
   * @throws VO_LIMIT_EXCEEDED The number of `RecognitionResult`
   *   instances would exceed the allowed limit (please remember that the limit
   *   can be shared among several types).
   */
  voRecognitionResult (VO_MSE_CALL *getResult)(voEngine engine, voEngineObject target);

  /**
   * Retrieves the recognition result associated with the target object.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param enablePartialMatches If true partial matches of the last word
   *          segment will be allowed.
   *
   * @return A `RecognitionResult` instance on success, otherwise
   *          `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement the `IRecognitionResultProvider` interface.
   * @throws VO_INVALID_STATE The object is not in a state where the
   *   result is available.
   * @throws VO_LIMIT_EXCEEDED The number of `RecognitionResult`
   *   instances would exceed the allowed limit (please remember that the limit
   *   can be shared among several types).
   *
   * @since 4.9_8
   */
  voRecognitionResult (VO_MSE_CALL *getResultEx)(voEngine engine, voEngineObject target, bool enablePartialMatches);
}
voIRecognitionResultProvider;


// -- Digital Ink Tagger -------------------------------------------------------

/**
 * Lists the digital ink tag types.
 */
enum VO_TAG_TYPE
{
  /**
   * Type of a text line tag.
   */
  VO_TAG_TEXT_LINE,
  /**
   * Type of a text block tag.
   */
  VO_TAG_TEXT_BLOCK,
  /**
   * Type of a correction block tag.
   */
  VO_TAG_CORRECTION_BLOCK,
  /**
   * Type of an erasure tag.
   */
  VO_TAG_ERASURE,
  /**
   * Type of an erased text tag.
   */
  VO_TAG_ERASED_TEXT,
  /**
   * Type of a strikethrough tag.
   */
  VO_TAG_STRIKETHROUGH,
  /**
   * Type of a double strikethrough tag.
   */
  VO_TAG_DOUBLE_STRIKETHROUGH,
  /**
   * Type of a cross out tag.
   */
  VO_TAG_CROSS_OUT,
  /**
   * Type of a scratch out tag.
   */
  VO_TAG_SCRATCH_OUT,
  /**
   * Type of an inserted text tag.
   */
  VO_TAG_INSERTED_TEXT,
  /**
   * Type of a missing pen lift tag.
   */
  VO_TAG_MISSING_PEN_LIFT,
  /**
   * Type of an emphasized character tag.
   */
  VO_TAG_EMPHASIZED_CHARACTER,
  /**
   * Type of a text column tag.
   *
   * @since 4.7_7
   */
  VO_TAG_TEXT_COLUMN,
  /**
   * The number of tags.
   */
  VO_TAG_COUNT = 32
};


/**
 * Reference to an instance of the `TagIterator` type.
 *
 * {@extends voIterator}
 * {@implements voITagIterator}
 */
typedef voIterator voTagIterator;

/**
 * Functions composing the `ITagIterator` interface. This
 * interface exposes the public methods of the `TagIterator`
 * type.
 *
 * {@extends voIIterator}
 * {@implementingTypes voTagIterator}
 * @see VO_ITagIterator, VO_TagIterator.
 */
typedef struct _voITagIterator
{
  /** {@inheritDoc} */
  voYesNo (VO_MSE_CALL *isAtEnd)(voEngine engine, voIterator target);
  /** {@inheritDoc} */
  bool (VO_MSE_CALL *next)(voEngine engine, voIterator target);

  /**
   * Returns the type of the tag pointed to by this tag iterator.
   *
   * @param engine a reference to an `Engine` instance.
   * @param target a reference to a `TagIterator` instance.
   *
   * @return a value from the `VO_TAG_TYPE` enumeration on success,
   * otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE if the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT if the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION if the `target` reference is not
   *   a reference to a `TagIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT if the iterator is positioned at the end of the
   *   iteration.
   *
   * @see enum VO_TAG_TYPE
   */
  int (VO_MSE_CALL *getType)(voEngine engine, voTagIterator target);

  /**
   * Returns the range in the input that corresponds to the tag pointed to by
   * this tag iterator.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `TagIterator` instance.
   * @param range Recipient for the result.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `TagIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT if the iterator is positioned at the end of the
   *   iteration.
   * @throws VO_INVALID_USER_BUFFER The `range` recipient is not
   *   readable or writable.
   * @throws VO_INVALID_USER_BUFFER The `elements` member of the
   *   `range` recipient is not writable.
   */
  bool (VO_MSE_CALL *getInputRange)(voEngine engine, voTagIterator target, voInputRange* range);
}
voITagIterator;


/**
 * Reference to an instance of the `TagList` type.
 *
 * {@extends voEngineObject}
 * {@implements voITagList}
 */
typedef voEngineObject voTagList;

/**
 * Functions composing the `ITagList` interface. This interface
 * exposes the public methods of the `TagList` type.
 *
 * {@implementingTypes voTagList}
 * @see VO_ITagList, VO_TagList.
 */
typedef struct _voITagList
  {
    /**
     * Returns an iterator over the items of this tag list.
     *
     * @param engine a reference to an `Engine` instance.
     * @param target a reference to a `TagList` instance.
     *
     * @return the iterator on success, otherwise `NULL`.
     *
     * @throws VO_NO_SUCH_ENGINE if the `engine` reference is invalid.
     * @throws VO_NO_SUCH_OBJECT if the `target` reference is invalid.
     * @throws VO_INVALID_OPERATION if the `target` reference is not
     * a reference to a `TagList` instance.
     */
    voTagIterator (VO_MSE_CALL *getIterator)(voEngine engine, voTagList target);
  }
  voITagList;


/**
 * Reference to an instance of the `DigitalInkTagger` type.
 *
 * {@extends voHandwritingContext}
 * {@implements voIDigitalInkTagger, voIRunnable}
 */
typedef voHandwritingContext voDigitalInkTagger;

/**
 * Functions composing the `IDigitalInkTagger` interface. This
 * interface exposes the public methods of the `DigitalInkTagger`
 * type.
 *
 * {@implementingTypes voDigitalInkTagger}
 * @see VO_IDigitalInkTagger, VO_DigitalInkTagger.
 */
typedef struct _voIDigitalInkTagger
{
  /**
   * Retrieves the detection sensitivity of a specific tag.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `DigitalInkTagger` instance.
   * @param tagType The type of the tag for which to retrieve the weight.
   *
   * @return The detection sensitivity for the specified type on success,
   *   otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `DigitalInkTagger` instance.
   * @throws VO_INVALID_ARGUMENT The `tagType` value is not a valid
   *   tag type.
   */
  float (VO_MSE_CALL *getDetectionSensitivity)(voEngine engine, voDigitalInkTagger target, int tagType);

  /**
   * Sets the detection sensitivity of a specific tag.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `DigitalInkTagger` instance.
   * @param tagType The type of the tag for which to retrieve the weight.
   * @param sensitivity The detection sensitivity value for the tag type.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `DigitalInkTagger` instance.
   * @throws VO_INVALID_ARGUMENT The `tagType` value is not a valid
   *   tag type.
   * @throws VO_INVALID_ARGUMENT The `sensitivity` value does not lie
   *   between `0` and `1`.
   */
  bool (VO_MSE_CALL *setDetectionSensitivity)(voEngine engine, voDigitalInkTagger target, int tagType, float sensitivity);

  /**
   * Returns the list of recognized tags.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `DigitalInkTagger` instance.
   *   instance.
   *
   * @return A `TagList` instance on success, otherwise
   *   `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `DigitalInkTagger` instance.
   * @throws VO_INVALID_STATE The `target` digital ink tagger was
   *   not run.
   * @throws VO_LIMIT_EXCEEDED The number of `TagList` instances
   *   would exceed the allowed limit (please remember that the limit can be
   *   shared among several types).
   */
  voTagList (VO_MSE_CALL *getTags)(voEngine engine, voDigitalInkTagger target);
}
voIDigitalInkTagger;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `DigitalInkTagger` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `DigitalInkTagger` object
 *   on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `DigitalInkTagger`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voDigitalInkTagger voCreateDigitalInkTagger(voEngine engine)
{
  return voCreateObject(engine, VO_DigitalInkTagger);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS

#endif // end of: #ifndef C_MYSCRIPTHWR_H
