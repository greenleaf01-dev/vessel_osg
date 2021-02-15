#ifndef C_MYSCRIPTJSON_H
#define C_MYSCRIPTJSON_H 0x06010000
/**
 * @file c/MyScriptJSON.h
 * Native interface to the MyScriptJSON service. Please note that the
 * implementation of MyScriptJSON is delivered as part of the MyScriptEngine
 * library.
 */

#include "MyScriptEngine.h"


// -- types and interfaces -----------------------------------------------------

/**
 * Lists the MyScriptJSON types.
 */
enum VO_JSON_T
{
  /**
   * Identifier of the `Json` type.
   * @see voJson.
   */
  VO_Json = 3000,
  /**
   * Identifier of the `JsonObjectIterator` type.
   * @see voJsonObjectIterator.
   */
  VO_JsonObjectIterator
};


/**
 * Lists the MyScriptJSON interfaces.
 */
enum VO_JSON_I
{
  /**
   * Identifier of the `IJson` interface.
   * @see voIJson.
   */
  VO_IJson = 3002,

  /**
   * Identifier of the `IJsonObjectIterator` interface.
   * @see voIJsonObjectIterator.
   */
  VO_IJsonObjectIterator
};


/**
 * Reference to an instance of the `Json` type.
 *
 * {@extends voEngineObject}
 * {@implements voIJson}
 */
typedef voEngineObject voJson;

/**
 * Reference to an instance of the `JsonObjectIterator` type.
 *
 * {@extends voIterator}
 * {@implements voIJsonObjectIterator}
 */
typedef voIterator voJsonObjectIterator;

/**
 * Represents the type of a JSON value.
 */
typedef enum _voJsonType
{
  VO_JSON_ERR = -1, /**< Error marker. */

  VO_JSON_NULL,     /**< The JSON value null. */
  VO_JSON_STRING,   /**< A JSON string value. */
  VO_JSON_NUMBER,   /**< A JSON number value. */
  VO_JSON_BOOLEAN,  /**< A JSON boolean value. */
  VO_JSON_OBJECT,   /**< A JSON object value. */
  VO_JSON_ARRAY     /**< A JSON array value. */
}
voJsonType;

/**
 * Functions composing the `IJson` interface.
 *
 * {@implementingTypes voJson}
 * @see VO_IJson, VO_Json.
 */
