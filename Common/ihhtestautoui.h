#pragma once

#include <QObject>

class IHHAction;

class IHHTestAutoUI{
public:
    ~IHHTestAutoUI() {}

    virtual void bindingAction(IHHAction *pIAction) = 0;

    virtual bool checkPropertyInfo(const QString &sProperty,
                                   const QVariant &checkValue) = 0;
};

Q_DECLARE_INTERFACE( IHHTestAutoUI, "com.hht.qtWhiteBoard.IHHTestAutoUI/1.0" )
Q_DECLARE_METATYPE( IHHTestAutoUI* )
