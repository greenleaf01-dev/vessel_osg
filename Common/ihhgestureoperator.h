#pragma once

#include <QObject>

class IHHGestureOperator {
public:
    virtual ~IHHGestureOperator(){}
    virtual int modifyGestureType( int nGestureType ) = 0;
    virtual void setEnable( bool bEnable ) = 0;
    virtual void resetUnitEnvironment() = 0;
};

Q_DECLARE_INTERFACE( IHHGestureOperator, "com.hht.qtWhiteBoard.IHHGestureOperator/1.0" )
Q_DECLARE_METATYPE( IHHGestureOperator* )
