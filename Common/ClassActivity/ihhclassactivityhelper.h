#pragma once

#include <QObject>

class IHHFileOperate;
class IHHClassActivityHelper{
public:
    ~IHHClassActivityHelper() {}

	virtual QObject* getObject() = 0;
    virtual void editActivityMatchInfo() = 0;
	virtual void replaceActivityItemBackground(const QString& strBackgroundPath) = 0;
    virtual void showCreateActivityUI() = 0;
	virtual QString selectImageFile(IHHFileOperate *pFileOpt) = 0;
};

Q_DECLARE_INTERFACE( IHHClassActivityHelper, "com.hht.qtWhiteBoard.IHHClassActivityHelper/1.0" )
Q_DECLARE_METATYPE( IHHClassActivityHelper* )
