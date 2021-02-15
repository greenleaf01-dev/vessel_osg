#include "hhpanelwithnail.h"

HHPanelTitle::HHPanelTitle(QWidget *parent)
    :QWidget(parent)
{
    this->setObjectName("HHPanelTitle");
    QWidget::installEventFilter(this);

    m_parentWidget = parent;
}

void HHPanelTitle::init(const QVariantMap &params)
{
    m_scale = params["scalefactor"].toDouble();
    m_strTitle = "title";
    m_strTitleSub = "subtitle";
    m_strNailIconPath = params.value("NailIconPath").toString();
    m_strNailedIconPath = params.value("NailedIconPath").toString();

    m_plblTitle = new QLabel(QObject::tr(m_strTitle.toLatin1().data()),this);
    m_plblTitleSub = new QLabel(QObject::tr(m_strTitleSub.toLatin1().data()),this);
    m_btnNail = new QPushButton(QIcon(m_strNailIconPath),"",this);
    m_btnNail->setFlat(true);

//#ifdef HiteTouchPro_CONF
    m_btnClose = new QPushButton(this);
    m_btnClose->setIcon(QIcon(params.value("CloseIconPath").toString()));
    m_plblTitle->setStyleSheet(QString("font-size:%1px; color: #333333;").arg(18*m_scale));
    m_plblTitleSub->setStyleSheet(QString("font-size:%1px; color:#ffffff;").arg(18*m_scale));
    setStyleSheet("QWidget#HHPanelTitle{background-color:#ffffff;border-bottom:1px solid #cfcfcf;border-top:1px solid #cfcfcf;}");
//#endif

    m_btnClose->setIconSize(QSize(30*m_scale,30*m_scale));
    m_btnNail->setIconSize(QSize(30*m_scale,30*m_scale));
    m_btnClose->setStyleSheet("QPushButton{background-color:transparent;border-radius:0px;}");
    m_btnNail->setStyleSheet("QPushButton{background-color:transparent;border-radius:0px;}");

    m_btnClose->setFlat(true);
    QHBoxLayout *titleCharacter = new QHBoxLayout();
    titleCharacter->addWidget(m_plblTitle);
    titleCharacter->addWidget(m_plblTitleSub);
    titleCharacter->setSpacing(34*m_scale);

    m_phblTitle = new QHBoxLayout();
    m_phblTitle->setSpacing(10*m_scale);
    m_phblTitle->setContentsMargins(10*m_scale,10*m_scale,10*m_scale,10*m_scale);

    m_phblTitle->addLayout(titleCharacter,Qt::AlignLeft|Qt::AlignHCenter);
    m_phblTitle->addStretch(50*m_scale);
    m_phblTitle->addWidget(m_btnNail);
    m_phblTitle->addWidget(m_btnClose);
    this->setLayout(m_phblTitle);

    m_bIsPressed = false;
    m_bNailed = false;

    m_posPressed = QPoint(0,0);

    setObjectName("HHPanelTitle");
}

HHPanelTitle::~HHPanelTitle()
{

}

void HHPanelTitle::setTitle(QString strTitle)
{
    m_strTitle = strTitle;
   // m_plblTitle->setText(QObject::tr(m_strTitle.toLatin1().data()));
	m_plblTitle->setText(m_strTitle);
    m_strTitleSub = "";
    m_plblTitleSub->setText(m_strTitleSub);
}

void HHPanelTitle::setTitle(QString strTitle1, QString strTitle2)
{
    m_strTitle = strTitle1;
    m_plblTitle->setText(m_strTitle);
    m_strTitleSub = strTitle2;
    m_plblTitleSub->setText(m_strTitleSub);
}

bool HHPanelTitle::eventFilter(QObject *watched, QEvent *event)
{   
    qDebug()<< "HHPanelTitle::eventFilter:"<<this->objectName();
    if( watched == this && QEvent::WindowDeactivate == event->type())
    {
        qDebug()<< "HHPanelTitle::eventFilter:" << m_bNailed;

        QPoint pt = QCursor::pos();
        bool bIsClickedInside = m_parentWidget->geometry().contains(pt);
        qDebug()<< "QCursor::pos():" << pt;
        qDebug()<< "this:" << m_parentWidget->geometry()<<bIsClickedInside;
		/*/TTQX-zhaozhengze-[B170518 - 002]【工具】显示三维工具后，切换其他windows窗口再回来，三维工具不见了
        /*/
		if (false && !bIsClickedInside && !m_bNailed)
		{
			m_btnClose->click();
		}
		//*/
        return true;
    }

    return false;
}

