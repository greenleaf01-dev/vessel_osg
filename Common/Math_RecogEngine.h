#ifndef HHTEXTRECOGNIZER
#define HHTEXTRECOGNIZER
#include <QString>
#include <QObject>
#include "utility_global.h"

class QPixmap;
class QWidget;
class UTILITYSHARED_EXPORT CMathRecogEngine : public QObject
{
public:
	CMathRecogEngine(){}
	virtual ~CMathRecogEngine(){}
	virtual long RecognizeAndShow(long * data, long hDC, float x, float y, long color, long fontSize) = 0;
	virtual class QPixmap *GetRecognizeBitmap(long* data) = 0;
	virtual void deleteBitmap(QPixmap* pBitmap) = 0;
	static CMathRecogEngine* CreateMathRecognizer();
	static void DeleteMathRecognizer(CMathRecogEngine*& pRecog);
	static void setSystemFilePath(const QString& strFilePath);

};

#endif