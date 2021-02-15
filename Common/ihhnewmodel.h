#ifndef IHHNEWMODEL_H
#define IHHNEWMODEL_H
#include <QObject>

class IHHResourceCollectionX;

class IHHNewModel {
public:
    enum LoadError
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

    virtual ~IHHNewModel(){}
    virtual QObject* getObject() = 0;
    virtual void loadMain( const QString &strMainXml,int result ) = 0;
    virtual void loadSlide(const QString &strSlideXml,int priority,int result) = 0;
    virtual void terminateWorking() = 0;
    virtual void savePre(const QUrl &url, bool bAutoSave ) = 0 ;
    virtual void setResCollection(IHHResourceCollectionX* resCollection) = 0;

};

Q_DECLARE_INTERFACE( IHHNewModel, "com.hht.qtWhiteBoard.IHHNewModel/1.0" )
Q_DECLARE_METATYPE( IHHNewModel* )

#endif // IHHNEWMODEL_H
