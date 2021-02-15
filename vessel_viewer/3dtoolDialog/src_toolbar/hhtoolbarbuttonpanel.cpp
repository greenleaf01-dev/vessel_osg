#include "hhtoolbarbuttonpanel.h"

HHToolbarButtonPanel::HHToolbarButtonPanel(QWidget *parent) : QWidget(parent)
{
    m_HHParent=parent;
    m_nSpacing=10;
}

void HHToolbarButtonPanel::init(QVariantMap param){

    m_scale = param["scalefactor"].toDouble();
    getInitParameters(param);

    QStringList listIDs_HavingSubMenu = param.value("IDs_HavingSubMenu").toStringList();

    m_gridLayout= new QGridLayout(this);
    m_gridLayout->setContentsMargins(10,10,10,10);

    for(int i=0;i<m_Ids.size();i++){
        QString strPixmapPath=QString("%1/%2.%3").arg(m_strPixmapPath).arg(m_Ids.at(i)).arg(m_strPixmapPostfix);
        qDebug()<<"strPixmapPath="<<strPixmapPath;

        QToolButton *button=new QToolButton(this);
        button->setToolButtonStyle(m_enumBtnStyle);

        button->setIcon(setToolButtonIcons(strPixmapPath,m_setIconSize));
        button->setIconSize(m_setIconSize);
        button->setStyleSheet(QString("QToolButton{font-size:%1px;border-width:0px;}").arg(m_setFontSize));
        button->setProperty("ID",m_Ids.at(i));

        button->setAutoRaise(true);
        button->setCheckable(false);
        button->setFixedSize(m_setButtonSize);
        m_gridLayout->addWidget(button, i/m_nCountPerLine, i%m_nCountPerLine);
        m_gridLayout->setAlignment(button, Qt::AlignCenter);

//        if(listIDs_HavingSubMenu.contains(m_Ids.at(i), Qt::CaseInsensitive))
//        {
////            QMenu* pMenu = new QMenu(this);
////            pMenu->addAction("test");
////            button->setMenu(pMenu);
//        }
//        else
        {
            bool bChecked = false;
            bChecked =connect(button,SIGNAL(clicked(bool)),this,SLOT(btnPanelClicked(bool)));
            Q_ASSERT(bChecked);
        }
    }

    retranslateUi();
}
void HHToolbarButtonPanel::getInitParameters(QVariantMap param){
    m_Ids=param["IDList"].toStringList();
    m_nCountPerLine=param["Column"].toInt();
    m_strPixmapPath=param["PixmapPath"].toString();
    m_strPixmapPostfix=param["PixmapPostfix"].toString();
    m_setIconSize=param["IConSize"].toSize();
    m_setFontSize=param["FontSize"].toInt();
    m_setFontColor=param["FontColor"].toString();
    m_setBackgroundColor=param["BackgroundColor"].toString();
    m_setPanelSize=param["PanelSize"].toSize();
    m_TitleID=param["TitleID"].toString();
    m_CloseBtnID=param["CloseBtnID"].toString();

    m_setIconSize = m_setIconSize + QSize( 6*m_scale, 6*m_scale ); //2017.9.5 wyp

    qDebug()<<"--------------HHToolbarButtonPanel------------";
    qDebug()<<"IDList"<<m_Ids;
    qDebug()<<"Column"<<m_nCountPerLine;
    qDebug()<<"PixmapPath"<<m_strPixmapPath;
    qDebug()<<"PixmapPostfix"<<m_strPixmapPostfix;
    qDebug()<<"IConSize"<<m_setIconSize;
    qDebug()<<"FontSize"<<m_setFontSize;
    qDebug()<<"FontColor"<<m_setFontColor;
    qDebug()<<"BackgroundColor"<<m_setBackgroundColor;
    qDebug()<<"PanelSize"<<m_setPanelSize;
    qDebug()<<"TitleID"<<m_TitleID;
    qDebug()<<"CloseBtnID"<<m_CloseBtnID;

    qDebug()<<"ToolButtonStyle var:"<<param["ToolButtonStyle"];
    QVariant var = param["ToolButtonStyle"];
    m_enumBtnStyle = static_cast<Qt::ToolButtonStyle>(var.toInt());
    qDebug() << "m_enumBtnStyle = " << m_enumBtnStyle;

    if(m_Ids.size()==0){
        qDebug()<<"m_Ids.size()==0;";
        return;
    }

    if(m_nCountPerLine>m_Ids.size() || m_nCountPerLine==0){
        qDebug()<<"m_nCountPerLine=="<<m_nCountPerLine;
        m_nCountPerLine=m_Ids.size();
    }

    if(m_strPixmapPostfix.isEmpty()){
        qDebug()<<"m_strPixmapPostfix==png;";
        m_strPixmapPostfix="png";
    }

    if(m_setIconSize.isEmpty()){
        qDebug()<<"m_setIconSize==QSize(32,32);";
        m_setIconSize=QSize(48*m_scale,48*m_scale);
    }

    if(m_setFontSize==0){
        qDebug()<<"m_setFontSize==12;";
        m_setFontSize=12*m_scale;
    }

    if(m_setFontColor.isEmpty()){
        qDebug()<<"m_setFontColor==#333333;";
        m_setFontColor="#333333";
    }

    if(m_setBackgroundColor.isEmpty()){
        qDebug()<<"m_setBackgroundColor==transparent";
        m_setBackgroundColor="#f0f0f0";
    }

    if(m_TitleID.isEmpty()){
        qDebug()<<"m_TitleID.isEmpty()";
        m_TitleID="";
    }

    if(m_CloseBtnID.isEmpty()){
        qDebug()<<"m_TitleID.isEmpty()";
        m_CloseBtnID="";
    }

    if(m_enumBtnStyle == Qt::ToolButtonTextUnderIcon)
        m_setButtonSize=m_setIconSize+QSize(m_setFontSize,m_setFontSize*2);
    else
        m_setButtonSize=m_setIconSize+QSize(m_setFontSize,m_setFontSize);

    qDebug()<<"m_setButtonSize=="<<m_setButtonSize;

    setPanelBackgroundColor(m_setBackgroundColor);

    if(m_setPanelSize.isEmpty()){
        qDebug()<<"m_setPanelSize==this->size()"<<this->size();
        m_setPanelSize=this->size();
    }else{
        setPanelFixedSize();
    }
}

