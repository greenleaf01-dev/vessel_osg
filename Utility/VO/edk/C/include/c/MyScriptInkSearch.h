#ifndef C_MYSCRIPTINKSEARCH_H
#define C_MYSCRIPTINKSEARCH_H 0x06010000
/**
 * @file c/MyScriptInkSearch.h
 * Native interface to the MyScript InkSearch service.
 */

#include "MyScriptEngine.h"
#include "MyScriptHWR.h"


// -- error codes --------------------------------------------------------------

/**
 * Lists the MyScript InkSearch errors.
 */
enum VO_INKSEARCH_ERR
{
  /**
   * Unable to complete the requested operation because the `Index`
   * object is missing.
   */
  VO_MISSING_INDEX = VO_INVALID_STATE | (3 << 16),
  /**
   * Unable to complete the requested operation because the `Query`
   * object is missing.
   */
  VO_MISSING_QUERY
};

// -- types and interfaces -----------------------------------------------------

/**
 * Lists the MyScript InkSearch types.
 */
enum VO_INKSEARCH_T
{
  /**
   * `Indexer` type.
   *
   * @see voIndexer.
   */
  VO_Indexer = 800,
  /**
   * `StructuredInputIndexer` type.
   *
   * @see voStructuredInputIndexer, voCreateStructuredInputIndexer.
   */
  VO_StructuredInputIndexer = 802,
  /**
   * `StructuredInputSlimIndexer` type.
   *
   * @see voStructuredInputSlimIndexer, voCreateStructuredInputSlimIndexer.
   */
  VO_StructuredInputSlimIndexer = 804,

  /**
   * `Index` type.
   *
   * @see voIndex.
   */
  VO_Index,

  /**
   * `Query` type.
   *
   * @see voQuery.
   */
  VO_Query,
  /**
   * `VocabularyQuery` type.
   *
   * @see voVocabularyQuery, voCreateVocabularyQuery.
   */
  VO_VocabularyQuery,
  /**
   * `StringQuery` type.
   *
   * @see voStringQuery, voCreateStringQuery.
   */
  VO_StringQuery,
  /**
   * `OrQuery` type.
   *
   * @see voOrQuery, voCreateBinaryQuery.
   */
  VO_OrQuery,
  /**
   * `AndQuery` type.
   *
   * @see voAndQuery, voCreateBinaryQuery.
   */
  VO_AndQuery,
  /**
   * `AndNotQuery` type.
   *
   * @see voAndNotQuery, voCreateBinaryQuery.
   */
  VO_AndNotQuery,
  /**
   * `NearQuery` type.
   *
   * @see voNearQuery, voCreateBinaryQuery.
   */
  VO_NearQuery,

  /**
   * `Finder` type.
   *
   * @see voFinder, voCreateFinder.
   */
  VO_Finder,

  /**
   * `FindResult` type.
   *
   * @see voFindResult.
   */
  VO_FindResult,
  /**
   * `OccurrenceIterator` type.
   *
   * @see voOccurrenceIterator.
   */
  VO_OccurrenceIterator,
  /**
   * `OccurrenceCharacterIterator` type.
   *
   * @since 4.1.0
   * @see voOccurrenceCharacterIterator.
   */
  VO_OccurrenceCharacterIterator,
  /**
   * `TextIndexer` type.
   *
   * @since 6.0
   * @see voTextIndexer.
   */
  VO_TextIndexer
};


/**
 * Lists the MyScript InkSearch interfaces.
 */
enum VO_INKSEARCH_I
{
  /**
   * `IIndexingResultProvider` interface type.
   *
   * @see voIIndexingResultProvider.
   */
  VO_IIndexingResultProvider = 900,
  /**
   * `IFindResultProvider` interface type.
   *
   * @see voIFindResultProvider.
   */
  VO_IFindResultProvider,
  /**
   * `IFindResult` interface type.
   *
   * @see voIFindResult.
   */
  VO_IFindResult,
  /**
   * `IOccurrenceIterator` interface type.
   *
   * @see voIOccurrenceIterator.
   */
  VO_IOccurrenceIterator,
  /**
   * `IOccurrenceCharacterIterator` interface type.
   *
   * @since 4.1.0
   *
   * @see voIOccurrenceCharacterIterator.
   */
  VO_IOccurrenceCharacterIterator
};


// --Index ---------------------------------------------------------------------

