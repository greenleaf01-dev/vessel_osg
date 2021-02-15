#ifndef IHHFRAMETEXTBOXCONTROLLER_H
#define IHHFRAMETEXTBOXCONTROLLER_H

#include <QObject>

class IHHFrameTextBoxController{
public:
    ~IHHFrameTextBoxController(){}

    virtual QObject *getObject() = 0;

    virtual void setVariantMap(const QVariantMap &value) = 0;
    virtual QVariantMap getVariantMap() = 0;

    virtual void createTextBox(const QString &sValue,
                               QPoint &showPos,
                               const QSize &size = QSize(300, 100)) = 0;

    virtual void switchTextBoxModule() = 0;
    virtual void setTextFormatInfo(const QString &sType, const QVariant &info) = 0;
};
Q_DECLARE_INTERFACE( IHHFrameTextBoxController, "com.hht.qtWhiteBoard.IHHFrameTextBoxController/1.0" )
Q_DECLARE_METATYPE( IHHFrameTextBoxController* )

#endif // IHHFRAMETEXTBOXCONTROLLER_H
