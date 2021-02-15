#pragma once
#include <QObject>
#include <QWidget>

class IHHToolButton{
public:
     ~IHHToolButton(){}
    virtual  QObject *getObject() = 0;
    virtual  void  setWgtToBtn(QWidget *pWgt) = 0;
};
Q_DECLARE_INTERFACE( IHHToolButton, "com.hht.qtWhiteBoard.IHHToolButton/1.0" )
Q_DECLARE_METATYPE( IHHToolButton* )


