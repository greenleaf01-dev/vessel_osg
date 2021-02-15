#pragma once

#include <QObject>

class IHHCanvas;
class IHHSlide;
class IHHActionsManager;
class IHHPresentationData;

class IHHClassActivityTeachingController{
public:
    ~IHHClassActivityTeachingController() {}

    enum ClassActivityFrameType{
        eActivityType_Unknown = -1,
        eActivityType_OnLine = 0,
        eActivityType_Classify = 1,
        eActivityType_FillTest = 2,
        eActivityType_Contest = 3,
    };

    virtual QObject *getObject() = 0;
    virtual int check_in(IHHCanvas *pIHHCanvas) = 0;
    virtual int check_out(IHHCanvas *pIHHCanvas) = 0;
	virtual int beforeOldPresentationClear(IHHCanvas *pIHHCanvas) = 0;
	virtual int afterNewPresentationOpen(IHHCanvas *pIHHCanvas) = 0;
    virtual void setActionManager(IHHActionsManager *pIHHActionsManager) = 0;
};

Q_DECLARE_INTERFACE( IHHClassActivityTeachingController,
                     "com.hht.qtWhiteBoard.IHHClassActivityTeachingController/1.0" )
Q_DECLARE_METATYPE( IHHClassActivityTeachingController* )
