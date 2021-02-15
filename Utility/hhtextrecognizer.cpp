#include "HZRecog.h"
#include "hhtextrecognizer.h"
#include <fstream>
#include <algorithm>
#include "RecogEngine.h"
//TTQX-zhaozhengze-����?����?D�䨺?��e��y??-?a??o����|??��?��?
#define MAKELANGID(p, s)       ((((WORD  )(s)) << 10) | (WORD  )(p))

#define LANG_ENGLISH                     0x09
#define SUBLANG_ENGLISH_US                          0x01 

class CSetVec :public std::vector<QString>
{
public:
	CSetVec(){}
	~CSetVec(){}

	void insert(const QString& strElem)
	{
		std::vector<QString>::iterator iter =
			std::find(this->begin(), this->end(), strElem);

		if (iter == this->end())
		{
			this->push_back(strElem);
		}
	}
};


static bool operator==(const std::pair<QString, CSetVec>& left, const std::pair<QString, CSetVec>& right)
{
	return left.first == right.first;
}

static bool operator==(const std::pair<QString, CSetVec>& left, const QString& right)
{
	return left.first == right;
}

class CMapVec :public std::vector<std::pair<QString, CSetVec> >
{
public:
	CMapVec(){}
	~CMapVec(){}

	void insert(const std::pair<QString, CSetVec>& pairStrVec)
	{
		std::vector<std::pair<QString, CSetVec> >::iterator iter =
			std::find(this->begin(), this->end(), pairStrVec);

		if (iter == this->end())
		{
			this->push_back(pairStrVec);
		}
	}
	const CSetVec& operator[](const QString& str) const  throw (std::exception)
	{
		return this->operator[](str);
	}

	CSetVec&  operator[](const QString& str)  throw (std::exception)
	{
		std::vector<std::pair<QString, CSetVec> >::iterator iter =
			std::find(this->begin(), this->end(), str);

		if (iter != this->end())
		{
			return iter->second;
		}
		else
		{
			throw std::exception();
		}
	}
	std::size_t count(const QString& str)
	{
		return std::count(this->begin(), this->end(), str);
	}
};

static eRecogEngineType GetDefaultEngineType()
{   
	bool bVOEngineExist = false;
	QString strFilePath = CRecogEngine::getSystemFilePath() + "MyScriptEngine.dll";
	std::ifstream in(strFilePath.toStdString().c_str());
	if (in)
	{
		bVOEngineExist = true;
	}
	in.close();
	eRecogEngineType nDefaultEngineType = eMSType;

	if (bVOEngineExist)
	{
		nDefaultEngineType = eFranceType;
	}
	return nDefaultEngineType;
}

static void CStringVectorFromStringWithoutNull(QString strValue, QString lpszSplit, TCStringVector& rvCString)
{
	QString strToken;
	QString strDelimiter(lpszSplit);
	rvCString.clear();
	//?a��??a??   
	int nStart = 0;
	int nLen = strDelimiter.length();

	for (;;)
	{
		int i = strValue.indexOf(strDelimiter, nStart);
		if (i < 0) break;
		if (i >= nStart)
		{
			strToken = strValue.mid(nStart, i - nStart);
			if (!strToken.isEmpty()) rvCString.push_back(strToken);
		}

		nStart = i + nLen;
	}

	//����??��?��?��?��?   
	if (nStart < strValue.length())
	{
		strToken = strValue.mid(nStart);
		if (!strToken.isEmpty()) rvCString.push_back(strToken);
	}
}

static void GetCandidateWords(QString& strRecognition, TCStringVector& vCandidateWords)
{
	vCandidateWords.clear();
	CStringVectorFromStringWithoutNull(strRecognition, HWR_RESULT_SPLIT, vCandidateWords);
}


class  LocalHHTextRecognizer : public HHTextRecognizer
{
public:
	LocalHHTextRecognizer(){}
	virtual ~LocalHHTextRecognizer();
public:
	virtual int InputRecognition(const TInputStrokes& strokes, int& begin, int& end, CRecoResults& vRecoResults);
	virtual void CreateRecogEngine(eRecogEngineType eRecogType);
	virtual void DeepDeleteRecogEngine();
	virtual void DeleteRecogEngine();
	virtual bool needAddSpace() const;
	virtual void SetRecogLanguage(const QString& strLanguage);
protected:
	//�̨���y??3??��?��2?D��
	//int InputRecognition(const vecStrokeProxy& strokes, int& begin, int& end, CRecoResults& vRecoResults);
	void PushRecoResult(CRecoResults& rvRecoResults, CRecoResult* pRecoResult, bool bAddSpace);
	static CRecogEngine* GetRecogEngine();
protected:
	static CRecogEngine* s_pRecognition;
	static CMapVec  s_mapCanditate;
};

