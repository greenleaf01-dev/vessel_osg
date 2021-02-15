#include "VORecogEngine.h"
#include "HZRecog.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////////
/* -- configuration --------------------------------------------------------- */


/*
* 1.2) Define the path to the MyScript Engine library
*/
#define MYSCRIPT_ENGINE_LIBRARY "${origin}"

/*
* 1.3) Include the MyScriptEngine dynamic linking helper source file
*/
#include "../src/MyScriptEngine-dlHelper.c"

/*
* 1.4) Include the certificate
*      CAUTION: This file must first be created by using certificate2src.
*      NOTE: In C examples, the certificate is automatically generated at build
*            time.
*/
#include "./VO/certificates/MyCertificate.h"

/*
* 1.5) Include the MyScriptEngine error utility
*/
#include "../src/MyScriptEngine-strerror.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

static size_t readFuncFILE(void* buffer, size_t bufferLength, void* userParam)
{
	return fread(buffer, 1, bufferLength, (FILE*)userParam);
}

static bool isGesture(char* label)
{
	return strcmp(label, VO_GESTURE_LEFT) == 0 ||
		strcmp(label, VO_GESTURE_RIGHT) == 0 ||
		strcmp(label, VO_GESTURE_DOWN_THEN_LEFT) == 0;
}

static  bool isSurroundChar(char* label)
{
	return strstr(label, VO_OPEN_SURROUNDING) != NULL &&
		strstr(label, VO_CLOSE_SURROUNDING) != NULL;
}

static bool isSpace(char* label)
{
	//verifyEx(label != NULL, "invalid label");
	return strcmp(label, "") == 0 || strcmp(label, " ") == 0 || strcmp(label, "\xA0") == 0;
}
CVORecogEngine::CVORecogEngine()
{
	//TTQX-zhaozhengze-添加手写识别引擎-缺陷
	m_strResourcePath = s_strFilePath + "resources\\";
	m_voEngine = NULL;
	m_voStructuredInputRecognizer = NULL;
	m_voFloatStructuredInput = NULL;
	m_voCharset = NULL;
	m_voResourceAK = NULL;
	m_voResourceLK = NULL; 
	m_bEnable = InitEngine();
}
CVORecogEngine::~CVORecogEngine()
{
	m_bEnable = FALSE;
	ExitEngine();
}


BOOL CVORecogEngine::ExitEngine()
{
	/*****************************************************************************
	* <p>Each <code>EngineObject</code> is associated with a specific
	* <code>Engine</code>, which can be viewed as its parent.</p>
	*
	* <p>Remember that when you destroy a parent <code>Engine</code>, all its
	* children are released.</p>
	******************************************************************************/
	RE_VERIFY_EXECUTE(m_voEngine, voDestroyEngine(m_voEngine));
	UnloadMyScriptEngine();

	m_voEngine = NULL;
	m_voCharset = NULL;
	m_voResourceAK = NULL;
	m_voResourceLK = NULL;
	m_voFloatStructuredInput = NULL;
	m_voStructuredInputRecognizer = NULL;

	return TRUE;
}

