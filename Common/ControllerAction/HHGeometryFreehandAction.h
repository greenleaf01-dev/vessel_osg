//智能笔
#ifndef HHGEOMETRYFREEHANDACTION_H
#define HHGEOMETRYFREEHANDACTION_H

#include <QObject>
#include "HHBaseCustomAction.h"
#include "lib_hhcontrolleraction_global.h"

class IHHSwitchModuleController;
class IHHModule;

class HHCONTROLLERACTIONSHARED_EXPORT HHGeometryFreehandAction : public HHBaseCustomAction
{
    Q_OBJECT
    Q_PROPERTY(int Width READ width WRITE setWidth)
    Q_PROPERTY(QColor Color READ color WRITE setColor)
    Q_PROPERTY(QString DashStyle READ dashStyle WRITE setDashStyle)
    Q_PROPERTY(int RecognitionTime READ recognitionTime WRITE setRecognitionTime)

public:
    explicit HHGeometryFreehandAction(
            IHHSwitchModuleController *pController,
            QObject *parent = nullptr);

    int width();
    void setWidth(int nWidth);

    QColor color();
    void setColor(const QColor &color);

    QString dashStyle();
    void setDashStyle(const QString &sDashStyle);

    int recognitionTime();
    void setRecognitionTime(int nTime);

    virtual void setPropertyInfo(const QJsonObject &info);
    virtual QJsonObject propertyInfo();

    virtual void triggerAction(const QJsonObject &info);

signals:
    void signalStrokeChangColor(const QColor &color);
    void signalStrokeChangWidth(int nWidth);
    void signalStrokeChangDashStyle(const QString &style);
    void signalStrokeChangRecognitionTime(int nTime);
    void signalStrokePropertyChange(QJsonObject);

public slots:
    void slotChangePropertyInfo(const QJsonObject &info);

private slots:
    void slotTriggered(bool);

private:
    void initSystemScale();
    void loadDefault();
    void updateModuleData();

private:
    IHHSwitchModuleController    *m_pIHHController;
    IHHModule                    *m_pIHHModule;

    int                         m_nWidth;
    QColor                      m_color;
    QString                     m_sCurDashStyle;
    int                         m_nCurRecognitionTime;

    int                         m_nDrawLineShape;
};

#endif // HHGEOMETRYFREEHANDACTION_H
