#ifndef HHTEXTRECOGNIZER
#define HHTEXTRECOGNIZER
#include <QString>
#include "utility_global.h"
#define FALSE   0
#define TRUE    1
#define NULL    0
typedef int BOOL;

class CRecogEngine
{
public:
	CRecogEngine() :m_bEnable(FALSE), m_bFullCharacter(FALSE),
		m_wRecogLangID(0), m_dwRecogFlags(0), m_dwRecogRange(0), m_dwRecogDisplay(0)
	{}
	virtual ~CRecogEngine(){}

public:
	virtual eRecogEngineType  GetEngineType(){ return eFranceType; }
	virtual QString	Recognize(TInputStrokes* pStrokes){ return ""; }
	virtual BOOL	Recognize(TInputStrokes* pStrokes, TCandidates* pCandidates){ return FALSE; }

public:
	virtual BOOL  IsEnable(){ return m_bEnable; }

	virtual BOOL  IsFullCharacter(){ return m_bFullCharacter; }
	virtual void  SetFullCharacter(BOOL bFullCharacter){ m_bFullCharacter = bFullCharacter; }

	virtual WORD  GetRecogLanguage(){ return m_wRecogLangID; }
	virtual void  SetRecogLanguage(WORD wRecogLangID){ m_wRecogLangID = wRecogLangID; }

	virtual DWORD GetRecogFlags(){ return m_dwRecogFlags; }
	virtual void  SetRecogFlags(DWORD dwRecogFlags){ m_dwRecogFlags = dwRecogFlags; }

	virtual DWORD GetRecogRange(){ return m_dwRecogRange; }
	virtual void  SetRecogRange(DWORD dwRecogRange){ m_dwRecogRange = dwRecogRange; }

	virtual DWORD GetRecogDisplay(){ return m_dwRecogDisplay; }
	virtual void  SetRecogDisplay(DWORD dwRecogDisplay){ m_dwRecogDisplay = dwRecogDisplay; }

	static  CRecogEngine* CreateRecogEngine(eRecogEngineType recogEngineType);
	static  void setSystemFilePath(const QString& strFilePath);
	static  QString getSystemFilePath();
protected:
	/// 识别激活状态
	BOOL			  m_bEnable;
	/// 全角显示
	BOOL			  m_bFullCharacter;
	/// 识别语言
	WORD  			  m_wRecogLangID;
	/// 识别标志
	DWORD			  m_dwRecogFlags;
	/// 识别范围
	DWORD			  m_dwRecogRange;
	/// 识别显示模式
	DWORD			  m_dwRecogDisplay;

	static QString s_strFilePath;
};

#endif