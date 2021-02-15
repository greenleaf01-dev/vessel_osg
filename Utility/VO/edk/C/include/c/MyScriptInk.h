#ifndef C_MYSCRIPTINK_H
#define C_MYSCRIPTINK_H 0x06010000
/**
 * @file c/MyScriptInk.h
 * Native interface to the MyScriptInk service.
 */

#include "MyScriptEngine.h"
#include <stdarg.h>


// -- types and interfaces -----------------------------------------------------

/**
 * Lists the MyScriptInk types.
 */
enum VO_INK_T
{
  /**
   * Identifier of the `InkStrokeFormat` type.
   * @see voInkStrokeFormat
   */
  VO_InkStrokeFormat = 3100,

  /**
   * Identifier of the `InkStrokeFormatBuilder` type.
   * @see voInkStrokeFormatBuilder
   */
  VO_InkStrokeFormatBuilder,

  /**
   * Identifier of the `InkStroke` type.
   * @see voInkStroke
   */
  VO_InkStroke,

  /**
   * Identifier of the `InkStrokeBuilder` type.
   * @see voInkStrokeBuilder
   */
  VO_InkStrokeBuilder,

  /**
   * Identifier of the `Ink` type.
   * @see voInk
   */
  VO_Ink,

  /**
   * Identifier of the `InkIntervals` type.
   * @see voInkIntervals
   */
  VO_InkIntervals,

  /**
   * Identifier of the `InkSegment` type.
   * @see voInkSegment
   */
  VO_InkSegment,

  /**
   * Identifier of the `InkSelection` type.
   * @see voInkSelection
   */
  VO_InkSelection,

  /**
   * Identifier of the `InkTagIterator` type.
   * @see voInkTagIterator
   */
  VO_InkTagIterator,

  /**
   * Identifier of the `Glyph` type.
   * @see voGlyph
   */
  VO_Glyph,

  /**
   * Identifier of the `ArcPrimitive` type.
   * @see voArcPrimitive
   */
  VO_ArcPrimitive,

  /**
   * Identifier of the `LinePrimitive` type.
   * @see voLinePrimitive
   */
  VO_LinePrimitive,
};


/**
 * Lists the MyScriptInk interfaces.
 */
enum VO_INK_I
{
  /**
   * Identifier of the `ISelectionChangeListener` interface.
   * @see voISelectionChangeListener
   */
  VO_ISelectionChangeListener = 3120,

  /**
   * Identifier of the `ISelection` interface.
   * @see voISelection
   */
  VO_ISelection,

  /**
   * Identifier of the `IInkStrokeFormat` interface.
   * @see voIInkStrokeFormat
   */
  VO_IInkStrokeFormat,

  /**
   * Identifier of the `IInkStrokeFormatBuilder` interface.
   * @see voIInkStrokeFormatBuilder
   */
  VO_IInkStrokeFormatBuilder,

  /**
   * Identifier of the `IInkStroke` interface.
   * @see voIInkStroke
   */
  VO_IInkStroke,

  /**
   * Identifier of the `IInkStrokeBuilder` interface.
   * @see voIInkStrokeBuilder
   */
  VO_IInkStrokeBuilder,

  /**
   * Identifier of the `IInk` interface.
   * @see voIInk
   */
  VO_IInk,

  /**
   * Identifier of the `IInkIntervals` interface.
   * @see voIInkIntervals
   */
  VO_IInkIntervals,

  /**
   * Identifier of the `IInkStrokeSet` interface.
   * @see voIInkStrokeSet
   */
  VO_IInkStrokeSet,

  /**
   * Identifier of the `IInkSelection` interface.
   * @see voIInkSelection
   */
  VO_IInkSelection,

  /**
   * Identifier of the `IGeometry` interface.
   * @see voIGeometry
   */
  VO_IGeometry,

  /**
   * Identifier of the `IInkTagIterator` interface.
   * @see voIInkTagIterator
   */
  VO_IInkTagIterator,

  /**
   * Identifier of the `IInkUpdateListener` interface.
   * @see voIInkUpdateListener
   */
  VO_IInkUpdateListener,

  /**
   * Identifier of the `IGlyph` interface.
   * @see voIGlyph
   */
  VO_IGlyph,

  /**
   * Identifier of the `IPrimitive` interface.
   * @see voIPrimitive
   */
  VO_IPrimitive
};


// -- Geometry -----------------------------------------------------------------

/**
 * Represents a point on the 2D plane.
 */
typedef struct _voPoint
{
  float x;      /**< The x position of the point. */
  float y;      /**< The y position of the point. */
}
voPoint;

/**
 * Represents the extent of some geometric object on the 2D plane.
 */
typedef struct _voExtent
{
  float xmin;   /**< The minimal x value. */
  float ymin;   /**< The minimal y value. */
  float xmax;   /**< The maximal x value. */
  float ymax;   /**< The maximal y value. */
}
voExtent;

/**
 * Represents an axis aligned rectangle on the 2D plane.
 */
typedef struct _voRectangle
{
  float x;      /**< The x position of the left edge of the rectangle. */
  float y;      /**< The y position of the top edge of the rectangle. */
  float width;  /**< The width of the rectangle. */
  float height; /**< The height of the rectangle. */
}
voRectangle;

/**
 * Represents a parallelogram with an origin and two vectors.
 */
typedef struct _voParallelogram
{
  float x; /** The x position of the origin point. */
  float y; /** The y position of the origin point. */
  float ux; /** The x projection of u: the first side vector. */
  float uy; /** The y projection of u: the first side vector. */
  float vx; /** The x projection of v: the adjacent vector. */
  float vy; /** The y projection of v: the adjacent vector. */
}
voParallelogram;

/**
 * Represents an axis-aligned rounded rectangle on the 2D plane.
 */
typedef struct _voRoundedRectangle
{
  float x;      /**< The x position of the left edge of the rectangle. */
  float y;      /**< The y position of the top edge of the rectangle. */
  float width;  /**< The width of the rectangle. */
  float height; /**< The height of the rectangle. */
  float rx;     /**< The x-axis radius of the corner ellipse. */
  float ry;     /**< The y-axis radius of the corner ellipse. */
}
voRoundedRectangle;

/**
 * Represents a circle on the 2D plane.
 */
typedef struct _voCircle
{
  float cx;     /**< The x position of the center of the circle. */
  float cy;     /**< The y position of the center of the circle. */
  float r;      /**< The radius of the circle. */
}
voCircle;

/**
 * Represents an axis-aligned ellipse on the 2D plane.
 */
typedef struct _voEllipse
{
  float cx;     /**< The x position of the center of the ellipse. */
  float cy;     /**< The y position of the center of the ellipse. */
  float rx;     /**< The x-axis radius of the ellipse. */
  float ry;     /**< The y-axis radius of the ellipse. */
}
voEllipse;

/**
 * Represents a line segment on the 2D plane.
 */
typedef struct _voLineSegment
{
  voPoint p1;   /**< first point. */
  voPoint p2;   /**< last point. */
}
voLineSegment;

/**
 * Represents a cubic bezier curve on the 2D plane.
 */
typedef struct _voCubicBezierCurve
{
  voPoint p0;   /**< first point. */
  voPoint p3;   /**< last point. */
  voPoint p1;   /**< first control point. */
  voPoint p2;   /**< last control point. */
}
voCubicBezierCurve;

/**
 * Represents a quadratic bezier curve on the 2D plane.
 */
typedef struct _voQuadraticBezierCurve
{
  voPoint p0;   /**< first point. */
  voPoint p2;   /**< last point. */
  voPoint p1;   /**< control point. */
}
voQuadraticBezierCurve;

/**
 * Represents an elliptic arc on the 2D plane, by its endpoint parameterization.
 */
typedef struct _voEndpointEllipticArc
{
  voPoint p1;   /**< first point. */
  voPoint p2;   /**< last point (must be different from first point). */
  float rx;     /**< x-axis radius (must be positive). */
  float ry;     /**< y-axis radius (must be positive). */
  float phi;    /**< x-axis rotation angle. */
  int fA;       /**< large-arc flag. */
  int fS;       /**< sweep-arc flag. */
}
voEndpointEllipticArc;

/**
 * Represents an elliptic arc on the 2D plane, by its center parameterization.
 */
typedef struct _voCenterEllipticArc
{
  float cx;         /**< center x position. */
  float cy;         /**< center y position. */
  float rx;         /**< x-axis or semi-major radius (must be positive). */
  float ry;         /**< y-axis or semi-minor radius (must be positive). */
  float phi;        /**< x-axis rotation angle. */
  float startAngle; /**< start angle (prior to stretch and rotate). */
  float sweepAngle; /**< sweep angle (prior to stretch and rotate). */
}
voCenterEllipticArc;

/**
 * Represents a 2D affine transform, defined as a 3x3 matrix with an implicit
 * third raw of <code>[ 0 0 1 ]</code>:
 *
 * <pre>
 * [  x' ]   [ a  b  c ]   [ x ]   [ a * x + b * y + c ]
 * [  y' ] = [ d  e  f ] * [ y ] = [ d * x + e * y + f ]
 * [  1  ]   [ 0  0  1 ]   [ 1 ]   [         1         ]
 * </pre>
 */
typedef struct _voTransform
{
  /**
   * The X coordinate scaling element <i>M</i><sub>1,1</sub> of the transform
   * matrix.
   */
  float a;

  /**
   * The X coordinate shearing element <i>M</i><sub>1,2</sub> of the transform
   * matrix.
   */
  float b;

  /**
   * The X coordinate translation element <i>M</i><sub>1,3</sub> of the
   * transform matrix.
   */
  float c;

  /**
   * The Y coordinate shearing element <i>M</i><sub>2,1</sub> of the transform
   * matrix.
   */
  float d;

  /**
   * The Y coordinate scaling element <i>M</i><sub>2,2</sub> of the transform
   * matrix.
   */
  float e;

  /**
   * The Y coordinate translation element <i>M</i><sub>2,3</sub> of the
   * transform matrix.
   */
  float f;
}
voTransform;


// -- Digital Ink --------------------------------------------------------------

/**
 * Reference to an instance of the `InkStrokeFormat` type.
 *
 * {@extends voEngineObject}
 * {@implements voIInkStrokeFormat}
 */
typedef voEngineObject voInkStrokeFormat;

/**
 * Reference to an instance of the `InkStrokeFormatBuilder` type.
 *
 * {@extends voEngineObject}
 * {@implements voIInkStrokeFormat, voIInkStrokeFormatBuilder}
 */
typedef voEngineObject voInkStrokeFormatBuilder;

/**
 * Reference to an instance of the `InkStroke` type.
 *
 * {@extends voEngineObject}
 * {@implements voIInkStroke}
 */
typedef voEngineObject voInkStroke;

/**
 * Reference to an instance of the `InkStrokeBuilder` type.
 *
 * {@extends voEngineObject}
 * {@implements voIInkStroke, voIInkStrokeBuilder}
 */
typedef voEngineObject voInkStrokeBuilder;

/**
 * Reference to an instance of the `Ink` type.
 *
 * {@extends voEngineObject}
 * {@implements voIInk, voIInkStrokeSet}
 */
typedef voEngineObject voInk;

/**
 * Reference to an instance of the `InkIntervals` type.
 *
 * {@extends voEngineObject}
 * {@implements voIInkIntervals, voIInkStrokeSet}
 */
typedef voEngineObject voInkIntervals;

/**
 * Reference to an instance of the `InkSegment` type.
 *
 * {@extends voInkIntervals}
 */
typedef voInkIntervals voInkSegment;

/**
 * Reference to an instance of the `InkSelection` type.
 *
 * {@extends voInkIntervals}
 * {@implements voISelection, voIInkSelection}
 */
typedef voInkIntervals voInkSelection;

/**
 * Reference to an instance of the `InkTagIterator` type.
 *
 * {@extends voIterator}
 * {@implements voIInkTagIterator}
 */
typedef voIterator voInkTagIterator;

/**
 * Reference to an instance of the `Glyph` type.
 *
 * {@extends voInkStroke}
 * {@implements voIInkStroke, voIGlyph}
 */
typedef voInkStroke voGlyph;

/**
 * Reference to an instance of the `ArcPrimitive` type.
 *
 * {@extends voInkStroke}
 * {@implements voIInkStroke, voIPrimitive}
 */
typedef voInkStroke voArcPrimitive;

/**
 * Reference to an instance of the `LinePrimitive` type.
 *
 * {@extends voInkStroke}
 * {@implements voIInkStroke, voIPrimitive}
 */
