#ifndef C_MYSCRIPTDOCUMENT_H
#define C_MYSCRIPTDOCUMENT_H 0x06010000

#include "MyScriptEngine.h"
#include "MyScriptJSON.h"
#include "MyScriptInk.h"
#include "MyScriptInkSearch.h"


// -- types and interfaces -----------------------------------------------------

/**
 * Lists the MyScript Document types.
 */
enum VO_DOCUMENT_T
{
  /**
   * Identifier of the `Document` type.
   * @see voDocument
   */
  VO_Document = 3200,

  /**
   * Identifier of the `Page` type.
   * @see voPage
   */
  VO_Page,

  /**
   * Identifier of the `PageSelection` type.
   * @see voPageSelection
   */
  VO_PageSelection,

  /**
   * Identifier of the `Content` type.
   * @see voContent
   */
  VO_Content,

  /**
   * Identifier of the `ContentField` type.
   * @see voContentField
   */
  VO_ContentField,

  /**
   * Identifier of the `Layout` type.
   * @see voLayout
   */
  VO_Layout,

  /**
   * Identifier of the `LayerIterator` type.
   * @see voLayerIterator
   */
  VO_LayerIterator,

  /**
   * Identifier of the `PenIterator` type.
   * @see voPenIterator
   */
  VO_PenIterator,

  /**
   * Identifier of the `LayoutItemIterator` type.
   * @see voLayoutItemIterator
   */
  VO_LayoutItemIterator,

  /**
   * `voDocumentFinder` type.
   * @see voDocumentFinder
   */
  VO_DocumentFinder,

  /**
   * `voDocumentFindResult` type.
   * @see voDocumentFindResult
   */
  VO_DocumentFindResult,

  /**
   * `voDocumentFindOccurrenceIterator` type.
   * @see voDocumentFindOccurrenceIterator
   */
  VO_DocumentFindOccurrenceIterator,

  /**
   * Identifier of the `ObjectIterator` type.
   * @see voObjectIterator
   */
  VO_ObjectIterator
};


/**
 * Lists the MyScript Document interfaces.
 */
enum VO_DOCUMENT_I
{
  /**
   * Identifier of the `IDocument` interface.
   * @see voIDocument
   */
  VO_IDocument = 3220,

  /**
   * Identifier of the `IPage` interface.
   * @see voIPage
   */
  VO_IPage,

  /**
   * Identifier of the `IPageSelection` interface.
   * @see voIPageSelection
   */
  VO_IPageSelection,

  /**
   * Identifier of the `IContent` interface.
   * @see voIContent
   */
  VO_IContent,

  /**
   * Identifier of the `IContentField` interface.
   * @see voIContentField
   */
  VO_IContentField,

  /**
   * Identifier of the `ILayout` interface.
   * @see voILayout
   */
  VO_ILayout,

  /**
   * Identifier of the `ILayerIterator` interface.
   * @see voILayerIterator
   */
  VO_ILayerIterator,

  /**
   * Identifier of the `IPenIterator` interface.
   * @see voIPenIterator
   */
  VO_IPenIterator,

  /**
   * Identifier of the `ILayoutItemIterator` interface.
   * @see voILayoutItemIterator
   */
  VO_ILayoutItemIterator,

  /**
   * Identifier of the `IPageUpdateListener` interface.
   * @see voIPageUpdateListener
   */
  VO_IPageUpdateListener,

  /**
   * Identifier of the `IContentFieldProcessor` interface.
   * @see voIContentFieldProcessor
   */
  VO_IContentFieldProcessor,

  /**
   * `voIDocumentFinder` interface type.
   * @see voIDocumentFinder
   */
  VO_IDocumentFinder,

  /**
   * `voIDocumentFindResult` interface type.
   * @see voIDocumentFindResult
   */
  VO_IDocumentFindResult,

  /**
   * `voIDocumentFindOccurrenceIterator` interface type.
   * @see voIDocumentFindOccurrenceIterator
   */
  VO_IDocumentFindOccurrenceIterator,

  /**
   * Identifier of the `IObjectIterator` interface.
   * @see voIObjectIterator
   */
  VO_IObjectIterator,

  /**
   * Identifier of the `IExtentProvider` interface.
   * @see voIExtentProvider
   */
  VO_IExtentProvider,
};


// -- Main Object Types --------------------------------------------------------

/**
 * Reference to an instance of the `Document` type.
 *
 * {@extends voEngineObject}
 * {@implements voIDocument}
 */
typedef voEngineObject voDocument;

/**
 * Reference to an instance of the `Page` type.
 *
 * {@extends voEngineObject}
 * {@implements voIPage}
 */
typedef voEngineObject voPage;

/**
 * Reference to an instance of the `Content` type.
 *
 * {@extends voEngineObject}
 * {@implements voIContent}
 */
typedef voEngineObject voContent;

/**
 * Reference to an instance of the `Layout` type.
 *
 * {@extends voEngineObject}
 * {@implements voILayout, voIExtentProvider}
 */
typedef voEngineObject voLayout;


// -- Object Iterator ----------------------------------------------------------

/**
 * Reference to an instance of the `ObjectIterator` type.
 *
 * {@extends voEngineObject}
 * {@implements voIObjectIterator}
 */
typedef voEngineObject voObjectIterator;

/**
 * Functions composing the `IObjectIterator` interface. This interface exposes 
 * the public methods of the `ObjectIterator` type.
 *
 * {@extends voIIterator}
 * {@implementingTypes voObjectIterator}
 * @see VO_IObjectIterator, VO_ObjectIterator.
 */
typedef struct _voIObjectIterator
{
  /** {@inheritDoc} */
  voYesNo (VO_MSE_CALL *isAtEnd)(voEngine engine, voIterator target);
  /** {@inheritDoc} */
  bool (VO_MSE_CALL *next)(voEngine engine, voIterator target);

  /**
   * Returns the url of the object at the current step of the iteration.
   *
   * @param engine the engine.
   * @param target the target iterator.
   * @param charset the charset to be used to encode the value.
   * @param url a recipient for the value.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `ObjectIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT the `target` refrence is positioned at the end
   *   of the iteration.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL` and no default
   *   charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a reference to a
   *   `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `url` recipient is not readable or
   *   writable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the `url` recipient is
   *   not writable.
   */
  bool (VO_MSE_CALL *getUrl)(voEngine engine, voObjectIterator target, voCharset charset, voString* url);
}
voIObjectIterator;


// -- Asynchronous Command Handler ---------------------------------------------

/**
 * Lists asynchronous commands of `voDocument` and
 * `voPage`.
 * @see voDocumentAsyncCommandCompletionCallback.
 */
typedef enum _voDocumentAsyncCommand
{
  /**
   * Indicates completion of `voDocument.save()` or
   * `voPage.save()`.
   */
  VO_CMD_SAVE,

  /**
   * Indicates completion of `voDocument.saveAs()`.
   */
  VO_CMD_SAVE_AS,

  /**
   * Indicates completion of `voPage.saveToTemp()`.
   */
  VO_CMD_SAVE_TO_TEMP,

  /**
   * Indicates completion of `voDocument.discardChanges()` or
   * `voPage.discardChanges()`.
   */
  VO_CMD_DISCARD_CHANGES,

  /**
   * Indicates completion of `voDocument.getMetadata()` or
   * `voPage.getMetadata()`.
   */
  VO_CMD_GET_METADATA,

  /**
   * Indicates completion of `voDocument.setMetadata()` or
   * `voPage.setMetadata()`.
   */
  VO_CMD_SET_METADATA,

  /**
   * Indicates completion of `voPage.getInk()`.
   */
  VO_CMD_GET_INK,

  /**
   * Indicates completion of `voPage.getLayout()`.
   */
  VO_CMD_GET_LAYOUT,

  /**
   * Indicates completion of `voPage.getContent()`.
   */
  VO_CMD_GET_CONTENT,

  /**
   * Indicates completion of `voPage.paste()`.
   */
  VO_CMD_PASTE,

  /**
   * Indicates completion of `voDocument.addObject()`.
   */
  VO_CMD_ADD_OBJECT,

  /**
   * Indicates completion of `voDocument.extractObjectTo()`.
   */
  VO_CMD_EXTRACT_OBJECT_TO,
}
voDocumentAsyncCommand;


/**
 * Contains the result of asynchronous commands of `voDocument` and
 * `voPage`.
 * @see voDocumentAsyncCommandCompletionCallback.
 */
typedef union _voDocumentAsyncCommandResult
{
  voEngineObject object;
  struct {
    voJson metadata;
  } getMetadata;
  struct {
    voInk ink;
  } getInk;
  struct {
    voLayout layout;
  } getLayout;
  struct {
    voContent content;
  } getContent;
}
voDocumentAsyncCommandResult;

/**
 * Callback called by the document I/O background thread upon completion of
 * asynchronous commands of `voDocument` and `voPage`.
 *
 * <p>The objects provided in `result` are valid only during the
 * callback execution, therefore you must use `voAcquireObject()` if
 * you want to retain the object for later use.</p>
 *
 * <p>Do not call sync() from this callback, or this will result in a
 * deadlock.</p>.
 *
 * <p>Do not call other asynchronous functions from this callback (functions
 * that call a callback upon completion), prefer calling asynchronous functions
 * in sequence.</p>
 *
 * @param cmd the command that just completed.
 * @param success `true` if the command was successful.
 * @param result the result of the command.
 * @param userParam the user parameter that was given .
 *
 * @see voIDocument, voIPage.
 */
typedef void (VO_MSE_CALL *voDocumentAsyncCommandCompletionCallback)(voDocumentAsyncCommand cmd, bool success, voDocumentAsyncCommandResult result, void* userParam);


// -- Document -----------------------------------------------------------------

/**
 * {@propertySet Document}
 */
enum VO_DOCUMENT_PROP
{
  /**
   * Specifies if the document uses the auto save feature.
   * This value must be false (disabled) or true (enabled).
   *
   * {@property bool}
   */
  VO_DOCUMENT_AUTO_SAVE = (VO_Document << 16),
};

/**
 * Represents the parameters required to create a `voDocument` object.
 * @see voDocument, voCreateObjectEx.
 */
