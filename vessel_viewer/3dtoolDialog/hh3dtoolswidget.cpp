#include "hh3dtoolswidget.h"
#include "viewerwidget.h"

QString getCloseFillColorString()
{
	return  QObject::tr("ID_3D_CLOSE_FILL_COLOR");
}
HH3DToolsWidget::HH3DToolsWidget(QWidget *parent)
: QWidget(parent), m_pView(NULL)
{
    setObjectName("HH3DToolsWidget");
}

HH3DToolsWidget::~HH3DToolsWidget()
{
}

void HH3DToolsWidget::retranslateUi()
{
    QObject::tr("ID_MATH_3D_CUBE"); QObject::tr( "ID_MATH_3D_PRISM");
    QObject::tr("ID_MATH_3D_SPHERE"); QObject::tr("ID_MATH_3D_COLUMN"); QObject::tr("ID_MATH_3D_CONE");
    QObject::tr("ID_MATH_3D_TETRAHEDRAL"); QObject::tr("ID_MATH_3D_PYRAMID");
    QObject::tr("ID_MATH_3D_ThreeSurface_Prism");

    QObject::tr("ID_MATH_3D_FourSurface_Pyramid");
    QObject::tr("ID_MATH_3D_MultiSurface_Pyramid");
    QObject::tr("ID_MATH_3D_SixSurface_Pyramid");

    QObject::tr("ID_MATH_3D_FourSurface_Prism");
    QObject::tr("ID_MATH_3D_MultiSurface_Prism");
    QObject::tr("ID_MATH_3D_SixSurface_Prism");

    QObject::tr("ID_3D_FILL_COLOR");QObject::tr("ID_3D_Opacity");
    QObject::tr("ID_3D_MODE_WIRE");QObject::tr("ID_3D_MODE_SOLID"); QObject::tr( "ID_3D_FrontView");
    QObject::tr("ID_3D_LeftView"); QObject::tr("ID_3D_TopView");

    QObject::tr("ID_3D_Reset"); QObject::tr( "ID_3D_ZOOMIN");
    QObject::tr("ID_3D_ZOOMOUT");
	QObject::tr("ID_3D_CLOSE_FILL_COLOR");

    m_pHHToolbar_left->retranslateUi();
    m_pHHToolbar_right_top->retranslateUi();
    m_pHHToolbar_right_bottom->retranslateUi();
    m_pHHToolbar_Prism->retranslateUi();
    m_pHHToolbar_Pyramid->retranslateUi();
}

/*/TTQX-zhaozhengze-[B160725-038]【工具】三维工具，涂色问题
/*/
QToolButton* HH3DToolsWidget::getToolBarButtonById(const QString& strID)
{
    QToolButton* pPtn = m_pHHToolbar_left->getToolBarButtonById(strID);
	if (NULL != pPtn)
	{
		return pPtn;
	}

	pPtn = m_pHHToolbar_right_top->getToolBarButtonById(strID);
	if (NULL != pPtn)
	{
		return pPtn;
	}

	pPtn = m_pHHToolbar_right_bottom->getToolBarButtonById(strID);
	if (NULL != pPtn)
	{
		return pPtn;
	}

	pPtn = m_pHHToolbar_Prism->getToolBarButtonById(strID);
	if (NULL != pPtn)
	{
		return pPtn;
	}

	return m_pHHToolbar_Pyramid->getToolBarButtonById(strID);

}
//*/

void HH3DToolsWidget::setIHHApplication(IHHApplication* pIApp)
{
    m_pIApp = pIApp;
}

void HH3DToolsWidget::init(const QVariantMap &params)
{
    m_params = params;
    m_scale = m_params["scalefactor"].toDouble();
	this->setGeometry(10, 10,1000, 800);

    createToolBars();
    setWidgetsToLayout();

    m_pHHToolbar_Pyramid->hide();
    m_pHHToolbar_Prism->hide();
}

