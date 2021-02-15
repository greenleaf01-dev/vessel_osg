#pragma once

#include <QObject>

class IHHCustomMenu {
public:
     ~IHHCustomMenu(){}

    virtual QObject *getObject() = 0;

    virtual void setMenuActionText(const QString &sBtnID, const QString &sBtnText) =0 ;
};

Q_DECLARE_INTERFACE( IHHCustomMenu, "com.hht.qtWhiteBoard.IHHCustomMenu/1.0" )
Q_DECLARE_METATYPE( IHHCustomMenu* )
