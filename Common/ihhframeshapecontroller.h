#ifndef IHHFRAMESHAPECONTROLLER_H
#define IHHFRAMESHAPECONTROLLER_H

#include <QObject>

class IHHFrameShapeController {
public:
    ~IHHFrameShapeController() {}
    virtual QObject *getObject() = 0;
    virtual void    shapeModeSwitched(QString itemid) = 0;
    virtual void setShapeJson(QString type, QString value) = 0;
    virtual QJsonObject getShapeJson() = 0;
    virtual QVariantMap getTextBoxVariantMap() = 0;
    virtual void setTextFormatInfo(const QString &sType, const QVariant &info) = 0;
};
Q_DECLARE_INTERFACE( IHHFrameShapeController, "com.hht.qtWhiteBoard.IHHFrameShapeController/1.0" )
Q_DECLARE_METATYPE( IHHFrameShapeController* )

#endif // IHHFRAMESHAPECONTROLLER_H