void HHPanelTitle::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

void HHPanelTitle::mousePressEvent(QMouseEvent *event)
{
    m_bIsPressed = true;
    m_posPressed = event->pos();
    QWidget::mousePressEvent(event);
}

void HHPanelTitle::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bIsPressed)
    {
        int dx = event->pos().x() - m_posPressed.x();
        int dy = event->pos().y() - m_posPressed.y();

        emit sigPositionChanged(dx,dy);

       // m_posPressed = event->pos();

    }
    QWidget::mouseMoveEvent(event);
}

void HHPanelTitle::mouseReleaseEvent(QMouseEvent *event)
{
    m_bIsPressed = false;
    QWidget::mouseReleaseEvent(event);
}


HHPanelWithNail::HHPanelWithNail(QWidget *parent)
    :QWidget(parent)
{
    m_pwndParent = parent;
    m_pwndContent = NULL;
	m_bNailed = false;
}

void HHPanelWithNail::init(const QVariantMap &params)
{
    qDebug()<<"new HHPanelTitle start.";
    m_scale = params["scalefactor"].toDouble();
    m_pPanelTitle = new HHPanelTitle(this);
    m_pPanelTitle->init(params);
   // m_pPanelTitle->setFixedHeight(52*m_scale);
    m_pvblMain = new QVBoxLayout();

    m_pvblMain->setSpacing(0);

    m_pvblMain->addWidget(m_pPanelTitle);
    m_pvblMain->addStretch(1*m_scale);

    this->setLayout(m_pvblMain);
    this->setObjectName("HHPanelWithNail");

    m_pvblMain->setContentsMargins(1*m_scale,0,1*m_scale,1*m_scale);
    this->setStyleSheet(QString("QWidget#HHPanelWithNail{background-color:white;border:1px solid #cfcfcf;border-radius:%1px;}").arg(3*m_scale));
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);

    connect(m_pPanelTitle->m_btnNail,SIGNAL(clicked()),this,SLOT(sltNailButtonClicked()));
    connect(m_pPanelTitle,SIGNAL(sigPositionChanged(int,int)),this,SLOT(sltPositionChanged(int,int)));
}

HHPanelWithNail::~HHPanelWithNail()
{
}

void HHPanelWithNail::setTitle(QString strTitle)
{
    m_pPanelTitle->setTitle(strTitle);
}

void HHPanelWithNail::setTitle(QString strTitle1, QString strTitle2)
{
    m_pPanelTitle->setTitle(strTitle1,strTitle2);
}

void HHPanelWithNail::setContentPanel(QWidget *contentPanel)
{
    if(m_pwndContent)
    {
        m_pvblMain->removeWidget(m_pwndContent);
    }
    //m_pwndContent = contentPanel;
	contentPanel->setFixedWidth(this->width() - 1);
	contentPanel->setFixedHeight(this->height() - m_pPanelTitle->height()-1);
    m_pvblMain->insertWidget(1,m_pwndContent,1);
}

void HHPanelWithNail::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

void HHPanelWithNail::resizeEvent(QResizeEvent *event)
{
    if(m_pwndContent)
    {
        m_pwndContent->adjustSize();
        m_pwndContent->setFixedHeight(this->height() - m_pPanelTitle->height());
    }
    QWidget::resizeEvent(event);
}

void HHPanelWithNail::sltNailButtonClicked()
{
    m_pPanelTitle->m_bNailed = !m_pPanelTitle->m_bNailed;

    QString strIcon;
    if(m_pPanelTitle->m_bNailed)
        strIcon = m_pPanelTitle->m_strNailedIconPath;
    else
        strIcon = m_pPanelTitle->m_strNailIconPath;
    m_pPanelTitle->m_btnNail->setIcon(QIcon(strIcon));

    m_bNailed = m_pPanelTitle->m_bNailed;
}

void HHPanelWithNail::sltPositionChanged(int dx, int dy)
{
    QPoint oldPos;
    if(m_bNailed)
    {
        oldPos = this->mapToParent(QPoint(0,0));
    }
    else
    {
        oldPos = this->mapToGlobal(QPoint(0,0));
    }

    QPoint newPos = QPoint(oldPos.x() + dx,oldPos.y() + dy);
   // this->setGeometry(newPos.x(),newPos.y(),this->width(),this->height());
    this->move(newPos.x(),newPos.y());
}

