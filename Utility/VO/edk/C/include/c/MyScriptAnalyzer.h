#ifndef C_MYSCRIPTANALYZER_H
#define C_MYSCRIPTANALYZER_H 0x06010000
/**
 * @file c/MyScriptAnalyzer.h
 * Native interface to the MyScript Analyzer service.
 */

#include "MyScriptEngine.h"
#include "MyScriptHWR.h"
#include "MyScriptShape.h"


// -- error codes --------------------------------------------------------------

/**
 * Lists the MyScript Analyzer errors.
 */
enum VO_ANALYZER_ERR
{
  /**
   * Unable to complete the requested operation because an
   * `AnalyzerKnowledge` is missing.
   *
   * @see voAnalyzerKnowledge.
   */
  VO_MISSING_ANALYZER_KNOWLEDGE = VO_INVALID_STATE | (6 << 16),
};


// -- types and interfaces -----------------------------------------------------

/**
 * Lists the MyScript Analyzer types.
 */
enum VO_ANALYZER_T
{
  /**
   * `Analyzer` type.
   *
   * @see voAnalyzer.
   */
  VO_Analyzer = 2000,
  /**
   * `AnalyzerDocument` type.
   *
   * @see voAnalyzerDocument.
   */
  VO_AnalyzerDocument,
  /**
   * `AnalyzerKnowledge` type.
   *
   * @see voAnalyzerKnowledge.
   */
  VO_AnalyzerKnowledge,
  /**
   * `AnalyzerElement` type.
   *
   * @see voAnalyzerElement.
   */
  VO_AnalyzerElement,
  /**
   * `AnalyzerUnderline` type.
   *
   * @see voAnalyzerUnderline.
   */
  VO_AnalyzerUnderline,
  /**
   * `AnalyzerTextLine` type.
   *
   * @see voAnalyzerTextLine.
   */
  VO_AnalyzerTextLine,
  /**
   * `AnalyzerLine` type.
   *
   * @see voAnalyzerLine.
   */
  VO_AnalyzerLine,
  /**
   * `AnalyzerCell` type.
   *
   * @see voAnalyzerCell.
   */
  VO_AnalyzerCell,
  /**
   * `AnalyzerTable` type.
   *
   * @see voAnalyzerTable.
   */
  VO_AnalyzerTable,
  /**
   * `AnalyzerShape` type.
   *
   * @see voAnalyzerShape.
   */
  VO_AnalyzerShape,
  /**
   * `AnalyzerGroup` type.
   *
   * @see voAnalyzerGroup.
   */
  VO_AnalyzerGroup
};

/**
 * Lists the MyScript Analyzer interfaces.
 */
enum VO_ANALYZER_I
{
  /**
   * `IIAnalyzerDocument` interface type.
   *
   * @see voIIAnalyzerDocument.
   */
  VO_IAnalyzerDocument = 2100,
  /**
   * `IAnalyzerDocumentProcessor` interface type.
   *
   * @see voIAnalyzerDocumentProcessor.
   */
  VO_IAnalyzerDocumentProcessor,
  /**
   * `IIAnalyzerUnderline` interface type.
   *
   * @see voIIAnalyzerUnderline.
   */
  VO_IAnalyzerUnderline,
  /**
   * `IIAnalyzerTextLine` interface type.
   *
   * @see voIIAnalyzerTextLine.
   */
  VO_IAnalyzerTextLine,
  /**
   * `IIAnalyzerLine` interface type.
   *
   * @see voIIAnalyzerLine.
   */
  VO_IAnalyzerLine,
  /**
   * `IIAnalyzerCell` interface type.
   *
   * @see voIIAnalyzerCell.
   */
  VO_IAnalyzerCell,
  /**
   * `IIAnalyzerTable` interface type.
   *
   * @see voIIAnalyzerTable.
   */
  VO_IAnalyzerTable,
  /**
   * `IIAnalyzerShape` interface type.
   *
   * @see voIIAnalyzerShape.
   */
  VO_IAnalyzerShape,
  /**
   * `IIAnalyzerGroup` interface type.
   *
   * @see voIIAnalyzerGroup.
   */
  VO_IAnalyzerGroup
};

/**
 * Lists the stroke types.
 */
