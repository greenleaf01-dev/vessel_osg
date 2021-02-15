#pragma once

#include <QObject>
class QWidget;
class IHHToolBar;

class IHHSwitchToolBar{
public:
     ~IHHSwitchToolBar(){}
    virtual QObject*                    getObject() = 0;
    virtual void                switchToolBar() = 0;
    virtual IHHToolBar *        getGroupToolBar(int nIndex) = 0;
    virtual void                addGroupToolBar(int nIndex, IHHToolBar *pIHHToolBar, bool bToolbarDir) = 0;
    virtual void                showSwitchToolbar(bool bIsShowToolBar,QPoint &showPoint) = 0;
};
Q_DECLARE_INTERFACE(IHHSwitchToolBar, "com.hht.qtWhiteBoard.IHHSwitchToolBar/1.0" )
Q_DECLARE_METATYPE( IHHSwitchToolBar* )