typedef struct _voIJson
{
  /**
   * Returns type of a JSON value.
   *
   * @param engine the engine.
   * @param target the target JSON value.
   *
   * @return the type of the JSON value on success, otherwise `VO_JSON_ERR`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION if `target` is not a `voJson`.
   */
  voJsonType (VO_MSE_CALL *getType)(voEngine engine, voJson target);

  /**
   * Creates a new JSON null value.
   *
   * @param engine the engine.
   *
   * @return the newly created JSON null value on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   */
  voJson (VO_MSE_CALL *createNull)(voEngine engine);

  /**
   * Creates a new JSON string.
   *
   * @param engine the engine.
   * @param charset the charset to be used to decode value.
   * @param value the string value.
   *
   * @return the newly created JSON string on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `value` string is not readable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the
   *   `value` string is not readable.
   */
  voJson (VO_MSE_CALL *createString)(voEngine engine, voCharset charset, const voString* value);

  /**
   * Creates a new JSON number.
   *
   * @param engine the engine.
   * @param value the number value.
   *
   * @return the newly created JSON number on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   */
  voJson (VO_MSE_CALL *createNumber)(voEngine engine, double value);

  /**
   * Creates a new JSON boolean.
   *
   * @param engine the engine.
   * @param value the value of the object to create.
   *
   * @return the newly created JSON number on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   */
  voJson (VO_MSE_CALL *createBoolean)(voEngine engine, bool value);

  /**
   * Creates a new JSON object.
   *
   * @param engine the engine.
   *
   * @return the newly created JSON object on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   */
  voJson (VO_MSE_CALL *createObject)(voEngine engine);

  /**
   * Creates a new JSON array.
   *
   * @param engine the engine.
   *
   * @return the newly created JSON array on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   */
  voJson (VO_MSE_CALL *createArray)(voEngine engine);

  /**
   * Parses the given input string as JSON.
   *
   * @param engine the engine.
   * @param charset the charset to be used to decode input.
   * @param input the input JSON string.
   *
   * @return the JSON value on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `input` string is not readable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the
   *   `input` string is not readable.
   * @throws VO_INVALID_ARGUMENT the input is not valid JSON.
   */
  voJson (VO_MSE_CALL *parse)(voEngine engine, voCharset charset, const voString* input);

  /**
   * Returns the value of a JSON string.
   *
   * @param engine the engine.
   * @param target the target JSON string.
   * @param charset the charset to be used to encode the value.
   * @param value a recipient for the value.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `Json` instance of type VO_JSON_STRING.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `value` recipient is not
   *   readable or writable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the
   *   `value` recipient is not writable.
   */
  bool (VO_MSE_CALL *getStringValue)(voEngine engine, voJson target, voCharset charset, voString* value);

  /**
   * Returns the value of a JSON number.
   *
   * @param engine the engine.
   * @param target the target JSON number.
   * @param value a recipient for the value.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `Json` instance of type VO_JSON_NUMBER.
   * @throws VO_INVALID_USER_BUFFER the `value` recipient is not
   *   readable or writable.
   */
  bool (VO_MSE_CALL *getNumberValue)(voEngine engine, voJson target, double* value);

  /**
   * Returns the value of a JSON boolean.
   *
   * @param engine the engine.
   * @param target the target JSON boolean.
   * @param value a recipient for the value.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `Json` instance of type VO_JSON_BOOLEAN.
   * @throws VO_INVALID_USER_BUFFER the `value` recipient is not
   *   readable or writable.
   */
  bool (VO_MSE_CALL *getBooleanValue)(voEngine engine, voJson target, bool* value);

  /**
   * Returns an iterator over the entries of a JSON object. Note that
   * MyScriptJSON keeps the insertion order for entries iteration.
   *
   * @param engine the engine.
   * @param target the target JSON object.
   *
   * @return the iterator on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `Json` instance of type VO_JSON_OBJECT.
   */
  voJsonObjectIterator (VO_MSE_CALL *getObjectEntries)(voEngine engine, voJson target);

  /**
   * Returns the value associated with the specified key within a JSON object.
   *
   * @param engine the engine.
   * @param target the target JSON object.
   * @param charset the charset to be used to decode key.
   * @param key the key to lookup for.
   *
   * @return the value associated with the key, if any.
   *   When `NULL`, use `voGetError()` to figure out whether an error occured.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `Json` instance of type VO_JSON_OBJECT.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `key` string is not readable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the
   *   `key` string is not readable.
   * @throws VO_INVALID_ARGUMENT the `key` string is empty.
   */
  voJson (VO_MSE_CALL *getObjectEntryValue)(voEngine engine, voJson target, voCharset charset, const voString* key);

  /**
   * Puts a new association in a JSON object. Any former value is erased.
   *
   * @param engine the engine.
   * @param object the target JSON object.
   * @param charset the charset to be used to decode key.
   * @param key the key to which the value should be associated.
   * @param value the JSON value.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `object` reference is invalid.
   * @throws VO_INVALID_OPERATION the `object` reference is not a
   *   reference to a `Json` instance of type VO_JSON_OBJECT.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `key` string is not readable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the
   *   `key` string is not readable.
   * @throws VO_INVALID_ARGUMENT the `key` string is empty.
   * @throws VO_INVALID_OBJECT the `value` reference is not a
   *   reference to a `voJson` instance.
   */
  bool (VO_MSE_CALL *putObjectEntry)(voEngine engine, voJson object, voCharset charset, const voString* key, voJson value);

  /**
   * Removes an association from a JSON object.
   *
   * @param engine the engine.
   * @param object the target JSON object.
   * @param charset the charset to be used to decode key.
   * @param key the key of the association to remove.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `object` reference is invalid.
   * @throws VO_INVALID_OPERATION the `object` reference is not a
   *   reference to a `Json` instance of type VO_JSON_OBJECT.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `key` string is not readable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the
   *   `key` string is not readable.
   * @throws VO_INVALID_ARGUMENT the `key` string is empty.
   */
  bool (VO_MSE_CALL *removeObjectEntry)(voEngine engine, voJson object, voCharset charset, const voString* key);

  /**
   * Returns the number of elements within a JSON array.
   *
   * @param engine the engine.
   * @param target the target JSON array.
   *
   * @return the number of elements in the array on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `Json` instance of type VO_JSON_ARRAY.
   */
  int (VO_MSE_CALL *getArrayLength)(voEngine engine, voJson target);

  /**
   * Returns the element at the specified index in a JSON array.
   *
   * @param engine the engine.
   * @param target the target JSON array.
   * @param index the index of the element to retrieve.
   *
   * @return the element at the specified index on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `Json` instance of type VO_JSON_ARRAY.
   * @throws VO_INDEX_OUT_OF_BOUNDS the `index` is invalid.
   */
  voJson (VO_MSE_CALL *getArrayValueAt)(voEngine engine, voJson target, int index);

  /**
   * Inserts an element to a JSON array. If the given index is valid then the
   * value is be placed at the given position and the existing values starting
   * from the index are shifted up. If the given index is `-1` the value is
   * inserted at the end of the array.
   *
   * @param engine the engine.
   * @param array the target JSON array.
   * @param index the index at which to place the new value.
   * @param value the JSON value to insert.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `object` reference is invalid.
   * @throws VO_INVALID_OPERATION the `object` reference is not a
   *   reference to a `Json` instance of type VO_JSON_ARRAY.
   * @throws VO_INDEX_OUT_OF_BOUNDS the `index` is not valid nor `-1`.
   * @throws VO_INVALID_OBJECT the `value` reference is not a
   *   reference to a `voJson` instance.
   */
  bool (VO_MSE_CALL *insertArrayValueAt)(voEngine engine, voJson array, int index, voJson value);

  /**
   * Removes the element at the specified position from a JSON array.
   *
   * @param engine the engine.
   * @param array the target JSON array.
   * @param index the index of the element to remove.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `object` reference is invalid.
   * @throws VO_INVALID_OPERATION the `object` reference is not a
   *   reference to a `Json` instance of type VO_JSON_ARRAY.
   * @throws VO_INDEX_OUT_OF_BOUNDS the `index` is not valid.
   */
  bool (VO_MSE_CALL *removeArrayValueAt)(voEngine engine, voJson array, int index);

  /**
   * Creates a new JSON string and fills it with the string representation of a
   * timestamp.
   *
   * @param engine the engine.
   * @param timestamp the timestamp, expressed in microseconds elapsed since
   *   the EPOCH.
   *
   * @return the newly created JSON string on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_INVALID_ARGUMENT the `timestamp` value is negative.
   */
  voJson (VO_MSE_CALL *createStringFromTimestamp)(voEngine engine, int64_t timestamp);

  /**
   * Returns the value of a JSON string, parsed as a timestamp string.
   *
   * @param engine the engine.
   * @param target the target JSON string.
   * @param timestamp the recipient for the timestamp, expressed in microseconds
   *   elapsed since the EPOCH.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `Json` instance of type VO_JSON_STRING.
   * @throws VO_INVALID_USER_BUFFER the `timestamp` is not writable.
   * @throws VO_INVALID_STATE the `target` string does not match the timestamp
   *   format.
   */
  bool (VO_MSE_CALL *getStringValueAsTimestamp)(voEngine engine, voJson target, int64_t* timestamp);
}
voIJson;

