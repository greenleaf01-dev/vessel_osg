#pragma once
#include <QString>
#include <QIODevice>
#include <QImage>
#include <QPixmap>
#include <QByteArray>
class IHHImageData;
class IHHImageCollection
{
public:
	virtual	IHHImageData *createImageData(const QString& fileUrl) = 0;
	virtual	IHHImageData *createImageData(const QImage &image, const QString& format = "jpeg") = 0;
	virtual	IHHImageData *createImageData(const QPixmap &image,const QString& format = "jpeg") = 0;
	virtual void removeKey(const QString& key) =0;
	virtual void  clear() = 0;
};

Q_DECLARE_INTERFACE(IHHImageCollection, "org.qt-project.Qt.IHHImageCollection");
Q_DECLARE_METATYPE( IHHImageCollection* )