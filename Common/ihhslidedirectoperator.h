#ifndef IHHSLIDEDIRECTOPERATOR_H
#define IHHSLIDEDIRECTOPERATOR_H

#include <QObject>
#include <QJsonObject>

class IHHSlideDirectOperator {
public:
    virtual ~IHHSlideDirectOperator(){}
    virtual void translate( float xOffset, float yOffset ) = 0;
    virtual void scale( QPointF ptCenter, float xRate, float yRate ) = 0;
    virtual void rotate( QPointF ptCenter, float degree ) = 0;
};
Q_DECLARE_INTERFACE( IHHSlideDirectOperator, "com.hht.qtWhiteBoard.IHHSlideDirectOperator/1.0" )
Q_DECLARE_METATYPE( IHHSlideDirectOperator* )

#endif // IHHSLIDEDIRECTOPERATOR_H