/**
 * Functions composing the `IJsonObjectIterator` interface. This interface
 * exposes the public methods of the `JsonObjectIterator` type.
 *
 * {@extends voIIterator}
 * {@implementingTypes voJsonObjectIterator}
 * @see VO_IJsonObjectIterator, VO_JsonObjectIterator.
 */
typedef struct _voIJsonObjectIterator
{
  /** {@inheritDoc} */
  voYesNo (VO_MSE_CALL *isAtEnd)(voEngine engine, voIterator target);
  /** {@inheritDoc} */
  bool (VO_MSE_CALL *next)(voEngine engine, voIterator target);

  /**
   * Returns the key of the JSON object entry at the current step of the
   * iteration.
   *
   * @param engine the engine.
   * @param target the target JSON object iterator.
   * @param charset the charset to be used to encode the key.
   * @param key a recipient for the key.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `JsonObjectIterator` instance.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `key` recipient is not
   *   readable or writable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the
   *   `key` recipient is not writable.
   */
  bool (VO_MSE_CALL *getKey)(voEngine engine, voJsonObjectIterator target, voCharset charset, voString* key);

  /**
   * Returns the value of the JSON object entry at the current step of the
   * iteration.
   *
   * @param engine the engine.
   * @param target the target JSON object iterator.
   *
   * @return the JSON value on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `JsonObjectIterator` instance.
   */
  voJson (VO_MSE_CALL *getValue)(voEngine engine, voJsonObjectIterator target);
}
voIJsonObjectIterator;

#endif // end of: #ifndef C_MYSCRIPTJSON_H
