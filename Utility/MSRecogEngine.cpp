#ifdef WIN32
#include <atlbase.h>        
#include <msinkaut.h>
#include <msinkaut_i.c>
#include "MSRecogEngine.h"


CMSRecogEngine::CMSRecogEngine()
{
	// Initialize the COM library and the Engine
	m_hCoInitialize = ::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	m_bEnable = InitEngine();
}

CMSRecogEngine::~CMSRecogEngine()
{
	m_bEnable = FALSE;
	// Release the Engine and the COM library
	ExitEngine();
	if (SUCCEEDED(m_hCoInitialize))
	{
		::CoUninitialize();
	}
}

//////////////////////////////////////////////////////////////////////////
// Helper methods

/////////////////////////////////////////////////////////
// CreateRecogContext
// 
// As it follows from the name, this helper method, given 
// a pointer to the recognizer, creates and initializes 
// new recognition context.
//        
// Parameters:
//      IInkRecognizer* pIInkRecognizer   
//              : [in] the recognizer to create a context with
//
// Return Values (bool):
//      true if succeeded creating new recognition context, false otherwise
/////////////////////////////////////////////////////////
bool CMSRecogEngine::CreateRecogContext(IInkRecognizer* pIInkRecognizer)
{
	RE_VERIFY_RETURN(false, pIInkRecognizer);
	// Create a new recognition context
	CComPtr<IInkRecognizerContext> spNewContext;
	RE_VERIFY_RETURN(false, SUCCEEDED(pIInkRecognizer->CreateRecognizerContext(&spNewContext)));
	// Replace the current context with the new one
	if (m_spIInkRecogContext != NULL)
	{
		// Reset the recognition context
		m_spIInkRecogContext->putref_Strokes(NULL);
	}
	// Detach and release the old context then use the new one
	m_spIInkRecogContext.Attach(spNewContext.Detach());
	//////////////////////////////////////////////////////////////////////////
	// Set the recognition context properties before attaching the stroke collection to it
	// Reset the Input Scope to baseline
	//CComBSTR bstrFactoid(FACTOID_DEFAULT);
	//if (FAILED(spNewContext->put_Factoid(bstrFactoid)))
	//{
	//	("Failed to set factoid to the new recognition context!"), 
	//}

	return true;
}

//Creates a IInkStrokeDisp, in InkDisp object, from an array of point data.
bool CMSRecogEngine::CreateInkStroke(TInputStroke* pInputStroke)
{
	RE_VERIFY_RETURN(false, pInputStroke && m_spIInkDisp);
	long lSize = pInputStroke->size();
	RE_VERIFY_RETURN(false, lSize > 0);
	//////////////////////////////////////////////////////////////////////////
	bool bRet = false;
	SAFEARRAY* psaPoints = ::SafeArrayCreateVector(VT_I4, 0, lSize * 2);
	if (psaPoints)
	{
		// VariantClear will invoke ::SafeArrayDestroy(psaPoints);
		CComVariant varPacketData;
		varPacketData.vt = VT_ARRAY | VT_I4;
		varPacketData.parray = psaPoints;
		LONG* plArray = NULL;

		if (SUCCEEDED(::SafeArrayAccessData(psaPoints, (void**)&plArray)))
		{
			for (long i = 0, n = 0; i < lSize; ++i)
			{
				plArray[n++] = (*pInputStroke)[i].first;
				plArray[n++] = (*pInputStroke)[i].second;
			}
			::SafeArrayUnaccessData(psaPoints);
			//////////////////////////////////////////////////////////////////////////
			CComPtr<IInkStrokeDisp> spIInkStrokeDisp;
			CComVariant varPacketDescription;
			// varPacketDescription is currently reserved, 
			// so it is just empty variant for now.
			if (SUCCEEDED(m_spIInkDisp->CreateStroke(varPacketData, varPacketDescription, &spIInkStrokeDisp)))
			{
				bRet = true;
			}
		}
	}

	return bRet;
}