typedef struct _voDocumentInitializer
{
  /**
   * The charset used to encode pathnames.
   */
  voCharset charset;

  /**
   * The pathname of the document.
   */
  voString fileName;

  /**
   * The pathname of the temporary directory to use. If empty, a directory name
   * will be set to `fileName + "-files"`.
   */
  voString temporaryDirectoryName;
}
voDocumentInitializer;

/**
 * Functions composing the `IDocument` interface. This interface
 * exposes the public methods of the `Document` type.
 *
 * Document manipulation will create temporary files in a directory located in
 * file system's temporary directory if it is set, otherwise in the same
 * directory as the document.
 * This directory is named by appending "-files" to the document's file name
 * (e.g. "mydoc.notes-files").
 * It will be removed upon saving or discarding of the document's modifications
 * (call to `save()` or `saveAs()` or `discardChanges()`).
 *
 * Document manipulation may also create temporary files at the root directory
 * of file system temporary directory if it is set, otherwise in the same
 * directory as the document. These temp files names end with a '~' to indicate
 * the temporary nature.
 *
 * {@implementingTypes voDocument}
 * @see VO_IDocument, VO_Document.
 */
typedef struct _voIDocument
{
  /**
   * Sets the temporary directory to be used by the document.
   * If a temporary directory has already been created, i.e. if `saveToTemp()`
   * has been called, this operation is not allowed anymore, you must call
   * `save()` or `discardChanges()` first.
   * If it does not exist, the temporary directory will be created.
   *
   * @param engine the engine.
   * @param target the target document.
   * @param charset the charset used to encode `directoryName`.
   * @param directoryName the new temporary directory name.
   *
   * @return `true` if process started successfully, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference
   *   to a `Document` instance.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `directoryName` recipient is not readable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the
   *   `directoryName` string is not readable.
   * @throws VO_INVALID_STATE the temporary directory has already been created.
   */
  bool (VO_MSE_CALL *setTemporaryDirectory)(voEngine engine, voDocument target, voCharset charset, const voString* directoryName);

  /**
   * Returns whether the document has been modified since the last saving
   * operation.
   *
   * @param engine the engine.
   * @param target the target document.
   *
   * @return `VO_YES` if document has been modified,
   *         `VO_NO` if it has not been modified, `VO_ERR`
   *         if an error occurred.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference
   *   to a `Document` instance.
   */
  voYesNo (VO_MSE_CALL *isModified)(voEngine engine, voDocument target);

  /**
   * Requests saving all ongoing modifications to the document.
   * Completion and success of this operation is indicated by calling the
   * callback provided by user.
   *
   * @param engine the engine.
   * @param target the target document.
   * @param callback the function that will be called upon completion of the
   *   save operation.
   * @param userParam the userParam that will be provided as input to
   *   `callback` function.
   *
   * @return `true` if process started successfully, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `Document` instance.
   * @throws VO_INVALID_STATE if document file name has not been set.
   */
  bool (VO_MSE_CALL *save)(voEngine engine, voDocument target, voDocumentAsyncCommandCompletionCallback callback, void* userParam);

  /**
   * Requests saving the document, and any ongoing modification, as a new file.
   * Completion and success of this operation is indicated by calling the
   * callback provided by user.
   *
   * @param engine the engine.
   * @param target the target document.
   * @param charset the charset used to encode `fileName`.
   * @param fileName the new document name.
   * @param callback the function that will be called upon completion
   *   of the save operation.
   * @param userParam the userParam that will be provided as input to
   *   `callback` function.
   *
   * @return `true` if process started successfully, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `Document` instance.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `fileName` string is not readable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the
   *   `fileName` string is not readable.
   */
  bool (VO_MSE_CALL *saveAs)(voEngine engine, voDocument target, voCharset charset, const voString* fileName, voDocumentAsyncCommandCompletionCallback callback, void* userParam);

  /**
   * Requests saving all ongoing modifications to the temporary folder.
   * Completion and success of this operation is indicated by calling the
   * callback provided by user.
   *
   * @param engine the engine.
   * @param target the target document.
   * @param callback the function that will be called upon completion of the
   *   save operation.
   * @param userParam the userParam that will be provided as input to
   *  `callback` function.
   *
   * @return `true` if process started successfully, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `Document` instance.
   * @throws VO_INVALID_STATE if no temporary directory has been set.
   */
  bool (VO_MSE_CALL *saveToTemp)(voEngine engine, voDocument target, voDocumentAsyncCommandCompletionCallback callback, void* userParam);

  /**
   * Requests discarding all changes that have been done but not saved to the
   * document.
   * This will remove the temporary directory associated with the document and
   * all unsaved content will be lost.
   * Completion and success of this operation is indicated by calling the
   * callback provided by user.
   *
   * @param engine the engine.
   * @param target the target document.
   * @param callback the function that will be called upon completion of the
   *   operation.
   * @param userParam the userParam that will be provided as input to
   *  `callback` function.
   *
   * @return `true` if process started successfully, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `Document` instance.
   */
  bool (VO_MSE_CALL *discardChanges)(voEngine engine, voDocument target, voDocumentAsyncCommandCompletionCallback callback, void* userParam);

  /**
   * Requests the metadata object associated with a document.
   * Completion and success of this operation is indicated by calling the
   * callback provided by user.
   *
   * @param engine the engine.
   * @param target the target document.
   * @param callback the function that will be called upon completion of the
   *   operation.
   * @param userParam the userParam that will be provided as input to
   *  `callback` function.
   *
   * @return `true` if process started successfully, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `Document` instance.
   */
  bool (VO_MSE_CALL *getMetadata)(voEngine engine, voDocument target, voDocumentAsyncCommandCompletionCallback callback, void* userParam);

  /**
   * Requests setting the metadata object associated with a document.
   * Completion and success of this operation is indicated by calling the
   * callback provided by user.
   *
   * @param engine the engine.
   * @param target the target document.
   * @param metadata the metadata to set.
   * @param callback the function that will be called upon completion of the
   *   operation.
   * @param userParam the userParam that will be provided as input to
   *  `callback` function.
   *
   * @return `true` if process started successfully, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `Document` instance.
   * @throws VO_INVALID_OBJECT the `metadata` reference is not a reference to
   *   a `Json` instance.
   */
  bool (VO_MSE_CALL *setMetadata)(voEngine engine, voDocument target, voJson metadata, voDocumentAsyncCommandCompletionCallback callback, void* userParam);

  /**
   * Returns the number of pages in the document.
   *
   * @param engine the engine.
   * @param target the target document.
   *
   * @return the number of pages on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `Document` instance.
   */
  int (VO_MSE_CALL *getPageCount)(voEngine engine, voDocument target);

  /**
   * Returns the page at the specified index in the document.
   *
   * @param engine the engine.
   * @param target the target document.
   * @param index the index of the page.
   *
   * @return the page on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to a
   *   `Document` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS the `index` is invalid.
   */
  voPage (VO_MSE_CALL *getPageAt)(voEngine engine, voDocument target, int index);

  /**
   * Returns the specified page.
   *
   * @param engine the engine.
   * @param target the target document.
   * @param charset the charset used to encode the page id.
   * @param id the page id.
   *
   * @return the page on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `Document` instance.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `id` is not readable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of `id` is not readable.
   * @throws VO_INVALID_ARGUMENT if no page exists with the specified id.
   */
  voPage (VO_MSE_CALL *getPage)(voEngine engine, voDocument target, voCharset charset, const voString* id);

  /**
   * Returns the index of a page within the target document.
   *
   * @param engine the engine.
   * @param target the target document.
   * @param page the page.
   *
   * @return the index of the page on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to a
   *   `Document` instance.
   * @throws VO_NO_SUCH_OBJECT the `page` reference is invalid.
   * @throws VO_INVALID_OBJECT the `page` reference is not a reference to a
   *   `Page` instance.
   * @throws VO_INVALID_OBJECT the page does not belong to the target document.
   */
  int (VO_MSE_CALL *indexOfPage)(voEngine engine, voDocument target, voPage page);

  /**
   * Adds a page to the document.
   *
   * @param engine the engine.
   * @param target the target document.
   *
   * @return the new page on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to a
   *   `Document` instance.
   */
  voPage (VO_MSE_CALL *addPage)(voEngine engine, voDocument target);

  /**
   * Adds a page to the document, that contains a given ink.
   *
   * @param engine the engine.
   * @param target the target document.
   * @param ink the ink that the new page will contain.
   *
   * @return the new page on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `ink` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to a
   *   `Document` instance.
   * @throws VO_INVALID_OBJECT the `ink` reference is not a
   *   reference to a `Ink` instance.
   * @throws VO_INVALID_OBJECT the `ink` is already in use in a page.
   */
  voPage (VO_MSE_CALL *addPageWithInk)(voEngine engine, voDocument target, voInk ink);

  /**
   * Removes a page from the document.
   *
   * @param engine the engine.
   * @param target the target document.
   * @param index the index of the page to remove.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to a
   *   `Document` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS the `index` is invalid.
   */
  bool (VO_MSE_CALL *removePage)(voEngine engine, voDocument target, int index);

  /**
   * Moves a page within the document.
   *
   * @param engine the engine.
   * @param target the target document.
   * @param fromIndex the current index of the page to move.
   * @param toIndex the new index of the page to move.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to a
   *   `Document` instance.
   * @throws VO_INDEX_OUT_OF_BOUNDS the `fromIndex` is invalid.
   * @throws VO_INDEX_OUT_OF_BOUNDS the `toIndex` is invalid.
   */
  bool (VO_MSE_CALL *movePage)(voEngine engine, voDocument target, int fromIndex, int toIndex);

  /**
   * Returns whether the document contains a given object.
   *
   * @param engine the engine.
   * @param target the target document.
   * @param charset the charset to be used to encode `url`.
   * @param url the URL of the object within the document.
   *
   * @return `VO_YES` if document contains an object with the specified URL,
   *         otherwise `VO_NO`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to a
   *   `Document` instance.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `url` recipient is not readable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of `url` is not readable.
   */
  voYesNo (VO_MSE_CALL *containsObject)(voEngine engine, voDocument target, voCharset charset, const voString* url);

  /**
   * Removes an object from the document.
   * The object will not be removed from the document file immediately,
   * to allow undo/redo of this action.
   * However, when the document is released, this object will not be
   * accessible anymore, and next time that the document is loaded,
   * the object will be actually removed.
   *
   * @param engine the engine.
   * @param target the target document.
   * @param charset the charset to be used to encode `url`.
   * @param url the URL of the object within the document.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to a
   *   `Document` instance.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `url` recipient is not readable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of `url` is not readable.
   */
  bool (VO_MSE_CALL *removeObject)(voEngine engine, voDocument target, voCharset charset, const voString* url);

  /**
   * Requests adding an object file to the document and associates it with a URL.
   * This object can then be referenced by its URL in the layout of the
   * document's pages.
   * Successful operation completion is indicated by calling the callback
   * provided as parameter.
   *
   * @param engine the engine.
   * @param target the target document.
   * @param charset the charset to be used to encode `url` and `fileName`.
   * @param url the URL to associate the object with.
   * @param fileName the path to the object file to add to the document.
   * @param callback the function that will be called upon completion of the
   *   operation.
   * @param userParam the userParam that will be provided as input to
   *  `callback` function.
   *
   * @return `true` if the operation started successfully, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to a
   *   `Document` instance.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `url` string is not readable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the
   *   `url` string is not readable.
   * @throws VO_INVALID_USER_BUFFER the `fileName` string is not readable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the
   *   `fileName` string is not readable.
   * @throws VO_INVALID_STATE the temporary directory is not set or cannot be
   *   inferred from the document path (document is not saved).
   */
  bool (VO_MSE_CALL *addObject)(voEngine engine, voDocument target, voCharset charset, const voString* url, const voString* fileName, voDocumentAsyncCommandCompletionCallback callback, void* userParam);

  /**
   * Requests extracting an object from the document to a given path.
   * Successful operation completion is indicated by calling the callback
   * provided as parameter.
   * The function fails immediately (the callback is not called) if the object
   * is not part of the document.
   *
   * @param engine the engine.
   * @param target the target document.
   * @param charset the charset to be used to encode `url` and `fileName`.
   * @param url the URL of the object within the document.
   * @param fileName the path to extract the object file to.
   * @param callback the function that will be called upon completion of the
   *   operation.
   * @param userParam the userParam that will be provided as input to
   *  `callback` function.
   *
   * @return `true` if process started successfully, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to a
   *   `Document` instance.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `url` string is not readable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the
   *   `url` string is not readable.
   * @throws VO_INVALID_USER_BUFFER the `fileName` string is not readable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the
   *   `fileName` string is not readable.
   */
  bool (VO_MSE_CALL *extractObjectTo)(voEngine engine, voDocument target, voCharset charset, const voString* url, const voString* fileName, voDocumentAsyncCommandCompletionCallback callback, void* userParam);

  /**
   * Waits until all pending actions are done.
   * Use this function to wait until `save()` or `saveAs()` are over.
   *
   * @param engine the engine.
   * @param target the target document.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to a
   *   `Document` instance.
   */
  bool (VO_MSE_CALL *sync)(voEngine engine, voDocument target);

  /**
   * Returns an iterator over the objects of the document.
   * When corresponding document is modified (adding or removing objects),
   * iterator will be invalidated.
   *
   * @param engine the engine.
   * @param target the target document.
   *
   * @return an object iterator on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` does not implement
   *   the `IDocument` interface.
   */
   voObjectIterator (VO_MSE_CALL *getObjects)(voEngine engine, voDocument target);
}
voIDocument;


