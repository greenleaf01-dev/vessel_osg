#pragma once

#include <QObject>
#include <QToolButton>
#include <QWidget>
#include <QHBoxLayout>

class IHHToolBar{
public:
     ~IHHToolBar(){}
    virtual QWidget * getWidget() = 0;
    virtual void   init(const QVariantMap &params) = 0;
    virtual void   setImagePath(const QString &sPath,const QString &sType) = 0;
    virtual void   setBtnCheckState(const QString &sBtnId, bool bIsChecked) = 0;
    virtual void   setBtnIsCheckable(const QString &sBtnId, bool bIsCheckable) = 0;
    virtual void   setIsCanMoveAble(bool bIsMoveFlg) = 0;
    virtual void   setBtnText(const QString sBtnId,const QString sBtnText) = 0;
    virtual void   setBtnIsDisabled(const QString sBtnId, bool bIsDisable) = 0;
    virtual  QToolButton *  getToolBar(const QString sBtnId) = 0;
    virtual void   resetToolBarLayout() = 0;
    virtual void   changePenBoxBtnStatus(const QString &sCurID) = 0;
};
Q_DECLARE_INTERFACE( IHHToolBar, "com.hht.qtWhiteBoard.IHHToolBar/1.0" )
Q_DECLARE_METATYPE( IHHToolBar* )