enum VO_ANALYZER_STROKE_TYPE
{
  /**
   * Unknown.
   */
  VO_ANALYZER_STROKE_TYPE_UNKNOWN,

  /**
   * Text.
   */
  VO_ANALYZER_STROKE_TYPE_TEXT,

  /**
   * Non text.
   */
  VO_ANALYZER_STROKE_TYPE_NON_TEXT,

  /**
   * Underline.
   */
  VO_ANALYZER_STROKE_TYPE_UNDERLINE,

  /**
   * Table.
   */
  VO_ANALYZER_STROKE_TYPE_TABLE,

  /**
   * Shape.
   */
  VO_ANALYZER_STROKE_TYPE_SHAPE,

  /**
   * Correction.
   */
  VO_ANALYZER_STROKE_TYPE_CORRECTION,

  /**
   * Erased text.
   */
  VO_ANALYZER_STROKE_TYPE_ERASED_TEXT,

  /**
   * Number of stroke types.
   */
  VO_ANALYZER_STROKE_TYPE_COUNT
};

/**
 * Lists the group types.
 */
enum VO_ANALYZER_GROUP_TYPE
{
  /**
   * Paragraph.
   */
  VO_ANALYZER_GROUP_TYPE_PARAGRAPH,

  /**
   * List.
   */
  VO_ANALYZER_GROUP_TYPE_LIST,

  /**
   * Text inside graphics.
   */
  VO_ANALYZER_GROUP_TYPE_TEXT_INSIDE_GRAPHICS
};

/**
 * Lists the justification types.
 */
enum VO_ANALYZER_JUSTIFICATION_TYPE
{
  /**
   * Left align.
   */
  VO_ANALYZER_JUSTIFICATION_TYPE_LEFT_ALIGN,

  /**
   * Center.
   */
  VO_ANALYZER_JUSTIFICATION_TYPE_CENTER
};

/**
 * The `AnalyzerInkRange` type models a range in the input.
 */
typedef struct _voAnalyzerInkRange
{
  /**
   * Index of the stroke.
   */
  int32_t stroke;

  /**
   * Position of the first point within the stroke.
   */
  float firstPoint;

  /**
   * Position of the last point within the stroke.
   */
  float lastPoint;
}
voAnalyzerInkRange;

/**
 * The `AnalyzerPointData` type models the location of a point in the
 * 2D space.
 */
typedef struct _voAnalyzerPointData
{
  /**
   * Coordinate along the x axis.
   */
  float x;

  /**
   * Coordinate along the y axis.
   */
  float y;
}
voAnalyzerPointData;


// -- Analyzer -----------------------------------------------------------------

/**
 * Reference to an instance of the `Analyzer` type.
 *
 * {@implements voIAttachTarget, voIAnalyzerDocumentProcessor}
 *
 * @note Please refer to `MyScriptEngine.h` reference documentation
 *   about the `IAttachTarget` interface.
 */
typedef voEngineObject voAnalyzer;

/**
 * Lists the processing levels, each level including the previous levels.
 */
enum VO_ANALYZER_PROCESSING_LEVEL_VALUE
{
  /**
   * Stroke type processing level: text/non-text processing.
   */
  VO_ANALYZER_PROCESSING_LEVEL_STROKE_TYPE = 1,

  /**
   * Layout processing level: text-lines extraction, implies
   * `VO_ANALYZER_PROCESSING_LEVEL_STROKE_TYPE`.
   */
  VO_ANALYZER_PROCESSING_LEVEL_TEXTLINE = 2,

  /**
   * Recognition processing level: shape/hwr recognition, implies
   * `VO_ANALYZER_PROCESSING_LEVEL_STROKE_TYPE` and
   * `VO_ANALYZER_PROCESSING_LEVEL_TEXTLINE`.
   */
  VO_ANALYZER_PROCESSING_LEVEL_RECOGNITION = 3,

  /**
   * Beautification processing level: layout beautification, implies.
   * `VO_ANALYZER_PROCESSING_LEVEL_STROKE_TYPE` and
   * `VO_ANALYZER_PROCESSING_LEVEL_TEXTLINE` and
   * `VO_ANALYZER_PROCESSING_LEVEL_RECOGNITION`.
   */
  VO_ANALYZER_PROCESSING_LEVEL_BEAUTIFICATION = 4,

