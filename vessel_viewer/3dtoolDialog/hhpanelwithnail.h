#ifndef HHPANELWITHNAIL_H
#define HHPANELWITHNAIL_H

#include <QtWidgets>

class HHPanelTitle : public QWidget
{
    Q_OBJECT
public:
    HHPanelTitle(QWidget *parent);
    ~HHPanelTitle();

    void init(const QVariantMap &params);

    void                    setTitle(QString strTitle);
    void                    setTitle(QString strTitle1,QString strTitle2);

    bool                    eventFilter(QObject *watched, QEvent *event);

protected:
    void                    paintEvent(QPaintEvent *event);
    void                    mousePressEvent(QMouseEvent *event);
    void                    mouseMoveEvent(QMouseEvent *event);
    void                    mouseReleaseEvent(QMouseEvent *event);

public:
    QString                 m_strTitle;
    QString                 m_strTitleSub;
    QString                 m_strNailIconPath;
    QString                 m_strNailedIconPath;
    QLabel                  *m_plblTitle;
    QLabel                  *m_plblTitleSub;

    QPushButton             *m_btnNail;
    QPushButton             *m_btnClose;
    QHBoxLayout             *m_phblTitle;

    bool                    m_bIsPressed;
    bool                    m_bNailed;

    QPoint                  m_posPressed;
    QWidget * m_parentWidget;
    double                  m_scale;
signals:
    void                    sigPositionChanged(int dx,int dy);
};

class HHPanelWithNail : public QWidget
{
    Q_OBJECT
public:
    HHPanelWithNail(QWidget *parent);
    ~HHPanelWithNail();

    void init(const QVariantMap &params);

    void                    setTitle(QString strTitle);
    void                    setTitle(QString strTitle1,QString strTitle2);
    void                    setContentPanel(QWidget *contentPanel);
    bool                    m_bNailed;

protected:
    void                    paintEvent(QPaintEvent *event);
    void                    resizeEvent(QResizeEvent *event);



signals:
    void                    sigSendEventToApp(QString type,QString path);
    void                    sigSendEventToApp(QString strSig);

public slots:
    void                    sltPositionChanged(int dx,int dy);
    void                    sltNailButtonClicked();

public:
    HHPanelTitle            *m_pPanelTitle;
    QVBoxLayout             *m_pvblMain;
    QWidget                 *m_pwndParent;
    QWidget                 *m_pwndContent;
    double                  m_scale;
};

#endif
