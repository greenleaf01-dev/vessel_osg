#ifndef HHTEXTRECOGNIZER
#define HHTEXTRECOGNIZER
#include <QString>
#include <QObject>
#include "utility_global.h"

class QPixmap;
class QWidget;
class UTILITYSHARED_EXPORT CChemRecogEngine : public QObject
{
public:
	CChemRecogEngine(){}
	virtual ~CChemRecogEngine(){}
	virtual long RecognizeAndShow(long * data, long hDC, float x, float y, long color, long fontSize) = 0;
	virtual class QPixmap *GetRecognizeBitmap(long* data) = 0;
	virtual void deleteBitmap(QPixmap* pBitmap) = 0;
	static CChemRecogEngine* CreateChemRecognizer();
	static void DeleteChemRecognizer(CChemRecogEngine*& pRecog);
	static void setSystemFilePath(const QString& strFilePath);

};
#endif