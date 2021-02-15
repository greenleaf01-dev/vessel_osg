#pragma once

#include <QObject>
#include <QWidget>

class IHHAction;
class QToolButton;

class IHHRubberBox{
public:
    ~IHHRubberBox(){}
    virtual void    init(const QVariantMap &params) = 0;
    virtual void    setImagePath(const QString &sPath,const QString &sType) = 0;
    virtual QObject *getObject() = 0;
    virtual void    setBtnCheckedState(const QString &sBtnId) = 0;
    virtual void    setBtnValueChecked(const QString &sBtnId) = 0;

    virtual void    bingingAction(IHHAction *pIHHAction) = 0;

    virtual QToolButton *getToolBtn(const QString &sBtnID) = 0;
    virtual QToolButton *getValueToolBtn(const QString &sBtnID) = 0;
};
Q_DECLARE_INTERFACE( IHHRubberBox, "com.hht.qtWhiteBoard.IHHRubberBox/1.0" )
Q_DECLARE_METATYPE( IHHRubberBox* )