void HH3DToolsWidget::createToolBars()
{
    QStringList m_ids[5];
    m_ids[0]<<"ID_MATH_3D_CUBE"<<"ID_MATH_3D_PRISM"
         <<"ID_MATH_3D_SPHERE"<<"ID_MATH_3D_COLUMN"<<"ID_MATH_3D_CONE"
        <<"ID_MATH_3D_TETRAHEDRAL"<<"ID_MATH_3D_ThreeSurface_Prism";

    m_ids[1]  //<<"ID_3D_FILL_COLOR"//<<"ID_3D_Opacity"
          <<"ID_3D_MODE_SOLID"
		  << "ID_3D_FrontView" << "ID_3D_LeftView" << "ID_3D_TopView" << "ID_3D_FILL_COLOR";

    m_ids[2]<<"ID_3D_Reset"<<"ID_3D_ZOOMIN" <<"ID_3D_ZOOMOUT";

    m_ids[3]<<"ID_MATH_3D_TETRAHEDRAL"<<"ID_MATH_3D_FourSurface_Pyramid"<<"ID_MATH_3D_MultiSurface_Pyramid"<<"ID_MATH_3D_SixSurface_Pyramid";
    m_ids[4]<<"ID_MATH_3D_ThreeSurface_Prism"<<"ID_MATH_3D_FourSurface_Prism"<<"ID_MATH_3D_MultiSurface_Prism"<<"ID_MATH_3D_SixSurface_Prism";

    QString pixmapPath = m_params.value("btnImageDir").toString();

	auto size = m_params.value("IConSize");
    QSize IConSize = m_params.value("IConSize").toSize()*m_scale;
    int FontSize = m_params.value("FontSize").toInt();

    int Column=1;
    int RadiusSize=15*m_scale;
    QVariantMap params;

        params["Column"]=Column;
        params["PixmapPath"]=pixmapPath;
        params["PixmapPostfix"]="png";
        params["IConSize"]=IConSize;
        params["FontSize"]=FontSize;
        params["FontColor"]="#333333";
        params["BackgroundColor"]="#f0f0f0";
        params["PanelSize"]=QSize(Column*(IConSize.width()+FontSize+10*m_scale)+10*m_scale,RadiusSize*3);
        params["scalefactor"] = m_scale;

        params["ToolButtonStyle"] = Qt::ToolButtonTextUnderIcon;

    m_pHHToolbar_left = new HHToolbarButtonPanel(this);
    m_pHHToolbar_right_top = new HHToolbarButtonPanel(this);
    m_pHHToolbar_right_bottom = new HHToolbarButtonPanel(this);

    m_pHHToolbar_Pyramid = new HHToolbarButtonPanel(this);
    m_pHHToolbar_Prism = new HHToolbarButtonPanel(this);

    m_pHHToolbar_Pyramid->setObjectName("m_pHHToolbar_Pyramid");
    m_pHHToolbar_Prism->setObjectName("m_pHHToolbar_Prism");

    HHToolbarButtonPanel* m_pHHToolbar_edit;
    QStringList listIDs_HavingSubMenu;

    for(int i=0; i<5; i++)
    {
        listIDs_HavingSubMenu.clear();

        if(i==0)
        {
            m_pHHToolbar_edit = m_pHHToolbar_left;
            listIDs_HavingSubMenu<<"ID_MATH_3D_TETRAHEDRAL"<<"ID_MATH_3D_ThreeSurface_Prism";
        }
        else if(i==1)
            m_pHHToolbar_edit = m_pHHToolbar_right_top;
        else if(i==2)
        {
            m_pHHToolbar_edit = m_pHHToolbar_right_bottom;
            params.remove("ToolButtonStyle");
            params["ToolButtonStyle"] = Qt::ToolButtonIconOnly;
        }
        else if(i==3)
        {
            m_pHHToolbar_edit = m_pHHToolbar_Pyramid;
            params.remove("Column");
            params["Column"] = 4;
            params.remove("ToolButtonStyle");
            params["ToolButtonStyle"] = Qt::ToolButtonTextUnderIcon;
        }
        else if(i==4)
            m_pHHToolbar_edit = m_pHHToolbar_Prism;


        params["IDList"]=m_ids[i];
        params["IDs_HavingSubMenu"] = listIDs_HavingSubMenu;

        m_pHHToolbar_edit->init(params);
        m_pHHToolbar_edit->retranslateUi();           

        bool bChecked = false;
        bChecked =connect(m_pHHToolbar_edit, SIGNAL(signalClickButton(QString,QVariantMap)),
                          this, SLOT(slotClickButton(QString,QVariantMap)));
        Q_ASSERT(bChecked);
    }
}

