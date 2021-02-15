#ifndef HHTEXTRECOGNIZER_H
#define HHTEXTRECOGNIZER_H

#include "utility_global.h"
#include "RecognitionResults.h"
#include <QObject>

class UTILITYSHARED_EXPORT HHTextRecognizer : public QObject {
    Q_OBJECT
public:
    HHTextRecognizer();
    virtual ~HHTextRecognizer(){}

Q_SIGNALS:
    void sigFinishedRecognize( QString result );

public:
    QString recognizeText();
	virtual int InputRecognition(const TInputStrokes& strokes, int& begin, int& end, CRecoResults& vRecoResults) = 0;
	virtual void CreateRecogEngine(eRecogEngineType eRecogType) = 0;
	virtual void DeepDeleteRecogEngine() = 0;
	virtual void DeleteRecogEngine() = 0;
	virtual bool needAddSpace() const = 0;
	virtual void SetRecogLanguage(const QString& strLanguage) = 0;
public: 
	static HHTextRecognizer* CreateTextRecognizer();
	static void DeleteTextRecognizer(HHTextRecognizer*& pRecog);
	static  void setSystemFilePath(const QString& strFilePath);
};

#endif