  /**
   * Default processing level, implies all other levels.
   */
  VO_ANALYZER_PROCESSING_LEVEL_ALL = VO_ANALYZER_PROCESSING_LEVEL_BEAUTIFICATION
};

/**
 * {@propertySet Analyzer}
 */
enum VO_ANALYZER_PROP
{
  /**
   * Adjusts the level of processing applied to the
   * `AnalyzerDocument`. By default, the highest level of processing
   * is applied.
   *
   * {@property voId}
   *
   * @see VO_ANALYZER_PROCESSING_LEVEL_VALUE
   */
  VO_ANALYZER_PROCESSING_LEVEL = (VO_Analyzer << 16)
};

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `Analyzer` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `Analyzer` object
 *   on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `Analyzer`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared by several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voAnalyzer voCreateAnalyzer(voEngine engine)
{
  return voCreateObject(engine, VO_Analyzer);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- AnalyzerElement ----------------------------------------------------------

/**
 * Reference to an instance of the `AnalyzerElement` type.
 */
typedef voEngineObject voAnalyzerElement;

/**
 * {@typePropertySet AnalyzerElement}
 */
enum VO_ANALYZER_ELEMENT_TPROP
{
  /**
   * Represents the maximum number of `AnalyzerElement` instances that
   * can exist at the same time in the user side of a MyScript enabled
   * application.
   * The special value zero means no limit. Other values are adjusted to the
   * next multiple of 16. A value under the current count is permitted and will
   * constrain future resource creations.
   *
   * {@property uint32_t}
   */
  VO_USER_ANALYZER_ELEMENT_LIMIT = VO_USER_OBJ_LIMIT,
  /**
   * Gives the number of `AnalyzerElement` instances that currently
   * exist in the user side of a MyScript enabled application.
   *
   * {@property read-only uint32_t}
   */
  VO_USER_ANALYZER_ELEMENT_COUNT = VO_USER_OBJ_COUNT
};


// -- AnalyzerUnderline ---------------------------------------------------------

/**
 * Reference to an instance of the `AnalyzerUnderline` type.
 *
 * {@extends voAnalyzerElement}
 * {@implements voIAnalyzerUnderline}
 */
typedef voAnalyzerElement voAnalyzerUnderline;

/**
 * The `AnalyzerUnderlineData` type models the data of an underline
 * space.
 */
typedef struct _voAnalyzerUnderlineData
{
  /**
   * Position of the first underlined character.
   */
  uint32_t firstCharacter;

  /**
   * Position of the last underlined character.
   */
  uint32_t lastCharacter;
}
voAnalyzerUnderlineData;

/**
 * Functions composing the `IAnalyzerUnderline` interface. This
 * interface exposes the public methods of the `AnalyzerUnderline`
 * type.
 *
 * {@implementingTypes voAnalyzerUnderline}
 * @see VO_IAnalyzerUnderline, VO_AnalyzerUnderline.
 */
typedef struct _voIAnalyzerUnderline
{
  /**
   * Returns the data that corresponds to that underline.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerUnderline` instance.
   * @param data Recipient for the data.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerUnderline` instance.
   * @throws VO_INVALID_USER_BUFFER The `data` recipient is not
   *   writable.
   */
  bool (VO_MSE_CALL *getData)(voEngine engine, voAnalyzerUnderline target, voAnalyzerUnderlineData* data);

  /**
   * Returns the number of ink ranges this underline covers.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerUnderline` instance.
   *
   * @return The number of ink ranges this underline covers on success,
   *   otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerUnderline` instance.
   * @throws VO_INVALID_STATE The portion of a MyScript Document associated with
   *   this underline has been modified, so the associated ink ranges are not
   *   valid anymore.
   */
  uint32_t (VO_MSE_CALL *getInkRangeCount)(voEngine engine, voAnalyzerUnderline target);

  /**
   * Returns the ink range at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerUnderline` instance.
   * @param index The zero-based index of the ink range to be retrieved.
   * @param inkRange Recipient for the ink range result.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerUnderline` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_INVALID_USER_BUFFER The `range` recipient is not
   *   writable.
   * @throws VO_INVALID_STATE The portion of a MyScript Document associated with
   *   this underline has been modified, so the associated ink ranges are not
   *   valid anymore.
   */
  bool (VO_MSE_CALL *getInkRangeAt)(voEngine engine, voAnalyzerUnderline target, uint32_t index, voAnalyzerInkRange* range);
}
voIAnalyzerUnderline;


// -- AnalyzerTextLine ---------------------------------------------------------

/**
 * Reference to an instance of the `AnalyzerTextLine` type.
 *
 * {@extends voAnalyzerElement}
 * {@implements voIAnalyzerTextLine}
 */
typedef voAnalyzerElement voAnalyzerTextLine;

/**
 * The `AnalyzerTextLineData` type models the data of a text line
 * space.
 */
typedef struct _voAnalyzerTextLineData
{
  /**
   * Top-Left point composing the text line box.
   */
  voAnalyzerPointData topLeftPoint;

  /**
   * Width of the box.
   */
  float width;

  /**
   * Height of the box.
   */
  float height;

  /**
   * Orientation of the box (angle in radians).
   */
  float orientation;

  /**
   * Position of the baseline.
   */
  float baselinePos;

  /**
   * Height of the text.
   */
  float textHeight;

  /**
   * Type of justification.
   */
  int justificationType;
}
voAnalyzerTextLineData;

/**
 * Functions composing the `IAnalyzerTextLine` interface. This
 * interface exposes the public methods of the `AnalyzerTextLine`
 * type.
 *
 * {@implementingTypes voAnalyzerTextLine}
 * @see VO_IAnalyzerTextLine, VO_AnalyzerTextLine.
 */
typedef struct _voIAnalyzerTextLine
{
  /**
   * Returns the data that corresponds to this text line.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerTextLine` instance.
   * @param data Recipient for the data.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerTextLine` instance.
   * @throws VO_INVALID_USER_BUFFER The `data` recipient is not
   *   writable.
   */
  bool (VO_MSE_CALL *getData)(voEngine engine, voAnalyzerTextLine target, voAnalyzerTextLineData* data);

  /**
   * Returns the recognition result of the text line.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerTextLine` instance.
   *
   * @return the recognition result of the text line on success, otherwise
   *   `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerTextLine` instance.
   */
  voRecognitionResult (VO_MSE_CALL *getResult)(voEngine engine, voAnalyzerTextLine target);

  /**
   * Returns the number of underlines.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerTextLine` instance.
   *
   * @return the number of underlines on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerTextLine` instance.
   */
  uint32_t (VO_MSE_CALL *getUnderlineCount)(voEngine engine, voAnalyzerTextLine target);

  /**
   * Returns the underline at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerTextLine` instance.
   * @param index The zero-based index of the underline to be retrieved.
   *
   * @return the underline on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerTextLine` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voAnalyzerUnderline (VO_MSE_CALL *getUnderlineAt)(voEngine engine, voAnalyzerTextLine target, uint32_t index);

  /**
   * Returns the number of ink ranges this text line covers.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `voAnalyzerTextLine` instance.
   *
   * @return The number of ink ranges this text line covers on success,
   *   otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `voAnalyzerTextLine` instance.
   * @throws VO_INVALID_STATE The portion of a MyScript Document associated with
   *   this line has been modified, so the associated ink ranges are not
   *   valid anymore.
   */
  uint32_t (VO_MSE_CALL *getInkRangeCount)(voEngine engine, voAnalyzerTextLine target);

  /**
   * Returns the ink range at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `voAnalyzerTextLine` instance.
   * @param index The zero-based index of the ink range to be retrieved.
   * @param inkRange Recipient for the ink range result.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `voAnalyzerTextLine` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_INVALID_USER_BUFFER The `range` recipient is not
   *   writable.
   * @throws VO_INVALID_STATE The portion of a MyScript Document associated with
   *   this line has been modified, so the associated ink ranges are not
   *   valid anymore.
   */
  bool (VO_MSE_CALL *getInkRangeAt)(voEngine engine, voAnalyzerTextLine target, uint32_t index, voAnalyzerInkRange* range);
}
voIAnalyzerTextLine;


// -- AnalyzerLine -------------------------------------------------------------

/**
 * Reference to an instance of the `AnalyzerLine` type.
 *
 * {@extends voAnalyzerElement}
 * {@implements voIAnalyzerLine}
 */
typedef voAnalyzerElement voAnalyzerLine;

/**
 * The `AnalyzerLineData` type models the data of a line segment in
 * the 2D space.
 *
 * @see voAnalyzerLine
 */
typedef struct _voAnalyzerLineData
{
  /**
   * First point composing the line segment.
   */
  voAnalyzerPointData p1;

  /**
   * Second point composing the line segment.
   */
  voAnalyzerPointData p2;
}
voAnalyzerLineData;

/**
 * Functions composing the `IAnalyzerLine` interface. This interface
 * exposes the public methods of the `AnalyzerLine` type.
 *
 * {@implementingTypes voAnalyzerLine}
 * @see VO_IAnalyzerLine, VO_AnalyzerLine.
 */
typedef struct _voIAnalyzerLine
{
  /**
   * Returns the data of the line segment at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerLine` instance.
   * @param index The zero-based index of the data of the line segment to be
   *   retrieved.
   * @param data Recipient for the line data.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerLine` instance.
   * @throws VO_INVALID_USER_BUFFER The `index` is out of bounds.
   */
  bool (VO_MSE_CALL *getData)(voEngine engine, voAnalyzerLine target, voAnalyzerLineData* data);
}
voIAnalyzerLine;


// -- AnalyzerCell -------------------------------------------------------------

/**
 * Reference to an instance of the `AnalyzerCell` type.
 *
 * {@extends voAnalyzerElement}
 * {@implements voIAnalyzerCell}
 */
typedef voAnalyzerElement voAnalyzerCell;

/**
 * The `AnalyzerCellData` type models the range of a cell space.
 */
typedef struct _voAnalyzerCellData
{
  /**
   * Position of the first row of the cell.
   */
  uint32_t firstRow;

  /**
   * Position of the last row of the cell.
   */
  uint32_t lastRow;

  /**
   * Position of the first column of the cell.
   */
  uint32_t firstColumn;

  /**
   * Position of the last column of the cell.
   */
  uint32_t lastColumn;

  /**
   * Top-Left point composing the cell box.
   */
  voAnalyzerPointData topLeftPoint;

  /**
   * Width of the cell box.
   */
  float width;

  /**
   * Height of the cell box.
   */
  float height;

  /**
   * Orientation of the cell box (angle in radians).
   */
  float orientation;

  /**
   * Tells if the cell has a left border.
   */
  bool leftBorder;

  /**
   * Tells if the cell has a top border.
   */
  bool topBorder;

  /**
   * Tells if the cell has a right border.
   */
  bool rightBorder;

  /**
   * Tells if the cell has a bottom border.
   */
  bool bottomBorder;
}
voAnalyzerCellData;

/**
 * Functions composing the `IAnalyzerCell` interface. This interface
 * exposes the public methods of the `AnalyzerCell` type.
 *
 * {@implementingTypes voAnalyzerCell}
 * @see VO_IAnalyzerCell, VO_AnalyzerCell.
 */
typedef struct _voIAnalyzerCell
{
  /**
   * Returns the data that corresponds to that cell.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerCell` instance.
   * @param data Recipient for the data.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerCell` instance.
   * @throws VO_INVALID_USER_BUFFER The `data` recipient is not
   *   writable.
   */
  bool (VO_MSE_CALL *getData)(voEngine engine, voAnalyzerCell target, voAnalyzerCellData* data);
}
voIAnalyzerCell;


// -- AnalyzerTable ------------------------------------------------------------

/**
 * Reference to an instance of the `AnalyzerTable` type.
 *
 * {@extends voAnalyzerElement}
 * {@implements voIAnalyzerTable}
 */
typedef voAnalyzerElement voAnalyzerTable;

/**
 * The `AnalyzerTableData` type models the data of a table space.
 */
typedef struct _voAnalyzerTableData
{
  /**
   * Number of rows composing the table.
   */
  uint32_t rowCount;

  /**
   * Number of columns composing the table.
   */
  uint32_t columnCount;
}
voAnalyzerTableData;

/**
 * Functions composing the `IAnalyzerTable` interface. This interface
 * exposes the public methods of the `AnalyzerTable` type.
 *
 * {@implementingTypes voAnalyzerTable}
 * @see VO_IAnalyzerTable, VO_AnalyzerTable.
 */
typedef struct _voIAnalyzerTable
{
  /**
   * Returns the data that corresponds to that table.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerTable` instance.
   * @param data Recipient for the data.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerTable` instance.
   * @throws VO_INVALID_USER_BUFFER The `data` recipient is not
   *   writable.
   */
  bool (VO_MSE_CALL *getData)(voEngine engine, voAnalyzerTable target, voAnalyzerTableData* data);

  /**
   * Returns the number of ink ranges this table covers.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerTable` instance.
   *
   * @return The number of ink ranges this table covers on success, otherwise
   * `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerTable` instance.
   * @throws VO_INVALID_STATE The portion of a MyScript Document associated with
   *   this table has been modified, so the associated ink ranges are not
   *   valid anymore.
   */
  uint32_t (VO_MSE_CALL *getInkRangeCount)(voEngine engine, voAnalyzerTable target);

  /**
   * Returns the ink range at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerTable` instance.
   * @param index The zero-based index of the ink range to be retrieved.
   * @param inkRange Recipient for the ink range result.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerTable` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_INVALID_USER_BUFFER The `range` recipient is not
   *   writable.
   * @throws VO_INVALID_STATE The portion of a MyScript Document associated with
   *   this table has been modified, so the associated ink ranges are not
   *   valid anymore.
   */
  bool (VO_MSE_CALL *getInkRangeAt)(voEngine engine, voAnalyzerTable target, uint32_t index, voAnalyzerInkRange* range);

  /**
   * Returns the number of lines.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerTable` instance.
   *
   * @return the number of lines on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerTable` instance.
   */
  uint32_t (VO_MSE_CALL *getLineCount)(voEngine engine, voAnalyzerTable target);

  /**
   * Returns the line at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerTable` instance.
   * @param index The zero-based index of the line to be retrieved.
   * @param line Recipient for the line.
   *
   * @return the line on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerTable` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voAnalyzerLine (VO_MSE_CALL *getLineAt)(voEngine engine, voAnalyzerTable target, uint32_t index);

  /**
   * Returns the number of cells.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerTable` instance.
   *
   * @return the number of cells on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerTable` instance.
   */
  uint32_t (VO_MSE_CALL *getCellCount)(voEngine engine, voAnalyzerTable target);

  /**
   * Returns the cell at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerTable` instance.
   * @param index The zero-based index of the cell to be retrieved.
   *
   * @return the cell on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerTable` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voAnalyzerCell (VO_MSE_CALL *getCellAt)(voEngine engine, voAnalyzerTable target, uint32_t index);
}
voIAnalyzerTable;


// -- AnalyzerShape ------------------------------------------------------------

/**
 * Reference to an instance of the `AnalyzerShape` type.
 *
 * {@extends voAnalyzerElement}
 * {@implements voIAnalyzerShape}
 */
typedef voAnalyzerElement voAnalyzerShape;

/**
 * Functions composing the `IAnalyzerShape` interface. This interface
 * exposes the public methods of the `AnalyzerShape` type.
 *
 * {@implementingTypes voAnalyzerShape}
 * @see VO_IAnalyzerShape, VO_AnalyzerShape.
 */
typedef struct _voIAnalyzerShape
{
  /**
   * Returns the shape segment.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerShape` instance.
   *
   * @return the shape segment on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerShape` instance.
   */
  voShapeSegment (VO_MSE_CALL *getSegment)(voEngine engine, voAnalyzerShape target);
}
voIAnalyzerShape;


// -- AnalyzerGroup ------------------------------------------------------------

/**
 * Reference to an instance of the `AnalyzerGroup` type.
 *
 * {@extends voAnalyzerElement}
 * {@implements voIAnalyzerGroup}
 */
typedef voAnalyzerElement voAnalyzerGroup;

/**
 * Functions composing the `IAnalyzerGroup` interface. This interface
 * exposes the public methods of the `AnalyzerGroup` type.
 *
 * {@implementingTypes voAnalyzerGroup}
 * @see VO_IAnalyzerGroup, VO_AnalyzerGroup.
 */
typedef struct _voIAnalyzerGroup
{
  /**
   * Returns the type of that group.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerGroup` instance.
   *
   * @return the type of group on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerGroup` instance.
   */
  int (VO_MSE_CALL *getType)(voEngine engine, voAnalyzerGroup target);

  /**
   * Returns the number of elements in the group.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerGroup` instance.
   *
   * @return the number of elements on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerGroup` instance.
   */
  uint32_t (VO_MSE_CALL *getElementCount)(voEngine engine, voAnalyzerGroup target);

  /**
   * Returns the element at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerGroup` instance.
   * @param index The zero-based index of the element to be retrieved.
   *
   * @return the element on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerGroup` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voAnalyzerElement (VO_MSE_CALL *getElementAt)(voEngine engine, voAnalyzerGroup target, uint32_t index);
}
voIAnalyzerGroup;


// -- AnalyzerDocument ---------------------------------------------------------

/**
 * Reference to an instance of the `AnalyzerDocument` type.
 *
 * {@implements voIAnalyzerDocument}
 */
typedef voEngineObject voAnalyzerDocument;

/**
 * Functions composing the `IAnalyzerDocument` interface. This
 * interface exposes the public methods of the `AnalyzerDocument`
 * type.
 *
 * {@implementingTypes voAnalyzerDocument}
 * @see VO_IAnalyzerDocument, VO_AnalyzerDocument.
 */
typedef struct _voIAnalyzerDocument
{
  /**
   * Clears this `AnalyzerDocument` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerDocument` instance.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerDocument` instance.
   */
  bool (VO_MSE_CALL *clear)(voEngine engine, voAnalyzerDocument target);

  /**
   * Adds a digital pen stroke to this `AnalyzerDocument` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerDocument` instance.
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
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerDocument` instance.
   * @throws VO_INVALID_ARGUMENT When `xByteStride == 0`
   * @throws VO_INVALID_ARGUMENT When `yByteStride == 0`
   * @throws VO_INVALID_ARGUMENT When `pointCount == 0`
   * @throws VO_INVALID_USER_BUFFER The combination of `x`,
   *   `xByteStride`, `y`, `yByteStride` and
   *   `pointCount` leads to invalid memory access.
   * @throws VO_LIMIT_EXCEEDED When `pointCount > 32767`
   */
  bool (VO_MSE_CALL *addStroke)(voEngine engine, voAnalyzerDocument target, const float* x, size_t xByteStride, const float* y, size_t yByteStride, uint32_t pointCount);

  /**
   * Returns the number of strokes.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerDocument` instance.
   *
   * @return the number of strokes on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerDocument` instance.
   */
  uint32_t (VO_MSE_CALL *getStrokeCount)(voEngine engine, voAnalyzerDocument target);

  /**
   * Returns the points of the stroke at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerDocument` instance.
   * @param index The index of the stroke to be retrieved.
   * @param x Pointer to the first x value.
   * @param xByteStride Stride in bytes between each x value.
   * @param y Pointer to the first y value.
   * @param yByteStride Stride in bytes between each y value.
   * @param pointCount Pointer to the capacity of the user buffer on input;
   *   number of points in the stroke on output.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerDocument` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_INVALID_USER_BUFFER The `pointCount` pointer is
   *   not readable or writable.
   * @throws VO_INVALID_USER_BUFFER The combination of `x`,
   *   `xByteStride`, `y`, `yByteStride` and
   *   `pointCount` leads to invalid memory access.
   *
   * @note You can pass `NULL` in place of `x` and
   *   `y` to retrieve the number of points in the stroke.
   */
  bool (VO_MSE_CALL *getStrokeAt)(voEngine engine, voAnalyzerDocument target, uint32_t index, float* x, size_t xByteStride, float* y, size_t yByteStride, uint32_t* pointCount);

  /**
   * Returns the type of the stroke at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerDocument` instance.
   * @param index The zero-based index of the type of the stroke to be retrieved.
   *
   * @return the type of the stroke on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerDocument` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  int (VO_MSE_CALL *getStrokeTypeAt)(voEngine engine, voAnalyzerDocument target, uint32_t index);

  /**
   * Returns the confidence score of the stroke at the specified
   * `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerDocument` instance.
   * @param index The zero-based index of the type of the stroke to be retrieved.
   *
   * @return the confidence score of classification of the stroke on success,
   * otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerDocument` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  float (VO_MSE_CALL *getStrokeConfidenceAt)(voEngine engine, voAnalyzerDocument target, uint32_t index);

  /**
   * Returns the number of text lines.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerDocument` instance.
   *
   * @return the number of text lines on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerDocument` instance.
   */
  uint32_t (VO_MSE_CALL *getTextLineCount)(voEngine engine, voAnalyzerDocument target);

  /**
   * Returns the text line at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerDocument` instance.
   * @param index The zero-based index of the text line to be retrieved.
   *
   * @return the text line on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerDocument` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voAnalyzerTextLine (VO_MSE_CALL *getTextLineAt)(voEngine engine, voAnalyzerDocument target, uint32_t index);

  /**
   * Returns the number of tables.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerDocument` instance.
   *
   * @return the number of tables on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerDocument` instance.
   */
  uint32_t (VO_MSE_CALL *getTableCount)(voEngine engine, voAnalyzerDocument target);

  /**
   * Returns the table at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerDocument` instance.
   * @param index The zero-based index of the table to be retrieved.
   *
   * @return the table on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerDocument` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voAnalyzerTable (VO_MSE_CALL *getTableAt)(voEngine engine, voAnalyzerDocument target, uint32_t index);

  /**
   * Returns the number of shapes.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerDocument` instance.
   *
   * @return the number of shapes on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerDocument` instance.
   */
  uint32_t (VO_MSE_CALL *getShapeCount)(voEngine engine, voAnalyzerDocument target);

  /**
   * Returns the shape at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerDocument` instance.
   * @param index The zero-based index of the shape to be retrieved.
   *
   * @return the shape on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerDocument` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voAnalyzerShape (VO_MSE_CALL *getShapeAt)(voEngine engine, voAnalyzerDocument target, uint32_t index);

  /**
   * Returns the number of groups.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerDocument` instance.
   *
   * @return the number of groups on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerDocument` instance.
   */
  uint32_t (VO_MSE_CALL *getGroupCount)(voEngine engine, voAnalyzerDocument target);

  /**
   * Returns the group at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `AnalyzerDocument` instance.
   * @param index The zero-based index of the group to be retrieved.
   *
   * @return the group on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `AnalyzerDocument` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  voAnalyzerGroup (VO_MSE_CALL *getGroupAt)(voEngine engine, voAnalyzerDocument target, uint32_t index);

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
}
voIAnalyzerDocument;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `AnalyzerDocument` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `AnalyzerDocument` object
 *   on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `AnalyzerDocument` instances
 *   would exceed the allowed limit. (please remember that the limit can be
 *   shared by several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voAnalyzerDocument voCreateAnalyzerDocument(voEngine engine)
{
  return voCreateObject(engine, VO_AnalyzerDocument);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- IAnalyzerDocumentProcessor -----------------------------------------------

/**
 * Functions composing the `IAnalyzerDocumentProcessor` interface.
 *
 * {@implementingTypes voAnalyzer}
 * @see VO_IAnalyzerDocumentProcessor, VO_Analyzer.
 */
typedef struct _voIAnalyzerDocumentProcessor
{
  /**
   * Processes a `AnalyzerDocument` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param AnalyzerDocument Reference to a `AnalyzerDocument` instance.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement this interface.
   * @throws VO_NO_SUCH_OBJECT The `analyzerDocument` reference is
   *   invalid.
   * @throws VO_INVALID_OBJECT The `analyzerDocument` object is not an
   *   instance of the `AnalyzerDocument` type.
   * @throws VO_INVALID_CALLBACK The notification callback crashed.
   * @throws VO_INVALID_STATE The `target` object is not in a state
   *   where the `process` function can be invoked.
   * @throws VO_CANCELED The operation has been canceled.
   *
   * @see voAnalyzerDocument
   */
  bool (VO_MSE_CALL *process)(voEngine engine, voEngineObject target, voAnalyzerDocument analyzerDocument, voNotifyProgressFunc notifyProgressFunc, void* userParam);
}
voIAnalyzerDocumentProcessor;


// -- AnalyzerKnowledge --------------------------------------------------------

/**
 * Reference to an instance of the `AnalyzerKnowledge` type.
 */
typedef voEngineObject voAnalyzerKnowledge;

#endif // end of: #ifndef C_MYSCRIPTANALYZER_H