int  CVORecogEngine::GetSegmentCandidates(voSegmentIterator segment, TCandidate& rCandidate)
{
	RE_VERIFY_RETURN(0, (segment && m_voEngine));
	//////////////////////////////////////////////////////////////////////////
	const voICandidateIterator* pICandidateIterator = VO_IFACE(m_voEngine, ICandidateIterator);
	const voISegmentIterator* pISegmentIterator = VO_IFACE(m_voEngine, ISegmentIterator);
	//////////////////////////////////////////////////////////////////////////
	/// retrieving the candidates of the segment or retrieving the first candidate of the segment 
	voCandidateIterator candidate = pISegmentIterator->getCandidates(m_voEngine, segment);
	/// retrieving the selected candidate index of the segment
	uint32_t selectedCandidateIndex = pISegmentIterator->getSelectedCandidateIndex(m_voEngine, segment);
	uint32_t candidateIndex = 0;
	int candidateCount = 0;
	QString strCandidates;
	/// retrieving the candidate list for the segment
	while (!pICandidateIterator->isAtEnd(m_voEngine, candidate))
	{
		char* label = getCandidateLabel(candidate);
		if (!isGesture(label) && !isSurroundChar(label))
		{
			if (!isSpace(label))
			{
				QString lpWideCharStr = label;
				
				if (candidateIndex == selectedCandidateIndex)
				{
					strCandidates = lpWideCharStr + (HWR_RESULT_SPLIT + strCandidates);
				}
				else
				{	
					strCandidates += lpWideCharStr + HWR_RESULT_SPLIT;
				}
				++candidateCount;
			}
		}

		free(label);
		++candidateIndex;
		pICandidateIterator->next(m_voEngine, candidate);
	}

	voReleaseObject(m_voEngine, candidate);

	if (candidateCount > 0)//!strCandidates.IsEmpty()
	{
		voInputRange inputRange = { NULL, 0 };
		pISegmentIterator->getInputRange(m_voEngine, segment, &inputRange);
		inputRange.elements = (voInputRangeElement*)malloc(sizeof(*inputRange.elements)*inputRange.count);
		pISegmentIterator->getInputRange(m_voEngine, segment, &inputRange);

		rCandidate.text = strCandidates;
		rCandidate.first = ((voInputRangeElement*)inputRange.elements)[0].first.componentIndex;
		rCandidate.last = ((voInputRangeElement*)inputRange.elements)[inputRange.count - 1].last.componentIndex;
		free(inputRange.elements);
	}

	return candidateCount;
}


void CVORecogEngine::ReleaseResource()
{
	RE_VERIFY_RETURN0(m_voEngine);
	// detaching the linguistic knowledge resource from the recognizer
	RE_VERIFY_EXECUTE(m_voResourceLK, VO_IFACE(m_voEngine, IAttachTarget)->detach(m_voEngine, m_voStructuredInputRecognizer, m_voResourceLK));
	RE_VERIFY_EXECUTE(m_voResourceAK, voReleaseObject(m_voEngine, m_voResourceAK));
	RE_VERIFY_EXECUTE(m_voResourceLK, voReleaseObject(m_voEngine, m_voResourceLK));

	m_voResourceAK = NULL;
	m_voResourceLK = NULL;
}

BOOL CVORecogEngine::AttachResource()
{
	RE_VERIFY_RETURN(FALSE, m_voEngine);
	ReleaseResource();
	//3) loading and attaching resources to the recognizer
	//3.1)loading the alphabet knowledge resource
	m_voResourceAK = LoadEngineObject(AK_RES);
	//3.2)attaching the alphabet knowledge resource to the recognizer
	RE_VERIFY_RETURN(FALSE, VO_IFACE(m_voEngine, IAttachTarget)->attach(m_voEngine, m_voStructuredInputRecognizer, m_voResourceAK));
	//3.3)loading the linguistic knowledge resource
	m_voResourceLK = LoadEngineObject(LK_RES);
	//3.4)attaching the linguistic knowledge resource to the recognizer
	RE_VERIFY_RETURN(FALSE, VO_IFACE(m_voEngine, IAttachTarget)->attach(m_voEngine, m_voStructuredInputRecognizer, m_voResourceLK));

	return TRUE;
}

