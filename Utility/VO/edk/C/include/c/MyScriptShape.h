#ifndef C_MYSCRIPTSHAPE_H
#define C_MYSCRIPTSHAPE_H 0x06010000
/**
 * @file c/MyScriptShape.h
 * Native interface to the MyScript Shape service.
 */

#include "MyScriptEngine.h"

// -- error codes --------------------------------------------------------------

/**
 * Lists the MyScript Shape errors.
 */
enum VO_SHAPE_ERR
{
  /**
   * Unable to complete the requested operation because a
   * `ShapeKnowledge` is missing.
   *
   * @see voShapeKnowledge.
   * @see voIAttachTarget.
   */
  VO_MISSING_SHAPE_KNOWLEDGE = VO_INVALID_STATE | (4 << 16),
  /**
   * The `endSegment` call does not match any prior
   * `startSegment` call.
   */
  VO_UNMATCHED_SHAPE_SEGMENT
};


// -- types and interfaces -----------------------------------------------------

/**
 * Lists the MyScript Shape types.
 */
enum VO_SHAPE_T
{
  /**
   * `ShapeModel` type.
   *
   * @see voShapeModel.
   */
  VO_ShapeModel = 4000,
  /**
   * `ShapeKnowledge` type.
   *
   * @see voShapeKnowledge.
   */
  VO_ShapeKnowledge,

  /**
   * `ShapeRecognizer` type.
   *
   * @see voShapeRecognizer.
   */
  VO_ShapeRecognizer,
  /**
   * `ShapeBeautifier` type.
   *
   * @see voShapeBeautifier.
   */
  VO_ShapeBeautifier,

  /**
   * `ShapeDocument` type.
   *
   * @see voShapeDocument.
   */
  VO_ShapeDocument,

  /**
   * `ShapePrimitive` type.
   *
   * @see voShapePrimitive.
   */
  VO_ShapePrimitive,
  /**
   * `ShapeLine` type.
   *
   * @see voShapeLine.
   */
  VO_ShapeLine,
  /**
   * `ShapeDecoratedLine` type.
   *
   * @see voShapeDecoratedLine.
   */
  VO_ShapeDecoratedLine,
  /**
   * `ShapeEllipticArc` type.
   *
   * @see voShapeEllipticArc.
   */
  VO_ShapeEllipticArc,
  /**
   * `ShapeDecoratedEllipticArc` type.
   *
   * @see voShapeDecoratedEllipticArc.
   */
  VO_ShapeDecoratedEllipticArc,

  /**
   * `ShapeSegment` type.
   *
   * @see voShapeSegment.
   */
  VO_ShapeSegment,

  /**
   * `ShapeCandidate` type.
   *
   * @see voShapeCandidate.
   */
  VO_ShapeCandidate,
  /**
   * `ShapeRecognized` type.
   *
   * @see voShapeRecognized.
   */
  VO_ShapeRecognized,
  /**
   * `ShapeScratchOut` type.
   *
   * @see voShapeScratchOut.
   */
  VO_ShapeScratchOut,
  /**
   * `ShapeErased` type.
   *
   * @see voShapeErased.
   */
  VO_ShapeErased,
  /**
   * `ShapeRejected` type.
   *
   * @see voShapeRejected.
   */
  VO_ShapeRejected,

  /**
   * `ShapeHistoryManager` type.
   *
   * @see voShapeHistoryManager.
   */
  VO_ShapeHistoryManager = 4029
};

/**
 * Lists the MyScript Shape interfaces.
 */
enum VO_SHAPE_I
{
  /**
   * `IShapeModel` interface type.
   *
   * @see voIShapeModel.
   */
  VO_IShapeModel = 4100,
  /**
   * `IShapeKnowledge` interface type.
   *
   * @see voIShapeKnowledge.
   */
  VO_IShapeKnowledge,

  /**
   * `IShapeRecognizer` interface type.
   *
   * @see voIShapeRecognizer.
   */
  VO_IShapeRecognizer,

  /**
   * `IShapeDocument` interface type.
   *
   * @see voIShapeDocument.
   */
  VO_IShapeDocument,

  /**
   * `IShapeLine` interface type.
   *
   * @see voIShapeLine.
   */
  VO_IShapeLine,
  /**
   * `IShapeDecoratedLine` interface type.
   *
   * @see voIShapeDecoratedLine.
   */
  VO_IShapeDecoratedLine,
  /**
   * `IShapeEllipticArc` interface type.
   *
   * @see voIShapeEllipticArc.
   */
  VO_IShapeEllipticArc,
  /**
   * `IShapeDecoratedEllipticArc` interface type.
   *
   * @see voIShapeDecorateEllipticArc.
   */
  VO_IShapeDecoratedEllipticArc,

  /**
   * `IShapeSegment` interface type.
   *
   * @see voIShapeSegment.
   */
  VO_IShapeSegment,

  /**
   * `IShapeRecognized` interface type.
   *
   * @see voIShapeRecognized.
   */
  VO_IShapeRecognized,

  /**
   * `IShapeScratchOut` interface type.
   *
   * @see voIShapeScratchOut.
   */
  VO_IShapeScratchOut,

  /**
   * `IShapeDocumentProcessor` interface type.
   *
   * @see voIShapeDocumentProcessor.
   */
  VO_IShapeDocumentProcessor,

  /**
   * `IShapeHistoryManager` interface type.
   *
   * @see voIShapeHistoryManager.
   */
  VO_IShapeHistoryManager
};


// -- ShapeModel ---------------------------------------------------------------

/**
 * Reference to an instance of the `ShapeModel` type.
 *
 * {@implements voIShapeModel}
 */
typedef voEngineObject voShapeModel;

/**
 * Functions composing the `IShapeModel` interface. This interface
 * exposes the public methods of the `ShapeModel` type.
 *
 * {@implementingTypes voShapeModel}
 * @see VO_IShapeModel, VO_ShapeModel.
 */
