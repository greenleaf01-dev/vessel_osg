#ifndef _IHHRESCOLLECTIONX_H_
#define _IHHRESCOLLECTIONX_H_

#include <QUrl>
#include <QSize>
#include <QList>
#include <QObject>

class IHHResourceCollectionX {
public:
	virtual ~IHHResourceCollectionX() {}

	virtual QObject *getObject() = 0;

	virtual void reqImageData(const QUrl &url, QObject *obj, const QSize &siz = QSize()) = 0; // request(external)
	virtual void reqResData(const QUrl &url, QObject *obj) = 0; // request(external)
	virtual void reqObjUnregister(const QObjectList &objs) = 0; // request(external)
	virtual void clearAll() = 0; // request(external)

	//virtual void reqMd5(const QString &fileName, QObject *obj) = 0; // request(external)
	virtual bool reqImageDataSync(const QUrl &url, QObject *obj, QPixmap &pix, const QSize &siz = QSize()) = 0; // request(external)
};

Q_DECLARE_INTERFACE(IHHResourceCollectionX, "com.hht.qtWhiteBoard.IHHResourceCollectionX/1.0");
Q_DECLARE_METATYPE(IHHResourceCollectionX *)

#endif // _IHHRESCOLLECTIONX_H_