voCandidateIterator CVORecogEngine::getSelectedCandidate(voSegmentIterator segment)
{
	uint32_t index;
	voCandidateIterator candidate;
	//verifyEx(segment != NULL, "invalid segment");
	candidate = VO_IFACE(m_voEngine, ISegmentIterator)->getCandidates(m_voEngine, segment);
	index = VO_IFACE(m_voEngine, ISegmentIterator)->getSelectedCandidateIndex(m_voEngine, segment);
	moveIterator(candidate, index);//verify(index == moveIterator(candidate, index));

	return candidate;
}
char* CVORecogEngine::getCandidateLabel(voCandidateIterator candidate)
{
	voString label = { NULL, 0 };
	VO_IFACE(m_voEngine, ICandidateIterator)->getLabel(m_voEngine, candidate, /*NULL*/m_voCharset, &label);
	label.bytes = (char*)malloc(label.byteCount + 1);
	VO_IFACE(m_voEngine, ICandidateIterator)->getLabel(m_voEngine, candidate, /*NULL*/m_voCharset, &label);
	label.bytes[label.byteCount] = '\0';

	return label.bytes;
}
int  CVORecogEngine::GetSegmentsCandidates(voSegmentIterator segments, TCandidates& pCandidates)
{  	
	RE_VERIFY_RETURN(0, segments && m_voEngine);
	//////////////////////////////////////////////////////////////////////////
	int candidateCount = 0;
	const voISegmentIterator* pISegmentIterator = VO_IFACE(m_voEngine, ISegmentIterator);
	/// candidate list for the segments
	while (!pISegmentIterator->isAtEnd(m_voEngine, segments))
	{
		TCandidate oCandidate;
		if (GetSegmentCandidates(segments, oCandidate) > 0)
		{
			pCandidates.push_back(oCandidate);
			++candidateCount;
		}
		pISegmentIterator->next(m_voEngine, segments);
	}

	return candidateCount;
}
BOOL CVORecogEngine::RecognizeWord(voCandidateIterator textCandidate, TCandidates& pCandidates)
{
	pCandidates.clear();
	RE_VERIFY_RETURN(FALSE, textCandidate && m_voEngine);
	//////////////////////////////////////////////////////////////////////////
	const voICandidateIterator* pICandidateIterator = VO_IFACE(m_voEngine, ICandidateIterator);
	/// retrieving the word segments of the text candidate
	voSegmentIterator wordSegments = pICandidateIterator->getSegments(m_voEngine, textCandidate);
	/// candidate list for the word segments
	GetSegmentsCandidates(wordSegments, pCandidates);
	voReleaseObject(m_voEngine, wordSegments);

	return pCandidates.size() > 0;
}
BOOL CVORecogEngine::RecognizeChar(voCandidateIterator textCandidate, TCandidates& pCandidates)
{
	pCandidates.clear();
	RE_VERIFY_RETURN(FALSE, (textCandidate && m_voEngine));
	//////////////////////////////////////////////////////////////////////////
	const voICandidateIterator* pICandidateIterator = VO_IFACE(m_voEngine, ICandidateIterator);
	const voISegmentIterator* pISegmentIterator = VO_IFACE(m_voEngine, ISegmentIterator);
	/// retrieving the word segments of the text candidate
	voSegmentIterator wordSegments = pICandidateIterator->getSegments(m_voEngine, textCandidate);
	/// candidate list for the word segments
	while (!pISegmentIterator->isAtEnd(m_voEngine, wordSegments))
	{
		/// retrieving the selected word candidate of the current word segment
		voCandidateIterator wordCandidate = getSelectedCandidate(wordSegments);
		/// retrieving the char segments of the selected word candidate
		voSegmentIterator charSegments = pICandidateIterator->getSegments(m_voEngine, wordCandidate);
		/// candidate list for the char segments
		GetSegmentsCandidates(charSegments, pCandidates);
		voReleaseObject(m_voEngine, charSegments);
		voReleaseObject(m_voEngine, wordCandidate);

		pISegmentIterator->next(m_voEngine, wordSegments);
	}
	voReleaseObject(m_voEngine, wordSegments);

	return (pCandidates.size() > 0);
}

