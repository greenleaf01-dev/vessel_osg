#ifndef C_MYSCRIPTEQUATION_H
#define C_MYSCRIPTEQUATION_H 0x06010000
/**
 * @file c/MyScriptEquation.h
 * Native interface to the MyScript Equation service.
 */

#include "MyScriptEngine.h"


// -- error codes --------------------------------------------------------------

/**
 * Lists the MyScript Equation errors.
 */
enum VO_EQUATION_ERR
{
  /**
   * Unable to complete the requested operation because an
   * `EquationAlphabetKnowledge` is missing.
   *
   * @see voEquationAlphabetKnowledge.
   */
  VO_MISSING_EQUATION_ALPHABET_KNOWLEDGE = VO_INVALID_STATE | (5 << 16),

  /**
   * Unable to complete the requested operation because an
   * `EquationGrammar` is missing.
   *
   * @see voEquationGrammar.
   * @see voIAttachTarget.
   */
  VO_MISSING_EQUATION_GRAMMAR
};


// -- types and interfaces -----------------------------------------------------

/**
 * Lists the MyScript Equation types.
 *
 * @see enum VO_EQUATION_ELEMENT_T.
 */
enum VO_EQUATION_T
{
  /**
   * `Equation` type.
   *
   * @see voEquation.
   */
  VO_Equation = 5000,
  /**
   * `EquationAlphabetKnowledge` type.
   *
   * @see voEquationAlphabetKnowledge.
   */
  VO_EquationAlphabetKnowledge,
  /**
   * `EquationGrammar` type.
   *
   * @see voEquationGrammar.
   */
  VO_EquationGrammar,
  /**
   * `EquationRecognizer` type.
   *
   * @see voEquationRecognizer.
   */
  VO_EquationRecognizer,
  /**
   * `EquationNode` type.
   *
   * @see voEquationNode.
   */
  VO_EquationNode = 8001,
  /**
   * `EquationTerminalNode` type.
   *
   * @see voEquationTerminalNode.
   */
  VO_EquationTerminalNode = 5005,
  /**
   * `EquationNonTerminalNode` type.
   *
   * @see voEquationNonTerminalNode.
   */
  VO_EquationNonTerminalNode,
  /**
   * `EquationRuleNode` type.
   *
   * @see voEquationRuleNode.
   */
  VO_EquationRuleNode,
  /**
   * `EquationScratchOut` type.
   *
   * @see voEquationScratchOut.
   *
   * @since 6.1_0
   */
  VO_EquationScratchOut
};

/**
 * Lists the MyScript Equation interfaces.
 */
enum VO_EQUATION_I
{
  /**
   * `IEquation` interface type.
   *
   * @see voIEquation.
   */
  VO_IEquation = 5100,
  /**
   * `IEquationAlphabet` interface type.
   *
   * @see voIEquationAlphabet.
   */
  VO_IEquationAlphabet,
  /**
   * `IEquationGrammar` interface type.
   *
   * @see voIEquationGrammar.
   */
  VO_IEquationGrammar,
  /**
   * `IEquationRecognizer` interface type.
   *
   * @see voIEquationRecognizer.
   */
  VO_IEquationRecognizer,

  /**
   * `IEquationTerminalNode` interface type.
   *
   * @see voIEquationTerminalNode.
   */
  VO_IEquationTerminalNode,

  /**
   * `IEquationNonTerminalNode` interface type.
   *
   * @see voIEquationNonTerminalNode.
   */
  VO_IEquationNonTerminalNode,

  /**
   * `IEquationRuleNode` interface type.
   *
   * @see voIEquationRuleNode.
   */
  VO_IEquationRuleNode,

  /**
   * `IEquationScratchOut` interface type.
   *
   * @see voIEquationScratchOut.
   *
   * @since 6.1_0
   */
  VO_IEquationScratchOut
};


// -- EquationNode -------------------------------------------------------------

/**
 * Reference to an instance of the `EquationNode` type.
 */
typedef voEngineObject voEquationNode;

/**
 * {@typePropertySet EquationNode}
 */
enum VO_EQUATION_NODE_TPROP
{
  /**
   * Represents the maximum number of `EquationNode` instances that can exist at
   * the same time in the user side of a MyScript enable application.
   * The special value zero means no limit. Other values are adjusted to the
   * next multiple of 16. A value under the current count is permitted and will
   * constrain future resource creations.
   *
   * {@property uint32_t}
   */
  VO_USER_EQUATION_NODE_LIMIT = VO_USER_OBJ_LIMIT,
  /**
   * Gives the number of `EquationNode` instances that currently
   * exist in the user side of a MyScript enabled application.
   *
   * {@property read-only uint32_t}
   */
  VO_USER_EQUATION_NODE_COUNT = VO_USER_OBJ_COUNT
};


// -- EquationScratchOut -------------------------------------------------------

/**
 * Reference to an instance of the `EquationScratchOut` type.
 *
 * {@implements voIEquationScratchOut}
 *
 * @since 6.1_0
 */
typedef voEngineObject voEquationScratchOut;


// -- Equation -----------------------------------------------------------------

/**
 * Reference to an instance of the `Equation` type.
 *
 * {@implements voIEquation}
 */
typedef voEngineObject voEquation;

/**
 * Functions composing the `IEquation` interface. This interface exposes the
 * public methods of the `Equation` type.
 *
 * {@implementingTypes voEquation}
 * @see VO_IEquation, VO_Equation.
 */
