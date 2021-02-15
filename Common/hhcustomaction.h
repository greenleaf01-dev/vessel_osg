#ifndef HHCUSTOMACTION_H
#define HHCUSTOMACTION_H

#include <QAction>
#include <QJsonObject>

#include "lib_framecontroller_global.h"

class FRAMECONTROLLERSHARED_EXPORT HHCustomAction : public QAction
{
    Q_OBJECT

public:
    explicit HHCustomAction(QObject *parent = nullptr);
    explicit HHCustomAction(const QString &text, QObject *parent = nullptr);
    explicit HHCustomAction(const QIcon &icon, const QString &text, QObject *parent = nullptr);

    void setCustomInfo(const QJsonObject &info);
    QJsonObject getCustomInfo();

signals:
    void customTriggered(const QVariantMap &info = QVariantMap(), bool checked = false);
    void customTriggered(const QString &sActionID, const QVariantMap &info = QVariantMap(), bool checked = false);

public slots:

private:
    QJsonObject                 m_jsonCustomInfo;
};

#endif // HHCUSTOMACTION_H