bool CMSRecogEngine::GetRecognitionAlternates(TCandidate& rCandidate, IInkRecognitionAlternates* pIInkRecogAlternates, long maximumAlternates/* = -1*/)
{
	RE_VERIFY_RETURN(false, pIInkRecogAlternates);
	// Count the alternates, it may be less then we asked for
	long lAlternatesCount = 0;
	RE_VERIFY_RETURN(false, SUCCEEDED(pIInkRecogAlternates->get_Count(&lAlternatesCount)) && lAlternatesCount > 0);
	//////////////////////////////////////////////////////////////////////////
	long lMaxLength = 0;
	rCandidate.first = rCandidate.last = 0;
	rCandidate.text = "";

	if (maximumAlternates < 0) maximumAlternates = lAlternatesCount;
	// Get the alternate strings
	for (LONG iItem = 0; (iItem < lAlternatesCount) && (iItem < maximumAlternates); ++iItem)
	{
		CComPtr<IInkRecognitionAlternate> spIInkRecogAlternate;
		// Get the alternate string if there is one
		if (SUCCEEDED(pIInkRecogAlternates->Item(iItem, &spIInkRecogAlternate)))
		{
			CComBSTR bstr;
			if (SUCCEEDED(spIInkRecogAlternate->get_String(&bstr)))
			{   
				BSTR bstr1 = bstr;
				QString strAlternate((QChar*)bstr1, wcslen(bstr1));
				rCandidate.text += strAlternate + HWR_RESULT_SPLIT;
				//////////////////////////////////////////////////////////////////////////
				CComPtr<IInkStrokes> spIInkStrokes;
				long selectionStart = 0;
				long selectionLength = strAlternate.length();
				/// Get the ink strokes collection from the ink object.
				if (SUCCEEDED(spIInkRecogAlternate->GetStrokesFromTextRange(&selectionStart, &selectionLength, &spIInkStrokes)))
				{
					long lStrokesCount = 0;
					if (SUCCEEDED(spIInkStrokes->get_Count(&lStrokesCount)) && lStrokesCount > 0)
					{
						if (rCandidate.last < lStrokesCount)
						{
							rCandidate.last = lStrokesCount;
						}
					}
				}
			}
		}
	}

	return !rCandidate.text.isEmpty();
}

bool CMSRecogEngine::GetRecogAlternatesFromSelection(TCandidate& rCandidate, IInkRecognitionResult* pIInkRecogResult, long selectionStart, long selectionLength, long maximumAlternates)
{
	RE_VERIFY_RETURN(false, pIInkRecogResult);
	//////////////////////////////////////////////////////////////////////////
	// Get the best lCount results
	CComPtr<IInkRecognitionAlternates> spIInkRecogAlternates;
	HRESULT hr = pIInkRecogResult->AlternatesFromSelection(
		selectionStart,			// in: selection start 
		selectionLength,		// in: selection length; -1 means "up to the last one"
		maximumAlternates,		// in: the number of alternates we're interested in
		&spIInkRecogAlternates	// out: the receiving pointer
		);

	RE_VERIFY_RETURN(false, SUCCEEDED(hr) && spIInkRecogAlternates);

	return GetRecognitionAlternates(rCandidate, spIInkRecogAlternates, maximumAlternates);
}

int CMSRecogEngine::GetRecogAlternatesChar(IInkRecognitionResult* pIInkRecogResult, TCandidates* pCandidates)
{
	RE_VERIFY_RETURN(0, pIInkRecogResult && pCandidates);
	CComBSTR bstr;
	RE_VERIFY_RETURN(0, SUCCEEDED(pIInkRecogResult->get_TopString(&bstr)));
	//////////////////////////////////////////////////////////////////////////
	BSTR bstr1 = bstr;
	QString strRecogResult((QChar*)bstr1, wcslen(bstr1));

	int candidateCount = 0;
	int nIndexNext = 0;
	int nCount = strRecogResult.length();

	for (int i = 0; i < nCount; ++i)
	{
		TCandidate unit;
		if (GetRecogAlternatesFromSelection(unit, pIInkRecogResult, i, 1, mc_lNumResults))
		{
			unit.first = nIndexNext;
			nIndexNext += unit.last;
			unit.last = nIndexNext - 1;
			pCandidates->push_back(unit);
			++candidateCount;
		}
	}

	return candidateCount;
}

