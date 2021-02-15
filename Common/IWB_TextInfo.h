#ifndef IWB_TEXTINFO_H
#define IWB_TEXTINFO_H
#include <vector>
#include <QString>

class CIWBTextInfo
{
public: 
	CIWBTextInfo() :m_bLineEnd(false)
	{
		m_strColor = "#000000";
		m_strFontWeight = "bold";
		m_strFontStretch = "normal";
		m_strFontStyle = "italic";
		m_strFontFamily = "Arial"; 
		m_strFontSize = "28";
		m_strFontDecoration = "underline";
		m_strTextAlign = "start";
	}

	~CIWBTextInfo(){}

	QString m_strColor; 
	QString m_strFontWeight;
	QString m_strFontStretch; 
	QString m_strFontStyle;
	QString m_strFontFamily;
	QString m_strFontSize; 
	QString m_strFontDecoration; 
	QString m_strTextAlign;
	QString m_strContentText;
	QString m_strBoundingBox;
	bool   m_bLineEnd;
};

typedef  std::vector<CIWBTextInfo> TVecIwbInfo; 
#endif // UTILITY_GLOBAL_H
