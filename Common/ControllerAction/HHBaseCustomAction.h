#ifndef HHBASECUSTOMACTION_H
#define HHBASECUSTOMACTION_H

#include <QAction>
#include <QJsonObject>

#include "lib_hhcontrolleraction_global.h"
#include "ihhaction.h"

class IHHCanvas;

class HHCONTROLLERACTIONSHARED_EXPORT HHBaseCustomAction : public QAction, public IHHAction
{
    Q_OBJECT
    Q_INTERFACES(IHHAction)
    Q_PROPERTY(QString ID READ id WRITE setID)
    Q_PROPERTY(IHHCanvas* Canvas READ canvas WRITE setCanvas)
    Q_PROPERTY(QJsonObject PropertyInfo READ propertyInfo WRITE setPropertyInfo)
    Q_PROPERTY(QString Scenario READ scenario WRITE setScenario)
    Q_PROPERTY(QString From READ from WRITE setFrom)

public:
    explicit HHBaseCustomAction(QObject *parent = nullptr);
    explicit HHBaseCustomAction(const QString &text, QObject *parent = nullptr);
    explicit HHBaseCustomAction(const QIcon &icon, const QString &text, QObject *parent = nullptr);

    virtual QObject *getObject();
    virtual QAction *getAction();

    QString id();
    virtual void setID(const QString &sID);

    IHHCanvas *canvas();
    virtual void setCanvas(IHHCanvas *pIHHCanvas);

    virtual QJsonObject propertyInfo();
    virtual void setPropertyInfo(const QJsonObject &info);

    virtual void triggerAction();
    virtual void triggerAction(const QJsonObject &info);

    virtual void bindingUI(IHHTestAutoUI *pIAutoTestUI);
    virtual void unBindingUI(IHHTestAutoUI *pIAutoTestUI);

    virtual bool isSucceed(QJsonObject &info);

    virtual void notifyErrorInfo(const QJsonObject &info);
    virtual void notifySucceeInfo(const QJsonObject &info);

    virtual QString scenario();
    virtual void setScenario(const QString &scenario);
    virtual void setScenario(IHHScenario *&pIHHScenario);

    virtual QString from();
    virtual void setFrom(const QString &sFrome);

    void getBaseActionInfo(QJsonObject &info);

    virtual void bingingStatisticsAction(IHHAction *pIHHAction);

signals:
    void customTriggered(const QVariantMap &info = QVariantMap(), bool checked = false);
    void customTriggered(const QString &sActionID, const QVariantMap &info = QVariantMap(), bool checked = false);

public slots:

protected:
    QString                    m_sID;
    IHHCanvas                  *m_pIHHCanvas;
    QJsonObject                 m_propertyInfoJson;
    bool                        m_bIsSucceed;
    QList<IHHTestAutoUI*>       m_lBindingUI;
    QJsonObject                 m_triggeredInfo;

    QString                     m_sCurScenario;
    QString                     m_sCurFrom;

    QStringList                 m_lPropertyChanged;

    IHHScenario                 **m_pIHHCurScenario;

    IHHAction                   *m_pIHHStatisticsAction;

private:

};

#endif // HHBASECUSTOMACTION_H