void HH3DToolsWidget::setWidgetsToLayout()
{
    QVBoxLayout *vLayout0 = new QVBoxLayout();
    vLayout0->setSpacing(0);
    vLayout0->setContentsMargins(0,0,0,0);
    vLayout0->addWidget(m_pHHToolbar_left);
    vLayout0->addStretch(0);

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setSpacing(0);
    vLayout->setContentsMargins(0,0,0,0);
    vLayout->addWidget(m_pHHToolbar_right_top);
    vLayout->addStretch(0);
    vLayout->addWidget(m_pHHToolbar_right_bottom);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setSpacing(0);
    hLayout->setContentsMargins(0,0,0,0);

	if (NULL != m_pView)
	{
		delete m_pView; 
	}

    m_pView = new ViewerWidget(this);
	//m_pView = ViewerWidget::getOsgWiget();
    m_pView->setCursor(QCursor(Qt::PointingHandCursor));
    //connect(this, SIGNAL(signalClickButton(QString, QVariantMap)), m_pView, SLOT(slotClickButton(QString, QVariantMap)));

	hLayout->addLayout(vLayout0);
	hLayout->addWidget(m_pView);
    hLayout->addLayout(vLayout);

//    m_phblTitle->addLayout(titleCharacter,Qt::AlignLeft|Qt::AlignHCenter);

    this->setLayout(hLayout);
}

void HH3DToolsWidget::connectSignals()
{
//    bool bChecked = false;
//    bChecked =connect(m_pHHToolbar_edit, SIGNAL(signalClickButton(QString,QVariantMap)),
//                      this, SLOT(slotClickButton(QString,QVariantMap)));
//    Q_ASSERT(bChecked);
}

void HH3DToolsWidget::slotClickButton(QString strID, QVariantMap param)
{
    qDebug()<<"HH3DToolsWidget::slotClickButton start."<<strID;

    QStringList listIDs_HavingSubMenu;
    listIDs_HavingSubMenu<<"ID_MATH_3D_TETRAHEDRAL"<<"ID_MATH_3D_ThreeSurface_Prism";

    HHToolbarButtonPanel *pToolbar = qobject_cast<HHToolbarButtonPanel *>(sender());
    if(pToolbar == m_pHHToolbar_left && listIDs_HavingSubMenu.contains(strID, Qt::CaseInsensitive))
    {
        qDebug()<<"show sub panel.";

        HHToolbarButtonPanel* m_pHHToolbar_edit;

        if(strID.contains("ID_MATH_3D_TETRAHEDRAL", Qt::CaseInsensitive))
            m_pHHToolbar_edit = m_pHHToolbar_Pyramid;
        else
            m_pHHToolbar_edit = m_pHHToolbar_Prism;

        int x = param[ "x" ].toInt();
        int y = param[ "y" ].toInt();
        int w = param[ "width" ].toInt();
        int h = param[ "height" ].toInt();

        m_pHHToolbar_edit->setWindowFlags(Qt::Popup | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
        m_pHHToolbar_edit->move(x+w, y);
        m_pHHToolbar_edit->show();
    }
    else
    {
        emit signalClickButton(strID, param);
    }
}
void HH3DToolsWidget::closeEvent(QCloseEvent *event)
{  
	ViewerWidget* pQtView = dynamic_cast<ViewerWidget*>(m_pView);
	if (nullptr != pQtView)
	{
		pQtView->closeLocalEvent(event);
	}
	QWidget::closeEvent(event);
}

//2017.9.5 wyp start
void HH3DToolsWidget::setViewerHeight( int nHeight )
{
    if( m_pView != NULL && nHeight != 0 )
    {
        m_pView->setFixedHeight( nHeight );
    }
}
//2017.9.5 wyp end
