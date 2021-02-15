#include "VORecogEngine.h"

#ifdef WIN32
#include "MSRecogEngine.h"
#endif

#include "RecogEngine.h"

QString CRecogEngine::s_strFilePath;

void CRecogEngine::setSystemFilePath(const QString& strFilePath)
{
	s_strFilePath = strFilePath;
}
QString CRecogEngine::getSystemFilePath()
{
	return s_strFilePath;
}

CRecogEngine* CRecogEngine::CreateRecogEngine(eRecogEngineType recogEngineType)
{   
	if (eFranceType == recogEngineType)
	{
		CRecogEngine* pRecogEngine = new CVORecogEngine();
		return pRecogEngine;
	}
#ifdef WIN32
	else if (eMSType == recogEngineType)
	{
		CRecogEngine* pRecogEngine = new CMSRecogEngine();
		return pRecogEngine;
	}
#endif
	return NULL;
}