QString CVORecogEngine::DoRecognizeAK()
{
	QString strRet;
	RE_VERIFY_RETURN(strRet, m_voEngine && m_voResourceAK && m_voStructuredInputRecognizer);
	//////////////////////////////////////////////////////////////////////////
	// detaching the linguistic knowledge resource from the recognizer
	RE_VERIFY_EXECUTE(m_voResourceLK, VO_IFACE(m_voEngine, IAttachTarget)->detach(m_voEngine, m_voStructuredInputRecognizer, m_voResourceLK));
	//5) running the handwriting recognition process
	if (VO_IFACE(m_voEngine, IRunnable)->run(m_voEngine, m_voStructuredInputRecognizer, NULL, NULL))
	{
		//6) retrieving the recognition result
		voRecognitionResult result = VO_IFACE(m_voEngine, IRecognitionResultProvider)->getResult(m_voEngine, m_voStructuredInputRecognizer);
		if (result != NULL)
		{
			//7) retrieving the first candidate of the recognition result
			voCandidateIterator iterator = VO_IFACE(m_voEngine, IRecognitionResult)->getCandidates(m_voEngine, result);
			//8)Make the candidate string: strRet
			const voICandidateIterator* pICandidateIterator = VO_IFACE(m_voEngine, ICandidateIterator);
			while (!pICandidateIterator->isAtEnd(m_voEngine, iterator))
			{
				char* label = getCandidateLabel(iterator);
				if (!isGesture(label) && !isSurroundChar(label))
				{
					QString lpWideCharStr = label;
					strRet = strRet + lpWideCharStr + HWR_RESULT_SPLIT;
				}

				free(label);
				pICandidateIterator->next(m_voEngine, iterator);
			}
			voReleaseObject(m_voEngine, iterator);
			voReleaseObject(m_voEngine, result);
		}
	}
	// attaching the linguistic knowledge resource to the recognizer
	RE_VERIFY_EXECUTE(m_voResourceLK, VO_IFACE(m_voEngine, IAttachTarget)->attach(m_voEngine, m_voStructuredInputRecognizer, m_voResourceLK));

	return strRet;
}
QString CVORecogEngine::DoRecognizeAKLK()
{
	QString strRet;
	RE_VERIFY_RETURN(strRet, m_voEngine && m_voResourceAK && m_voResourceLK && m_voStructuredInputRecognizer);
	//////////////////////////////////////////////////////////////////////////
	//5) running the handwriting recognition process
	RE_VERIFY_RETURN(strRet, VO_IFACE(m_voEngine, IRunnable)->run(m_voEngine, m_voStructuredInputRecognizer, NULL, NULL));
	//6) retrieving the recognition result
	voRecognitionResult result = VO_IFACE(m_voEngine, IRecognitionResultProvider)->getResult(m_voEngine, m_voStructuredInputRecognizer);
	RE_VERIFY_RETURN(strRet, result != NULL);
	//7) retrieving the proper text of the recognition result
	voCandidateIterator textProper = VO_IFACE(m_voEngine, IRecognitionResult)->getCandidates(m_voEngine, result);
	//8)Make the proper text string: strRet
	const voICandidateIterator* pICandidateIterator = VO_IFACE(m_voEngine, ICandidateIterator);
	if (!pICandidateIterator->isAtEnd(m_voEngine, textProper))
	{
		char* label = getCandidateLabel(textProper);
		if (!isGesture(label) && !isSurroundChar(label))
		{
			QString lpWideCharStr = label;
			strRet = strRet + lpWideCharStr + HWR_RESULT_SPLIT;
		}
		free(label);
	}
	voReleaseObject(m_voEngine, textProper);
	voReleaseObject(m_voEngine, result);

	return strRet;
}

