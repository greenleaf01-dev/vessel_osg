#pragma once

#include <QObject>

class IHHCanvas;
class IHHSlide;
class IHHActivitySoundEffectController;
class IHHFrameActivityController;

class IHHClassActivityUIHelper{
public:
    ~IHHClassActivityUIHelper() {}

    virtual QObject *getObject() = 0;

    virtual void checkInTeaching(IHHCanvas *pIHHCanvas, IHHSlide *pIHHSlide) = 0;
    virtual void checkOutTeaching(IHHCanvas *pIHHCanvas, IHHSlide *pIHHSlide) = 0;

    virtual void setTimeInfo(const QString &sTimeInfo) = 0;

    virtual void startUIVisible(bool bVisible) = 0;
    virtual void resultUIVisible(bool bVisible) = 0;
    virtual void checkResultOperBtnVisible(bool bVisible) = 0;
    virtual void checkOperBtnVisible(bool bVisible) = 0;
    virtual void answerUIVisible(bool bVisible, const QJsonObject &answerInfo) = 0;

    virtual void reviseUI(IHHCanvas *pIHHCanvas) = 0;

    virtual void stopTimer() = 0;
    virtual void resetTimer() = 0;
    virtual void timingUIVisible(IHHCanvas *pIHHCanvas, bool bVisible) = 0;

    virtual void bindActivityFrameController(IHHFrameActivityController *pIHHFrameCtrl) = 0;
};

Q_DECLARE_INTERFACE( IHHClassActivityUIHelper,
                     "com.hht.qtWhiteBoard.IHHClassActivityUIHelper/1.0" )
Q_DECLARE_METATYPE( IHHClassActivityUIHelper* )
