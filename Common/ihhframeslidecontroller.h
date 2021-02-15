#ifndef IHHFRAMESLIDECONTROLLER_H
#define IHHFRAMESLIDECONTROLLER_H

#include <QObject>

class IHHFrameSlideController{
public:
    ~IHHFrameSlideController() {}

    virtual QObject *getObject() = 0;
};
Q_DECLARE_INTERFACE( IHHFrameSlideController, "com.hht.qtWhiteBoard.IHHFrameSlideController/1.0" )
Q_DECLARE_METATYPE( IHHFrameSlideController* )

#endif // IHHFRAMESLIDECONTROLLER_H