#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `Document` type.
 *
 * @param engine the engine.
 *
 * @return A reference to the newly created `Document` object on success,
 *   otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED the number of `Document`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared among several types).
 * @throws VO_OUT_OF_MEMORY not enough memory to create the object.
 */
VO_INLINE voDocument voCreateDocument(voEngine engine)
{
  return voCreateObject(engine, VO_Document);
}

/**
 * Creates an instance of the `Document` type.
 *
 * @param engine the engine.
 * @param charset the charset used to encode pathnames.
 * @param filename the pathname of the document.
 * @param temporaryDirectoryName the pathname of the temporary directory to use.
 *   If empty, a directory name will be set to `fileName + "-files"`.
 *
 * @return A reference to the newly created `Document` object on success,
 *   otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED the number of `Document`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared among several types).
 * @throws VO_OUT_OF_MEMORY not enough memory to create the object.
 */
VO_INLINE voDocument voCreateDocumentEx(voEngine engine,
                                        voCharset charset,
                                        const voString* fileName,
                                        const voString* temporaryDirectoryName)
{
  voDocumentInitializer initializer;

  initializer.charset = charset;

  initializer.fileName.bytes = ((fileName != NULL) ? fileName->bytes : NULL);
  initializer.fileName.byteCount = ((fileName != NULL) ? fileName->byteCount : 0);

  initializer.temporaryDirectoryName.bytes = ((temporaryDirectoryName != NULL)
                                      ? temporaryDirectoryName->bytes : NULL);
  initializer.temporaryDirectoryName.byteCount = ((temporaryDirectoryName != NULL)
                                      ? temporaryDirectoryName->byteCount : 0);

  return voCreateObjectEx(engine, VO_Document, &initializer, sizeof(initializer));
}
#endif // end of: #ifndef VO_NO_FUNCTIONS


// -- Page ---------------------------------------------------------------------

/**
 * Reference to an instance of the `PageSelection` type.
 * Note that it is possible to parse the content a page selection via the
 * `ILayout` interfaces, but it is not allowed to modify the layout via
 * the page selection.
 *
 * {@extends voEngineObject}
 * {@implements voIPageSelection, voIInkStrokeSet, voISelection, voILayout, voIExtentProvider}
 */
typedef voEngineObject voPageSelection;

/**
 * Reference to an instance of the `LayerIterator` type.
 *
 * {@extends voIterator}
 * {@implements voILayerIterator, voIExtentProvider}
 */
typedef voIterator voLayerIterator;

/**
 * Reference to an instance of the `PenIterator` type.
 *
 * {@extends voIterator}
 * {@implements voIPenIterator}
 */
typedef voIterator voPenIterator;

/**
 * Reference to an instance of the `LayoutItemIterator` type.
 *
 * {@extends voIterator}
 * {@implements voILayoutItemIterator, voIExtentProvider}
 */
typedef voIterator voLayoutItemIterator;

/**
 * Functions composing the `IPage` interface. This interface exposes
 * the public methods of the `Page` type.
 *
 * {@implementingTypes voPage}
 * @see VO_IPage, VO_Page.
 */
