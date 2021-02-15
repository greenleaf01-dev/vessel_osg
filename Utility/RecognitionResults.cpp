#include "RecognitionResults.h"

void CRecoResultUnit::SetPositionBound(const QRect& rect)
{
	m_rcPositionBound = rect;
}

QRect CRecoResultUnit::GetPositionBound() const
{
	return m_rcPositionBound;
}


void CRecoResultUnit::SetUnit(QString strUnit)
{
	m_strUnit = strUnit;
}

QString CRecoResultUnit::GetUnit()
{
	return m_strUnit;
}

CRecoResultUnit& CRecoResultUnit::operator = (const CRecoResultUnit& oRightSide)
{
	m_strUnit = oRightSide.m_strUnit;
	m_vstrCandidate = oRightSide.m_vstrCandidate;
	m_rcPositionBound = oRightSide.m_rcPositionBound;
	return *this;
}

void CRecoResultUnit::Clear()
{
	m_strUnit = "";
	m_vstrCandidate.clear();
	m_rcPositionBound = QRect();
}

CRecoResultUnits::~CRecoResultUnits()
{ 
	ClearAll(); 
}

void CRecoResultUnits::ClearAll()
{
	for (int i = 0; i < size(); ++i)
	{
		CRecoResultUnit* pUnit = at(i);
		delete pUnit;
	}
	clear();
}

CRecoResults::~CRecoResults()
{ 
	ClearAll(); 
}

void CRecoResults::ClearAll()
{
	for (int i = 0; i < size(); ++i)
	{
		CRecoResultUnit* pResult = this->at(i);
		delete pResult;
	}
	clear();
}