typedef struct _voIShapeModel
{
  /**
   * Returns the label of this `ShapeModel`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeModel` instance.
   * @param charset Reference to the `Charset` instance to be used
   *   to encode the returned label.
   * @param string Recipient for the label.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeModel` instance.
   * @throws VO_NO_SUCH_OBJECT The `charset` reference is invalid.
   * @throws VO_INVALID_OBJECT The `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER The `string` recipient is not
   *   readable or writable.
   * @throws VO_INVALID_USER_BUFFER The `bytes` member of the
   *   `string` recipient is not writable.
   *
   * @note You can use the `VO_DEFAULT_CHARSET` property to provide
   *   the `Engine` with a default `Charset`. When done,
   *   you are allowed to pass `NULL` in place of a reference to a
   *   `Charset`.
   *
   * @see voEngine
   */
  bool (VO_MSE_CALL *getLabel)(voEngine engine, voShapeModel target, voCharset charset, voString* string);
}
voIShapeModel;


// -- ShapeKnowledge -----------------------------------------------------------

/**
 * Reference to an instance of the `ShapeKnowledge` type.
 *
 * {@implements voIShapeKnowledge}
 */
typedef voEngineObject voShapeKnowledge;

/**
 * Functions composing the `IShapeKnowledge` interface. This
 * interface exposes the public methods of the `ShapeKnowledge` type.
 *
 * {@implementingTypes voShapeKnowledge}
 * @see VO_IShapeKnowledge, VO_ShapeKnowledge.
 */
typedef struct _voIShapeKnowledge
{
  /**
   * Returns the number of models in this `ShapeKnowledge`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeKnowledge` instance.
   *
   * @return The number of models on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeKnowledge` instance.
   */
  uint32_t (VO_MSE_CALL *getModelCount)(voEngine engine, voShapeKnowledge target);

  /**
   * Returns the model at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeKnowledge` instance.
   * @param index The index of the model to be retrieved.
   *
   * @return A `ShapeModel` instance on success, otherwise
   *   `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeKnowledge` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_LIMIT_EXCEEDED The number of `ShapeModel` instances
   *   would exceed the allowed limit (please remember that the limit can be
   *   shared among several types).
   */
  voShapeModel (VO_MSE_CALL *getModelAt)(voEngine engine, voShapeKnowledge target, uint32_t index);
}
voIShapeKnowledge;


// -- ShapeRecognizer ----------------------------------------------------------

/**
 * Reference to an instance of the `ShapeRecognizer` type.
 *
 * {@implements voIAttachTarget, voIShapeDocumentProcessor}
 *
 * @note Please refer to `MyScriptEngine.h` reference documentation
 *   about the `IAttachTarget` interface.
 */
typedef voEngineObject voShapeRecognizer;

/**
 * {@propertySet ShapeRecognizer}
 */
enum VO_SHAPE_RECOGNIZER_PROP
{
  /**
   * A value between `0.0f` and `1.0f` that adjusts the
   * reject detection sensitivity.
   *
   * {@property float}
   *
   * @note A value equal to `0.0f` disables reject detection.
   */
  VO_SHAPE_RECOGNIZER_REJECT_DETECTION_SENSITIVITY = (VO_ShapeRecognizer << 16),

  /**
   * A value between `0.0f` and `1.0f` that adjusts the
   * scratch out detection sensitivity.
   *
   * {@property float}
   *
   * @note A value equal to `0.0f` disables scratch out detection.
   */
  VO_SHAPE_RECOGNIZER_SCRATCH_OUT_DETECTION_SENSITIVITY
};

/**
 * Functions composing the `IShapeRecognizer` interface. This
 * interface exposes the public methods of the `ShapeRecognizer`
 * type.
 *
 * {@implementingTypes voShapeRecognizer}
 * @see VO_IShapeRecognizer, VO_ShapeRecognizer.
 */