/**
 * Reference to an instance of the `Index` type.
 *
 * {@extends voEngineObject}
 *
 * @see VO_Index.
 * @see voStructuredInputIndexer, voStructuredInputSlimIndexer.
 */
typedef voEngineObject voIndex;


// -- Indexer ------------------------------------------------------------------

/**
 * Reference to an instance of the `Indexer` type.
 *
 * {@extends voHandwritingContext}
 * {@subTypes voStructuredInputIndexer, voStructuredInputSlimIndexer}
 * {@implements voIRunnable, voIIndexingResultProvider}
 * {@properties VO_INDEXER_PROP}
 *
 * @see VO_Indexer.
 * @see voStructuredInputIndexer, voStructuredInputSlimIndexer.
 */
typedef voHandwritingContext voIndexer;

/**
 * Lists the `Index` size versus accuracy compromise special values.
 */
enum VO_INDEX_SIZE_ACCURACY_COMPROMISE_VALUE
{
  /**
   * Minimize index size.
   */
  VO_MINIMIZE_INDEX_SIZE = 0,
  /**
   * Maximize search accuracy.
   */
  VO_MAXIMIZE_ACCURACY = 255
};

/**
 * {@propertySet Indexer}
 */
enum VO_INDEXER_PROP
{
  /**
   * Adjusts the treatment optimization compromise between index size and search
   * accuracy.
   *
   * {@property uint8_t}
   *
   * @note you can use `VO_MINIMIZE_INDEX_SIZE`,
   * `VO_MAXIMIZE_ACCURACY`, or any value between `0` and
   * `255`.
   * However, there are less than 255 levels and the value will be adjusted to
   * the closest acceptable value. The default value of this property is 128.
   */
  VO_INDEX_SIZE_ACCURACY_COMPROMISE = (VO_Indexer << 16)
};


// -- IIndexingResultProvider --------------------------------------------------

/**
 * Functions composing the `IIndexingResultProvider` interface.
 *
 * {@implementingTypes voStructuredInputIndexer, voStructuredInputSlimIndexer}
 */
typedef struct _voIIndexingResultProvider
{
  /**
   * Returns the indexing result (an `Index` object) associated with
   * the target object.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   *
   * @returns An `Index` instance on success, otherwise
   *   `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement the `IIndexingResultProvider` interface.
   * @throws VO_LIMIT_EXCEEDED The number of `Index` instances
   *   would exceed the allowed limit (please remember that the limit can be
   *   shared among several types).
   */
  voIndex (VO_MSE_CALL *getResult)(voEngine engine, voEngineObject target);
}
voIIndexingResultProvider;


// -- StructuredInputIndexer ---------------------------------------------------

/**
 * Reference to an instance of the `StructuredInputIndexer` type.
 *
 * {@extends voIndexer}
 *
 * @see VO_StructuredInputIndexer, voCreateStructuredInputIndexer.
 */
