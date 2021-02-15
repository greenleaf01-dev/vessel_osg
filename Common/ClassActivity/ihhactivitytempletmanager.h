#pragma once

#include <QObject>
#include <QMap>

class IHHActivityTempletInfo;

class IHHActivityTempletManager{
public:
    ~IHHActivityTempletManager(){}

    virtual QObject *getObject() = 0;

    virtual QMap<QString, IHHActivityTempletInfo*> getClassActivites(const QString &sType) = 0;
    virtual void initActivityTempletData() = 0;
    virtual QJsonObject getIntroduceVides() = 0;
    virtual QJsonObject getActivityAudios() = 0;
    virtual QJsonArray getDefaultUserData(QString) = 0;
    virtual QJsonObject getGapFillingDefaultUserData() = 0;
    virtual QJsonObject getCompetitionDefaultUserData() = 0;

    virtual QJsonObject getTemplateInfo(QString type,int index) = 0;
    virtual QVector<QString>  getThumbnails(QString type) = 0;
    virtual QVector<QString>  getContainerPictures(QString type,QString picType) = 0;
    virtual QVector<QString>  getMaterialPictures(QString type,QString picType) = 0;
    virtual QVector<QString>  getBackPictures(QString type,QString picType) = 0;
    virtual QJsonObject getTemplateGifPath(QString type,int index) = 0;
};

Q_DECLARE_INTERFACE( IHHActivityTempletManager,
                     "com.hht.qtWhiteBoard.IHHActivityTempletManager/1.0" )
Q_DECLARE_METATYPE( IHHActivityTempletManager* )
