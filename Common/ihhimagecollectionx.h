#ifndef _IHHIMAGECOLLECTIONX_H_
#define _IHHIMAGECOLLECTIONX_H_

#include <QUrl>
#include <QSize>
#include <QList>
#include <QObject>

class IHHImageCollectionX {
public:
	virtual ~IHHImageCollectionX() {}

	virtual QObject *getObject() = 0;

	virtual void reqImageData(const QUrl &url, QObject *obj, const QSize &siz = QSize()) = 0; // request(external)
	virtual void reqObjUnregister(const QObjectList &objs) = 0; // request(external)
	virtual void clearAll() = 0; // request(external)
};

Q_DECLARE_INTERFACE(IHHImageCollectionX, "com.hht.qtWhiteBoard.IHHImageCollectionX/1.0");
Q_DECLARE_METATYPE(IHHImageCollectionX *)

#endif // _IHHIMAGECOLLECTIONX_H_
