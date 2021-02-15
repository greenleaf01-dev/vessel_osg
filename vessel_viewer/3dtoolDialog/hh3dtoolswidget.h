#ifndef HH3DTOOLSWIDGET_H
#define HH3DTOOLSWIDGET_H

#include <QWidget>
#include <QVariantMap>
#include <QMouseEvent>
#include <QPainter>

#include "src_toolbar/hhtoolbarbuttonpanel.h"

class IHHApplication;
class HH3DToolsWidget : public QWidget
{
    Q_OBJECT

public:
    HH3DToolsWidget(QWidget *parent=0);
    ~HH3DToolsWidget();

    void setIHHApplication(IHHApplication* pIApp);
    void init(const QVariantMap &params);

    void retranslateUi();

    void setViewerHeight( int nHeight );//2017.9.5 wyp

	/*/TTQX-zhaozhengze-[B160725-038]【工具】三维工具，涂色问题
	/*/
    QToolButton* getToolBarButtonById(const QString& strID);
	//*/

    HHToolbarButtonPanel* m_pHHToolbar_Pyramid;
    HHToolbarButtonPanel* m_pHHToolbar_Prism;
signals:
    void sigSendEventToApp(bool);
    void signalClickButton(QString strID, QVariantMap param);
public slots:
    void slotClickButton(QString strID, QVariantMap param);
protected:
	virtual void closeEvent(QCloseEvent *event);
private:    
    void connectSignals();
    void createToolBars();
    void setWidgetsToLayout();

    HHToolbarButtonPanel* m_pHHToolbar_left;
    HHToolbarButtonPanel* m_pHHToolbar_right_top;
    HHToolbarButtonPanel* m_pHHToolbar_right_bottom;

    QVariantMap m_params;
    IHHApplication* m_pIApp;
    QWidget* m_pView;
    double m_scale;
};

#endif // HH3DTOOLSWIDGET_H