typedef struct _voIShapeRecognizer
{
  /**
   * Returns the number of models in the `ShapeKnowledge` attached to
   * this `ShapeRecognizer`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeRecognizer` instance.
   *
   * @return The number of models on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `voShapeRecognizer` instance.
   * @throws VO_MISSING_SHAPE_KNOWLEDGE The `ShapeRecognizer` has no
   *   attached `ShapeKnowledge`.
   */
  uint32_t (VO_MSE_CALL *getModelCount)(voEngine engine, voShapeRecognizer target);

  /**
   * Returns the model at the specified `index` in the
   * `ShapeKnowledge` attached to this `ShapeRecognizer`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeRecognizer` instance.
   * @param index The index of the model to be retrieved.
   *
   * @return A `ShapeModel` instance on success, otherwise
   *   `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeKnowledge` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_LIMIT_EXCEEDED The number of `ShapeModel` instances
   *   would exceed the allowed limit (please remember that the limit can be
   *   shared among several types).
   * @throws VO_MISSING_SHAPE_KNOWLEDGE The `ShapeRecognizer` has no
   *   attached `ShapeKnowledge`.
   */
  voShapeModel (VO_MSE_CALL *getModelAt)(voEngine engine, voShapeRecognizer target, uint32_t index);

  /**
   * Returns the detection sensitivity associated with the specified model.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeRecognizer` instance.
   * @param model Reference to a `ShapeModel` instance.
   *
   * @return The detection sensitivity for the specified model on success,
   *   otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeRecognizer` instance.
   * @throws VO_NO_SUCH_OBJECT The `model` reference is invalid.
   * @throws VO_INVALID_OBJECT The `model` reference is not a
   *   reference to a `ShapeModel` instance.
   * @throws VO_INVALID_ARGUMENT The `model` reference does not
   *   belong to the `ShapeKnowledge` that is attached to the
   *   `ShapeRecognizer`.
   * @throws VO_MISSING_SHAPE_KNOWLEDGE The `ShapeRecognizer` has no
   *   attached `ShapeKnowledge`.
   */
  float (VO_MSE_CALL *getModelDetectionSensitivity)(voEngine engine, voShapeRecognizer target, voShapeModel model);

  /**
   * Sets the detection sensitivity associated with the specified model.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeRecognizer` instance.
   * @param model Reference to a `ShapeModel` instance.
   * @param sensitivity The detection sensitivity value for the specified model.
   *
   * @return `true` on success, otherwise `false`.

   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeRecognizer` instance.
   * @throws VO_NO_SUCH_OBJECT The `model` reference is invalid.
   * @throws VO_INVALID_OBJECT The `model` reference is not a
   *   reference to a `ShapeModel` instance.
   * @throws VO_INVALID_ARGUMENT The `model` reference does not
   *   belong to the `ShapeKnowledge` that is attached to the
   *   `ShapeRecognizer`.
   * @throws VO_INVALID_ARGUMENT The `sensitivity` is not between
   *   `0.0f` and `1.0f`.
   * @throws VO_MISSING_SHAPE_KNOWLEDGE The `ShapeRecognizer` has no
   *   attached `ShapeKnowledge`.
   */
  bool (VO_MSE_CALL *setModelDetectionSensitivity)(voEngine engine, voShapeRecognizer target, voShapeModel model, float sensitivity);
}
voIShapeRecognizer;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `ShapeRecognizer` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `ShapeRecognizer` object
 *   on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `ShapeRecognizer`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared by several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voShapeRecognizer voCreateShapeRecognizer(voEngine engine)
{
  return voCreateObject(engine, VO_ShapeRecognizer);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- ShapeBeautifier ----------------------------------------------------------

/**
 * Reference to an instance of the `ShapeBeautifier` type.
 *
 * {@implements voIAttachTarget, voIShapeDocumentProcessor}
 *
 * @note Please refer to `MyScriptEngine.h` reference documentation
 * on the `IAttachTarget` interface.
 */
typedef voEngineObject voShapeBeautifier;

/**
 * {@propertySet ShapeBeautifier}
 */
enum VO_SHAPE_BEAUTIFIER_PROP
{
  /**
   * A value between `0.0f` and `1.0f` that adjusts the
   * beautification alignment strength of the beautifier.
   *
   * {@property float}
   *
   * @note A value equal to `0.0f` disables the alignment constraints
   * of the beautification process. A value close to `1.0f` increases
   * the likelihood of shapes being aligned with the vertical and horizontal
   * document axis.
   */
  VO_SHAPE_BEAUTIFIER_ALIGNMENT_STRENGTH = (VO_ShapeBeautifier << 16),

  /**
   * A value between `0.0f` and `1.0f` that adjusts the
   * beautification congruence strength of the beautifier.
   *
   * {@property float}
   *
   * @note A value equal to `0.0f` disables the congruence
   * constraints of the beautification process. A value close to
   * `1.0f` increases the likelihood of shapes being of the same size
   * and aligned with each other.
   */
  VO_SHAPE_BEAUTIFIER_CONGRUENCE_STRENGTH,

  /**
   * A value between `0.0f` and `1.0f` that adjusts the
   * beautification connection strength of the beautifier.
   *
   * {@property float}
   *
   * @note A value equal to `0.0f` disables the connection
   * constraints of the beautification process. A value close to
   * `1.0f` increases the likelihood of shapes being connected.
   */
  VO_SHAPE_BEAUTIFIER_CONNECTION_STRENGTH
};

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `ShapeBeautifier` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `ShapeBeautifier` object
 *   on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `ShapeBeautifier`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared by several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voShapeBeautifier voCreateShapeBeautifier(voEngine engine)
{
  return voCreateObject(engine, VO_ShapeBeautifier);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- ShapeDocument ------------------------------------------------------------

/**
 * Reference to an instance of the `ShapeDocument` type.
 *
 * {@implements voIShapeDocument}
 */
typedef voEngineObject voShapeDocument;

/**
 * Reference to an instance of the `ShapePrimitive` type.
 */
typedef voEngineObject voShapePrimitive;

/**
 * Reference to an instance of the `ShapeSegment` type.
 *
 * {@implements voIShapeSegment}
 */
typedef voEngineObject voShapeSegment;

/**
 * Functions composing the `IShapeDocument` interface. This interface
 * exposes the public methods of the `ShapeDocument` type.
 *
 * {@implementingTypes voShapeDocument}
 * @see VO_IShapeDocument, VO_ShapeDocument.
 */
typedef struct _voIShapeDocument
{
  /**
   * Clears this `ShapeDocument`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeDocument` instance.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeDocument` instance.
   */
  bool (VO_MSE_CALL *clear)(voEngine engine, voShapeDocument target);

  /**
   * Adds a digital pen stroke to this `ShapeDocument`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeDocument` instance.
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
   *   reference to a `ShapeDocument` instance.
   * @throws VO_INVALID_ARGUMENT When `xByteStride == 0`
   * @throws VO_INVALID_ARGUMENT When `yByteStride == 0`
   * @throws VO_INVALID_ARGUMENT When `pointCount == 0`
   * @throws VO_INVALID_USER_BUFFER The combination of `x`,
   *   `xByteStride`, `y`, `yByteStride` and
   *   `pointCount` leads to invalid memory access.
   * @throws VO_LIMIT_EXCEEDED When `pointCount > 32767`
   */
  bool (VO_MSE_CALL *addStroke)(voEngine engine, voShapeDocument target, const float* x, size_t xByteStride, const float* y, size_t yByteStride, uint32_t pointCount);

  /**
   * Adds a primitive to this `ShapeDocument` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeDocument` instance.
   * @param primitive Reference to a `ShapePrimitive` instance.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeDocument` instance.
   * @throws VO_NO_SUCH_OBJECT The `primitive` reference is invalid.
   * @throws VO_INVALID_OBJECT The `primitive` object is not an
   *   instance of the `ShapePrimitive` type.
   * @throws VO_INVALID_ARGUMENT The `primitive` object cannot be
   *   added.
   *
   * @see voShapePrimitive
   */
  bool (VO_MSE_CALL *addPrimitive)(voEngine engine, voShapeDocument target, voShapePrimitive const primitive);

  /**
   * Starts a new segment.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeDocument` instance.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeDocument` instance.
   */
  bool (VO_MSE_CALL *startSegment)(voEngine engine, voShapeDocument target);

  /**
   * Ends the current segment.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeDocument` instance.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeDocument` instance.
   * @throws VO_UNMATCHED_SHAPE_SEGMENT The `endSegment` call does
   *   not match any prior `startSegment` call.
   */
  bool (VO_MSE_CALL *endSegment)(voEngine engine, voShapeDocument target);

  /**
   * Returns the number of segments in this `ShapeDocument` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeDocument` instance.
   *
   * @return The number of segments on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeDocument` instance.
   */
  uint32_t (VO_MSE_CALL *getSegmentCount)(voEngine engine, voShapeDocument target);

  /**
   * Returns the segment at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeDocument` instance.
   * @param index The index of the segment to be retrieved.
   *
   * @return A `ShapeSegment` instance on success, otherwise
   *   `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeDocument` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_LIMIT_EXCEEDED The number of `ShapeSegment` instances
   *   would exceed the allowed limit. (please remember that the limit can be
   *   shared by several types).
   */
  voShapeSegment (VO_MSE_CALL *getSegmentAt)(voEngine engine, voShapeDocument target, uint32_t index);

  /**
   * Removes the segment at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeDocument` instance.
   * @param index The index of the segment to remove.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeDocument` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   */
  bool (VO_MSE_CALL *removeSegmentAt)(voEngine engine, voShapeDocument target, uint32_t index);

  /**
   * Inserts a segment at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeDocument` instance.
   * @param target Reference to a `ShapeSegment` instance.
   * @param index The position index where to insert the segment.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `segment` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeDocument` instance.
   * @throws VO_INVALID_OBJECT The `segment` object is not an
   *   instance of the `ShapeSegment` type.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_INVALID_STATE The `segment` already exists in the
   *   `ShapeDocument`.
   */
  bool (VO_MSE_CALL *insertSegmentAt)(voEngine engine, voShapeDocument target, voShapeSegment const segment, uint32_t index);

  /**
   * Returns the number of strokes in this `ShapeDocument` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeDocument` instance.
   *
   * @return the number of strokes on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeDocument` instance.
   */
  uint32_t (VO_MSE_CALL *getStrokeCount)(voEngine engine, voShapeDocument target);

  /**
   * Returns the points of the stroke at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeDocument` instance.
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
   *   reference to a `ShapeDocument` instance.
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
  bool (VO_MSE_CALL *getStrokeAt)(voEngine engine, voShapeDocument target, uint32_t index, float* x, size_t xByteStride, float* y, size_t yByteStride, uint32_t* pointCount);

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
   *
   * @since 5.0_0
   */
  bool (VO_MSE_CALL *setCoordinateResolution)(voEngine engine, voEngineObject target, float resolution);
}
voIShapeDocument;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `ShapeDocument` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `ShapeDocument` object on
 *   success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `ShapeDocument` instances
 *   would exceed the allowed limit. (please remember that the limit can be
 *   shared by several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voShapeDocument voCreateShapeDocument(voEngine engine)
{
  return voCreateObject(engine, VO_ShapeDocument);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- ShapeLine ----------------------------------------------------------------

/**
 * Reference to an instance of the `ShapeLine` type.
 *
 * {@extends voShapePrimitive}
 * {@implements voIShapeLine}
 */
typedef voShapePrimitive voShapeLine;

/**
 * The `ShapePointData` type models the location of a point in the 2D
 * space.
 */
typedef struct _voShapePointData
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
voShapePointData;

/**
 * The `ShapeLineData` type models the data of a line segment in the
 * 2D space.
 *
 * @see voShapeLine
 */
typedef struct _voShapeLineData
{
  /**
   * First point composing the line segment.
   */
  voShapePointData p1;

  /**
   * Second point composing the line segment.
   */
  voShapePointData p2;
}
voShapeLineData;

/**
 * Functions composing the `IShapeLine` interface. This interface
 * exposes the public methods of the `ShapeLine` type.
 *
 * {@implementingTypes voShapeLine}
 * @see VO_IShapeLine, VO_ShapeLine.
 */
typedef struct _voIShapeLine
{
  /**
   * Returns both points of the line segment.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeLine` instance.
   * @param data Recipient for the data.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeLine` instance.
   * @throws VO_INVALID_USER_BUFFER The `data` recipient is not
   *   writable.
   */
  bool (VO_MSE_CALL *getData)(voEngine engine, voShapeLine target, voShapeLineData* data);

  /**
   * Sets both points of the line segment.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeLine` instance.
   * @param data Recipient for the data.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeLine` instance.
   * @throws VO_INVALID_USER_BUFFER The `data` recipient is not
   *   readable.
   */
  bool (VO_MSE_CALL *setData)(voEngine engine, voShapeLine target, const voShapeLineData* data);
}
voIShapeLine;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `ShapeLine` type.
 *
 * @param engine Reference to an `Engine` instance.
 * @param data the geometric parameters of shape to create.
 *
 * @return A reference to the newly created `ShapeLine` object
 *   on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `ShapeLine` instances
 *   would exceed the allowed limit (please remember that the limit can be
 *   shared by several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voShapeLine voCreateShapeLine(voEngine engine, const voShapeLineData* data)
{
  return voCreateObjectEx(engine, VO_ShapeLine, data, sizeof(*data));
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- ShapeDecoratedLine -------------------------------------------------------

/**
 * Lists the decoration types.
 */
enum VO_SHAPE_DECORATION_TYPE
{
  /**
   * No decoration.
   */
  VO_SHAPE_DECORATION_NONE,

  /**
   * Arrow head.
   */
  VO_SHAPE_DECORATION_ARROW_HEAD
};

/**
 * Reference to an instance of the `ShapeDecoratedLine` type.
 *
 * {@extends voShapePrimitive}
 * {@implements voIShapeDecoratedLine}
 */
typedef voShapePrimitive voShapeDecoratedLine;

/**
 * The `ShapeDecoratedLineData` type models the data of a decorated
 * line in the 2D space.
 */
typedef struct _voShapeDecoratedLineData
{
  /**
   * Line data.
   */
  voShapeLineData line;

  /**
   * Decoration associated with the first point of the line.
   */
  voId p1Decoration;

  /**
   * Decoration associated with the second point of the line.
   */
  voId p2Decoration;
}
voShapeDecoratedLineData;

/**
 * Functions composing the `IShapeDecoratedLine` interface. This
 * interface exposes the public methods of the `ShapeDecoratedLine`
 * type.
 *
 * {@implementingTypes voShapeDecoratedLine}
 * @see VO_IShapeDecoratedLine, VO_ShapeDecoratedLine.
 */
typedef struct _voIShapeDecoratedLine
{
  /**
   * Returns the decorated line data.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeDecoratedLine` instance.
   * @param data Recipient for the data.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeDecoratedLine` instance.
   * @throws VO_INVALID_USER_BUFFER The `data` recipient is not
   *   writable.
   */
  bool (VO_MSE_CALL *getData)(voEngine engine, voShapeDecoratedLine target, voShapeDecoratedLineData* data);

  /**
   * Sets the decorated line data.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeDecoratedLine` instance.
   * @param data Recipient for the data.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeDecoratedLine` instance.
   * @throws VO_INVALID_USER_BUFFER The `data` recipient is not
   *   readable.
   */
  bool (VO_MSE_CALL *setData)(voEngine engine, voShapeDecoratedLine target, const voShapeDecoratedLineData* data);

  /**
   * Computes the tangent angle at point p1 of the line.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeDecoratedLine`
   *   instance.
   * @param angle Recipient for the tangent angle.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeDecoratedLine` instance.
   */
  bool (VO_MSE_CALL *getP1TangentAngle)(voEngine engine, voShapeDecoratedLine target, float* angle);

  /**
   * Computes the tangent angle at point p2 of the line.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeDecoratedLine`
   *   instance.
   * @param angle Recipient for the tangent angle.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeDecoratedLine` instance.
   */
  bool (VO_MSE_CALL *getP2TangentAngle)(voEngine engine, voShapeDecoratedLine target, float* angle);
}
voIShapeDecoratedLine;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `ShapeDecoratedLine` type.
 *
 * @param engine Reference to an `Engine` instance.
 * @param data the geometric parameters of shape to create.
 *
 * @return A reference to the newly created `ShapeDecoratedLine`
 *   object on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `ShapeDecoratedLine`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared by several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voShapeDecoratedLine voCreateShapeDecoratedLine(voEngine engine, const voShapeDecoratedLineData* data)
{
  return voCreateObjectEx(engine, VO_ShapeDecoratedLine, data, sizeof(*data));
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- ShapeEllipticArc ---------------------------------------------------------

/**
 * Reference to an instance of the `ShapeEllipticArc` type.
 *
 * {@extends voShapePrimitive}
 * {@implements voIShapeEllipticArc}
 */
typedef voShapePrimitive voShapeEllipticArc;

/**
 * The `EllipticArcData` type models the data of an elliptic arc in
 * the 2D space.
 *
 * @see voShapeEllipticArc
 */
typedef struct _voShapeEllipticArcData
{
  /**
   * Center of ellipse.
   */
  voShapePointData center;

  /**
   * Ellipse minor radius.
   */
  float minRadius;

  /**
  * Ellipse major radius.
   */
  float maxRadius;

  /**
   * Orientation: angle of major axis of ellipse, in radians.
   */
  float orientation;

  /**
   * Starting angle of open arc, in radians.
   */
  float startAngle;

  /**
   * Sweep angle of open arc, measured clockwise, in radians.
   */
  float sweepAngle;
}
voShapeEllipticArcData;

/**
 * Functions composing the `IShapeEllipticArc` interface. This
 * interface exposes the public methods of the `ShapeEllipticArc`
 * type.
 *
 * {@implementingTypes voShapeEllipticArc}
 * @see VO_IShapeEllipticArc, VO_ShapeEllipticArc.
 */
typedef struct _voIShapeEllipticArc
{
  /**
   * Returns the elliptic arc data.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeEllipticArc` instance.
   * @param data Recipient for the data.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeEllipticArc` instance.
   * @throws VO_INVALID_USER_BUFFER The `data` recipient is not
   *   writable.
   */
  bool (VO_MSE_CALL *getData)(voEngine engine, voShapeEllipticArc target, voShapeEllipticArcData* data);

  /**
   * Sets the elliptic arc data.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeEllipticArc` instance.
   * @param data Recipient for the data.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeEllipticArc` instance.
   * @throws VO_INVALID_USER_BUFFER The `data` recipient is not
   *   readable.
   */
  bool (VO_MSE_CALL *setData)(voEngine engine, voShapeEllipticArc target, const voShapeEllipticArcData* data);
}
voIShapeEllipticArc;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `ShapeEllipticArc` type.
 *
 * @param engine Reference to an `Engine` instance.
 * @param data the geometric parameters of shape to create.
 *
 * @return A reference to the newly created `ShapeEllipticArc` object
 *   on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `ShapeEllipticArc`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared by several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voShapeEllipticArc voCreateShapeEllipticArc(voEngine engine, const voShapeEllipticArcData* data)
{
  return voCreateObjectEx(engine, VO_ShapeEllipticArc, data, sizeof(*data));
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- ShapeDecoratedEllipticArc ------------------------------------------------

/**
 * Reference to an instance of the `ShapeDecoratedEllipticArc` type.
 *
 * {@extends voShapePrimitive}
 * {@implements voIShapeDecoratedEllipticArc}
 */
typedef voShapePrimitive voShapeDecoratedEllipticArc;

/**
 * The `ShapeDecoratedEllipticArcData` type models the data of a
 * decorated elliptic arc in the 2D space.
 */
typedef struct _voShapeDecoratedEllipticArcData
{
  /**
   * Arc data.
   */
  voShapeEllipticArcData arc;

  /**
   * Decoration associated with the first end of the arc.
   */
  voId firstDecoration;

  /**
   * Decoration associated with the last end of the arc.
   */
  voId lastDecoration;
}
voShapeDecoratedEllipticArcData;

/**
 * Functions composing the `IShapeDecoratedEllipticArc` interface.
 * This interface exposes the public methods of the
 * `ShapeDecoratedEllipticArc` type.
 *
 * {@implementingTypes voShapeDecoratedEllipticArc}
 * @see VO_IShapeDecoratedEllipticArc, VO_ShapeDecoratedEllipticArc.
 */
typedef struct _voIShapeDecoratedEllipticArc
{
  /**
   * Returns the decorated arc data.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeDecoratedEllipticArc`
   *   instance.
   * @param data Recipient for the data.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeDecoratedEllipticArc` instance.
   * @throws VO_INVALID_USER_BUFFER The `data` recipient is not
   *   writable.
   */
  bool (VO_MSE_CALL *getData)(voEngine engine, voShapeDecoratedEllipticArc target, voShapeDecoratedEllipticArcData* data);

  /**
   * Sets the decorated arc data.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeDecoratedEllipticArc`
   *   instance.
   * @param data Recipient for the data.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeDecoratedEllipticArc` instance.
   * @throws VO_INVALID_USER_BUFFER The `data` recipient is not
   *   readable.
   */
  bool (VO_MSE_CALL *setData)(voEngine engine, voShapeDecoratedEllipticArc target, const voShapeDecoratedEllipticArcData* data);

  /**
   * Computes the tangent angles at the first end of the elliptic arc.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeDecoratedEllipticArc`
   *   instance.
   * @param angle Recipient for the tangent angle.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeDecoratedEllipticArc` instance.
   */
  bool (VO_MSE_CALL *getFirstTangentAngle)(voEngine engine, voShapeDecoratedEllipticArc target, float* angle);

  /**
   * Computes the tangent angles at the last end of the elliptic arc.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeDecoratedEllipticArc`
   *   instance.
   * @param angle Recipient for the tangent angle.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeDecoratedEllipticArc` instance.
   */
  bool (VO_MSE_CALL *getLastTangentAngle)(voEngine engine, voShapeDecoratedEllipticArc target, float* angle);
}
voIShapeDecoratedEllipticArc;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `ShapeDecoratedEllipticArc` type.
 *
 * @param engine Reference to an `Engine` instance.
 * @param data the geometric parameters of shape to create.
 *
 * @return A reference to the newly created
 *   `ShapeDecoratedEllipticArc` object on success, otherwise
 *   `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of
 *   `ShapeDecoratedEllipticArc` instances would exceed the allowed
 *   limit (please remember that the limit can be shared by several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voShapeDecoratedEllipticArc voCreateShapeDecoratedEllipticArc(voEngine engine, const voShapeDecoratedEllipticArcData* data)
{
  return voCreateObjectEx(engine, VO_ShapeDecoratedEllipticArc, data, sizeof(*data));
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- ShapeSegment -------------------------------------------------------------

/**
 * Reference to an instance of the `ShapeCandidate` type.
 */
typedef voEngineObject voShapeCandidate;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `ShapeCandidate` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `ShapeCandidate` object on
 *   success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `ShapeCandidate` instances
 *   would exceed the allowed limit. (please remember that the limit can be
 *   shared by several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voShapeCandidate voCreateShapeCandidate(voEngine engine)
{
  return voCreateObject(engine, VO_ShapeCandidate);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS

/**
 * The `ShapeInkRange` type models a range in the input.
 */
typedef struct _voShapeInkRange
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
voShapeInkRange;

/**
 * {@propertySet ShapeSegment}
 */
enum VO_SHAPE_SEGMENT_PROP
{
  /**
   * Freezes the recognition process for this `ShapeSegment`.
   *
   * {@property bool}
   */
  VO_SHAPE_SEGMENT_FREEZE_RECOGNITION = (VO_ShapeSegment << 16),

  /**
   * Freezes the beautification process for this `ShapeSegment`.
   *
   * {@property bool}
   */
  VO_SHAPE_SEGMENT_FREEZE_BEAUTIFICATION
};

/**
 * Functions composing the `IShapeSegment` interface. This interface
 * exposes the public methods of the `ShapeSegment` type.
 *
 * {@implementingTypes voShapeSegment}
 * @see VO_IShapeSegment, VO_ShapeSegment.
 */
typedef struct _voIShapeSegment
{
  /**
   * Returns the number of ink ranges this segment covers.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeSegment` instance.
   *
   * @return The number of ink ranges this segment covers on success, otherwise
   * `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeSegment` instance.
   * @throws VO_INVALID_STATE The portion of a MyScript Document associated with
   *   this segment has been modified, so the associated input ranges are not 
   *   valid anymore.
   */
  uint32_t (VO_MSE_CALL *getInkRangeCount)(voEngine engine, voShapeSegment target);

  /**
   * Returns the ink range at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeSegment` instance.
   * @param index The zero-based index of the ink range to be retrieved.
   * @param inkRange Recipient for the ink range result.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeSegment` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_INVALID_USER_BUFFER The `range` recipient is not
   *   writable.
   * @throws VO_INVALID_STATE The portion of a MyScript Document associated with
   *   this segment has been modified, so the associated input ranges are not 
   *   valid anymore.
   */
  bool (VO_MSE_CALL *getInkRangeAt)(voEngine engine, voShapeSegment target, uint32_t index, voShapeInkRange* range);

  /**
   * Returns the number of candidates this segment contains.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeSegment` instance.
   *
   * @return The number of candidates this segment contains on success,
   *   otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeSegment` instance.
   */
  uint32_t (VO_MSE_CALL *getCandidateCount)(voEngine engine, voShapeSegment target);

  /**
   * Returns the candidate at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeSegment` instance.
   * @param index The zero-based index of the candidate to be retrieved.
   *
   * @return A `ShapeCandidate` instance on success, otherwise
   *   `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeSegment` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_LIMIT_EXCEEDED The number of `ShapeCandidate`
   *   instances would exceed the allowed limit (please remember that the limit
   *   can be shared by several types).
   */
  voShapeCandidate (VO_MSE_CALL *getCandidateAt)(voEngine engine, voShapeSegment target, uint32_t index);

  /**
   * Returns the index of the selected candidate in this
   * `ShapeSegment`'s candidate list.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeSegment` instance.
   *
   * @return The position of the selected candidate on success, otherwise
   *   `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeSegment` instance.
   * @throws VO_INVALID_STATE The object is not in a state where the selected
   *   candidate is available.
   */
  uint32_t (VO_MSE_CALL *getSelectedCandidateIndex)(voEngine engine, voShapeSegment target);

  /**
   * Selects the candidate at the specified `index` position in this
   * `ShapeSegment`'s candidate list.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeSegment` instance.
   * @param index The zero-based index of the candidate to be selected.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeSegment` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_INVALID_STATE The object is not in a state where the selected
   *   candidate can be set.
   */
  bool (VO_MSE_CALL *selectCandidateAt)(voEngine engine, voShapeSegment target, uint32_t index);
}
voIShapeSegment;


// -- ShapeRecognized ----------------------------------------------------------

/**
 * Reference to an instance of the `ShapeRecognized` type.
 *
 * {@extends voShapeCandidate}
 * {@implements voIShapeRecognized}
 */
typedef voShapeCandidate voShapeRecognized;

/**
 * Functions composing the `IShapeRecognized` interface. This
 * interface exposes the public methods of the `ShapeRecognized`
 * type.
 *
 * {@implementingTypes voShapeRecognized}
 * @see VO_IShapeRecognized, VO_ShapeRecognized.
 */
typedef struct _voIShapeRecognized
{
  /**
   * Returns the `ShapeModel` model associated with this
   * `ShapeRecognized` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeRecognized` instance.
   *
   * @return A `ShapeModel` instance on success, otherwise
   *   `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeRecognized` instance.
   * @throws VO_LIMIT_EXCEEDED The number of `ShapeModel` instances
   *   would exceed the allowed limit (please remember that the limit can be
   *   shared by several types).
   */
  voShapeModel (VO_MSE_CALL *getModel)(voEngine engine, voShapeRecognized target);

  /**
   * Returns the resemblance score of this `ShapeRecognized`
   * instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeRecognized` instance.
   *
   * @return The resemblance score of this `ShapeRecognized` instance
   *   on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeRecognized` instance.
   */
  float (VO_MSE_CALL *getResemblanceScore)(voEngine engine, voShapeRecognized target);

  /**
   * Returns the normalized recognition score of this
   * `ShapeRecognized` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeRecognized` instance.
   *
   * @return The normalized recognition score of this
   *   `ShapeRecognized` instance on success, otherwise
   *   `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeRecognized` instance.
   */
  float (VO_MSE_CALL *getNormalizedRecognitionScore)(voEngine engine, voShapeRecognized target);

  /**
   * Returns the number of primitives this `ShapeRecognized` instance
   * is made of.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeRecognized` instance.
   *
   * @return The number of primitives on success, otherwise
   *   `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeRecognized` instance.
   */
  uint32_t (VO_MSE_CALL *getPrimitiveCount)(voEngine engine, voShapeRecognized target);

  /**
   * Returns the primitive at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeRecognized` instance.
   * @param index The zero-based index of the primitive to be retrieved.
   *
   * @return A `ShapePrimitive` instance on success, otherwise
   *   `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeRecognized` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_LIMIT_EXCEEDED The number of `ShapePrimitive`
   *   instances would exceed the allowed limit (please remember that the limit
   *   can be shared by several types).
   */
  voShapePrimitive (VO_MSE_CALL *getPrimitiveAt)(voEngine engine, voShapeRecognized target, uint32_t index);
}
voIShapeRecognized;


// -- ShapeScratchOut ----------------------------------------------------------

/**
 * Reference to an instance of the `ShapeScratchOut` type.
 *
 * {@extends voShapeCandidate}
 * {@implements voIShapeScratchOut}
 */
typedef voShapeCandidate voShapeScratchOut;

/**
 * Functions composing the `IShapeScratchOut` interface. This
 * interface exposes the public methods of the `ShapeScratchOut`
 * type.
 *
 * {@implementingTypes voShapeScratchOut}
 * @see VO_IShapeScratchOut, VO_ShapeScratchOut.
 */
typedef struct _voIShapeScratchOut
{
  /**
   * Returns the number of erased ink ranges corresponding to the ink erased by
   * this `ShapeScratchOut` candidate.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeSegment` instance.
   *
   * @return The number of ink ranges corresponding to the erased ink on
   *   success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeSegment` instance.
   * @throws VO_INVALID_STATE The portion of a MyScript Document associated with
   *   this candidate has been modified, so the associated ink ranges are not
   *   valid anymore.
   */
  uint32_t (VO_MSE_CALL *getErasedInkRangeCount)(voEngine engine, voShapeScratchOut target);

  /**
   * Returns the erased ink range at the specified `index`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeSegment` instance.
   * @param index The zero-based index of the ink range to be retrieved.
   * @param inkRange Recipient for the ink range result.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeSegment` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS The `index` is out of bounds.
   * @throws VO_INVALID_USER_BUFFER The `range` recipient is not
   *   writable.
   * @throws VO_INVALID_STATE The portion of a MyScript Document associated with
   *   this candidate has been modified, so the associated ink ranges are not
   *   valid anymore.
   */
  bool (VO_MSE_CALL *getErasedInkRangeAt)(voEngine engine, voShapeScratchOut target, uint32_t index, voShapeInkRange* range);
}
voIShapeScratchOut;


// -- ShapeErased --------------------------------------------------------------

/**
 * Reference to an instance of the `ShapeErased` type.
 *
 * {@extends voShapeCandidate}
 */
typedef voShapeCandidate voShapeErased;


// -- ShapeRejected ------------------------------------------------------------

/**
 * Reference to an instance of the `ShapeRejected` type.
 *
 * {@extends voShapeCandidate}
 */
typedef voShapeCandidate voShapeRejected;


// -- IShapeDocumentProcessor --------------------------------------------------

/**
 * Functions composing the `IShapeDocumentProcessor` interface.
 *
 * {@implementingTypes voShapeRecognizer, voShapeBeautifier}
 * @see VO_IShapeDocumentProcessor, VO_ShapeRecognizer, VO_ShapeBeautifier.
 */
typedef struct _voIShapeDocumentProcessor
{
  /**
   * Processes a `ShapeDocument` instance.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to the target `EngineObject` instance.
   * @param shapeDocument Reference to a `ShapeDocument` instance.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` object does not
   *   implement this interface.
   * @throws VO_NO_SUCH_OBJECT The `shapeDocument` reference is
   *   invalid.
   * @throws VO_INVALID_OBJECT The `shapeDocument` object is not an
   *   instance of the `ShapeDocument` type.
   * @throws VO_INVALID_CALLBACK The notification callback crashed.
   * @throws VO_INVALID_STATE The `target` object is not in a state
   *   where the `process` function can be invoked.
   * @throws VO_MISSING_SHAPE_KNOWLEDGE The `target` object is an
   *   instance of the `ShapeRecognizer` or
   *   `ShapeBeautifier` type that has no attached
   *   `ShapeKnowledge`.
   * @throws VO_CANCELED The operation has been canceled.
   *
   * @see voShapeDocument
   */
  bool (VO_MSE_CALL *process)(voEngine engine, voEngineObject target, voShapeDocument shapeDocument, voNotifyProgressFunc notifyProgressFunc, void* userParam);
}
voIShapeDocumentProcessor;


// -- ShapeHistoryManager ------------------------------------------------------

/**
 * Reference to an instance of the `ShapeHistoryManager` type.
 *
 * {@implements voIShapeHistoryManager}
 */
typedef voEngineObject voShapeHistoryManager;

/**
 * {@propertySet ShapeHistoryManager}
 */
enum VO_SHAPE_HISTORY_MANAGER_PROP
{
  /**
   * A value that adjusts the depth of the undo stack.
   *
   * {@property uint32_t}
   *
   * @note A value equal to `0` removes any limit.
   */
  VO_SHAPE_HISTORY_MANAGER_UNDO_STACK_DEPTH = (VO_ShapeHistoryManager << 16),
};

typedef struct _voIShapeHistoryManager
{
  /**
   * Tells whether you can undo the last stroke on the associated
   *   `ShapeDocument`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeHistoryManager` instance.
   *
   * @return `VO_YES` or `VO_NO` on success, otherwise
   *   `VO_ERR` on failure.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeHistoryManager` instance.
   * @throws VO_INVALID_STATE The `ShapeHistoryManager` is not
   *   attached to a `ShapeDocument` instance.
   */
  voYesNo (VO_MSE_CALL *canUndo)(voEngine engine, voShapeHistoryManager target);

  /**
   * Tells whether you can redo the last stroke on the associated
   *   `ShapeDocument`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeHistoryManager` instance.
   *
   * @return `VO_YES` or `VO_NO` on success, otherwise
   *   `VO_ERR` on failure.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeHistoryManager` instance.
   * @throws VO_INVALID_STATE The `ShapeHistoryManager` is not
   *   attached to a `ShapeDocument` instance.
   */
  voYesNo (VO_MSE_CALL *canRedo)(voEngine engine, voShapeHistoryManager target);

  /**
   * Undo the last stroke and re-process the associated
   *   `ShapeDocument`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeHistoryManager` instance.
   * @param recognizer Reference to a `ShapeRecognizer` instance.
   * @param beautifier Reference to a `ShapeBeautifier` instance
   *   or `NULL` when no beautification processing is required.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `recognizer` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `beautifier` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeHistoryManager` instance.
   * @throws VO_INVALID_OPERATION The `recognizer` reference is not a
   *   reference to a `ShapeRecognizer` instance.
   * @throws VO_INVALID_OPERATION The `beautifier` reference is not a
   *   reference to a `ShapeBeautifier` instance.
   * @throws VO_INVALID_STATE The `ShapeHistoryManager` isn't
   *   attached to a `ShapeDocument` instance.
   * @throws VO_INVALID_STATE The undo operation is not possible on the
   *   associated `ShapeDocument` instance.
   */
  bool (VO_MSE_CALL *undoLastStroke)(voEngine engine, voShapeHistoryManager target, voShapeRecognizer recognizer, voShapeBeautifier beautifier);

  /**
   * Redo the last stroke and re-process the associated
   *   `ShapeDocument`.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `ShapeHistoryManager` instance.
   * @param recognizer Reference to a `ShapeRecognizer` instance.
   * @param beautifier Reference to a `ShapeBeautifier` instance
   *   or `NULL` when no beautification processing is required.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `target` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `recognizer` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT The `beautifier` reference is invalid.
   * @throws VO_INVALID_OPERATION The `target` reference is not a
   *   reference to a `ShapeHistoryManager` instance.
   * @throws VO_INVALID_OPERATION The `recognizer` reference is not a
   *   reference to a `ShapeRecognizer` instance.
   * @throws VO_INVALID_OPERATION The `beautifier` reference is not a
   *   reference to a `ShapeBeautifier` instance.
   * @throws VO_INVALID_STATE The `ShapeHistoryManager` isn't
   *   attached to a `ShapeDocument` instance.
   * @throws VO_INVALID_STATE The undo operation is not possible on the
   *   associated `ShapeDocument` instance.
   */
  bool (VO_MSE_CALL *redoLastStroke)(voEngine engine, voShapeHistoryManager target, voShapeRecognizer recognizer, voShapeBeautifier beautifier);
}
voIShapeHistoryManager;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `ShapeHistoryManager` type.
 *
 * @param engine Reference to an `Engine` instance.
 *
 * @return A reference to the newly created `ShapeHistoryManager`
 *   object on success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE The `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED The number of `ShapeHistoryManager`
 *   instances would exceed the allowed limit. (please remember that the limit
 *   can be shared by several types).
 * @throws VO_OUT_OF_MEMORY Not enough memory to create the object.
 */
VO_INLINE voShapeHistoryManager voCreateShapeHistoryManager(voEngine engine)
{
  return voCreateObject(engine, VO_ShapeHistoryManager);
}
#endif // end of: #ifndef VO_NO_FUNCTIONS

#endif // end of: #ifndef C_MYSCRIPTSHAPE_H