int CVORecogEngine::FuelingInput(TInputStrokes& Strokes, BOOL bClearFirst)
{
	if (0 == Strokes.size())
	{
		return FALSE; 
	}
	RE_VERIFY_RETURN(0, m_voEngine && m_voFloatStructuredInput);
	//////////////////////////////////////////////////////////////////////////
	const voIFloatStructuredInput* pIFloatUnstructuredInput = VO_IFACE(m_voEngine, IFloatStructuredInput);
	if (bClearFirst)
	{
		pIFloatUnstructuredInput->clear(m_voEngine, m_voFloatStructuredInput, true);
	}
	//////////////////////////////////////////////////////////////////////////
	int nAddedStrokesCount = Strokes.size();
	for (int i = 0; i < nAddedStrokesCount; i++)
	{   
		TInputStroke& Stroke = Strokes.at(i);
		int nCount = Stroke.size();
		float* xPos = new float[nCount];
		float* yPos = new float[nCount];

		for (int j = 0; j < nCount; j++)
		{
			xPos[j] = Stroke.at(j).first;
			yPos[j] = Stroke.at(j).second;
		}

		pIFloatUnstructuredInput->addStroke(m_voEngine, m_voFloatStructuredInput, xPos, sizeof(float), yPos, sizeof(float), nCount);

		delete[] xPos;
		delete[] yPos;
	}

	return nAddedStrokesCount;
}
void CVORecogEngine::SetProperty()
{
	RE_VERIFY_RETURN0(m_voEngine);
	RE_VERIFY_RETURN0(m_voStructuredInputRecognizer);

	/// configureCandidateListProduction
	uint32_t charCandidateListSize = 5;
	voSetProperty(m_voEngine, m_voStructuredInputRecognizer, VO_CHAR_CANDIDATE_LIST_SIZE, &charCandidateListSize, sizeof(charCandidateListSize));
	uint32_t wordCandidateListSize = 5;
	voSetProperty(m_voEngine, m_voStructuredInputRecognizer, VO_WORD_CANDIDATE_LIST_SIZE, &wordCandidateListSize, sizeof(wordCandidateListSize));
	uint32_t textCandidateListSize = 5;
	voSetProperty(m_voEngine, m_voStructuredInputRecognizer, VO_TEXT_CANDIDATE_LIST_SIZE, &textCandidateListSize, sizeof(textCandidateListSize));
	bool bDiscardCaseVariations = true;
	voSetProperty(m_voEngine, m_voStructuredInputRecognizer, VO_DISCARD_CASE_VARIATIONS, &bDiscardCaseVariations, sizeof(bDiscardCaseVariations));

	voId value = 1;
	voSetProperty(m_voEngine, m_voStructuredInputRecognizer, VO_OVERRIDE_CASING_SCHEME, &value, sizeof(value));

	value = 1;
	voSetProperty(m_voEngine, m_voStructuredInputRecognizer, VO_OVERRIDE_ACCENTUATION_SCHEME, &value, sizeof(value));
}

