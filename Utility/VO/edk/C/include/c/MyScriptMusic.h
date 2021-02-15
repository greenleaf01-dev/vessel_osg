#ifndef C_MYSCRIPTMUSIC_H

#define C_MYSCRIPTMUSIC_H 0x06010000
/**
 * @file c/MyScriptMusic.h
 * Native interface to the MyScript Music service.
 */

#include "MyScriptEngine.h"


// -- error codes --------------------------------------------------------------

/**
 * Lists the MyScript Music errors.
 */
enum VO_MUSIC_ERR
{
  /**
   * Unable to complete the requested operation because a
   * `MusicAlphabetKnowledge` is missing.
   *
   * @see voMusicAlphabetKnowledge.
   */
  VO_MISSING_MUSIC_ALPHABET_KNOWLEDGE = VO_INVALID_STATE | (7 << 16),

  /**
   * Unable to complete the requested operation because an `MusicGrammar` is
   * missing.
   *
   * @see voMusicGrammar.
   * @see voIAttachTarget.
   */
  VO_MISSING_MUSIC_GRAMMAR,

  /**
   * Unable to complete the requested operation because a staff is missing.
   *
   * @see voMusicDocument.
   * @see voMusicRecognizer.
   */
  VO_MISSING_MUSIC_STAFF
};


// -- types and interfaces -----------------------------------------------------

/**
 * Lists the MyScript Music types.
 *
 * @see enum VO_MUSIC_ELEMENT_T.
 */
enum VO_MUSIC_T
{
  /**
   * `MusicDocument` type.
   *
   * @see voMusic.
   */
  VO_MusicDocument = 9000,
  /**
   * `MusicAlphabetKnowledge` type.
   *
   * @see voMusicAlphabetKnowledge.
   */
  VO_MusicAlphabetKnowledge,
  /**
   * `MusicGrammar` type.
   *
   * @see voMusicGrammar.
   */
  VO_MusicGrammar,
  /**
   * `MusicRecognizer` type.
   *
   * @see voMusicRecognizer.
   */
  VO_MusicRecognizer,
  /**
   * `MusicScore` type.
   *
   * @see voMusicScore.
   */
  VO_MusicScore,
  /**
   * `MusicPart` type.
   *
   * @see voMusicPart.
   */
  VO_MusicPart,
  /**
   * `MusicElement` type.
   *
   * @see voMusicElement.
   */
  VO_MusicElement,
  /**
   * `MusicArticulationMark` type.
   *
   * @see voMusicArticulationMark.
   */
  VO_MusicArticulationMark,
  /**
   * `MusicBar` type.
   *
   * @see voMusicBar.
   */
  VO_MusicBar,
  /**
   * `MusicClef` type.
   *
   * @see voMusicClef.
   */
  VO_MusicClef,
  /**
   * `MusicAccidental` type.
   *
   * @see voMusicAccidental.
   */
  VO_MusicAccidental,
  /**
   * `MusicKeySignature` type.
   *
   * @see voMusicKeySignature.
   */
  VO_MusicKeySignature,
  /**
   * `MusicAnnotation` type.
   *
   * @see voMusicAnnotation.
   */
  VO_MusicAnnotation,
  /**
   * `MusicTimeSignature` type.
   *
   * @see voMusicTimeSignature.
   */
  VO_MusicTimeSignature,
  /**
   * `MusicNote` type.
   *
   * @see voMusicNote.
   */
  VO_MusicNote,
  /**
   * `MusicHead` type.
   *
   * @see voMusicHead.
   */
  VO_MusicHead,
  /**
   * `MusicStem` type.
   *
   * @see voMusicStem.
   */
  VO_MusicStem,
  /**
   * `MusicBeam` type.
   *
   * @see voMusicBeam.
   */
  VO_MusicBeam,
  /**
   * `MusicDots` type.
   *
   * @see voMusicDots.
   */
  VO_MusicDots,
  /**
   * `MusicTie` type.
   *
   * @see voMusicTie.
   */
  VO_MusicTie,
  /**
   * `MusicSlur` type.
   *
   * @see voMusicSlur.
   */
  VO_MusicSlur,
  /**
   * `MusicLedgerLine` type.
   *
   * @see voMusicLedgerLine.
   */
  VO_MusicLedgerLine,
  /**
   * `MusicRest` type.
   *
   * @see voMusicRest.
   */
  VO_MusicRest,
  /**
   * `MusicChord` type.
   *
   * @see voMusicChord.
   */
  VO_MusicChord,
  /**
   * `MusicScratchOut` type.
   *
   * @see voMusicScratchOut.
   *
   * @since 6.1_0
   */
  VO_MusicScratchOut
};

/**
 * Lists the MyScript Music interfaces.
 */
enum VO_MUSIC_I
{
  /**
   * `IMusicDocument` interface type.
   *
   * @see voIMusicDocument.
   */
  VO_IMusicDocument = 9050,
  /**
   * `IMusicGrammar` interface type.
   *
   * @see voIMusicGrammar.
   */
  VO_IMusicGrammar,
  /**
   * `IMusicRecognizer` interface type.
   *
   * @see voIMusicRecognizer.
   */
  VO_IMusicRecognizer,

  /**
   * `IMusicScore` interface type.
   *
   * @see voIMusicScore.
   */
  VO_IMusicScore,
  /**
   * `IMusicPart` interface type.
   *
   * @see voIMusicPart.
   */
  VO_IMusicPart,
  /**
   * `IMusicElement` interface type.
   *
   * @see voIMusicElement.
   */
  VO_IMusicElement,
  /**
   * `IMusicArticulationMark` interface type.
   *
   * @see voIMusicArticulationMark.
   */
  VO_IMusicArticulationMark,
  /**
   * `IMusicBar` interface type.
   *
   * @see voIMusicBar.
   */
  VO_IMusicBar,
  /**
   * `IMusicClef` interface type.
   *
   * @see voIMusicClef.
   */
  VO_IMusicClef,
  /**
   * `IMusicAccidental` interface type.
   *
   * @see voIMusicAccidental.
   */
  VO_IMusicAccidental,
  /**
   * `IMusicKeySignature` interface type.
   *
   * @see voIMusicKeySignature.
   */
  VO_IMusicKeySignature,
  /**
   * `IMusicAnnotation` interface type.
   *
   * @see voIMusicAnnotation.
   */
  VO_IMusicAnnotation,
  /**
   * `IMusicTimeSignature` interface type.
   *
   * @see voIMusicTimeSignature.
   */
  VO_IMusicTimeSignature,
  /**
   * `IMusicNote` interface type.
   *
   * @see voIMusicNote.
   */
  VO_IMusicNote,
  /**
   * `IMusicHead` interface type.
   *
   * @see voIMusicHead.
   */
  VO_IMusicHead,
  /**
   * `IMusicStem` interface type.
   *
   * @see voIMusicStem.
   */
  VO_IMusicStem,
  /**
   * `IMusicBeam` interface type.
   *
   * @see voIMusicBeam.
   */
  VO_IMusicBeam,
  /**
   * `IMusicDots` interface type.
   *
   * @see voIMusicDots.
   */
  VO_IMusicDots,
  /**
   * `IMusicTie` interface type.
   *
   * @see voIMusicTie.
   */
  VO_IMusicTie,
  /**
   * `IMusicSlur` interface type.
   *
   * @see voIMusicSlur.
   */
  VO_IMusicSlur,
  /**
   * `IMusicRest` interface type.
   *
   * @see voIMusicRest.
   */
  VO_IMusicRest,
  /**
   * `IMusicChord` interface type.
   *
   * @see voIMusicChord.
   */
  VO_IMusicChord,
  /**
   * `IMusicScratchOut` type.
   *
   * @see voIMusicScratchOut.
   *
   * @since 6.1_0
   */
  VO_IMusicScratchOut
};


// -- MusicElement -------------------------------------------------------------

/**
 * Represents an element placement.
 */
typedef enum _voMusicPlacement
{
  VO_MUSIC_PLACEMENT_ERR = -1, /**< Error marker. */

  VO_MUSIC_PLACEMENT_ABOVE,    /**< Above. */
  VO_MUSIC_PLACEMENT_BELOW,    /**< Below. */

  VO_MUSIC_PLACEMENT_COUNT
}
voMusicPlacement;


/**
 * Reference to an instance of the `MusicElement` type.
 *
 * {@extends voEngineObject}
 * {@implements voIMusicElement}
 */
typedef voEngineObject voMusicElement;

/**
 * {@typePropertySet MusicElement}
 */
enum VO_MUSIC_ELEMENT_TPROP
{
  /**
   * Represents the maximum number of `MusicElement` instances that can exist at
   * the same time in the user side of a MyScript enabled application. The
   * special value zero means no limit. Other values are adjusted to the next
   * multiple of 16. A value under the current count is permitted and will
   * constrain future resource creations.
   *
   * {@property uint32_t}
   */
  VO_USER_MUSIC_ELEMENT_LIMIT = VO_USER_OBJ_LIMIT,
  /**
   * Gives the number of `MusicElement` instances that currently exist in the
   * user side of a MyScript enabled application.
   *
   * {@property read-only uint32_t}
   */
  VO_USER_MUSIC_ELEMENT_COUNT = VO_USER_OBJ_COUNT
};


/**
 * The `MusicInputRange` type models a range in the input.
 */
