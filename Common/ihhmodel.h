#pragma once

#include <QJsonObject>
#include <QVariantMap>
#include <QRectF>


class IHHPresentation;
class QObject;
class IHHModel {
public:
	enum Error
	{
		NoError,
	    Saveing,
	    Readonly,
		NoSpace,
		CreateDir,
		NoContent,
		OldVersion,
		ContentErr,
		NoResource
	};
    enum ProcessState
    {
        None,
        Save,
        Open
    };
public:
    virtual ~IHHModel(){}
    virtual void insertPresentation( QString pId, QVariantMap data ) = 0;
    virtual Error savePresentation( IHHPresentation* presentionPoint, const QString& file ,bool isAutoSave  ) = 0;
    virtual void terminateSaveing() = 0;
    virtual ProcessState getCurrentState() =0;
    virtual void setCurrentFile(const QString& file) = 0;
    virtual QJsonObject openPresentation( const QString& file ) = 0;
    virtual QObject* getObject() = 0;
    virtual QVariant getParameters( QString type ) = 0;// 得到参数 
    virtual void importPPT( QString fileName ,QRectF canvas_rectf) = 0;
    virtual void exportIWBFile( QString filePath ,IHHPresentation* presentionPoint) = 0;
    virtual void importIWB( QString fileName ,IHHPresentation* presentionPoint) = 0; 
	virtual void setBlockSignals(bool block) = 0;
};
Q_DECLARE_INTERFACE( IHHModel, "com.hht.qtWhiteBoard.IHHModel/1.0" )
Q_DECLARE_METATYPE( IHHModel* )