int CMSRecogEngine::GetRecogAlternatesWord(IInkRecognitionResult* pIInkRecogResult, TCandidates* pCandidates)
{
	RE_VERIFY_RETURN(0, pIInkRecogResult && pCandidates);
	CComBSTR bstr;
	RE_VERIFY_RETURN(0, SUCCEEDED(pIInkRecogResult->get_TopString(&bstr)));
	//////////////////////////////////////////////////////////////////////////
	BSTR bstr1 = bstr;
	QString strRecogResult((QChar*)bstr1, wcslen(bstr1));
	int candidateCount = 0;
	int nFirst = 0;
	int nLength = 0;
	int nIndexNext = 0;
	int nBound = strRecogResult.length() - 1;

	for (int i = 0; i <= nBound; ++i)
	{
		bool bWord = false;
		if (i == nBound)
		{
			bWord = true;
			++nLength;
		}
		else
		{
			if (strRecogResult[i] == L' ')
			{
				bWord = true;
			}
			else
			{
				++nLength;
			}
		}

		if (bWord)
		{
			TCandidate unit;
			if (GetRecogAlternatesFromSelection(unit, pIInkRecogResult, nFirst, nLength, mc_lNumResults))
			{
				unit.first = nIndexNext;
				nIndexNext += unit.last;
				unit.last = nIndexNext - 1;
				pCandidates->push_back(unit);
				++candidateCount;
			}
			nFirst += nLength + 1;
			nLength = 0;
		}
	}

	return candidateCount;
}

//////////////////////////////////////////////////////////////////////////
// Implementation & Operations

void CMSRecogEngine::SetRecogLanguage(WORD wRecogLangID)
{
	if (wRecogLangID == m_wRecogLangID)
	{
		return;
	}
	//////////////////////////////////////////////////////////////////////////
	if (!m_spIInkRecognizers) return;
	// Get the number of the recognizers known to the system
	LONG lCount = 0;
	HRESULT hr = m_spIInkRecognizers->get_Count(&lCount);
	if (lCount <= 0) return;
	//////////////////////////////////////////////////////////////////////////
	// Get a pointer to the recognizer object from the recognizer collection  
	// Use DefaultRecognizer method to get a pointer to the default recognizer
	// or use index for any other one

	// The first parameter is the language id, passing 0 means that the language 
	// id will be retrieved using the user default-locale identifier
	CComPtr<IInkRecognizer> spIInkRecognizer;
	hr = m_spIInkRecognizers->GetDefaultRecognizer(wRecogLangID, &spIInkRecognizer);//0,
	// Create new recognition context
	if (SUCCEEDED(hr) && CreateRecogContext(spIInkRecognizer))
	{
		m_wRecogLangID = wRecogLangID;
		//CComBSTR m_bstrCurRecoName;
		//m_bstrCurRecoName.Empty();
		//spIInkRecognizer->get_Name(&m_bstrCurRecoName);
	}
	else
	{
		wRecogLangID = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);
		CComPtr<IInkRecognizer> spIInkRecognizer;
		hr = m_spIInkRecognizers->GetDefaultRecognizer(wRecogLangID, &spIInkRecognizer);//0,
		// Create new recognition context
		if (SUCCEEDED(hr) && CreateRecogContext(spIInkRecognizer))
		{
			m_wRecogLangID = wRecogLangID;
		}
		/*/TTQX-zhaozhengze-[B170706-024]【手写识别】win10下软件启动后识别范围选择英文，书写识别不了，改为中文可以识别；英文下中文也可以识别
		这个问题产生的原因是win10系统下没有安装英文语言包，但是不知道为什么无法安装上。所以解决的方法是
		如果当前没有英语，则默认为汉语。
		/*/
		else
		{

			wRecogLangID = MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED);
			CComPtr<IInkRecognizer> spIInkRecognizer;
			hr = m_spIInkRecognizers->GetDefaultRecognizer(wRecogLangID, &spIInkRecognizer);//0,
																							// Create new recognition context
			if (SUCCEEDED(hr) && CreateRecogContext(spIInkRecognizer))
			{
				m_wRecogLangID = wRecogLangID;
			}
		}
		//*/
		
	}
	//////////////////////////////////////////////////////////////////////////
	//for (LONG i = 0; i < lCount; i++)
	//{
	//	CComPtr<IInkRecognizer> spIInkRecognizer;
	//	if (FAILED(m_spIInkRecognizers->Item(i, &spIInkRecognizer)))  
	//		continue;
	//	// Filter out non-language recognizers by checking for 
	//	// the languages supported by the recognizer - there'll be 
	//	// none if it's a gesture or object recognizer.
	//	CComVariant vLanguages;
	//	if (SUCCEEDED(spIInkRecognizer->get_Languages(&vLanguages)))
	//	{
	//		if ((VT_ARRAY == (VT_ARRAY & vLanguages.vt))            // it should be an array
	//			&& (NULL != vLanguages.parray)      
	//			&& (0 < vLanguages.parray->rgsabound[0].cElements)) // with at least one element
	//		{
	//			CComBSTR bstrName;
	//			if (SUCCEEDED(spIInkRecognizer->get_Name(&bstrName)))
	//			{
	//				bstrName;
	//			}
	//		}
	//	}
	//}
	//////////////////////////////////////////////////////////////////////////
	//LANGID wLandId = ::GetUserDefaultLangID();
	//CComVariant vLangIDs;
	//if (SUCCEEDED(pIInkRecognizer->get_Languages(&vLangIDs)) && NULL != vLangIDs.parray)
	//{
	//	WORD* pwLIDs;
	//	if (SUCCEEDED(::SafeArrayAccessData(vLangIDs.parray, (void HUGEP**)&pwLIDs)))
	//	{
	//		wLandId = pwLIDs[0];
	//		::SafeArrayUnaccessData(vLangIDs.parray);
	//	}
	//}
}