void HHToolbarButtonPanel::retranslateUi()
{
    QList<QToolButton *> btnList = this->findChildren<QToolButton *>();

    int nCount = btnList.count();
    for(int i=0; i<nCount; i++)
    {
        QToolButton *btn = btnList.at(i);
        QString strID = btn->property("ID").toString();
        if(strID.length() > 0){
            btn->setToolTip( QObject::tr( strID.toLatin1().data() ) );
            QFontMetrics elidfont(btn->font());
            btn->setText(elidfont.elidedText(QObject::tr(strID.toLatin1().data()), Qt::ElideRight, btn->width()-5*m_scale));
        }
    }
}

/*/TTQX-zhaozhengze-[B160725-038]【工具】三维工具，涂色问题
/*/
QToolButton* HHToolbarButtonPanel::getToolBarButtonById(const QString& strID)
{
    QList<QToolButton *> btnList = this->findChildren<QToolButton *>();
	int nCount = btnList.count();
	for (int i = 0; i<nCount; i++)
	{
        QToolButton *btn = btnList.at(i);
		QString strLocalID = btn->property("ID").toString();
		if (strLocalID == strID)
		{
			return btn;
		}
	}
	return NULL;
}
//*/

void HHToolbarButtonPanel::setPanelBackgroundColor(const QString &strColor){
    setStyleSheet(QString("HHToolbarButtonPanel{background-color: %1;}").arg(strColor));
}

