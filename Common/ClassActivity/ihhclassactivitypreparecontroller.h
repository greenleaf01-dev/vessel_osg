#pragma once

#include <QObject>
#include <QJsonObject>

class IHHActivityTempletManager;
class IHHSlide;
class IHHAction;

class   IHHClassActivityPrepareController{
public:
    ~IHHClassActivityPrepareController() {}

    virtual QObject *getObject() = 0;
    virtual IHHActivityTempletManager * getTempletManager() = 0;
    virtual int createClassAcitivty(const QJsonObject &info) = 0;
    virtual QJsonObject getActivityInfo() = 0;
    virtual void setActivityMatchInfo(const QJsonObject &info) = 0;
    virtual QJsonObject getActivityMatchInfo() = 0;
    virtual void setActivityTempletInfo(const QJsonObject &info) = 0;
	virtual void replaceActivityItemBackground(const QString& strBackgroundPath) = 0;

    virtual QString getCurrentSlideActivityType() = 0;

    virtual void notifyUpdateActivityMacthInfo() = 0;
    virtual void notifyWorkAreaChanged() = 0;

    virtual void activeClassActivitySlide(IHHSlide *pIHHSlide) = 0;

    virtual void bindingSelectAction(IHHAction *pIHHAction) = 0;
};

Q_DECLARE_INTERFACE( IHHClassActivityPrepareController,
                     "com.hht.qtWhiteBoard.IHHClassActivityPrepareController/1.0" )
Q_DECLARE_METATYPE( IHHClassActivityPrepareController*)