typedef struct _voIPage
{
  /**
   * Returns the document that contains the target page.
   *
   * @param engine the engine.
   * @param target the target page.
   *
   * @return the document on success, `NULL` otherwise.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `Page` instance.
   * @throws VO_LIMIT_EXCEEDED the number of `Document` instances would exceed
   *   the allowed limit (please remember that the limit can be shared among
   *   several types).
   * @throws VO_OUT_OF_MEMORY not enough memory to create the object.
   */
  voDocument (VO_MSE_CALL *getDocument)(voEngine engine, voPage target);

  /**
   * Returns the identifier of the target page.
   *
   * @param engine the engine.
   * @param target the target page.
   * @param charset the charset to be used to encode the value.
   * @param id a recipient for the value.
   *
   * @return `true`on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to a
   *   `Page` instance.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL` and no default
   *   charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a reference to a
   *   `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `id` recipient is not readable or
   *   writable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the `id` recipient is
   *   not writable.
   */
  bool (VO_MSE_CALL *getId)(voEngine engine, voPage target, voCharset charset, voString* id);

  /**
   * Adds the specified listener to the target page.
   *
   * @param engine the engine.
   * @param target the target page.
   * @param listener the change listener to add.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `Page` instance.
   * @throws VO_INVALID_OBJECT if `listener` does not implement the
   *   `IPageUpdateListener` interface.
   * @throws VO_INVALID_STATE if `listener` is already registered.
   */
  bool (VO_MSE_CALL *addListener)(voEngine engine, voPage target, voEngineObject listener);

  /**
   * Removes the specified listener from the target page.
   *
   * @param engine the engine.
   * @param target the target page.
   * @param listener the listener to remove.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `Page` instance.
   * @throws VO_INVALID_OBJECT if `listener` does not implement the
   *   `IPageUpdateListener` interface.
   * @throws VO_INVALID_STATE if `listener` is not registered in this page.
   */
  bool (VO_MSE_CALL *removeListener)(voEngine engine, voPage target, voEngineObject listener);

  /**
   * Returns whether the page has been modified since the last saving operation.
   *
   * @param engine the engine.
   * @param target the target page.
   *
   * @return `VO_YES` if page has been modified, `VO_NO`
   *         if it has not been modified, `VO_ERR` if an error
   *         occurred.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `Page` instance.
   */
  voYesNo (VO_MSE_CALL *isModified)(voEngine engine, voPage target);

  /**
   * Requests saving all ongoing modifications on the page to the document.
   * Completion and success of this operation is indicated through the provided
   * callback.
   *
   * @param engine the engine.
   * @param target the target page.
   * @param callback the function that will be called upon completion of the
   *   operation.
   * @param userParam the userParam that will be provided as input to `callback`
   *   function.
   *
   * @return `true` if process started successfully, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `Page` instance.
   */
  bool (VO_MSE_CALL *save)(voEngine engine, voPage target, voDocumentAsyncCommandCompletionCallback callback, void* userParam);

  /**
   * Requests saving all ongoing modifications to the page to the temporary
   * directory.
   * Completion and success of this operation is indicated through the provided
   * callback.
   *
   * @param engine the engine.
   * @param target the target page.
   * @param callback the function that will be called upon completion of the
   *   operation.
   * @param userParam the userParam that will be provided as input to `callback`
   *   function.
   *
   * @return `true` if process started successfully, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `Page` instance.
   */
  bool (VO_MSE_CALL *saveToTemp)(voEngine engine, voPage target, voDocumentAsyncCommandCompletionCallback callback, void* userParam);

  /**
   * Requests discarding all changes that have been done but not saved to the
   * document. Changes saved to the temporary folder will be discarded too.
   * Completion and success of this operation is indicated through the provided
   * callback.
   *
   * @param engine the engine.
   * @param target the target page.
   * @param callback the function that will be called upon completion of the
   *   operation.
   * @param userParam the userParam that will be provided as input to `callback`
   *   function.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `Page` instance.
   */
  bool (VO_MSE_CALL *discardChanges)(voEngine engine, voPage target, voDocumentAsyncCommandCompletionCallback callback, void* userParam);

  /**
   * Requests the metadata object associated with the page.
   * Completion and success of this operation is indicated through the provided
   * callback.
   *
   * @param engine the engine.
   * @param target the target page.
   * @param callback the function that will be called upon completion of the
   *   operation.
   * @param userParam the userParam that will be provided as input to `callback`
   *   function.
   *
   * @return `true` if process started successfully, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `Page` instance.
   */
  bool (VO_MSE_CALL *getMetadata)(voEngine engine, voPage target, voDocumentAsyncCommandCompletionCallback callback, void* userParam);

  /**
   * Requests setting the metadata object associated with the page.
   * Completion and success of this operation is indicated through the provided
   * callback.
   *
   * @param engine the engine.
   * @param target the target page.
   * @param metadata the new metadata.
   * @param callback the function that will be called upon completion of the
   *   operation.
   * @param userParam the userParam that will be provided as input to `callback`
   *   function.
   *
   * @return `true` if process started successfully, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `Page` instance.
   * @throws VO_INVALID_OBJECT the `metadata` reference is not a reference to
   *   a `Json` instance.
   */
  bool (VO_MSE_CALL *setMetadata)(voEngine engine, voPage target, voJson metadata, voDocumentAsyncCommandCompletionCallback callback, void* userParam);

  /**
   * Requests the ink object associated with the page.
   * Completion and success of this operation is indicated through the provided
   * callback.
   *
   * @param engine the engine.
   * @param target the target page.
   * @param callback the function that will be called upon completion of the
   *   operation.
   * @param userParam the userParam that will be provided as input to `callback`
   *   function.
   *
   * @return `true` if process started successfully, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `Page` instance.
   */
  bool (VO_MSE_CALL *getInk)(voEngine engine, voPage target, voDocumentAsyncCommandCompletionCallback callback, void* userParam);

  /**
   * Requests the layout of the page.
   * Completion and success of this operation is indicated through the provided
   * callback.
   *
   * @param engine the engine.
   * @param target the target page.
   * @param callback the function that will be called upon completion of the
   *   operation.
   * @param userParam the userParam that will be provided as input to `callback`
   *   function.
   *
   * @return `true` if process started successfully, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `Page` instance.
   */
  bool (VO_MSE_CALL *getLayout)(voEngine engine, voPage target, voDocumentAsyncCommandCompletionCallback callback, void* userParam);

  /**
   * Requests the content of a page.
   * Completion and success of this operation is indicated through the provided
   * callback.
   *
   * @param engine the engine.
   * @param target the target page.
   * @param callback the function that will be called upon completion of the
   *   operation.
   * @param userParam the userParam that will be provided as input to `callback`
   *   function.
   *
   * @return `true` if process started successfully, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `Page` instance.
   */
  bool (VO_MSE_CALL *getContent)(voEngine engine, voPage target, voDocumentAsyncCommandCompletionCallback callback, void* userParam);

  /**
   * Erases the selected items from the page.
   *
   * @param engine the engine.
   * @param target the target page.
   * @param selection the selection to erase.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `Page` instance.
   * @throws VO_INVALID_OBJECT the `selection` reference is not a
   *   reference to a `voPageSelection` instance.
   * @throws VO_INVALID_OBJECT the `selection` was not create on
   *   `target` page.
   */
  bool (VO_MSE_CALL *erase)(voEngine engine, voPage target, voPageSelection selection);

  /**
   * Transforms the selected items in the page.
   *
   * @param engine the engine.
   * @param target the target page.
   * @param selection the selection to transform.
   * @param transform the affine transform to apply.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `Page` instance.
   * @throws VO_INVALID_OBJECT the `selection` reference is not a
   *   reference to a `voPageSelection` instance.
   * @throws VO_INVALID_OBJECT the `selection` was not create on
   *   `target` page.
   * @throws VO_INVALID_USER_BUFFER the `transform` parameter is not readable.
   */
  bool (VO_MSE_CALL *transform)(voEngine engine, voPage target, voPageSelection selection, const voTransform* transform);

  /**
   * Pastes the selected items into the page. The selection may have been
   * created on another page, or another document.
   * Completion and success of this operation is indicated through the provided
   * callback.
   *
   * @param engine the engine.
   * @param target the target page.
   * @param selection the selection to paste.
   * @param callback the function that will be called upon completion of the
   *   operation.
   * @param userParam the userParam that will be provided as input to `callback`
   *   function.
   *
   * @return `true` if process started successfully, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `Page` instance.
   * @throws VO_INVALID_OBJECT the `selection` reference is not a
   *   reference to a `voPageSelection` instance.
   */
  bool (VO_MSE_CALL *paste)(voEngine engine, voPage target, voPageSelection selection, voDocumentAsyncCommandCompletionCallback callback, void* userParam);

  /**
   * Groups the selected items.
   *
   * @param engine the engine.
   * @param target the target page.
   * @param selection the selection of items to group.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `Page` instance.
   * @throws VO_INVALID_OBJECT the `selection` reference is not a
   *   reference to a `voPageSelection` instance.
   * @throws VO_INVALID_OBJECT the `selection` was not create on
   *   `target` page.
   */
  bool (VO_MSE_CALL *group)(voEngine engine, voPage target, voPageSelection selection);

  /**
   * Ungroups selected items. Any group that contain selected items will be
   * removed.
   *
   * @param engine the engine.
   * @param target the target page.
   * @param selection the selection of items to ungroup.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `Page` instance.
   * @throws VO_INVALID_OBJECT the `selection` reference is not a
   *   reference to a `voPageSelection` instance.
   * @throws VO_INVALID_OBJECT the `selection` was not create on
   *   `target` page.
   */
  bool (VO_MSE_CALL *ungroup)(voEngine engine, voPage target, voPageSelection selection);

  /**
   * Removes all groups from the page.
   *
   * @param engine the engine.
   * @param target the target page.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `Page` instance.
   */
  bool (VO_MSE_CALL *ungroupAll)(voEngine engine, voPage target);

  /**
   * Brings the selected items to the front of their layer. If items are part of
   * a group, the entire group will be moved. Items will stay in the same layer.
   *
   * @param engine the engine.
   * @param target the target page.
   * @param selection the selection of items to move.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `Page` instance.
   * @throws VO_INVALID_OBJECT the `selection` reference is not a
   *   reference to a `voPageSelection` instance.
   * @throws VO_INVALID_OBJECT the `selection` was not create on
   *   `target` page.
   */
  bool (VO_MSE_CALL *bringToFront)(voEngine engine, voPage target, voPageSelection selection);

  /**
   * Pushes the selected items to the back of their layer. If items are part of
   * a group, the entire group will be moved. Items will stay in the same layer.
   *
   * @param engine the engine.
   * @param target the target page.
   * @param selection the selection of items to move.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `Page` instance.
   * @throws VO_INVALID_OBJECT the `selection` reference is not a
   *   reference to a `voPageSelection` instance.
   * @throws VO_INVALID_OBJECT the `selection` was not create on
   *   `target` page.
   */
  bool (VO_MSE_CALL *pushToBack)(voEngine engine, voPage target, voPageSelection selection);

  /**
   * Moves the selected items to the front of the given layer. If items are part
   * of a group, the entire group will be moved.
   *
   * @param engine the engine.
   * @param target the target page.
   * @param selection the selection of items to move.
   * @param layer the layer to move the selection to.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `Page` instance.
   * @throws VO_INVALID_OBJECT the `selection` reference is not a
   *   reference to a `voPageSelection` instance.
   * @throws VO_INVALID_OBJECT the `selection` was not create on
   *   `target` page.
   * @throws VO_NO_SUCH_ELEMENT the `layer` iterator is positioned at the
   *   end of the iteration.
   */
  bool (VO_MSE_CALL *moveToLayer)(voEngine engine, voPage target, voPageSelection selection, voLayerIterator layer);

  /**
   * Cleans the content of the page.
   * In the page layout, this will:
   *   remove unused pens (i.e. not referenced in a strokes item),
   *   remove strokes items whose corresponding ink has been removed,
   *   remove images whose corresponding object has been removed from the document.
   * This operation can be undone via the history manager.
   * This function does not need to be run frequently, it can be run e.g. at the time
   * of page release.
   *
   * @param engine the engine.
   * @param target the target page.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `Page` instance.
   */
  bool (VO_MSE_CALL *cleanup)(voEngine engine, voPage target);

  /**
   * Waits until all pending actions are done. Use this function to wait until
   * functions that use callbacks are done.
   *
   * @param engine the engine.
   * @param target the target page.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `Page` instance.
   */
  bool (VO_MSE_CALL *sync)(voEngine engine, voPage target);
}
voIPage;


/**
 * Represents the parameters required to create a page selection.
 */
typedef struct _voPageSelectionInitializer
{
  /**
   * The target page.
   */
  voPage page;
}
voPageSelectionInitializer;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `PageSelection` type.
 *
 * <p>Please note that a page selection needs the ink and layout of page to
 * function. Therefore, this call may block for the time required to load ink
 * and layout if they are not already loaded before.</p>
 *
 * @param engine the engine.
 * @param page the target page.
 *
 * @return A reference to the newly created `PageSelection` object on
 *   success, otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED the number of `PageSelection` instances would
 *   exceed the allowed limit (please remember that the limit can be shared
 *   among several types).
 * @throws VO_OUT_OF_MEMORY not enough memory to create the object.
 */
VO_INLINE voPageSelection voCreatePageSelection(voEngine engine, voPage page)
{
  voPageSelectionInitializer initializer = { page };
  return voCreateObjectEx(engine, VO_PageSelection, &initializer, sizeof(initializer));
}
#endif // end of: #ifndef VO_NO_FUNCTIONS

/**
 * Functions composing the `IPageSelection` interface. This interface
 * exposes the public methods of the `PageSelection` type.
 *
 * {@implementingTypes voPageSelection}
 * @see VO_IPageSelection, VO_PageSelection.
 */