typedef struct _voIEquation
{
  /**
   * Clears this `Equation` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `Equation` instance.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `Equation` instance.
   */
  bool (VO_MSE_CALL *clear)(voEngine engine, voEquation target);

  /**
   * Adds a digital pen stroke to this `Equation` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `Equation` instance.
   * @param x Pointer to the first x value.
   * @param xByteStride Stride in bytes between each x value.
   * @param y Pointer to the first y value.
   * @param yByteStride Stride in bytes between each y value.
   * @param pointCount Number of points.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `Equation` instance.
   * @throws VO_INVALID_ARGUMENT When `xByteStride == 0`
   * @throws VO_INVALID_ARGUMENT When `yByteStride == 0`
   * @throws VO_INVALID_ARGUMENT When `pointCount == 0`
   * @throws VO_INVALID_USER_BUFFER The combination of `x`,
   *   `xByteStride`, `y`, `yByteStride` and
   *   `pointCount` leads to invalid memory access.
   * @throws VO_LIMIT_EXCEEDED When `pointCount > 32767`
   */
  bool (VO_MSE_CALL *addStroke)(voEngine engine, voEquation target, const float* x, size_t xByteStride, const float* y, size_t yByteStride, int32_t pointCount);

  /**
   * Adds a digital text character with respect to its position in this
   * `Equation` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `Equation` instance.
   * @param character Reference to the `InputCharacter` to be added.
   * @param x The x position of the enclosing rectangle of the character.
   * @param y The y position of the enclosing rectangle of the character.
   * @param width The width of the enclosing rectangle of the character.
   * @param height The height of the enclosing rectangle of the character.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `Equation` instance.
   * @throws VO_NO_SUCH_OBJECT The `character` reference is invalid.
   * @throws VO_INVALID_OBJECT The `character` object is not an instance of the
   *   `InputCharacter` type.
   * @throws VO_INVALID_ARGUMENT The `character` contains no alternate.
   * @throws VO_INVALID_ARGUMENT The `width` is less than or equal to 0.
   * @throws VO_INVALID_ARGUMENT The `height` is less than or equal to 0.
   */
  bool (VO_MSE_CALL *addCharacter)(voEngine engine, voEquation target, voInputCharacter character, float x, float y, float width, float height);

  /**
   * Deletes a component from this `Equation` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `Equation` instance.
   * @param index The component index to delete
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `Equation` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   *
   * @since 5.0_0
   */
  bool (VO_MSE_CALL *deleteComponentAt)(voEngine engine, voEquation target, int32_t index);

  /**
   * Undeletes a component from this `Equation` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `Equation` instance.
   * @param index The component index to undelete
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `Equation` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   *
   * @since 5.0_0
   */
  bool (VO_MSE_CALL *undeleteComponentAt)(voEngine engine, voEquation target, int32_t index);

  /**
   * Tells whether this `Equation` instance has an associated parse tree.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `Equation` instance.
   *
   * @return `VO_YES` or `VO_NO` on success, otherwise `VO_ERR` on failure.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `Equation` instance.
   */
  voYesNo (VO_MSE_CALL *hasParseTree)(voEngine engine, voEquation target);

  /**
   * Returns the root node of the parse tree after this `Equation` instance has
   * been processed.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `Equation` instance.
   *
   * @return An `EquationNode` instance on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `Equation` instance.
   * @throws VO_LIMIT_EXCEEDED The number of `EquationNode` instances would
   *   exceed the allowed limit. (please remember that the limit can be shared
   *   by several types).
   * @throws VO_INVALID_STATE The `Equation` has no associated parse tree.
   */
  voEquationNode (VO_MSE_CALL *getParseTree)(voEngine engine, voEquation target);

  /**
   * Returns the number of active scratch outs after this `Equation` instance
   * has been processed.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `Equation` instance.
   *
   * @return The number of active scratch outs on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `Equation` instance.
   *
   * @since 6.1_0
   */
  int32_t (VO_MSE_CALL *getScratchOutCount)(voEngine engine, voEquation target);

  /**
   * Returns the scratch out at the specified index after this `Equation`
   * instance has been processed.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `Equation` instance.
   * @param index The zero-based index of the scratch out to be retrieved.
   * @param target Reference to an `Equation` instance.
   *
   * @return An `EquationScratchOut` instance on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `Equation` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   *
   * @since 6.1_0
   */
  voEquationScratchOut (VO_MSE_CALL *getScratchOutAt)(voEngine engine, voEquation target, int32_t index);
}
voIEquation;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `Equation` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `Equation` object on success,
 *   otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `Equation` instances would exceed the
 *   allowed limit. (please remember that the limit can be shared by several
 *   types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voEquation voCreateEquation(voEngine engine)
{
  return voCreateObject(engine, VO_Equation);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- EquationAlphabetKnowledge ------------------------------------------------

/**
 * Reference to an instance of the `EquationAlphabetKnowledge` type.
 *
 * {@implements voIEquationAlphabet}
 */
typedef voEngineObject voEquationAlphabetKnowledge;


// -- IEquationAlphabet --------------------------------------------------------

/**
 * Functions composing the `IEquationAlphabet` interface. The term "alphabet"
 * here denotes a finite set of characters.

 * {@implementingTypes voEquationAlphabetKnowledge}
 */
typedef struct _voIEquationAlphabet
{
  /**
   * Returns the number of characters in this alphabet.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `EngineObject` instance.
   *
   * @return The number of characters in this alphabet on success, otherwise
   *   `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not implement the
   *   `IEquationAlphabet` interface.
   */
  uint32_t (VO_MSE_CALL *getCharacterCount)(voEngine engine, voEngineObject target);

  /**
   * Returns the character at the specified `index`, as a character string.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `EngineObject` instance.
   * @param index Index of the requested character.
   * @param charset Reference to the `Charset` instance to be used to encode the
   *   character string.
   * @param string Recipient for the character string.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not implement the
   *   `IEquationAlphabet` interface.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_INVALID_USER_BUFFER The `string` recipient is not readable or
   *   writable.
   * @throws VO_INVALID_USER_BUFFER The `bytes` member of the `string` recipient
   *   is not writable.
   */
  bool (VO_MSE_CALL *getCharacterAt)(voEngine engine, voEngineObject target, uint32_t index, voCharset charset, voString* string);
}
voIEquationAlphabet;


// -- EquationGrammar ----------------------------------------------------------

/**
 * Reference to an instance of the `EquationGrammar` type.
 *
 * {@implements voIEquationGrammar}
 */
typedef voEngineObject voEquationGrammar;

/**
 * Type of a symbol in an `EquationGrammar`.
 */
typedef voId voEquationSymbol;

typedef struct _voIEquationGrammar
{
  /**
   * Creates a terminal symbol in the `EquationGrammar`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param grammar Reference to the `EquationGrammar` instance.
   * @param charset Reference to the `Charset` instance to be used when decoding
   *   the symbol name and the symbol string.
   * @param name Pointer to the symbol name.
   * @param str Pointer to the terminal string.
   *
   * @return the symbol id on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `grammar` reference is invalid.
   * @throws VO_INVALID_OPERATION The `grammar` reference is not a reference to
   *   an `EquationGrammar` instance.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_INVALID_OBJECT The `charset` reference is not a reference to a
   *   `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER The `name` recipient is not readable.
   * @throws VO_INVALID_USER_BUFFER The `bytes` member of the `name` recipient
   *   is not readable.
   * @throws VO_INVALID_ARGUMENT The `name` is the empty string.
   * @throws VO_INVALID_USER_BUFFER The `str` recipient is not readable.
   * @throws VO_INVALID_USER_BUFFER The `bytes` member of the `str` recipient is
   *   not readable.
   * @throws VO_INVALID_ARGUMENT The `str` is the empty string.
   * @throws VO_LIMIT_EXCEEDED The `str` contains more than 16 characters.
   *
   * @note You can use the `VO_DEFAULT_CHARSET` property to provide the `Engine`
   *   with a default `Charset`. When done, you are allowed to pass `NULL` in
   *   place of a reference to a `Charset`.
   *
   * @see voEngine
   */
  voEquationSymbol (VO_MSE_CALL *createTerminalSymbol)(voEngine engine, voEquationGrammar grammar, voCharset charset, voString* name, voString* str);

  /**
   * Creates a non terminal symbol in the `EquationGrammar`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param grammar Reference to the `EquationGrammar` instance.
   * @param charset Reference to the `Charset` instance to be used when decoding
   *   the symbol name.
   * @param name Pointer to the symbol name.
   *
   * @return the symbol id on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `grammar` reference is invalid.
   * @throws VO_INVALID_OPERATION The `grammar` reference is not a reference to
   *   an `EquationGrammar` instance.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_INVALID_OBJECT The `charset` reference is not a reference to a
   *   `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER The `name` recipient is not readable.
   * @throws VO_INVALID_USER_BUFFER The `bytes` member of the `name` recipient
   *   is not readable.
   * @throws VO_INVALID_ARGUMENT The `name` is the empty string.
   *
   * @note You can use the `VO_DEFAULT_CHARSET` property to provide the `Engine`
   *   with a default `Charset`. When done, you are allowed to pass `NULL` in
   *   place of a reference to a `Charset`.
   *
   * @see voEngine
   */
  voEquationSymbol (VO_MSE_CALL *createNonTerminalSymbol)(voEngine engine, voEquationGrammar grammar, voCharset charset, voString* name);

  /**
   * Adds an identity rule to the `EquationGrammar`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param grammar Reference to the `EquationGrammar` instance.
   * @param targetSymbol id of the target non terminal symbol.
   * @param sourceSymbol id of the source symbol.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `grammar` reference is invalid.
   * @throws VO_INVALID_OPERATION The `grammar` reference is not a reference to
   *   an `EquationGrammar` instance.
   * @throws VO_INVALID_ARGUMENT The `targetSymbol` is not a valid non terminal
   *   symbol in the `EquationGrammar`.
   * @throws VO_INVALID_ARGUMENT The `sourceSymbol` is not a valid symbol in the
   *   `EquationGrammar`.
   */
  bool (VO_MSE_CALL *addIdentityRule)(voEngine engine, voEquationGrammar grammar, voEquationSymbol targetSymbol, voEquationSymbol sourceSymbol);

  /**
   * Adds an horizontal pair rule to the `EquationGrammar`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param grammar Reference to the `EquationGrammar` instance.
   * @param targetSymbol id of the target non terminal symbol.
   * @param leftSymbol id of the left symbol.
   * @param rightSymbol id of the right symbol.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `grammar` reference is invalid.
   * @throws VO_INVALID_OPERATION The `grammar` reference is not a reference to
   *   an `EquationGrammar` instance.
   * @throws VO_INVALID_ARGUMENT The `targetSymbol` is not a valid non terminal
   *   symbol in the `EquationGrammar`.
   * @throws VO_INVALID_ARGUMENT The `leftSymbol` is not a valid symbol in the
   *   `EquationGrammar`.
   * @throws VO_INVALID_ARGUMENT The `rightSymbol` id is not a valid symbol in
   *   the `EquationGrammar`.
   */
  bool (VO_MSE_CALL *addHorizontalPairRule)(voEngine engine, voEquationGrammar grammar, voEquationSymbol targetSymbol, voEquationSymbol leftSymbol, voEquationSymbol rightSymbol);

  /**
   * Adds a fence rule to the `EquationGrammar`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param grammar Reference to the `EquationGrammar` instance.
   * @param targetSymbol id of the target non terminal symbol.
   * @param sourceSymbol id of the source symbol.
   * @param leftSymbol id of the left terminal symbol.
   * @param rightSymbol id of the right terminal symbol.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `grammar` reference is invalid.
   * @throws VO_INVALID_OPERATION The `grammar` reference is not a reference to
   *   an `EquationGrammar` instance.
   * @throws VO_INVALID_ARGUMENT The `targetSymbol` is not a valid non terminal
   *   symbol in the `EquationGrammar`.
   * @throws VO_INVALID_ARGUMENT The `sourceSymbol` is not a valid symbol in the
   *   `EquationGrammar`.
   * @throws VO_INVALID_ARGUMENT The `leftSymbol` is not a valid terminal symbol
   *   in the `EquationGrammar`.
   * @throws VO_INVALID_ARGUMENT The `rightSymbol` is not a valid terminal
   *   symbol in the `EquationGrammar`.
   */
  bool (VO_MSE_CALL *addFenceRule)(voEngine engine, voEquationGrammar grammar, voEquationSymbol targetSymbol, voEquationSymbol sourceSymbol, voEquationSymbol leftSymbol, voEquationSymbol rightSymbol);

  /**
   * Adds a fraction rule to the `EquationGrammar`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param grammar Reference to the `EquationGrammar` instance.
   * @param targetSymbol id of the target non terminal symbol.
   * @param numeratorSymbol id of the numerator symbol.
   * @param denominatorSymbol id of the denominator symbol.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `grammar` reference is invalid.
   * @throws VO_INVALID_OPERATION The `grammar` reference is not a reference to
   *   an `EquationGrammar` instance.
   * @throws VO_INVALID_ARGUMENT The `targetSymbol` is not a valid non terminal
   *   symbol in the `EquationGrammar`.
   * @throws VO_INVALID_ARGUMENT The `numeratorSymbol` is not a valid symbol in
   *   the `EquationGrammar`.
   * @throws VO_INVALID_ARGUMENT The `denominatorSymbol` is not a valid symbol
   *   in the `EquationGrammar`.
   */
  bool (VO_MSE_CALL *addFractionRule)(voEngine engine, voEquationGrammar grammar, voEquationSymbol targetSymbol, voEquationSymbol numeratorSymbol, voEquationSymbol denominatorSymbol);

  /**
   * Adds a square root rule to the `EquationGrammar`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param grammar Reference to the `EquationGrammar` instance.
   * @param targetSymbol id of the target non terminal symbol.
   * @param sourceSymbol id of the source symbol.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `grammar` reference is invalid.
   * @throws VO_INVALID_OPERATION The `grammar` reference is not a reference to
   *   an `EquationGrammar` instance.
   * @throws VO_INVALID_ARGUMENT The `targetSymbol` is not a valid non terminal
   *   symbol in the `EquationGrammar`.
   * @throws VO_INVALID_ARGUMENT The `sourceSymbol` is not a valid symbol in the
   *   `EquationGrammar`.
   */
  bool (VO_MSE_CALL *addSqrtRule)(voEngine engine, voEquationGrammar grammar, voEquationSymbol targetSymbol, voEquationSymbol sourceSymbol);

  /**
   * Adds a subscript rule to the `EquationGrammar`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param grammar Reference to the `EquationGrammar` instance.
   * @param targetSymbol id of the target non terminal symbol.
   * @param sourceSymbol id of the source symbol.
   * @param indexSymbol id of the index symbol.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `grammar` reference is invalid.
   * @throws VO_INVALID_OPERATION The `grammar` reference is not a reference to
   *   an `EquationGrammar` instance.
   * @throws VO_INVALID_ARGUMENT The `targetSymbol` is not a valid non terminal
   *   symbol in the `EquationGrammar`.
   * @throws VO_INVALID_ARGUMENT The `sourceSymbol` is not a valid symbol in the
   *   `EquationGrammar`.
   * @throws VO_INVALID_ARGUMENT The `indexSymbol` is not a valid symbol in the
   *   `EquationGrammar`.
   */
  bool (VO_MSE_CALL *addSubscriptRule)(voEngine engine, voEquationGrammar grammar, voEquationSymbol targetSymbol, voEquationSymbol sourceSymbol, voEquationSymbol indexSymbol);

  /**
   * Adds a superscript rule to the `EquationGrammar`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param grammar Reference to the `EquationGrammar` instance.
   * @param targetSymbol id of the target non terminal symbol.
   * @param sourceSymbol id of the source symbol.
   * @param exponentSymbol id of the exponent symbol.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `grammar` reference is invalid.
   * @throws VO_INVALID_OPERATION The `grammar` reference is not a reference to
   *   an `EquationGrammar` instance.
   * @throws VO_INVALID_ARGUMENT The `targetSymbol` is not a valid non terminal
   *   symbol in the `EquationGrammar`.
   * @throws VO_INVALID_ARGUMENT The `sourceSymbol` is not a valid symbol in the
   *   `EquationGrammar`.
   * @throws VO_INVALID_ARGUMENT The `exponentSymbol` is not a valid symbol in
   *   the `EquationGrammar`.
   */
  bool (VO_MSE_CALL *addSuperscriptRule)(voEngine engine, voEquationGrammar grammar, voEquationSymbol targetSymbol, voEquationSymbol sourceSymbol, voEquationSymbol exponentSymbol);

  /**
   * Adds an subsuperscript rule to the `EquationGrammar`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param grammar Reference to the `EquationGrammar` instance.
   * @param targetSymbol id of the target non terminal symbol.
   * @param sourceSymbol id of the source symbol.
   * @param indexSymbol id of the index symbol.
   * @param exponentSymbol id of the exponent symbol.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `grammar` reference is invalid.
   * @throws VO_INVALID_OPERATION The `grammar` reference is not a reference to
   *   an `EquationGrammar` instance.
   * @throws VO_INVALID_ARGUMENT The `targetSymbol` is not a valid non terminal
   *   symbol n the `EquationGrammar`.
   * @throws VO_INVALID_OPERATION The `exponentSymbol` id is not a valid symbol
   *   in the `EquationGrammar`.
   * @throws VO_INVALID_OPERATION The `sourceSymbol` id is not a valid symbol in
   *   the `EquationGrammar`.
   * @throws VO_INVALID_OPERATION The `indexSymbol` id is not a valid symbol in
   *   the `EquationGrammar`.
   */
  bool (VO_MSE_CALL *addSubsuperscriptRule)(voEngine engine, voEquationGrammar grammar, voEquationSymbol targetSymbol, voEquationSymbol sourceSymbol, voEquationSymbol indexSymbol, voEquationSymbol exponentSymbol);

  /**
   * Adds an underscript rule to the `EquationGrammar`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param grammar Reference to the `EquationGrammar` instance.
   * @param targetSymbol id of the target non terminal symbol.
   * @param sourceSymbol id of the source symbol.
   * @param bottomSymbol id of the bottom symbol.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `grammar` reference is invalid.
   * @throws VO_INVALID_OPERATION The `grammar` reference is not a reference to
   *   an `EquationGrammar` instance.
   * @throws VO_INVALID_ARGUMENT The `targetSymbol` is not a valid non terminal
   *   symbol n the `EquationGrammar`.
   * @throws VO_INVALID_OPERATION The `sourceSymbol` id is not a valid symbol in
   *   the `EquationGrammar`.
   * @throws VO_INVALID_OPERATION The `bottomSymbol` id is not a valid symbol in
   *   the `EquationGrammar`.
   */
  bool (VO_MSE_CALL *addUnderscriptRule)(voEngine engine, voEquationGrammar grammar, voEquationSymbol targetSymbol, voEquationSymbol sourceSymbol, voEquationSymbol bottomSymbol);

  /**
   * Adds an overscript rule to the `EquationGrammar`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param grammar Reference to the `EquationGrammar` instance.
   * @param targetSymbol id of the target non terminal symbol.
   * @param sourceSymbol id of the source symbol.
   * @param topSymbol id of the top symbol.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `grammar` reference is invalid.
   * @throws VO_INVALID_OPERATION The `grammar` reference is not a reference to
   *   an `EquationGrammar` instance.
   * @throws VO_INVALID_ARGUMENT The `targetSymbol` is not a valid non terminal
   *   symbol n the `EquationGrammar`.
   * @throws VO_INVALID_OPERATION The `sourceSymbol` id is not a valid symbol in
   *   the `EquationGrammar`.
   * @throws VO_INVALID_OPERATION The `topSymbol` id is not a valid symbol in
   *   the `EquationGrammar`.
   */
  bool (VO_MSE_CALL *addOverscriptRule)(voEngine engine, voEquationGrammar grammar, voEquationSymbol targetSymbol, voEquationSymbol sourceSymbol, voEquationSymbol topSymbol);

  /**
   * Adds an underoverscript rule to the `EquationGrammar`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param grammar Reference to the `EquationGrammar` instance.
   * @param targetSymbol id of the target non terminal symbol.
   * @param sourceSymbol id of the source symbol.
   * @param bottomSymbol id of the bottom symbol.
   * @param topSymbol id of the top symbol.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `grammar` reference is invalid.
   * @throws VO_INVALID_OPERATION The `grammar` reference is not a reference to
   *   an `EquationGrammar` instance.
   * @throws VO_INVALID_ARGUMENT The `targetSymbol` is not a valid non terminal
   *   symbol n the `EquationGrammar`.
   * @throws VO_INVALID_OPERATION The `topSymbol` id is not a valid symbol in
   *   the `EquationGrammar`.
   * @throws VO_INVALID_OPERATION The `sourceSymbol` id is not a valid symbol in
   *   the `EquationGrammar`.
   * @throws VO_INVALID_OPERATION The `bottomSymbol` id is not a valid symbol in
   *   the `EquationGrammar`.
   */
  bool (VO_MSE_CALL *addUnderoverscriptRule)(voEngine engine, voEquationGrammar grammar, voEquationSymbol targetSymbol, voEquationSymbol sourceSymbol, voEquationSymbol bottomSymbol, voEquationSymbol topSymbol);

  /**
   * Sets the start symbol of the `EquationGrammar`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param grammar Reference to the `EquationGrammar` instance.
   * @param startSymbol id of the starting symbol.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `grammar` reference is invalid.
   * @throws VO_INVALID_OPERATION The `grammar` reference is not a reference to
   *   an `EquationGrammar` instance.
   * @throws VO_INVALID_ARGUMENT The `startSymbol` is not a valid symbol in the
   *   `EquationGrammar`.
   */
  bool (VO_MSE_CALL *setStartSymbol)(voEngine engine, voEquationGrammar grammar, voEquationSymbol startSymbol);

  /**
   * Adds a presuperscript rule to the `EquationGrammar`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param grammar Reference to the `EquationGrammar` instance.
   * @param targetSymbol id of the target non terminal symbol.
   * @param sourceSymbol id of the source symbol.
   * @param exponentSymbol id of the exponent symbol.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `grammar` reference is invalid.
   * @throws VO_INVALID_OPERATION The `grammar` reference is not a reference to
   *   an `EquationGrammar` instance.
   * @throws VO_INVALID_ARGUMENT The `targetSymbol` is not a valid non terminal
   *   symbol in the `EquationGrammar`.
   * @throws VO_INVALID_ARGUMENT The `sourceSymbol` is not a valid symbol in the
   *   `EquationGrammar`.
   * @throws VO_INVALID_ARGUMENT The `exponentSymbol` is not a valid symbol in
   *   the `EquationGrammar`.
   */
  bool (VO_MSE_CALL *addPresuperscriptRule)(voEngine engine, voEquationGrammar grammar, voEquationSymbol targetSymbol, voEquationSymbol sourceSymbol, voEquationSymbol exponentSymbol);

  /**
   * Adds a vertical pair rule to the <code>EquationGrammar</code>.
   *
   * @param engine Reference to an <code>Engine</code> instance.
   * @param grammar Reference to the <code>EquationGrammar</code> instance.
   * @param targetSymbol id of the target non terminal symbol.
   * @param topSymbol id of the top symbol.
   * @param bottomSymbol id of the bottom symbol.
   *
   * @return <code>true</code> on success, otherwise <code>false</code>.
   *
   * @throws VO_NO_SUCH_ENGINE The <code>engine</code> reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The <code>grammar</code> reference is invalid.
   * @throws VO_INVALID_OPERATION The <code>grammar</code> reference is not a
   *   reference to an <code>EquationGrammar</code> instance.
   * @throws VO_INVALID_ARGUMENT The <code>targetSymbol</code> is not a valid
   *   non terminal symbol in the <code>EquationGrammar</code>.
   * @throws VO_INVALID_ARGUMENT The <code>topSymbol</code> is not a valid
   *   symbol in the <code>EquationGrammar</code>.
   * @throws VO_INVALID_ARGUMENT The <code>bottomSymbol</code> id is not a valid
   *   symbol in the <code>EquationGrammar</code>.
   *
   * @since 6.0_0
   */
  bool (VO_MSE_CALL *addVerticalPairRule)(voEngine engine, voEquationGrammar grammar, voEquationSymbol targetSymbol, voEquationSymbol topSymbol, voEquationSymbol bottomSymbol);

   /**
   * Adds a left fence rule to the `EquationGrammar`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param grammar Reference to the `EquationGrammar` instance.
   * @param targetSymbol id of the target non terminal symbol.
   * @param sourceSymbol id of the source symbol.
   * @param leftSymbol id of the left terminal symbol.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `grammar` reference is invalid.
   * @throws VO_INVALID_OPERATION The `grammar` reference is not a reference to
   *   an `EquationGrammar` instance.
   * @throws VO_INVALID_ARGUMENT The `targetSymbol` is not a valid non terminal
   *   symbol in the `EquationGrammar`.
   * @throws VO_INVALID_ARGUMENT The `sourceSymbol` is not a valid symbol in the
   *   `EquationGrammar`.
   * @throws VO_INVALID_ARGUMENT The `leftSymbol` is not a valid terminal symbol
   *   in the `EquationGrammar`.
   *
   * @since 6.0_0
   */
  bool (VO_MSE_CALL *addLeftFenceRule)(voEngine engine, voEquationGrammar grammar, voEquationSymbol targetSymbol, voEquationSymbol sourceSymbol, voEquationSymbol leftSymbol);
}
voIEquationGrammar;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `EquationGrammar` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `EquationGrammar` object on success,
 *   otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `EquationGrammar` instances would
 *   exceed the allowed limit (please remember that the limit can be shared by
 *   several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voEquationGrammar voCreateEquationGrammar(voEngine engine)
{
  return voCreateObject(engine, VO_EquationGrammar);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- EquationRecognizer -------------------------------------------------------

/**
 * Reference to an instance of the `EquationRecognizer` type.
 *
 * {@implements voIAttachTarget, voIEquationRecognizer}
 *
 * @note Please refer to `MyScriptEngine.h` reference documentation about the
 *   `IAttachTarget` interface.
 */
typedef voEngineObject voEquationRecognizer;

/**
 * {@propertySet EquationRecognizer}
 */
enum VO_EQUATION_RECOGNIZER_PROP
{
  /**
   * A value between `0.0f` and `1.0f` that adjusts the scratch out detection
   * sensitivity.
   *
   * {@property float}
   *
   * @note A value equal to `0.0f` disables scratch out detection.
   */
  VO_EQUATION_RECOGNIZER_SCRATCH_OUT_DETECTION_SENSITIVITY = (VO_EquationRecognizer << 16)
};

typedef struct _voIEquationRecognizer
{
  /**
   * Performs the recognition of an `Equation` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param recognizer Reference to the `EquationRecognizer` instance.
   * @param equation Reference to an `Equation` instance.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `recognizer` reference is invalid.
   * @throws VO_INVALID_OPERATION The `recognizer` reference is not a reference
   *   to an `EquationRecognizer` instance.
   * @throws VO_NO_SUCH_OBJECT The `equation` reference is invalid.
   * @throws VO_INVALID_OBJECT The `equation` object is not an instance of the
   *   `Equation` type.
   * @throws VO_INVALID_CALLBACK The notification callback crashed.
   * @throws VO_INVALID_STATE The `target` object is not in a state where the
   *   `process` function can be invoked.
   * @throws VO_MISSING_EQUATION_ALPHABET_KNOWLEDGE The `EquationRecognizer` has
   *   no attached `EquationAlphabetKnowledge`.
   * @throws VO_MISSING_EQUATION_GRAMMAR The `EquationRecognizer` has no
   *   attached `EquationGrammar`.
   * @throws VO_CANCELED The operation has been canceled.
   */
  bool (VO_MSE_CALL *process)(voEngine engine, voEquationRecognizer recognizer, voEquation equation, voNotifyProgressFunc notifyProgressFunc, void* userParam);
}
voIEquationRecognizer;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `EquationRecognizer` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `EquationRecognizer` object on
 *   success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `EquationRecognizer` instances would
 *   exceed the allowed limit (please remember that the limit can be shared by
 *   several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voEquationRecognizer voCreateEquationRecognizer(voEngine engine)
{
  return voCreateObject(engine, VO_EquationRecognizer);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- EquationTerminalNode -----------------------------------------------------

/**
 * Reference to an instance of the `EquationTerminalNode` type.
 *
 * {@implements voIEquationTerminalNode}
 */
typedef voEquationNode voEquationTerminalNode;

/**
 * The `EquationInputRange` type models a range in the input.
 */
typedef struct _voEquationInputRange
{
  /**
   * Index of the component (stroke or character).
   */
  int32_t component;

  /**
   * Position of the first item within the component (eg, first point within a
   * stroke).
   */
  float firstItem;

  /**
   * Position of the last item within the component (eg, last point within a
   * stroke).
   */
  float lastItem;
}
voEquationInputRange;

/**
 * Functions composing the `IEquationTerminalNode` interface. This interface
 * exposes the public methods of the `EquationTerminalNode` type.
 *
 * {@implementingTypes voEquationTerminalNode}
 * @see VO_IEquationTerminalNode, VO_EquationTerminalNode.
 */
typedef struct _voIEquationTerminalNode
{
  /**
   * Returns the name of this `EquationTerminalNode`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `EquationTerminalNode` instance.
   * @param charset Reference to the `Charset` instance to be used to encode the
   *   returned name.
   * @param string Recipient for the name.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `EquationTerminalNode` instance.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_INVALID_OBJECT The `charset` reference is not a reference to a
   *   `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER The `string` recipient is not readable or
   *   writable.
   * @throws VO_INVALID_USER_BUFFER The `bytes` member of the `string` recipient
   *   is not writable.
   *
   * @note You can use the `VO_DEFAULT_CHARSET` property to provide the `Engine`
   *   with a default `Charset`. When done, you are allowed to pass `NULL` in
   *   place of a reference to a `Charset`.
   *
   * @see voEngine
   */
  bool (VO_MSE_CALL *getName)(voEngine engine, voEquationTerminalNode target, voCharset charset, voString* string);

  /**
   * Returns the number of input ranges this terminal node covers.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `EquationTerminalNode` instance.
   *
   * @return The number of input ranges this terminal node covers on success,
   *   otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `EquationTerminalNode` instance.
   * @throws VO_INVALID_STATE The portion of a MyScript Document associated with
   *   this node has been modified, so the associated input ranges are not valid
   *   anymore.
   */
  uint32_t (VO_MSE_CALL *getInputRangeCount)(voEngine engine, voEquationTerminalNode target);

  /**
   * Returns the input range at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `EquationTerminalNode` instance.
   * @param index The zero-based index of the input range to be retrieved.
   * @param inputRange Recipient for the input range result.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `EquationTerminalNode` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_INVALID_USER_BUFFER The `range` recipient is not writable.
   * @throws VO_INVALID_STATE The portion of a MyScript Document associated with
   *   this node has been modified, so the associated input ranges are not valid
   *   anymore.
   */
  bool (VO_MSE_CALL *getInputRangeAt)(voEngine engine, voEquationTerminalNode target, uint32_t index, voEquationInputRange* range);

  /**
   * Returns the number of candidates this terminal node contains.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `EquationTerminalNode` instance.
   *
   * @return The number of candidates this terminal node contains on success,
   *   otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `EquationTerminalNode` instance.
   */
  uint32_t (VO_MSE_CALL *getCandidateCount)(voEngine engine, voEquationTerminalNode target);

  /**
   * Returns the label of the candidate at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `EquationTerminalNode` instance.
   * @param index The zero-based index of the candidate label to be retrieved.
   * @param charset Reference to the `Charset` instance to be used to encode the
   *   returned label.
   * @param string Recipient for the label.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `EquationTerminalNode` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_INVALID_OBJECT The `charset` reference is not a reference to a
   *   `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER The `string` recipient is not readable or
   *   writable.
   * @throws VO_INVALID_USER_BUFFER The `bytes` member of the `string` recipient
   *   is not writable.
   *
   * @note You can use the `VO_DEFAULT_CHARSET` property to provide the `Engine`
   *   with a default `Charset`. When done, you are allowed to pass `NULL` in
   *   place of a reference to a `Charset`.
   *
   * @see voEngine
   */
  bool (VO_MSE_CALL *getCandidateLabelAt)(voEngine engine, voEquationTerminalNode target, uint32_t index, voCharset charset, voString* string);

  /**
   * Returns the normalized recognition score of the candidate at the specified
   * `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `EquationTerminalNode` instance.
   * @param index The zero-based index of the candidate normalized recognition
   *   score to be retrieved.
   *
   * @return The normalized recognition score of the candidate at the specified
   *   `index` on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `EquationTerminalNode` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  float (VO_MSE_CALL *getCandidateNormalizedRecognitionScoreAt)(voEngine engine, voEquationTerminalNode target, uint32_t index);

  /**
   * Returns the index of the selected candidate in this
   * `EquationTerminalNode`'s candidate list.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `EquationTerminalNode` instance.
   *
   * @return The position of the selected candidate on success, otherwise
   *   `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `EquationTerminalNode` instance.
   * @throws VO_INVALID_STATE The object is not in a state where the selected
   *   candidate is available.
   */
  uint32_t (VO_MSE_CALL *getSelectedCandidateIndex)(voEngine engine, voEquationTerminalNode target);
}
voIEquationTerminalNode;


// -- EquationNonTerminalNode --------------------------------------------------

/**
 * Reference to an instance of the `EquationNonTerminalNode` type.
 *
 * {@implements voIEquationNonTerminalNode}
 */
typedef voEquationNode voEquationNonTerminalNode;

/**
 * Functions composing the `IEquationNonTerminalNode` interface. This interface
 * exposes the public methods of the `EquationNonTerminalNode` type.
 *
 * {@implementingTypes voEquationNonTerminalNode}
 * @see VO_IEquationNonTerminalNode, VO_EquationNonTerminalNode.
 */
typedef struct _voIEquationNonTerminalNode
{
  /**
   * Returns the name of this `EquationNonTerminalNode`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `EquationNonTerminalNode` instance.
   * @param charset Reference to the `Charset` instance to be used to encode the
   *   returned name.
   * @param string Recipient for the name.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `EquationNonTerminalNode` instance.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_INVALID_OBJECT The `charset` reference is not a reference to a
   *   `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER The `string` recipient is not readable or
   *   writable.
   * @throws VO_INVALID_USER_BUFFER The `bytes` member of the `string` recipient
   *   is not writable.
   *
   * @note You can use the `VO_DEFAULT_CHARSET` property to provide the `Engine`
   *   with a default `Charset`. When done, you are allowed to pass `NULL` in
   *   place of a reference to a `Charset`.
   *
   * @see voEngine
   */
  bool (VO_MSE_CALL *getName)(voEngine engine, voEquationNonTerminalNode target, voCharset charset, voString* string);

  /**
   * Returns the number of input ranges this non terminal node covers.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `EquationNonTerminalNode` instance.
   *
   * @return The number of input ranges this non terminal node covers on
   *   success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `EquationNonTerminalNode` instance.
   * @throws VO_INVALID_STATE The portion of a MyScript Document associated with
   *   this node has been modified, so the associated input ranges are not valid
   *   anymore.
   */
  uint32_t (VO_MSE_CALL *getInputRangeCount)(voEngine engine, voEquationNonTerminalNode target);

  /**
   * Returns the input range at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `EquationNonTerminalNode` instance.
   * @param index The zero-based index of the input range to be retrieved.
   * @param inputRange Recipient for the input range result.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `EquationNonTerminalNode` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_INVALID_USER_BUFFER The `range` recipient is not writable.
   * @throws VO_INVALID_STATE The portion of a MyScript Document associated with
   *   this node has been modified, so the associated input ranges are not valid
   *   anymore.
   */
  bool (VO_MSE_CALL *getInputRangeAt)(voEngine engine, voEquationNonTerminalNode target, uint32_t index, voEquationInputRange* range);

  /**
   * Returns the number of candidates this non terminal node contains.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `EquationNonTerminalNode` instance.
   *
   * @return The number of candidates this non terminal node contains on
   *   success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `EquationNonTerminalNode` instance.
   */
  uint32_t (VO_MSE_CALL *getCandidateCount)(voEngine engine, voEquationNonTerminalNode target);

  /**
   * Returns the candidate at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `EquationNonTerminalNode` instance.
   * @param index The zero-based index of the candidate to be retrieved.
   *
   * @return An `EquationNode` instance on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `EquationNonTerminalNode` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_LIMIT_EXCEEDED The number of `EquationNode`
   *   instances would exceed the allowed limit (please remember that the limit
   *   can be shared by several types).
   */
  voEquationNode (VO_MSE_CALL *getCandidateAt)(voEngine engine, voEquationNonTerminalNode target, uint32_t index);

  /**
   * Returns the index of the selected candidate in this
   * `EquationNonTerminalNode`'s candidate list.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `EquationNonTerminalNode` instance.
   *
   * @return The position of the selected candidate on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `EquationNonTerminalNode` instance.
   * @throws VO_INVALID_STATE The object is not in a state where the selected
   *   candidate is available.
   */
  uint32_t (VO_MSE_CALL *getSelectedCandidateIndex)(voEngine engine, voEquationNonTerminalNode target);
}
voIEquationNonTerminalNode;


// -- EquationRuleNode ---------------------------------------------------------

/**
 * Reference to an instance of the `EquationRuleNode` type.
 *
 * {@implements voIEquationRuleNode}
 */
typedef voEquationNode voEquationRuleNode;

/**
 * Functions composing the `IEquationRuleNode` interface. This interface exposes
 * the public methods of the `EquationRuleNode` type.
 *
 * {@implementingTypes voEquationRuleNode}
 * @see VO_IEquationRuleNode, VO_EquationRuleNode.
 */
typedef struct _voIEquationRuleNode
{
  /**
   * Returns the name of this rule node.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `EquationRuleNode` instance.
   * @param charset Reference to the `Charset` instance to be used to encode the
   *   returned name.
   * @param string Recipient for the name.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `EquationRuleNode` instance.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_INVALID_OBJECT The `charset` reference is not a reference to a
   *   `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER The `string` recipient is not readable or
   *   writable.
   * @throws VO_INVALID_USER_BUFFER The `bytes` member of the `string` recipient
   *   is not writable.
   *
   * @note You can use the `VO_DEFAULT_CHARSET` property to provide the `Engine`
   *   with a default `Charset`. When done, you are allowed to pass `NULL` in
   *   place of a reference to a `Charset`.
   *
   * @see voEngine
   */
  bool (VO_MSE_CALL *getName)(voEngine engine, voEquationRuleNode target, voCharset charset, voString* string);

  /**
   * Returns the number of children this rule node contains.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `EquationRuleNode` instance.
   *
   * @return The number of children this rule node contains on success,
   *   otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `EquationRuleNode` instance.
   */
  uint32_t (VO_MSE_CALL *getChildCount)(voEngine engine, voEquationRuleNode target);

  /**
   * Returns the child at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `EquationRuleNode` instance.
   * @param index The zero-based index of the child to be retrieved.
   *
   * @return An `EquationNode` instance on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `EquationRuleNode` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_LIMIT_EXCEEDED The number of `EquationNode` instances would
   *   exceed the allowed limit (please remember that the limit can be shared by
   *   several types).
   */
  voEquationNode (VO_MSE_CALL *getChildAt)(voEngine engine, voEquationRuleNode target, uint32_t index);
}
voIEquationRuleNode;


// -- EquationScratchOut -------------------------------------------------------

/**
 * Functions composing the `IEquationScratchOut` interface. This interface
 * exposes the public methods of the `EquationScratchOut` type.
 *
 * {@implementingTypes voEquationScratchOut}
 * @see VO_IEquationScratchOut, VO_EquationScratchOut.
 *
 * @since 6.1_0
 */
typedef struct _voIEquationScratchOut
{
  /**
   * Returns the number of input ranges this scratch out covers.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `EquationScratchOut` instance.
   *
   * @return The number of input ranges this scratch out covers on success,
   *   otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `EquationScratchOut` instance.
   */
  uint32_t (VO_MSE_CALL *getInputRangeCount)(voEngine engine, voEquationScratchOut target);

  /**
   * Returns the input range at the specified `index` this scratch out covers.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `EquationScratchOut` instance.
   * @param index The zero-based index of the input range to be retrieved.
   * @param inputRange Recipient for the input range result.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `EquationScratchOut` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_INVALID_USER_BUFFER The `range` recipient is not writable.
   */
  bool (VO_MSE_CALL *getInputRangeAt)(voEngine engine, voEquationScratchOut target, uint32_t index, voEquationInputRange* range);

  /**
   * Returns the number of input ranges this scratch out erases.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `EquationScratchOut` instance.
   *
   * @return The number of input ranges this scratch out covers on success,
   *   otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `EquationScratchOut` instance.
   */
  uint32_t (VO_MSE_CALL *getErasedInputRangeCount)(voEngine engine, voEquationScratchOut target);

  /**
   * Returns the input range at the specified `index` this scratch out erases.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `EquationScratchOut` instance.
   * @param index The zero-based index of the input range to be retrieved.
   * @param inputRange Recipient for the input range result.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   an `EquationScratchOut` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_INVALID_USER_BUFFER The `range` recipient is not writable.
   */
  bool (VO_MSE_CALL *getErasedInputRangeAt)(voEngine engine, voEquationScratchOut target, uint32_t index, voEquationInputRange* range);
}
voIEquationScratchOut;

#endif // end of: #ifndef C_MYSCRIPTEQUATION_H
