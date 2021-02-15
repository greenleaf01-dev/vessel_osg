/**
 * @file MyScriptEngine-strtype.c
 *
 */

#include "MyScriptEngine-strtype.h"
#include <c/MyScriptEngine.h>
#include <c/MyScriptInk.h>
#include <c/MyScriptHWR.h>
#include <c/MyScriptInkSearch.h>
#include <c/MyScriptTrainer.h>
#include <c/MyScriptShape.h>
#include <c/MyScriptEquation.h>
#include <c/MyScriptAnalyzer.h>
#include <c/MyScriptPrediction.h>
#include <c/MyScriptDocument.h>
#include <c/MyScriptJSON.h>
#include <c/MyScriptWriterAdaptation.h>
#include <c/MyScriptMusic.h>


char const* strMyScriptType(voTypeId typeId)
{
#define __CASE_FROM_TYPE(x) case VO_##x: return #x
  switch (typeId)
  {
#ifdef C_MYSCRIPTENGINE_H
  __CASE_FROM_TYPE(Engine);
  __CASE_FROM_TYPE(EngineObject);
  __CASE_FROM_TYPE(Iterator);
  __CASE_FROM_TYPE(Charset);
  __CASE_FROM_TYPE(Input);
  __CASE_FROM_TYPE(StructuredInput);
  __CASE_FROM_TYPE(FloatStructuredInput);
  __CASE_FROM_TYPE(InputCharacter);
  __CASE_FROM_TYPE(HistoryManager);
  __CASE_FROM_TYPE(UserObject);
  __CASE_FROM_TYPE(IIterator);
  __CASE_FROM_TYPE(ICharset);
  __CASE_FROM_TYPE(IAttachTarget);
  __CASE_FROM_TYPE(ICompilable);
  __CASE_FROM_TYPE(IInput);
  __CASE_FROM_TYPE(IStructuredInput);
  __CASE_FROM_TYPE(IFloatStructuredInput);
  __CASE_FROM_TYPE(IInputConsumer);
  __CASE_FROM_TYPE(IRunnable);
  __CASE_FROM_TYPE(IInkTransmitter);
  __CASE_FROM_TYPE(IInputCharacter);
  __CASE_FROM_TYPE(IHistoryManager);
  __CASE_FROM_TYPE(IVersionable);
  __CASE_FROM_TYPE(IUserObject);
#endif // end of: #ifdef C_MYSCRIPTENGINE_H

#ifdef C_MYSCRIPTINK_H
  __CASE_FROM_TYPE(InkStrokeFormat);
  __CASE_FROM_TYPE(InkStrokeFormatBuilder);
  __CASE_FROM_TYPE(InkStroke);
  __CASE_FROM_TYPE(InkStrokeBuilder);
  __CASE_FROM_TYPE(Ink);
  __CASE_FROM_TYPE(InkIntervals);
  __CASE_FROM_TYPE(InkSegment);
  __CASE_FROM_TYPE(InkSelection);
  __CASE_FROM_TYPE(InkTagIterator);
  __CASE_FROM_TYPE(Glyph);
  __CASE_FROM_TYPE(ArcPrimitive);
  __CASE_FROM_TYPE(LinePrimitive);
  __CASE_FROM_TYPE(ISelectionChangeListener);
  __CASE_FROM_TYPE(ISelection);
  __CASE_FROM_TYPE(IInkStrokeFormat);
  __CASE_FROM_TYPE(IInkStrokeFormatBuilder);
  __CASE_FROM_TYPE(IInkStroke);
  __CASE_FROM_TYPE(IInkStrokeBuilder);
  __CASE_FROM_TYPE(IInk);
  __CASE_FROM_TYPE(IInkIntervals);
  __CASE_FROM_TYPE(IInkStrokeSet);
  __CASE_FROM_TYPE(IInkSelection);
  __CASE_FROM_TYPE(IGeometry);
  __CASE_FROM_TYPE(IInkTagIterator);
  __CASE_FROM_TYPE(IInkUpdateListener);
  __CASE_FROM_TYPE(IGlyph);
  __CASE_FROM_TYPE(IPrimitive);
#endif // end of: #ifdef C_MYSCRIPTINK_H

#ifdef C_MYSCRIPTHWR_H
  __CASE_FROM_TYPE(HandwritingContext);
  __CASE_FROM_TYPE(Recognizer);
  __CASE_FROM_TYPE(StructuredInputRecognizer);
  __CASE_FROM_TYPE(TextRecognizer);
  __CASE_FROM_TYPE(DigitalTextMatcher);
  __CASE_FROM_TYPE(Resource);
  __CASE_FROM_TYPE(AlphabetKnowledge);
  __CASE_FROM_TYPE(CursiveAlphabetKnowledge);
  __CASE_FROM_TYPE(HandPrintedAlphabetKnowledge);
  __CASE_FROM_TYPE(IsolatedAlphabetKnowledge);
  __CASE_FROM_TYPE(LinguisticKnowledge);
  __CASE_FROM_TYPE(Vocabulary);
  __CASE_FROM_TYPE(LexicalUnit);
  __CASE_FROM_TYPE(Lexicon);
  __CASE_FROM_TYPE(Grammar);
  __CASE_FROM_TYPE(SubsetKnowledge);
  __CASE_FROM_TYPE(Archive);
  __CASE_FROM_TYPE(WordIterator);
  __CASE_FROM_TYPE(RecognitionResult);
  __CASE_FROM_TYPE(CandidateIterator);
  __CASE_FROM_TYPE(SegmentIterator);
  __CASE_FROM_TYPE(DigitalInkTagger);
  __CASE_FROM_TYPE(TagList);
  __CASE_FROM_TYPE(TagIterator);
  __CASE_FROM_TYPE(ILexicalUnit);
  __CASE_FROM_TYPE(ILexicon);
  __CASE_FROM_TYPE(ISubsetKnowledge);
  __CASE_FROM_TYPE(IWordIterator);
  __CASE_FROM_TYPE(IRecognitionResult);
  __CASE_FROM_TYPE(ICandidateIterator);
  __CASE_FROM_TYPE(ISegmentIterator);
  __CASE_FROM_TYPE(IDigitalTextMatcher);
  __CASE_FROM_TYPE(IAlphabet);
  __CASE_FROM_TYPE(IRecognitionResultProvider);
  __CASE_FROM_TYPE(IDigitalInkTagger);
  __CASE_FROM_TYPE(ITagList);
  __CASE_FROM_TYPE(ITagIterator);
#endif // end of: #ifdef C_MYSCRIPTHWR_H

#ifdef C_MYSCRIPTINKSEARCH_H
  __CASE_FROM_TYPE(Indexer);
  __CASE_FROM_TYPE(StructuredInputIndexer);
  __CASE_FROM_TYPE(StructuredInputSlimIndexer);
  __CASE_FROM_TYPE(Index);
  __CASE_FROM_TYPE(Query);
  __CASE_FROM_TYPE(VocabularyQuery);
  __CASE_FROM_TYPE(StringQuery);
  __CASE_FROM_TYPE(OrQuery);
  __CASE_FROM_TYPE(AndQuery);
  __CASE_FROM_TYPE(AndNotQuery);
  __CASE_FROM_TYPE(NearQuery);
  __CASE_FROM_TYPE(Finder);
  __CASE_FROM_TYPE(FindResult);
  __CASE_FROM_TYPE(OccurrenceIterator);
  __CASE_FROM_TYPE(OccurrenceCharacterIterator);
  __CASE_FROM_TYPE(TextIndexer);
  __CASE_FROM_TYPE(IIndexingResultProvider);
  __CASE_FROM_TYPE(IFindResultProvider);
  __CASE_FROM_TYPE(IFindResult);
  __CASE_FROM_TYPE(IOccurrenceIterator);
  __CASE_FROM_TYPE(IOccurrenceCharacterIterator);
#endif // end of: #ifdef C_MYSCRIPTINKSEARCH_H

#ifdef C_MYSCRIPTTRAINER_H
  __CASE_FROM_TYPE(TrainingSet);
  __CASE_FROM_TYPE(TrainingSetExtractor);
  __CASE_FROM_TYPE(TrainingInformationSet);
  __CASE_FROM_TYPE(AdvancedTrainer);
  __CASE_FROM_TYPE(ITrainingResultProvider);
  __CASE_FROM_TYPE(ITrainingSet);
  __CASE_FROM_TYPE(ITrainingSetExtractor);
#endif // end of: #ifdef C_MYSCRIPTTRAINER_H

#ifdef C_MYSCRIPTSHAPE_H
  __CASE_FROM_TYPE(ShapeModel);
  __CASE_FROM_TYPE(ShapeKnowledge);
  __CASE_FROM_TYPE(ShapeRecognizer);
  __CASE_FROM_TYPE(ShapeBeautifier);
  __CASE_FROM_TYPE(ShapeDocument);
  __CASE_FROM_TYPE(ShapePrimitive);
  __CASE_FROM_TYPE(ShapeLine);
  __CASE_FROM_TYPE(ShapeDecoratedLine);
  __CASE_FROM_TYPE(ShapeEllipticArc);
  __CASE_FROM_TYPE(ShapeDecoratedEllipticArc);
  __CASE_FROM_TYPE(ShapeSegment);
  __CASE_FROM_TYPE(ShapeCandidate);
  __CASE_FROM_TYPE(ShapeRecognized);
  __CASE_FROM_TYPE(ShapeScratchOut);
  __CASE_FROM_TYPE(ShapeErased);
  __CASE_FROM_TYPE(ShapeRejected);
  __CASE_FROM_TYPE(ShapeHistoryManager);
  __CASE_FROM_TYPE(IShapeModel);
  __CASE_FROM_TYPE(IShapeKnowledge);
  __CASE_FROM_TYPE(IShapeRecognizer);
  __CASE_FROM_TYPE(IShapeDocument);
  __CASE_FROM_TYPE(IShapeLine);
  __CASE_FROM_TYPE(IShapeDecoratedLine);
  __CASE_FROM_TYPE(IShapeEllipticArc);
  __CASE_FROM_TYPE(IShapeDecoratedEllipticArc);
  __CASE_FROM_TYPE(IShapeSegment);
  __CASE_FROM_TYPE(IShapeRecognized);
  __CASE_FROM_TYPE(IShapeScratchOut);
  __CASE_FROM_TYPE(IShapeDocumentProcessor);
  __CASE_FROM_TYPE(IShapeHistoryManager);
#endif // end of: #ifdef C_MYSCRIPTSHAPE_H

#ifdef C_MYSCRIPTEQUATION_H
  __CASE_FROM_TYPE(Equation);
  __CASE_FROM_TYPE(EquationAlphabetKnowledge);
  __CASE_FROM_TYPE(EquationGrammar);
  __CASE_FROM_TYPE(EquationRecognizer);
  __CASE_FROM_TYPE(EquationNode);
  __CASE_FROM_TYPE(EquationTerminalNode);
  __CASE_FROM_TYPE(EquationNonTerminalNode);
  __CASE_FROM_TYPE(EquationRuleNode);
  __CASE_FROM_TYPE(EquationScratchOut);
  __CASE_FROM_TYPE(IEquation);
  __CASE_FROM_TYPE(IEquationAlphabet);
  __CASE_FROM_TYPE(IEquationGrammar);
  __CASE_FROM_TYPE(IEquationRecognizer);
  __CASE_FROM_TYPE(IEquationTerminalNode);
  __CASE_FROM_TYPE(IEquationNonTerminalNode);
  __CASE_FROM_TYPE(IEquationRuleNode);
  __CASE_FROM_TYPE(IEquationScratchOut);
#endif // end of: #ifdef C_MYSCRIPTEQUATION_H

#ifdef C_MYSCRIPTANALYZER_H
  __CASE_FROM_TYPE(Analyzer);
  __CASE_FROM_TYPE(AnalyzerDocument);
  __CASE_FROM_TYPE(AnalyzerKnowledge);
  __CASE_FROM_TYPE(AnalyzerElement);
  __CASE_FROM_TYPE(AnalyzerUnderline);
  __CASE_FROM_TYPE(AnalyzerTextLine);
  __CASE_FROM_TYPE(AnalyzerLine);
  __CASE_FROM_TYPE(AnalyzerCell);
  __CASE_FROM_TYPE(AnalyzerTable);
  __CASE_FROM_TYPE(AnalyzerShape);
  __CASE_FROM_TYPE(AnalyzerGroup);
  __CASE_FROM_TYPE(IAnalyzerDocument);
  __CASE_FROM_TYPE(IAnalyzerDocumentProcessor);
  __CASE_FROM_TYPE(IAnalyzerUnderline);
  __CASE_FROM_TYPE(IAnalyzerTextLine);
  __CASE_FROM_TYPE(IAnalyzerLine);
  __CASE_FROM_TYPE(IAnalyzerCell);
  __CASE_FROM_TYPE(IAnalyzerTable);
  __CASE_FROM_TYPE(IAnalyzerShape);
  __CASE_FROM_TYPE(IAnalyzerGroup);
#endif // end of: #ifdef C_MYSCRIPTANALYZER_H

#ifdef C_MYSCRIPTPREDICTION_H
  __CASE_FROM_TYPE(Predictor);
#endif // end of: #ifdef C_MYSCRIPTPREDICTION_H

#ifdef C_MYSCRIPTDOCUMENT_H
  __CASE_FROM_TYPE(Document);
  __CASE_FROM_TYPE(Page);
  __CASE_FROM_TYPE(PageSelection);
  __CASE_FROM_TYPE(Content);
  __CASE_FROM_TYPE(ContentField);
  __CASE_FROM_TYPE(Layout);
  __CASE_FROM_TYPE(LayerIterator);
  __CASE_FROM_TYPE(PenIterator);
  __CASE_FROM_TYPE(LayoutItemIterator);
  __CASE_FROM_TYPE(DocumentFinder);
  __CASE_FROM_TYPE(DocumentFindResult);
  __CASE_FROM_TYPE(DocumentFindOccurrenceIterator);
  __CASE_FROM_TYPE(ObjectIterator);
  __CASE_FROM_TYPE(IDocument);
  __CASE_FROM_TYPE(IPage);
  __CASE_FROM_TYPE(IPageSelection);
  __CASE_FROM_TYPE(IContent);
  __CASE_FROM_TYPE(IContentField);
  __CASE_FROM_TYPE(ILayout);
  __CASE_FROM_TYPE(ILayerIterator);
  __CASE_FROM_TYPE(IPenIterator);
  __CASE_FROM_TYPE(ILayoutItemIterator);
  __CASE_FROM_TYPE(IPageUpdateListener);
  __CASE_FROM_TYPE(IContentFieldProcessor);
  __CASE_FROM_TYPE(IDocumentFinder);
  __CASE_FROM_TYPE(IDocumentFindResult);
  __CASE_FROM_TYPE(IDocumentFindOccurrenceIterator);
  __CASE_FROM_TYPE(IObjectIterator);
  __CASE_FROM_TYPE(IExtentProvider);
#endif // end of: #ifdef C_MYSCRIPTDOCUMENT_H

#ifdef C_MYSCRIPTJSON_H
  __CASE_FROM_TYPE(Json);
  __CASE_FROM_TYPE(JsonObjectIterator);
  __CASE_FROM_TYPE(IJson);
  __CASE_FROM_TYPE(IJsonObjectIterator);
#endif // end of: #ifdef C_MYSCRIPTJSON_H

#ifdef C_MYSCRIPTWRITERADAPTATION_H
  __CASE_FROM_TYPE(WriterAdaptationCollector);
  __CASE_FROM_TYPE(WriterAdaptationProfile);
  __CASE_FROM_TYPE(WriterAdaptationTrainer);
  __CASE_FROM_TYPE(IWriterAdaptationCollector);
#endif // end of: #ifdef C_MYSCRIPTWRITERADAPTATION_H

#ifdef C_MYSCRIPTMUSIC_H
  __CASE_FROM_TYPE(MusicDocument);
  __CASE_FROM_TYPE(MusicAlphabetKnowledge);
  __CASE_FROM_TYPE(MusicGrammar);
  __CASE_FROM_TYPE(MusicRecognizer);
  __CASE_FROM_TYPE(MusicScore);
  __CASE_FROM_TYPE(MusicPart);
  __CASE_FROM_TYPE(MusicElement);
  __CASE_FROM_TYPE(MusicArticulationMark);
  __CASE_FROM_TYPE(MusicBar);
  __CASE_FROM_TYPE(MusicClef);
  __CASE_FROM_TYPE(MusicAccidental);
  __CASE_FROM_TYPE(MusicKeySignature);
  __CASE_FROM_TYPE(MusicAnnotation);
  __CASE_FROM_TYPE(MusicTimeSignature);
  __CASE_FROM_TYPE(MusicNote);
  __CASE_FROM_TYPE(MusicHead);
  __CASE_FROM_TYPE(MusicStem);
  __CASE_FROM_TYPE(MusicBeam);
  __CASE_FROM_TYPE(MusicDots);
  __CASE_FROM_TYPE(MusicTie);
  __CASE_FROM_TYPE(MusicSlur);
  __CASE_FROM_TYPE(MusicLedgerLine);
  __CASE_FROM_TYPE(MusicRest);
  __CASE_FROM_TYPE(MusicChord);
  __CASE_FROM_TYPE(MusicScratchOut);
  __CASE_FROM_TYPE(IMusicDocument);
  __CASE_FROM_TYPE(IMusicGrammar);
  __CASE_FROM_TYPE(IMusicRecognizer);
  __CASE_FROM_TYPE(IMusicScore);
  __CASE_FROM_TYPE(IMusicPart);
  __CASE_FROM_TYPE(IMusicElement);
  __CASE_FROM_TYPE(IMusicArticulationMark);
  __CASE_FROM_TYPE(IMusicBar);
  __CASE_FROM_TYPE(IMusicClef);
  __CASE_FROM_TYPE(IMusicAccidental);
  __CASE_FROM_TYPE(IMusicKeySignature);
  __CASE_FROM_TYPE(IMusicAnnotation);
  __CASE_FROM_TYPE(IMusicTimeSignature);
  __CASE_FROM_TYPE(IMusicNote);
  __CASE_FROM_TYPE(IMusicHead);
  __CASE_FROM_TYPE(IMusicStem);
  __CASE_FROM_TYPE(IMusicBeam);
  __CASE_FROM_TYPE(IMusicDots);
  __CASE_FROM_TYPE(IMusicTie);
  __CASE_FROM_TYPE(IMusicSlur);
  __CASE_FROM_TYPE(IMusicRest);
  __CASE_FROM_TYPE(IMusicChord);
  __CASE_FROM_TYPE(IMusicScratchOut);
#endif // end of: #ifdef C_MYSCRIPTMUSIC_H


  default:
    return "<<UNKNOWN - update strMyScriptType implementation>>";
  }
#undef __CASE_FROM_TYPE
}