BOOL CMSRecogEngine::InitEngine()
{
	HRESULT hr;
	//////////////////////////////////////////////////////////////////////////
	// Create the enumerator for the installed recognizers
	hr = m_spIInkRecognizers.CoCreateInstance(CLSID_InkRecognizers);//, NULL, CLSCTX_INPROC_HANDLER
	if (FAILED(hr)) return FALSE;
	// Get the number of the recognizers known to the system
	LONG lCount = 0;
	hr = m_spIInkRecognizers->get_Count(&lCount);
	if (0 == lCount)
	{
		//("There are no handwriting recognizers installed.\n"),
		return FALSE;
	}
	//////////////////////////////////////////////////////////////////////////
	/// Create an ink object.
	hr = m_spIInkDisp.CoCreateInstance(CLSID_InkDisp);
	if (FAILED(hr)) return FALSE;

	//////////////////////////////////////////////////////////////////////////
	return TRUE;
}

BOOL CMSRecogEngine::ExitEngine()
{
	if (m_spIInkRecogContext != NULL)
	{
		// Detach the strokes collection from the recognition context 
		m_spIInkRecogContext->EndInkInput();
		m_spIInkRecogContext.Release();
	}
	// Release the other objects and collections
	m_spIInkDisp.Release();
	m_spIInkRecognizers.Release();

	//////////////////////////////////////////////////////////////////////////
	return TRUE;
}

