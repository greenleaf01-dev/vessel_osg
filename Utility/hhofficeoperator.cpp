#include "hhofficeoperator.h"
#include "hhofficedoc.h"
#include <QWidget>
#include <QDebug>

OfficeThread::OfficeThread( HHOfficeOperator *mainwindow ) :
    QThread( mainwindow ) {
    m_bStop = false;
    m_bPause = true;
    m_mainwindow = mainwindow;
}
void OfficeThread::run() {
    while( !m_bStop ) {
        msleep( 2000 );
        if( !m_bPause )
            m_mainwindow->sltDetectOffice();
    }
}

HHOfficeOperator::HHOfficeOperator(bool bExport)
{
    m_doc = new HHOfficeDoc;
    m_whiteboard = NULL;
    m_timer = NULL;
    m_bExport = bExport;
    connect(this,SIGNAL(sigRefreshPPTPlaying()),this,SLOT(sltRefreshPPTPlaying()));
}

HHOfficeOperator::HHOfficeOperator( QRect rect, QWidget *whiteboard ) {
    m_doc = new HHOfficeDoc;
    m_rect = rect;
    m_whiteboard = whiteboard;
    m_timer = new OfficeThread( this );
    m_timer->start();
    m_bExport = false;
    connect(this,SIGNAL(sigRefreshPPTPlaying()),this,SLOT(sltRefreshPPTPlaying()));
}

HHOfficeOperator::~HHOfficeOperator() {
    //m_timer->m_bStop = true;
    if(NULL != m_timer)
    {
        m_timer->m_bStop = true;
        delete m_timer;
        m_timer = NULL;
    }
    if( m_doc ) {
        delete m_doc;
        m_doc = NULL;
    }
}

void HHOfficeOperator::sltDetectOffice() {
    m_strDocumentType = m_doc->getDocumentTypeFromTopWindows( ( HWND )m_whiteboard->winId() );
    emit sigHaveOffice( m_strDocumentType );
    if( m_strDocumentType == "pptplaying" || m_strDocumentType == "wpspptplaying" ) {
        emit sigRefreshPPTPlaying();
    }
}

void HHOfficeOperator::startDetect() {
    m_timer->m_bPause = false;
    sltDetectOffice();
}

void HHOfficeOperator::stopDetect() {
   m_timer->m_bPause = true;
}

void HHOfficeOperator::embedImage( QString strFile, QRect rectEmbeded, QString strDoc ) {
    if( strDoc.isEmpty() )
        strDoc = m_strDocumentType;

    if( strDoc == "ppt" ) {
		m_whiteboard->hide();
		m_doc->embedPPT(strFile, rectEmbeded);
		m_whiteboard->show();
    } else if( strDoc == "word" ) {
        m_whiteboard->hide();
		m_doc->embedWord(strFile, rectEmbeded);
        m_whiteboard->show();
    } else if( strDoc == "excel" ) {
		m_whiteboard->hide();
        m_doc->embedExcel( strFile, rectEmbeded );
		m_whiteboard->show();
    } else if( strDoc == "pptplaying" ) {
        m_whiteboard->hide();
        m_doc->embedPPTPlaying( strFile, rectEmbeded );
        m_whiteboard->show();
    }
}

void HHOfficeOperator::setPPTPlayingNext() {
    bool bIsEnd = false;
    if( m_strDocumentType == "wpspptplaying" )
        m_doc->setWPSPPTNext();
    else
        m_doc->setPPTNext( bIsEnd );
}

void HHOfficeOperator::setPPTPlayingPrevious() {
    if( m_strDocumentType == "wpspptplaying" )
        m_doc->setWPSPPTPrevious();
    else
        m_doc->setPPTPrevious();
}

void HHOfficeOperator::setPPTPlayingEnd() {
    if( m_strDocumentType == "wpspptplaying" )
        m_doc->setWPSPPtEnd();
    else
        m_doc->setPPTEnd();
}

bool HHOfficeOperator::exportPPT(QString fileName, QStringList picList)
{
    return m_doc->exportPPT(fileName, picList);
}

bool HHOfficeOperator::exportPDF(QString fileName, QStringList picList)
{
    return m_doc->exportPDF(fileName, picList);
}

bool HHOfficeOperator::exportWORD(QString fileName, QStringList picList)
{
    return m_doc->exportWORD(fileName, picList);
}

bool HHOfficeOperator::exportHTML(QString fileName, QStringList picList)
{
    return m_doc->exportHTML(fileName, picList);
}

bool HHOfficeOperator::exportImage(QString fileName, QStringList picList)
{
    return m_doc->exportImage(fileName, picList);
}

bool HHOfficeOperator::exportEXCEL(QString fileName, QStringList picList)
{
    return m_doc->exportEXCEL(fileName, picList);
}