void HHToolbarButtonPanel::setPanelFixedSize(){
    int nBtnCount=m_Ids.size();
    int nColCount=m_nCountPerLine;
    int nRowCount;
    if( nBtnCount % nColCount == 0 )
        nRowCount = nBtnCount/nColCount;
    else
        nRowCount = nBtnCount/nColCount+1;

    int nNewWidth = nColCount * (m_setButtonSize.width() + m_nSpacing) +m_nSpacing;
    int nNewHeight = nRowCount * (m_setButtonSize.height() + m_nSpacing);
    this->setFixedSize(nNewWidth, nNewHeight);
}

QSize HHToolbarButtonPanel::getPanelFixedSize(){
    return this->size();
}

QPixmap HHToolbarButtonPanel::setToolButtonIcons(const QString &str,const QSize &size){
    QPixmap image;
    image.load(str, 0, Qt::ThresholdDither | Qt::AvoidDither | Qt::ThresholdAlphaDither);
    if( !image.isNull() ) {
        QPixmap pixmap = image.scaled(size, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

        return pixmap;
    }
    return image;
}

QVariantMap HHToolbarButtonPanel::getParam(QToolButton *_button) {
    QPoint globalPoint( mapToGlobal( QPoint( _button->x(), _button->y() ) ) );
    int x = globalPoint.x();
    int y = globalPoint.y();
    QVariantMap obj;
    obj[ "x" ] = x;
    obj[ "y" ] = y;
    obj[ "width" ] = _button->width();
    obj[ "height" ] = _button->height();

    QPoint Point( mapToGlobal( QPoint(this->x(), this->y() ) ) );
    int  middleLine = Point.y()+this->height()/2;
    if( y < middleLine)
        obj[ "position" ] = "top";
    else
        obj[ "position" ] = "bottom";

    return obj;
}

void HHToolbarButtonPanel::btnPanelClicked(bool bChecked){
    QToolButton *btn = qobject_cast<QToolButton *>(sender());
    QString strID = btn->property("ID").toString();
    qDebug()<<"btnPanelClicked:"<<strID;

    if(strID.contains("ID_3D_MODE_", Qt::CaseInsensitive))
    {
        QString strNewID;
        QObject *obj_sender = QObject::sender();
        QToolButton *button = dynamic_cast<QToolButton*>(obj_sender);

        if(strID.contains("ID_3D_MODE_WIRE", Qt::CaseInsensitive)){
            strNewID = "ID_3D_MODE_SOLID";
            button->setText(QObject::tr("ID_3D_MODE_SOLID"));
        }else{
            strNewID = "ID_3D_MODE_WIRE";
            button->setText(QObject::tr("ID_3D_MODE_WIRE"));
        }

        QString strPixmapPath=QString("%1/%2.%3").arg(m_strPixmapPath).arg(strNewID).arg(m_strPixmapPostfix);
        qDebug()<<"strPixmapPath="<<strPixmapPath;

        button->setIcon(setToolButtonIcons(strPixmapPath,m_setIconSize));
        button->setIconSize(m_setIconSize);
        button->setProperty("ID", strNewID);
    }

    QVariantMap param = getParam(btn);
    emit signalClickButton(strID, param);
}

void HHToolbarButtonPanel::slotBtnChecked(QString strID){
    QList<QToolButton *> m_listBtn = this->findChildren<QToolButton *>();

    for(int i=0;i<m_listBtn.size();i++){
        QString ID = m_listBtn.at(i)->property("ID").toString();
        if(ID=="ID_ITEM_DELETE_PIXEL" || ID=="ID_ITEM_DELETE_ITEM"){
            m_listBtn.at(i)->setCheckable(true);
            if(strID==ID)
                 m_listBtn.at(i)->setChecked(true);
            else
                 m_listBtn.at(i)->setChecked(false);


        }
    }

}