typedef voInkStroke voLinePrimitive;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `InkStrokeFormatBuilder` type.
 *
 * @param engine the engine.
 *
 * @return A reference to the newly created `InkStrokeFormatBuilder`
 *   object on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `InkStrokeFormatBuilder`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voInkStrokeFormatBuilder voCreateInkStrokeFormatBuilder(voEngine engine)
{
  return voCreateObject(engine, VO_InkStrokeFormatBuilder);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS

/**
 * Represents the parameters required to create a voInkStrokeBuilder, the first
 * way.
 */
typedef struct _voInkStrokeBuilderInitializer1
{
  /**
   * The format of the strokes to build.
   */
  voInkStrokeFormat strokeFormat;
}
voInkStrokeBuilderInitializer1;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `InkStrokeBuilder` type, the first way.
 *
 * @param engine the engine.
 * @param strokeFormat the format of the strokes to build.
 *
 * @return A reference to the newly created `InkStrokeBuilder` object
 *   on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `InkStrokeBuilder`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */

VO_INLINE voInkStrokeBuilder voCreateInkStrokeBuilder1(voEngine engine, voInkStrokeFormat strokeFormat)
{
  voInkStrokeBuilderInitializer1 initializer = { strokeFormat };
  return voCreateObjectEx(engine, VO_InkStrokeBuilder, &initializer, sizeof(initializer));
}
#endif // end of: #ifndef VO_NO_FUNCTIONS

/**
 * Represents the parameters required to create a voInkStrokeBuilder, the second
 * way.
 */
typedef struct _voInkStrokeBuilderInitializer2
{

  /**
   * The charset to be used to decode the string, or `NULL` to use
   * the default charset.
   */
  voCharset charset;

  /**
   * The string that represents the stroke format to create.
   */
  voString strokeFormatString;
}
voInkStrokeBuilderInitializer2;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `InkStrokeBuilder` type, the second way.
 *
 * @param engine the engine.
 * @param charset the charset to be used to decode the string, or
 *   `NULL` to use the default charset.
 * @param strokeFormatString the string that represents the format of the
 *   strokes to build.
 *
 * @return A reference to the newly created `InkStrokeBuilder`
 *   object on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `InkStrokeBuilder`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voInkStrokeBuilder voCreateInkStrokeBuilder2(voEngine engine, voCharset charset, const voString* strokeFormatString)
{
  voInkStrokeBuilderInitializer2 initializer = { charset, { strokeFormatString->bytes, strokeFormatString->byteCount } };
  return voCreateObjectEx(engine, VO_InkStrokeBuilder, &initializer, sizeof(initializer));
}
#endif // end of: #ifndef VO_NO_FUNCTIONS

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `Ink` type.
 *
 * @param engine the engine.
 *
 * @return A reference to the newly created `Ink` object on success,
 *   otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `Ink`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voInk voCreateInk(voEngine engine)
{
  return voCreateObject(engine, VO_Ink);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS

/**
 * Represents the parameters required to create a voInkSelection.
 */
typedef struct _voInkSelectionInitializer
{
  /**
   * The ink on which the selection will be based.
   */
  voInk ink;
}
voInkSelectionInitializer;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `InkSelection` type.
 *
 * @param engine the engine.
 * @param ink the ink on which the selection will be based.
 *
 * @return A reference to the newly created `InkSelection` object on
 *   success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `InkSelection`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */

VO_INLINE voInkSelection voCreateInkSelection(voEngine engine, voInk ink)
{
  voInkSelectionInitializer initializer = { ink };
  return voCreateObjectEx(engine, VO_InkSelection, &initializer, sizeof(initializer));
}
#endif // end of: #ifndef VO_NO_FUNCTIONS

/**
 * Represents a position on the discrete trace formed by the sequence of strokes
 * in a stroke set.
 */
typedef struct _voInkCursor
{
  /**
   * The index of the stroke.
   */
  int stroke;

  /**
   * The point position. The integer part represents the index of the sample in
   * the stroke and the decimal part represents position along the segment that
   * links to the next sample.
   */
  float point;

  /**
   * When used as the endpoint of an interval, tells whether this endpoint is
   * included or not.
   */
  bool included;
}
voInkCursor;

/**
 * Represents an interval on the ink cursor line.
 */
typedef struct _voInkInterval
{
  /**
   * The lower endpoint.
   */
  voInkCursor from;

  /**
   * The upper endpoint.
   */
  voInkCursor to;
}
voInkInterval;

/**
 * Functions composing the `IInkStrokeFormat` interface.
 *
 * {@implementingTypes voInkStrokeFormat, voInkStrokeFormatBuilder}
 * @see VO_IInkStrokeFormat.
 */
typedef struct _voIInkStrokeFormat
{
  /**
   * Returns the number of channels in this stroke format.
   *
   * @param engine the engine.
   * @param target the target stroke format.
   *
   * @return the number of channels in the stroke format.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStrokeFormat`.
   */
  int (VO_MSE_CALL *getChannelCount)(voEngine engine, voEngineObject target);

  /**
   * Returns the name of the channel at the specified index.
   *
   * @param engine the engine.
   * @param target the target stroke format.
   * @param charset the charset to be used to encode `name`.
   * @param name a recipient for the channel name.
   *
   * @return the number of channels in the stroke format.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStrokeFormat`.
   * @throws VO_INDEX_OUT_OF_BOUNDS if `index` is out of the valid
   *   channel indices.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `name` recipient is not
   *   readable or writable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the
   *   `name` recipient is not writable.
   */
  bool (VO_MSE_CALL *getChannelNameAt)(voEngine engine, voEngineObject target, int index, voCharset charset, voString* name);

  /**
   * Returns the unit of the channel at the specified index.
   *
   * <p>Unit is expressed as a string and formatted following the SI
   * (International System of Units), for example: `mm`, `s`, etc.</p>
   *
   * @param engine the engine.
   * @param target the target stroke format.
   * @param charset the charset to be used to encode `unit`.
   * @param unit a recipient for the channel unit.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStrokeFormat`.
   * @throws VO_INDEX_OUT_OF_BOUNDS if `index` is out of the valid
   *   channel indices.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `unit` recipient is not
   *   readable or writable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the
   *   `unit` recipient is not writable.
   * @throws VO_INVALID_STATE no unit is specified for the channel.
   */
  bool (VO_MSE_CALL *getChannelUnitAt)(voEngine engine, voEngineObject target, int index, voCharset charset, voString* unit);

  /**
   * Returns the quantization value of the channel at the specified index.
   *
   * @param engine the engine.
   * @param target the target stroke format.
   * @param quantization a recipient for the channel quantization.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStrokeFormat`.
   * @throws VO_INDEX_OUT_OF_BOUNDS if `index` is out of the valid
   *   channel indices.
   * @throws VO_INVALID_USER_BUFFER the `quantization` recipient is not
   *   readable or writable.
   * @throws VO_INVALID_STATE no quantization is specified for the channel.
   */
  bool (VO_MSE_CALL *getChannelQuantizationAt)(voEngine engine, voEngineObject target, int index, float* quantization);

  /**
   * Returns the minimum value of the channel at the specified index.
   *
   * @param engine the engine.
   * @param target the target stroke format.
   * @param min a recipient for the channel minimum.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStrokeFormat`.
   * @throws VO_INDEX_OUT_OF_BOUNDS if `index` is out of the valid
   *   channel indices.
   * @throws VO_INVALID_USER_BUFFER the `minimum` recipient is not
   *   readable or writable.
   * @throws VO_INVALID_STATE no minimum is specified for the channel.
   */
  bool (VO_MSE_CALL *getChannelMinAt)(voEngine engine, voEngineObject target, int index, float* min);

  /**
   * Returns the maximum value of the channel at the specified index.
   *
   * @param engine the engine.
   * @param target the target stroke format.
   * @param max a recipient for the channel maximum.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStrokeFormat`.
   * @throws VO_INDEX_OUT_OF_BOUNDS if `index` is out of the valid
   *   channel indices.
   * @throws VO_INVALID_USER_BUFFER the `maximum` recipient is not
   *   readable or writable.
   * @throws VO_INVALID_STATE no maximum is specified for the channel.
   */
  bool (VO_MSE_CALL *getChannelMaxAt)(voEngine engine, voEngineObject target, int index, float* max);

  /**
   * Returns the nominal sample rate of this stroke format.
   *
   * @param engine the engine.
   * @param target the target stroke format.
   *
   * @return the nominal sample rate on success, otherwise a negative value.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStrokeFormat`.
   *
   * @note the result may slightly differ from the sample rate that was given to
   *   the ink stroke format builder, due to rounding operations.
   */
  float (VO_MSE_CALL *getSampleRate)(voEngine engine, voEngineObject target);

  /**
   * Returns the indication of whether sample rate is uniform or not.
   *
   * @param engine the engine.
   * @param target the target stroke format.
   *
   * @return `VO_YES` if sample rate is uniform. `VO_NO`
   *  if sample rate is NOT uniform. `VO_ERR` if an error occurred.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStrokeFormat`.
   */
  voYesNo (VO_MSE_CALL *isSampleRateUniform)(voEngine engine, voEngineObject target);

  /**
   * Lookups this stroke format for a channel with the specified name.
   *
   * @param engine the engine.
   * @param target the target stroke format.
   * @param charset the charset used to encode `name`.
   * @param name the name of the channel to look for.
   *
   * @return the index of the channel if found, otherwise `-1`.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStrokeFormat`.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `name` recipient is not
   *   readable.
   */
  int (VO_MSE_CALL *lookupChannel)(voEngine engine, voEngineObject target, voCharset charset, const voString* name);
}
voIInkStrokeFormat;

/**
 * Functions composing the `IInkStrokeFormatBuilder` interface.
 *
 * {@implementingTypes voInkStrokeFormatBuilder}
 * @see VO_IInkStrokeFormatBuilder.
 */
typedef struct _voIInkStrokeFormatBuilder
{
  /**
   * Clears this stroke format builder so that we start building a new stroke
   * format.
   *
   * @param engine the engine.
   * @param target the target stroke format builder.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInkStrokeFormatBuilder`.
   */
  bool (VO_MSE_CALL *clear)(voEngine engine, voInkStrokeFormatBuilder target);

  /**
   * Adds a new channel to the stroke format to build.
   *
   * <p>Here below are the predefined names and their recognized meaning:</p>
   * <table>
   *   <tr><td>Name</td><td>Description</td></tr>
   *   <tr><td>X</td><td>Horizontal position, increasing to the right.</td></tr>
   *   <tr><td>Y</td><td>Vertical position, increasing downward.</td></tr>
   *   <tr><td>W</td><td>Stroke width.</td></tr>
   *   <tr><td>T</td><td>Sample timestamp.</td></tr>
   *   <tr><td>F</td><td>Tip force.</td></tr>
   *   <tr><td>OTx</td><td>Tilt along the X axis.</td></tr>
   *   <tr><td>OTy</td><td>Tilt along the Y axis.</td></tr>
   *   <tr><td>OA</td><td>Azimuth angle (yaw).</td></tr>
   *   <tr><td>OE</td><td>Elevation angle (pitch).</td></tr>
   *   <tr><td>OR</td><td>Rotation (counter-clockwise rotation around the pen axis).</td></tr>
   * </table>
   * <p>You can also store application specific values by using a name not found
   * in the table above.</p>
   * <p>A stroke format must at least contain X and Y channels.</p>
   *
   * @param engine the engine.
   * @param target the target stroke format builder.
   * @param charset the charset used to encode `name`.
   * @param name the name of channel to add.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInkStrokeFormatBuilder`.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `name` recipient is not
   *   readable.
   */
  bool (VO_MSE_CALL *addChannel)(voEngine engine, voInkStrokeFormatBuilder target, voCharset charset, const voString* name);

  /**
   * Sets the unit of a channel.
   *
   * <p>Unit should be expressed as a string and formatted following the SI
   * (International System of Units), for example: `mm`, `s`, etc.</p>
   *
   * <p>A dpi resolution can be expressed as the invert of a unit, i.e. a 1000
   * dpi resolution corresponds to a unit described as `0.001 in`.</p>
   *
   * @param engine the engine.
   * @param target the target stroke format builder.
   * @param charset the charset used to encode `name` and `unit`.
   * @param name the name of channel.
   * @param unit the unit of channel.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInkStrokeFormatBuilder`.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `name` or the `unit` recipients are not
   *   readable.
   * @throws VO_INVALID_ARGUMENT the `name` does not correspond to a channel.
   * @throws VO_INVALID_ARGUMENT the `unit` cannot be parsed as a unit string
   *   description.
   */
  bool (VO_MSE_CALL *setChannelUnit)(voEngine engine, voInkStrokeFormatBuilder target, voCharset charset, const voString* name, const voString* unit);

  /**
   * Sets the quantization of a channel.
   * This quantization value is typically used together with minimum and maximum
   * value to enable optimum integer quantization.
   *
   * @param engine the engine.
   * @param target the target stroke format builder.
   * @param charset the charset used to encode `name`.
   * @param name the name of channel.
   * @param quantization the channel quantization.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInkStrokeFormatBuilder`.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `name` recipient is not
   *   readable.
   * @throws VO_INVALID_ARGUMENT the `name` does not correspond to a channel.
   */
  bool (VO_MSE_CALL *setChannelQuantization)(voEngine engine, voInkStrokeFormatBuilder target, voCharset charset, const voString* name, float quantization);

  /**
   * Sets the minimum value of a channel.
   * This minimum value is typically used together with quantization and maximum
   * value to enable optimum integer quantization.
   *
   * <p>Note that the values stored in the channel will not be checked against
   * this minimum, so values below minimum may be stored in the channel.</p>
   *
   * @param engine the engine.
   * @param target the target stroke format builder.
   * @param charset the charset used to encode `name`.
   * @param name the name of channel.
   * @param min the minimum value in the channel.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInkStrokeFormatBuilder`.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `name` recipient is not
   *   readable.
   * @throws VO_INVALID_ARGUMENT the `name` does not correspond to a channel.
   */
  bool (VO_MSE_CALL *setChannelMin)(voEngine engine, voInkStrokeFormatBuilder target, voCharset charset, const voString* name, float min);

  /**
   * Sets the maximum value of a channel.
   * This maximum value is typically used together with quantization and minimum
   * value to enable optimum integer quantization.
   *
   * <p>Note that the values stored in the channel will not be checked against
   * this maximum, so values above maximum may be stored in the channel.</p>
   *
   * @param engine the engine.
   * @param target the target stroke format builder.
   * @param charset the charset used to encode `name`.
   * @param name the name of channel.
   * @param max the maximum value in the channel.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInkStrokeFormatBuilder`.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `name` recipient is not
   *   readable.
   * @throws VO_INVALID_ARGUMENT the `name` does not correspond to a channel.
   */
  bool (VO_MSE_CALL *setChannelMax)(voEngine engine, voInkStrokeFormatBuilder target, voCharset charset, const voString* name, float max);

  /**
   * Sets the sample rate and indicates whether sample rate is uniform or not.
   *
   * @param engine the engine.
   * @param target the target stroke format builder.
   * @param rate the nominal sample rate.
   * @param uniform indicates whether the sample rate is uniform or not.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInkStrokeFormatBuilder`.
   */
  bool (VO_MSE_CALL *setSampleRate)(voEngine engine, voInkStrokeFormatBuilder target, float rate, bool uniform);

  /**
   * Creates the builded stroke format.
   *
   * @param engine the engine.
   * @param target the target stroke format builder.
   *
   * @return the newly created stroke format on success, otherwise
   *   `NULL`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInkStrokeFormatBuilder`.
   */
  voInkStrokeFormat (VO_MSE_CALL *createStrokeFormat)(voEngine engine, voInkStrokeFormatBuilder target);

  /**
   * Creates a stroke format from its string representation.
   *
   * @param engine the engine.
   * @param charset the charset to be used to decode the string, or
   *   `NULL` to use the default charset.
   * @param string the string representation of the stroke format to create.
   *
   * @return the newly created stroke format on success, otherwise
   *   `NULL`.
   */
  voInkStrokeFormat (VO_MSE_CALL *parseStrokeFormat)(voEngine engine, voCharset charset, const voString* string);
}
voIInkStrokeFormatBuilder;

/**
 * Functions composing the `IInkStroke` interface.
 *
 * {@implementingTypes voInkStroke, voInkStrokeBuilder}
 * @see VO_IInkStroke.
 */
typedef struct _voIInkStroke
{
  /**
   * Returns the format of this stroke.
   *
   * @param engine the engine.
   * @param target the target stroke.
   *
   * @return the stroke format on success, otherwise `NULL`.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStroke`.
   */
  voInkStrokeFormat (VO_MSE_CALL *getFormat)(voEngine engine, voEngineObject target);

  /**
   * Returns the timestamp of the stroke as the number of microseconds elapsed
   * since the Unix EPOCH (January 1, 1970, 00:00:00 GMT).
   *
   * @param engine the engine.
   * @param target the target stroke.
   *
   * @return the timestamp of the stroke on success, otherwise -1.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStroke`.
   */
  int64_t (VO_MSE_CALL *getTimestamp)(voEngine engine, voEngineObject target);

  /**
   * Returns whether the first point of the stroke corresponds to the left
   * boundary of a left open interval.
   *
   * @param engine the engine.
   * @param target the target stroke.
   *
   * @return `VO_YES` if true,
   *   `VO_NO` if false,
   *   `VO_ERR` if an error occurred.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStroke`.
   */
  voYesNo (VO_MSE_CALL *isFirstPointIncluded)(voEngine engine, voEngineObject target);

  /**
   * Returns whether the last point of the stroke corresponds to the right
   * boundary of a right open interval.
   *
   * @param engine the engine.
   * @param target the target stroke.
   *
   * @return `VO_YES` if true,
   *   `VO_NO` if false,
   *   `VO_ERR` if an error occurred.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStroke`.
   */
  voYesNo (VO_MSE_CALL *isLastPointIncluded)(voEngine engine, voEngineObject target);

  /**
   * Returns whether the first point of the stroke corresponds to the beginning
   * of a raw stroke.
   *
   * @param engine the engine.
   * @param target the target stroke.
   *
   * @return `VO_YES` if true,
   *   `VO_NO` if false,
   *   `VO_ERR` if an error occurred.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStroke`.
   */
  voYesNo (VO_MSE_CALL *isFirstPointPenDown)(voEngine engine, voEngineObject target);

  /**
   * Returns whether the last point of the stroke corresponds to the end of a
   * raw stroke.
   *
   * @param engine the engine.
   * @param target the target stroke.
   *
   * @return `VO_YES` if true,
   *   `VO_NO` if false,
   *   `VO_ERR` if an error occurred.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStroke`.
   */
  voYesNo (VO_MSE_CALL *isLastPointPenUp)(voEngine engine, voEngineObject target);

  /**
   * Returns the number of samples in this stroke.
   *
   * @param engine the engine.
   * @param target the target stroke.
   *
   * @return the number of samples in the strokes on success, otherwise -1.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStroke`.
   */
  int (VO_MSE_CALL *getSampleCount)(voEngine engine, voEngineObject target);

  /**
   * Returns whether this stroke has interleaved floating-point X and Y
   * channels that can be retrieved directly as an array of `voPoint`,
   * or not.
   *
   * @param engine the engine.
   * @param target the target stroke.
   *
   * @return `VO_YES` if stroke points can be retrieved by calling
   *   `getPointArray()`, `VO_NO` if stroke points must
   *   be retrieved by calling `getPoints()`, `VO_ERR` if
   *   an error occurred.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStroke`.
   */
  voYesNo (VO_MSE_CALL *isPointArrayCompatible)(voEngine engine, voEngineObject target);

  /**
   * Returns the points array for this stroke. This function can be called
   * only if `isPointArrayCompatible()` returns VO_YES.
   *
   * @param engine the engine.
   * @param target the target stroke.
   *
   * @return the array of points for this strokes.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStroke`.
   * @throws VO_INVALID_STATE if this function cannot be called (use
   *   `getPoints()` instead).
   */
  const voPoint* (VO_MSE_CALL *getPointArray)(voEngine engine, voEngineObject target);

  /**
   * Returns the points of the stroke.
   *
   * @param engine the engine.
   * @param target the target stroke.
   * @param sampleOffset the offset of the points to retrieve.
   * @param sampleCount the number of points to retrieve.
   * @param points the array of points to be filled.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStroke`.
   * @throws VO_INDEX_OUT_OF_BOUNDS if `channelIndex` is out of the
   *   available channel indices.
   * @throws VO_INDEX_OUT_OF_BOUNDS if `sampleOffset` and/or
   *   `sampleCount` are out of the available data indices.
   * @throws VO_INVALID_ARGUMENT if `points` is NULL.
   */
  bool (VO_MSE_CALL *getPoints)(voEngine engine, voEngineObject target,
                                int sampleOffset, int sampleCount,
                                voPoint* points);

  /**
   * Returns whether the sample data for a given channel can be retrieved as
   * a direct float array.
   *
   * @param engine the engine.
   * @param target the target stroke.
   * @param channelIndex the index of the channel to get samples from.
   *
   * @return `VO_YES` if points for channel `channelIndex`
   *         can be retrieved by calling `getFloatArray()`,
   *         `VO_NO`  if points for channel `channelIndex`
   *         must be retrieved by calling `getValuesAsFloat()`,
   *         `VO_ERR` if an error occurred.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStroke`.
   * @throws VO_INDEX_OUT_OF_BOUNDS if `channelIndex` is out of the
   *   available channel indices.
   */
  voYesNo (VO_MSE_CALL *isFloatArrayCompatible)(voEngine engine, voEngineObject target,
                                                int channelIndex);

  /**
   * Returns the float array corresponding to the stroke samples of a given
   * channel.
   *
   * @param engine the engine.
   * @param target the target stroke.
   * @param channelIndex the index of the channel to get samples from.
   *
   * @return a pointer to the float array that contains the channel samples.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStroke`.
   * @throws VO_INDEX_OUT_OF_BOUNDS if `channelIndex` is out of the
   *   available channel indices.
   * @throws VO_INVALID_STATE if this function cannot be called (use
   *   `getValuesAsFloat()` instead).
   */
  const float* (VO_MSE_CALL *getFloatArray)(voEngine engine, voEngineObject target,
                                            int channelIndex);

  /**
   * Returns the float values of a given channel of the stroke.
   *
   * @param engine the engine.
   * @param target the target stroke.
   * @param channelIndex the index of the channel to get samples from.
   * @param sampleOffset the offset of the samples to retrieve.
   * @param sampleCount the number of samples to retrieve.
   * @param firstValue the array of float to be filled.
   * @param byteStride the offset, in bytes, between 2 values in
   *   `firstValue`.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStroke`.
   * @throws VO_INDEX_OUT_OF_BOUNDS if `channelIndex` is out of the
   *   available channel indices.
   * @throws VO_INDEX_OUT_OF_BOUNDS if `sampleOffset` and/or
   *   `sampleCount` are out of the available data indexes.
   * @throws VO_INVALID_ARGUMENT if `firstValue` is NULL.
   */
  bool (VO_MSE_CALL *getValuesAsFloat)(voEngine engine, voEngineObject target,
                                       int channelIndex,
                                       int sampleOffset, int sampleCount,
                                       float* firstValue, size_t byteStride);

  /**
   * Returns whether the sample data for a given channel can be retrieved as
   * a direct int32_t array.
   *
   * @param engine the engine.
   * @param target the target stroke.
   * @param channelIndex the index of the channel to get samples from.
   *
   * @return `VO_YES` if points for channel `channelIndex`
   *         can be retrieved by calling `getInt32Array()`,
   *         `VO_NO`  if points for channel `channelIndex`
   *         must be retrieved by calling `getValuesAsInt32()`,
   *         `VO_ERR` if an error occurred.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStroke`.
   * @throws VO_INDEX_OUT_OF_BOUNDS if `channelIndex` is out of the
   *   available channel indices.
   */
  voYesNo (VO_MSE_CALL *isInt32ArrayCompatible)(voEngine engine, voEngineObject target,
                                                int channelIndex);

  /**
   * Returns the int32_t array corresponding to the stroke samples of a given
   * channel.
   *
   * @param engine the engine.
   * @param target the target stroke.
   * @param channelIndex the index of the channel to get samples from.
   *
   * @return a pointer to the int32_t array that contains the channel samples.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStroke`.
   * @throws VO_INDEX_OUT_OF_BOUNDS if `channelIndex` is out of the
   *   available channel indices.
   * @throws VO_INVALID_STATE if this function cannot be called (use
   *   `getValuesAsInt32()` instead).
   */
  const int32_t* (VO_MSE_CALL *getInt32Array)(voEngine engine, voEngineObject target,
                                              int channelIndex);

  /**
   * Returns int32_t values of a given channel of the stroke.
   *
   * @param engine the engine.
   * @param target the target stroke.
   * @param channelIndex the index of the channel to get samples from.
   * @param sampleOffset the offset of the samples to retrieve.
   * @param sampleCount the number of samples to retrieve.
   * @param firstValue the array of int32_t to be filled.
   * @param byteStride the offset, in bytes, between 2 values in
   *   `firstValue`.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStroke`.
   * @throws VO_INDEX_OUT_OF_BOUNDS if `channelIndex` is out of the
   *   available channel indices.
   * @throws VO_INDEX_OUT_OF_BOUNDS if `sampleOffset` and/or
   *   `sampleCount` are out of the available data indices.
   * @throws VO_INVALID_ARGUMENT if `firstValue` is NULL.
   */
  bool (VO_MSE_CALL *getValuesAsInt32)(voEngine engine, voEngineObject target,
                                       int channelIndex,
                                       int sampleOffset, int sampleCount,
                                       int32_t* firstValue, size_t byteStride);

  /**
   * Returns whether the sample data for a given channel can be retrieved as
   * a direct int64_t array.
   *
   * @param engine the engine.
   * @param target the target stroke.
   * @param channelIndex the index of the channel to get points from.
   *
   * @return `VO_YES` if points for channel `channelIndex`
   *   can be retrieved by calling `getInt32Array()`,
   *   `VO_NO`  if points for channel `channelIndex` must
   *   be retrieved by calling `getValuesAsInt32()`,
   *   `VO_ERR` if an error occurred.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStroke`.
   * @throws VO_INDEX_OUT_OF_BOUNDS if `channelIndex` is out of the
   *   available channel indices.
   */
  voYesNo (VO_MSE_CALL *isInt64ArrayCompatible)(voEngine engine, voEngineObject target,
                                                int channelIndex);

  /**
   * Returns the int64_t array corresponding to the stroke samples for a given
   * channel.
   *
   * @param engine the engine.
   * @param target the target stroke.
   * @param channelIndex the index of the channel to get samples from.
   *
   * @return a pointer to the int64_t array that contains the channel samples.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStroke`.
   * @throws VO_INDEX_OUT_OF_BOUNDS if `channelIndex` is out of the
   *   available channel indices.
   * @throws VO_INVALID_STATE if this function cannot be called (use
   *   `getValuesAsInt64()` instead).
   */
  const int64_t* (VO_MSE_CALL *getInt64Array)(voEngine engine, voEngineObject target,
                                              int channelIndex);

  /**
   * Returns int64_t values of a given channel of the stroke.
   *
   * @param engine the engine.
   * @param target the target stroke.
   * @param channelIndex the index of the channel to get samples from.
   * @param sampleOffset the offset of the samples to retrieve.
   * @param sampleCount the number of samples to retrieve.
   * @param firstValue the array of int64_t to be filled.
   * @param byteStride the offset, in bytes, between 2 values in
   *   `firstValue`.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStroke`.
   * @throws VO_INDEX_OUT_OF_BOUNDS if `channelIndex` is out of the
   *   available channel indices.
   * @throws VO_INDEX_OUT_OF_BOUNDS if `sampleOffset` and/or
   *   `sampleCount` are out of the available data indices.
   * @throws VO_INVALID_ARGUMENT if `firstValue` is NULL.
   */
  bool (VO_MSE_CALL *getValuesAsInt64)(voEngine engine, voEngineObject target,
                                       int channelIndex,
                                       int sampleOffset, int sampleCount,
                                       int64_t* firstValue, size_t byteStride);

}
voIInkStroke;

/**
 * Represents the parameters required to create an axis aligned voGlyph.
 */
typedef struct _voGlyphInitializer1
{
  /**
   * The input character describing the glyph.
   */
  voInputCharacter character;

  /**
   * The extent (or bounding box) of the glyph.
   */
  voExtent extent;

  /**
   * The charset used to encode unit, or `NULL` to use the default charset.
   */
  voCharset charset;

  /**
   * The unit in which `extent` is expressed, formatted following the SI
   * (International System of Units), for example: `mm`, `s`, etc
   * `unit` may be left empty, which indicates that no unit is specified.
   */
  voString unit;
}
voGlyphInitializer1;

/**
 * Represents the parameters required to create a voGlyph.
 */
typedef struct _voGlyphInitializer2
{
  /**
   * The input character describing the glyph.
   */
  voInputCharacter character;

  /**
   * The glyph bounding parallelogram, the origin point beeing the top left
   * point for a straight glyph, and u, the vector on top of the glyph.
   */
  voParallelogram parallelogram;

  /**
   * The charset used to encode unit, or `NULL` to use the default charset.
   */
  voCharset charset;

  /**
   * The unit in which `parallelogram` is expressed, formatted following the SI
   * (International System of Units), for example: `mm`, `s`, etc.
   * `unit` may be left empty, which indicates that no unit is specified.
   */
  voString unit;
}
voGlyphInitializer2;

/**
 * Represents the typography lines of a glyph.
 */
typedef struct _voGlyphLines
{
  /**
   * The ratio of the baseline from the top side of the glyph. It can be greater
   * that `1` or negative if this glyph is not properly placed on a long text
   * line.
   */
  float baseline;
  /**
   * The positive ratio between the height of the x letter, and the height of
   * the glyph. `0` means unspecified.
   */
  float x_height;
}
voGlyphLines;

/**
 * Represents the parameters required to create a positionned voGlyph.
 */
typedef struct _voGlyphInitializer3
{
  /**
   * The input character describing the glyph.
   */
  voInputCharacter character;

  /**
   * The glyph bounding parallelogram, the origin point beeing the top left
   * point for a straight glyph, and u, the vector on top of the glyph.
   */
  voParallelogram parallelogram;

  /**
   * The glyph typography lines.
   */
  voGlyphLines lines;

  /**
   * The charset used to encode unit, or `NULL` to use the default charset.
   */
  voCharset charset;

  /**
   * The unit in which `parallelogram` is expressed, formatted following the SI
   * (International System of Units), for example: `mm`, `s`, etc.
   * `unit` may be left empty, which indicates that no unit is specified.
   */
  voString unit;
}
voGlyphInitializer3;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `Glyph` type.
 *
 * @param engine the engine.
 * @param glyphInitializer the `voGlyphInitializer1` used for glyph
 *   creation.
 *
 * @return A reference to the newly created `Glyph` object on success,
 *   otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `Glyph` instances would
 *   exceed the allowed limit (please remember that the limit can be shared
 *   among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voGlyph voCreateGlyph1(voEngine engine, const voGlyphInitializer1* glyphInitializer)
{
  return voCreateObjectEx(engine, VO_Glyph, glyphInitializer, sizeof(*glyphInitializer));
}

/**
 * Creates an instance of the `Glyph` type.
 *
 * @param engine the engine.
 * @param glyphInitializer the `voGlyphInitializer2` used for glyph
 *   creation.
 *
 * @return A reference to the newly created `Glyph` object on success,
 *   otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `Glyph` instances would
 *   exceed the allowed limit (please remember that the limit can be shared
 *   among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voGlyph voCreateGlyph2(voEngine engine, const voGlyphInitializer2* glyphInitializer)
{
  return voCreateObjectEx(engine, VO_Glyph, glyphInitializer, sizeof(*glyphInitializer));
}

/**
 * Creates an instance of the `Glyph` type.
 *
 * @param engine the engine.
 * @param glyphInitializer the `voGlyphInitializer3` used for glyph
 *   creation.
 *
 * @return A reference to the newly created `Glyph` object on success,
 *   otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `Glyph` instances would
 *   exceed the allowed limit (please remember that the limit can be shared
 *   among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voGlyph voCreateGlyph3(voEngine engine, const voGlyphInitializer3* glyphInitializer)
{
  return voCreateObjectEx(engine, VO_Glyph, glyphInitializer, sizeof(*glyphInitializer));
}
#endif // end of: #ifndef VO_NO_FUNCTIONS

/**
 * Functions composing the `IGlyph` interface.
 *
 * {@implementingTypes voGlyph}
 * @see VO_IGlyph.
 */
typedef struct _voIGlyph
{
  /**
   * Returns the most probable label of this glyph.
   *
   * @param engine the engine.
   * @param target the target glyph.
   * @param charset the charset to be used to encode `string`. Set
   *   this to NULL to use the default charset.
   * @param string a recipient for the label associated with the target with
   *   highest probability.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION
   *   if `voGetType(engine, target) != VO_Glyph`.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `string` recipient is not
   *   readable or writable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the
   *   `string` recipient is not writable.
   */
  bool (VO_MSE_CALL *getLabel)(voEngine engine, voEngineObject target, voCharset charset, voString* string);

  /**
   * Returns the parallelogram that defines the glyph. It is redundant with the
   * samples that are read through the `IInkStroke` interface.
   *
   * @param engine the engine.
   * @param target the target glyph.
   * @param parallelogram a recipient for the bounding parallelogram.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION
   *   if `voGetType(engine, target) != VO_Glyph`.
   * @throws VO_INVALID_USER_BUFFER the `parallelogram` recipient is not
   *   readable or writable.
   */
  bool (VO_MSE_CALL *getParallelogram)(voEngine engine, voEngineObject target, voParallelogram* parallelogram);

  /**
   * Returns whether the target glyph has typography lines defined.
   *
   * @param engine the engine.
   * @param target the target glyph.
   *
   * @return `VO_YES` if lines are defined for this glyph, `VO_NO` if not,
   *   `VO_ERR` if an error occurred.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION
   *   if `voGetType(engine, target) != VO_Glyph`.
   */
  voYesNo (VO_MSE_CALL *hasLines)(voEngine engine, voEngineObject target);

  /**
   * Returns the typography lines of the target glyph.
   *
   * @param engine the engine.
   * @param target the target glyph.
   * @param lines a recipient for the typography lines.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION
   *   if `voGetType(engine, target) != VO_Glyph`.
   * @throws VO_INVALID_USER_BUFFER the `lines` recipient is not
   *   readable or writable.
   */
  bool (VO_MSE_CALL *getLines)(voEngine engine, voEngineObject target, voGlyphLines* lines);

  /**
   * Returns the alternate count of the target glyph.
   *
   * @param engine the engine.
   * @param target the target glyph.
   *
   * @return alternate count on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION
   *   if `voGetType(engine, target) != VO_Glyph`.
   */
  int (VO_MSE_CALL *getAlternateCount)(voEngine engine, voEngineObject target);

  /**
   * Returns the alternate at the specified index of the target glyph.
   *
   * @param engine the engine.
   * @param target the target glyph.
   * @param charset the charset to be used to encode the value.
   * @param string a recipient for the value of the alternate.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION
   *   if `voGetType(engine, target) != VO_Glyph`.
   * @throws VO_INDEX_OUT_OF_BOUNDS the `index` is invalid.
   * @throws VO_INVALID_USER_BUFFER the `p` recipient is not
   *   readable or writable.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `string` recipient is not
   *   readable or writable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the
   *   `string` recipient is not writable.
   */
  bool (VO_MSE_CALL *getAlternateAt)(voEngine engine, voEngineObject target, int index, float* p, voCharset charset, voString* string);

} voIGlyph;


/**
 * Lists the decoration types.
 * This enum matches the VO_SHAPE_DECORATION_TYPE defined in MyScriptShape.h.
 */
enum VO_INK_DECORATION_TYPE
{
  /**
   * No decoration.
   */
  VO_INK_DECORATION_NONE,

  /**
   * Arrow head.
   */
  VO_INK_DECORATION_ARROW_HEAD
};

/**
 * Represents the parameters required to create a voArcPrimitive, using center
 * parameterization.
 */
typedef struct _voArcPrimitiveInitializer
{
  /**
   * The geometric parametrization of the primitive.
   * The angle parameters can be modified internally so that the phi angle
   * belongs to the interval ]-pi/2 ; pi/2].
   */
  voCenterEllipticArc data;

  /**
   * The type of decoration at the first point of the primitive,
   * `VO_INK_DECORATION_NONE` by default.
   */
  voId firstDecoration;

  /**
   * The type of decoration at the last point of the primitive,
   * `VO_INK_DECORATION_NONE` by default.
   */
  voId lastDecoration;

  /**
   * The charset used to encode unit, or `NULL` to use the default charset.
   */
  voCharset charset;

  /**
   * The unit in which `data` is expressed, formatted following the SI
   * (International System of Units), for example: `mm`, `s`, etc.
   * `unit` may be left empty, which indicates that no unit is specified.
   */
  voString unit;

} voArcPrimitiveInitializer;

/**
 * Represents the parameters required to create a voArcPrimitive, using endpoint
 * parameterization.
 */
typedef struct _voArcPrimitiveInitializer2
{
  /**
   * The geometric parametrization of the primitive.
   * The angle parameter phi might be modified internally so that it
   * belongs to the interval ]-pi/2 ; pi/2].
   * The radii rx and ry also might be scaled to fit the provided end points.
   */
  voEndpointEllipticArc data;

  /**
   * The type of decoration at the first point of the primitive,
   * `VO_INK_DECORATION_NONE` by default.
   */
  voId firstDecoration;

  /**
   * The type of decoration at the last point of the primitive,
   * `VO_INK_DECORATION_NONE` by default.
   */
  voId lastDecoration;

  /**
   * The charset used to encode unit, or `NULL` to use the default charset.
   */
  voCharset charset;

  /**
   * The unit in which `data` is expressed, formatted following the SI
   * (International System of Units), for example: `mm`, `s`, etc.
   * `unit` may be left empty, which indicates that no unit is specified.
   */
  voString unit;
} voArcPrimitiveInitializer2;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `ArcPrimitive` type.
 *
 * @param engine the engine.
 * @param primitiveInitializer the `voArcPrimitiveInitializer` used for primitive creation.
 *
 * @return A reference to the newly created `ArcPrimitive` object on success,
 *   otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `ArcPrimitive` instances would
 *   exceed the allowed limit (please remember that the limit can be shared
 *   among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voArcPrimitive voCreateArcPrimitive(voEngine engine, const voArcPrimitiveInitializer* primitiveInitializer)
{
  return voCreateObjectEx(engine, VO_ArcPrimitive, primitiveInitializer, sizeof(voArcPrimitiveInitializer));
}

/**
 * Creates an instance of the `ArcPrimitive` type.
 *
 * @param engine the engine.
 * @param primitiveInitializer the `voArcPrimitiveInitializer2` used for primitive creation.
 *
 * @return A reference to the newly created `ArcPrimitive` object on success,
 *   otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `ArcPrimitive` instances would
 *   exceed the allowed limit (please remember that the limit can be shared
 *   among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voArcPrimitive voCreateArcPrimitive2(voEngine engine, const voArcPrimitiveInitializer2* primitiveInitializer)
{
  return voCreateObjectEx(engine, VO_ArcPrimitive, primitiveInitializer, sizeof(voArcPrimitiveInitializer2));
}
#endif // end of: #ifndef VO_NO_FUNCTIONS

/**
 * Represents the parameters required to create a voLinePrimitive.
 */
typedef struct _voLinePrimitiveInitializer
{
  /**
   * The voLineSegment describing the line primitive.
   */
  voLineSegment data;

  /**
   * The VO_INK_DECORATION_TYPE for the first point of the primitive, VO_INK_DECORATION_NONE by default.
   */
  voId firstDecoration;

  /**
   * The VO_INK_DECORATION_TYPE for the first point of the primitive, VO_INK_DECORATION_NONE by default.
   */
  voId lastDecoration;

  /**
   * The charset used to encode unit, or `NULL` to use the default charset.
   */
  voCharset charset;

  /**
   * The unit in which `data` is expressed, formatted following the SI
   * (International System of Units), for example: `mm`, `s`, etc.
   * `unit` may be left empty, which indicates that no unit is specified.
   */
  voString unit;
}
voLinePrimitiveInitializer;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `LinePrimitive` type.
 *
 * @param engine the engine.
 * @param primitiveInitializer the `voLinePrimitiveInitializer` used for primitive creation.
 *
 * @return A reference to the newly created `ArcPrimitive` object on success,
 *   otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `ArcPrimitive` instances would
 *   exceed the allowed limit (please remember that the limit can be shared
 *   among several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voLinePrimitive voCreateLinePrimitive(voEngine engine, const voLinePrimitiveInitializer* primitiveInitializer)
{
  return voCreateObjectEx(engine, VO_LinePrimitive, primitiveInitializer, sizeof(voLinePrimitiveInitializer));
}

#endif // end of: #ifndef VO_NO_FUNCTIONS

/**
 * Functions composing the `IPrimitive` interface.
 *
 * {@implementingTypes voArcPrimitive, voLinePrimitive}
 * @see VO_IPrimitive.
 */
typedef struct _voIPrimitive
{
  /**
   * Returns the intrinsic geometric parameters of this primitive. The actual
   * type of the returned data depends on the type of the target primitive,
   * resolved by the provided size of data recipient:
   * For a `voLinePrimitive` you must give a pointer to a `voLineSegment`.
   * For a `voArcPrimitive` you must give either a pointer to a
   * `voEndpointEllipticArc` or a pointer to a `voCenterEllipticArc`.
   *
   * @param engine the engine.
   * @param target the target primitive.
   * @param data the recipient for the geometric parameters.
   * @param sizeOfData the size of the data recipient.
   *
   * @return true on success, otherwise false.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement `voIPrimitive`.
   * @throws VO_INVALID_USER_BUFFER if `data` is NULL.
   * @throws VO_INVALID_ARGUMENT if `sizeOfData` does not correspond to one of
   *   the possible data for the target primitive.
   */
  bool (VO_MSE_CALL *getData)(voEngine engine, voEngineObject target, void* data, size_t sizeOfData);

  /**
   * Returns the type of the decoration at the first endpoint.
   *
   * @param engine the engine.
   * @param target the target primitive.
   *
   * @return the type of the decoration on success, `-1` otherwise.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement `voIPrimitive`.
   *
   * @see VO_INK_DECORATION_TYPE
   */
  voId (VO_MSE_CALL *getFirstDecoration)(voEngine engine, voEngineObject target);

  /**
   * Returns the tangent angle at the first endpoint. Note that this is a
   * derived property that is computed from the intrinsic geometric parameters.
   *
   * @param engine the engine.
   * @param target the target primitive.
   * @param angle a recipient for the computed tangent angle.
   *
   * @return true on success, otherwise false.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement `voIPrimitive`.
   * @throws VO_INVALID_USER_BUFFER if `angle` is NULL.
   */
  bool (VO_MSE_CALL *getFirstTangentAngle)(voEngine engine, voEngineObject target, float* angle);

  /**
   * Returns the type of the decoration at the last endpoint.
   *
   * @param engine the engine.
   * @param target the target primitive.
   *
   * @return the type of the decoration on success, `-1` otherwise.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement `voIPrimitive`.
   *
   * @see VO_INK_DECORATION_TYPE
   */
  voId (VO_MSE_CALL *getLastDecoration)(voEngine engine, voEngineObject target);

  /**
   * Returns the tangent angle at the last endpoint. Note that this is a
   * derived property that is computed from the intrinsic geometric parameters.
   *
   * @param engine the engine.
   * @param target the target primitive.
   * @param angle a recipient for the computed tangent angle.
   *
   * @return true on success, otherwise false.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement `voIPrimitive`.
   * @throws VO_INVALID_USER_BUFFER if `angle` is NULL.
   */
  bool (VO_MSE_CALL *getLastTangentAngle)(voEngine engine, voEngineObject target, float* angle);
}
voIPrimitive;

/**
 * Functions composing the `IInkStrokeBuilder` interface.
 *
 * {@implementingTypes voInkStrokeBuilder}
 * @see VO_IInkStrokeBuilder.
 */
typedef struct _voIInkStrokeBuilder
{
  /**
   * Clears this stroke builder so that you can start building a new stroke.
   *
   * @param engine the engine.
   * @param target the target stroke builder.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *         `IInkStrokeBuilder` interface.
   */
  bool (VO_MSE_CALL *clear)(voEngine engine, voEngineObject target);

  /**
   * Adds a new sample to the stroke being built.
   *
   * @param engine the engine.
   * @param target the target stroke builder.
   * @param signature the description of a sample, with one character per
   *   channel. For example "FFI" means following parameters will be float,
   *   float and int. Signature must match the channel settings of the stroke
   *   format.
   * @param ... the sample values corresponding to `signature`
   *   indications.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *         `IInkStrokeBuilder` interface.
   * @throws VO_LIMIT_EXCEEDED if sample count would exceed `32767`.
   * @throws VO_INVALID_ARGUMENT if `signature` is NULL.
   */
  bool (VO_MSE_CALL *addSample)(voEngine engine, voEngineObject target, const char* signature, ...);

  /**
   * Adds a new sample to the stroke being built.
   *
   * @param engine the engine.
   * @param target the target stroke builder.
   * @param signature the description of a sample, with one character per
   *   channel. For example "FFI" means following parameters will be float,
   *   float and int. Signature must match the channel settings of the stroke
   *   format.
   * @param args the sample values corresponding to `signature`
   *   indications.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *         `IInkStrokeBuilder` interface.
   * @throws VO_LIMIT_EXCEEDED if sample count would exceed `32767`.
   * @throws VO_INVALID_ARGUMENT if `signature` is NULL.
   */
  bool (VO_MSE_CALL *addSampleV)(voEngine engine, voEngineObject target, const char* signature, va_list args);

  /**
   * Adds a new sample to the stroke being built.
   *
   * @param engine the engine.
   * @param target the target stroke builder.
   * @param values a table containing the new sample channel values.
   * @param count the number of channels in `values`.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *         `IInkStrokeBuilder` interface.
   * @throws VO_LIMIT_EXCEEDED if sample count would exceed `32767`.
   * @throws VO_INVALID_ARGUMENT if `values` is NULL
   *         or if `count` is 0.
   *         or if `count` is greater than the number of channels.
   */
  bool (VO_MSE_CALL *addSampleA_f)(voEngine engine, voEngineObject target, const float values[], int count);

  /**
   * Creates the built stroke.
   *
   * @param engine the engine.
   * @param target the target stroke builder.
   *
   * @return the newly created stroke on success, otherwise `NULL`.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `IInkStrokeBuilder` interface.
   * @throws VO_INVALID_STATE if `target` does not contains any
   *   sample.
   */
  voInkStroke (VO_MSE_CALL *createStroke)(voEngine engine, voEngineObject target);
}
voIInkStrokeBuilder;

/**
 * Functions composing the `IInkStrokeSet` interface.
 *
 * {@implementingTypes voInk, voInkIntervals}
 * @see VO_IInkStrokeSet.
 */
typedef struct _voIInkStrokeSet
{
  /**
   * Returns the number of strokes.
   *
   * @param engine the engine.
   * @param target the target stroke set.
   *
   * @return the number of strokes on success, otherwise `-1`.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStrokeSet`.
   */
  int (VO_MSE_CALL *getStrokeCount)(voEngine engine, voEngineObject target);

  /**
   * Returns the stroke at the specified index.
   *
   * @param engine the engine.
   * @param target the target stroke set.
   * @param index the index of the stroke to retrieve.
   *
   * @return the requested stroke on success, otherwise `NULL`.
   *
   * @throws VO_INVALID_OPERATION if `target` does not implement
   *   `voIInkStrokeSet`.
   * @throws VO_INDEX_OUT_OF_BOUNDS if `index` exceeds stroke count.
   */
  voInkStroke (VO_MSE_CALL *getStrokeAt)(voEngine engine, voEngineObject target, int index);
}
voIInkStrokeSet;

/**
 * Functions composing the `IInkIntervals` interface. This interface
 * exposes the public methods of the `InkIntervals` type.
 *
 * {@implementingTypes voInkIntervals}
 * @see VO_IInkIntervals, VO_InkIntervals.
 */
typedef struct _voIInkIntervals
{
  /**
   * Converts the target intervals into a `voInkSegment`.
   *
   * @param engine the engine.
   * @param target the target intervals.
   *
   * @return the ink segment corresponding to the selection on success,
   *   otherwise `NULL`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInkIntervals`.
   */
  voInkSegment (VO_MSE_CALL *toSegment)(voEngine engine, voInkIntervals target);

  /**
   * Returns the number of intervals that compose this ink intervals.
   *
   * @param engine the engine.
   * @param target the target intervals.
   *
   * @return the number of intervals on success, otherwise `-1`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInkIntervals`.
   */
  int (VO_MSE_CALL *getIntervalCount)(voEngine engine, voInkIntervals target);

  /**
   * Returns the interval at the specified index.
   *
   * @param engine the engine.
   * @param target the target intervals.
   * @param index the index of the interval to retrieve.
   * @param result a recipient for the interval value.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInkIntervals`.
   * @throws VO_INDEX_OUT_OF_BOUNDS if `index` exceeds interval count.
   * @throws VO_INVALID_ARGUMENT if `result` is NULL.
   */
  bool (VO_MSE_CALL *getIntervalAt)(voEngine engine, voInkIntervals target,
                                    int index, voInkInterval* result);

  /**
   * Lookups the target intervals for the specified cursor.
   *
   * @param engine the engine.
   * @param target the target intervals.
   * @param cursor the cursor to search for.
   * @param ptr_index a recipient for the interval index.
   *
   * @return `VO_YES` if the cursor is inside the interval at the
   *   returned index, `VO_NO` if the cursor is before the interval
   *   at the returned index, `VO_ERR` if an error occurred.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInkIntervals`.
   */
  voYesNo (VO_MSE_CALL *lookup)(voEngine engine, voInkIntervals target,
                                const voInkCursor* cursor, int* ptr_index);

  /**
   * Tells whether the two intervals intersects or not.
   *
   * @param engine the engine.
   * @param target the target intervals.
   * @param ref the reference intervals to test the intersection with.
   * @param equals a pointer to a boolean value that will be set to true if the
   *   intervals are equal.
   *
   * @return `VO_YES` if the target intersects, `VO_NO`
   *   if they are disjoint, `VO_ERR` if an error occurred.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInkIntervals`.
   * @throws VO_INVALID_OPERATION if `ref` is not a
   *   `voInkIntervals`.
   */
  voYesNo (VO_MSE_CALL *intersects)(voEngine engine, voInkIntervals target,
                                    voInkIntervals ref, bool* equals);

}
voIInkIntervals;

/**
 * Represents the way a lookup handles the query intervals parameter.
 */
typedef enum _voInkIntervalsMatchMode
{
  /**
   * Search for objects that strictly include the query.
   */
  VO_INKINTERVALS_MATCH_INCLUDE = 0,

  /**
   * Search for objects that possess exactly the query.
   */
  VO_INKINTERVALS_MATCH_EXACT = 1,

  /**
   * Search for objects that intersect the query.
   */
  VO_INKINTERVALS_MATCH_INTERSECT = 2,
}
voInkIntervalsMatchMode;

/**
 * Represents the parameters to run a lookup on tag set.
 */
typedef struct _voInkTagQuery
{
  /**
   * The id of the tag to look for, or `-1` for any id.
   */
  int64_t id;

  /**
   * The charset used to encode name, or `NULL` to use the default charset.
   */
  voCharset charset;

  /**
   * The name of the tag(s) to look for, or empty string for any name.
   */
  voString name;

  /**
   * The intervals to look for, or `NULL` for any intervals.
   */
  voInkIntervals intervals;

  /**
   * The intervals match mode : do the provided intervals match exactly
   * (or be included by, or intersect with) the tags's segments?
   */
  voInkIntervalsMatchMode mode;
}
voInkTagQuery;

#define voInkTagQuery_EMPTY_INITIALIZER                       { -1, NULL, { NULL, 0 }, NULL, VO_INKINTERVALS_MATCH_INCLUDE }
#define voInkTagQueryById_INITIALIZER(id)                     { id, NULL, { NULL, 0 }, NULL, VO_INKINTERVALS_MATCH_INCLUDE }
#define voInkTagQueryByVoString_INITIALIZER(string)           { -1, NULL, string, NULL, VO_INKINTERVALS_MATCH_INCLUDE }
#define voInkTagQueryByName_INITIALIZER(name)                 { -1, NULL, voString_INITIALIZER(name), NULL, VO_INKINTERVALS_MATCH_INCLUDE }
#define voInkTagQueryByIntervals_INITIALIZER(intervals, mode) { -1, NULL, { NULL, 0 }, intervals, mode }

/**
 * Functions composing the `IInk` interface. This interface exposes
 * the public methods of the `Ink` type.
 *
 * {@implementingTypes voInk}
 * @see VO_IInk, VO_Ink.
 */
typedef struct _voIInk
{
  /**
   * Adds the specified listener to the target ink.
   *
   * @param engine the engine.
   * @param target the target ink.
   * @param listener the listener to add.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInk`.
   * @throws VO_INVALID_OBJECT if `listener` does not implement the
   *   `IInkUpdateListener` interface.
   * @throws VO_INVALID_STATE if `listener` is already registered.
   */
  bool (VO_MSE_CALL *addListener)(voEngine engine, voInk target, voEngineObject listener);

  /**
   * Removes the specified listener from the target ink.
   *
   * @param engine the engine.
   * @param target the target ink.
   * @param listener the listener to remove.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInk`.
   * @throws VO_INVALID_OBJECT if `listener` does not implement the
   *   `IInkUpdateListener` interface.
   * @throws VO_INVALID_STATE if `listener` is not registered in this
   *   ink.
   */
  bool (VO_MSE_CALL *removeListener)(voEngine engine, voInk target, voEngineObject listener);

  /**
   * Adds a stroke to the target ink.
   * If stroke format differs from the existing strokes formats, its samples
   * are converted to ensure that the units associated with each stroke format
   * channel is the same for all strokes.
   *
   * @param engine the engine.
   * @param target the target ink.
   * @param stroke the stroke to add.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInk`.
   * @throws VO_INVALID_OBJECT if `stroke` is not a
   *   `voInkStroke`.
   * @throws VO_INVALID_STATE if `stroke` is already part of the
   *   target stroke set or already belongs to another stroke.
   * @throws VO_LIMIT_EXCEEDED if stroke count would exceed `32767`.
   */
  bool (VO_MSE_CALL *addStroke)(voEngine engine, voInk target, voInkStroke stroke);

  /**
   * Adds a stroke to the target ink and also add it to existing tags.
   *
   * @param engine the engine.
   * @param target the target ink.
   * @param stroke the stroke to add.
   * @param tagIds a table of the tags to add the stroke to.
   * @param tagCount the number of ids the table contains.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInk`.
   * @throws VO_INVALID_OBJECT if `stroke` is not a
   *   `voInkStroke`.
   * @throws VO_INVALID_STATE if `stroke` is already part of the
   *   target stroke set or already belongs to another stroke set.
   * @throws VO_LIMIT_EXCEEDED if stroke count would exceed `32767`.
   * @throws VO_INVALID_ARGUMENT if tagIds is `NULL` with a strictly
   *   positive tagCount, or inversely.
   * @throws VO_INVALID_ARGUMENT if one of the tagIds is invalid.
   */
  bool (VO_MSE_CALL *addStrokeEx)(voEngine engine, voInk target, voInkStroke stroke, int64_t* tagIds, int tagCount);

  /**
   * Adds all the strokes from the specified set into this ink.
   *
   * @param engine the engine.
   * @param target the target ink.
   * @param strokeSet the set of strokes to copy. Any object implementing the
   *   `IInkStrokeSet` interface can be used here.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInk`.
   * @throws VO_INVALID_OBJECT if `strokeSet` does not implement
   *   `voIInkStrokeSet`.
   */
  bool (VO_MSE_CALL *paste)(voEngine engine, voInk target, voEngineObject strokeSet);

  /**
   * Erases the specified portion of ink.
   *
   * @param engine the engine.
   * @param target the target ink.
   * @param intervals the ink intervals that represent the portion to erase.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInk`.
   * @throws VO_INVALID_OBJECT if `intervals` is not a
   *   `voInkIntervals`.
   * @throws VO_INVALID_OBJECT if `intervals` does not refer to this
   *   ink.
   */
  bool (VO_MSE_CALL *erase)(voEngine engine, voInk target, voInkIntervals intervals);

  /**
   * Chops the strokes at the lower and upper endpoints of each interval from
   * the given intervals.
   *
   * @param engine the engine.
   * @param target the target ink.
   * @param intervals the intervals that represent the strokes to chop.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInk`.
   * @throws VO_INVALID_OBJECT if `intervals` is not a
   *   `voInkIntervals`.
   * @throws VO_INVALID_OBJECT if `intervals` does not refer to this
   *   ink.
   */
  bool (VO_MSE_CALL *chop)(voEngine engine, voInk target, voInkIntervals intervals);

  /**
   * Transforms the strokes referenced by the given intervals.
   *
   * @param engine the engine.
   * @param target the target ink.
   * @param intervals the intervals that represent the strokes to transform.
   * @param transform the transform matrix that represents the geometrical
   *   transform.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInk`.
   * @throws VO_INVALID_OBJECT if `intervals` is not a
   *   `voInkIntervals`.
   * @throws VO_INVALID_OBJECT if `intervals` does not refer to this
   *   ink.
   * @throws VO_INVALID_STATE if one of the strokes referenced by the intervals
   *   is not an entire or chopped stroke.
   */
  bool (VO_MSE_CALL *transform)(voEngine engine, voInk target, voInkIntervals intervals, const voTransform* transform);

  /**
   * Returns the raw strokes of the target ink as a stroke set. Raw strokes
   * are left unchanged after any of the erase(), chop(), and
   * transform() operations.
   *
   * @param engine the engine.
   * @param target the target ink.
   *
   * @return an object that implements the `IInkStrokeSet` interface.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInk`.
   */
  voEngineObject (VO_MSE_CALL *getRawStrokes)(voEngine engine, voInk target);

  /**
   * Returns the interval associated with a given stroke.
   *
   * @param engine the engine.
   * @param target the target ink.
   * @param stroke the stroke to get the interval from.
   * @param interval the interval to fill with the stroke's interval data.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInk`.
   * @throws VO_INVALID_OBJECT if `stroke` is not a
   *   `voInkStroke`.
   * @throws VO_INVALID_ARGUMENT if `result` is NULL.
   */
  bool (VO_MSE_CALL *getStrokeInterval)(voEngine engine, voInk target, voInkStroke stroke, voInkInterval* result);

  /**
   * Adds a new tag into this ink.
   *
   * @param engine the engine.
   * @param target the target ink.
   * @param charset the charset used to encode `tagName`.
   * @param tagName the name to be associated with the tag.
   * @param intervals the intervals that define the segment to be associated
   *   with the tag, or NULL to if the tag should be empty.
   * @param data the data to be associated with the tag, or NULL if no data
   *   should be associated with the tag.
   *
   * @return the id of the tag just added. On failure `-1`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInk`.
   * @throws VO_INVALID_USER_BUFFER if string or its bytes member is not
   *   readable.
   * @throws VO_INVALID_ARGUMENT if string is empty.
   * @throws VO_INVALID_OBJECT if `charset` is not a
   *   `voCharset`.
   * @throws VO_INVALID_OBJECT if `intervals` is not a
   *   `voInkIntervals`.
   * @throws VO_INVALID_OBJECT if `intervals` does not refer to this
   *   ink.
   */
  int64_t (VO_MSE_CALL *addTag)(voEngine engine, voInk target, voCharset charset, const voString* name, voInkIntervals intervals, voEngineObject data);

  /**
   * Updates a tag from this ink.
   *
   * @param engine the engine.
   * @param target the target ink.
   * @param tagId the id of the tag, as returned by `addTag()`.
   * @param newIntervals the intervals that define the segment to be associated
   *   with the tag, or `NULL` to keep the segment unchanged.
   * @param newData the data to be associated with the tag, or `NULL` to keep
   * the data unchanged.
   *
   * @return true on success, false otherwise.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInk`.
   * @throws VO_INVALID_USER_BUFFER if string or its bytes member is not
   *   readable.
   * @throws VO_INVALID_ARGUMENT if `tagId` is invalid.
   * @throws VO_INVALID_ARGUMENT if both `newIntervals` and
   *   `newData` are NULL.
   */
  bool (VO_MSE_CALL *updateTag)(voEngine engine, voInk target, int64_t tagId, voInkIntervals newIntervals, voEngineObject newData);

  /**
   * Returns the number of tags selected by the specified query.
   *
   * @param engine the engine.
   * @param target the target ink.
   * @param query the query that defines the selection criteria.
   *
   * @return the number of selected tags on success, otherwise `-1`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInk`.
   * @throws VO_INVALID_ARGUMENT if the `query.id` is invalid.
   * @throws VO_INVALID_USER_BUFFER if `query.name` string or its
   *   bytes member is not readable.
   * @throws VO_INVALID_OBJECT if `query.charset` is not a
   *   `voCharset`.
   * @throws VO_INVALID_OBJECT if `query.intervals` is not a
   *   `voInkIntervals`.
   * @throws VO_INVALID_OBJECT if `query.intervals` does not refer to
   *   this ink.
   * @throws VO_INVALID_ARGUMENT if the `query.mode` is invalid.
   */
  int (VO_MSE_CALL *tagLookupCount)(voEngine engine, voInk target, const voInkTagQuery* query);

  /**
   * Returns an iterator over the tags selected by the specified query.
   *
   * @param engine the engine.
   * @param target the target ink.
   * @param query the query that defines the selection criteria.
   *
   * @return an iterator over the selected tags on success, otherwise `NULL`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInk`.
   * @throws VO_INVALID_ARGUMENT if the `query.id` is invalid.
   * @throws VO_INVALID_USER_BUFFER if `query.name` string or its
   *   bytes member is not readable.
   * @throws VO_INVALID_OBJECT if `query.charset` is not a
   *   `voCharset`.
   * @throws VO_INVALID_OBJECT if `query.intervals` is not a
   *   `voInkIntervals`.
   * @throws VO_INVALID_OBJECT if `query.intervals` does not refer to
   *   this ink.
   * @throws VO_INVALID_ARGUMENT if the `query.mode` is invalid.
   */
   voInkTagIterator (VO_MSE_CALL *tagLookup)(voEngine engine, voInk target, const voInkTagQuery* query);

}
voIInk;

/**
 * Lists possible values of the `action` member of `voInkUpdateTagInfo`.
 * @see voInkUpdateTagInfo
 */
enum VO_TAG_ACTION
{
  VO_TAG_ADDED,   /**< The tag was added. */
  VO_TAG_UPDATED, /**< The tag was updated. */
  VO_TAG_DELETED, /**< The tag was deleted. */
};

/**
 * Represents information about what happened to a tag.
 */
typedef struct _voInkUpdateTagInfo
{
  int64_t tagId;  /**< The identifier of the tag. */
  int action;     /**< The action that happened (@see VO_TAG_ACTION). */
  int flags;      /**< The change flags, if any (@see VO_CHANGE_FLAG). */
}
voInkUpdateTagInfo;


/**
 * Functions composing the `IInkUpdateListener` interface.
 * Note that this interface is implementable by user objects. Also, user code is
 * not allowed to invoke this interface, that's why voGetInterface() will return
 * `NULL`.
 */
typedef struct _voIInkUpdateListener
{
  /**
   * Called when the target change listener is added to an ink object.
   *
   * @param engine the engine.
   * @param target the target change listener.
   * @param ink the ink to which the change listener was added.
   */
  void (VO_MSE_CALL *added)(voEngine engine, voEngineObject target, voInk ink);

  /**
   * Called when the target change listener is removed from an ink object.
   *
   * @param engine the engine.
   * @param target the target change listener.
   * @param ink the ink from which the change listener was removed.
   */
  void (VO_MSE_CALL *removed)(voEngine engine, voEngineObject target, voInk ink);

  /**
   * Called when the ink has been updated.
   *
   * @param engine the engine.
   * @param target the target change listener.
   * @param ink the ink that has been updated.
   * @param extent the extent of updates on the X and Y axes. Note that you
   *   should add half the pen width to compute screen update rectangle.
   * @param tagInfos an array of information about tag related actions.
   * @param tagInfoCount the number of items in the above array.
   */
  void (VO_MSE_CALL *onUpdate)(voEngine engine, voEngineObject target, voInk ink, const voExtent* extent, const voInkUpdateTagInfo* tagInfos, int tagInfoCount);
}
voIInkUpdateListener;


/**
 * Represents the way an input will be combine with existing selection.
 */
typedef enum _voSelectionModifier
{
  /**
   * Only use the input in the selection (discard existing selection).
   */
  VO_SELECT_SET = 0,

  /**
   * Select the union between existing selection and input.
   */
  VO_SELECT_UNION = 1,

  /**
   * Select the intersection of existing selection and input.
   */
  VO_SELECT_INTERSECTION = 2,

  /**
   * Select the difference between existing selection and input.
   */
  VO_SELECT_DIFFERENCE = 3
}
voSelectionModifier;


/**
 * Functions composing the `ISelection` interface.
 *
 * {@implementingTypes voInkSelection}
 * @see VO_ISelection.
 */
typedef struct _voISelection
{
  /**
   * Adds the specified change listener to the target selection.
   *
   * @param engine the engine.
   * @param target the target selection.
   * @param listener the change listener to add.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION the `target` does not implement
   *   `voISelection`.
   * @throws VO_INVALID_OBJECT if `listener` does not implement
   *   `voISelectionChangeListener`.
   * @throws VO_INVALID_STATE if `listener` is already registered.
   */
  bool (VO_MSE_CALL *addChangeListener)(voEngine engine, voEngineObject target, voEngineObject listener);

  /**
   * Removes the specified change listener from the target selection.
   *
   * @param engine the engine.
   * @param target the target selection.
   * @param listener the change listener to remove.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION the `target` does not implement
   *   `voISelection`.
   * @throws VO_INVALID_OBJECT if `listener` does not implement
   *   `voISelectionChangeListener`.
   * @throws VO_INVALID_STATE if `listener` is not registered.
   */
  bool (VO_MSE_CALL *removeChangeListener)(voEngine engine, voEngineObject target, voEngineObject listener);

  /**
   * Creates a new selection of the items contained in the specified rectangle
   * and combine it with existing selection.
   *
   * @param engine the engine.
   * @param target the target selection.
   * @param rectangle the rectangle from which to build the selection.
   * @param modifier the way new selection should be combined with the existing
   *   selection.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION the `target` does not implement
   *   `voISelection`.
   * @throws VO_INVALID_ARGUMENT if `rectange == NULL`.
   * @throws VO_INVALID_ARGUMENT if `rectange` has a null dimension.
   */
  bool (VO_MSE_CALL *selectRectangle)(voEngine engine, voEngineObject target, const voRectangle* rectangle, voSelectionModifier modifier);

  /**
   * Creates a new selection of the items that are contained in the specified
   * polygon and combine it with the existing selection.
   *
   * @param engine the engine.
   * @param target the target selection.
   * @param vertices the array of points that define the polygon from which to
   *   build the selection.
   * @param vertexCount the number of points of the polygon.
   * @param modifier the way new selection should be combined with the existing
   *   selection.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION the `target` does not implement
   *   `voISelection`.
   * @throws VO_INVALID_ARGUMENT if `vertices == NULL`.
   * @throws VO_INVALID_ARGUMENT if `vertexCount == 0`.
   */
  bool (VO_MSE_CALL *selectPolygon)(voEngine engine, voEngineObject target, const voPoint* vertices, int vertexCount, voSelectionModifier modifier);

  /**
   * Creates a new selection of the items that are contained in the specified
   * circle and combine it with the existing selection.
   *
   * @param engine the engine.
   * @param target the target selection.
   * @param circle the circle from which to build the selection.
   * @param modifier the way the new selection should be combined with the
   *   existing selection.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION the `target` does not implement
   *   `voISelection`.
   * @throws VO_INVALID_ARGUMENT if `circle == NULL`.
   */
  bool (VO_MSE_CALL *selectCircle)(voEngine engine, voEngineObject target, const voCircle* circle, voSelectionModifier modifier);

  /**
   * Selects all the items from the selection's source.
   *
   * @param engine the engine.
   * @param target the target selection.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION the `target` does not implement
   *   `voISelection`.
   */
  bool (VO_MSE_CALL *selectAll)(voEngine engine, voEngineObject target);

  /**
   * Clears the selection.
   *
   * @param engine the engine.
   * @param target the target selection.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION the `target` does not implement
   *   `voISelection`.
   */
  bool (VO_MSE_CALL *selectNone)(voEngine engine, voEngineObject target);

  /**
   * Combines the existing selection with another selection.
   *
   * @param engine the engine.
   * @param target the target selection.
   * @param other the other selection.
   * @param modifier the way the other selection should be combined with the
   *   existing selection.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION the `target` does not implement
   *   `voISelection`.
   * @throws VO_INVALID_ARGUMENT the `other` has not the same type as
   *   `target`.
   */
  bool (VO_MSE_CALL *combine)(voEngine engine, voEngineObject target, voEngineObject other, voSelectionModifier modifier);
}
voISelection;

/**
 * Functions composing the `IInkSelection` interface. This interface
 * exposes the public methods of the `InkSelection` type.
 *
 * {@implementingTypes voInkSelection}
 * @see VO_IInkSelection, VO_InkSelection.
 */
typedef struct _voIInkSelection
{
  /**
   * Returns the ink on which the target ink selection is based.
   *
   * @param engine the engine.
   * @param target the target ink selection.
   *
   * @return the ink on success, `NULL` otherwise.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a reference to
   *   a `InkSelection` instance.
   * @throws VO_LIMIT_EXCEEDED The number of `InkSelection` instances would
   *   exceed the allowed limit (please remember that the limit can be shared
   *   among several types).
   * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
   */
  voInk (VO_MSE_CALL *getInk)(voEngine engine, voInkSelection target);

  /**
   * Parses the given string as a selection and combine it into the selection.
   *
   * @param engine the engine.
   * @param target the target InkSelection.
   * @param charset the charset used to encode `string`.
   * @param string the string to parse.
   * @param modifier the way the new selection should be combined with the
   *   existing selection.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInkSelection`.
   */
  bool (VO_MSE_CALL *parse)(voEngine engine, voInkSelection target, voCharset charset, const voString* string, voSelectionModifier modifier);


  /**
   * Creates a new selection of the strokes and portion of strokes that are
   * contained in the specified interval and combine it with existing selection.
   *
   * @param engine the engine.
   * @param target the target InkSelection.
   * @param interval the interval from which to build the selection.
   * @param modifier the way the new selection should be combined with the
   *   existing selection.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInkSelection`.
   * @throws VO_INVALID_ARGUMENT if `interval == NULL`.
   * @throws VO_INVALID_ARGUMENT if `interval` does not match existing ink
   *   or if its `from` cursor is after its `to` cursor.
   */
  bool (VO_MSE_CALL *selectInterval)(voEngine engine, voInkSelection target, const voInkInterval* interval, voSelectionModifier modifier);

  /**
   * Creates a new selection of the strokes that are contained in a given tag
   * and combine it with existing selection.
   *
   * @param engine the engine.
   * @param target the target InkSelection.
   * @param tagId the id of the input tag.
   * @param modifier the way the new selection should be combined with the
   *   existing selection.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInkSelection`.
   * @throws VO_INVALID_ARGUMENT if `tagId` does not correspond to a valid tag.
   */
  bool (VO_MSE_CALL *selectTag)(voEngine engine, voInkSelection target, int64_t tagId, voSelectionModifier modifier);

  /**
   * Creates a new selection of the input stroke and combine it with existing
   * selection.
   *
   * @param engine the engine.
   * @param target the target InkSelection.
   * @param stroke the input stroke.
   * @param modifier the way the new selection should be combined with the
   *   existing selection.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInkSelection`.
   * @throws VO_INVALID_OBJECT the `stroke` is not a
   *   `voInkStroke`.
   * @throws VO_INVALID_OBJECT if `stroke` does not belong to the ink
   *   referenced by `target`.
   */
  bool (VO_MSE_CALL *selectStroke)(voEngine engine, voInkSelection target, voInkStroke stroke, voSelectionModifier modifier);

  /**
   * Combine the selection with a given segment.
   *
   * @param engine the engine.
   * @param target the target InkSelection.
   * @param segment the input segment.
   * @param modifier the way the new selection should be combined with the
   *   existing selection.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInkSelection`.
   * @throws VO_INVALID_OBJECT the `stroke` is not a
   *   `voInkStroke`.
   * @throws VO_INVALID_OBJECT if `target` and `intervals`
   *   do not refer to the same ink.
   */
  bool (VO_MSE_CALL *selectIntervals)(voEngine engine, voInkSelection target, voInkIntervals intervals, voSelectionModifier modifier);

  /**
   * Adjusts the selection to full strokes, only if all the selected portions of
   * each stroke exceed the lengthRatio compared to full stroke.
   *
   * @param engine the engine.
   * @param target the target InkSelection.
   * @param selection the selection to adjust.
   * @param lengthRatio the length ratio (between 0 and 1) above which a stroke
   *   will be kept.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInkSelection`.
   * @throws VO_INVALID_ARGUMENT if `lengthRatio` is not between 0
   *   and 1.
   */
  bool (VO_MSE_CALL *adjustToStrokeBoundaries)(voEngine engine, voInkSelection target, float lengthRatio);

  /**
   * Adjusts the selection to a given tag name.
   *
   * @param engine the engine.
   * @param target the target InkSelection.
   * @param selection the selection to adjust.
   * @param charset the charset used to encode `name`.
   * @param name the name of the tag to select.
   * @param overlap the overlap ratio (between 0 and 1) above which a tag will
   *   be kept.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInkSelection`.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `name` recipient is not
   *   readable.
   */
  bool (VO_MSE_CALL *adjustToTagBoundaries)(voEngine engine, voInkSelection target, voCharset charset, const voString* name, float overlapRatio);

  /**
   * Select the closest stroke within a circle.
   *
   * @param engine the engine.
   * @param target the target InkSelection.
   * @param circle the circle to select from.
   * @param modifier the way the new selection should be combined with the
   *   existing selection.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInkSelection`.
   * @throws VO_INVALID_ARGUMENT if `circle` is invalid.
   */
  bool (VO_MSE_CALL *hitStroke)(voEngine engine, voInkSelection target, const voCircle* circle, voSelectionModifier modifier);

  /**
   * Selects the closest tag within a circle. The closest tag is the tag that
   * has the bigger overlap and is closest to the center if more than one tag
   * completely overlap.
   *
   * @param engine the engine.
   * @param target the target InkSelection.
   * @param charset the charset used to encode `name`.
   * @param name the name of the tag to select.
   * @param circle the circle to select from.
   * @param ptr_tagId a recipient that will receive the id of the tag if found,
   *   otherwise -1.
   * @param modifier the way the new selection should be combined with the
   *   existing selection.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `target` is not a
   *   `voInkSelection`.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `name` recipient is not
   *   readable.
   * @throws VO_INVALID_ARGUMENT if `circle` is invalid.
   */
  bool (VO_MSE_CALL *hitTag)(voEngine engine, voInkSelection target, voCharset charset, const voString* name, const voCircle* circle, int64_t* ptr_tagId, voSelectionModifier modifier);
}
voIInkSelection;


/**
 * Lists flag bits for the `flags` parameter of the
 * `voISelectionChangeListener::changed()` and the
 * `voIInkChangeListener::preUpdateTag()` functions.
 * Those flags may be combined using the bitwise OR operator.
 */
enum VO_CHANGE_FLAG
{
  /**
   * Indicates that data changed, which means the intrinsic parameters of an
   * object changed.
   */
  VO_CF_DATA_CHANGED = 1,

  /**
   * Indicates that a transform has been applied on an object or part of that
   * object.
   */
  VO_CF_TRANSFORM_APPLIED = 2,
};

/**
 * Functions composing the `ISelectionChangeListener` interface.
 * Note that this interface is implementable by user objects. Also, user code is
 * not allowed to invoke this interface, that's why voGetInterface() will return
 * `NULL`.
 */
typedef struct _voISelectionChangeListener
{
  /**
   * Called when the target change listener is added to an ink object.
   *
   * @param engine the engine.
   * @param target the target change listener.
   * @param selection the selection to which the change listener was added.
   */
  void (VO_MSE_CALL *added)(voEngine engine, voEngineObject target, voEngineObject selection);

  /**
   * Called when the target change listener is removed from an ink object.
   *
   * @param engine the engine.
   * @param target the target change listener.
   * @param selection the selection from which the change listener was removed.
   */
  void (VO_MSE_CALL *removed)(voEngine engine, voEngineObject target, voEngineObject selection);

  /**
   * Called when the selection has changed.
   *
   * @param engine the engine.
   * @param target the target change listener.
   * @param selection the selection that changed.
   * @param flags an indication of what changed in the selection (@see VO_CHANGE_FLAG).
   */
  void (VO_MSE_CALL *changed)(voEngine engine, voEngineObject target, voEngineObject selection, int flags);
}
voISelectionChangeListener;


/**
 * Functions composing the `IGeometry` interface.
 *
 * @see VO_IGeometry.
 */
typedef struct _voIGeometry
{
  /**
   * Sets the transform to the identity.
   *
   * @param engine the engine.
   * @param transform a pointer to the target transform.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE if `engine` is invalid.
   * @throws VO_INVALID_USER_BUFFER if `transform` is `NULL`.
   */
  bool (VO_MSE_CALL *setIdentity)(voEngine engine, voTransform* transform);

  /**
   * Multiplies the transform with a translation transformation. This is
   * equivalent to calling multiply(T), where T is a <code>Transform</code>
   * represented by the following matrix:
   *
   * <pre>
   *   [   1    0    tx  ]
   *   [   0    1    ty  ]
   *   [   0    0    1   ]
   * </pre>
   *
   * @param engine the engine.
   * @param transform a pointer to the target transform.
   * @param tx the offset along the X axis.
   * @param ty the offset along the Y axis.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE if `engine` is invalid.
   * @throws VO_INVALID_USER_BUFFER if `transform` is `NULL`.
   */
  bool (VO_MSE_CALL *translate)(voEngine engine, voTransform* transform, float tx, float ty);

  /**
   * Multiplies this transform with a scaling transformation. This is equivalent
   * to calling multiply(S), where S is a <code>Transform</code> represented by
   * the following matrix:
   *
   * <pre>
   *   [   sx   0    0   ]
   *   [   0    sy   0   ]
   *   [   0    0    1   ]
   * </pre>
   *
   * @param engine the engine.
   * @param transform a pointer to the target transform.
   * @param sx the scaling factor along the X axis.
   * @param sy the scaling factor along the Y axis.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE if `engine` is invalid.
   * @throws VO_INVALID_USER_BUFFER if `transform` is `NULL`.
   */
  bool (VO_MSE_CALL *scale)(voEngine engine, voTransform* transform, float sx, float sy);

  /**
   * Multiplies the transform with a rotation transformation. This is equivalent
   * to calling multiply(R), where R is a <code>Transform</code> represented by
   * the following matrix:
   *
   * <pre>
   *   [   cos(a)   -sin(a)    -cos(a) * x0 + sin(a) * y0 + x0   ]
   *   [   sin(a)    cos(a)    -sin(a) * x0 - cos(a) * y0 + y0   ]
   *   [   0           0                      1                  ]
   * </pre>
   *
   * @param engine the engine.
   * @param transform a pointer to the target transform.
   * @param a the rotation angle in radians.
   * @param x0 the x position of the origin point.
   * @param y0 the y position of the origin point.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE if `engine` is invalid.
   * @throws VO_INVALID_USER_BUFFER if `transform` is `NULL`.
   */
  bool (VO_MSE_CALL *rotate)(voEngine engine, voTransform* transform, float a, float x0, float y0);

  /**
   * Multiplies the transform with an horizontal shearing transformation. This
   * is equivalent to calling multiply(SHX), where SHX is a
   * <code>Transform</code> represented by the following matrix:
   *
   * <pre>
   *   [    1     tan(a)   -y0 * tan(a) ]
   *   [    0       1           0       ]
   *   [    0       0           1       ]
   * </pre>
   *
   * @param engine the engine.
   * @param transform a pointer to the target transform.
   * @param a the shearing angle in radians.
   * @param y0 the y position of the origin point.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE if `engine` is invalid.
   * @throws VO_INVALID_USER_BUFFER if `transform` is `NULL`.
   */
  bool (VO_MSE_CALL *shearX)(voEngine engine, voTransform* transform, float a, float y0);

  /**
   * Multiplies the transform with a vertical shearing transformation. This is
   * equivalent to calling multiply(SHY), where SHY is a <code>Transform</code>
   * represented by the following matrix:
   *
   * <pre>
   *   [    1       0           0       ]
   *   [   tan(a)   1      -x0 * tan(a) ]
   *   [    0       0           1       ]
   * </pre>
   *
   *
   * @param engine the engine.
   * @param transform a pointer to the target transform.
   * @param a the shearing angle in radians.
   * @param x0 the x position of the origin point.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE if `engine` is invalid.
   * @throws VO_INVALID_USER_BUFFER if `transform` is `NULL`.
   */
  bool (VO_MSE_CALL *shearY)(voEngine engine, voTransform* transform, float a, float x0);

  /**
   * Multiplies the target transform by the second transform.
   *
   * @param engine the engine.
   * @param transform1 a pointer to the target transform.
   * @param transform2 a pointer to the second transform.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE if `engine` is invalid.
   * @throws VO_INVALID_USER_BUFFER if `transform1` is `NULL`.
   * @throws VO_INVALID_USER_BUFFER if `transform2` is `NULL`.
   */
  bool (VO_MSE_CALL *multiply)(voEngine engine, voTransform* transform1, voTransform* transform2);

  /**
   * Inverts the target transform.
   *
   * @param engine the engine.
   * @param transform a pointer to the target transform.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE if `engine` is invalid.
   * @throws VO_INVALID_USER_BUFFER if `transform` is `NULL`.
   * @throws VO_INVALID_STATE if `transform` is not invertible, because its
   *   determinant <code>(a * e - b * d)</code> is zero.
   */
  bool (VO_MSE_CALL *invert)(voEngine engine, voTransform* transform);
}
voIGeometry;


/**
 * Functions composing the `IInkTagIterator` interface.
 *
 * @see VO_IInkTagIterator.
 */
typedef struct _voIInkTagIterator
{

  /**
   * Tells if this iterator is positioned at the end of the iteration.
   *
   * @param engine Reference to an `Engine` instance.
   * @param iterator Reference to the target `EngineObject` instance.
   *
   * @return `VO_YES` or `VO_NO` on success, otherwise
   *   `VO_ERR` on failure.
   *
   * @throws VO_INVALID_OPERATION if `iterator` is not a
   *   `voInkTagIterator`.
   */
  voYesNo (VO_MSE_CALL *isAtEnd)(voEngine engine, voInkTagIterator iterator);

  /**
   * Positions this iterator on the next element of the iteration.
   *
   * @param engine Reference an `Engine` instance.
   * @param iterator Reference to the target `EngineObject` instance.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `iterator` is not a
   *   `voInkTagIterator`.
   * @throws VO_NO_SUCH_ELEMENT if `iterator` is positioned at the
   *   end of the iteration.
   */
  bool (VO_MSE_CALL *next)(voEngine engine, voInkTagIterator iterator);

  /**
   * Removes the tag associated with this iterator. This does not invalidate
   * the iterator so that several tags can be removed in the same iteration.
   *
   * @param engine Reference an `Engine` instance.
   * @param iterator Reference to the target `EngineObject` instance.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `iterator` is not a
   *   `voInkTagIterator`.
   * @throws VO_NO_SUCH_ELEMENT if `iterator` is positioned at the
   *   end of the iteration.
   */
  bool (VO_MSE_CALL *remove)(voEngine engine, voInkTagIterator iterator);

  /**
   * Get the identifier of the tag associated with this iterator.
   *
   * @param engine Reference an `Engine` instance.
   * @param iterator Reference to the target `EngineObject` instance.
   *
   * @return the unsigned index on success, otherwise `-1`.
   *
   * @throws VO_INVALID_OPERATION if `iterator` is not a
   *   `voInkTagIterator`.
   * @throws VO_NO_SUCH_ELEMENT if `iterator` is positioned at the
   *   end of the iteration.
   */
  int64_t (VO_MSE_CALL *getId)(voEngine engine, voInkTagIterator iterator);

  /**
   * Get the name of the tag associated with this iterator.
   *
   * @param engine Reference an `Engine` instance.
   * @param iterator Reference to the target `EngineObject` instance.
   * @param charset Reference to the `Charset` instance that defines
   *   the output string representation.
   * @param string Recipient for the bytes of the output string. On input the
   *   `voString.byteCount` member denotes the maximum number of
   *   bytes allowed (`-1` means infinite). On output the
   *   `voString.byteCount` value receives the actual number of bytes
   *   of the string. You can set the `voString.bytes` member to
   *   `NULL` to retrieve the number of bytes you need to allocate
   *   and make a second call with the allocated bytes.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `iterator` is not a
   *   `voInkTagIterator`.
   * @throws VO_NO_SUCH_ELEMENT if `iterator` is positioned at the
   *   end of the iteration.
   * @throws VO_INVALID_OBJECT if `charset` is not a
   *   `voCharset`.
   * @throws VO_INVALID_USER_BUFFER if `tagName` is not writable.
   */
  bool (VO_MSE_CALL *getName)(voEngine engine, voInkTagIterator iterator, voCharset charset, voString* string);

  /**
   * Get the ink segment of the tag associated with this iterator.
   *
   * @param engine Reference an `Engine` instance.
   * @param iterator Reference to the target `EngineObject` instance.
   *
   * @return the `voInkSegment` on success, otherwise `NULL`.
   *
   * @throws VO_INVALID_OPERATION if `iterator` is not a
   *   `voInkTagIterator`.
   * @throws VO_NO_SUCH_ELEMENT if `iterator` is positioned at the
   *   end of the iteration.
   */
  voInkSegment (VO_MSE_CALL *getSegment)(voEngine engine, voInkTagIterator iterator);

  /**
   * Get the data of the tag associated with this iterator.
   *
   * @param engine Reference an `Engine` instance.
   * @param iterator Reference to the target `EngineObject` instance.
   *
   * @return the `voEngineObject` on success, otherwise `VO_INVALID_REFERENCE`.
   *
   * @throws VO_INVALID_OPERATION if `iterator` is not a
   *   `voInkTagIterator`.
   * @throws VO_NO_SUCH_ELEMENT if `iterator` is positioned at the
   *   end of the iteration.
   */
  voEngineObject (VO_MSE_CALL *getData)(voEngine engine, voInkTagIterator iterator);

  /**
   * Associates an `EngineObject` to the tag associated with this iterator.
   * The former data is released.
   *
   * @param engine Reference an `Engine` instance.
   * @param iterator Reference to the target `EngineObject` instance.
   * @param data Reference to the data `EngineObject` instance.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_INVALID_OPERATION if `iterator` is not a
   *   `voInkTagIterator`.
   * @throws VO_NO_SUCH_ELEMENT if `iterator` is positioned at the
   *   end of the iteration.
   */
  bool (VO_MSE_CALL *setData)(voEngine engine, voInkTagIterator iterator, voEngineObject data);
}
voIInkTagIterator;

#endif // end of: #ifndef C_MYSCRIPTINK_H