/// 识别
QString CMSRecogEngine::Recognize(TInputStrokes* pStrokes)
{
	//
	//TTQX - zhaozhengze - 添加手写识别引擎-缺陷  IsEngineEnable这个函数需要写上
	RE_VERIFY_RETURN((""), pStrokes && m_spIInkDisp && m_spIInkRecogContext/* && IsEngineEnable()*/);
	//////////////////////////////////////////////////////////////////////////
	// Reset the recognition context
	// Detach the stroke collection from the recognition context
	m_spIInkRecogContext->putref_Strokes(NULL);
	// Delete all strokes from the Ink object,
	// Passing NULL as a stroke collection pointer 
	// means asking to delete all strokes
	m_spIInkDisp->DeleteStrokes(NULL);
	//////////////////////////////////////////////////////////////////////////
	/// CreateInkStrokes
	for (int i = 0; i < pStrokes->size(); ++i)
	{
		CreateInkStroke(&(*pStrokes)[i]);
	}
	//////////////////////////////////////////////////////////////////////////
	QString strRecogResult;
	CComPtr<IInkStrokes> spIInkStrokes;
	/// Get the ink strokes collection from the ink object.
	if (SUCCEEDED(m_spIInkDisp->get_Strokes(&spIInkStrokes)))
	{
		long lCount = 0;
		if (SUCCEEDED(spIInkStrokes->get_Count(&lCount)) && lCount > 0)
		{
			// Attach the stroke collection to the recognition context
			if (SUCCEEDED(m_spIInkRecogContext->putref_Strokes(spIInkStrokes)))
			{
				// Recognize 
				InkRecognitionStatus ink_recog_status = IRS_NoError;
				CComPtr<IInkRecognitionResult> spIInkRecogResult;
				if (SUCCEEDED(m_spIInkRecogContext->Recognize(&ink_recog_status, &spIInkRecogResult)))
				{
					TCandidate oCandidate;
					if (GetRecogAlternatesFromSelection(oCandidate, spIInkRecogResult, 0, -1, mc_lNumResults))
					{
						strRecogResult = oCandidate.text;
					}
				}
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	// Reset the recognition context
	m_spIInkRecogContext->putref_Strokes(NULL);
	// Delete all strokes from the Ink object,
	m_spIInkDisp->DeleteStrokes(NULL);

	return strRecogResult;
}

BOOL CMSRecogEngine::Recognize(TInputStrokes* pStrokes, TCandidates* pCandidates)
{
	RE_VERIFY_RETURN(FALSE, pCandidates);
	pCandidates->clear();
	RE_VERIFY_RETURN(FALSE, pStrokes && m_spIInkDisp && m_spIInkRecogContext /*&& IsEngineEnable()*/);
	//////////////////////////////////////////////////////////////////////////
	// Reset the recognition context
	// Detach the stroke collection from the recognition context
	m_spIInkRecogContext->putref_Strokes(NULL);
	// Delete all strokes from the Ink object,
	// Passing NULL as a stroke collection pointer 
	// means asking to delete all strokes
	m_spIInkDisp->DeleteStrokes(NULL);
	//////////////////////////////////////////////////////////////////////////
	/// CreateInkStrokes
	for (int i = 0; i < pStrokes->size(); ++i)
	{
		CreateInkStroke(&(*pStrokes)[i]);
	}
	//////////////////////////////////////////////////////////////////////////
	CComPtr<IInkStrokes> spIInkStrokes;
	/// Get the ink strokes collection from the ink object.
	if (SUCCEEDED(m_spIInkDisp->get_Strokes(&spIInkStrokes)))
	{
		long lCount = 0;
		spIInkStrokes->get_Count(&lCount);
		if (lCount > 0)
		{
			// Attach the stroke collection to the recognition context
			if (SUCCEEDED(m_spIInkRecogContext->putref_Strokes(spIInkStrokes)))
			{
				// Recognize 
				InkRecognitionStatus ink_recog_status = IRS_NoError;
				CComPtr<IInkRecognitionResult> spIInkRecogResult;
				if (SUCCEEDED(m_spIInkRecogContext->Recognize(&ink_recog_status, &spIInkRecogResult)))
				{
					if (LANG_CHINESE == PRIMARYLANGID(m_wRecogLangID))
					{
						GetRecogAlternatesChar(spIInkRecogResult, pCandidates);
					}
					else
					{
						GetRecogAlternatesWord(spIInkRecogResult, pCandidates);
					}
				}
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	// Reset the recognition context
	m_spIInkRecogContext->putref_Strokes(NULL);
	// Delete all strokes from the Ink object,
	m_spIInkDisp->DeleteStrokes(NULL);
	//////////////////////////////////////////////////////////////////////////	
	return pCandidates->size() > 0;
}
#endif