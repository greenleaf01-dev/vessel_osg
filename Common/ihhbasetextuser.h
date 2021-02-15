#ifndef IHHBASETEXTUSER_H
#define IHHBASETEXTUSER_H

#include <QRectF>
#include <QString>
#include <QObject>

class IHHBaseTextUser
{
public:
    virtual void changeTextProperty(QString str) = 0; //文本框属性发生变化时，通知user 哪些属性发生变化，str 为属性名
    virtual QRectF getItemRect() = 0;  //得到当前user的boundingRect
    virtual void notifyTextItemRectChanged( QRectF rect ) = 0;
    virtual QObject* getTextUserObject() = 0;
};
Q_DECLARE_INTERFACE(IHHBaseTextUser, "com.hht.qtWhiteBoard.IHHBaseTextUser/1.0")
Q_DECLARE_METATYPE(IHHBaseTextUser*)


#endif // IHHBASETEXTUSER_H
