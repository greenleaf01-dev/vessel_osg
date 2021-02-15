#pragma once
#include <QString>
#include <QImage>
#include <QSize>
#include <QTimer>
#include <chrono>

class IHHImageData
{
public:
	virtual 	QImage pixmap(const QSize &targetSize = QSize()) = 0;
	virtual 	QString   key() const  =0;
	virtual     QSize     size() const = 0;
	virtual     void      setTimerInterval(int time) =0;
	virtual     void      copyOrigFile(const QString& file) =0;
	virtual     QString   file() = 0;
	virtual ~IHHImageData() {};
};
Q_DECLARE_INTERFACE(IHHImageData, "org.qt-project.Qt.IHHImageData");
Q_DECLARE_METATYPE( IHHImageData* )