typedef voIndexer voStructuredInputIndexer;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `StructuredInputIndexer` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `StructuredInputIndexer`
 *   object on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `StructuredInputIndexer`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voStructuredInputIndexer voCreateStructuredInputIndexer(voEngine engine)
{
  return voCreateObject(engine, VO_StructuredInputIndexer);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- StructuredInputSlimIndexer -----------------------------------------------

/**
 * Reference to an instance of the `StructuredInputSlimIndexer` type.
 *
 * {@extends voIndexer}
 *
 * @see VO_StructuredInputSlimIndexer, voCreateStructuredInputSlimIndexer.
 */
typedef voIndexer voStructuredInputSlimIndexer;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `StructuredInputSlimIndexer` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created
 *   `StructuredInputSlimIndexer` object on success, otherwise
 *   `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of
 *   `StructuredInputSlimIndexer` instances would exceed the allowed
 *   limit (please remember that the limit can be shared among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voStructuredInputSlimIndexer voCreateStructuredInputSlimIndexer(voEngine engine)
{
  return voCreateObject(engine, VO_StructuredInputSlimIndexer);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS

// -- TextIndexer --------------------------------------------------------------

/**
 * Reference to an instance of the `TextIndexer` type.
 *
 * {@extends voEngineObject}
 * {@implements voIAttachTarget, voIContentFieldProcessor}
 * {@properties VO_INDEXER_PROP}
 */
typedef voEngineObject voTextIndexer;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `TextIndexer` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created
 *   `TextIndexer` object on success, otherwise
 *   `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of
 *   `StructuredInputSlimIndexer` instances would exceed the allowed
 *   limit (please remember that the limit can be shared among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voTextIndexer voCreateTextIndexer(voEngine engine)
{
  return voCreateObject(engine, VO_TextIndexer);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- Query --------------------------------------------------------------------

/**
 * Reference to an instance of the `Query` type.
 *
 * {@extends voEngineObject}
 * {@subTypes voVocabularyQuery, voStringQuery, voOrQuery, voAndQuery, voAndNotQuery, voNearQuery}
 *
 * @see VO_Query.
 */
typedef voEngineObject voQuery;

/**
 * Reference to an instance of the `VocabularyQuery` type.
 *
 * {@extends voQuery}
 *
 * @see VO_VocabularyQuery, voCreateVocabularyQuery.
 */
typedef voQuery voVocabularyQuery;

/**
 * Reference to an instance of the `StringQuery` type.
 *
 * {@extends voQuery}
 *
 * @see VO_StringQuery, voCreateStringQuery.
 */
typedef voQuery voStringQuery;

/**
 * Reference to an instance of the `OrQuery` type.
 *
 * {@extends voQuery}
 *
 * @see VO_OrQuery, voCreateBinaryQuery.
 */
typedef voQuery voOrQuery;

/**
 * Reference to an instance of the `AndQuery` type.
 *
 * {@extends voQuery}
 *
 * @see VO_AndQuery, voCreateBinaryQuery.
 */
typedef voQuery voAndQuery;

/**
 * Reference to an instance of the `AndNotQuery` type.
 *
 * {@extends voQuery}
 *
 * @see VO_AndNotQuery, voCreateBinaryQuery.
 */
typedef voQuery voAndNotQuery;

/**
 * Reference to an instance of the `NearQuery` type.
 *
 * {@extends voQuery}
 *
 * @see VO_NearQuery, voCreateBinaryQuery.
 */
typedef voQuery voNearQuery;

/**
 * Initializer to be used when creating a `VocabularyQuery` object
 * using the `voCreateObjectEx` function.
 */
typedef struct _voVocabularyQueryInitializer
  {
    /**
     * Vocabulary.
     */
    voVocabulary vocabulary;
  }
  voVocabularyQueryInitializer;

/**
 * Initializer to be used when creating a `StringQuery` object using
 * the `voCreateObjectEx` function.
 */
typedef struct _voStringQueryInitializer
{
  /**
   * Charset.
   */
  voCharset charset;
  /**
   * String.
   */
  const voString* string;
  /**
   * Case sensitivity.
   */
  bool matchCase;
  /**
   * Accent sensitivity.
   */
  bool matchAccent;
  /**
   * Interpret, or not, wildcards characters: '?' (any character) and
   * '*' (any character, any number of times).
   */
  bool interpretWildcards;
}
voStringQueryInitializer;

/**
 * Initializer to be used when creating a binary `Query` object
 * (`OrQuery`, `AndQuery`, `AndNotQuery`,
 *  `NearQuery`) using the `voCreateObjectEx` function.
 */
typedef struct _voBinaryQueryInitializer
{
  /**
   * First query.
   */
  voQuery query1;
  /**
   * Second query.
   */
  voQuery query2;
}
voBinaryQueryInitializer;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `VocabularyQuery` type.
 *
 * @param engine Reference to an `Engine` instance.
 * @param vocabulary Reference to a `Vocabulary` instance.
 *
 * @return A reference to the newly created `VocabularyQuery` object
 *   on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_NO_SUCH_OBJECT The `vocabulary` reference is invalid.
 * @throws VO_INVALID_OBJECT The `vocabulary` reference is not a
 *   reference to a `VocabularyQuery` instance.
 * @throws VO_NOT_COMPILED The `vocabulary` object is not compiled.
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 * @throws VO_LIMIT_EXCEEDED The number of `Vocabulary` instances
 *   would exceed the allowed limit (please remember that the limit can be
 *   shared among several types).
 */
VO_INLINE voVocabularyQuery voCreateVocabularyQuery(voEngine engine, voVocabulary vocabulary)
{
  voVocabularyQueryInitializer initializer = { vocabulary };
  return voCreateObjectEx(engine, VO_VocabularyQuery, &initializer, sizeof(initializer));
}

/**
 * Creates an instance of the `StringQuery` type.
 *
 * @param engine Reference to an `Engine` instance.
 * @param charset Reference to the `Charset` instance to be used
 *   when decoding the string.
 * @param string Pointer to the string.
 * @param matchCase Case sensitivity.
 * @param matchAccent Accent sensitivity.
 * @param interpretWildcards Interpret, or not, wildcard characters: '?'
 *   (any character) and '*' (any character, any number of times).
 *
 * @return A reference to the created object or NULL on failure.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
 * @throws VO_INVALID_OBJECT The `charset` reference is not a
 *   reference to a `Charset` instance.
 * @throws VO_INVALID_USER_BUFFER The string or its bytes member is not
 *   readable.
 * @throws VO_INVALID_ARGUMENT The string is empty.
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 * @throws VO_LIMIT_EXCEEDED The number of `StringQuery` instances
 *   would exceed the allowed limit (please remember that the limit can be
 *   shared among several types).
 */
VO_INLINE voStringQuery voCreateStringQuery(voEngine engine, voCharset charset, const voString* string, bool matchCase, bool matchAccent, bool interpretWildcards)
{
  voStringQueryInitializer initializer = { charset, string, matchCase, matchAccent, interpretWildcards };
  return voCreateObjectEx(engine, VO_StringQuery, &initializer, sizeof(initializer));
}

/**
 * Creates a new binary `Query` object of the specified type.
 *
 * @param engine Reference to an `Engine` instance.
 * @param type The type of the `Query` object to be created:
 *   `VO_OrQuery`, `VO_AndQuery`,
 *   `VO_AndNotQuery` or `VO_NearQuery`.
 * @param query1 Reference to the first query.
 * @param query2 Reference to the second query.
 *
 * @return A reference to the newly created binary `Query` object on
 *   success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_NO_SUCH_TYPE The specified type is invalid.
 * @throws VO_TYPE_NOT_CONCRETE The specified type is not concrete.
 * @throws VO_NO_SUCH_CONSTRUCTOR The specified type does not have a
 *   constructor with the given initializer.
 * @throws VO_INVALID_SIZE The type of the given initializer does not have the
 *   right size.
 * @throws VO_NO_SUCH_OBJECT One of the `query1` or
 *   `query2` references is invalid.
 * @throws VO_INVALID_OBJECT One of the `query1` or
 *   `query2` objects is not an instance of query.
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 * @throws VO_LIMIT_EXCEEDED The number of `Query` instances would
 *   exceed the allowed limit (please remember that the limit can be shared
 *   among several types).
 */
VO_INLINE voQuery voCreateBinaryQuery(voEngine engine, voTypeId type, voQuery query1, voQuery query2)
{
  voBinaryQueryInitializer initializer = { query1, query2 };
  return voCreateObjectEx(engine, type, &initializer, sizeof(initializer));
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- Finder -------------------------------------------------------------------

/**
 * Reference to an instance of the `Finder` type.
 *
 * {@extends voEngineObject}
 * {@implements voIAttachTarget, voIRunnable, voIFindResultProvider}
 * {@properties VO_FINDER_PROP}
 *
 * @see VO_Finder, voCreateFinder.
 */
typedef voEngineObject voFinder;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `Finder` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `Finder` object on
 *   success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `Finder` instances would
 *   exceed the allowed limit (please remember that the limit can be shared
 *   among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voFinder voCreateFinder(voEngine engine)
{
  return voCreateObject(engine, VO_Finder);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS

/**
 * {@propertySet Finder}
 */
enum VO_FINDER_PROP
{
  /**
   * Value between `0` and `1`, below which occurrences
   * are rejected. The default value is `0.3f`.
   *
   * {@property float}
   */
  VO_FIND_SCORE_THRESHOLD = (VO_Finder << 16)
};


// -- FindResult ---------------------------------------------------------------

/**
 * Reference to an instance of the `FindResult` type.
 *
 * {@extends voEngineObject}
 * {@implements voIFindResult}
 *
 * @see VO_FindResult.
 */
typedef voEngineObject voFindResult;

/**
 * Reference to an instance of the `OccurrenceIterator` type.
 *
 * {@extends voIterator}
 * {@implements voIOccurrenceIterator}
 *
 * @see VO_OccurrenceIterator.
 */
typedef voIterator voOccurrenceIterator;

/**
 * Reference to an instance of the `OccurrenceCharacterIterator`
 * type.
 *
 * {@extends voIterator}
 * {@implements voIOccurrenceCharacterIterator}
 *
 * @since 4.1.0
 *
 * @see VO_OccurrenceCharacterIterator.
 */
typedef voIterator voOccurrenceCharacterIterator;

/**
 * Functions composing the `IFindResultProvider` interface.
 *
 * {@implementingTypes voFinder}
 */
typedef struct _voIFindResultProvider
{
  /**
   * Returns the find result associated with the target object.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   *
   * @returns A `FindResult` instance on success,
   *   otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement the `ICompilable` interface.
   * @throws VO_LIMIT_EXCEEDED The number of `FindResult`
   *   instances would exceed the allowed limit (please remember that the limit
   *   can be shared among several types).
   */
  voFindResult (VO_MSE_CALL *getResult)(voEngine engine, voEngineObject target);
}
voIFindResultProvider;

/**
 * Functions composing the `IFindResult` interface. This interface
 * exposes the public methods of the `FindResult` type.
 *
 * {@implementingTypes voFindResult}
 * @see VO_IFindResult, VO_FindResult.
 */
typedef struct _voIFindResult
{
  /**
   * Returns the global search result score, which is a combination of
   * all the occurrence scores. Varies from 0.0 (low probability) to 1.0
   * (high probability).
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `FindResult` instance.
   *
   * @return the global search score on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `FindResult` instance.
   */
  float (VO_MSE_CALL *getGlobalScore)(voEngine engine, voFindResult target);

  /**
   * Returns an iterator over the different occurrences.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `FindResult` instance.
   *
   * @return an `OccurrenceIterator` instance on success, otherwise
   *   `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `FindResult` instance.
   * @throws VO_OUT_OF_MEMORY Not enough memory to create the
   *   `OccurrenceIterator` instance.
   * @throws VO_LIMIT_EXCEEDED The number of `OccurrenceIterator`
   *   instances would exceed the allowed limit (please remember that the limit
   *   can be shared among several types).
   */
  voOccurrenceIterator (VO_MSE_CALL *getOccurrences)(voEngine engine, voFindResult target);
}
voIFindResult;

/**
 * Functions composing the `IOccurrenceIterator` interface. This
 * interface exposes the public methods of the `OccurrenceIterator`
 * type.
 *
 * {@extends voIIterator}
 * {@implementingTypes voOccurrenceIterator}
 * @see VO_IOccurrenceIterator, VO_OccurrenceIterator.
 *
 * @note As the C language does not provide any mechanism that could be used to
 *   simulate inheritance, inherited members are simply copied from the base
 *   structure.
 */
typedef struct _voIOccurrenceIterator
{
  /** {@inheritDoc} */
  voYesNo (VO_MSE_CALL *isAtEnd)(voEngine engine, voIterator target);
  /** {@inheritDoc} */
  bool (VO_MSE_CALL *next)(voEngine engine, voIterator target);

  /**
   * Returns the label of this occurrence.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `OccurrenceIterator` instance.
   * @param charset Reference to the `Charset` instance to be used
   *   to convert the MyScript internal characters into a character string.
   * @param string Recipient for the label.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to an `OccurrenceIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT The iterator is positioned at the end of the
   *   iteration.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_INVALID_OBJECT The `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER The string recipient is not readable or
   *   writable.
   */
  bool (VO_MSE_CALL *getLabel)(voEngine engine, voOccurrenceIterator target, voCharset charset, voString* string);

  /**
   * Returns the score of this occurrence.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `OccurrenceIterator` instance.
   *
   * @return the score of this occurrence on success, otherwise
   *   `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to an `OccurrenceIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT The iterator is positioned at the end of the
   *   iteration.
   */
  float (VO_MSE_CALL *getScore)(voEngine engine, voOccurrenceIterator target);

  /**
   * Returns the range in the input of this occurrence.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `OccurrenceIterator` instance.
   * @param range Recipient for the result.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to an `OccurrenceIterator` instance.
   * @throws VO_INVALID_ARGUMENT The given range count exceeds the range count
       of this occurrence.
   * @throws VO_INVALID_USER_BUFFER The given range points to an unreadable
   *   memory location.
   * @throws VO_NO_SUCH_ELEMENT The iterator is positioned at the end of the
   *   iteration.
   */
  bool (VO_MSE_CALL *getInputRange)(voEngine engine, voOccurrenceIterator target, voInputRange* range);

  /**
   * Returns the index of the search unit that contains the occurrence.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `OccurrenceIterator` instance.
   *
   * @return the search unit of this occurrence on success, otherwise
   *   `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to an `OccurrenceIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT The iterator is positioned at the end of the
   *   iteration.
   */
  short (VO_MSE_CALL *getSearchUnit)(voEngine engine, voOccurrenceIterator target);

  /**
   * Returns an iterator over the different characters of this occurrence.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `OccurrenceIterator` instance.
   *
   * @return an `OccurrenceCharacterIterator` instance on success,
   *   otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to an `OccurrenceIterator` instance.
   * @throws VO_OUT_OF_MEMORY Not enough memory to create the iterator.
   * @throws VO_NO_SUCH_ELEMENT The iterator is positioned at the end of the
   *  iteration.
   * @throws VO_LIMIT_EXCEEDED The number of
   *   `OccurrenceCharacterIterator` instances would exceed the
   *   allowed limit (please remember that the limit can be shared among several
   *   types).
   *
   * @since 4.1.0
   */
  voOccurrenceCharacterIterator (VO_MSE_CALL *getCharacters)(voEngine engine, voOccurrenceIterator target);

  /**
   * Returns the zero-based index of the matched query.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `OccurrenceIterator` instance.
   *
   * @return the zero-based index of the matched query on success, otherwise
   *   `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to an `OccurrenceIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT The iterator is positioned at the end of the
   *   iteration.
   *
   * @since 4.4.0
   */
  int (VO_MSE_CALL *getQueryIndex)(voEngine engine, voOccurrenceIterator target);
}
voIOccurrenceIterator;

/**
 * Functions composing the `IOccurrenceCharacterIterator` interface.
 * This interface exposes the public methods of the
 * `OccurrenceCharacterIterator` type.
 *
 * {@extends voIIterator}
 * {@implementingTypes voOccurrenceCharacterIterator}
 * @see VO_IOccurrenceCharacterIterator, VO_OccurrenceCharacterIterator.
 *
 * @note As the C language does not provide any mechanism that could be used to
 *   simulate inheritance, inherited members are simply copied from the base
 *   structure.
 *
 * @since 4.1.0
 */
typedef struct _voIOccurrenceCharacterIterator
  {
    /** {@inheritDoc} */
    voYesNo (VO_MSE_CALL *isAtEnd)(voEngine engine, voIterator target);
    /** {@inheritDoc} */
    bool (VO_MSE_CALL *next)(voEngine engine, voIterator target);

    /**
     * Returns the label of this character occurrence.
     *
     * @param engine Reference to an `Engine` instance.
     * @param target Reference to an `OccurrenceCharacterIterator`
     *   instance.
     * @param charset Reference to the `Charset` instance to be used
     *   to convert the MyScript internal characters into a character string.
     * @param string Recipient for the label.
     *
     * @return `true` on success, otherwise `false`.
     *
     * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
     * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
     * @throws VO_INVALID_OPERATION The `target` reference is not a
     *   reference to an `OccurrenceCharacterIterator` instance.
     * @throws VO_NO_SUCH_ELEMENT The iterator is positioned at the end of
     *   the iteration.
     * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
     * @throws VO_INVALID_OBJECT The `charset` reference is not a
     *   reference to a `Charset` instance.
     * @throws VO_INVALID_USER_BUFFER The string recipient is not readable or
     *   writable.
     * @throws VO_INVALID_USER_BUFFER The bytes member of the string recipient
     *   is not writable.
     */
    bool (VO_MSE_CALL *getLabel)(voEngine engine, voOccurrenceCharacterIterator target, voCharset charset, voString* string);

    /**
     * Returns the range in the input of this character occurrence.
     *
     * @param engine Reference to an `Engine` instance.
     * @param target Reference to an `OccurrenceCharacterIterator`
     *   instance.
     * @param range Recipient for the result.
     *
     * @return `true` on success, otherwise `false`.
     *
     * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
     * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
     * @throws VO_INVALID_OPERATION The `target` reference is not a
     *   reference to an `OccurrenceIterator` instance.
     * @throws VO_INVALID_ARGUMENT The given range count exceeds the range count
         of this occurrence.
     * @throws VO_INVALID_USER_BUFFER The given range points to an unreadable
     *   memory location.
     * @throws VO_NO_SUCH_ELEMENT The iterator is positioned at the end of
     *   the iteration.
     */
    bool (VO_MSE_CALL *getInputRange)(voEngine engine, voOccurrenceCharacterIterator target, voInputRange* range);
  }
  voIOccurrenceCharacterIterator;

#endif // end of: #ifndef C_MYSCRIPTINKSEARCH_H
