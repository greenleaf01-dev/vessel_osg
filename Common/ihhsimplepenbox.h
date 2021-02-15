#pragma once

#include <QObject>

class QAbstractButton;
class IHHAction;

class IHHSimplePenBox{
public:
     ~IHHSimplePenBox(){}

    virtual QObject *getObject() = 0;

    virtual void setColorBtnChecked(const QString &sColor) = 0;
    virtual void setPenBtnChecked(const QString &sPenID) = 0;
    virtual void setPenInfo(const QJsonObject &penInfo) = 0;
    virtual void setPenText(const QString &sPenID, const QString &sText) = 0;
    virtual QAbstractButton * getPenButton(const QString &sPenID) = 0;
    virtual QAbstractButton * getColorButton(const QString &sColor) = 0;

    virtual void bindingAction(IHHAction *pIHHAction) = 0;
};

Q_DECLARE_INTERFACE( IHHSimplePenBox, "com.hht.qtWhiteBoard.IHHSimplePenBox/1.0" )
Q_DECLARE_METATYPE( IHHSimplePenBox* )