typedef struct _voIPageSelection
{
  /**
   * Returns the page on which the target page selection is based.
   *
   * @param engine the engine.
   * @param target the target page selection.
   *
   * @return the page on success, `NULL` otherwise.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `PageSelection` instance.
   */
  voPage (VO_MSE_CALL *getPage)(voEngine engine, voPageSelection target);

  /**
   * Selects the top most item that intersects the specified circle.
   *
   * @param engine the engine.
   * @param target the target page selection.
   * @param circle the circle to select.
   * @param layer an iterator positioned on the layer on which the selection
   *   should be performed, or `NULL` for all layers.
   * @param modifier the way the new selection should be combined with the
   *   existing selection.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `PageSelection` instance.
   * @throws VO_INVALID_OBJECT the `layer` reference is not a reference to
   *   a `LayerIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT the `layer` iterator is positioned at the
   *   end of the iteration.
   * @throws VO_INVALID_ARGUMENT the `circle` is invalid.
   * @throws VO_INVALID_OBJECT the layer is from a different page.
   */
  bool (VO_MSE_CALL *hit)(voEngine engine, voPageSelection target, const voCircle* circle, voLayerIterator layer, voSelectionModifier modifier);

  /**
   * Selects the specified layer.
   *
   * @param engine the engine.
   * @param target the target page selection.
   * @param layer an iterator positioned on the layer to select.
   * @param modifier the way the new selection should be combined with the
   *   existing selection.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `PageSelection` instance.
   * @throws VO_INVALID_OBJECT the `layer` reference is not a reference to
   *   a `LayerIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT the `layer` iterator is positioned at the
   *   end of the iteration.
   * @throws VO_INVALID_OBJECT the layer is from a different page.
   */
  bool (VO_MSE_CALL *selectLayer)(voEngine engine, voPageSelection target, voLayerIterator layer, voSelectionModifier modifier);

  /**
   * Selects the specified item. If that item belongs to a group, the entire
   * group will be selected.
   *
   * @param engine the engine.
   * @param target the target page selection.
   * @param item an iterator positioned on the layout item to select.
   * @param modifier the way the new selection should be combined with the
   *   existing selection.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `PageSelection` instance.
   * @throws VO_INVALID_OBJECT the `item` reference is not a reference to
   *   a `LayoutItemIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT the `item` iterator is positioned at the
   *   end of the iteration.
   * @throws VO_INVALID_OBJECT the layout item is from a different page.
   */
  bool (VO_MSE_CALL *selectItem)(voEngine engine, voPageSelection target, voLayoutItemIterator item, voSelectionModifier modifier);

  /**
   * Returns the selected portion of a layout item, as an ink segment.
   *
   * @param engine the engine.
   * @param target the target page selection.
   * @param item an iterator positioned on the layout item.
   *
   * @return the ink segment corresponding to the item on success, otherwise
   *   `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `PageSelection` instance.
   * @throws VO_INVALID_OBJECT the `item` reference is not a reference to
   *   a `LayoutItemIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT the `item` iterator is positioned at the
   *   end of the iteration.
   * @throws VO_INVALID_OBJECT the layout item is from a different page.
   * @throws VO_INVALID_OBJECT the layout item type is not
   *   `VO_LAYOUT_ITEM_STROKES`
   */
  voInkSegment (VO_MSE_CALL *getSelectedSegmentForItem)(voEngine engine, voPageSelection target, voLayoutItemIterator item);

  /**
   * Returns the ink selection corresponding to the page selection.
   *
   * @param engine the engine.
   * @param target the target page selection.
   *
   * @return the ink selection on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `PageSelection` instance.
   */
  voInkSelection (VO_MSE_CALL *getInkSelection)(voEngine engine, voPageSelection target);
}
voIPageSelection;


/**
 * Functions composing the `IPageUpdateListener` interface.
 * Note that this interface is implementable by user objects. Also, user code is
 * not allowed to invoke this interface, that's why voGetInterface() will return
 * `NULL`.
 */
typedef struct _voIPageUpdateListener
{
  /**
   * Called when the target change listener is added to a page object.
   *
   * @param engine the engine.
   * @param target the target change listener.
   * @param page the page to which the change listener was added.
   */
  void (VO_MSE_CALL *added)(voEngine engine, voEngineObject target, voPage page);

  /**
   * Called when the target change listener is removed from a page object.
   *
   * @param engine the engine.
   * @param target the target change listener.
   * @param page the page from which the change listener was removed.
   */
  void (VO_MSE_CALL *removed)(voEngine engine, voEngineObject target, voPage page);

  /**
   * Called when the page has been updated.
   *
   * @param engine the engine.
   * @param target the target change listener.
   * @param page the page that has been updated.
   * @param layerIndex the layout layer index on to which extent applies, or -1
   *    if no layer indication is available.
   * @param extent the extent of updates on the X and Y axes for layer layerIndex.
   *          Note that you should add half the pen width to compute screen update rectangle.
   */
  void (VO_MSE_CALL *onUpdate)(voEngine engine, voEngineObject target, voPage page, int layerIndex, const voExtent* extent);
}
voIPageUpdateListener;


/**
 * Functions composing the `IExtentProvider` interface.
 *
 * {@implementingTypes voLayout, voLayerIterator, voLayoutItemIterator, voPageSelection}
 * @see VO_IExtentProvider.
 */
typedef struct _voIExtentProvider
{
  /**
   * Returns the extent associated with `target`.
   *
   * @param engine the engine.
   * @param target the target layout-related object.
   * @param extent a recipient for the extent.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` does not implement
   *   `voIExtentProvider`.
   * @throws VO_INVALID_USER_BUFFER the `extent` recipient is not writable.
   */
  bool (VO_MSE_CALL *getExtent)(voEngine engine, voEngineObject target, voExtent* extent);
}
voIExtentProvider;


// -- Content ------------------------------------------------------------------

/**
 * Reference to an instance of the `ContentField` type.
 *
 * {@extends voEngineObject}
 * {@implements voIContentField}
 */
typedef voEngineObject voContentField;

/**
 * Lists types of content fields.
 * @see voContent.
 */
typedef enum _voContentFieldType
{
  VO_CONTENT_FIELD_TEXT,      /**< The type of a text field. */
  VO_CONTENT_FIELD_SHAPE,     /**< The type of a shape field. */
  VO_CONTENT_FIELD_EQUATION,  /**< The type of an equation field. */
  VO_CONTENT_FIELD_ANALYZER,  /**< The type of an analyzer field. */
}
voContentFieldType;

/**
 * Functions composing the `IContent` interface. This interface
 * exposes the public methods of the `Content` type.
 *
 * {@implementingTypes voContent}
 * @see VO_IContent.
 */
typedef struct _voIContent
{
  /**
   * Creates a field of the specified type.
   *
   * @param engine the engine.
   * @param target the target content.
   * @param type the type of the field.
   * @param charset the charset used to encode the field id.
   * @param id the field id.
   *
   * @return the newly created `ContentField` on success, `NULL` otherwise.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `Content` instance.
   * @throws VO_INVALID_ARGUMENT the `type` can not be
   *   `VO_CONTENT_FIELD_NOT_A_FIELD`.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `id` is not readable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of `id` is not readable.
   */
  voContentField (VO_MSE_CALL *addNewField)(voEngine engine, voContent target, voContentFieldType type, voCharset charset, const voString* id);

  /**
   * Returns the specified field.
   *
   * @param engine the engine.
   * @param target the target content.
   * @param charset the charset used to encode the field id.
   * @param id the field id.
   *
   * @return the field on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `Content` instance.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `id` is not readable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of `id` is not readable.
   */
  voContentField (VO_MSE_CALL *getField)(voEngine engine, voContent target, voCharset charset, const voString* id);

  /**
   * Removes the specified field.
   *
   * @param engine the engine.
   * @param target the target content.
   * @param charset the charset used to encode the field id.
   * @param id the field id.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to a
   *   `Content` instance.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a reference to a
   *   `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `id` is not readable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of `id` is not readable.
   */
  bool (VO_MSE_CALL *removeField)(voEngine engine, voContent target, voCharset charset, const voString* id);

  /**
   * Returns the number of fields of the specified type.
   *
   * @param engine the engine.
   * @param target the target content.
   * @param type the type of field targeted.
   *
   * @return the number of fields on success, otherwise `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to a
   *   `Content` instance.
   * @throws VO_INVALID_ARGUMENT the `type` is not a value from the
   *   `voContentFieldType` enumeration.
   */
  int (VO_MSE_CALL *getFieldCount)(voEngine engine, voContent target, voContentFieldType type);

  /**
   * Returns the field at the specified index from the list of fields of the
   * specified type.
   *
   * @param engine the engine.
   * @param target the target content.
   * @param type the type of field.
   * @param index the index of the field.
   *
   * @return the field on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to a
   *   `Content` instance.
   * @throws VO_INVALID_ARGUMENT the `type` is not a value from the
   *   `voContentFieldType` enumeration.
   * @throws VO_INDEX_OUT_OF_BOUNDS the `index` is invalid.
   */
  voContentField (VO_MSE_CALL *getFieldAt)(voEngine engine, voContent target, voContentFieldType type, int index);
}
voIContent;

/**
 * Functions composing the `IContentField` interface.
 *
 * {@implementingTypes voContentField}
 * @see VO_IContentField.
 */
