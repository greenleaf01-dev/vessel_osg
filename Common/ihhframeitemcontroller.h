#ifndef IHHFRAMEITEMCONTROLLER_H
#define IHHFRAMEITEMCONTROLLER_H

#include <QObject>

class IHHFrameItemController{
public:
    ~IHHFrameItemController() {}

    virtual QObject *getObject() = 0;

    // 清页
    virtual void clearAllInfo() = 0;
    // 清除笔迹
    virtual void clearItemStrokes() = 0;
};
Q_DECLARE_INTERFACE( IHHFrameItemController, "com.hht.qtWhiteBoard.IHHFrameItemController/1.0" )
Q_DECLARE_METATYPE( IHHFrameItemController* )

#endif // IHHFRAMEITEMCONTROLLER_H