typedef struct _voMusicInputRange
{
  /**
   * Index of the component (stroke or element).
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
voMusicInputRange;

/**
 * Functions composing the `IMusicElement` interface. This interface exposes the
 * public methods of the `MusicElement` type.
 *
 * {@implementingTypes voMusicElement}
 * @see VO_IMusicElement, VO_MusicElement.
 */
typedef struct _voIMusicElement
{
  /**
   * Returns the number of input ranges this element covers.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicElement` instance.
   *
   * @return The number of input ranges this element covers on success,
   *   otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicElement` instance.
   */
  int (VO_MSE_CALL *getInputRangeCount)(voEngine engine, voMusicElement target);

  /**
   * Returns the input range at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicElement` instance.
   * @param index The zero-based index of the input range to be retrieved.
   * @param inputRange Recipient for the input range result.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicElement` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_INVALID_USER_BUFFER The `range` recipient is not writable.
   */
  bool (VO_MSE_CALL *getInputRangeAt)(voEngine engine, voMusicElement target, int index, voMusicInputRange* range);
}
voIMusicElement;


// -- MusicArticulationMark ----------------------------------------------------

/**
 * Reference to an instance of the `MusicArticulationMark` type.
 *
 * {@extends voMusicElement}
 * {@implements voIMusicArticulationMark, voIMusicElement}
 */
typedef voMusicElement voMusicArticulationMark;

/**
 * Represents a music articulation mark symbol.
 */
typedef enum _voMusicArticulationMarkSymbol
{
  VO_MUSIC_ARTICULATION_MARK_SYMBOL_ERR = -1,       /**< Error marker. */

  VO_MUSIC_ARTICULATION_MARK_SYMBOL_NORMAL_FERMATA, /**< Normal fermata. */
  VO_MUSIC_ARTICULATION_MARK_SYMBOL_ANGLED_FERMATA, /**< Angled fermata. */
  VO_MUSIC_ARTICULATION_MARK_SYMBOL_SQUARE_FERMATA, /**< Square fermata. */

  VO_MUSIC_ARTICULATION_MARK_SYMBOL_COUNT
}
voMusicArticulationMarkSymbol;

/**
 * Functions composing the `IMusicArticulationMark` interface. This interface
 * exposes the public methods of the `MusicArticulationMark` type.
 *
 * {@implementingTypes voMusicArticulationMark}
 * @see VO_IMusicArticulationMark, VO_MusicArticulationMark.
 */
typedef struct _voIMusicArticulationMark
{
  /**
   * Returns the articulation mark symbol.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicArticulationMark` instance.
   *
   * @return The articulation mark symbol on success, otherwise
   *   `VO_MUSIC_ARTICULATION_MARK_SYMBOL_ERR`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicArticulationMark` instance.
   */
  voMusicArticulationMarkSymbol (VO_MSE_CALL *getSymbol)(voEngine engine, voMusicArticulationMark target);

  /**
   * Returns the placement of the articulation mark.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicArticulationMark` instance.
   *
   * @return the placement of the articulation mark on success, otherwise
   *   `VO_MUSIC_PLACEMENT_ERR`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicArticulationMark` instance.
   */
  voMusicPlacement (VO_MSE_CALL *getPlacement)(voEngine engine, voMusicArticulationMark target);
}
voIMusicArticulationMark;


// -- MusicBar -----------------------------------------------------------------

/**
 * Reference to an instance of the `MusicBar` type.
 *
 * {@extends voMusicElement}
 * {@implements voIMusicBar, voIMusicElement}
 */
typedef voMusicElement voMusicBar;

/**
 * Represents a music bar style.
 */
typedef enum _voMusicBarStyle
{
  VO_MUSIC_BAR_STYLE_ERR = -1,     /**< Error marker. */

  VO_MUSIC_BAR_STYLE_REGULAR,      /**< Normal. */
  VO_MUSIC_BAR_STYLE_DOTTED,       /**< Dotted. */
  VO_MUSIC_BAR_STYLE_LIGHT_LIGHT,  /**< Double. */
  VO_MUSIC_BAR_STYLE_LIGHT_HEAVY,  /**< End. */
  VO_MUSIC_BAR_STYLE_HEAVY_LIGHT,  /**< Start repeat. */

  VO_MUSIC_BAR_STYLE_COUNT
}
voMusicBarStyle;

/**
 * Represents a music bar repeat direction (if any).
 */
typedef enum _voMusicBarRepeatDirection
{
  VO_MUSIC_BAR_REPEAT_DIRECTION_ERR = -1, /**< Error marker. */

  VO_MUSIC_BAR_REPEAT_DIRECTION_NONE,     /**< None. */
  VO_MUSIC_BAR_REPEAT_DIRECTION_FORWARD,  /**< Repeat forward. */
  VO_MUSIC_BAR_REPEAT_DIRECTION_BACKWARD, /**< Repeat backward. */

  VO_MUSIC_BAR_REPEAT_DIRECTION_COUNT
}
voMusicBarRepeatDirection;

/**
 * Functions composing the `IMusicBar` interface. This interface exposes the
 * public methods of the `MusicBar` type.
 *
 * {@implementingTypes voMusicBar}
 * @see VO_IMusicBar, VO_MusicBar.
 */
typedef struct _voIMusicBar
{
  /**
   * Returns the bar style.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicBar` instance.
   *
   * @return The bar style on success, otherwise `VO_MUSIC_BAR_STYLE_ERR`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicBar` instance.
   */
  voMusicBarStyle (VO_MSE_CALL *getStyle)(voEngine engine, voMusicBar target);

   /**
   * Returns the bar repeat direction.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicBar` instance.
   *
   * @return The bar repeat direction on succcess, otherwise
   *   `VO_MUSIC_BAR_REPEAT_DIRECTION_ERR`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicBar` instance.
   */
  voMusicBarRepeatDirection (VO_MSE_CALL *getRepeatDirection)(voEngine engine, voMusicBar target);

  /**
   * Returns the number of articulation marks on this bar.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicBar` instance.
   *
   * @return The number of articulation marks on this bar on success, otherwise
   *   `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicBar` instance.
   */
  int (VO_MSE_CALL *getArticulationMarkCount)(voEngine engine, voMusicBar target);

  /**
   * Returns the articulation mark at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicBar` instance.
   * @param index Index of the requested articulation mark.
   *
   * @return A reference to a `MusicArticulationMark` instance on success,
   *   otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicBar` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voMusicArticulationMark (VO_MSE_CALL *getArticulationMarkAt)(voEngine engine, voMusicBar target, int index);
}
voIMusicBar;


// -- MusicClef ----------------------------------------------------------------

/**
 * Reference to an instance of the `MusicClef` type.
 *
 * {@extends voMusicElement}
 * {@implements voIMusicClef, voIMusicElement}
 */
typedef voMusicElement voMusicClef;

/**
 * Represents a music clef symbol.
 */
typedef enum _voMusicClefSymbol
{
  VO_MUSIC_CLEF_SYMBOL_ERR = -1,  /**< Error marker. */

  VO_MUSIC_CLEF_SYMBOL_G,         /**< G. */
  VO_MUSIC_CLEF_SYMBOL_F,         /**< F. */
  VO_MUSIC_CLEF_SYMBOL_C,         /**< C. */

  VO_MUSIC_CLEF_SYMBOL_COUNT
}
voMusicClefSymbol;

/**
 * Functions composing the `IMusicClef` interface. This interface exposes the
 * public methods of the `MusicClef` type.
 *
 * {@implementingTypes voMusicClef}
 * @see VO_IMusicClef, VO_MusicClef.
 */
typedef struct _voIMusicClef
{
  /**
   * Returns the clef symbol.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicClef` instance.
   *
   * @return The clef symbol on success, otherwise `VO_MUSIC_CLEF_SYMBOL_ERR`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicClef` instance.
   */
  voMusicClefSymbol (VO_MSE_CALL *getSymbol)(voEngine engine, voMusicClef target);

  /**
   * Returns the line on which the clef is positioned.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicClef` instance.
   * @param line Recipient for the line value.
   *
   * @return The line on which the clef is positioned on success, otherwise
   *   `INT32_MAX`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicClef` instance.
   */
  int32_t (VO_MSE_CALL *getLine)(voEngine engine, voMusicClef target);

  /**
   * Returns the clef octave.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicClef` instance.
   * @param octave Recipient for the octave value.
   *
   * @return The clef octave on success otherwise `INT32_MAX`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicClef` instance.
   */
  int32_t (VO_MSE_CALL *getOctave)(voEngine engine, voMusicClef target);
}
voIMusicClef;


// -- MusicAccidental ----------------------------------------------------------

/**
 * Reference to an instance of the `MusicAccidental` type.
 *
 * {@extends voMusicElement}
 * {@implements voIMusicAccidental, voIMusicElement}
 */
typedef voMusicElement voMusicAccidental;

/**
 * Represents a music accidental type.
 */
typedef enum _voMusicAccidentalType
{
  VO_MUSIC_ACCIDENTAL_TYPE_ERR = -1,      /**< Error marker. */

  VO_MUSIC_ACCIDENTAL_TYPE_NATURAL,       /**< Natural accidental. */
  VO_MUSIC_ACCIDENTAL_TYPE_SHARP,         /**< Sharp accidental. */
  VO_MUSIC_ACCIDENTAL_TYPE_DOUBLE_SHARP,  /**< Double sharp accidental. */
  VO_MUSIC_ACCIDENTAL_TYPE_FLAT,          /**< Flat accidental. */
  VO_MUSIC_ACCIDENTAL_TYPE_FLAT_FLAT,     /**< Double flat accidental. */

  VO_MUSIC_ACCIDENTAL_TYPE_COUNT
}
voMusicAccidentalType;

/**
 * Functions composing the `IMusicAccidental` interface. This interface exposes
 * the public methods of the `MusicAccidental` type.
 *
 * {@implementingTypes voMusicAccidental}
 * @see VO_IMusicAccidental, VO_MusicAccidental.
 */
typedef struct _voIMusicAccidental
{
  /**
   * Returns the type of accidental.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicAccidental` instance.
   *
   * @return the type of accidental on success, otherwise
   *   `VO_MUSIC_ACCIDENTAL_TYPE_ERR`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicAccidental` instance.
   */
  voMusicAccidentalType (VO_MSE_CALL *getType)(voEngine engine, voMusicAccidental target);
}
voIMusicAccidental;


// -- MusicKeySignature --------------------------------------------------------

/**
 * Reference to an instance of the `MusicKeySignature` type.
 *
 * {@extends voMusicElement}
 * {@implements voIMusicKeySignature, voIMusicElement}
 */
typedef voMusicElement voMusicKeySignature;

/**
 * Represents a key signature.
 */
typedef struct _voMusicKeySignatureData
{
  int32_t fifths; /**< Fifths. */
  int32_t cancel; /**< Cancel. */
}
voMusicKeySignatureData;

/**
 * Functions composing the `IMusicKeySignature` interface. This interface
 * exposes the public methods of the `MusicKeySignature` type.
 *
 * {@implementingTypes voMusicKeySignature}
 * @see VO_IMusicKeySignature, VO_MusicKeySignature.
 */
typedef struct _voIMusicKeySignature
{
  /**
   * Return the key signature data.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicKeySignature` instance.
   * @param data Recipient for the signature data.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicKeySignature` instance.
   * @throws VO_INVALID_USER_BUFFER The `data` recipient is not writable.
   */
  bool (VO_MSE_CALL *getSignature)(voEngine engine, voMusicKeySignature target, voMusicKeySignatureData* data);

  /**
   * Returns the number of accidentals in this key signature.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicKeySignature` instance.
   *
   * @return The number of accidentals in this key signature on success,
   *   otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicKeySignature` instance.
   */
  int (VO_MSE_CALL *getAccidentalCount)(voEngine engine, voMusicKeySignature target);

  /**
   * Returns the accidental at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicKeySignature` instance.
   * @param index Index of the requested accidental.
   *
   * @return A reference to a `MusicAccidental` instance on success, otherwise
   *   `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicKeySignature` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voMusicAccidental (VO_MSE_CALL *getAccidentalAt)(voEngine engine, voMusicKeySignature target, int index);
}
voIMusicKeySignature;


// -- MusicAnnotation ----------------------------------------------------------

/**
 * Reference to an instance of the `MusicAnnotation` type.
 *
 * {@extends voMusicElement}
 * {@implements voIMusicAnnotation, voIMusicElement}
 */
typedef voMusicElement voMusicAnnotation;

/**
 * Functions composing the `IMusicAnnotation` interface. This interface
 * exposes the public methods of the `MusicAnnotation` type.
 *
 * {@implementingTypes voMusicAnnotation}
 * @see VO_IMusicAnnotation, VO_MusicAnnotation.
 */
typedef struct _voIMusicAnnotation
{
  /**
   * Returns the label of this annotation.
   *
   * @param engine Reference to an <code>Engine</code> instance.
   * @param target Reference to a <code>MusicAnnotation</code> instance.
   * @param charset Reference to the <code>Charset</code> instance to be used
   *   to encode the returned label.
   * @param string Recipient for the label.
   *
   * @return <code>true</code> on success, otherwise <code>false</code>.
   *
   * @throws VO_NO_SUCH_ENGINE The <code>engine</code> reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The <code>target</code> reference is invalid.
   * @throws VO_INVALID_OPERATION The <code>target</code> reference is not a
   *   reference to a <code>MusicAnnotation</code> instance.
   * @throws VO_NO_SUCH_OBJECT The <code>charset</code> reference is
   *   <code>NULL</code> and no default charset was set.
   * @throws VO_INVALID_OBJECT The <code>charset</code> reference is not a
   *   reference to a <code>Charset</code> instance.
   * @throws VO_INVALID_USER_BUFFER The <code>string</code> recipient is not
   *   readable or writable.
   * @throws VO_INVALID_USER_BUFFER The <code>bytes</code> member of the
   *   <code>string</code> recipient is not writable.
   *
   * @note You can use the <code>VO_DEFAULT_CHARSET</code> property to provide
   *   the <code>Engine</code> with a default <code>Charset</code>. When done,
   *   you are allowed to pass <code>NULL</code> in place of a reference to a
   *   <code>Charset</code>.
   */
  bool (VO_MSE_CALL *getLabel)(voEngine engine, voMusicAnnotation target, voCharset charset, voString* string);
}
voIMusicAnnotation;


// -- MusicTimeSignature -------------------------------------------------------

/**
 * Reference to an instance of the `MusicTimeSignature` type.
 *
 * {@extends voMusicElement}
 * {@implements voIMusicTimeSignature, voIMusicElement}
 */
typedef voMusicElement voMusicTimeSignature;

/**
 * Represents a time signature type.
 */
typedef enum _voMusicTimeSignatureType
{
  VO_MUSIC_TIME_SIGNATURE_TYPE_ERR = -1,    /**< Error marker. */

  VO_MUSIC_TIME_SIGNATURE_TYPE_NORMAL,      /**< Normal. */
  VO_MUSIC_TIME_SIGNATURE_TYPE_COMMON,      /**< Common. */
  VO_MUSIC_TIME_SIGNATURE_TYPE_ALLA_BREVE,  /**< Alla breve. */

  VO_MUSIC_TIME_SIGNATURE_TYPE_COUNT
}
voMusicTimeSignatureType;

/**
 * Functions composing the `IMusicTimeSignature` interface. This interface
 * exposes the public methods of the `MusicTimeSignature` type.
 *
 * {@implementingTypes voMusicTimeSignature}
 * @see VO_IMusicTimeSignature, VO_MusicTimeSignature.
 */
typedef struct _voIMusicTimeSignature
{
  /**
   * Returns the time signature type.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicTimeSignature` instance.
   *
   * @return The time signature type on success, otherwise
   *   `VO_MUSIC_TIME_SIGNATURE_TYPE_ERR`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicTimeSignature` instance.
   */
  voMusicTimeSignatureType (VO_MSE_CALL *getType)(voEngine engine, voMusicTimeSignature target);

  /**
   * Returns the time signature top annotation (optional).
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicTimeSignature` instance.
   *
   * @return The time signature top annotation as a `MusicAnnotation` instance
   *   if any. When `NULL`, use `voGetError()` to figure out whether an error
   *   occured.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicTimeSignature` instance.
   */
  voMusicAnnotation (VO_MSE_CALL *getTop)(voEngine engine, voMusicTimeSignature target);

  /**
   * Returns the time signature bottom annotation (optional).
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicTimeSignature` instance.
   *
   * @return The time signature bottom annotation as a `MusicAnnotation`
   *   instance if any. When `NULL`, use `voGetError()` to figure out whether an
   *   error occured.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicTimeSignature` instance.
   */
  voMusicAnnotation (VO_MSE_CALL *getBottom)(voEngine engine, voMusicTimeSignature target);
}
voIMusicTimeSignature;


// -- MusicHead ----------------------------------------------------------------

/**
 * Reference to an instance of the `MusicHead` type.
 *
 * {@extends voMusicElement}
 * {@implements voIMusicHead, voIMusicElement}
 */
typedef voMusicElement voMusicHead;

/**
 * Represents a head type.
 */
typedef enum _voMusicHeadType
{
  VO_MUSIC_HEAD_TYPE_ERR = -1,  /**< Error marker. */

  VO_MUSIC_HEAD_TYPE_BLACK,     /**< Black / Full. */
  VO_MUSIC_HEAD_TYPE_WHITE,     /**< White / Empty. */

  VO_MUSIC_HEAD_TYPE_COUNT
}
voMusicHeadType;

/**
 * Functions composing the `IMusicHead` interface. This interface exposes the
 * public methods of the `MusicHead` type.
 *
 * {@implementingTypes voMusicHead}
 * @see VO_IMusicHead, VO_MusicHead.
 */
typedef struct _voIMusicHead
{
  /**
   * Returns the type of head.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicHead` instance.
   *
   * @return the type of head on success, otherwise `VO_MUSIC_HEAD_TYPE_ERR`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicHead` instance.
   */
  voMusicHeadType (VO_MSE_CALL *getType)(voEngine engine, voMusicHead target);
}
voIMusicHead;


// -- MusicStem ----------------------------------------------------------------

/**
 * Reference to an instance of the `MusicStem` type.
 *
 * {@extends voMusicElement}
 * {@implements voIMusicStem, voIMusicElement}
 */
typedef voMusicElement voMusicStem;

/**
 * Represents a stem type.
 */
typedef enum _voMusicStemType
{
  VO_MUSIC_STEM_TYPE_ERR = -1,    /**< Error marker. */

  VO_MUSIC_STEM_TYPE_UP,          /**< Up. */
  VO_MUSIC_STEM_TYPE_UP_FLAG1,    /**< Up eighth. */
  VO_MUSIC_STEM_TYPE_UP_FLAG2,    /**< Up 16th. */
  VO_MUSIC_STEM_TYPE_UP_FLAG3,    /**< Up 32nd. */
  VO_MUSIC_STEM_TYPE_UP_FLAG4,    /**< Up 64th. */

  VO_MUSIC_STEM_TYPE_DOWN,        /**< Down. */
  VO_MUSIC_STEM_TYPE_DOWN_FLAG1,  /**< Down eighth. */
  VO_MUSIC_STEM_TYPE_DOWN_FLAG2,  /**< Down 16th. */
  VO_MUSIC_STEM_TYPE_DOWN_FLAG3,  /**< Down 32nd. */
  VO_MUSIC_STEM_TYPE_DOWN_FLAG4,  /**< Down 64th. */

  VO_MUSIC_STEM_TYPE_COUNT
}
voMusicStemType;

/**
 * Functions composing the `IMusicStem` interface. This interface exposes the
 * public methods of the `MusicStem` type.
 *
 * {@implementingTypes voMusicStem}
 * @see VO_IMusicStem, VO_MusicStem.
 */
typedef struct _voIMusicStem
{
  /**
   * Returns the type of stem.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicStem` instance.
   *
   * @return the type of stem on success, otherwise `VO_MUSIC_STEM_TYPE_ERR`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicStem` instance.
   */
  voMusicStemType (VO_MSE_CALL *getType)(voEngine engine, voMusicStem target);
}
voIMusicStem;


// -- MusicBeam ----------------------------------------------------------------

/**
 * Reference to an instance of the `MusicBeam` type.
 *
 * {@extends voMusicElement}
 * {@implements voIMusicElement}
 */
typedef voMusicElement voMusicBeam;

/**
 * Represents a beam type.
 */
typedef enum _voMusicBeamType
{
  VO_MUSIC_BEAM_TYPE_ERR = -1,      /**< Error marker. */

  VO_MUSIC_BEAM_TYPE_BEGIN,         /**< Begin. */
  VO_MUSIC_BEAM_TYPE_CONTINUE,      /**< Continue. */
  VO_MUSIC_BEAM_TYPE_END,           /**< End. */
  VO_MUSIC_BEAM_TYPE_FORWARD_HOOK,  /**< Forward hook. */
  VO_MUSIC_BEAM_TYPE_BACKWARD_HOOK, /**< Backward hook. */

  VO_MUSIC_BEAM_TYPE_COUNT
}
voMusicBeamType;

typedef enum _voMusicBeamSlope
{
  VO_MUSIC_BEAM_SLOPE_ERR = -1,   /**< Error marker. */

  VO_MUSIC_BEAM_SLOPE_HORIZONTAL, /**< Horizontal beam. */
  VO_MUSIC_BEAM_SLOPE_UP,         /**< Upslope beam. */
  VO_MUSIC_BEAM_SLOPE_DOWN,       /**< Downslope beam. */

  VO_MUSIC_BEAM_SLOPE_COUNT
}
voMusicBeamSlope;

/**
 * Functions composing the `IMusicBeam` interface. This interface exposes the
 * public methods of the `MusicBeam` placement.
 *
 * {@implementingPlacements voMusicBeam}
 * @see VO_IMusicBeam, VO_MusicBeam.
 */
typedef struct _voIMusicBeam
{
  /**
   * Returns the placement of the beam.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicBeam` instance.
   *
   * @return the placement of the beam on success, otherwise
   *   `VO_MUSIC_PLACEMENT_ERR`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicBeam` instance.
   */
  voMusicPlacement (VO_MSE_CALL *getPlacement)(voEngine engine, voMusicBeam target);

  /**
   * Return the number of lines on the left half of the beam.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicBeam` instance.
   *
   * @return The number of dots on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicBeam` instance.
   */
  int (VO_MSE_CALL *getLeftCount)(voEngine engine, voMusicBeam target);

  /**
   * Return the number of lines on the right half of the beam.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicBeam` instance.
   *
   * @return The number of dots on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicBeam` instance.
   */
  int (VO_MSE_CALL *getRightCount)(voEngine engine, voMusicBeam target);
}
voIMusicBeam;


// -- MusicDots ----------------------------------------------------------------

/**
 * Reference to an instance of the `MusicDots` type.
 *
 * {@extends voMusicElement}
 * {@implements voIMusicDots, voIMusicElement}
 */
typedef voMusicElement voMusicDots;

/**
 * Functions composing the `IMusicDots` interface. This interface exposes the
 * public methods of the `MusicDots` type.
 *
 * {@implementingTypes voMusicDots}
 * @see VO_IMusicDots, VO_MusicDots.
 */
typedef struct _voIMusicDots
{
  /**
   * Return the number of dots.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicDots` instance.
   *
   * @return The number of dots on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicDots` instance.
   */
  int (VO_MSE_CALL *getCount)(voEngine engine, voMusicDots target);
}
voIMusicDots;


// -- MusicTie -----------------------------------------------------------------

/**
 * Reference to an instance of the `MusicTie` type.
 *
 * {@extends voMusicElement}
 * {@implements voIMusicTie, voIMusicElement}
 */
typedef voMusicElement voMusicTie;

/**
 * Functions composing the `IMusicTie` interface. This interface exposes the
 * public methods of the `MusicTie` placement.
 *
 * {@implementingPlacements voMusicTie}
 * @see VO_IMusicTie, VO_MusicTie.
 */
typedef struct _voIMusicTie
{
  /**
   * Returns the placement of the tie.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicTie` instance.
   *
   * @return the placement of the tie on success, otherwise
   *   `VO_MUSIC_PLACEMENT_ERR`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicTie` instance.
   */
  voMusicPlacement (VO_MSE_CALL *getPlacement)(voEngine engine, voMusicTie target);
}
voIMusicTie;


// -- MusicSlur ----------------------------------------------------------------

/**
 * Reference to an instance of the `MusicSlur` type.
 *
 * {@extends voMusicElement}
 * {@implements voIMusicSlur, voIMusicElement}
 */
typedef voMusicElement voMusicSlur;

/**
 * Functions composing the `IMusicSlur` interface. This interface exposes the
 * public methods of the `MusicSlur` placement.
 *
 * {@implementingPlacements voMusicSlur}
 * @see VO_IMusicSlur, VO_MusicSlur.
 */
typedef struct _voIMusicSlur
{
  /**
   * Returns the placement of the slur.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicSlur` instance.
   *
   * @return the placement of the slur on success, otherwise
   *   `VO_MUSIC_PLACEMENT_ERR`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicSlur` instance.
   */
  voMusicPlacement (VO_MSE_CALL *getPlacement)(voEngine engine, voMusicSlur target);
}
voIMusicSlur;


// -- MusicLedgerLine ----------------------------------------------------------

/**
 * Reference to an instance of the `MusicLedgerLine` type.
 *
 * {@extends voMusicElement}
 * {@implements voIMusicElement}
 */
typedef voMusicElement voMusicLedgerLine;


// -- MusicNote ----------------------------------------------------------------

/**
 * Reference to an instance of the `MusicNote` type.
 *
 * {@extends voMusicElement}
 * {@implements voIMusicNote, voIMusicElement}
 */
typedef voMusicElement voMusicNote;

/**
 * Represents a pitch step.
 */
typedef enum _voMusicPitchStep
{
  VO_MUSIC_PITCH_STEP_UNKNOWN,  /**< Unknown pitch step. */

  VO_MUSIC_PITCH_STEP_A,        /**< A. */
  VO_MUSIC_PITCH_STEP_B,        /**< B. */
  VO_MUSIC_PITCH_STEP_C,        /**< C. */
  VO_MUSIC_PITCH_STEP_D,        /**< D. */
  VO_MUSIC_PITCH_STEP_E,        /**< E. */
  VO_MUSIC_PITCH_STEP_F,        /**< F. */
  VO_MUSIC_PITCH_STEP_G,        /**< G. */

  VO_MUSIC_PITCH_STEP_COUNT
}
voMusicPitchStep;

/**
 * Represents pitch data.
 */
typedef struct _voMusicPitchData
{
  voMusicPitchStep step;  /**< Pitch data. */
  int32_t octave;         /**< Octave. */
  int32_t alteration;     /**< Chromatic alteration. */
}
voMusicPitchData;

/**
 * Represents a note type.
 */
typedef enum _voMusicNoteType
{
  VO_MUSIC_NOTE_TYPE_ERR = -1,        /**< Error marker. */

  VO_MUSIC_NOTE_TYPE_WHOLE,           /**< Whole. */
  VO_MUSIC_NOTE_TYPE_HALF,            /**< Half. */
  VO_MUSIC_NOTE_TYPE_QUARTER,         /**< Quarter. */
  VO_MUSIC_NOTE_TYPE_EIGHTH,          /**< Eighth. */
  VO_MUSIC_NOTE_TYPE_SIXTEENTH,       /**< 16th. */
  VO_MUSIC_NOTE_TYPE_THIRTY_SECOND,   /**< 32nd. */
  VO_MUSIC_NOTE_TYPE_SIXTY_FOURTH,    /**< 64th. */

  VO_MUSIC_NOTE_TYPE_COUNT
}
voMusicNoteType;

/**
 * Functions composing the `IMusicNote` interface. This interface exposes the
 * public methods of the `MusicNote` type.
 *
 * {@implementingTypes voMusicNote}
 * @see VO_IMusicNote, VO_MusicNote.
 */
typedef struct _voIMusicNote
{
  /**
   * Returns the note type.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicNote` instance.
   * @return The note type on success, otherwise `VO_NUSIC_NOTE_TYPE_ERR`.
   *
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicNote` instance.
   */
  voMusicNoteType (VO_MSE_CALL *getType)(voEngine engine, voMusicNote target);

  /**
   * Returns the note pitch.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicNote` instance.
   * @param data Recipient for the signature data.
   *
   * @return `true` on success, otherwise `false`
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicNote` instance.
   * @throws VO_INVALID_USER_BUFFER The `data` recipient is not writable.
   */
  bool (VO_MSE_CALL *getPitch)(voEngine engine, voMusicNote target, voMusicPitchData* data);

  /**
   * Returns the note duration.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicNote` instance.
   * @param divisions Number of divisions.
   *
   * @return the note duration on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicNote` instance.
   * @throws VO_INVALID_ARGUMENT When `division <= 0`.
   */
  int (VO_MSE_CALL *getDuration)(voEngine engine, voMusicNote target, int divisions);

  /**
   * Returns the line on which the note is positioned.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicNote` instance.
   *
   * @return The line on which the note is positioned on success, otherwise
   *   `INT32_MAX`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicNote` instance.
   */
  int32_t (VO_MSE_CALL *getLine)(voEngine engine, voMusicNote target);

  /**
   * Returns the note head.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicNote` instance.
   *
   * @return The note head as a `MusicHead` instance on success, otherwise
   *   `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicNote` instance.
   */
  voMusicHead (VO_MSE_CALL *getHead)(voEngine engine, voMusicNote target);

  /**
   * Returns the note stem (optional).
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicNote` instance.
   *
   * @return The note stem as a `MusicStem` instance if any.
   *   When `NULL`, use `voGetError()` to figure out whether an error occured.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicNote` instance.
   */
  voMusicStem (VO_MSE_CALL *getStem)(voEngine engine, voMusicNote target);

  /**
   * Returns the note accidental (optional).
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicNote` instance.

   * @return The note accidental as a `MusicAccidental` instance if any.
   *   When `NULL`, use `voGetError()` to figure out whether an error occured.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicNote` instance.
   */
  voMusicAccidental (VO_MSE_CALL *getAccidental)(voEngine engine, voMusicNote target);

  /**
   * Returns the note dots (optional).
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicNote` instance.
   *
   * @return The note dots as a `MusicDots` instance if any.
   *   When `NULL`, use `voGetError()` to figure out whether an error occured.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicNote` instance.
   */
  voMusicDots (VO_MSE_CALL *getDots)(voEngine engine, voMusicNote target);

  /**
   * Returns the number of beam types on this note.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicNote` instance.
   *
   * @return The number of beam types on this note on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicNote` instance.
   */
  int (VO_MSE_CALL *getBeamTypeCount)(voEngine engine, voMusicNote target);

  /**
   * Returns the beam type at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicNote` instance.
   * @param index Index of the requested note beam.
   *
   * @return The beam type at the specified `index` on success, otherwise
   *   `VO_MUSIC_BEAM_TYPE_ERR`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicNote` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voMusicBeamType (VO_MSE_CALL *getBeamTypeAt)(voEngine engine, voMusicNote target, int index);

  /**
   * Returns the beam starting from this note (optional).
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicNote` instance.
   *
   * @return The starting beam as a `MusicBeam` instance if any.
   *   When `NULL`, use `voGetError()` to figure out whether an error occured.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicNote` instance.
   */
  voMusicBeam (VO_MSE_CALL *getStartBeam)(voEngine engine, voMusicNote target);

  /**
   * Returns the beam stopping on this note (optional).
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicNote` instance.
   *
   * @return The stopping beam as a `MusicBeam` instance if any.
   *   When `NULL`, use `voGetError()` to figure out whether an error occured.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicNote` instance.
   */
  voMusicBeam (VO_MSE_CALL *getStopBeam)(voEngine engine, voMusicNote target);

  /**
   * Returns the tie starting from this note (optional).
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicNote` instance.
   *
   * @return The starting tie as a `MusicTie` instance if any.
   *   When `NULL`, use `voGetError()` to figure out whether an error occured.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicNote` instance.
   */
  voMusicTie (VO_MSE_CALL *getStartTie)(voEngine engine, voMusicNote target);

  /**
   * Returns the tie stopping on this note (optional).
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicNote` instance.
   *
   * @return The stopping tie as a `MusicTie` instance if any.
   *   When `NULL`, use `voGetError()` to figure out whether an error occured.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicNote` instance.
   */
  voMusicTie (VO_MSE_CALL *getStopTie)(voEngine engine, voMusicNote target);

  /**
   * Returns the number slurs starting from this note.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicNote` instance.
   *
   * @return The number of slurs starting from this note on success, otherwise
   *   `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicNote` instance.
   */
  int (VO_MSE_CALL *getStartSlurCount)(voEngine engine, voMusicNote target);

  /**
   * Returns the starting slur at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicNote` instance.
   * @param index Index of the requested slur.
   *
   * @return A reference to a `MusicSlur` instance on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicNote` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voMusicSlur (VO_MSE_CALL *getStartSlurAt)(voEngine engine, voMusicNote target, int index);

  /**
   * Returns the number slurs stopping from this note.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicNote` instance.
   *
   * @return The number of slurs stopping on this note on success, otherwise
   *   `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicNote` instance.
   */
  int (VO_MSE_CALL *getStopSlurCount)(voEngine engine, voMusicNote target);

  /**
   * Returns the stopping slur at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicNote` instance.
   * @param index Index of the requested slur.
   *
   * @return A reference to a `MusicSlur` instance on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicNote` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voMusicSlur (VO_MSE_CALL *getStopSlurAt)(voEngine engine, voMusicNote target, int index);

  /**
   * Returns the number of ledger lines for this note.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicNote` instance.
   *
   * @return The number of ledger lines for this note this note on success,
   *   otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicNote` instance.
   */
  int (VO_MSE_CALL *getLedgerLineCount)(voEngine engine, voMusicNote target);

  /**
   * Returns the ledger line at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicNote` instance.
   * @param index Index of the requested ledger line.
   *
   * @return A reference to a `MusicLedgerLine` instance on success, otherwise
   *   `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicNote` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voMusicLedgerLine (VO_MSE_CALL *getLedgerLineAt)(voEngine engine, voMusicNote target, int index);

  /**
   * Returns the number of articulation marks on this note.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicNote` instance.
   *
   * @return The number of articulation marks on this note on success, otherwise
   *   `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicNote` instance.
   */
  int (VO_MSE_CALL *getArticulationMarkCount)(voEngine engine, voMusicNote target);

  /**
   * Returns the articulation mark at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicNote` instance.
   * @param index Index of the requested articulation mark.
   *
   * @return A reference to a `MusicArticulationMark` instance on success,
   *   otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicNote` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voMusicArticulationMark (VO_MSE_CALL *getArticulationMarkAt)(voEngine engine, voMusicNote target, int index);
}
voIMusicNote;


// -- MusicRest ----------------------------------------------------------------

/**
 * Reference to an instance of the `MusicRest` type.
 *
 * {@extends voMusicElement}
 * {@implements voIMusicRest, voIMusicElement}
 */
typedef voMusicElement voMusicRest;

/**
 * Represents a rest type.
 */
typedef enum _voMusicRestType
{
  VO_MUSIC_REST_TYPE_ERR = -1,        /**< Error marker. */

  VO_MUSIC_REST_TYPE_WHOLE,           /**< Whole. */
  VO_MUSIC_REST_TYPE_HALF,            /**< Half. */
  VO_MUSIC_REST_TYPE_QUARTER,         /**< Quarter. */
  VO_MUSIC_REST_TYPE_EIGHTH,          /**< Eighth. */
  VO_MUSIC_REST_TYPE_SIXTEENTH,       /**< 16th. */
  VO_MUSIC_REST_TYPE_THIRTY_SECOND,   /**< 32nd. */
  VO_MUSIC_REST_TYPE_SIXTY_FOURTH,    /**< 64th. */

  VO_MUSIC_REST_TYPE_COUNT
}
voMusicRestType;

/**
 * Functions composing the `IMusicRest` interface. This interface exposes the
 * public methods of the `MusicRest` type.
 *
 * {@implementingTypes voMusicRest}
 * @see VO_IMusicRest, VO_MusicRest.
 */
typedef struct _voIMusicRest
{
  /**
   * Returns the rest type.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicRest` instance.
   *
   * @return The rest type on success, otherwise `VO_MUSIC_REST_TYPE_ERR`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicRest` instance.
   */
  voMusicRestType (VO_MSE_CALL *getType)(voEngine engine, voMusicRest target);

  /**
   * Returns the rest duration.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicRest` instance.
   * @param divisions Number of divisions.
   *
   * @return the rest duration on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicRest` instance.
   */
  int (VO_MSE_CALL *getDuration)(voEngine engine, voMusicRest target, int divisions);

  /**
   * Returns the rest dots (optional).
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicRest` instance.
   *
   * @return The rest dots as a `MusicDots` instance.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicRest` instance.
   */
  voMusicDots (VO_MSE_CALL *getDots)(voEngine engine, voMusicRest target);

  /**
   * Returns the number slurs starting from this rest.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicRest` instance.
   *
   * @return The number of slurs starting from this rest on success, otherwise
   *   `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicRest` instance.
   */
  int (VO_MSE_CALL *getStartSlurCount)(voEngine engine, voMusicRest target);

  /**
   * Returns the starting slur at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicRest` instance.
   * @param index Index of the requested slur.
   *
   * @return A reference to a `MusicSlur` instance on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicRest` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voMusicSlur (VO_MSE_CALL *getStartSlurAt)(voEngine engine, voMusicRest target, int index);

  /**
   * Returns the number slurs stopping from this rest.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicRest` instance.
   *
   * @return The number of slurs stopping on this rest on success, otherwise
   *   `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicRest` instance.
   */
  int (VO_MSE_CALL *getStopSlurCount)(voEngine engine, voMusicRest target);

  /**
   * Returns the stopping slur at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicRest` instance.
   * @param index Index of the requested slur.
   *
   * @return A reference to a `MusicSlur` instance on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicRest` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voMusicSlur (VO_MSE_CALL *getStopSlurAt)(voEngine engine, voMusicRest target, int index);

  /**
   * Returns the number of articulation marks on this rest.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicRest` instance.
   *
   * @return The number of articulation marks on this rest on success, otherwise
   *   `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicRest` instance.
   */
  int (VO_MSE_CALL *getArticulationMarkCount)(voEngine engine, voMusicRest target);

  /**
   * Returns the articulation mark at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicRest` instance.
   * @param index Index of the requested articulation mark.
   *
   * @return A reference to a `MusicArticulationMark` instance on success,
   *   otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicRest` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voMusicArticulationMark (VO_MSE_CALL *getArticulationMarkAt)(voEngine engine, voMusicRest target, int index);
}
voIMusicRest;


// -- MusicChord ---------------------------------------------------------------

/**
 * Reference to an instance of the `MusicChord` type.
 *
 * {@extends voMusicElement}
 * {@implements voIMusicChord, voIMusicElement}
 */
typedef voMusicElement voMusicChord;

/**
 * Functions composing the `IMusicChord` interface. This interface exposes the
 * public methods of the `MusicChord` type.
 *
 * {@implementingTypes voMusicChord}
 * @see VO_IMusicChord, VO_MusicChord.
 */
typedef struct _voIMusicChord
{
  /**
   * Returns the chord duration.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicChord` instance.
   * @param divisions Number of divisions.
   *
   * @return the chord duration on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicChord` instance.
   */
  int (VO_MSE_CALL *getDuration)(voEngine engine, voMusicChord target, int divisions);

  /**
   * Returns the chord stem (optional).
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicChord` instance.
   *
   * @return The chord stem as a `MusicStem` instance if any.
   *   When `NULL`, use `voGetError()` to figure out whether an error occured.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicChord` instance.
   */
  voMusicStem (VO_MSE_CALL *getStem)(voEngine engine, voMusicChord target);

  /**
   * Returns the number of beam types on this chord.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicChord` instance.
   *
   * @return The number of beam types on this chord on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicChord` instance.
   */
  int (VO_MSE_CALL *getBeamTypeCount)(voEngine engine, voMusicChord target);

  /**
   * Returns the beam type at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicChord` instance.
   * @param index Index of the requested chord beam.
   *
   * @return The beam type at the specified `index` on success, otherwise
   *   `VO_MUSIC_BEAM_TYPE_ERR`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicChord` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voMusicBeamType (VO_MSE_CALL *getBeamTypeAt)(voEngine engine, voMusicChord target, int index);

  /**
   * Returns the beam starting from this chord (optional).
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicChord` instance.
   *
   * @return The start beam as a `MusicBeam` instance if any.
   *   When `NULL`, use `voGetError()` to figure out whether an error occured.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicChord` instance.
   */
  voMusicBeam (VO_MSE_CALL *getStartBeam)(voEngine engine, voMusicChord target);

  /**
   * Returns the beam stopping on this chord (optional).
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicChord` instance.
   *
   * @return The stopping beam as a `MusicBeam` instance if any.
   *   When `NULL`, use `voGetError()` to figure out whether an error occured.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicChord` instance.
   */
  voMusicBeam (VO_MSE_CALL *getStopBeam)(voEngine engine, voMusicChord target);

  /**
   * Returns the number slurs starting from this chord.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicChord` instance.
   *
   * @return The number of slurs starting from this chord on success, otherwise
   *   `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicChord` instance.
   */
  int (VO_MSE_CALL *getStartSlurCount)(voEngine engine, voMusicChord target);

  /**
   * Returns the starting slur at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicChord` instance.
   * @param index Index of the requested slur.
   *
   * @return A reference to a `MusicSlur` instance on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicChord` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voMusicSlur (VO_MSE_CALL *getStartSlurAt)(voEngine engine, voMusicChord target, int index);

  /**
   * Returns the number slurs stopping from this chord.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicChord` instance.
   *
   * @return The number of slurs stopping on this chord on success, otherwise
   *   `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicChord` instance.
   */
  int (VO_MSE_CALL *getStopSlurCount)(voEngine engine, voMusicChord target);

  /**
   * Returns the stopping slur at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicChord` instance.
   * @param index Index of the requested slur.
   *
   * @return A reference to a `MusicSlur` instance on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicChord` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voMusicSlur (VO_MSE_CALL *getStopSlurAt)(voEngine engine, voMusicChord target, int index);

  /**
   * Returns the number of ledger lines for this chord.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicChord` instance.
   *
   * @return The number of ledger lines for this chord this chord on success,
   *   otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicChord` instance.
   */
  int (VO_MSE_CALL *getLedgerLineCount)(voEngine engine, voMusicChord target);

  /**
   * Returns the ledger line at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicChord` instance.
   * @param index Index of the requested ledger line.
   *
   * @return A reference to a `MusicLedgerLine` instance on success, otherwise
   *   `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicChord` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voMusicLedgerLine (VO_MSE_CALL *getLedgerLineAt)(voEngine engine, voMusicChord target, int index);

  /**
   * Returns the number of articulation marks on this chord.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicChord` instance.
   *
   * @return The number of articulation marks on this chord on success,
   *   otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicChord` instance.
   */
  int (VO_MSE_CALL *getArticulationMarkCount)(voEngine engine, voMusicChord target);

  /**
   * Returns the articulation mark at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicChord` instance.
   * @param index Index of the requested articulation mark.
   *
   * @return A reference to a `MusicArticulationMark` instance on success,
   *   otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicChord` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voMusicArticulationMark (VO_MSE_CALL *getArticulationMarkAt)(voEngine engine, voMusicChord target, int index);

  /**
   * Returns the number of notes in this chord.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicChord` instance.
   *
   * @return The number of notes in this chord on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicChord` instance.
   */
  int (VO_MSE_CALL *getNoteCount)(voEngine engine, voMusicChord target);

  /**
   * Returns the note at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicChord` instance.
   * @param index Index of the requested chord line.
   *
   * @return A reference to a `MusicNote` instance on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicChord` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voMusicNote (VO_MSE_CALL *getNoteAt)(voEngine engine, voMusicChord target, int index);
}
voIMusicChord;


// -- MusicPart ----------------------------------------------------------------

/**
 * Reference to an instance of the `MusicPart` type.
 *
 * {@extends voEngineObject}
 * {@implements voIMusicPart}
 */
typedef voEngineObject voMusicPart;

/**
 * Functions composing the `IMusicPart` interface. This interface exposes the
 * public methods of the `MusicPart` type.
 *
 * {@implementingTypes voMusicPart}
 * @see VO_IMusicPart, VO_MusicPart.
 */
typedef struct _voIMusicPart
{
  /**
   * Returns the number of elements in this part.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicPart` instance.
   *
   * @return The number of elements in this part on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicPart` instance.
   */
  int (VO_MSE_CALL *getElementCount)(voEngine engine, voMusicPart target);

  /**
   * Returns the element at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicPart` instance.
   * @param index Index of the requested element.
   *
   * @return A reference to a `MusicElement` instance on success, otherwise
   *   `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicPart` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voMusicElement (VO_MSE_CALL *getElementAt)(voEngine engine, voMusicPart target, int index);
}
voIMusicPart;


// -- MusicScore ---------------------------------------------------------------

/**
 * Reference to an instance of the `MusicScore` type.
 *
 * {@extends voEngineObject}
 * {@implements voIMusicScore}
 */
typedef voEngineObject voMusicScore;

/**
 * Functions composing the `IMusicScore` interface. This interface exposes the
 * public methods of the `MusicScore` type.
 *
 * {@implementingTypes voMusicScore}
 * @see VO_IMusicScore, VO_MusicScore.
 */
typedef struct _voIMusicScore
{
  /**
   * Returns the number of parts in this document.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicPart` instance.
   *
   * @return The number of parts in this document on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicScore` instance.
   */
  int (VO_MSE_CALL *getPartCount)(voEngine engine, voMusicScore target);

  /**
   * Returns the part at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicScore` instance.
   * @param index Index of the requested part.
   *
   * @return A reference to a `MusicPart` instance on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicScore` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_LIMIT_EXCEEDED The number of `MusicPart` instances would exceed
   *   the allowed limit. (please remember that the limit can be shared by
   *   several types).
   */
  voMusicPart (VO_MSE_CALL *getPartAt)(voEngine engine, voMusicScore target, int index);
}
voIMusicScore;


// -- MusicScratchOut ----------------------------------------------------------

/**
 * Reference to an instance of the MusicScratchOut` type.
 *
 * {@implements voIMusicScratchOut}
 *
 * @since 6.1_0
 */
typedef voEngineObject voMusicScratchOut;

/**
 * Functions composing the `IMusicScratchOut` interface. This interface exposes
 * the public methods of the `MusicScratchOut` type.
 *
 * {@implementingTypes voMusicScratchOut}
 * @see VO_IMusicScratchOut, VO_MusicScratchOut.
 *
 * @since 6.1_0
 */
typedef struct _voIMusicScratchOut
{
  /**
   * Returns the number of input ranges this scratch out covers.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `MusicScratchOut` instance.
   *
   * @return The number of input ranges this scratch out covers on success,
   *   otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicScratchOut` instance.
   */
  uint32_t (VO_MSE_CALL *getInputRangeCount)(voEngine engine, voMusicScratchOut target);

  /**
   * Returns the input range at the specified `index` this scratch out covers.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `MusicScratchOut` instance.
   * @param index The zero-based index of the input range to be retrieved.
   * @param inputRange Recipient for the input range result.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicScratchOut` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_INVALID_USER_BUFFER The `range` recipient is not writable.
   */
  bool (VO_MSE_CALL *getInputRangeAt)(voEngine engine, voMusicScratchOut target, uint32_t index, voMusicInputRange* range);

  /**
   * Returns the number of input ranges this scratch out erases.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `MusicScratchOut` instance.
   *
   * @return The number of input ranges this scratch out covers on success,
   *   otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicScratchOut` instance.
   */
  uint32_t (VO_MSE_CALL *getErasedInputRangeCount)(voEngine engine, voMusicScratchOut target);

  /**
   * Returns the input range at the specified `index` this scratch out erases.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `MusicScratchOut` instance.
   * @param index The zero-based index of the input range to be retrieved.
   * @param inputRange Recipient for the input range result.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicScratchOut` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  bool (VO_MSE_CALL *getErasedInputRangeAt)(voEngine engine, voMusicScratchOut target, uint32_t index, voMusicInputRange* range);
}
voIMusicScratchOut;


// -- MusicDocument ------------------------------------------------------------

/**
 * Reference to an instance of the `MusicDocument` type.
 *
 * {@implements voIMusicDocument}
 */
typedef voEngineObject voMusicDocument;

/**
 * Functions composing the `IMusicDocument` interface. This interface exposes
 * the public methods of the `MusicDocument` type.
 *
 * {@implementingTypes voMusicDocument}
 * @see VO_IMusicDocument, VO_MusicDocument.
 */
typedef struct _voIMusicDocument
{
  /**
   * Clears this `MusicDocument` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicDocument` instance.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicDocument` instance.
   */
  bool (VO_MSE_CALL *clear)(voEngine engine, voMusicDocument target);

  /**
   * Adds a staff by defining line positions.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicDocument` instance.
   * @param count Number of lines in the staff.
   * @param top Position of the top line along the y axis.
   * @param gap Distance between two consecutive lines.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicDocument` instance.
   * @throws VO_LIMIT_EXCEEDED The number of staves would exceed the current
   *   limit equal to 1.
   * @throws VO_INVALID_ARGUMENT When `count != 5`.
   * @throws VO_INVALID_ARGUMENT When `gap <= 0`.
   */
  bool (VO_MSE_CALL *addStaff)(voEngine engine, voMusicDocument target, int count, float top, float gap);

  /**
   * Adds a digital pen stroke to this `MusicDocument` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicDocument` instance.
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
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicDocument` instance.
   * @throws VO_INVALID_ARGUMENT When `xByteStride == 0`
   * @throws VO_INVALID_ARGUMENT When `yByteStride == 0`
   * @throws VO_INVALID_ARGUMENT When `pointCount == 0`
   * @throws VO_INVALID_USER_BUFFER The combination of `x`, `xByteStride`, `y`,
   *   `yByteStride` and `pointCount` leads to invalid memory access.
   * @throws VO_LIMIT_EXCEEDED When `pointCount > 32767`
   */
  bool (VO_MSE_CALL *addStroke)(voEngine engine, voMusicDocument target, const float* x, size_t xByteStride, const float* y, size_t yByteStride, int pointCount);

  /**
   * Adds an articulation mark with respect to its position in this
   * `MusicDocument` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicDocument` instance.
   * @param symbol The symbol of the articulation mark to be added.
   * @param placement The placement of the articulation mark to be added.
   * @param x The x position of the enclosing rectangle of the element.
   * @param y The y position of the enclosing rectangle of the element.
   * @param width The width of the enclosing rectangle of the element.
   * @param height The height of the enclosing rectangle of the element.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicDocument` instance.
   * @throws VO_INVALID_ARGUMENT The `symbol` value is invalid.
   * @throws VO_INVALID_ARGUMENT The `placement` value is invalid.
   * @throws VO_INVALID_ARGUMENT The `width` is less than or equal to 0.
   * @throws VO_INVALID_ARGUMENT The `height` is less than or equal to 0.
   */
  bool (VO_MSE_CALL *addArticulationMark)(voEngine engine, voMusicDocument target, voMusicArticulationMarkSymbol symbol, voMusicPlacement placement, float x, float y, float width, float height);

  /**
   * Adds a bar with respect to its position in this `MusicDocument` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicDocument` instance.
   * @param style The style of the bar to be added.
   * @param repeatDirection The repeat direction of the bar to be added.
   * @param x The x position of the enclosing rectangle of the element.
   * @param y The y position of the enclosing rectangle of the element.
   * @param width The width of the enclosing rectangle of the element.
   * @param height The height of the enclosing rectangle of the element.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicDocument` instance.
   * @throws VO_INVALID_ARGUMENT The `style` value is invalid.
   * @throws VO_INVALID_ARGUMENT The `repeatDirection` value is invalid.
   * @throws VO_INVALID_ARGUMENT The combination of `style` and
   *   `repeatDirection` is invalid.
   * @throws VO_INVALID_ARGUMENT The `width` is less than or equal to 0.
   * @throws VO_INVALID_ARGUMENT The `height` is less than or equal to 0.
   */
  bool (VO_MSE_CALL *addBar)(voEngine engine, voMusicDocument target, voMusicBarStyle style, voMusicBarRepeatDirection repeatDirection, float x, float y, float width, float height);

  /**
   * Adds a clef with respect to its position in this `MusicDocument` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicDocument` instance.
   * @param style The symbol of the clef to be added.
   * @param octave The octave of the clef to be added.
   * @param yAnchor The y position of the anchor point of the clef to be added.
   * @param x The x position of the enclosing rectangle of the element.
   * @param y The y position of the enclosing rectangle of the element.
   * @param width The width of the enclosing rectangle of the element.
   * @param height The height of the enclosing rectangle of the element.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicDocument` instance.
   * @throws VO_INVALID_ARGUMENT The `symbol` value is invalid.
   * @throws VO_INVALID_ARGUMENT The `octave` value is invalid.
   * @throws VO_INVALID_ARGUMENT The `width` is less than or equal to 0.
   * @throws VO_INVALID_ARGUMENT The `height` is less than or equal to 0.
   */
  bool (VO_MSE_CALL *addClef)(voEngine engine, voMusicDocument target, voMusicClefSymbol symbol, int32_t octave, float yAnchor, float x, float y, float width, float height);

  /**
   * Adds an accidental with respect to its position in this `MusicDocument`
   * instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicDocument` instance.
   * @param type The type of the accidendal to be added.
   * @param x The x position of the enclosing rectangle of the element.
   * @param y The y position of the enclosing rectangle of the element.
   * @param width The width of the enclosing rectangle of the element.
   * @param height The height of the enclosing rectangle of the element.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicDocument` instance.
   * @throws VO_INVALID_ARGUMENT The `type` value is invalid.
   * @throws VO_INVALID_ARGUMENT The `width` is less than or equal to 0.
   * @throws VO_INVALID_ARGUMENT The `height` is less than or equal to 0.
   */
  bool (VO_MSE_CALL *addAccidental)(voEngine engine, voMusicDocument target, voMusicAccidentalType type, float x, float y, float width, float height);

  /**
   * Adds a time signature with respect to its position in this `MusicDocument`
   * instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicDocument` instance.
   * @param type The type of the time signature to be added (common or alla
   *   breve).
   * @param x The x position of the enclosing rectangle of the element.
   * @param y The y position of the enclosing rectangle of the element.
   * @param width The width of the enclosing rectangle of the element.
   * @param height The height of the enclosing rectangle of the element.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicDocument` instance.
   * @throws VO_INVALID_ARGUMENT The `type` value is invalid.
   * @throws VO_INVALID_ARGUMENT The `width` is less than or equal to 0.
   * @throws VO_INVALID_ARGUMENT The `height` is less than or equal to 0.
   */
  bool (VO_MSE_CALL *addTimeSignature)(voEngine engine, voMusicDocument target, voMusicTimeSignatureType type, float x, float y, float width, float height);

  /**
   * Adds a note head with respect to its position in this `MusicDocument`
   * instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicDocument` instance.
   * @param type The type of the head to be added.
   * @param x The x position of the enclosing rectangle of the element.
   * @param y The y position of the enclosing rectangle of the element.
   * @param width The width of the enclosing rectangle of the element.
   * @param height The height of the enclosing rectangle of the element.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicDocument` instance.
   * @throws VO_INVALID_ARGUMENT The `type` value is invalid.
   * @throws VO_INVALID_ARGUMENT The `width` is less than or equal to 0.
   * @throws VO_INVALID_ARGUMENT The `height` is less than or equal to 0.
   */
  bool (VO_MSE_CALL *addHead)(voEngine engine, voMusicDocument target, voMusicHeadType type, float x, float y, float width, float height);

  /**
   * Adds a note stem with respect to its position in this `MusicDocument`
   * instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicDocument` instance.
   * @param type The type of the stem to be added.
   * @param x The x position of the enclosing rectangle of the element.
   * @param y The y position of the enclosing rectangle of the element.
   * @param width The width of the enclosing rectangle of the element.
   * @param height The height of the enclosing rectangle of the element.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicDocument` instance.
   * @throws VO_INVALID_ARGUMENT The `type` value is invalid.
   * @throws VO_INVALID_ARGUMENT The `width` is less than or equal to 0.
   * @throws VO_INVALID_ARGUMENT The `height` is less than or equal to 0.
   */
  bool (VO_MSE_CALL *addStem)(voEngine engine, voMusicDocument target, voMusicStemType type, float x, float y, float width, float height);

  /**
   * Adds a note beam with respect to its position in this `MusicDocument`
   * instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicDocument` instance.
   * @param placement The placement of the beam to be added.
   * @param leftCount The number of lines on the left half of the beam to be
   *   added.
   * @param rightCount The number of lines on the right half of the beam to be
   *   added.
   * @param slope The slope of the beam to be added.
   * @param gap Distance between two consecutive lines.
   * @param x The x position of the enclosing rectangle of the element.
   * @param y The y position of the enclosing rectangle of the element.
   * @param width The width of the enclosing rectangle of the element.
   * @param height The height of the enclosing rectangle of the element.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicDocument` instance.
   * @throws VO_INVALID_ARGUMENT The `angle` value is invalid.
   * @throws VO_INVALID_ARGUMENT When `leftCount == 0`
   * @throws VO_INVALID_ARGUMENT When `leftCount > 4`
   * @throws VO_INVALID_ARGUMENT When `rightCount == 0`
   * @throws VO_INVALID_ARGUMENT When `rightCount > 4`
   * @throws VO_INVALID_ARGUMENT The `width` is less than or equal to 0.
   * @throws VO_INVALID_ARGUMENT The `height` is less than or equal to 0.
   */
  bool (VO_MSE_CALL *addBeam)(voEngine engine, voMusicDocument target, voMusicPlacement placement, int leftCount, int rightCount, voMusicBeamSlope slope, float gap, float x, float y, float width, float height);

  /**
   * Adds dots with respect to their position in this `MusicDocument`
   * instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicDocument` instance.
   * @param count The number of dots to be added.
   * @param x The x position of the enclosing rectangle of the element.
   * @param y The y position of the enclosing rectangle of the element.
   * @param width The width of the enclosing rectangle of the element.
   * @param height The height of the enclosing rectangle of the element.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicDocument` instance.
   * @throws VO_INVALID_ARGUMENT When `count == 0`
   * @throws VO_INVALID_ARGUMENT When `count > 2`
   * @throws VO_INVALID_ARGUMENT The `width` is less than or equal to 0.
   * @throws VO_INVALID_ARGUMENT The `height` is less than or equal to 0.
   */
  bool (VO_MSE_CALL *addDots)(voEngine engine, voMusicDocument target, int count, float x, float y, float width, float height);

  /**
   * Adds a note tie or a slur with respect to its position in this
   * `MusicDocument` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicDocument` instance.
   * @param placement The placement of the tie or slur to be added.
   * @param x The x position of the enclosing rectangle of the element.
   * @param y The y position of the enclosing rectangle of the element.
   * @param width The width of the enclosing rectangle of the element.
   * @param height The height of the enclosing rectangle of the element.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicDocument` instance.
   * @throws VO_INVALID_ARGUMENT The `placement` value is invalid.
   * @throws VO_INVALID_ARGUMENT The `width` is less than or equal to 0.
   * @throws VO_INVALID_ARGUMENT The `height` is less than or equal to 0.
   */
  bool (VO_MSE_CALL *addTieOrSlur)(voEngine engine, voMusicDocument target, voMusicPlacement placement, float x, float y, float width, float height);

  /**
   * Adds a ledger line with respect to its position in this `MusicDocument`
   * instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicDocument` instance.
   * @param x The x position of the enclosing rectangle of the element.
   * @param y The y position of the enclosing rectangle of the element.
   * @param width The width of the enclosing rectangle of the element.
   * @param height The height of the enclosing rectangle of the element.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicDocument` instance.
   * @throws VO_INVALID_ARGUMENT The `width` is less than or equal to 0.
   * @throws VO_INVALID_ARGUMENT The `height` is less than or equal to 0.
   */
  bool (VO_MSE_CALL *addLedgerLine)(voEngine engine, voMusicDocument target, float x, float y, float width, float height);

  /**
   * Adds a rest with respect to its position in this `MusicDocument` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicDocument` instance.
   * @param type The type of the rest to be added.
   * @param x The x position of the enclosing rectangle of the element.
   * @param y The y position of the enclosing rectangle of the element.
   * @param width The width of the enclosing rectangle of the element.
   * @param height The height of the enclosing rectangle of the element.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicDocument` instance.
   * @throws VO_INVALID_ARGUMENT The `type` value is invalid.
   * @throws VO_INVALID_ARGUMENT The `width` is less than or equal to 0.
   * @throws VO_INVALID_ARGUMENT The `height` is less than or equal to 0.
   */
  bool (VO_MSE_CALL *addRest)(voEngine engine, voMusicDocument target, voMusicRestType type, float x, float y, float width, float height);

  /**
   * Adds a digital text character with respect to its position in this
   *   `MusicDocument` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `MusicDocument` instance.
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
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to an `MusicDocument` instance.
   * @throws VO_NO_SUCH_OBJECT The `character` reference is invalid.
   * @throws VO_INVALID_OBJECT The `character` object is not an
   *   instance of the `InputCharacter` type.
   * @throws VO_INVALID_ARGUMENT The `character` contains no
   *   alternate.
   * @throws VO_INVALID_ARGUMENT The `width` is less than or equal to 0.
   * @throws VO_INVALID_ARGUMENT The `height` is less than or equal to 0.
   */
  bool (VO_MSE_CALL *addCharacter)(voEngine engine, voMusicDocument target, voInputCharacter character, float x, float y, float width, float height);

  /**
   * Deletes a component from this `MusicDocument` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicDocument` instance.
   * @param index The index of the component to be deleted.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicDocument` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  bool (VO_MSE_CALL *deleteComponentAt)(voEngine engine, voMusicDocument target, int index);

  /**
   * Undeletes a component from this `MusicDocument` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicDocument` instance.
   * @param index The index of the component to be undeleted.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicDocument` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  bool (VO_MSE_CALL *undeleteComponentAt)(voEngine engine, voMusicDocument target, int index);

  /**
   * Returns the interpretation of this `MusicDocument` instance after it has
   * been processed.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `MusicDocument` instance.
   *
   * @return A `MusicScore` instance if any.
   *   When `NULL`, use `voGetError()` to figure out whether an error occured.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to a
   *   `MusicDocument` instance.
   * @throws VO_LIMIT_EXCEEDED The number of `MusicScore` instances would exceed
   *   the allowed limit. (please remember that the limit can be shared by
   *   several types).
   * @throws VO_INVALID_STATE The `MusicDocument` has not been processed.
   */
  voMusicScore (VO_MSE_CALL *getScore)(voEngine engine, voMusicDocument target);
  
  /**
   * Returns the number of active scratch outs after this `MusicDocument`
   * instance has been processed.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `MusicDocument` instance.
   *
   * @return The number of active scratch outs on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   a `MusicDocument` instance.
   *
   * @since 6.1_0
   */
  int32_t (VO_MSE_CALL *getScratchOutCount)(voEngine engine, voMusicDocument target);


  /**
   * Returns the scratch out at the specified index after this `MusicDocument`
   * instance has been processed.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `MusicDocument` instance.
   * @param index The zero-based index of the scratch out to be retrieved.
   *
   * @return A `MusicScratchOut` instance on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   a `MusicDocument` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   *
   * @since 6.1_0
   */
  voMusicScratchOut (VO_MSE_CALL *getScratchOutAt)(voEngine engine, voMusicDocument target, int32_t index);
}
voIMusicDocument;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `MusicDocument` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `MusicDocument` object on success,
 *   otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `MusicDocument` instances would
 *   exceed the allowed limit. (please remember that the limit can be shared by
 *   several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voMusicDocument voCreateMusicDocument(voEngine engine)
{
  return voCreateObject(engine, VO_MusicDocument);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- MusicAlphabetKnowledge ---------------------------------------------------

/**
 * Reference to an instance of the `MusicAlphabetKnowledge` type.
 */
typedef voEngineObject voMusicAlphabetKnowledge;


// -- MusicGrammar -------------------------------------------------------------

/**
 * Reference to an instance of the `MusicGrammar` type.
 *
 */
typedef voEngineObject voMusicGrammar;


// -- MusicRecognizer ----------------------------------------------------------

/**
 * Reference to an instance of the `MusicRecognizer` type.
 *
 * {@implements voIAttachTarget, voIMusicRecognizer}
 *
 * @note Please refer to `MyScriptEngine.h` reference documentation of the
 *   `IAttachTarget` interface.
 */
typedef voEngineObject voMusicRecognizer;

/**
 * {@propertySet MusicRecognizer}
 */
enum VO_MUSIC_RECOGNIZER_PROP
{
  /**
   * A value between `0.0f` and `1.0f` that adjusts the scratch out detection
   * sensitivity.
   *
   * {@property float}
   *
   * @note A value equal to `0.0f` disables scratch out detection.
   */
  VO_MUSIC_RECOGNIZER_SCRATCH_OUT_DETECTION_SENSITIVITY = (VO_MusicRecognizer << 16)
};

typedef struct _voIMusicRecognizer
{
  /**
   * Performs the recognition of a `MusicDocument` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param recognizer Reference to the `MusicRecognizer` instance.
   * @param document Reference to a `MusicDocument` instance.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `recognizer` reference is invalid.
   * @throws VO_INVALID_OPERATION The `recognizer` reference is not a reference
   *   to a `MusicRecognizer` instance.
   * @throws VO_NO_SUCH_OBJECT The `document` reference is invalid.
   * @throws VO_INVALID_OBJECT The `document` object is not an instance of the
   *   `MusicDocument` type.
   * @throws VO_INVALID_CALLBACK The notification callback crashed.
   * @throws VO_INVALID_STATE The `target` object is not in a state where the
   *   `process` function can be invoked.
   * @throws VO_MISSING_MUSIC_ALPHABET_KNOWLEDGE The `MusicRecognizer` has no
   *   attached `MusicAlphabetKnowledge`.
   * @throws VO_MISSING_MUSIC_GRAMMAR The `MusicRecognizer` has no attached
   *   `MusicGrammar`.
   * @throws VO_MISSING_MUSIC_STAFF The `MusicDocument` has no staff defined.
   * @throws VO_CANCELED The operation has been canceled.
   */
  bool (VO_MSE_CALL *process)(voEngine engine, voMusicRecognizer recognizer, voMusicDocument document, voNotifyProgressFunc notifyProgressFunc, void* userParam);
}
voIMusicRecognizer;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `MusicRecognizer` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `MusicRecognizer`
 *   object on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `MusicRecognizer` instances would
 *   exceed the allowed limit (please remember that the limit can be shared by
 *   several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voMusicRecognizer voCreateMusicRecognizer(voEngine engine)
{
  return voCreateObject(engine, VO_MusicRecognizer);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS

#endif // end of: #ifndef C_MYSCRIPTMUSIC_H
