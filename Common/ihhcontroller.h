#ifndef IHHCONTROLLER_H
#define IHHCONTROLLER_H
#include <QObject>

class IHHController {
public:
    virtual ~IHHController(){}
    virtual void executionAction( QString id, QVariantMap args ) = 0;
};

Q_DECLARE_INTERFACE( IHHController, "com.hht.qtWhiteBoard.IHHController/1.0" )
Q_DECLARE_METATYPE( IHHController* )

#endif // IHHCONTROLLER_H