typedef struct _voIContentField
{
  /**
   * Returns the type of the field.
   *
   * @param engine the engine.
   * @param target the target content field.
   * @param type a recipient for the type.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `ContentField` instance.
   * @throws VO_INVALID_ARGUMENT `type` is NULL.
   */
  bool (VO_MSE_CALL *getType)(voEngine engine, voContentField target, voContentFieldType* type);

  /**
   * Returns the identifier of the target field.
   *
   * @param engine the engine.
   * @param target the target content field.
   * @param charset the charset to be used to encode the value.
   * @param id a recipient for the value.
   *
   * @return `true`on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to a
   *   `ContentField` instance.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL` and no default
   *   charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a reference to a
   *   `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `id` recipient is not readable or
   *   writable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the `id` recipient is
   *   not writable.
   */
  bool (VO_MSE_CALL *getId)(voEngine engine, voContentField target, voCharset charset, voString* id);

  /**
   * Clears the field in the content.
   *
   * @param engine the engine.
   * @param target the target content field.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `ContentField` instance.
   */
  bool (VO_MSE_CALL *clear)(voEngine engine, voContentField target);

  /**
   * Adds the ink described by the given intervals or page selection to the
   * field.
   *
   * @param engine the engine.
   * @param target the target content field.
   * @param items the ink to be added to this field, as a `voInkIntervals`
   *   or as a `voPageSelection`
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `ContentField` instance.
   * @throws VO_INVALID_OBJECT if `items` is not a `voInkIntervals` or a
   *   `voPageSelection`.
   */
  bool (VO_MSE_CALL *addItems)(voEngine engine, voContentField target, voEngineObject items);

  /**
   * Removes from the field the ink described by the given intervals or page
   * selection.
   *
   * @param engine the engine.
   * @param target the target content field.
   * @param items the ink to be removed from this field, as a `voInkIntervals`
   *   or as a `voPageSelection`.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `ContentField` instance.
   * @throws VO_INVALID_OBJECT if `items` is not a `voInkIntervals` or a
   *   `voPageSelection`.
   */
  bool (VO_MSE_CALL *removeItems)(voEngine engine, voContentField target, voEngineObject items);

  /**
   * Returns the recognition result from the content.
   *
   * @param engine engine the engine.
   * @param target the target content.
   *
   * @return a recognition result instance on success, otherwise
   *          `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` does not implement
   *   the `IContentField` interface.
   * @throws VO_INVALID_STATE the object is not in a state where the
   *   result is available.
   * @throws VO_LIMIT_EXCEEDED the number of `voEngineObject`
   *   instances would exceed the allowed limit (please remember that the limit
   *   can be shared among several types).
   */
  voEngineObject (VO_MSE_CALL *getResult)(voEngine engine, voContentField target);
}
voIContentField;

/**
 * Functions composing the `IContentFieldProcessor` interface.
 *
 * @see VO_IContentFieldProcessor.
 */
typedef struct _voIContentFieldProcessor
{
  /**
   * Processes a `ContentField` instance.
   *
   * @param engine the engine.
   * @param target the target processor able to process this content field.
   * @param contentField the content field to be processed.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference does not
   *   implement this interface.
   * @throws VO_NO_SUCH_OBJECT the `contentField` reference is
   *   invalid.
   * @throws VO_INVALID_OBJECT the `contentField` object is not an
   *   instance of the `ContentField` type.
   * @throws VO_INVALID_CALLBACK the notification callback crashed.
   * @throws VO_INVALID_STATE the `target` object is not in a state
   *   where the `process` function can be invoked.
   * @throws VO_CANCELED the operation has been canceled.
   *
   */
  bool (VO_MSE_CALL *process)(voEngine engine, voEngineObject target, voContentField contentField, voNotifyProgressFunc notifyProgressFunc, void* userParam);
}
voIContentFieldProcessor;


// -- Layout -------------------------------------------------------------------

/**
 * Describes the available item types in the layout of a page.
 * @see voLayoutItemIterator.
 */
enum VO_LAYOUT_ITEM_TYPE
{
  VO_LAYOUT_ITEM_STROKES = 1,   /**< Associates an ink portion with a pen. */
  VO_LAYOUT_ITEM_IMAGE,         /**< Defines the position of an image. */
  VO_LAYOUT_ITEM_OBJECT,        /**< Defines the position of a generic object. */
};

/**
 * Represents the properties of a strokes layout item.
 */
typedef struct _voLayoutStrokesData
{
  /**
   * The identifier of the tag that defines the set of strokes in the page
   * ink.
   */
  int64_t tagId;

  /**
   * The identifier of the pen to be used to draw the strokes.
   */
  const char* penId;
}
voLayoutStrokesData;

/**
 * Represents the properties of an image layout item.
 */
typedef struct _voLayoutImageData
{
  /**
   * The URL of the image. You have to give this URL to
   * `voIDocument::extractObjectTo()` in order to retrieve the image data.
   */
  const char* url;

  /**
   * The position of the image in the layout, prior to the transformation if
   * there is one.
   */
  voRectangle rectangle;

  /**
   * The identifier of the transformation to be applied to the image, if any.
   * Otherwise `NULL`. You have to give this identifier to
   * `voILayout::getTransform()` to get the transform matrix.
   */
  const char* transformId;
}
voLayoutImageData;

/**
 * Represents the properties of an object layout item.
 */
typedef struct _voLayoutObjectData
{
  /**
   * The URL of the object. You have to give this URL to
   * `voIDocument::extractObjectTo()` in order to retrieve the object data.
   */
  const char* url;

  /**
   * The position of the object in the layout, prior to the transformation
   * if there is one.
   */
  voRectangle rectangle;

  /**
   * The identifier of the transformation to be applied to the image, if any.
   * Otherwise `NULL`. You have to give this identifier to
   * `voILayout::getTransform()` to get the transform matrix.
   */
  const char* transformId;

  /**
   * The mime type of the object, if specified. Otherwise `NULL`.
   */
  const char* mimeType;
}
voLayoutObjectData;

/**
 * Represents the properties of a layout item.
 * @see voLayout.
 */
typedef struct _voLayoutItemData
{
  /**
   * The type of the layout item.
   * @see VO_LAYOUT_ITEM_TYPE.
   */
  int64_t type;

  /**
   * The properties of the layout item. Used member depends on `type`.
   */
  union {
    /**
     * The properties of the layout item when `type == VO_LAYOUT_ITEM_STROKES`.
     */
    voLayoutStrokesData strokes;

    /**
     * The properties of the layout item when  `type == VO_LAYOUT_ITEM_IMAGE`.
     */
    voLayoutImageData image;

    /**
     * The properties of the layout item when `type == VO_LAYOUT_ITEM_OBJECT`.
     */
    voLayoutObjectData object;
  } data;
}
voLayoutItemData;

/**
 * Represents the properties of a pen.
 * @see voLayout.
 */
typedef struct _voPenData
{
  /**
   * The name of the brush, if any. Otherwise `NULL`.
   */
  const char* brush;

  /**
   * The name of the smoothing algorithm, if any. Otherwise `NULL`.
   */
  const char* smoothing;

  /**
   * The width of the pen.
   */
  float width;

  /**
   * The color of the pen, in RGBA format.
   */
  uint32_t color;
}
voPenData;

/**
 * Functions composing the `ILayout` interface.
 *
 * {@implementingTypes voLayout, voPageSelection}
 * @see VO_ILayout, VO_Layout, VO_Selection.
 */
typedef struct _voILayout
{
  /**
   * Returns the layout viewport.
   *
   * @param engine the engine.
   * @param target the target layout.
   * @param rectangle a recipient for the viewport rectangle.
   *
   * @return true on success, otherwise false.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` does not implement
   *   the `ILayout` interface.
   * @throws VO_INVALID_USER_BUFFER the `rectangle` is NULL.
   */
  bool (VO_MSE_CALL *getViewport)(voEngine engine, voLayout target, voRectangle* rectangle);

  /**
   * Sets the layout viewport.
   *
   * @param engine the engine.
   * @param target the target layout.
   * @param rectangle the viewport rectangle.
   *
   * @return true on success, false otherwise.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` does not implement
   *   the `ILayout` interface.
   * @throws VO_INVALID_USER_BUFFER the `rectangle` is NULL.
   */
  bool (VO_MSE_CALL *setViewport)(voEngine engine, voLayout target, const voRectangle* rectangle);

  /**
   * Returns the number of layers in the layout.
   *
   * @param engine the engine.
   * @param target the target layout.
   *
   * @return the number of layers on success, otherwise -1.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` does not implement
   *   the `ILayout` interface.
   */
  int (VO_MSE_CALL *getLayerCount)(voEngine engine, voLayout target);

  /**
   * Returns an iterator over the layers of the layout.
   * If `id` is not `NULL`, the iterator points only to the specified layer.
   * If no layer corresponds to `id`, the iterator created is empty.
   * When corresponding page is modified, iterator will be invalidated.
   *
   * @param engine the engine.
   * @param target the target layout.
   * @param charset the charset used to encode id, if any.
   * @param id the id of the layer to return, or `NULL` to iterate over all
   *   layers.
   *
   * @return a layer iterator on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` does not implement
   *   the `ILayout` interface.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `id` string is not readable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the
   *   `id` string is not readable.
   */
   voLayerIterator (VO_MSE_CALL *getLayers)(voEngine engine, voLayout target, voCharset charset, const voString* id);

  /**
   * Appends a new layer on front of the layout.
   *
   * @param engine the engine.
   * @param target the target layout.
   * @param charset the charset used to encode id.
   * @param id the identifier of the layer to create.
   *
   * @return true on success, false otherwise.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` does not implement
   *   the `ILayout` interface.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `id` string is not readable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the
   *   `id` string is not readable.
   */
  bool (VO_MSE_CALL *addLayer)(voEngine engine, voLayout target, voCharset charset, const voString* id);

  /**
   * Returns the number of pens in the layout.
   *
   * @param engine the engine.
   * @param target the target layout.
   *
   * @return the number of pens on success, otherwise -1.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` does not implement
   *   the `ILayout` interface.
   */
  int (VO_MSE_CALL *getPenCount)(voEngine engine, voLayout target);

  /**
   * Returns an iterator over the pens of the specified layout.
   * If `id` is not `NULL`, the iterator points only to the specified pen.
   * If no pen corresponds to `id`, the iterator created is empty.
   * When corresponding page is modified, iterator will be invalidated.
   *
   * @param engine the engine.
   * @param target the target layout.
   * @param charset the charset used to encode the id.
   * @param id the identifier of the pen to retrieve.
   *
   * @return true on success, false otherwise.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` does not implement
   *   the `ILayout` interface.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `id` string is not readable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the
   *   `id` string is not readable.
   */
  voPenIterator (VO_MSE_CALL *getPens)(voEngine engine, voLayout target, voCharset charset, const voString* id);

  /**
   * Adds a new pen element to the layout.
   * If a pen with same id already exists, operation will fail.
   *
   * @param engine the engine.
   * @param target the target layout.
   * @param charset the charset used to encode the id.
   * @param id the id of the pen to create.
   * @param data the description of the pen.
   *
   * @return true on success, false otherwise.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` does not implement
   *   the `ILayout` interface.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `id` string is not readable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the
   *   `id` string is not readable.
   * @throws VO_INVALID_USER_BUFFER the `data` is not readable.
   */
  bool (VO_MSE_CALL *addPen)(voEngine engine, voLayout target, voCharset charset, const voString* id, const voPenData* data);

  /**
   * Returns the parameters of the specified transform.
   *
   * @param engine the engine.
   * @param target the target layout.
   * @param charset the charset used to encode the id.
   * @param id the id of the transform to return.
   * @param transform a recipient for the transform matrix.
   *
   * @return true on success, otherwise false.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` does not implement
   *   the `ILayout` interface.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `id` string is not readable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the
   *   `id` string is not readable.
   * @throws VO_INVALID_USER_BUFFER the `transform` is not writeable.
   */
  bool (VO_MSE_CALL *getTransform)(voEngine engine, voLayout target, voCharset charset, const voString* id, voTransform* transform);
}
voILayout;

