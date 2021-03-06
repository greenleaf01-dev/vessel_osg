#include "hh3dtoolspanel.h"
#include "hh3dtoolswidget.h"
#include <string>
#include "ihhapplication.h"
#include "ihhframe.h"
#include "viewerwidget.h"
//*/TTQX-zhaozhengze-?????????????
/*/
bool isVersionSuitable()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    //???崰???С
    glutInitWindowSize(300, 300);
    //???崰??λ??
    glutInitWindowPosition(100, 100);
    //????????
    glutCreateWindow("OpenGL Version");
    const GLubyte* name = glGetString(GL_VERSION); //??????????OpenGL???????????
    if (NULL == name)
    {
        return false;
    }

    std::string strVersion = (char*)name;
    QString strBuf = QString::fromUtf8(strVersion.c_str());
    qDebug()<<"opengl version:"<<strBuf;

    if (strVersion.size() < 3)
    {
        return false;
    }
    std::string strSub = strVersion.substr(0, 3);
    std::string strCom1 = "1.1";
    std::string strCom = "1.0";

    QString str = QString::fromUtf8(strSub.c_str());
    qDebug()<<"GL_VERSION:"<<str;
    if (strSub == strCom1 || strSub == strCom)
    {
        return false;
    }
    return  true;
}
//*/

HH3DToolsPanel*  HH3DToolsPanel::m_3DToolsPanel = nullptr;
// HH3DToolsPanel start
HH3DToolsPanel::HH3DToolsPanel(QWidget *parent)
    :HHPanelWithNail(parent)
{
    m_3DToolsPanel = this;
	rect = QRect(50, 50, 1000, 1000);
	if (nullptr != parent)
	{
		rect = parentWidget()->geometry();
	}
    this->setFixedSize(rect.width() * 0.8, rect.height() * 0.8);
    this->setGeometry(rect.width() * 0.05, rect.height() * 0.1, rect.width() * 0.8, rect.height() * 0.8);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	//this->setWindowModality(Qt::WindowModal);//阻挡父亲窗口内其他控件，除非本dialog关闭
    m_pIApp = NULL;
}

HH3DToolsPanel::~HH3DToolsPanel() {
}

void HH3DToolsPanel::setIHHApplication(IHHApplication* pIApp)
{
    m_pIApp = pIApp;
}

ViewerWidget*  pView = nullptr;
void HH3DToolsPanel::init(const QVariantMap &params)
{  
	this->setGeometry(100, 100, 800, 600);

    qDebug()<<"HH3DToolsPanel::init start.";
    m_scale = params["scalefactor"].toDouble();


    HHPanelWithNail::init(params);

    connect(m_pPanelTitle->m_btnClose,SIGNAL(clicked()),this,SLOT(sltClose()));
    m_params = params;    

    m_pHH3DToolsWidget = new HH3DToolsWidget(this);
    m_pHH3DToolsWidget->init(m_params);
    connect(m_pHH3DToolsWidget,SIGNAL(sigSendEventToApp(bool)),this,SLOT(sltReceiveEvent(bool)));
    setContentPanel(m_pHH3DToolsWidget);
	//m_pvblMain->insertWidget(1, m_pHH3DToolsWidget, 1);
    m_pHH3DToolsWidget->raise();
    m_pHH3DToolsWidget->show();


    qDebug()<<"init end.";
}

void HH3DToolsPanel::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi();
        break;
    default:
        break;
    }
}

void HH3DToolsPanel::retranslateUi()
{
    setTitle(QObject::tr("ID_TOOL_3DTOOLS"));
    m_pHH3DToolsWidget->retranslateUi();
}

void HH3DToolsPanel::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

void HH3DToolsPanel::sltReceiveEvent(bool sig)
{
    if(!m_bNailed)
    {
        this->hide();
    }
}

void HH3DToolsPanel::sltClose()
{
    m_pPanelTitle->m_bNailed= true;
    sltNailButtonClicked();

    m_pHH3DToolsWidget->m_pHHToolbar_Prism->hide();
    m_pHH3DToolsWidget->m_pHHToolbar_Pyramid->hide();

    this->hide();
}

//2017.9.5 wyp start
void HH3DToolsPanel::showWindow()
{
    this->show();
    int nHeight = m_pHH3DToolsWidget->height();
    nHeight = nHeight - 30*m_scale;
    m_pHH3DToolsWidget->setViewerHeight( nHeight - 3);
}
//2017.9.5 wyp end
