#ifndef HVORECOGENGINE_H
#define HVORECOGENGINE_H

#ifndef USING_IMPORT_LIB
#define VO_MSE_FUNC_THROUGH_POINTERS /* because we want dynamic linking */
#endif

#include "c/MyScriptEngine.h"
//#include "VO\edk\C\include\c\MyScriptEngine.h"
#include "c/MyScriptHWR.h"
#include <QLibrary>
#include "RecogEngine.h"
#include "utility_global.h"

#define VO_OPEN_SURROUNDING			"\xF3\xB0\x80\x80"
#define VO_CLOSE_SURROUNDING		"\xF3\xB0\x80\x81"
#define VO_GESTURE_LEFT				"\xF3\xB0\x80\x82"
#define VO_GESTURE_RIGHT			"\xF3\xB0\x80\x83"
#define VO_GESTURE_DOWN_THEN_LEFT	"\xF3\xB0\x80\x84"

class CVORecogEngine : public CRecogEngine
{
public:
	CVORecogEngine();
	virtual ~CVORecogEngine();
public:
	virtual eRecogEngineType  GetEngineType(){ return eFranceType; }
	virtual void  SetRecogLanguage(unsigned short wRecogLangID);
	virtual QString	Recognize(TInputStrokes* pStrokes);
	virtual BOOL	Recognize(TInputStrokes* pStrokes, TCandidates* pCandidates);

protected:
	BOOL InitEngine();
	BOOL ExitEngine();
	voEngineObject LoadEngineObject(QString lpstrObjName);
	BOOL LoadMyScriptEngine();
	void UnloadMyScriptEngine();
	void SetProperty();
	int FuelingInput(TInputStrokes& Strokes, BOOL bClearFirst);

	int  GetSegmentCandidates(voSegmentIterator segment, TCandidate& rCandidate);
	int  GetSegmentsCandidates(voSegmentIterator segments, TCandidates& pCandidates);
	BOOL RecognizeWord(voCandidateIterator textCandidate, TCandidates& pCandidates);
	BOOL RecognizeChar(voCandidateIterator textCandidate, TCandidates& pCandidates);
	QString DoRecognizeAK();
	QString DoRecognizeAKLK();
	char* getCandidateLabel(voCandidateIterator candidate);
	voCandidateIterator getSelectedCandidate(voSegmentIterator segment);
	BOOL AttachResource();
	void ReleaseResource();
	uint32_t moveIterator(voIterator iterator, uint32_t count)
	{
		uint32_t i;
		//verifyEx(iterator != NULL, "invalid iterator");
		//verifyEx(count >= 0, "invalid count");

		for (i = 0; (i < count) && !VO_IFACE(m_voEngine, IIterator)->isAtEnd(m_voEngine, iterator); ++i)
			VO_IFACE(m_voEngine, IIterator)->next(m_voEngine, iterator);

		return i;
	}
protected:
	QLibrary               m_hMyScriptEngine;
	voEngine						m_voEngine;
	voCharset						m_voCharset;
	voFloatStructuredInput		    m_voFloatStructuredInput;
	voStructuredInputRecognizer	    m_voStructuredInputRecognizer;
	voResource						m_voResourceAK;
	voResource						m_voResourceLK;
	QString  m_strResourcePath;

	QString AK_RES;//Path to the alphabet knowledge resource
	QString LK_RES;//Path to the linguistic knowledge resource.
};
#endif
