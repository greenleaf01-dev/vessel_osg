#ifndef IHHVIRTUALKEYBOARD_H
#define IHHVIRTUALKEYBOARD_H

#include <QObject>

class IHHVirtualKeyboard {
public:
    IHHVirtualKeyboard(){}
    ~IHHVirtualKeyboard(){}
    virtual void showVirtualKeyboard(QObject *obj, QEvent *event)=0;
};

Q_DECLARE_INTERFACE( IHHVirtualKeyboard, "com.hht.qtWhiteBoard.IHHVirtualKeyboard/1.0" )
Q_DECLARE_METATYPE( IHHVirtualKeyboard* )

#endif // IHHVIRTUALKEYBOARD_H