/**
 * Functions composing the `ILayerIterator` interface. This interface exposes
 * the public methods of the `LayerIterator` type.
 * Note that layer iterators created from a `voPageSelection` are not allowed
 * to modify the layout.
 *
 * {@extends voIIterator}
 * {@implementingTypes voLayerIterator}
 * @see VO_ILayerIterator, VO_LayerIterator.
 */
typedef struct _voILayerIterator
{
  /** {@inheritDoc} */
  voYesNo (VO_MSE_CALL *isAtEnd)(voEngine engine, voIterator target);
  /** {@inheritDoc} */
  bool (VO_MSE_CALL *next)(voEngine engine, voIterator target);

  /**
   * Returns the identifier of the layer at the current step of the iteration.
   *
   * @param engine the engine.
   * @param target the target iterator.
   * @param charset the charset to be used to encode the value.
   * @param id a recipient for the value.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `LayerIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT the `target` instance is positioned at the end
   *   of the iteration.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL` and no default
   *   charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a reference to a
   *   `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `id` recipient is not readable or
   *   writable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the `id` recipient is
   *   not writable.
   */
  bool (VO_MSE_CALL *getId)(voEngine engine, voLayerIterator target, voCharset charset, voString* id);

  /**
   * Returns the background color of the layer at the current step of the
   * iteration. The default color is `0xFFFFFF00` (transparent white).
   *
   * @param engine the engine.
   * @param target the target iterator.
   * @param color the color of the background in RGBA format (32 bits).
   *
   * @return true on success, false otherwise.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `LayerIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT the `target` instance is positioned at the
   *   end of the iteration.
   * @throws VO_INVALID_USER_BUFFER the `color` recipient is not writable.
   */
  bool (VO_MSE_CALL *getBackgroundColor)(voEngine engine, voLayerIterator target, uint32_t* color);

  /**
   * Sets the background color of the layer at the current step of the iteration.
   * The default color is `0xFFFFFF00` (transparent white).
   *
   * @param engine the engine.
   * @param target the target iterator.
   * @param color the color of the background in RGBA format (32 bits).
   *
   * @return true on success, false otherwise.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `LayerIterator` instance.
   * @throws VO_INVALID_OPERATION the `target` was created from a
   *   `voPageSelection`.
   * @throws VO_NO_SUCH_ELEMENT the `target` instance is positioned at the
   *   end of the iteration.
   */
  bool (VO_MSE_CALL *setBackgroundColor)(voEngine engine, voLayerIterator target, uint32_t color);

  /**
   * Removes the layer at the current step of the iteration from the layout.
   * The iterator advances to the next iteration.
   *
   * @param engine the engine.
   * @param target the target iterator.
   *
   * @return true on success, false otherwise.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `LayerIterator` instance.
   * @throws VO_INVALID_OPERATION the `target` was created from a
   *   `voPageSelection`.
   * @throws VO_NO_SUCH_ELEMENT the `target` instance is positioned at the
   *   end of the iteration.
   */
  bool (VO_MSE_CALL *remove)(voEngine engine, voLayerIterator target);

  /**
   * Returns the number of layout items in the layer.
   *
   * @param engine the engine.
   * @param target the target iterator.
   *
   * @return the number of layout items on success, otherwise -1.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `LayerIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT the `target` instance is positioned at the
   *   end of the iteration.
   */
  int (VO_MSE_CALL *getItemCount)(voEngine engine, voLayerIterator target);

  /**
   * Returns an iterator over the layout items of the layer. When the
   * corresponding page is modified, the iterator will be invalidated.
   *
   * @param engine the engine.
   * @param target the target iterator.
   *
   * @return the layer iterator on success, otherwise `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `LayerIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT the `target` instance is positioned at the
   *   end of the iteration.
   */
  voLayoutItemIterator (VO_MSE_CALL *getItems)(voEngine engine, voLayerIterator target);

  /**
   * Adds a new item at the top of the layer.
   *
   * @param engine the engine.
   * @param target the target iterator.
   * @param data the properties of the layout item.
   *
   * @return true on success, false otherwise.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `LayerIterator` instance.
   * @throws VO_INVALID_OPERATION the `target` was created from a
   *   `voPageSelection`.
   * @throws VO_NO_SUCH_ELEMENT the `target` instance is positioned at the
   *   end of the iteration.
   * @throws VO_INVALID_USER_BUFFER the `data` parameter is not readable.
   */
  bool (VO_MSE_CALL *addItem)(voEngine engine, voLayerIterator target, const voLayoutItemData* data);
}
voILayerIterator;

/**
 * Functions composing the `IPenIterator` interface. This interface exposes the
 * public methods of the `PenIterator` type.
 *
 * {@extends voIIterator}
 * {@implementingTypes voIPenIterator}
 * @see VO_IPenIterator, VO_PenIterator.
 */
typedef struct _voIPenIterator
{
  /** {@inheritDoc} */
  voYesNo (VO_MSE_CALL *isAtEnd)(voEngine engine, voIterator target);
  /** {@inheritDoc} */
  bool (VO_MSE_CALL *next)(voEngine engine, voIterator target);

  /**
   * Returns the identifier of the pen at the current step of the iteration.
   *
   * @param engine the engine.
   * @param target the target iterator.
   * @param charset the charset to be used to encode the id.
   * @param id a recipient for the id.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to a
   *   `PenIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT the `target` instance is positioned at the end
   *   of the iteration.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL` and no default
   *   charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a reference to a
   *   `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `id` recipient is not readable or
   *   writable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the `id` recipient is
   *   not writable.
   */
  bool (VO_MSE_CALL *getId)(voEngine engine, voPenIterator target, voCharset charset, voString* id);

  /**
   * Returns the properties of the pen at the current step of the iteration.
   *
   * @param engine the engine.
   * @param target the target iterator.
   * @param data a recipient for the properties of the pen.
   *
   * @return true on success, false otherwise.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `PenIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT the `target` instance is positioned at the
   *   end of the iteration.
   * @throws VO_INVALID_USER_BUFFER the `data` recipient is not writable.
   */
  bool (VO_MSE_CALL *getData)(voEngine engine, voPenIterator target, voPenData* data);

  /**
   * Sets the properties of the pen at the current step of the iteration.
   *
   * @param engine the engine.
   * @param target the target iterator.
   * @param data the properties of the pen.
   *
   * @return true on success, false otherwise.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a reference to
   *   a `PenIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT the `target` instance is positioned at the
   *   end of the iteration.
   * @throws VO_INVALID_USER_BUFFER the `data` parameter is not readable.
   */
  bool (VO_MSE_CALL *setData)(voEngine engine, voPenIterator target, const voPenData* data);

}
voIPenIterator;

/**
 * Functions composing the `ILayoutItemIterator` interface. This interface
 * exposes the public methods of the `LayoutItemIterator` type.
 *
 * {@extends voIIterator}
 * {@implementingTypes voLayoutItemIterator}
 * @see VO_ILayoutItemIterator, VO_LayoutItemIterator.
 */
typedef struct _voILayoutItemIterator
{
  /** {@inheritDoc} */
  voYesNo (VO_MSE_CALL *isAtEnd)(voEngine engine, voIterator target);
  /** {@inheritDoc} */
  bool (VO_MSE_CALL *next)(voEngine engine, voIterator target);

  /**
   * Returns the properties of the layout item at the current step of the
   * iteration.
   *
   * @param engine the engine.
   * @param target the target iterator.
   * @param data the properties of the layout item.
   *
   * @return true on success, false otherwise.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` does not implement
   *   the `ILayoutItemIterator` interface.
   * @throws VO_NO_SUCH_ELEMENT the `target` instance is positioned at the
   *   end of the iteration.
   * @throws VO_INVALID_USER_BUFFER the `data` recipient is not writable.
   */
  bool (VO_MSE_CALL *getData)(voEngine engine, voLayoutItemIterator target, voLayoutItemData* data);

}
voILayoutItemIterator;


// -- DocumentFinder -----------------------------------------------------------

/**
 * Reference to an instance of the `DocumentFinder` type.
 *
 * {@extends voEngineObject}
 * {@implements voIDocumentFinder}
 *
 * @see VO_DocumentFinder.
 */
typedef voEngineObject voDocumentFinder;

/**
 * Reference to an instance of the `DocumentFindResult` type.
 *
 * {@extends voEngineObject}
 * {@implements voIDocumentFindResult}
 *
 * @see VO_DocumentFindResult.
 */
typedef voEngineObject voDocumentFindResult;

/**
 * Reference to an instance of the `DocumentFindOccurrenceIterator` type.
 *
 * {@extends voIterator}
 * {@implements voIDocumentFindOccurrenceIterator}
 *
 * @see VO_DocumentFindOccurrenceIterator.
 */
typedef voEngineObject voDocumentFindOccurrenceIterator;


/**
 * Lists asynchronous events of `voDocumentFinder`.
 * @see voDocumentFinderCallback.
 */
