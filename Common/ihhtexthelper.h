#ifndef IHHTEXTHELPER_H
#define IHHTEXTHELPER_H
#include <QObject>
#include <QSize>
#include <QJsonObject>

class IHHPrimitiveItem;
class IHHTextHelper
{
public:
    virtual QObject* getObject() = 0;
    virtual void createTextBox(const QString &sValue, const QJsonObject& textFormat = QJsonObject(),
		QPoint &showPos  = QPoint(), const QSize &size = QSize(300, 100)) = 0;
};
Q_DECLARE_INTERFACE(IHHTextHelper, "com.hht.qtWhiteBoard.IHHTextHelper/1.0")
Q_DECLARE_METATYPE(IHHTextHelper*)
#endif // IHHTEXTHELPER_H
