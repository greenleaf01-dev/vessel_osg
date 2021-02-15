#ifndef RECONGNITIONRESULT
#define RECONGNITIONRESULT
#include <QString>
#include <vector>
#include <QRect>

#define  STR_SPACE		" "	
#define  STR_NULL		""	
typedef std::vector<QString> TCStringVector;
//////////////////////////////////////////////////////////////////////////
class CRecoResultUnit
{
public: 
	CRecoResultUnit(){}
	virtual ~CRecoResultUnit(){}

	void SetPositionBound(const QRect& rect);
	QRect GetPositionBound() const;
	void SetUnit(QString strUnit);
	QString GetUnit();

	CRecoResultUnit& CRecoResultUnit::operator = (const CRecoResultUnit& oRightSide);

	virtual void Clear();
public:
	TCStringVector		m_vstrCandidate;
private:
	QString				m_strUnit;
	QRect m_rcPositionBound;
};



class CRecoResultUnits : public ::std::vector< CRecoResultUnit* >
{
public:
	~CRecoResultUnits();

public:
	void ClearAll();
};

class CRecoResults : public ::std::vector< CRecoResultUnit* >
{
public:
	~CRecoResults();

public:
	void ClearAll();
};
typedef  CRecoResultUnit  CRecoResult;
#endif