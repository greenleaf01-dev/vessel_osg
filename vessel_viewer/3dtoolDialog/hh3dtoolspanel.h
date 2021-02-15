#ifndef HH3DTOOLSPANEL_H
#define HH3DTOOLSPANEL_H

#include <QWidget>
#include <QVariantMap>
#include <QMouseEvent>
#include <QPainter>
#include "lib_3dtools.h"

#include "hhpanelwithnail.h"

class HH3DToolsWidget;
class IHHApplication;

/*/TTQX-zhaozhengze-三维崩溃的问题
/*/
//bool LIB_EXPORT_3DTOOLS isVersionSuitable();
//*/

class HH3DToolsPanel : public HHPanelWithNail
{
    Q_OBJECT

public:
    HH3DToolsPanel(QWidget *parent=0);
    ~HH3DToolsPanel();

    void setIHHApplication(IHHApplication* pIApp);
    void init(const QVariantMap &params);

    void showWindow();//2017.9.5 wyp

public slots:
    void sltReceiveEvent(bool sig);
    void sltClose();

protected:
    void changeEvent(QEvent *e);
    void paintEvent(QPaintEvent *event);

private:
    void retranslateUi();

    HH3DToolsWidget    *m_pHH3DToolsWidget = nullptr;

    QVariantMap m_params;
    IHHApplication* m_pIApp;
    double m_scale;//自适应比例因子
    QRect  rect;
public:
    static  HH3DToolsPanel       *m_3DToolsPanel;
};

#endif // HH3DTOOLSPANEL_H

