#ifndef IHHDATAPROVIDER_H
#define IHHDATAPROVIDER_H

#include <QUrl>
#include <QObject>

class IHHDataProvider {
public:
    virtual ~IHHDataProvider(){}

    virtual QObject* getObject() = 0;
    virtual void getFile(const QUrl &strFile) = 0;
    virtual QString getCurTempFilePath() const = 0;
	virtual bool isUnZipFin() const = 0;
};

Q_DECLARE_INTERFACE( IHHDataProvider, "com.hht.qtWhiteBoard.IHHDataProvider/1.0" )
Q_DECLARE_METATYPE( IHHDataProvider* )

#endif // IHHDATAPROVIDER_H