BOOL CVORecogEngine::LoadMyScriptEngine()
{
	m_hMyScriptEngine.unload();

	BOOL bOk = FALSE;
	//TTQX - zhaozhengze - 添加手写识别引擎 - 缺陷
	//应该通过系统来获得路径
	QString strProgramPath = s_strFilePath + "MyScriptEngine.dll";
	m_hMyScriptEngine.setFileName(strProgramPath);
	if (m_hMyScriptEngine.load())
	{
		bOk = TRUE;
		void** sym_ptr;
		/* get functions pointers */
#undef VO_MSE_FUNC
#define VO_MSE_FUNC(type,name,params)\
		if (bOk)\
		bOk = (sym_ptr = (void**)&name, *sym_ptr = (void*)m_hMyScriptEngine.resolve(#name)) != NULL
#undef C_MYSCRIPTENGINE_H
#include <c/MyScriptEngine.h>		
#undef VO_MSE_FUNC
	}

	if (!bOk && m_hMyScriptEngine.isLoaded())
	{
		UnloadMyScriptEngine();
	}
	return bOk;
}

void CVORecogEngine::UnloadMyScriptEngine()
{
	if (!m_hMyScriptEngine.isLoaded())
		return;

	m_hMyScriptEngine.unload();

#undef VO_MSE_FUNC
#define VO_MSE_FUNC(type,name,params)\
	name = NULL
#undef C_MYSCRIPTENGINE_H
#include <c/MyScriptEngine.h>
#undef VO_MSE_FUNC

}

voEngineObject CVORecogEngine::LoadEngineObject(QString lpstrObjName)
{
	voEngineObject result = NULL;
	if (m_voEngine)
	{  
		QString strPath(m_strResourcePath);
		strPath += lpstrObjName;
		FILE* file = fopen(strPath.toStdString().c_str(), "rb");

		if (file)
		{
			result = voLoadObject(m_voEngine, readFuncFILE, file);
			fclose(file);
		}
	}
	return result;
}

BOOL CVORecogEngine::InitEngine()
{
	//2.1) library initialization 
	RE_VERIFY_RETURN(FALSE, LoadMyScriptEngine());
	//2.2) creating a new engine initialized with your certificate
	m_voEngine = voCreateEngine(VO_MSE_VER, &myCertificate, NULL);
	RE_VERIFY_RETURN(FALSE, m_voEngine);
	//2.3) creating a new UnstructuredInputRecognizer object
	m_voStructuredInputRecognizer = voCreateStructuredInputRecognizer(m_voEngine);
	RE_VERIFY_RETURN(FALSE, m_voStructuredInputRecognizer);
	////2.4) creating a voFloatUnstructuredInput object
	m_voFloatStructuredInput = voCreateFloatStructuredInput(m_voEngine);
	RE_VERIFY_RETURN(FALSE, m_voFloatStructuredInput);
	////2.5) setting the input object as the source of the recognizer object
	RE_VERIFY_RETURN(FALSE, VO_IFACE(m_voEngine, IInputConsumer)->setSource(m_voEngine, m_voStructuredInputRecognizer, m_voFloatStructuredInput));
	//2.6) loading a new Charset object
	/*m_voCharset = LoadEngineObject("UTF-8.charset");
	RE_VERIFY_RETURN(FALSE, m_voCharset);*/
	//2.7) SetProperty
	SetProperty();
	return TRUE;
}

BOOL  CVORecogEngine::Recognize(TInputStrokes* pStrokes, TCandidates* pCandidates)
{

	RE_VERIFY_RETURN(FALSE, pCandidates);
	pCandidates->clear();
	//TTQX - zhaozhengze - 添加手写识别引擎 - 缺陷
	RE_VERIFY_RETURN(FALSE, pStrokes && m_voEngine && m_voStructuredInputRecognizer /*&& IsEngineEnable()*/);
	//////////////////////////////////////////////////////////////////////////
	//4) fueling the input with strokes
	RE_VERIFY_RETURN(FALSE, FuelingInput(*pStrokes, TRUE) > 0);
	//////////////////////////////////////////////////////////////////////////
	//5) running the handwriting recognition process
	RE_VERIFY_RETURN(FALSE, VO_IFACE(m_voEngine, IRunnable)->run(m_voEngine, m_voStructuredInputRecognizer, NULL, NULL));
	//6) retrieving the recognition result
	voRecognitionResult result = VO_IFACE(m_voEngine, IRecognitionResultProvider)->getResult(m_voEngine, m_voStructuredInputRecognizer);
	RE_VERIFY_RETURN(FALSE, result != NULL);
	//7) retrieving the proper text of the recognition result
	voCandidateIterator textProper = VO_IFACE(m_voEngine, IRecognitionResult)->getCandidates(m_voEngine, result);
	//8) retrieving the candidates of the proper text
	if (LANG_CHINESE == PRIMARYLANGID(m_wRecogLangID))
	{
		RecognizeChar(textProper, *pCandidates);
	}
	else
	{
		RecognizeWord(textProper, *pCandidates);
	}

	voReleaseObject(m_voEngine, textProper);
	voReleaseObject(m_voEngine, result);

	return pCandidates->size() > 0;
}

/// 识别
QString CVORecogEngine::Recognize(TInputStrokes* pStrokes)
{   
	//TTQX-zhaozhengze-添加手写识别引擎-缺陷	 IsEngineEnable还没写检查设备
	RE_VERIFY_RETURN("", pStrokes && m_voEngine/* && IsEngineEnable()*/);
	//////////////////////////////////////////////////////////////////////////
	// fueling the input with strokes
	RE_VERIFY_RETURN("", FuelingInput(*pStrokes, TRUE) > 0);
	//////////////////////////////////////////////////////////////////////////
	QString strRet = DoRecognizeAKLK();
	QString strRetAK = DoRecognizeAK();


	if (strRet.isEmpty())
	{
		return strRetAK;
	}
	else if (!strRetAK.isEmpty())
	{
		strRetAK.replace(strRet, "");
		strRet += strRetAK;
	}
	return strRet;
}


void  CVORecogEngine::SetRecogLanguage(unsigned short wRecogLangID)
{
	if (m_wRecogLangID == wRecogLangID)
	{
		return;
	}

	m_wRecogLangID = wRecogLangID;

	switch (m_wRecogLangID)
	{
	case MAKELANGID(LANG_ARABIC, SUBLANG_ARABIC_SAUDI_ARABIA)://_T("阿拉伯语(沙特阿拉伯)")
	{
		AK_RES = "ar-ak-cur.res";
		LK_RES = "ar-lk-text.res";
		break;
	}
	case MAKELANGID(LANG_HEBREW, SUBLANG_DEFAULT)://_T("希伯来语")
	{
		AK_RES = "he_IL-ak-cur.res";
		LK_RES = "he_IL-lk-text.res";
		break;
	}
	case MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED)://_T("中文(中国)")
	{
        AK_RES = "zh_CN-ak-cur.res";
        LK_RES = "zh_CN-lk-text.res";
		break;
	}
	case MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_TRADITIONAL)://_T("中文(台湾)")
	{
        AK_RES = "zh_TW-ak-cur.res";
		LK_RES = "zh_TW-lk-text.res";
		break;
	}
	case MAKELANGID(LANG_KOREAN, SUBLANG_DEFAULT)://_T("朝鲜语")
	{
        AK_RES = "ko_KR-ak-cur.res";
		LK_RES = "ko_KR-lk-text.res";
		break;
	}
	case MAKELANGID(LANG_FRENCH, SUBLANG_FRENCH)://_T("法语")
	{
		AK_RES = "fr_FR-ak-cur.res";
		LK_RES = "fr_FR-lk-text.res";
		break;
	}
	case MAKELANGID(LANG_RUSSIAN, SUBLANG_DEFAULT)://_T("俄语")
	{
		AK_RES = "ru_RU-ak-cur.res";
		LK_RES = "ru_RU-lk-text.res";
		break;
	}
	case MAKELANGID(LANG_POLISH, SUBLANG_DEFAULT)://_T("波兰语")
	{
		AK_RES = "pl_PL-ak-cur.res";
		LK_RES = "pl_PL-lk-text.res";
		break;
	}
	case MAKELANGID(LANG_FINNISH, SUBLANG_DEFAULT)://_T("芬兰语")
	{
		AK_RES = "fi_FI-ak-cur.res";
		LK_RES = "fi_FI-lk-text.res";
		break;
	}
	case MAKELANGID(LANG_ITALIAN, SUBLANG_ITALIAN)://_T("意大利语(意大利)")
	{
		AK_RES = "it_IT-ak-cur.res";
		LK_RES = "it_IT-lk-text.res";
		break;
	}
	case MAKELANGID(LANG_HUNGARIAN, SUBLANG_DEFAULT)://_T("匈牙利语")
	{
		AK_RES = "hu_HU-ak-cur.res";
		LK_RES = "hu_HU-lk-text.res";
		break;
	}
	case MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH_MODERN)://_T("西班牙语(西班牙 - 现代风格)")
	{
		AK_RES = "es_ES-ak-cur.res";
		LK_RES = "es_ES-lk-text.res";
		break;
	}
	case MAKELANGID(LANG_THAI, SUBLANG_DEFAULT)://_T("泰语")//Letra级支持
	{
		AK_RES = "thai-ak-iso.res";
        LK_RES = "th_TH-lk-text.res";
		break;
	}
		//case MAKELANGID(LANG_SLOVAK, SUBLANG_DEFAULT)://_T("斯洛伐克语")
		//	{
		//		AK_RES = _T("?-ak-cur.res");
		//		LK_RES = _T("?-lk-text.res");
		//		break;
		//	}
	default://MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)://_T("英语")
	{
				AK_RES = "en_US-ak-cur.res";
				LK_RES = "en_US-lk-text.res";
				m_wRecogLangID = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);
				break;
	}
	}
	AttachResource();
}
