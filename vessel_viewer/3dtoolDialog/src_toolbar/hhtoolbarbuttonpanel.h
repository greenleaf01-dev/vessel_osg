/******************************************************
    QVariantMap param:
    param["IDList"]     =m_Ids(QStringList);    //Key point
    param["Column"]     =m_nCountPerLine(int);
    param["PixmapPath"] =m_strPixmapPath(QString);
    param["PixmapPostfix"]=m_strPixmapPostfix(QString);
    param["IConSize"]   =m_setIConSize(QSize);
    param["FontSize"]   =m_setFontSize(int);
    param["FontColor"]  =m_setFontcolor(QString);
    param["BackgroundColor"]=m_setBackgroundColor(QString);
    param["PanelSize"]  =m_setPanelSize(QSize); //Not Used
    param["TitleID"]    =m_TitleID(QString);    //Not Used
    param["CloseBtnID"] =m_CloseBtnID(QString); //Not Used
    param["RadiusSize"] =m_setRadiusSize(int);  //Not Used
    param["CircleColor"]=m_setCircleColor(QString);//Not Used
    param["SliderMaximum"]=m_setSliderMaximum(int);//Not Used
    param["SliderMinimum"]=m_setSliderMinimum(int);//Not Used
*******************************************************/
#ifndef HHTOOLBARBUTTONPANEL_H
#define HHTOOLBARBUTTONPANEL_H

#include <QtWidgets>
#include <QStringList>


class HHToolbarButtonPanel : public QWidget
{
    Q_OBJECT
public:
    explicit HHToolbarButtonPanel(QWidget *parent = 0);

    void init(QVariantMap param); 
    void retranslateUi();
	/*/TTQX-zhaozhengze-[B160725-038]【工具】三维工具，涂色问题
	/*/
    QToolButton* getToolBarButtonById(const QString& strID);

    void setPanelBackgroundColor(const QString &strColor);
    void setPanelFixedSize();
    QSize getPanelFixedSize();
    QPixmap setToolButtonIcons(const QString &str,const QSize &size);
    QVariantMap getParam(QToolButton *_button);

signals:
    void signalClickButton(QString strID, QVariantMap param);

public slots:
    void btnPanelClicked(bool bChecked);
    void slotBtnChecked(QString strID);

private:
    void getInitParameters(QVariantMap param);
    QWidget         *m_HHParent;
    QStringList      m_Ids;
    int              m_nCountPerLine;
    QString          m_strPixmapPath;
    QString          m_strPixmapPostfix;
    QSize            m_setIconSize;
    int              m_setFontSize;
    QString          m_setFontColor;
    QString          m_setBackgroundColor;
    QSize            m_setPanelSize;
    QString          m_TitleID;
    QString          m_CloseBtnID;

    int              m_nSpacing;
    QSize            m_setButtonSize;
    QGridLayout     *m_gridLayout;

    Qt::ToolButtonStyle m_enumBtnStyle;
    double           m_scale;
};

#endif // HHTOOLBARBUTTONPANEL_H
