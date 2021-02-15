#ifndef _IHHDATACONTROLLER_H_
#define _IHHDATACONTROLLER_H_

#include <QUrl>
#include <QObject>
#include <QStringList>

#include "hhglobaldefine.h"

class IHHDataController {
public:
    virtual ~IHHDataController() {}
    
    virtual QObject* getObject() = 0;

	virtual void reqOpenFile(const QUrl &url) = 0;
	virtual void reqGetSlides(const QStringList &slides) = 0;
	virtual void reqCreateFile(const QUrl &url, const QVariantMap &vMap) = 0;
	virtual void reqSaveFile(const QUrl &url, bool autoSave = false) = 0;
	virtual void reqSaveAsFile(const QUrl &url) = 0;
	virtual void reqStopAll() = 0;

public:
    enum  TERMINATE_TYPE {
        TERMINATE_NONE = 0,
        TERMINATE_DATAPROVIDER = 1,
        TERMINATE_MODEL = 2
    };

};

Q_DECLARE_INTERFACE( IHHDataController, "com.hht.qtWhiteBoard.IHHDataController/1.0" )
Q_DECLARE_METATYPE( IHHDataController* )

#endif // _IHHDATACONTROLLER_H_