bool HHOfficeOperator::exportWPSWord( QString fileName, QStringList picList )
{
    return m_doc->exportWPSWord( fileName, picList );
}

bool HHOfficeOperator::exportWPSExcel( QString fileName, QStringList picList )
{
    return m_doc->exportWPSExcel( fileName, picList );
}

bool HHOfficeOperator::exportWPSPpt( QString fileName, QStringList picList )
{
    return m_doc->exportWPSPpt( fileName, picList );
}

bool HHOfficeOperator::connectWPS()
{
    QAxObject* wps = new QAxObject( "kwpp.Application" );
    QString uuid = wps->control();
    delete wps;
    if( !uuid.isEmpty() )
        return true;
    else
    {
        return false;
    }
}

bool HHOfficeOperator::connectOffice()
{
    QAxObject* office = new QAxObject( "Powerpoint.Application" );
    QString uuid = office->control();
	delete office;
    if( !uuid.isEmpty() )
        return true;
    else
    {
        return false;
    }
}

QStringList HHOfficeOperator::importPPT(QString fileName, QString saveDir)
{
    return m_doc->importPPT(fileName, saveDir);
}

QVariantMap HHOfficeOperator::importPPT2(QString fileName )
{
    return m_doc->importPPT2( fileName );
}

QVariantMap HHOfficeOperator::getJSONFromPPTSlide( void* pSlide, QString strDir )
{
    return m_doc->getJSONFromPPTSlide(pSlide,strDir);
}

QJsonObject HHOfficeOperator::getItemJson(void *pItem,QString strDirList)
{   
	/*/TTQX-zhaozhengze-ppt导入视频和音频
	/*/
	QStringList  strList = strDirList.split("|*&&&&&*|");
	QString strDir;
	QString strUncompressPath;
	QString strSlideIndex;
	if (strList.size() > 0)
	{
		strDir = strList[0];
	}
	
	if (strList.size() > 1)
	{
		strUncompressPath = strList[1];
	}

	if (strList.size() > 2)
	{
		strSlideIndex = strList[2];
	}
	//*/

    int type =  m_doc->getTypeFromPPTItem(pItem);
	/*/TTQX-zhaozhengze-ppt将所有的东西除了视频音频都导出为图片。
	if (type == msoTextBox || type == msoAutoShape ||type== msoPlaceholder) //msoPlaceholder 中有文本 Wangxb.
	{
		return m_doc->getTextEditJSON(pItem, strDir);
	}
	/*/
	//*/
  
	/*/TTQX-zhaozhengze-ppt导入视频和音频
	/*/
	if (type == msoMedia)
	{
		return m_doc->getMediaJSON(pItem, strDir, strUncompressPath, strSlideIndex);
	}
	//*/
	else
	{
		return m_doc->getPictureJSON(pItem, strDir);
	}
}

void HHOfficeOperator::closePPTPresentation(void *presentation)
{
    m_doc->closePPTPresentation( presentation );
}
//Add by wangxianbing,2018/1/10 尝试关闭ppt进程。
void HHOfficeOperator::closePPTApp()
{
    m_doc->closePPTApp();//需要关闭进程 
}
void HHOfficeOperator::getPPTPageInfo(QString &sPageInfo)
{
    bool bIsEnd = false;
    if( m_strDocumentType == "wpspptplaying" )
        m_doc->getWPSPPTPageInfo(sPageInfo);
    else
        m_doc->getPPTPageInfo( sPageInfo );
}

void HHOfficeOperator::setPPTPenInfo(const QString &sPenType, const QVariantMap &args)
{
    if( m_strDocumentType == "wpspptplaying" )
        m_doc->setWPSPPTPenInfo(sPenType, args);
    else
        m_doc->setPPTPenInfo(sPenType, args);
}

bool HHOfficeOperator::getPPTThumbnail(QStringList &lResultFile, const QString &sPath,
                                       const QString sImgType, const QSize imgSize)
{
    bool bRet = false;
    if( m_strDocumentType == "wpspptplaying" )
        bRet = m_doc->getWPSPPTThumbnail(lResultFile, sPath,
                                  sImgType, imgSize);
    else
        bRet = m_doc->getPPTThumbnail(lResultFile, sPath,
                               imgSize, sImgType);

    return bRet;
}

void HHOfficeOperator::sltRefreshPPTPlaying()
{
    int index = -1;
    if( m_strDocumentType == "pptplaying" )
        index = m_doc->getPPTPlayingIndex();
    else if( m_strDocumentType == "wpspptplaying" )
        index = m_doc->getWPSPPTPlagingIndex();
    emit sigPPTPlayingSlideIndex( index );
}

void HHOfficeOperator::setWPSPPTPlayingPenType( QString strType )
{
    m_doc->setWPSPenType( strType );
}