typedef enum _voDocumentFinderEvent
{
  /**
   * Indicates the worker thread started a new find process.
   */
  VO_DOCUMENT_FINDER_EVENT_START,

  /**
   * Indicates the worker thread has found new occurrences.
   */
  VO_DOCUMENT_FINDER_EVENT_NEW_OCCURRENCES,

  /**
   * Indicates the worker thread has completed the find process.
   */
  VO_DOCUMENT_FINDER_EVENT_DONE,

  /**
   * Indicates cancellation of the find process.
   */
  VO_DOCUMENT_FINDER_EVENT_CANCELLED,
}
voDocumentFinderEvent;

/**
 * Callback called by the document finder background thread upon completion of
 * asynchronous events of `voDocumentFinder`.
 *
 * <p>The objects provided in `result` are valid only during the
 * callback execution, therefore you must use `voAcquireObject()` if
 * you want to retain the object for later use.</p>
 *
 * <p>Do not call wait() from this callback, or this will result in a
 * deadlock.</p>.
 *
 * <p>Do not call other asynchronous functions from this callback (functions
 * that call a callback upon completion), prefer calling asynchronous functions
 * in sequence.</p>
 *
 * @param eventId the id of the event that occurred.
 * @param occurrenceIterator an iterator over the new occurrences, if `eventId`
 *   is `VO_EVENT_FINDER_OCCURRENCES`.
 * @param userParam the user parameter that was given.
 *
 * @see voIDocumentFinder.
 */
typedef void (VO_MSE_CALL *voDocumentFinderCallback)(voDocumentFinderEvent eventId, voDocumentFindOccurrenceIterator occurrenceIterator, void* userParam);


/**
 * Represents the parameters required to create a `voDocumentFinder` object.
 * @see voDocumentFinder, voCreateObjectEx.
 */
typedef struct _voDocumentFinderInitializer
{
  /**
   * The associated document.
   */
  voDocument document;

  /**
   * The callback used to handle the asynchronous events of the document finder.
   */
  voDocumentFinderCallback callback;

  /**
   * The user parameter sent to the callback.
   */
  void* userParam;
}
voDocumentFinderInitializer;

#ifndef VO_NO_FUNCTIONS
/**
 * Creates an instance of the `DocumentFinder` type.
 *
 * @param engine the engine.
 * @param document the document to search in.
 * @param callback the callback that will receive worker thread events.
 * @param userParam a parameter that will be passed to the callback.
 *
 * @return A reference to the newly created `DocumentFinder` object on success,
 *   otherwise `NULL`.
 *
 * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
 * @throws VO_NO_SUCH_OBJECT the `document` reference is invalid.
 * @throws VO_LIMIT_EXCEEDED the number of `DocumentFinder`
 *   instances would exceed the allowed limit (please remember that the limit
 *   can be shared among several types).
 * @throws VO_OUT_OF_MEMORY not enough memory to create the object.
 */
VO_INLINE voDocumentFinder voCreateDocumentFinder(voEngine engine, voDocument document, voDocumentFinderCallback callback, void* userParam)
{
  voDocumentFinderInitializer initializer = { document, callback, userParam };
  return voCreateObjectEx(engine, VO_DocumentFinder, &initializer, sizeof(initializer));
}
#endif // end of: #ifndef VO_NO_FUNCTIONS

/**
 * Functions composing the `IDocumentFinder` interface. This interface
 * exposes the public methods of the `DocumentFinder` type.
 *
 * {@implementingTypes voDocumentFinder}
 * @see VO_IDocumentFinder, VO_DocumentFinder.
 */
typedef struct _voIDocumentFinder
{
  /**
   * Launches a find process with the specified query.
   *
   * @param engine the engine.
   * @param target the target document finder.
   * @param query the query to search for.
   */
  bool (VO_MSE_CALL *process)(voEngine engine, voDocumentFinder target, voQuery query);

  /**
   * Returns the result of a find process.
   *
   * @param engine the engine.
   * @param target the target document finder.
   * @param wait whether to wait for the result to be available.
   */
  voDocumentFindResult (VO_MSE_CALL *getResult)(voEngine engine, voDocumentFinder target, bool wait);

  /**
   * Requests cancellation of an ongoing find process.
   *
   * @param engine the engine.
   * @param target the target document finder.
   */
  bool (VO_MSE_CALL *cancel)(voEngine engine, voDocumentFinder target);
}
voIDocumentFinder;


/**
 * Functions composing the `IDocumentFindResult` interface. This interface
 * exposes the public methods of the `DocumentFindResult` type.
 *
 * {@implementingTypes voDocumentFindResult}
 * @see VO_IDocumentFindResult, VO_DocumentFindResult.
 */
typedef struct _voIDocumentFindResult
{
  /**
   * Returns an iterator over the occurrences that compose the target find
   * result.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to a `DocumentFindResult` instance.
   *
   * @return an `DocumentOccurrenceIterator` instance on success, otherwise
   *   `NULL`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to a `DocumentFindResult` instance.
   * @throws VO_OUT_OF_MEMORY not enough memory to create the
   *   `DocumentOccurrenceIterator` instance.
   * @throws VO_LIMIT_EXCEEDED the number of `DocumentOccurrenceIterator`
   *   instances would exceed the allowed limit (please remember that the limit
   *   can be shared among several types).
   */
  voDocumentFindOccurrenceIterator (VO_MSE_CALL *getOccurrences)(voEngine engine, voDocumentFindResult target);
}
voIDocumentFindResult;


/**
 * Functions composing the `IDocumentFindOccurrenceIterator` interface. This
 * interface exposes the public methods of the `DocumentFindOccurrenceIterator`
 * type.
 *
 * {@extends voIIterator}
 * {@implementingTypes voDocumentOccurrenceIterator}
 * @see VO_IDocumentFindOccurrenceIterator, VO_DocumentFindOccurrenceIterator.
 *
 * @note As the C language does not provide any mechanism that could be used to
 *   simulate inheritance, inherited members are simply copied from the base
 *   structure.
 */
typedef struct _voIDocumentFindOccurrenceIterator
{
  /** {@inheritDoc} */
  voYesNo (VO_MSE_CALL *isAtEnd)(voEngine engine, voIterator target);
  /** {@inheritDoc} */
  bool (VO_MSE_CALL *next)(voEngine engine, voIterator target);

  /**
   * Returns the identifier of the page that contains the occurrence at the
   * current step of the iteration.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `DocumentOccurrenceIterator` instance.
   * @param charset Reference to the `Charset` instance to be used
   *   to convert the MyScript internal characters into a character string.
   * @param string Recipient for the page identifier.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to an `DocumentOccurrenceIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT the iterator is positioned at the end of the
   *   iteration.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `string` recipient is not readable or
   *   writable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the `string`
   * recipient is not writable.
   */
  bool (VO_MSE_CALL *getPageId)(voEngine engine, voDocumentFindOccurrenceIterator target, voCharset charset, voString* string);

  /**
   * Returns the identifier of the indexed field that contains the occurrence at
   * the current step of the iteration.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `DocumentOccurrenceIterator` instance.
   * @param charset Reference to the `Charset` instance to be used
   *   to convert the MyScript internal characters into a character string.
   * @param string Recipient for the page identifier.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to an `DocumentOccurrenceIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT the iterator is positioned at the end of the
   *   iteration.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `string` recipient is not readable or
   *   writable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the `string`
   * recipient is not writable.
   */
  bool (VO_MSE_CALL *getFieldId)(voEngine engine, voDocumentFindOccurrenceIterator target, voCharset charset, voString* string);

  /**
   * Returns the string representation of the ink segment of the occurrence at
   * the current step of the iteration.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `DocumentOccurrenceIterator` instance.
   * @param charset Reference to the `Charset` instance to be used
   *   to convert the MyScript internal characters into a character string.
   * @param string Recipient for the string representation.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to an `DocumentOccurrenceIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT the iterator is positioned at the end of the
   *   iteration.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `string` recipient is not readable or
   *   writable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the `string`
   * recipient is not writable.
   */
  bool (VO_MSE_CALL *getInkSegment)(voEngine engine, voDocumentFindOccurrenceIterator target, voCharset charset, voString* string);

  /**
   * Returns the label of the occurrence at the current step of the iteration.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `DocumentOccurrenceIterator` instance.
   * @param charset Reference to the `Charset` instance to be used
   *   to convert the MyScript internal characters into a character string.
   * @param string Recipient for the label.
   *
   * @return `true` on success, otherwise `false`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to an `DocumentOccurrenceIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT the iterator is positioned at the end of the
   *   iteration.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `charset` reference is `NULL`
   *   and no default charset was set.
   * @throws VO_INVALID_OBJECT the `charset` reference is not a
   *   reference to a `Charset` instance.
   * @throws VO_INVALID_USER_BUFFER the `string` recipient is not readable or
   *   writable.
   * @throws VO_INVALID_USER_BUFFER the `bytes` member of the `string`
   * recipient is not writable.
   */
  bool (VO_MSE_CALL *getLabel)(voEngine engine, voDocumentFindOccurrenceIterator target, voCharset charset, voString* string);

  /**
   * Returns the score of the occurrence at the current step of the iteration.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `DocumentOccurrenceIterator` instance.
   *
   * @return the score of this occurrence on success, otherwise
   *   `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to an `DocumentOccurrenceIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT the iterator is positioned at the end of the
   *   iteration.
   */
  float (VO_MSE_CALL *getScore)(voEngine engine, voDocumentFindOccurrenceIterator target);

  /**
   * Returns the index of the matched query for the occurrence at the current
   * step of the iteration.
   *
   * @param engine Reference to an `Engine` instance.
   * @param target Reference to an `DocumentOccurrenceIterator` instance.
   *
   * @return the zero-based index of the matched query on success, otherwise
   *   `-1`.
   *
   * @throws VO_NO_SUCH_ENGINE the `engine` reference is invalid.
   * @throws VO_NO_SUCH_OBJECT the `target` reference is invalid.
   * @throws VO_INVALID_OPERATION the `target` reference is not a
   *   reference to an `DocumentOccurrenceIterator` instance.
   * @throws VO_NO_SUCH_ELEMENT the iterator is positioned at the end of the
   *   iteration.
   */
  int (VO_MSE_CALL *getQueryIndex)(voEngine engine, voDocumentFindOccurrenceIterator target);
}
voIDocumentFindOccurrenceIterator;

#endif // end of: #ifndef C_MYSCRIPTDOCUMENT_H