HHTextRecognizer::HHTextRecognizer() 
{
}

QString HHTextRecognizer::recognizeText() {
    return "";
}

HHTextRecognizer* HHTextRecognizer::CreateTextRecognizer()
{
	return new LocalHHTextRecognizer();
}

void HHTextRecognizer::setSystemFilePath(const QString& strFilePath)
{
	CRecogEngine::setSystemFilePath(strFilePath + "reco\\");
}

void HHTextRecognizer::DeleteTextRecognizer(HHTextRecognizer*& pRecog)
{
	delete pRecog;
	pRecog = NULL;
}

LocalHHTextRecognizer:: ~LocalHHTextRecognizer()
{
	DeepDeleteRecogEngine();
}

void LocalHHTextRecognizer::SetRecogLanguage(const QString& strLanguage)
{   
	if (NULL != GetRecogEngine())
	{   
        if( "ID_PENBOX_CHINESE" == strLanguage)
		{
			GetRecogEngine()->SetRecogLanguage(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED));
		}
        else if( "ID_PENBOX_ENGLISH" == strLanguage)
		{
			GetRecogEngine()->SetRecogLanguage(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		}
	}
}

CRecogEngine* LocalHHTextRecognizer::GetRecogEngine()
{
	if (NULL == s_pRecognition)
	{
		eRecogEngineType eRecogType = GetDefaultEngineType();
		s_pRecognition = CRecogEngine::CreateRecogEngine(eRecogType);
		//TTQX-zhaozhengze-����?����?D�䨺?��e��y??-????��?�䨲??2?��|???��?a��?����?��
		s_pRecognition->SetFullCharacter(false);
		s_pRecognition->SetRecogRange(RECOG_RANGE_GB | RECOG_RANGE_GBK_ONLY | RECOG_RANGE_GB2_RADICAL | RECOG_RANGE_NUMBER | RECOG_RANGE_SYMBOL | RECOG_RANGE_INTERPUNCTION);
		s_pRecognition->SetRecogLanguage(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
	}
	return s_pRecognition;
}

void LocalHHTextRecognizer::DeepDeleteRecogEngine()
{
	delete s_pRecognition;
	s_pRecognition = NULL;
	s_mapCanditate.clear();
}

void LocalHHTextRecognizer::DeleteRecogEngine()
{
	if (NULL != s_pRecognition)
	{
		if (eMSType == s_pRecognition->GetEngineType())
		{
			DeepDeleteRecogEngine();
		}
		else
		{
			s_mapCanditate.clear();
		}
	}
}

void LocalHHTextRecognizer::CreateRecogEngine(eRecogEngineType eRecogType)
{
	DeleteRecogEngine();
	if (eDefaultType == eRecogType)
	{
		eRecogType = GetDefaultEngineType();
	}

	s_pRecognition = CRecogEngine::CreateRecogEngine(eRecogType);
	//TTQX-zhaozhengze-����?����?D�䨺?��e��y??-????��?�䨲??2?��|???��?a��?����?��
    if(NULL != s_pRecognition)
    {
        s_pRecognition->SetFullCharacter(false);
        s_pRecognition->SetRecogRange(RECOG_RANGE_GB | RECOG_RANGE_GBK_ONLY | RECOG_RANGE_GB2_RADICAL | RECOG_RANGE_NUMBER | RECOG_RANGE_SYMBOL | RECOG_RANGE_INTERPUNCTION);
        s_pRecognition->SetRecogLanguage(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
    }
}

int LocalHHTextRecognizer::InputRecognition(const TInputStrokes& strokes, int& begin, int& end, CRecoResults& vRecoResults)
{
	int hResult = 0;//??��D��?��e
	if (strokes.empty() ||
		begin < 0 ||
		begin >= end)
	{
		return hResult;
	}

	int nStroksCount = end - begin;
	if (false && nStroksCount < 3)//��������???����?-?Y2?��|����
	{
		return hResult;
	}
	TInputStrokes oStrokes;
	for (int i = begin; i != end; i++)
	{
		oStrokes.push_back(TInputStroke());
		TInputStroke& pStroke = oStrokes.back();
		const TInputStroke& pHHTStroke = strokes.at(i);

		for (int j = 0; j < pHHTStroke.size(); j++)
		{
			TInputPoint point;
			point.first = pHHTStroke[j].first;
			point.second = pHHTStroke[j].second;
			pStroke.push_back(point);
		}
	}

	int nEngineType = GetRecogEngine()->GetEngineType();
	WORD wRecogLang = GetRecogEngine()->GetRecogLanguage();

	TCandidates oCandidates;
	//TTQX-zhaozhengze-����?����?D�䨺?��e��y??-����?Y GetRecogEngine 2?��|??��?2?��y
	if (GetRecogEngine()->Recognize(&oStrokes, &oCandidates))
	{
		//TTQX-zhaozhengze-����?����?D�䨺?��e��y??-����?Y GetRecogEngine 2?��|??��?2?��y
		//?����?��e��y??????��?D�䨢?????��?��?��?��?��?o������?-?��2?��?��e��?����?a�̡�D??aD?����?-��?
		//?��?����?????��?��?��?��?��????��2??????a???����a��?��D?��������??����?��e?��������?��?D��1?2?o?��?o��?��???��
		BOOL bAddSpace = needAddSpace();
		int nCandidatesCount = oCandidates.size();
		for (int i = 0; i < nCandidatesCount; i++)
		{
			TCStringVector vCandidateWords;
			GetCandidateWords(oCandidates[i].text, vCandidateWords);
			if (vCandidateWords.empty())
			{
				continue;
			}

			CRecoResult* pRecoResult = new CRecoResult;
			pRecoResult->SetUnit(vCandidateWords.at(0));
			pRecoResult->m_vstrCandidate.clear();
			std::copy(vCandidateWords.begin(), vCandidateWords.end(), std::back_inserter(pRecoResult->m_vstrCandidate));
			PushRecoResult(vRecoResults, pRecoResult, bAddSpace);
		}

		if (vRecoResults.size() > 0)
		{
			CRecoResults::iterator iter = vRecoResults.begin();
			for (; iter != vRecoResults.end(); ++iter)
			{
				if (NULL == *iter)
				{
					continue;
				}

				s_mapCanditate.insert(make_pair((*iter)->GetUnit(), CSetVec()));
				if (s_mapCanditate.count((*iter)->GetUnit()) > 0)
				{
					CSetVec& strCanditateSet = s_mapCanditate[(*iter)->GetUnit()];

					for (int i = 0; i < ((*iter)->m_vstrCandidate).size(); ++i)
					{
						strCanditateSet.insert((*iter)->m_vstrCandidate.at(i));
					}
				}
			}
		}
	}
	return 1;
}



void LocalHHTextRecognizer::PushRecoResult(CRecoResults& rvRecoResults, CRecoResult* pRecoResult, bool bAddSpace)
{
	if (!pRecoResult)
	{
		return;
	}

	if (bAddSpace && !rvRecoResults.empty())
	{
		if (rvRecoResults.back()->GetUnit() != STR_SPACE)
		{
			CRecoResult* pSpace = new CRecoResult;
			pSpace->SetUnit(STR_SPACE);
			rvRecoResults.push_back(pSpace);
		}
	}

	rvRecoResults.push_back(pRecoResult);
}


bool LocalHHTextRecognizer::needAddSpace() const
{   
	if (NULL != GetRecogEngine())
	{
		WORD wRecogLang = GetRecogEngine()->GetRecogLanguage();
		bool bAddSpace = ((LANG_CHINESE_SIMPLIFIED == PRIMARYLANGID(wRecogLang)) || (LANG_CHINESE_TRADITIONAL == PRIMARYLANGID(wRecogLang)) || (LANG_JAPANESE == PRIMARYLANGID(wRecogLang)) || (LANG_KOREAN == PRIMARYLANGID(wRecogLang)) || (LANG_HEBREW == PRIMARYLANGID(wRecogLang)) || (LANG_THAI == PRIMARYLANGID(wRecogLang))) ? true : false;
		return !bAddSpace;
	}
	
	return true;
}

CRecogEngine* LocalHHTextRecognizer::s_pRecognition = NULL;
CMapVec  LocalHHTextRecognizer::s_mapCanditate;

