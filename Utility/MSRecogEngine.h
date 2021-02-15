#ifndef MSRECONGNITION
#define MSRECONGNITION
#ifdef WIN32
#include <atlbase.h> 
#include "RecogEngine.h"
#include "utility_global.h"

const long mc_lNumResults = 5;	// the maximum number of alternates we're interested in

//////////////////////////////////////////////////////////////////////////
class IInkDisp;
class IInkStrokes;
class IInkRecognizer;
class IInkRecognizers;
class IInkRecognizerContext;
class IInkRecognitionResult;
class IInkRecognitionAlternates;

class CMSRecogEngine : public CRecogEngine
{
public:
	CMSRecogEngine();
	virtual ~CMSRecogEngine();

public:
	// Automation API interface pointers
	CComPtr<IInkDisp>               m_spIInkDisp;
	CComPtr<IInkRecognizers>        m_spIInkRecognizers;
	CComPtr<IInkRecognizerContext>  m_spIInkRecogContext;

	// Helper data members
	HRESULT m_hCoInitialize;
public:
	virtual eRecogEngineType GetEngineType(){ return eMSType; }
	virtual void	SetRecogLanguage(WORD wRecogLangID);
	virtual QString	Recognize(TInputStrokes* pStrokes);
	virtual BOOL	Recognize(TInputStrokes* pStrokes, TCandidates* pCandidates);

public:
	BOOL InitEngine();
	BOOL ExitEngine();

protected:
	// Helper methods
	bool CreateRecogContext(IInkRecognizer* pIInkRecognizer);
	bool CreateInkStroke(TInputStroke* pInputStroke);
	bool GetRecognitionAlternates(TCandidate& rCandidate, IInkRecognitionAlternates* pIInkRecogAlternates, long maximumAlternates = -1);
	bool GetRecogAlternatesFromSelection(TCandidate& rCandidate, IInkRecognitionResult* pIInkRecogResult, long selectionStart, long selectionLength, long maximumAlternates);
	int  GetRecogAlternatesWord(IInkRecognitionResult* pIInkRecogResult, TCandidates* pCandidates);
	int  GetRecogAlternatesChar(IInkRecognitionResult* pIInkRecogResult, TCandidates* pCandidates);

};
#endif
#endif