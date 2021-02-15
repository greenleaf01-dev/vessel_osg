#include "hhofficedoc.h"
#include "ImportFile/pdflib.hpp"
#include <qdebug.h>
#include <QVector>
#include <QFile>
#include <QDir>
#include <TlHelp32.h>
#include "hhtoolhelper.h"
#include <QTextEdit>
#include <atlbase.h>
#include <atlapp.h>
#define _ATL_NO_HOSTING  1
#include <atlwin.h>
#undef _ATL_NO_HOSTING
#include <atlgdi.h>
#include <atlctrls.h>
#include <qwinfunctions.h>
#define _WTL_NO_CSTRING
#define _WTL_NO_WTYPES
#include <atlstr.h>
#include <sstream>
#include <string>
#include <streambuf>
#include <QDomNode>
#include "JlCompress.h"
#include <QMutex>
#include <QApplication>
using namespace std;

#define AFXAPI __stdcall

#if _MSC_VER == 1900
#define _MFC_FILENAME_VER "140"
#elif  _MSC_VER == 1800
#define _MFC_FILENAME_VER "120"
#else
#define _MFC_FILENAME_VER "120"
#endif
#pragma comment(lib, "mfc" _MFC_FILENAME_VER "u.lib")
#pragma comment(lib, "mfcs" _MFC_FILENAME_VER "u.lib")

typedef int     BOOL;
BOOL AFXAPI AfxInitRichEdit();

static QString  CS2QS(CString cs) { return  QString::fromWCharArray((LPCTSTR)cs, cs.GetLength()); }
static CString  QS2CS(QString qs) { return  qs.toStdString().c_str(); }


/*/TTQX-zhaozhengze-ppt导入视频和音频
/*/
typedef std::map<QString, QString> TMap;
typedef std::vector<TMap> TMapVec;
typedef std::map<QString, TMapVec> TMapStringToMV; 
typedef std::map<QString, TMap> TMapStringToMap;

//解析视频路径的方法是： 存储映射，存储当前的name 和 link 所对应的内容。每个name和link是一对。name为视频的名字
//link为链接的映射值。通过vba得到当前的视频的名字，通过这个名字和s_VecMap找到对应的链接。
//s_VecMap存储了当前页面所有视频和name和link的映射组合。
//s_refmap存储了当前的link和真正媒体对应的路径名的对应。
//s_map为中间变量，负责解析。解析完毕 clear。
//s_StringMapToVec 存储了映射。页面和s_VecMap的映射。

static TMapVec s_VecMap;  
static TMap s_map;
static TMap  s_refmap;
static TMapStringToMV  s_StringMapToVec;
static TMapStringToMap s_StringToMap;

static QString s_strAttName = "name";
static QString s_strAttLink = "r:link";
static QString s_strId = "Id";
static QString s_strTarget = "Target";

static void reVisitDocument(QDomNode&  node)
{
	TMap strNameMap;
	for (QDomNode n = node.firstChild(); !n.isNull(); n = n.nextSibling())
	{
		QString name = n.nodeName();
		if (n.hasAttributes())
		{
			QDomNamedNodeMap qm = n.attributes();
			if (qm.contains(s_strAttLink))
			{
				if (s_map.count(s_strAttName) > 0)
				{
					QDomElement e = n.toElement();
					if (!e.isNull())
					{
						QString strName = e.attribute(s_strAttLink);
						s_map[s_strAttLink] = strName;
						s_VecMap.push_back(s_map);
						s_map.clear();
					}
				}

			}

			if (qm.contains(s_strAttName))
			{
				QDomElement e = n.toElement();
				if (!e.isNull())
				{
					QString strName = e.attribute(s_strAttName);
					s_map[s_strAttName] = strName;
				}
			}
		}

		if (n.hasChildNodes())
		{
			reVisitDocument(n);
		}
	}
}

static void extractNameAndLinkInfo(QDomElement& element) //提取名字和链接的信息。
{
	for (QDomNode n = element.firstChild(); !n.isNull(); n = n.nextSibling())
	{
		QString name = n.nodeName();
		reVisitDocument(n);
	}
}

static void extractIdAndTarget(QDomElement& element)  //提取id和目标的信息
{
	for (QDomNode n = element.firstChild(); !n.isNull(); n = n.nextSibling())
	{
		QDomNamedNodeMap qm = n.attributes();
		QString strAttName;
		if (qm.contains(s_strId))
		{
			QDomElement e = n.toElement();
			if (!e.isNull())
			{
				strAttName = e.attribute(s_strId);
			}
		}
		else
		{
			continue;
		}

		if (qm.contains(s_strTarget))
		{
			QDomElement e = n.toElement();
			if (!e.isNull())
			{
				QString strTanget = e.attribute(s_strTarget);
				s_refmap.insert(std::make_pair(strAttName, strTanget));
			}
		}
		else
		{
			continue;
		}
	}
}
//*/


static DWORD CALLBACK StdStreamOutCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{

	ostringstream* oss = (ostringstream*)dwCookie;
	if (NULL != oss)
	{
		string strPrint = (char*)pbBuff;
		*oss << strPrint;
	}
	*pcb = cb;
	return 0;
}

class CTextCtrl : public WTL::CRichEditCtrlT < WTL::CEditT<ATL::CWindow> >//WTL::CRichEditCtrl
{
public:
    CTextCtrl();
    ~CTextCtrl(){};

	QString GetTextContent();
    void CreateTextBox(HWND hParent);
};
CTextCtrl::CTextCtrl()
{
    AfxInitRichEdit();
};
void CTextCtrl::CreateTextBox(HWND hParent)
{
#define ID_RICH_EDIT_CTRL     4569

    AfxInitRichEdit();
    DWORD dwStyle = WS_CLIPSIBLINGS | WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN;//|ES_AUTOHSCROLL
	RECT rect; 
	rect.bottom = 0; 
	rect.top = 0; 
	rect.right = 100;
	rect.bottom = 100;
	//CRect rect(0, 0, 100, 100);
    if (!ATL::CWindow::Create(_T("RICHEDIT20W"), (HWND)hParent, rect, NULL, dwStyle, NULL, ID_RICH_EDIT_CTRL))
    {
        return ;
    }
}

QString CTextCtrl::GetTextContent()
{
	QString strContent;

    if (IsWindow())
    {
        // 1. 首先保存为一个.rtf文件
        // 2. 从rtf文件中读入一个字符串
        // 3. 将rtf文件删除
		ostringstream oss;
		EDITSTREAM es;
		es.dwCookie = (DWORD)&oss;
		es.pfnCallback = StdStreamOutCallback;
		::SendMessage(m_hWnd, EM_STREAMOUT, SF_RTF, (LPARAM)&es);//写入文件
		string strContent = oss.str();
		return QString(strContent.c_str());
    }

	return QString("");
}

#ifdef UNICODE

#define QStringToTCHAR(x)     (wchar_t*) x.utf16()

#define PQStringToTCHAR(x)    (wchar_t*) x->utf16()

#define TCHARToQString(x)     QString::fromUtf16((x))

#define TCHARToQStringN(x,y)  QString::fromUtf16((x),(y))

#else

#define QStringToTCHAR(x)     x.local8Bit().constData()

#define PQStringToTCHAR(x)    x->local8Bit().constData()

#define TCHARToQString(x)     QString::fromLocal8Bit((x))

#define TCHARToQStringN(x,y)  QString::fromLocal8Bit((x),(y))

#endif

//word
CComPtr<MSWord::_Application> m_WordApp=NULL;



CComPtr<XPDF::CAcroApp>			m_pdfAcroApp=NULL;

CComPtr<MSVISIO::IVApplication>  m_VisioApp=NULL;
/*/TTQX-zhaozhengze-[B170707-004]-ppt新建页面嵌入失败
这个函数主要是完成这个工作：
先往ppt里添加图片，然后得到这个图片的左上角角的位置，然后再往里面插入一个图片，得到左上角的位置。
判断这两个位置是不是重合，如果不重合，继续往下循环插入并比较。如果重合，则将之前的所有插入的图片
统统删除，只保留最后一个。
为什么这么处理？
因为现在ppt插入出现一个问题，就是新建一个ppt页面，由于有默认的文本框，所以插入的图片就会位置错误，似乎是以默认的文本框的
窗口为插入窗口了。但是，当把默认的文本框都插入一个图片，那么再插入就正确了。
所以解决方法是，不停地插入，直到位置不再改变为止。但是为了避免无限循环，规定了最多循环四次，超过四次，错了也不处理了。
/*/
static void addShapePictureWithSpecialProcess(QAxObject *shapes, QVariantList params)
{
	if (NULL == shapes || 0 == params.size())
	{
		return;
	}

	QAxObject * result = shapes->querySubObject("AddPicture(QString, Office::MsoTriState, Office::MsoTriState, double, double, double, double)", params);
	double vLeft = result->property("Left").toDouble();
	double vTop = result->property("Top").toDouble();

	std::vector<QAxObject*> vecAxObj;
	vecAxObj.push_back(result);

	int nCount = 0;
	while (true)
	{
		if (nCount > 4)
		{
			break;
		}

		QAxObject * result1 = shapes->querySubObject("AddPicture(QString, Office::MsoTriState, Office::MsoTriState, double, double, double, double)", params);
		vecAxObj.push_back(result1);

		double vLeft1 = result1->property("Left").toDouble();
		double vTop1 = result1->property("Top").toDouble();

		result = result1;

		if (fabs(vLeft1 - vLeft) < 1e-5  && fabs(vTop1 - vTop) < 1e-5)
		{
			break;
		}
		vLeft = vLeft1;
		vTop = vTop1;

		++nCount;
	}

	for (int i = 0; i < vecAxObj.size() - 1; ++i)
	{
		if (NULL != vecAxObj.at(i))
		{
			vecAxObj.at(i)->dynamicCall("Delete()");
		}
	}
}
//*/


// don't connect office in the constructor, because of needing lots of time
HHOfficeDoc::HHOfficeDoc() {
	CoInitialize(NULL);
    m_hPPTShowWndHWnd = NULL;
    axWPSPpt = NULL;
    axPptApp = NULL;
}

HHOfficeDoc::~HHOfficeDoc() {
	::CoUninitialize();
    m_hPPTShowWndHWnd = NULL;
    if( axWPSPpt )
        disConnectWPSPpt();
}

QVector< HWND > m_topHWNDs;
BOOL CALLBACK HHOfficeDoc::GetDesktopWindow( HWND hwnd, LPARAM lParam ) {
    m_topHWNDs.push_back( hwnd );
    return TRUE;
}

QString HHOfficeDoc::getDocumentTypeFromHWND( HWND hwnd ) {
    QString str;
    str = isPPTPlaying( hwnd );
    if( !str.isEmpty() )
        return str;
    str = isWord( hwnd );
    if( !str.isEmpty() )
        return str;
    str = isPPT( hwnd );
    if( !str.isEmpty() )
        return str;
    str = isExcel( hwnd );
    if( !str.isEmpty() )
        return str;
    str = isVisio( hwnd );
    if( !str.isEmpty() )
        return str;
    return "";
}

QString HHOfficeDoc::isVisio( HWND hwnd ) {
    TCHAR szClassName[255] = { 0 };
    ::GetClassName( hwnd, szClassName, 254 );
    if( _tcscmp( szClassName, _T( "VISIOG" ) ) == 0 ) {
        RECT rect;
        ::GetWindowRect( hwnd, ( LPRECT )( &rect ) );
        if( - GetSystemMetrics( SM_CXSCREEN ) < rect.left )
            return "visio";
    }
    return "";
}

QString HHOfficeDoc::isExcel( HWND hwnd ) {
    TCHAR szClassName[255] = { 0 };
    ::GetClassName( hwnd, szClassName, 254 );
    if( _tcscmp( szClassName, _T( "XLMAIN" ) ) == 0 ||
        _tcscmp( szClassName, _T( "EXCEL7" ) ) == 0 ||
        _tcscmp( szClassName, _T( "EXCEL6" ) ) == 0 ) {
        TCHAR szCaptionName[ 255 ] = { 0 };
        ::GetWindowText( hwnd, szCaptionName, 254 );
        if( _tcsstr( szCaptionName, _T("WPS 表格") ))
            return "";
        RECT rect;
        ::GetWindowRect( hwnd, ( LPRECT )( &rect ) );
        if( - GetSystemMetrics( SM_CXSCREEN ) < rect.left ) {
            m_hExcelShowWndHWnd = hwnd;
            return "excel";
        }
    }
    return "";
}

QString HHOfficeDoc::isWord( HWND hwnd ) {
    TCHAR szClassName[255] = { 0 };
    ::GetClassName( hwnd, szClassName, 254 );
    if( _tcscmp( szClassName, _T( "_WwG" ) ) == 0 ||
        _tcscmp( szClassName, _T( "OpusApp" ) ) == 0 ) {
        TCHAR szCaptionName[ 255 ] = { 0 };
        ::GetWindowText( hwnd, szCaptionName, 254 );
        if( _tcsstr( szCaptionName, _T("WPS 文字") ))
            return "";
        RECT rect;
        ::GetWindowRect( hwnd, ( LPRECT )( &rect ) );
		if (-GetSystemMetrics(SM_CXSCREEN) < rect.left){
			m_hWordShowWndHWnd = hwnd;
			return "word";
		}
    }
    return "";
}

QString HHOfficeDoc::isPPTPlaying( HWND hwnd ) {
    TCHAR szClassName[255] = { 0 };
    ::GetClassName( hwnd, szClassName, 254 );
    if( _tcscmp( szClassName, _T( "screenClass" ) ) == 0 ) {
        m_hPPTShowWndHWnd = hwnd;
        return "pptplaying";
    }
    return "";
}

void HHOfficeDoc::deleteTempPicture(QStringList picList)
{
    if(picList.isEmpty())
        return;

    int picNum = picList.size();
    for(int i=0; i<picNum; i++)
    {
		QFile::remove(picList[i]);
    }
}

bool HHOfficeDoc::createHtmlFile(QString fileName, QStringList relativePicList)
{
    QFile htmlFile(fileName);
    if(htmlFile.exists())
        htmlFile.remove();

    int picNum = relativePicList.size();
    QString htmlSrc("<html>\n<head><title>MyHtml</title></head>\n");
    htmlSrc.append("<body><font size = 5 align = center color = red></font><p><hr></p>");
    htmlSrc.append("<table border = 0 width = 100%>\n");

    QString imgSrc("<td> <a href = \" %1 \" ><img src=\" %2 \" width = 200 height =120 </img></a>  </td> \n");
    for(int i=0; i<picNum; i++)
    {
        if(i != 0 && i%4 == 0)
        {
            htmlSrc.append("<tr>\n");
            htmlSrc.append("</tr>\n");
        }

        QString relPicPath = relativePicList[i];
        QString imgObj = imgSrc.arg(relPicPath, relPicPath);
        htmlSrc.append(imgObj);
    }
    htmlSrc.append("</table> \n</body> \n</html> \n");

    if(!htmlFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&htmlFile);
    out<<htmlSrc<<endl;
    out.flush();
    htmlFile.close();

    return true;
}

QString HHOfficeDoc::isPPT( HWND hwnd ) {
    TCHAR szClassName[255] = { 0 };
    ::GetClassName( hwnd, szClassName, 254 );
    if( _tcscmp( szClassName, _T( "paneClassDC" ) ) == 0 ||
        _tcscmp( szClassName, _T( "mdiClass" ) ) == 0  ||
        _tcscmp( szClassName, _T( "PPTFrameClass" ) ) == 0 ||
        _tcscmp( szClassName, _T( "PP11FrameClass" ) ) == 0 ||
        _tcscmp( szClassName, _T( "PP10FrameClass" ) ) == 0 ||
        _tcscmp( szClassName, _T( "PP9FrameClass" ) ) == 0 ||
        _tcscmp( szClassName, _T( "PP12FrameClass" ) ) == 0 ) {
        TCHAR szCaptionName[ 255 ] = { 0 };
        ::GetWindowText( hwnd, szCaptionName, 254 );
        if( _tcsstr( szCaptionName, _T("WPS 演示") ))
            return "";
        RECT rect;
        ::GetWindowRect( hwnd, ( LPRECT )( &rect ) );
		if (-GetSystemMetrics(SM_CXSCREEN) < rect.left){
			m_hPPTNormalWndHWnd = hwnd;
			return "ppt";
		}
    }
    return "";
}

QString HHOfficeDoc::filterDocumentType( HWND hwndWhiteBoard, HWND hwnd, QString strFilter ) {
    QString str = "";
    if( strFilter == "word" )
        str = isWord( hwnd );
    else if( strFilter == "excel" )
        str = isExcel( hwnd );
    else if( strFilter == "visio" )
        str = isVisio( hwnd );
    else if( strFilter == "pptplaying" )
        str = isPPTPlaying( hwnd );
    else if( strFilter == "ppt" )
        str = isPPT( hwnd );
    if( !str.isEmpty() )
        return str;

    HWND next = ::GetNextWindow( hwndWhiteBoard, GW_HWNDNEXT );
    do {
        QString strNext;
        if( strFilter == "word" )
            strNext = isWord( next );
        else if( strFilter == "excel" )
            strNext = isExcel( next );
        else if( strFilter == "visio" )
            strNext = isVisio( next );
        else if( strFilter == "pptplaying" )
            strNext = isPPTPlaying( next );
        else if( strFilter == "ppt" )
            strNext = isPPT( next );

        if( !strNext.isEmpty() && strNext == strFilter )
            return strFilter;
        TCHAR szClassName[255] = { 0 };
        ::GetClassName( next, szClassName, 254 );
        if( _tcscmp( szClassName, _T( "tooltips_class32" ) ) == 0 ) {
            next = ::GetNextWindow( next, GW_HWNDNEXT );
            continue;
        }
        RECT rect;
        ::GetWindowRect( next, ( LPRECT )( &rect ) );
        if( GetSystemMetrics( SM_CXSCREEN ) / 2 <= rect.right - rect.left &&
            GetSystemMetrics( SM_CYSCREEN ) / 2 <= rect.bottom - rect.top ) {
            break;
        }
        next = ::GetNextWindow( next, GW_HWNDNEXT );
    } while( next );
    return "";
}

QString HHOfficeDoc::getDocumentTypeFromTopWindows( HWND hwndWhiteBoard ) {
    QString strRtn = "";
    HWND next = ::GetForegroundWindow();
    while( next )
    {
        if( ::IsIconic( next ) || !::IsWindowVisible( next ))
        {
            next = ::GetNextWindow( next, GW_HWNDNEXT );
            continue;
        }
        strRtn = isWord( next );
        if( !strRtn.isEmpty() )
            break;
        strRtn = isExcel( next );
        if( !strRtn.isEmpty() )
            break;
        strRtn = isPPT( next );
        if( !strRtn.isEmpty() )
            break;
        strRtn = isPPTPlaying( next );
        if( !strRtn.isEmpty() )
            break;
        strRtn = isWPSPPTPlaying( next );
        if( !strRtn.isEmpty() )
            break;

        if( next == hwndWhiteBoard )
        {
            next = ::GetNextWindow( next, GW_HWNDNEXT );
            continue;
        }

        TCHAR szClassName[255] = { 0 };
        ::GetClassName( next, szClassName, 254 );
        if( _tcscmp( szClassName, _T( "tooltips_class32" ) ) == 0 ) {
            next = ::GetNextWindow( next, GW_HWNDNEXT );
            continue;
        }
        RECT rect;
        ::GetWindowRect( next, ( LPRECT )( &rect ) );
        if( GetSystemMetrics( SM_CXSCREEN ) / 2 <= rect.right - rect.left &&
                GetSystemMetrics( SM_CYSCREEN ) / 2 <= rect.bottom - rect.top ) {
            break;
        }
        next = ::GetNextWindow( next, GW_HWNDNEXT );
    }
    return strRtn;
}

QString HHOfficeDoc::getDocumentTypeFromPoint( int x, int y ) {
    POINT pt;
    pt.x = x;
    pt.y = y;
    HWND pHndOffice = ::WindowFromPoint( pt );
    if( pHndOffice == NULL )
        return "";
    return getDocumentTypeFromHWND( pHndOffice );
}

bool HHOfficeDoc::embedWord(QString strFilename, QRect InputRect) {

	HWND pHwndWord = NULL;// m_hWordShowWndHWnd;
//    if( m_bIsWPS )
//        return InsertWPSWord(strFilename, InputRect, pHwndWord );
    return InsertWord(strFilename, InputRect, pHwndWord);    
}

bool HHOfficeDoc::connectPPT() {
    if( m_PptApplication )
        return true;
    HRESULT hRet = m_PptApplication.CoCreateInstance( __uuidof(MSPPT::Application), NULL, CLSCTX_SERVER );
    if( FAILED( hRet ) || NULL == m_PptApplication ) {
        if( m_PptApplication ) {
            m_PptApplication.Release();
            m_PptApplication = NULL;
        }
        return false;
    } else {
        _bstr_t version = m_PptApplication->GetVersion();
        m_PptVersion = atof((const char*)version);
        return true;
    }
}

bool HHOfficeDoc::disConnectPPT() {
    try {
        if( NULL != m_PptApplication ) {
            m_PptApplication.Release();
            m_PptApplication = NULL;
        }
    } catch(...) {
        return false;
    }
    return true;
}

bool HHOfficeDoc::connectPPTApp() {

    axPptApp = new QAxObject("Powerpoint.Application");
    QString uuid = axPptApp->control()+"&";
    axPptApp->setControl(uuid);
    m_bPPTFocusState = false;
    return true;

}

bool HHOfficeDoc::disConnectPPTApp() {
	if (!axPptApp)		return false;
    axPptApp->disableMetaObject();
    axPptApp->deleteLater();
    axPptApp->clear();
    delete axPptApp;
    axPptApp = NULL;
    return true;

}

//BOOL HHOfficeDoc::ConnectPPT() {

//    qDebug()<<"HHOfficeDoc::ConnectPPT-------Begin";
//    if ( NULL != m_PptApplication )
//        return TRUE;

//    CLSID clsid;
////    CLSIDFromProgID(L"Powerpoint.Application", &clsid);
//    CLSIDFromProgID(L"Powerpnt.Application", &clsid);
//    try
//    {
//        IUnknown *pUnk;
//        HRESULT hr = GetActiveObject(clsid, NULL, (IUnknown**)&pUnk);

//        qDebug()<<"HHOfficeDoc::ConnectPPT-------------11111111111111111";
//        if (hr == S_OK)
//        {
//            qDebug()<<"HHOfficeDoc::ConnectPPT--------------222222222222";
//            IDispatch *pDisp;
//            hr = pUnk->QueryInterface(IID_IDispatch, (void **)&pDisp);
//            pUnk->Release();
//            qDebug()<<"HHOfficeDoc::ConnectPPT---------------333333333333";
//            CComQIPtr<MSPPT::_Application> Application(pDisp);
//            ATLASSERT(Application);
//            m_PptApplication = NULL;
//            qDebug()<<"HHOfficeDoc::ConnectPPT---------------4444444444444";
//            Application->QueryInterface( __uuidof(MSPPT::_Application), (void**)&m_PptApplication );
//            qDebug()<<"HHOfficeDoc::ConnectPPT---------------5555555555555";
//            ATLASSERT(m_PptApplication);
//            if ( NULL == m_PptApplication )
//                return FALSE;

//            pDisp->Release();
//            TCHAR * stopstring;
//            m_PptVersion = _tcstod( m_PptApplication->GetVersion(), &stopstring );

//            return TRUE;
//        }
//        qDebug()<<"HHOfficeDoc::ConnectPPT------------Failed!!!";
//    }
//    catch(...)
//    {
//        qDebug()<<::GetLastError();
//        return FALSE;
//    }

//    if( !m_PptApplication )
//        return FALSE;
//    else
//        return TRUE;
//}

//BOOL HHOfficeDoc::DisConnectPPT() {

//    try
//    {
//        if ( NULL != m_PptApplication )
//        {
//            m_PptApplication.Release();
//            m_PptApplication = NULL;
//        }
//    }
//    catch(...)
//    {
//        return FALSE;
//    }
//    return TRUE;
//}

bool HHOfficeDoc::embedPPT(QString strFilename, QRect InputRect) {

//    if( m_bIsWPS )
//        return InsertWPSPpt(strFilename,InputRect);
    return Insertnormalppt(strFilename, InputRect); 
}

bool HHOfficeDoc::embedPPTPlaying( QString strFilename, QRect InputRect ) {

//    if( m_bIsWPS )
//        return InsertWPSPpt(strFilename,InputRect);
    return Insertnormalppt( strFilename, InputRect );
}

bool HHOfficeDoc::setPPTPrevious() {

//    if( m_bIsWPS )
//        return setWPSPPTPrevious();

    if( !connectPPT() )
        return false;
    try {
        m_PptPresentation = m_PptApplication->GetActivePresentation();
        m_PptSlideShowWindow = m_PptPresentation->GetSlideShowWindow();
        if( !m_PptSlideShowWindow )
        {
            disConnectPPT();
            return false;
        }
        m_PptSlideshowView = m_PptSlideShowWindow->GetView();
        m_PptSlideshowView->Previous();
    } catch( ... ) {
        disConnectPPT();
        return false;
    }
    HWND hWnd = ::FindWindow( L"screenClass", NULL );
    if( hWnd )
    {
        SetForegroundWindow(hWnd );
        SetFocus(hWnd);
    }
    disConnectPPT();
    return true;
//    if( !connectPPTApp() )
//        return false;
//    QAxObject *presentation = axPptApp->querySubObject("ActivePresentation");
//    QAxObject *slideShowWindow = presentation->querySubObject("SlideShowWindow");
//    if( !slideShowWindow )
//        return false;
//    QAxObject *view = slideShowWindow->querySubObject("View");
//    view->dynamicCall("Previous(void)");
//    disConnectPPTApp();
//    return true;
}

bool HHOfficeDoc::setPPTNext( bool &bIsEnd  ) {

//    if( m_bIsWPS )
//        return setWPSPPTNext();

    if( !connectPPT() )
    {
        qDebug()<<"HHOfficeDoc::setPPTNext  connectPPT Failed!";
        return false;
    }
    try {
        m_PptPresentation = m_PptApplication->GetActivePresentation();
        m_PptSlideShowWindow = m_PptPresentation->GetSlideShowWindow();
        if( !m_PptSlideShowWindow )
        {
            disConnectPPT();
            return false;
        }
        m_PptSlideshowView = m_PptSlideShowWindow->GetView();
        m_PptSlideshowView->Next();
    } catch( ... ) {
        disConnectPPT();
        return false;
    }
    //保证PPT下次动作有效，否则，在PPT2010版本，有些页面动作会无效。
    HWND hWnd = ::FindWindow( L"screenClass", NULL );
    if( hWnd )
    {
        SetForegroundWindow(hWnd );
        SetFocus(hWnd);
    }
    disConnectPPT();
    return true;
//    if( !connectPPTApp() )
//        return false;
//    QAxObject *presentation = axPptApp->querySubObject("ActivePresentation");
//    QAxObject *slideShowWindow = presentation->querySubObject("SlideShowWindow");
//    if( !slideShowWindow )
//        return false;
//    QAxObject *view = slideShowWindow->querySubObject("View");
//    view->dynamicCall("Next(void)");
//    disConnectPPTApp();
//    return true;
}

bool HHOfficeDoc::setPPTEnd() {

//    if( m_bIsWPS )
//        return setWPSPPtEnd();

    if( !connectPPT() )
        return false;
    try {
        m_PptPresentation = m_PptApplication->GetActivePresentation();
        m_PptSlideShowWindow = m_PptPresentation->GetSlideShowWindow();
        if( !m_PptSlideShowWindow )
        {
            disConnectPPT();
            return false;
        }
        m_PptSlideshowView = m_PptSlideShowWindow->GetView();
        m_PptSlideshowView->Exit();
    } catch( ... ) {
        disConnectPPT();
        return false;
    }
    disConnectPPT();
    return true;
//    if( !connectPPTApp() )
//        return false;
//    QAxObject *presentation = axPptApp->querySubObject("ActivePresentation");
//    QAxObject *slideShowWindow = presentation->querySubObject("SlideShowWindow");
//    if( !slideShowWindow )
//        return false;
//    QAxObject *view = slideShowWindow->querySubObject("View");
//    view->dynamicCall("Exit(void)");
//    disConnectPPTApp();
//    return true;
}

int HHOfficeDoc::getPPTPlayingIndex() {
//    if( m_bIsWPS )
//        return getWPSPPTPlagingIndex();
    if( !connectPPT() )
        return - 1;
    try {
        m_PptPresentation = m_PptApplication->GetActivePresentation();
        m_PptSlideShowWindow = m_PptPresentation->GetSlideShowWindow();
        m_PptSlideshowView = m_PptSlideShowWindow->GetView();
        return m_PptSlideshowView->GetCurrentShowPosition();
    } catch( ... ) {
        return - 1;
    }
    return - 1;
}

bool HHOfficeDoc::exportWPSPpt( QString fileName, QStringList picList )
{
    connectWPSPpt();
    if( !axWPSPpt )
        return false;
    axWPSPpt->setProperty( "Visible", false );
    axWPSPpt->setProperty( "ShowWindowsInTaskbar", false );

    QAxObject* presentations = axWPSPpt->querySubObject( "Presentations" );
    if( !presentations )
    {
        disConnectWPSPpt();
        return false;
    }
    QAxObject* presentation = presentations->querySubObject( "Add( bool )", true );
    if( !presentation )
    {
        disConnectWPSPpt();
        return false;
    }
    QAxObject* slides = presentation->querySubObject("Slides");
    if( !slides )
    {
        disConnectWPSPpt();
        return false;
    }

    int picNum = picList.size();
    for(int i = picNum - 1; i >= 0; i--)
    {
        QString picPath = picList[i];
        picPath.replace( "/", "//" );
        slides->dynamicCall( "Add( int, int )", 1, 12 );  /*MSPPT::PpSlideLayout::ppLayoutBlank12 );*/
        QAxObject* slide = slides->querySubObject( "Item( int )", 1 );
        if( !slide )
        {
            disConnectWPSPpt();
            return false;
        }
        slide->setProperty( "DisplayMasterShapes", true );
        slide->setProperty( "FollowMasterBackground", false );

        QAxObject* pageSetup = presentation->querySubObject( "PageSetup" );
        int fWidth = pageSetup->property( "SlideWidth" ).toInt();
        int fHeight = pageSetup->property( "SlideHeight" ).toInt();
        QAxObject* shapes = slide->querySubObject( "Shapes" );
        if( !shapes )
        {
            disConnectWPSPpt();
            return false;
        }
        qDebug()<<"picPath = "<<picPath;
        QAxObject* shape = shapes->querySubObject("AddPicture (const QString&, bool, bool, float, float, float, float).Select",
                             picPath, false, true, 0, 0, fWidth, fHeight );

        if( !shape )
        {
            disConnectWPSPpt();
            return false;
        }
    }

    presentation->dynamicCall( "SaveAs( QString, int, bool )", fileName, 1, true );
    axWPSPpt->dynamicCall( "Quit(void)" );
    disConnectWPSPpt();
    deleteTempPicture( picList );
    return true;
}

bool HHOfficeDoc::getWPSPPTPageInfo(QString &sPageInfo)
{
    if( axWPSPpt == NULL )
    {
        if( !connectWPSPpt() )
            return -1;
    }
    QAxObject *presentation = axWPSPpt->querySubObject("ActivePresentation");
    if( !presentation )
        return -1;
    QAxObject *slideShowWindow = presentation->querySubObject("SlideShowWindow");
    if( !slideShowWindow )
        return -1;
    QAxObject *view = slideShowWindow->querySubObject("View");
    QAxObject *slide = view->querySubObject("Slide");
    QAxObject *slides = view->querySubObject("Slides");
    if( slide && slides )
    {
        int nPosition = slide->dynamicCall("SlideIndex").toInt();
        int nAllCount = slides->dynamicCall("Count").toInt();

        slide->disableMetaObject();
        slides->disableMetaObject();
        slideShowWindow->disableMetaObject();
        presentation->disableMetaObject();

        sPageInfo = QString("%1/%2").arg(nPosition).arg(nAllCount);
        return nPosition;
    }
    else
    {
        QAxObject *slides = presentation->querySubObject("Slides");
        int nPosition = slides->dynamicCall("Count").toInt();
        slides->disableMetaObject();
        view->disableMetaObject();
        slideShowWindow->disableMetaObject();
        presentation->disableMetaObject();

        sPageInfo = QString("%1/%2").arg(nPosition).arg(nPosition);
        return nPosition + 1;
    }
    return -1;
}

bool HHOfficeDoc::setWPSPPTPenInfo(const QString &sPageType, const QVariantMap &args)
{
    if( axWPSPpt == NULL )
    {
        if( !connectWPSPpt() )
            return false;
    }

    setWPSPenType(sPageType);

    if(!args.isEmpty()){

    }

    return true;
}

bool HHOfficeDoc::getWPSPPTThumbnail(QStringList &lResultFile,
                                     const QString &sPath,
                                     const QString sImgType,
                                     const QSize imgSize)
{
    return true;
}

bool HHOfficeDoc::exportPPT(QString fileName, QStringList picList)
{
    if(fileName.isEmpty() || picList.isEmpty())
        return false;

    HRESULT hRet( E_FAIL );
    if(!connectPPT())
        return false;

    m_PptApplication->put_Visible( msoFalse );
    m_PptApplication->put_ShowWindowsInTaskbar( msoFalse );

    MSPPT::PresentationsPtr Presentations = NULL;
    MSPPT::_PresentationPtr Presentation = NULL;
    MSPPT::SlidesPtr		pSlides = NULL;
    MSPPT::_SlidePtr		pSlide = NULL;
    MSPPT::ShapeRangePtr	pShapeRange = NULL;
    MSPPT::FillFormatPtr	pFillFormat = NULL;

    m_PptApplication->get_Presentations( &Presentations );
    if ( Presentations == NULL)
        goto failed_return;

    Presentation = Presentations->Add( msoTrue );
    if ( Presentation == NULL  )
    {
        Presentations = NULL;
        goto failed_return;
    }

    pSlides = Presentation->GetSlides();
    if( NULL == pSlides )
    {
        Presentations = NULL;
        Presentation = NULL;
        goto failed_return;
    }

    int picNum = picList.size();
    for(int i=picNum-1; i>=0; i--)
    {
        QString picPath = picList[i];

        hRet = pSlides->Add( 1, MSPPT::PpSlideLayout::ppLayoutBlank ) ;
        if( FAILED( hRet ) )
        {
            Presentations = NULL;
            Presentation = NULL;
            pSlides = NULL;
            goto failed_return;
        }

        VARIANT varIndex;
        varIndex.vt = VT_I4;
        varIndex.lVal = 1;


        pSlide = pSlides->Item( varIndex );
        if(NULL == pSlide)
        {
            Presentations = NULL;
            Presentation = NULL;
            pSlides = NULL;
            goto failed_return;
        }

        hRet = pSlide->put_DisplayMasterShapes( msoTrue );
        if( FAILED(hRet))
            goto failed_null;

        hRet =  pSlide->put_FollowMasterBackground( msoFalse );
        if( FAILED(hRet) )
            goto failed_null;

//        pShapeRange = pSlide->GetBackground();
//        pFillFormat = pShapeRange->GetFill();

        /// 设置图片的位置
        float fWidth = 0.0f;
        float fHeight = 0.0f;
        MSPPT::PageSetupPtr pPageSetup = NULL;
        pPageSetup = Presentation->GetPageSetup();
        if(NULL == pPageSetup)
            goto failed_null;

        pPageSetup->get_SlideWidth(&fWidth);
        pPageSetup->get_SlideHeight(&fHeight);
        pSlide->Shapes->AddPicture((_bstr_t)picPath.toUtf8().data(),MsoTriState::msoFalse,
                                     MsoTriState::msoTrue, 0,0,fWidth,fHeight);

//        QString exportImage("D:\\%1.png");
//        pSlide->Export(exportImage.arg(QString::number(i)).toStdString().c_str(), "PNG",fWidth,fHeight);
    }

    try
    {
        hRet = Presentation->SaveAs( (_bstr_t)QStringToTCHAR(fileName), MSPPT::PpSaveAsFileType::ppSaveAsPresentation, msoCTrue );
    }
    catch( ... )
    {
        hRet = E_FAIL;
    }

    Presentation->Close();
    m_PptApplication->Quit();
    Presentations = NULL;
    Presentation = NULL;
    pSlides = NULL;
    pSlide = NULL;
//    pShapeRange = NULL;
//    pFillFormat = NULL;
    disConnectPPT();

    if( FAILED(hRet) )
    {
        return false;
    }

    deleteTempPicture(picList);
    return true;

failed_null:
    Presentations = NULL;
    Presentation = NULL;
    pSlides = NULL;
    pSlide = NULL;

failed_return:
    if( NULL != m_PptApplication )
    {
        m_PptApplication.Release();
        m_PptApplication = NULL;
		disConnectPPT();
    }
    return false;
}

bool HHOfficeDoc::exportPDF(QString fileName, QStringList picList)
{
    if(fileName.isEmpty() || picList.isEmpty())
        return false;

    try {
        PDFlib pdf;
        pdf.set_parameter("compatibility", "1.4" );
        if(-1 == pdf.open( (char*)(_bstr_t)QStringToTCHAR(fileName) ) )
            return false;

        QString sScaleFactor = QApplication::instance()->property("scalefactor").toString();
        double scale;
        if(sScaleFactor.isEmpty()){
            scale = 1.0;
        }else{
            scale = sScaleFactor.toDouble();
        }
        int picNum = picList.size();
        for(int i=0; i<picNum; i++)
        {

            QString picPath = picList.at(i);
            QPixmap pixmap = QPixmap(picPath);
            pdf.begin_page(pixmap.width()*scale,pixmap.height()*scale);

            int img = pdf.open_image_file( "png", picPath.toLocal8Bit().data(), "", 0);
            pdf.place_image(img, 0.0, 0.0, scale);
            pdf.close_image(img);

            pdf.end_page();

        }

        //deleteTempPicture(picList); //改为在文件导出后删除临时文件
        pdf.close();
    } catch (...) {
        return false;
    }

    return true;
}

bool HHOfficeDoc::exportWORD(QString fileName, QStringList picList)
{
    if(fileName.isEmpty() || picList.isEmpty())
        return false;

    if ( NULL == m_WordApp )
    {
        m_WordApp.CoCreateInstance( __uuidof(MSWord::Application), NULL, CLSCTX_SERVER );
        if( NULL == m_WordApp )
            return false;
    }

    m_WordApp->put_Visible( msoFalse );
    MSWord::DocumentsPtr pDocuments = NULL;
    m_WordApp->get_Documents(&pDocuments);
    if(NULL == pDocuments)
    {
        DisConnectWord();
        return false;
    }

    m_WordDocument = NULL;
    CComVariant Template(""); //为了简单，没有使用WORD的文档模板
    CComVariant NewTemplate(false),DocumentType(0),Visible;
    m_WordDocument = pDocuments->Add( &Template,&NewTemplate,&DocumentType,&Visible );
    if( NULL == m_WordDocument )
    {
        DisConnectWord();
        return false;
    }

    m_WordSelection = NULL;
    m_WordDocument->Select();
    m_WordSelection = m_WordApp->GetSelection();
    if(NULL == m_WordSelection)
    {
        DisConnectWord();
        return false;
    }
    m_WordSelection->Collapse( &CComVariant( (short)1 ) );//折叠范围或选定内容

    MSWord::ShapeRangePtr	pShapeRange = NULL;
    MSWord::FillFormatPtr	pFillFormat = NULL;
    int nFinishAddpic = 1;
    int picNum = picList.size() - 1;
    for(int i=picNum; i>=0; i--)
    {
        m_WordShapes = NULL;
        m_WordShapes = m_WordDocument->GetShapes();
        if(NULL == m_WordShapes)
        {
            DisConnectWord();
            return false;
        }

        try
        {
            if( i != picNum )
            {
                // wdPageBreak
                m_WordSelection->InsertBreak( &CComVariant((short)7));
                /// wdLine
                m_WordSelection->MoveUp( &CComVariant((short)5),&CComVariant((short)1) );
                MSWord::WindowPtr pWordWindow = NULL;
                pWordWindow = m_WordApp->GetActiveWindow();
                if( NULL != pWordWindow )
                {
                    MSWord::PanePtr pWordPane = NULL;
                    pWordPane = pWordWindow->GetActivePane();
                    pWordPane->put_VerticalPercentScrolled( 0 );
                }
            }
        }
        catch(...)
        {

        }

        QString strFileName = picList[i];
        try
        {
            float fw = 0.0f;
            float fh = 0.0f;
            MSWord::PageSetupPtr pPageSetup = NULL;
            pPageSetup = m_WordDocument->GetPageSetup();
            if( NULL != pPageSetup )
            {
                /// 设置图片从页面起始0.0点插入
                pPageSetup->put_LeftMargin(0.0f);
                pPageSetup->put_TopMargin(0.0f);
                fw = (double)GetSystemMetrics( SM_CXSCREEN )*0.7;
                fh = (double)GetSystemMetrics( SM_CYSCREEN )*0.7;
                pPageSetup->put_PageHeight(fh);
                pPageSetup->put_PageWidth(fw);
            }
            m_WordShapes->AddShape( MsoAutoShapeType::msoShapeRectangle, 0.0f, 0.0f, fw, fh );

            long lShapsCount = m_WordShapes->GetCount();
            for( int j = nFinishAddpic; j <= lShapsCount; j++ )
            {
                VARIANT varIndex;
                varIndex.vt = VT_I4;
                varIndex.lVal = j;
                pShapeRange = m_WordShapes->Range( &varIndex );
                if( NULL != pShapeRange )
                {
                    pFillFormat = pShapeRange->GetFill();
                    pFillFormat->UserPicture( (_bstr_t)strFileName.toUtf8().data() );
                }
            }
            nFinishAddpic++;
        }
        catch(...)
        {

        }

        try
        {
            //CComVariant FileName(fileName.toUtf8().data());	//文件名
            CComVariant FileName(QStringToTCHAR(fileName));	//文件名
            CComVariant FileFormat(0);
            CComVariant LockComments(false),Password("");
            CComVariant AddToRecentFiles(true),WritePassword("");
            CComVariant ReadOnlyRecommended(false),EmbedTrueTypeFonts(false);
            CComVariant SaveNativePictureFormat(false),SaveFormsData(false);
            CComVariant SaveAsAOCELetter(false);

            /// 保存
            HRESULT hr(E_FAIL);
            hr = m_WordDocument->SaveAs(&FileName,&FileFormat,&LockComments,&Password,
                &AddToRecentFiles,&WritePassword,&ReadOnlyRecommended,
                &EmbedTrueTypeFonts,&SaveNativePictureFormat,&SaveFormsData,
                &SaveAsAOCELetter);
        }
        catch(...)
        {

        }
    }

    if( NULL != m_WordApp )
    {
        CComVariant vFalse((short)FALSE);
        m_WordDocument->raw_Close( &vFalse, &vtMissing, &vtMissing );
        pDocuments->raw_Close();
        VARIANT vt ;
        vt.vt =VT_ERROR;
        vt.scode =DISP_E_PARAMNOTFOUND;
        VARIANT v;
        v.vt =VT_BOOL;
        v.boolVal =VARIANT_TRUE;
        m_WordApp->Quit(&v,&vt,&vt);
        m_WordApp.Release();
        m_WordApp = NULL;
        pDocuments = NULL;
        m_WordDocument = NULL;
        pShapeRange =NULL;
        pFillFormat = NULL;
    }

    deleteTempPicture(picList);
    return true;
}

bool HHOfficeDoc::connectWPSWord()
{
    m_axWPSWord = new QAxObject("kwps.Application");
    QString uuid = m_axWPSWord->control() + "&";
    m_axWPSWord->setControl(uuid);
    return true;
}

bool HHOfficeDoc::disConnetWPSWord()
{
    m_axWPSWord->disableMetaObject();
    m_axWPSWord->deleteLater();
    m_axWPSWord->clear();
    delete m_axWPSWord;
    m_axWPSWord = NULL;
    return true;
}

bool HHOfficeDoc::exportWPSWord( QString fileName, QStringList picList )
{
    connectWPSWord();
    if( !m_axWPSWord )
        return false;
    m_axWPSWord->setProperty( "Visible", false );
    QAxObject* documents = m_axWPSWord->querySubObject("Documents");
    if( !documents )
    {
        disConnetWPSWord();
        return false;
    }

    QAxObject* document = documents->querySubObject("Add( QString, bool, int, bool )","",false,0,false);
    if( !document )
    {
        disConnetWPSWord();
        return false;
    }

    QAxObject* selection = m_axWPSWord->querySubObject("Selection");
    if( !selection )
    {
        disConnetWPSWord();
        return false;
    }

    selection->dynamicCall("Collapse(int)",1);

    int nFinishAddpic = 1;
    int picNum = picList.size() - 1;
    for(int i=picNum; i>=0; i--){
        QAxObject* shapes = document->querySubObject("Shapes");
        if( !shapes )
        {
            disConnetWPSWord();
            return false;
        }

        if( i != picNum )
        {
            selection->dynamicCall( "InsertBreak( int )", 7 );
            selection->dynamicCall( "MoveUp( int, int )", 5, 1 );
            QAxObject* activeWindow = m_axWPSWord->querySubObject( "ActiveWindow" );
            if( !activeWindow )
            {
                QAxObject* pane = activeWindow->querySubObject("ActivePane");
                pane->setProperty( "VerticalPercentScrolled", 0 );
            }
        }

        QString strFileName = picList[i];
        float fw = 0.0f;
        float fh = 0.0f;
        QAxObject* pageSetup = document->querySubObject( "PageSetup" );
        if( pageSetup )
        {
            pageSetup->setProperty( "LeftMarign", 0.0f );
            pageSetup->setProperty( "TopMarign", 0.0f );
            fw = (double)GetSystemMetrics( SM_CXSCREEN )*0.7;
            fh = (double)GetSystemMetrics( SM_CYSCREEN )*0.7;
            pageSetup->setProperty( "PageWidth", fw );
            pageSetup->setProperty( "PageHeight", fh );
        }
        shapes->dynamicCall( "AddShape( int, float, float, float, float )", 1, 0.0f, 0.0f, fw, fh );
        int shapesCount = shapes->dynamicCall("Count( void )").toInt();
        for( int j = nFinishAddpic; j <= shapesCount; j++ )
        {
//            varIndex.vt = VT_I4;
//            varIndex.lVal = j;
            QAxObject* shapeRange = shapes->querySubObject( "Range( int )", j );
            if( shapeRange )
            {
                QAxObject* fillFormat = shapeRange->querySubObject("Fill()");
                fillFormat->dynamicCall( "UserPicture( QString )", strFileName );
            }
        }
        document->dynamicCall( "SaveAs2( QString, int )", fileName, 0 );
        nFinishAddpic++;
    }
    disConnetWPSWord();
    deleteTempPicture( picList );
}

bool HHOfficeDoc::connectWPSExcel()
{
    m_axWPSExcel = new QAxObject("ket.Application");
    QString uuid = m_axWPSExcel->control() + "&";
    m_axWPSExcel->setControl( uuid );
    return true;
}

bool HHOfficeDoc::disConnectWPSExcel()
{
    m_axWPSExcel->disableMetaObject();
    m_axWPSExcel->deleteLater();
    m_axWPSExcel->clear();
    delete m_axWPSExcel;
    m_axWPSExcel = NULL;
    return true;
}

bool HHOfficeDoc::exportWPSExcel( QString fileName, QStringList picList )
{
    connectWPSExcel();
    if( !m_axWPSExcel )
        return false;
    m_axWPSExcel->setProperty( "Visible", false );
    QAxObject* workBooks = m_axWPSExcel->querySubObject("Workbooks");
    if( !workBooks )
    {
        disConnectWPSExcel();
        return false;
    }
    QAxObject* workBook = workBooks->querySubObject("Add( void )");
    if( !workBook )
    {
        disConnectWPSExcel();
        return false;
    }
    QAxObject* sheets = workBook->querySubObject("Sheets");
    if( !sheets )
    {
        disConnectWPSExcel();
        return false;
    }
    int nNum = sheets->dynamicCall("Count( void )").toInt();
    for( int i = 1; i <= nNum; i++ )
    {
        QAxObject* workSheet = sheets->querySubObject("Item( int )", i );
        if( !workSheet )
            continue;
        workSheet->dynamicCall( "Delete( void )" );
    }

    QRect rect(0,0,1024,768);
    int picNum = picList.size()-1;
    QString tempName("Page%1");
    for( int i = picNum; i >= 0; i-- )
    {
        sheets->dynamicCall("Add(void)");
        QAxObject* workSheet= m_axWPSExcel->querySubObject( "ActiveSheet" );
        if ( !workSheet )
            continue;
        QString sheetName = tempName.arg(QString::number(i+1));
        workSheet->setProperty( "Name", sheetName );
        QAxObject* shapes = workSheet->querySubObject( "Shapes" );
        if( !shapes )
            continue;
        QString picName = picList[i];
        shapes->dynamicCall( "AddPicture( QString, bool, bool, int, int, int, int )",
                             picName, false, true, rect.left(), rect.top(),rect.width(),rect.height() );
    }

    nNum = sheets->dynamicCall("Count( void )").toInt();
    for ( int i = nNum; i>= 1; i-- )
    {
        QAxObject* workSheet = sheets->querySubObject("Item( int )", i );
        if ( !workSheet )
            continue;
        QString strSheetName = workSheet->property("Name").toString();
        if ( strSheetName.contains("Sheet")  )
        {
            workSheet->dynamicCall("Delete( void )");
            break;
        }
    }

    workBook->dynamicCall("SaveAs( QString )", fileName );
    workBook->dynamicCall( "Close(void)" );
    disConnectWPSExcel();
    deleteTempPicture( picList );
    return true;
}

bool HHOfficeDoc::exportEXCEL(QString fileName, QStringList picList)
{
    if(fileName.isEmpty() || picList.isEmpty())
        return false;

    if(!connectExcel())
        return false;

    MSExcel::WorkbooksPtr				pWorkBooks = NULL;
    MSExcel::SheetsPtr					pExcelWorksheets = NULL;
    MSExcel::_WorksheetPtr              pExcelWorksheet = NULL;
    MSExcel::WindowPtr  				pExcelWindow = NULL;
    MSExcel::ShapesPtr  			    pExcelShapes = NULL;
    MSExcel::ShapePtr					pExcelShape = NULL;
    m_pWorkBook = NULL;

    try
    {
        m_ExcelApp->put_Visible( 1, msoFalse );
        pWorkBooks = m_ExcelApp->GetWorkbooks();
        if(NULL == pWorkBooks)
        {
            disConnectExcel();
            return false;
        }

        m_pWorkBook = pWorkBooks->Add( );
        if(NULL == m_pWorkBook)
        {
            disConnectExcel();
            return false;
        }

        pExcelWorksheets = m_pWorkBook->GetSheets();
        if(NULL == pExcelWorksheets)
        {
            disConnectExcel();
            return false;
        }

        /// 删除其余sheet
        long nNum = 0;
        pExcelWorksheets->get_Count(&nNum);
        _variant_t vt;
        vt.vt = VT_I2;
        for ( int i = 1; i<= nNum; i++ )
        {
            vt.iVal = i;
            pExcelWorksheet = NULL;
            pExcelWorksheet = pExcelWorksheets->GetItem(vt);
            if (pExcelWorksheet == NULL)
                continue;
            /// excel 2013环境下这句话报错
            ///pExcelWorksheet->Delete();
            try
            {
                pExcelWorksheet->Delete();
            }
            catch(...)
            {
                break;
            }
            nNum = 0;
            pExcelWorksheets->get_Count(&nNum);
            i = 1;
        }
    }
    catch (...)
    {
        if( NULL != m_ExcelApp )
        {
            pWorkBooks = NULL;
            m_pWorkBook = NULL;
            pExcelWorksheets = NULL;
            pExcelWorksheet = NULL;
            pExcelWindow = NULL;
            pExcelShapes = NULL;
            pExcelShape = NULL;

            m_ExcelApp->Quit();
            m_ExcelApp.Release();
            m_ExcelApp = NULL;
        }
        return false;
    }

    /// 得到图片的区域
    QRect rect(0,0,1024,768);
    int picNum = picList.size()-1;
    QString tempName("Page%1");
    for( int i = picNum; i >= 0; i-- )
    {
        ///  根据页面数生成对应的sheet
        pExcelWorksheets->Add();
        pExcelWorksheet = m_ExcelApp->GetActiveSheet();
        if (pExcelWorksheet == NULL)
            continue;

        QString sheetName = tempName.arg(QString::number(i+1));
        /// 更改Sheet的名字
        pExcelWorksheet->put_Name( CComBSTR( QStringToTCHAR(sheetName) ) );
        pExcelShapes = pExcelWorksheet->GetShapes();
        if(NULL == pExcelShapes)
            continue;

        pExcelShape = NULL;
        QString picName = picList[i];

        pExcelShape = pExcelShapes->AddPicture(_bstr_t( QStringToTCHAR(picName) ),msoFalse,msoTrue,rect.left(),rect.top(),rect.width(),rect.height() );
    }

    /// 删除默认生成的sheet
    long nNum = 0;
    pExcelWorksheets->get_Count(&nNum);
    _variant_t vt2;
    vt2.vt = VT_I2;
    for ( int i = nNum; i>= 1; i-- )
    {
        vt2.iVal = i;
        pExcelWorksheet = NULL;
        pExcelWorksheet= pExcelWorksheets->GetItem(vt2);

        if (pExcelWorksheet == NULL)
            continue;

        BSTR bSheetname;
        pExcelWorksheet->get_Name( &bSheetname );
        QString strSheetName( (char*)(_bstr_t)bSheetname );
        ///找到表名为Resource的
        if ( strSheetName.contains("Sheet")  )
        {
            pExcelWorksheet->Delete();
            break;
        }
    }

    fileName.replace("/","\\");
    BSTR bsname = SysAllocString((OLECHAR*)fileName.data());
    CComVariant FileName(bsname);	//文件名
    try
    {
        CComVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
        m_pWorkBook->SaveAs(FileName,covOptional,
            covOptional,covOptional,
            covOptional,covOptional,MSExcel::XlSaveAsAccessMode::xlExclusive,covOptional,covOptional,covOptional,
            covOptional);
        m_pWorkBook->Close(covOptional,covOptional,covOptional);
    }
    catch(...)
    {
        qDebug()<<"----------catch---";
    }
    SysFreeString(bsname);

    if( NULL != m_ExcelApp )
    {
        pWorkBooks->Close();
        pWorkBooks = NULL;
        m_pWorkBook = NULL;
        pExcelWorksheets = NULL;
        pExcelWorksheet = NULL;
        pExcelWindow = NULL;
        pExcelShapes = NULL;
        pExcelShape = NULL;

        m_ExcelApp->Quit();
        m_ExcelApp.Release();
        m_ExcelApp = NULL;
    }

    deleteTempPicture(picList);
    return true;
}

bool HHOfficeDoc::exportHTML(QString fileName, QStringList picList)
{
    if(fileName.isEmpty() || picList.isEmpty())
        return false;

    QString tempFileName(fileName);//"c://b/a.htm"
    int nLastSlash = tempFileName.lastIndexOf("/");
    int nLastDot = tempFileName.lastIndexOf(".");
    QString name = tempFileName.mid(nLastSlash+1, nLastDot-nLastSlash-1);//"a"
    name.append(".files");//"a.files"

    //创建html同目录下同名资源文件夹
    QString resPath = tempFileName.mid(0, nLastSlash+1);//"c://b/"
    resPath.append(name);
    QDir dir(resPath);
    if(dir.exists())
        dir.removeRecursively();
    dir.mkdir(resPath);

    //从临时图片目录剪切图片到资源目录
    resPath.append("/");
    name.append("/");
    QStringList relativePicList;
    relativePicList.clear();
    int picNum = picList.size();
    for(int i=0; i<picNum; i++)
    {
        QString newName = QString::number(i) + ".png";
        QString newPicPath(resPath);
        newPicPath += newName;
        if(QFile::rename(picList[i], newPicPath))
        {
            QString relativeName = name + newName;
            relativePicList<<relativeName;
        }
    }

    //创建html文件
    return createHtmlFile(fileName, relativePicList);
}

bool HHOfficeDoc::exportImage(QString fileName, QStringList picList)
{
    if(fileName.isEmpty() || picList.isEmpty())
        return false;

    QString tempFileName(fileName);//"c://b/a.png"
    int nLastDot = tempFileName.lastIndexOf(".");
    QString sCurDir = tempFileName.mid(0, nLastDot);//"a"
    QDir dir(sCurDir);
   if(dir.exists())
    {
        dir.removeRecursively();
    }
    dir.mkpath(sCurDir);

    int picNum = picList.size();
    for(int i=0; i<picNum; i++)
    {
        QString newName = QObject::tr("ID_HH_PAGE") + QString::number(i+1) + ".png";

        newName = sCurDir +"/"+ newName;
        QFile file(newName);
        //modify by zhangjinlu 2018/04/17 start 解决导出到图片重名覆盖时，保存不成功的问题
        if(file.exists()){
            file.remove();
        }
        //modify by zhangjinlu 2018/04/17 end
        QFile::rename(picList[i], newName);
    }

    return true;
}

QStringList HHOfficeDoc::importPPT(QString fileName, QString saveDir)
{
    QStringList picList;
    if(fileName.isEmpty() || saveDir.isEmpty())
        return picList;

    QString newPPTFile(saveDir);

    if(!connectPPT())
        return picList;

    QString picNameTemp("%1.png");
    MSPPT::PresentationsPtr Presentations = NULL;
    MSPPT::_PresentationPtr Presentation = NULL;
    MSPPT::SlidesPtr		pSlides = NULL;
    MSPPT::_SlidePtr		pSlide = NULL;
    MSPPT::ShapeRangePtr	pShapeRange = NULL;

    try
    {
        m_PptApplication->get_Presentations( &Presentations );
        if ( NULL == Presentations )
            goto end_import;

        //copy到临时目录，并改名
        QString format = fileName.mid( fileName.lastIndexOf(".")+1 );
//        QString newPPTFile(saveDir);
        newPPTFile.append("temp.").append(format);
//        qDebug()<<"------------------importPPT___newPPTFile:"<<newPPTFile;

        bool copySuccess = QFile::copy(fileName, newPPTFile);
        if(!copySuccess)
            goto end_import;

//        qDebug()<<"-----------------importPPT___---1-";
        BSTR bsname = SysAllocString((OLECHAR*)newPPTFile.data());//	pWorkbooks->raw_Open(_bstr_t(bsname)
//        BSTR bsname = SysAllocString(fileName.toStdWString().c_str());
        Presentation = Presentations->Open(_bstr_t(bsname), msoTrue, msoTrue, msoFalse);
        if( NULL == Presentation)
            goto end_import;
        SysFreeString(bsname);

        pSlides = Presentation->GetSlides();
        if( NULL == pSlides )
            goto end_import;

        int count = pSlides->GetCount();
        HRESULT hr(E_FAIL);
        picNameTemp.prepend(saveDir);

        for(int i=0; i<count; i++)
        {
            VARIANT varIndex;
            varIndex.vt = VT_I4;
            varIndex.lVal = i+1;

            pSlide = pSlides->Item(varIndex);
            if(NULL == pSlide)
                continue;

            pShapeRange = pSlide->GetBackground();
            if(NULL == pShapeRange)
                continue;

            MSPPT::PageSetupPtr pPageSetup = NULL;
            pPageSetup = Presentation->GetPageSetup();
            if(NULL == pPageSetup)
                goto end_import;

            float fWidth = 0.0f;
            float fHeight = 0.0f;
            pPageSetup->get_SlideWidth(&fWidth);
            pPageSetup->get_SlideHeight(&fHeight);
            QString picName = picNameTemp.arg(QString::number(i));
            qDebug()<<"picName = "<<picName;
            hr = pSlide->Export(picName.toStdString().c_str(), "PNG", fWidth * 4 / 3, fHeight * 4 / 3 );
            if(!FAILED(hr))
                picList<<picName;

            MSPPT::ShapesPtr pShapes = pSlide->GetShapes();
            int shapesCount = pShapes->GetCount();
            for( int j = 1; j <= shapesCount; j++ )
            {
                VARIANT shapeVarIndex;
                shapeVarIndex.vt = VT_I4;
                shapeVarIndex.lVal = j;

                MSPPT::ShapePtr pShape  = NULL;
                pShape = pShapes->Item( shapeVarIndex );
                if( NULL == pShape )
                    continue;

                QString itemPath = "C:/Users/Administrator/Desktop/Demo/" + QString::number(i) + "_" + QString::number(j) + ".png" /*".bmp"*//*".jpg"*/;

                HRESULT shapeHr(E_FAIL);
                shapeHr = pShape->Export(itemPath.toStdString().c_str(), MSPPT::PpShapeFormat::ppShapeFormatPNG/*MSPPT::PpShapeFormat::ppShapeFormatBMP*//*MSPPT::PpShapeFormat::ppShapeFormatJPG*/, 0, 0, MSPPT::ppScaleXY/*MSPPT::PpExportMode::ppRelativeToSlide*/);
                qDebug()<<"itemPath = "<<itemPath;
                qDebug()<<"shapeHr = "<<FAILED( shapeHr );
                if( FAILED( shapeHr ) )
                    qDebug()<<"Item Export Filed!!!";
            }
        }

    }
    catch(...)
    {
        goto end_import;
    }
    pShapeRange = NULL;
    pSlide = NULL;
    pSlides = NULL;

end_import:
    if(NULL != Presentation)
    {
        Presentation->Close();
        Presentation = NULL;
    }
    Presentations = NULL;
//    m_PptApplication->Quit();
    disConnectPPT();

    QFile pFile(newPPTFile);
    if(pFile.exists())
    {
        pFile.remove();
    }

    qDebug()<<"picList = "<<picList;
    return picList;
}

QVariantMap HHOfficeDoc::importPPT2(QString fileName)
{
    QVariantMap presMap;
    if( !axPptApp )
        connectPPTApp();
    axPptApp->setProperty( "Visible", true );
    QAxObject* presentations = axPptApp->querySubObject("Presentations");
    if( presentations == NULL )
    {
        disConnectPPTApp(); //需要关闭 wangxb.
        return presMap;
    }
    QAxObject* presentation = presentations->querySubObject( "Open( QString, bool, bool, bool)", fileName, true, true, false );
    if( presentation == NULL )
    {
        disConnectPPTApp(); //需要关闭 wangxb.
        return presMap;
    }

    QAxObject* pageSetup = presentation->querySubObject("PageSetup()");
    QAxObject* slides = presentation->querySubObject("Slides");
    qDebug()<<"slides = "<<slides;
    int count = slides->dynamicCall("Count").toInt();
    QVariantList vSlideAry;
    for( int i = 1; i <= count; i++ )
    {
        QAxObject* slide = slides->querySubObject( "Item( int )", i );

        QVariant v = QVariant::fromValue((void *) slide);
        vSlideAry.push_back( v );

        presMap["width"] = pageSetup->property("SlideWidth").toFloat()*4/3;
        presMap["height"] = pageSetup->property("SlideHeight").toFloat()*4/3;
    }
    presMap[ "Slides" ] = vSlideAry;
    presMap[ "presentation"] = QVariant::fromValue( (void*)presentation );
    return presMap;
}

QVariantMap HHOfficeDoc::getJSONFromPPTSlide(void* pSlide, QString strDir )
{
    QVariantMap mapShapes;
    QAxObject* slide = (QAxObject*)pSlide;
    QString slideId = HHToolHelper::getObjectID();
    strDir = strDir.replace( "/", "\\" );
    QString filePath = strDir + "index\\" + slideId + ".png";
    if( slide == NULL ) {
        qDebug()<<"slide is Invalied!!!";
        return mapShapes;
    }
    slide->dynamicCall("Export(QString,QString)",filePath,"PNG");
    QAxObject* shapes = slide->querySubObject("Shapes");
	//有可能没有shapes，从而引起崩溃。
	int shapesCount = 0;
	if (shapes != NULL) 
	     shapesCount = shapes->dynamicCall("Count").toInt();

    QVector< QAxObject* > vecShapes;  //定义准确些 Wangxb
    QVariantList listShape;
	QAxObject* shape = nullptr;
	for (int i = 1; i <= shapesCount; i++) {
		shape = nullptr;
		shape = shapes->querySubObject("Item( int )", i);
		if (shape) {
			if (shape->dynamicCall("Visible").toBool()) {
				shape->dynamicCall("SetVisible(bool)", false);

				vecShapes.push_back(shape);

				QVariant v = QVariant::fromValue((void *)shape);
				listShape.push_back(v);
			}
		}
	}
	filePath=strDir + "filelibrary\\" + slideId + ".png";
    slide->dynamicCall( "Export(QString,QString,float,float)", filePath,"PNG");

    for( int i = 0; i < vecShapes.size(); i++ ){
        vecShapes[i]->dynamicCall( "SetVisible(bool)", true );
    }

    mapShapes[ "ID" ] = slideId;
    mapShapes[ "ICON" ] = slideId + ".png";
    mapShapes[ "Shapes" ] = listShape;
    return mapShapes;
}

int HHOfficeDoc::getTypeFromPPTItem( void *	pItem )
{  
	//JlCompress::extractDir("F:\\file_hhtx\\zzz-1.zip", "F:\\file_hhtx\\hitler"); //压缩
    QAxObject* item = (QAxObject*)pItem;
    if( item )
    {
        return item->dynamicCall("Type( void )").toInt();
    }
    else
        return -1;
}
/*/TTQX-zhaozhengze-ppt导入视频和音频
/*/

static void clearMapInformation()
{
	s_VecMap.clear();
	s_map.clear();
	s_refmap.clear();
	s_StringMapToVec.clear();
	s_StringToMap.clear();;
}
static bool isFileExit(QString& strFileNames)
{
	QFile file3(strFileNames);
	return file3.exists();
}

//初始化slide的信息
static void initialSlideInformation(QString& strFileSlideName)
{
	QDomDocument doc(strFileSlideName);
	QFile file(strFileSlideName);
	if (!file.open(QIODevice::ReadOnly))
		return ;
	if (!doc.setContent(&file))
	{
		file.close();
		return ;
	}
	file.close();

	QDomElement element = doc.documentElement();
	extractNameAndLinkInfo(element);
}

static void initialSlideRefInformation(QString& strRefFileSlideName)
{
	QDomDocument doc(strRefFileSlideName);
	QFile file(strRefFileSlideName);
	if (!file.open(QIODevice::ReadOnly))
		return;
	if (!doc.setContent(&file))
	{
		file.close();
		return;
	}
	file.close();

	QDomElement element = doc.documentElement();
	extractIdAndTarget(element);
}
static void initialCurrmentSlideInformation(QString strSlideIndex, QString strUnCompressPath)
{
	/*
	需要的文件
	1 找到当前slide的文件。
	2 找到当前media所在的文件。
	3 找到当前slide ref所在的文件夹。
	slides\_rels
	*/
	clearMapInformation();
	QString strSlideName = "slide" + strSlideIndex + ".xml";
	QString strFileSlideName = strUnCompressPath + "\\ppt\\slides\\" + strSlideName;
	if(!isFileExit(strFileSlideName))
	{
		return;
	}

	QString strRefFileSlideName = strUnCompressPath + "\\ppt\\slides\\_rels\\" + strSlideName + ".rels";
	if (!isFileExit(strRefFileSlideName))
	{
		return;
	}

	initialSlideInformation(strFileSlideName);
	initialSlideRefInformation(strRefFileSlideName);
	s_StringMapToVec.insert(std::make_pair(strSlideIndex, s_VecMap));
	s_StringToMap.insert(std::make_pair(strSlideIndex, s_refmap));

	s_VecMap.clear();
	s_refmap.clear();
}

static QString getPathNamebyMediaName(QString& strMediaName,TMapVec& vecMap, TMap& refMap)
{  
	TMapVec::iterator iter = vecMap.begin();
	for (; iter != vecMap.end(); ++iter)
	{
		TMap& lM = *iter; 
		if (lM.count(s_strAttName) == 0)
		{
			continue; 
		}

		if (lM.count(s_strAttLink) == 0)
		{
			continue;
		}

		QString strItemName = lM[s_strAttName];
		if (strMediaName != strItemName)
		{
			continue;
		}

		QString strLinkName = lM[s_strAttLink];
		if (refMap.count(strLinkName) > 0)
		{
			return refMap[strLinkName];
		}
		break;
	}
	return QString();
}

QJsonObject HHOfficeDoc::getMediaJSON(void* pItem, QString strDir, QString strUnCompressPath, QString strSlideIndex)
{
	if (NULL == pItem)
	{
		return getPictureJSON(pItem,strDir);
	}

	if (strDir.isEmpty() || strUnCompressPath.isEmpty() || strSlideIndex.isEmpty())
	{
		return getPictureJSON(pItem, strDir);
	}

	/*
	ppMediaTypeMixed	=-2
	ppMediaTypeOther	=1
	ppMediaTypeSound	=2
	ppMediaTypeMovie	=3
	*/
	QAxObject* item = (QAxObject*)pItem;
	int nType = item->property("MediaType").toInt();
	if (3 == nType  || 2 == nType) //视频和音频一起处理
	{ 
		QString strMediaFullPath;
		QAxObject* pLinkFormat = item->querySubObject("LinkFormat");
		if (NULL  != pLinkFormat)
		{
			strMediaFullPath = pLinkFormat->property("SourceFullName").toString();
		}
		//修正bug：[B171228-052]【版本软件+ppt导入】音频导入后音频的名称显示不正确，不是音频本身的名称，如图；视频名称也不是本身的名称
		//得到选中视频或者音频的名字
		QString strMediaName = item->property("Name").toString();
		QString strExtend = "";
		QString strDestFile = "";
		if (strMediaFullPath.isEmpty())
		{
			//获得视频或者音频的路径。
			if (0 == s_StringMapToVec.count(strSlideIndex) || 0 == s_StringToMap.count(strSlideIndex))
			{
				initialCurrmentSlideInformation(strSlideIndex, strUnCompressPath);
			}

			if (0 == s_StringMapToVec.count(strSlideIndex) || 0 == s_StringToMap.count(strSlideIndex))
			{
				return  getPictureJSON(pItem, strDir);
			}

			TMapVec& vecMap = s_StringMapToVec[strSlideIndex];
			TMap&    refMap = s_StringToMap[strSlideIndex];

			QString strMediaPathName = getPathNamebyMediaName(strMediaName, vecMap, refMap);
			//.mid(strPPtFileName.lastIndexOf(".") + 1);
			QString strMediaEmbedName = strMediaPathName.mid(strMediaPathName.lastIndexOf("/") + 1);
			strMediaFullPath = strUnCompressPath + "\\ppt\\media\\" + strMediaEmbedName;
			strExtend = strMediaEmbedName.mid(strMediaEmbedName.lastIndexOf("."));
			strDestFile = strDir + "filelibrary/" + strMediaName + strExtend;
			QFile::rename(strMediaFullPath, strDestFile);
		}

		if (isFileExit(strDestFile)) {   //视频或音频类型，需要传入位置宽度和路径。
			QJsonObject itemObj;
			QString itemId = HHToolHelper::getObjectID();

			float left = item->property("Left").toFloat()*4.0 / 3.0;
			float top = item->property("Top").toFloat()*4.0 / 3.0;
			float width = item->property("Width").toFloat()*4.0 / 3.0;
			float height = item->property("Height").toFloat()*4.0 / 3.0;
			
			itemObj["BoundingBox"] = QString::number(left) + ","
				+ QString::number(top) + ","
				+ QString::number(left + width) + ","
				+ QString::number(top + height);
			itemObj["ID"] = itemId;
			//已经将文件调整为hhtx文件的相对路径位置。
			//itemObj["AbsMediaFile"] = strMediaFullPath;
			QString strFile = strMediaName + strExtend;
			itemObj["MultiMediaFile"] = strFile;
			itemObj["Angle"] = item->dynamicCall("Rotation( void )").toFloat();
			itemObj["InfiniteClone"] = false;
			itemObj["LockIn"] = false;
			QString strItemName = "HHMediaVideo";
			if (2  == nType)
			{
				strItemName = "HHMediaAudio";
			}
			itemObj["Type"] = strItemName;
			itemObj["Visible"] = true;
			itemObj["fun"] = "";
			itemObj["saveType"] = "local";
			//为PPt导入中的视频item添加一标志：itemObj["fromPPT"] = "pptimport"，供视频模块特殊处理。
			itemObj["fromPPT"] = "pptimport";
			return itemObj;
		}
		else
		{
			 return getPictureJSON(pItem, strDir);
		}
	}

	return getPictureJSON(pItem, strDir);
}
//*/

QJsonObject HHOfficeDoc::getTextEditJSON(void* pItem, QString strDir)
{
	QJsonObject itemObj;
	QAxObject* item = (QAxObject*)pItem;
	if (item)
	{    
		//pItem->
		long lHasTextFrame = item->dynamicCall("HasTextFrame(void)").toInt();
		if (!lHasTextFrame)
		{
			return getPictureJSON(pItem, strDir); 
		} 
		else
		{   
			QAxObject* textFrame = item->querySubObject( "TextFrame");
			if (NULL == textFrame)
			{
				return getPictureJSON(pItem, strDir);
			}
			textFrame->setProperty("AutoSize", 1);

			QAxObject* textRange = textFrame->querySubObject("TextRange");
			if (NULL == textRange)
			{
				return getPictureJSON(pItem, strDir);
			}
			textRange->dynamicCall("Copy(void)");

            QWidget  widget;
            CTextCtrl  pc;
            pc.CreateTextBox((HWND)widget.winId());

            QString strTextLabel ="TextHtml";
            QString strText;
            if(pc.IsWindow())
            {
                pc.SendMessage(EM_PASTESPECIAL);
				QTextEdit textEdit;
				textEdit.paste();
				strText = pc.GetTextContent() + QString("|*&&&&&*|") + textEdit.toPlainText() + QString("|*&&&&&*|") + textEdit.toHtml();
                strTextLabel ="TextRTF";
            }
            else
            {
                QTextEdit textEdit;
                textEdit.paste();
                strText = textEdit.toHtml();
            }

			QString itemId = HHToolHelper::getObjectID();
			float left = item->property("Left").toFloat()*4.0 / 3.0;
			float top = item->property("Top").toFloat()*4.0 / 3.0;
			float width = item->property("Width").toFloat()*4.0 / 3.0 ;
			float height = item->property("Height").toFloat()*4.0 / 3.0 ;

			itemObj["BoundingBox"] = QString::number(left) + ","
				+ QString::number(top) + ","
				+ QString::number(left + width) + ","
				+ QString::number(top + height);
			itemObj["ID"] = itemId;
			itemObj["Angle"] = item->dynamicCall("Rotation( void )").toFloat();
			itemObj["InfiniteClone"] = false;
			itemObj["LockIn"] = false;
			itemObj["Type"] = "HHTextBoard_FromPPt";
			itemObj["Visible"] = true;
			itemObj["fun"] = "";
			itemObj["saveType"] = "local";
            itemObj[strTextLabel] = strText;
		}
	}
	return itemObj;
}

QJsonObject HHOfficeDoc::getPictureJSON(void *pItem, QString strDir)
{
	QMutex   mutex;
	mutex.lock();
    QJsonObject itemObj;
    QAxObject* item = (QAxObject*)pItem;
    if( item )
    {
        QString itemId = HHToolHelper::getObjectID();
        QString fileName = QUuid::createUuid().toString()+ ".png";
        QString path = strDir + "filelibrary/" + "temp.png";

        float left = item->property("Left").toFloat()*4.0/3.0;
        float top = item->property("Top").toFloat()*4.0/3.0;
        float width = item->property("Width").toFloat()*4.0/3.0;
        float height = item->property("Height").toFloat()*4.0/3.0;
        item->dynamicCall("Export(QString,int,float,float)",path,MSPPT::PpShapeFormat::ppShapeFormatPNG);
		//Modify by wangxianbing,2017,12,26.
		//前面的item宽高可能不准，根据导出的图片尺寸来修正,这很关键，许多错位bug就因此产生。
		QPixmap tmpPix;
		if (tmpPix.load(path)) {
			QSize szImg = tmpPix.size();
			//调整位置
			left -= (szImg.width() - width) / 2.0;
			top -= (szImg.height() - height) / 2.0;
			//调整宽高
			width = szImg.width();
			height = szImg.height();
		}
		//end.

        itemObj[ "BoundingBox" ] = QString::number(left) + ","
                                    + QString::number(top) + ","
                                    + QString::number(left + width) + ","
                                    + QString::number(top + height);
        itemObj[ "ID" ] = itemId;
        itemObj[ "MultiMediaFile" ] = fileName;
        itemObj[ "Angle" ] = item->dynamicCall("Rotation( void )").toFloat();
        itemObj[ "InfiniteClone" ] = false;
        itemObj[ "LockIn" ] = false;
        itemObj[ "Type" ] = "HHImagePic";
        itemObj[ "Visible" ] = true;
        itemObj[ "fun" ] = "";
        itemObj[ "saveType" ] = "local";
		itemObj["fromPPT"] = "pptimport";
        QFile::rename( path, strDir + "filelibrary/" + fileName);
    }
	mutex.unlock();
    return itemObj;
}
//Add by wangxianbing,2018/1/10 尝试关闭ppt进程。
void HHOfficeDoc::closePPTApp()
{
	disConnectPPTApp();//需要关闭进程 wangxb
}
void HHOfficeDoc::closePPTPresentation(void *pItem)
{
    if( !pItem )        return;
    QAxObject *presentation = (QAxObject*)pItem;
    presentation->dynamicCall("Close(void)");
    disConnectPPTApp();  //需要关闭进程 wangxb

    /*/TTQX-zhaozhengze-ppt导入视频和音频
	/*/
	clearMapInformation();
	//*/
}

bool HHOfficeDoc::getPPTPageInfo(QString &sPageInfo)
{
    if( !connectPPT() )
        return - 1;
    try {
        m_PptPresentation = m_PptApplication->GetActivePresentation();
        m_PptSlideShowWindow = m_PptPresentation->GetSlideShowWindow();
        m_PptSlideshowView = m_PptSlideShowWindow->GetView();

        m_PptSlides = m_PptPresentation->GetSlides();
        int nTotal = m_PptSlides->GetCount();
        int nCurPage = m_PptSlideshowView->GetCurrentShowPosition();

        sPageInfo = QString("%1/%2").arg(nCurPage).arg(nTotal);

        return nCurPage;
    } catch( ... ) {
        return - 1;
    }
    return - 1;
}

bool HHOfficeDoc::setPPTPenInfo(const QString &sPageInfo, const QVariantMap &args)
{
    if( !connectPPT() )
        return - 1;
    try {
        m_PptPresentation = m_PptApplication->GetActivePresentation();
        m_PptSlideShowWindow = m_PptPresentation->GetSlideShowWindow();
        m_PptSlideshowView = m_PptSlideShowWindow->GetView();

        if(sPageInfo == QString("ID_MODULE_SELECT")){
            m_PptSlideshowView->PutPointerType(
                        MSPPT::ppSlideShowPointerArrow);
        }
        else if(sPageInfo == QString("ID_MODULE_STROKESMOOTH")){
            m_PptSlideshowView->PutPointerType(MSPPT::ppSlideShowPointerPen);
            QString sPenID = args.value("PenID").toString();
            if(sPenID == QString("ID_ITEM_STROKE_SMOOTH")){
                //m_PptSlideshowView->PutPointerType(MSPPT::ppSlideShowPointerPen);
            }
            else if(sPenID == QString("ID_ITEM_STROKE_LASER")){
                m_PptSlideshowView->PutPointerType(
                            MSPPT::ppSlideShowPointerArrow);
                m_PptSlideshowView->PutAcceleratorsEnabled(Office::msoTrue);
            }
            else if(sPenID == QString("ID_ITEM_STROKE_FLUORESCENT")){

            }

            QString sColor = args.value("Color").toString();
            if(!sColor.isEmpty()){
                QStringList lColor = sColor.split(",");
                if (lColor.size() < 3) return 0;

                int nRed = lColor.at(0).toInt();
                int nGreen = lColor.at(1).toInt();
                int nBlue = lColor.at(2).toInt();
                m_PptSlideshowView->PointerColor->PutPPTRGB(
                            RGB(nRed, nGreen, nBlue));
            }
        }
        else if(sPageInfo == QString("ID_MODULE_DELETE")){
            m_PptSlideshowView->PutPointerType(
                        (MSPPT::PpSlideShowPointerType)5);
        }

        return 0;

    } catch( ... ) {
        return - 1;
    }

    return - 1;
}

bool HHOfficeDoc::getPPTThumbnail(QStringList &lResultFile,
                                  const QString &sPath,
                                  const QSize imgSize,
                                  const QString sImgType)
{
    if( !connectPPT() )
        return - 1;
    try {
        m_PptPresentation = m_PptApplication->GetActivePresentation();

        m_PptSlides = m_PptPresentation->GetSlides();
        if(m_PptSlides == nullptr) return -1;

        lResultFile.clear();
        int nCount = m_PptSlides->GetCount();
        for(int i = 1; i <= nCount; i++){
           m_PptSlide = m_PptSlides->Item(i);
           if(m_PptSlide != nullptr){
               QString sFilePath = QString("%1/%2/.%3")
                       .arg(sPath).arg(i).arg(sImgType);
               int nResult = m_PptSlide->Export(sFilePath.toStdWString().c_str(),
                                  sImgType.toStdWString().c_str(),
                                  imgSize.width(), imgSize.height());
               if(nResult >= 0){
                   lResultFile.append(sFilePath);
               }
           }
        }

        return 0;

    } catch( ... ) {
        return - 1;
    }

    return - 1;
}

bool HHOfficeDoc::connectExcel() {
    if( m_ExcelApp )
        return true;
    HRESULT hRet = m_ExcelApp.CoCreateInstance( __uuidof(MSExcel::Application), NULL, CLSCTX_SERVER );
    if( FAILED( hRet ) || NULL == m_ExcelApp ) {
        if( m_ExcelApp ) {
            m_ExcelApp.Release();
            m_ExcelApp = NULL;
        }
        return false;
    } else {
        _bstr_t version = m_ExcelApp->GetVersion();
        m_ExcelVersion = atof((const char*)version);
        return true;
    }
}

bool HHOfficeDoc::disConnectExcel() {
    try {
        if( NULL != m_ExcelApp ) {
            m_ExcelApp.Release();
            m_ExcelApp = NULL;
        }
    } catch(...) {
        return false;
    }
    return true;
}

bool HHOfficeDoc::embedExcel( QString strFilename, QRect InputRect ) {

//    if( m_bIsWPS )
//        return InsertWPSExcel( strFilename, InputRect );
    return InsertExcel(strFilename, InputRect);   
}

BOOL HHOfficeDoc::ConnectExcel()
{
    if( NULL != m_ExcelApp )
    {
        return TRUE;
    }

    CLSID clsid;
    CLSIDFromProgID(L"Excel.Application", &clsid);

    try
    {
        IUnknown *pUnk;
        HRESULT hr = GetActiveObject(clsid, NULL, (IUnknown**)&pUnk);

        if (hr == S_OK)
        {
            IDispatch *pDisp;
            hr = pUnk->QueryInterface(IID_IDispatch, (void **)&pDisp);
            pUnk->Release();

            CComQIPtr<MSExcel::_Application> Application(pDisp);
            ATLASSERT(Application);
            m_ExcelApp = NULL;
            Application->QueryInterface( __uuidof(MSExcel::_Application), (void**)&m_ExcelApp );
            ATLASSERT(m_ExcelApp);

            if( !m_ExcelApp )
            {

                return FALSE;
            }

            pDisp->Release();
            TCHAR * stopstring;
            m_ExcelVersion = _tcstod( m_ExcelApp->GetVersion(), &stopstring );

            return TRUE;
        }
        else{

        }
    }
    catch(...)
    {

        return FALSE;
    }

    if( !m_ExcelApp )
        return FALSE;
    else
        return TRUE;
}

BOOL HHOfficeDoc::DisConnectExcel()
{
    try
    {
        if( NULL != m_ExcelApp )
        {
            m_ExcelApp.Release();
            m_ExcelApp = NULL;
        }
    }

    catch(...)
    {
        return FALSE;
    }

    return TRUE;
}
float HHOfficeDoc::GetExcelShowPercentage()
{
    m_ExcelWindow = m_ExcelApp->GetActiveWindow();
    VARIANT varpercent = m_ExcelWindow->GetZoom();

    return (float)varpercent.dblVal / (float)100;
}

void HHOfficeDoc::ExcelUndoClear()
{
    CComVariant vTrue((short)TRUE);
    CComVariant vPassword(_T(""));

    try
    {
        m_ExcelWorksheet = m_ExcelApp->GetActiveSheet();
        m_ExcelWorksheet->Protect(vPassword, vTrue, vTrue,vTrue,vTrue);
        m_ExcelWorksheet->Unprotect(vPassword);
    }

    catch(...)
    {
        ;
    }
}

BOOL HHOfficeDoc::InsertExcel(const QString& strFilename,const QRect& InputRect, HWND pHwndExcel)
{
	float fScalePix = 1.0;
	float fPixToPoints = 0.75;
	try
	{
		SetProcessDPIAware();
		HDC hdcScreen = ::GetDC(NULL);
		float fScreenWidth = ::GetDeviceCaps(hdcScreen, LOGPIXELSX);
		float fScreenWidth1 = ::GetDeviceCaps(hdcScreen, LOGPIXELSY);
		float& fScale = fScalePix;
		fScale = fScreenWidth / 96.0;
		if (fScale - 2.0 > -1e-4)
		{
			fScale = 2.0;
		}
		else
		{
			fScale = 1.0;
		}

		QRect tempRect = InputRect;
		tempRect.setLeft(InputRect.left() * fScale);
		tempRect.setTop(InputRect.top() * fScale);
		tempRect.setRight(InputRect.right() * fScale);
		tempRect.setBottom(InputRect.bottom() * fScale);

		const_cast<QRect&>(InputRect) = tempRect;

		fPixToPoints = 72.0 / fScreenWidth;
	}
	catch (...)
	{
		return FALSE;
	}



	QPoint ptShapeTopLeft = InputRect.topLeft();//.TopLeft();

	//	float rectw = InputRect.width();
	//	float recth = InputRect.height();

	QPoint ptShapeCenterPoint;
	ptShapeCenterPoint.setX(ptShapeTopLeft.x() + 5);
	ptShapeCenterPoint.setY(ptShapeTopLeft.y() + 5);

	POINT pttl, pt;
	pttl.x = ptShapeTopLeft.rx();
	pttl.y = ptShapeTopLeft.ry();

	pt.x = ptShapeCenterPoint.rx();
	pt.y = ptShapeCenterPoint.ry();

	if (pHwndExcel == NULL)
	{
		pHwndExcel = ::WindowFromPoint(pt);
		if (pHwndExcel == NULL)
			return FALSE;
	}

	if (!ConnectExcel())
		return FALSE;

	if (false && m_ExcelVersion >= 16)
	{
		float ExcelShowPercentage = GetExcelShowPercentage() * 100;
		m_ExcelWindow = m_ExcelApp->GetActiveWindow();
		float fLeft = m_ExcelWindow->PointsToScreenPixelsX(0);
		float fTop = m_ExcelWindow->PointsToScreenPixelsY(0);

		fLeft = ((float)InputRect.left() - fLeft)*fPixToPoints * 100 / ExcelShowPercentage;
		fTop = ((float)InputRect.top() - fTop)*fPixToPoints * 100 / ExcelShowPercentage;

		float fWidth = (float)InputRect.width()*fPixToPoints * 100 / ExcelShowPercentage;
		float fHeight = (float)InputRect.height()*fPixToPoints * 100 / ExcelShowPercentage;

		m_ExcelWorksheet = m_ExcelApp->GetActiveSheet();

		m_ExcelShapes = m_ExcelWorksheet->GetShapes();

		BSTR bsname = SysAllocString((OLECHAR*)strFilename.data());

		float fAdust = 0.0;
		if (m_ExcelVersion >= 16)
		{
			fAdust = 0.0;
		}

		m_ExcelShape = m_ExcelShapes->AddPicture(_bstr_t(bsname), msoFalse, msoTrue, fLeft, fTop - fAdust, fWidth, fHeight);
		return TRUE;
	}

	///  遮挡窗体
	//    if( NULL != m_pProxyMaskWnd )
	//    {
	//        CRect rRect;
	//        ::GetClientRect( g_Presentation->m_hRootWnd, &rRect );
	//        ::SetWindowPos( m_hProxyWnd, NULL, rRect.left, rRect.top, rRect.Width(), rRect.Height(),
	//            SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_SHOWWINDOW );
	//    }


	::PostMessage(pHwndExcel, WM_KEYDOWN, WPARAM(BYTE(VK_ESCAPE)), 1);

	try
	{
		//LOG_DEBUG(("m_OfficeCmdBars = m_ExcelApp->GetCommandBars();"));
		m_OfficeCmdBars = m_ExcelApp->GetCommandBars();

		if (m_ExcelVersion < 12.0)
		{
			m_OfficeCmdBar = m_OfficeCmdBars->GetItem(CComVariant(_T("Lines")));
			m_OfficeCmdBarControls = m_OfficeCmdBar->GetControls();
			m_OfficeCmdBarControl = m_OfficeCmdBarControls->GetItem(CComVariant(long(6)));
		}
		else
		{
			m_OfficeCmdBarControl = m_OfficeCmdBars->FindControl(CComVariant(long(1)), CComVariant(long(1111)), CComVariant(_T("")), CComVariant(long(0)));
			if (NULL == m_OfficeCmdBarControl)
			{
				m_OfficeCmdBar = m_OfficeCmdBars->GetItem(CComVariant(_T("Lines")));
				m_OfficeCmdBarControls = m_OfficeCmdBar->GetControls();
				m_OfficeCmdBarControl = m_OfficeCmdBarControls->GetItem(CComVariant(long(6)));
			}

		}



		m_OfficeCmdBarControl->Execute();


		m_ExcelWorksheet = m_ExcelApp->GetActiveSheet();

		m_ExcelShapes = m_ExcelWorksheet->GetShapes();

		long ShapesCount = m_ExcelShapes->GetCount() + 1;


		::SetFocus(pHwndExcel);
		::SetForegroundWindow(pHwndExcel);

		::ScreenToClient(pHwndExcel, &pttl);
		::PostMessage(pHwndExcel, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pttl.x, pttl.y));
		::PostMessage(pHwndExcel, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pttl.x, pttl.y));
		::ScreenToClient(pHwndExcel, &pt);
		if (m_ExcelVersion > 11.0)
			::PostMessage(pHwndExcel, WM_MOUSEMOVE, MK_LBUTTON, MAKELPARAM(pt.x, pt.y));
		::PostMessage(pHwndExcel, WM_LBUTTONUP, 0, MAKELPARAM(pt.x, pt.y));


		for (int i = 0;; i++)
		{
			if (m_ExcelShapes->GetCount() == ShapesCount)
			{
				break;
			}

			if (i == 25)
			{
				throw (FALSE);
			}

			Sleep(20);
		}

		MSExcel::ShapePtr pExcelShape = m_ExcelShapes->Item(CComVariant(ShapesCount));


		float Left = (float)pExcelShape->GetLeft();
		float Top = (float)pExcelShape->GetTop();

		//		float w = pExcelShape->GetWidth();
		//		float h = pExcelShape->GetHeight();


		float ExcelShowPercentage = GetExcelShowPercentage();
		float Width = (float)(InputRect.width() / ExcelShowPercentage * fPixToPoints);
		float Height = (float)(InputRect.height() / ExcelShowPercentage * fPixToPoints);
		//        float Width = (float)(InputRect.width()*w / 5.0 / ExcelShowPercentage * 3 / 4);
		//        float Height = (float)(InputRect.height()*h / 5.0 / ExcelShowPercentage * 3 / 4);


		//        float Width = 5.0*w ;
		//        float Height = 5.0*h;


		BSTR bsname = SysAllocString((OLECHAR*)strFilename.data());
		m_ExcelShape = m_ExcelShapes->AddPicture(_bstr_t(bsname), msoFalse, msoTrue, Left, Top, Width, Height);
		pExcelShape->Delete();



		ExcelUndoClear();
		DisConnectExcel();
		m_OfficeCmdBars = NULL;
		m_OfficeCmdBar = NULL;
		m_OfficeCmdBarControls = NULL;
		m_OfficeCmdBarControl = NULL;
		m_ExcelWorksheet = NULL;
		m_ExcelShapes = NULL;
		m_ExcelShape = NULL;

		//       m_pProxyMaskWnd->ShowWindow( SW_HIDE );
		//        ::SetWindowPos( m_hProxyWnd, NULL, 0, 0, 0, 0,
		//            SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_SHOWWINDOW );

	}

	catch (...)
	{
		try
		{
			ExcelUndoClear();
			DisConnectExcel();

			//            m_pProxyMaskWnd->ShowWindow( SW_HIDE );
			//            ::SetWindowPos( m_hProxyWnd, NULL, 0, 0, 0, 0,
			//                SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_SHOWWINDOW );


			m_OfficeCmdBars = NULL;
			m_OfficeCmdBar = NULL;
			m_OfficeCmdBarControls = NULL;
			m_OfficeCmdBarControl = NULL;
			m_ExcelWorksheet = NULL;
			m_ExcelShapes = NULL;
			m_ExcelShape = NULL;
		}

		catch (...)
		{
			DisConnectExcel();

			//             m_pProxyMaskWnd->ShowWindow( SW_HIDE );
			//            ::SetWindowPos( m_hProxyWnd, NULL, 0, 0, 0, 0,
			//                SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_SHOWWINDOW );

			m_OfficeCmdBars = NULL;
			m_OfficeCmdBar = NULL;
			m_OfficeCmdBarControls = NULL;
			m_OfficeCmdBarControl = NULL;
			m_ExcelWorksheet = NULL;
			m_ExcelShapes = NULL;
			m_ExcelShape = NULL;
		}
		return FALSE;
	}
	return TRUE;
}


BOOL HHOfficeDoc::ConnectWord()
{
    if ( NULL != m_WordApp )
        return TRUE;

    CLSID clsid;
    CLSIDFromProgID(L"Word.Application", &clsid);
    try
    {
        IUnknown *pUnk;
        HRESULT hr = GetActiveObject(clsid, NULL, (IUnknown**)&pUnk);

        if (hr == S_OK)
        {
            IDispatch *pDisp;
            hr = pUnk->QueryInterface(IID_IDispatch, (void **)&pDisp);
            pUnk->Release();

            CComQIPtr<MSWord::_Application> Application(pDisp);
            ATLASSERT(Application);
            m_WordApp = NULL;
            Application->QueryInterface( __uuidof(MSWord::_Application), (void**)&m_WordApp );
            ATLASSERT(m_WordApp);
            if ( NULL == m_WordApp )
                return FALSE;

            pDisp->Release();
            TCHAR * stopstring;
            m_WordVersion = _tcstod( m_WordApp->GetVersion(), &stopstring );

            return TRUE;
        }
    }
    catch(...)
    {
        return FALSE;
    }

    if( !m_WordApp )
        return FALSE;
    else
        return TRUE;
}

BOOL HHOfficeDoc::DisConnectWord()
{
    try
    {
        if ( NULL != m_WordApp )
        {
            m_WordApp.Release();
            m_WordApp = NULL;
        }
    }
    catch(...)
    {
        return FALSE;
    }
    return TRUE;
}

void HHOfficeDoc::AdjustWordOptions(BOOL bRestore)
{
    static VARIANT_BOOL s_bAutoCreateNewDrawings = FALSE;
    static BOOL s_bSnapToGrid = FALSE;
    static MSWord::WdWrapTypeMerged s_PictureWrapType = MSWord::WdWrapTypeMerged::wdWrapMergeFront;

    try
    {
        m_WordDocument = m_WordApp->GetActiveDocument();
        m_WordOptions = m_WordApp->GetOptions();

        if (bRestore)
        {
            if (s_bSnapToGrid)
            {
                m_WordDocument->put_SnapToGrid( VARIANT_TRUE );
                s_bSnapToGrid = FALSE;
            }

            if (m_WordVersion > 9.0 && m_WordVersion != 15)
            {
                if (s_bAutoCreateNewDrawings)
                {
                    m_WordOptions->put_AutoCreateNewDrawings( VARIANT_TRUE );
                    s_bAutoCreateNewDrawings = FALSE;
                }

                if (s_PictureWrapType != 4)
                {
                    m_WordOptions->put_PictureWrapType( s_PictureWrapType );
                    s_PictureWrapType = MSWord::WdWrapTypeMerged::wdWrapMergeFront;
                }
            }
        }
        else
        {
            s_bSnapToGrid = m_WordDocument->GetSnapToGrid();

            if (s_bSnapToGrid)
            {
                m_WordDocument->put_SnapToGrid( VARIANT_FALSE );
            }

            if (m_WordVersion > 9.0 && m_WordVersion != 15)
            {
                m_WordOptions->get_AutoCreateNewDrawings( &s_bAutoCreateNewDrawings );
                if (s_bAutoCreateNewDrawings)
                {
                    m_WordOptions->put_AutoCreateNewDrawings( VARIANT_FALSE );
                }

                m_WordOptions->get_PictureWrapType( &s_PictureWrapType );

                if (s_PictureWrapType != 4)
                {
                    m_WordOptions->put_PictureWrapType( MSWord::WdWrapTypeMerged::wdWrapMergeFront );
                }
            }
        }
    }

    catch(...)
    {
        s_bAutoCreateNewDrawings = FALSE;
        s_bSnapToGrid = FALSE;
        s_PictureWrapType = MSWord::WdWrapTypeMerged::wdWrapMergeFront;
    }
}

BOOL HHOfficeDoc::InsertWord(const QString& strFilename, const QRect& InputRect, HWND pHwndWord)
{
    HRESULT hr(E_FAIL);

	float fScalePix = 1.0;
	float fPixToPoints = 0.75;
	try
	{
		SetProcessDPIAware();
		HDC hdcScreen = ::GetDC(NULL);
		float fScreenWidth = ::GetDeviceCaps(hdcScreen, LOGPIXELSX);
		float fScreenWidth1 = ::GetDeviceCaps(hdcScreen, LOGPIXELSY);
		float& fScale = fScalePix;
		fScale = fScreenWidth / 96.0;
		if (fScale - 2.0 > -1e-4)
		{
			fScale = 2.0;
		}
		else
		{
			fScale = 1.0;
		}

		QRect tempRect = InputRect;
		tempRect.setLeft(InputRect.left() * fScale);
		tempRect.setTop(InputRect.top() * fScale);
		tempRect.setRight(InputRect.right() * fScale);
		tempRect.setBottom(InputRect.bottom() * fScale);

		const_cast<QRect&>(InputRect) = tempRect;

		fPixToPoints = 72.0 / fScreenWidth;
	}
	catch (...)
	{
		return FALSE;
	}


    QPoint ptShapeTopLeft = InputRect.topLeft();
    QPoint ptShapeCenterPoint = InputRect.center();
	QPoint ptBottomRight = InputRect.bottomRight();
    POINT pttl,ptbr,pt;

	float rectw = InputRect.width();
	float recth = InputRect.height();


	//顶点
    pttl.x = ptShapeTopLeft.rx();
    pttl.y = ptShapeTopLeft.ry();
	//右下角点
	ptbr.x = ptBottomRight.rx();
	ptbr.y = ptBottomRight.ry();

    pt.x = ptShapeCenterPoint.rx();
    pt.y = ptShapeCenterPoint.ry();

    if (pHwndWord == NULL)
    {
        pHwndWord = ::WindowFromPoint(pt);
        if (pHwndWord == NULL)
            return FALSE;
    }

    if (!ConnectWord())
        return FALSE;


    try
    {
        //
        m_WordWindow = m_WordApp->GetActiveWindow();
        m_WordView = m_WordWindow->GetView();

		if (m_WordVersion >= 15)
		{   
			POINT ptn;
			ptn.x = ptShapeCenterPoint.rx();
			ptn.y = ptShapeCenterPoint.ry();
			::ScreenToClient(pHwndWord, &ptn);
			PostMessage(pHwndWord, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(ptn.x, ptn.y));
			PostMessage(pHwndWord, WM_MOUSEMOVE, 0, MAKELPARAM(ptn.x, ptn.y));
			PostMessage(pHwndWord, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(ptn.x, ptn.y));

			m_WordDocument = m_WordApp->GetActiveDocument();
			if (m_WordDocument)
			{
				m_WordDocument = m_WordApp->GetActiveDocument();
				m_WordShapes = m_WordDocument->GetShapes();
				m_WordWindow = m_WordDocument->ActiveWindow;
				m_WordView = m_WordWindow->GetView();

				int nPageCount = m_WordDocument->ActiveWindow->ActivePane->Pages->GetCount();
				MSWord::SelectionPtr pSelection = m_WordApp->GetSelection();
				if (pSelection)
				{
					CComPtr <MSWord::Range> pr = m_WordApp->Selection->Range;
					pr->SetRange(-1, -1);

					VARIANT vCurrentPageNumber;
					pSelection->get_Information(MSWord::WdInformation::wdActiveEndPageNumber, &vCurrentPageNumber);
					if (true  || vCurrentPageNumber.intVal <  nPageCount)
					{
						CComVariant vWhat(MSWord::wdGoToPage);
						CComVariant vWhich(MSWord::wdGoToAbsolute);

						MSWord::RangePtr pRange = m_WordDocument->GoTo(&vWhat, &vWhich, &vCurrentPageNumber);

						CComVariant vLoacalTrue((short)TRUE);
						CComVariant vLoacalFalse((short)FALSE);
						CComVariant vLoacalLeft(0);
						CComVariant vLoacalTop(0);
						CComVariant vLoacalWidth(10);
						CComVariant vLoacalHeight(10);

						VARIANT vr;
						vr.vt = VT_DISPATCH;
						vr.pdispVal = pRange;

						BSTR bsname = SysAllocString((OLECHAR*)strFilename.data());
						m_WordShapes = m_WordDocument->GetShapes();
						MSWord::ShapePtr WordShape = m_WordShapes->AddPicture(bsname, &vLoacalFalse, &vLoacalTrue,
							&vLoacalLeft, &vLoacalTop, &vLoacalWidth, &vLoacalHeight, &vr);

						qDebug() << "vCurrentpageNumber = " << vCurrentPageNumber.intVal;
						MSWord::ZoomPtr pWordZoom = m_WordView->GetZoom();
						float WordShowPercentage = (float)pWordZoom->GetPercentage();

						long fLeft = 0;
						long fTop = 0;
						float fWidth = 0;
						float fHeight = 0;

						m_WordWindow->GetPoint(&fLeft, &fTop, (long*)&fWidth, (long*)&fHeight, WordShape);
						WordShape->Delete();

						fWidth = InputRect.width()*fPixToPoints * 100 / WordShowPercentage;
						fHeight = InputRect.height()*fPixToPoints * 100 / WordShowPercentage;
						float fMoveX = ((float)InputRect.left() - (float)fLeft) * fPixToPoints * 100 / WordShowPercentage;
						float fMoveY = ((float)InputRect.top() - (float)fTop) * fPixToPoints * 100 / WordShowPercentage;

						CComVariant vTrue((short)TRUE);
						CComVariant vFalse((short)FALSE);
						CComVariant vLeft(fMoveX);
						CComVariant vTop(fMoveY);

						CComVariant vWidth(fWidth);
						CComVariant vHeight(fHeight);

						m_WordShape = m_WordShapes->AddPicture(bsname, &vFalse, &vTrue,
							&vLeft, &vTop, &vWidth, &vHeight, &vr);

						DisConnectWord();
						return TRUE;
					}
				}
			}
		}


        AdjustWordOptions();
        m_WordPane = m_WordWindow->GetActivePane();
        long VerticalPercent = m_WordPane->GetVerticalPercentScrolled();
        long HorizontalPercent = m_WordPane->GetHorizontalPercentScrolled();

        m_OfficeCmdBars = m_WordApp->GetCommandBars();
        m_OfficeCmdBar = m_OfficeCmdBars->GetItem(CComVariant(_T("Lines")));
        m_OfficeCmdBarControls = m_OfficeCmdBar->GetControls();
        m_OfficeCmdBarControl = m_OfficeCmdBarControls->GetItem(CComVariant(long(6)));
        m_OfficeCmdBarControl->Execute();


        m_WordDocument = m_WordApp->GetActiveDocument();
        m_WordShapes = m_WordDocument->GetShapes();

        /// 绘制线段
        ::ScreenToClient(pHwndWord,&pttl);
		::ScreenToClient(pHwndWord, &ptbr);
        ::ScreenToClient(pHwndWord,&pt);

		PostMessage(pHwndWord, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pttl.x, pttl.y));

        /// 如果word是2010版本
        if ( m_WordVersion >= 14.0 )
        {
			PostMessage(pHwndWord, WM_MOUSEMOVE, 0, MAKELPARAM(pttl.x + rectw/5.0, pttl.y + recth/5.0));
			PostMessage(pHwndWord, WM_MOUSEMOVE, 0, MAKELPARAM(pttl.x + rectw / 5.0, pttl.y + recth / 5.0));
        }

		PostMessage(pHwndWord, WM_LBUTTONUP, 0, MAKELPARAM(pttl.x + rectw / 5.0, pttl.y + recth / 5.0));

        MSWord::SelectionPtr pSelection = NULL;
        MSWord::InlineShapesPtr pInlineShaps = NULL;
//        MSWord::InlineShapePtr pInlineShap = NULL;
        MSWord::ShapeRangePtr pShapeRange = NULL;

        pSelection = m_WordApp->GetSelection();
        pInlineShaps = pSelection->GetInlineShapes();
        pSelection->get_ShapeRange( &pShapeRange );
        LONG lCount = pShapeRange->GetCount();
        /// 如果当前选中的不是一个Shape
        if( 1 != lCount )
            throw ( FALSE );

        //
        m_WordShape = NULL;
        m_WordShape = pShapeRange->Item( &CComVariant(1) );

        //
        if ( m_WordVersion >= 14.0 && m_WordVersion != 15)
        {
            /// 在第一页插入图片,位置偏移
            VARIANT vCurrentPageNumber;
            m_WordApp->GetSelection()->get_Information( MSWord::WdInformation::wdActiveEndPageNumber, &vCurrentPageNumber);
            /// 得到当前的页码
            int nPageNumber = vCurrentPageNumber.intVal;

            /// 通过该后缀名判断文件是否是07或者10
            BSTR bFileName;
            m_WordDocument->get_Name( &bFileName );
            QString strName( (QChar*)bFileName );
            QString strExt = ""; //CHHHelperFunction::GetFileExtNameFromWholeString( strName );
            /// 指定相对位置
            if( strExt != "doc" && 1 == nPageNumber )
                m_WordShape->put_RelativeVerticalPosition( MSWord::WdRelativeVerticalPosition::wdRelativeVerticalPositionMargin );
        }

        //
        float Left = (float)m_WordShape->GetLeft();
        float Top = (float)m_WordShape->GetTop();
		//奇怪，下面获取到的w，h为0.？？？？微软bug?
		float w = m_WordShape->GetWidth();
		float h = m_WordShape->GetHeight();

        //float WordShowPercentage = GetWordShowPercentage();

        //
        MSWord::ZoomPtr pWordZoom = m_WordView->GetZoom();
        float WordShowPercentage = (float)pWordZoom->GetPercentage()/(float)100;

        //换一种方法计算宽，高
		//float Width = ((float)InputRect.width()) / WordShowPercentage*15/23;
		//float Height = ((float)InputRect.height()) / WordShowPercentage * 15/23;
		float Width = 5 * w;
		float Height = 5 * h;

        CComPtr <MSWord::Range> pr = m_WordApp->Selection->Range;
        VARIANT vr;
        vr.vt = VT_DISPATCH;
        vr.pdispVal = pr;

        m_WordShape->Delete();

        m_WordShape = NULL;
        CComVariant vTrue((short)TRUE);
        CComVariant vFalse((short)FALSE);
        CComVariant vLeft(Left);
        CComVariant vTop(Top);
       // CComVariant vWidth(m_WordApp->PixelsToPoints(Width,&vFalse));
       // CComVariant vHeight(m_WordApp->PixelsToPoints(Height,&vTrue));
		 CComVariant vWidth(Width);
         CComVariant vHeight(Height);
        /// 添加图片
        BSTR bsname =  SysAllocString((OLECHAR*)strFilename.data());
        m_WordShape = m_WordShapes->AddPicture(bsname,&vFalse,&vTrue,
            &vLeft,&vTop,&vWidth,&vHeight, &vr );

        if (m_WordVersion < 10.0)
        {
            m_WordWrapFormat = m_WordShape->GetWrapFormat();
            m_WordWrapFormat->put_Type( MSWord::WdWrapType::wdWrapNone );
            m_WordShape->put_Left(Left);
            m_WordShape->put_Top(Top);
        }

        m_WordDocument->UndoClear();
        AdjustWordOptions(TRUE);
        if(VerticalPercent != 0 )
            m_WordPane->put_VerticalPercentScrolled(VerticalPercent);
        if(HorizontalPercent != 0 )
            m_WordPane->put_HorizontalPercentScrolled(HorizontalPercent);
    }

    catch(...)
    {
        return FALSE;
    }

    DisConnectWord();
    return TRUE;
}



BOOL CALLBACK HHOfficeDoc::GetAnyDesktopWindow(HWND hwnd, LPARAM lParam)
{
    *(HWND*)lParam = hwnd;
    return FALSE;
}

OFFICETYPE HHOfficeDoc::WhichOffice( HWND& pWndOffice )
{
    TCHAR szClassName[255];
    OFFICETYPE ret = NONOFFICE;

    HWND pWnd = NULL;
    EnumWindows(GetAnyDesktopWindow,(LPARAM)&pWnd);
    if (pWnd == NULL)
    {
        return ret;
    }

    HWND pWndTemp = ::GetWindow( pWnd, GW_HWNDFIRST );
    if (pWndTemp)
    {
        pWnd = pWndTemp;
    }

    while(pWnd)
    {
        if ( ::IsWindowVisible( pWnd ) )
        {
            ::GetClassName(pWnd,szClassName,254);
            if(_tcscmp(szClassName, _T("OpusApp")) == 0)
            {
                pWndOffice && (pWndOffice = pWnd);
                ret = ISMSWORD;
                break;
            }

            if (_tcscmp(szClassName, _T("screenClass"))    == 0 ||//PPT playing!
                _tcscmp(szClassName, _T("PP11FrameClass")) == 0 ||
                _tcscmp(szClassName, _T("PP10FrameClass")) == 0 ||
                _tcscmp(szClassName, _T("PP9FrameClass"))  == 0)
            {
                pWndOffice && (pWndOffice = pWnd);
                ret = ISMSPPT;
                break;
            }

            if(_tcscmp(szClassName, _T("XLMAIN")) == 0)
            {
                pWndOffice && (pWndOffice = pWnd);
                ret = ISMSEXCEL;
                break;
            }
        }
        pWnd = ::GetNextWindow( pWnd, GW_HWNDNEXT );
    }
    return ret;
}

BOOL HHOfficeDoc::InsertPptLast( const QString & strFilename, const int & index, QRect& InputRect)
{
    if (index == -1)
        return FALSE;

    if (m_hPPTShowWndHWnd==NULL)
        return FALSE;


    HRESULT hRet( E_FAIL );
    if ( NULL == m_PptApplication )
    {

        hRet = m_PptApplication.CoCreateInstance( __uuidof(MSPPT::Application), NULL, CLSCTX_SERVER );
        if( FAILED(hRet) || NULL == m_PptApplication )
        {

            if (m_PptApplication)
            {
                m_PptApplication.Release();
                m_PptApplication = NULL;
            }
            return FALSE;
        }
    }

    BOOL bSlideShowMode = TRUE;
    long ShowPosition = -1;
    float PptShowPercentage = 0;
    float Left = 0,Top = 0,Width = 0,Height = 0;

    m_PptPresentation = NULL;
    m_PptSlideShowWindow = NULL;
    m_PptSlideShowSettings = NULL;
    m_PptSlideshowView = NULL;
    m_PptSlides = NULL;
    m_PptSlide = NULL;
    m_PptShapes = NULL;
    m_PptShape = NULL;
    try
    {
        m_PptPresentation = m_PptApplication->GetActivePresentation();
        m_PptSlideShowWindow = m_PptPresentation->GetSlideShowWindow();

        m_PptSlideshowView = m_PptSlideShowWindow->GetView();
        ShowPosition = index;

        PptShowPercentage = (float)m_PptSlideshowView->GetZoom()/100.0;

        m_PptMaster = m_PptPresentation->GetSlideMaster();
        float MasterWidth = m_PptMaster->GetWidth();
        float MasterHeight = m_PptMaster->GetHeight();
        float SlideWidth = (float)(MasterWidth*PptShowPercentage*4/3);
        float SlideHeight = (float)(MasterHeight*PptShowPercentage*4/3);
        QRect rcSlideShow;

        ::GetWindowRect( m_hPPTShowWndHWnd,(LPRECT) (&rcSlideShow) );

        float offsetx =	(float)((rcSlideShow.width() - SlideWidth)/2);
        float offsety = (float)((rcSlideShow.height() - SlideHeight)/2);
        float SlideLeft = (float)rcSlideShow.left() + offsetx;
        float SlideTop = (float)rcSlideShow.top() + offsety;

        Left = (float)((InputRect.left() - SlideLeft)/PptShowPercentage*3/4);
        Top  = (float)((InputRect.top()  - SlideTop)/PptShowPercentage*3/4);
        Width = (float)(InputRect.width()/PptShowPercentage*3/4);
        Height = (float)(InputRect.height()/PptShowPercentage*3/4);

        m_PptSlides = m_PptPresentation->GetSlides();

        m_PptSlide = m_PptSlides->Item(CComVariant(ShowPosition));
        m_PptShapes = m_PptSlide->GetShapes();


        BSTR bsname = SysAllocString( (OLECHAR*)strFilename.data());
        if (m_PptVersion >= 14)
        {
            MSPPT::ShapePtr	PptShape = m_PptShapes->AddPicture(_bstr_t(bsname),msoFalse,msoTrue,Left,Top,Width,Height);
            MSPPT::ShapePtr	PptShape1 = m_PptShapes->AddPicture(_bstr_t(bsname),msoFalse,msoTrue,Left,Top,Width,Height);
            m_PptShape = m_PptShapes->AddPicture(_bstr_t(bsname),msoFalse,msoTrue,Left,Top,Width,Height);
            PptShape1->Delete();
            PptShape1 = NULL;
            PptShape->Delete();
            PptShape= NULL;
        }
        else
        {
            m_PptShape = m_PptShapes->AddPicture(_bstr_t(bsname),msoFalse,msoTrue,Left,Top,Width,Height);
        }

    }
    catch(...)
    {
        int i=0;
    }
    m_PptPresentation = NULL;
    m_PptSlideShowWindow = NULL;
    m_PptSlideShowSettings = NULL;
    m_PptSlideshowView = NULL;
    m_PptSlides = NULL;
    m_PptSlide = NULL;
    m_PptShapes = NULL;
    m_PptShape = NULL;
    m_PptApplication.Release();
    m_PptApplication = NULL;
    return TRUE;

}

float HHOfficeDoc::GetPptShowPercentage(BOOL bSlideShowMode)
{
    HRESULT hRet( E_FAIL );
    if ( NULL == m_PptApplication )
    {
        hRet = m_PptApplication.CoCreateInstance( __uuidof(MSPPT::Application), NULL, CLSCTX_SERVER );
        if( FAILED(hRet) || NULL == m_PptApplication )
        {
            if (m_PptApplication)
            {
                m_PptApplication.Release();
                m_PptApplication = NULL;
            }

            return 0.0f;
        }
    }

    float Zoom;
    try
    {
        if (bSlideShowMode)
        {
            m_PptPresentation = m_PptApplication->GetActivePresentation();
            m_PptSlideShowWindow = m_PptPresentation->GetSlideShowWindow();
            m_PptSlideshowView = m_PptSlideShowWindow->GetView();
            Zoom = (float)m_PptSlideshowView->GetZoom();
        }
        else
        {
            m_PptDocumentWindow = m_PptApplication->GetActiveWindow();
            m_PptView = m_PptDocumentWindow->GetView();
            Zoom = (float)m_PptView->GetZoom();
        }
        return Zoom/(float)100;
    }
    catch(...)
    {
        m_PptPresentation = NULL;
        m_PptSlideShowWindow = NULL;
        m_PptDocumentWindow = NULL;
        m_PptSlideshowView = NULL;
        m_PptView = NULL;
        m_PptApplication.Release();
        m_PptApplication = NULL;

        return 0.0f;
    }
    m_PptPresentation = NULL;
    m_PptSlideShowWindow = NULL;
    m_PptDocumentWindow = NULL;
    m_PptSlideshowView = NULL;
    m_PptView = NULL;
    m_PptApplication.Release();
    m_PptApplication = NULL;
}
void HHOfficeDoc::SetPPTPageIndexBrforeChange()
{
    HRESULT hRet( E_FAIL );
    if ( NULL == m_PptApplication )
    {
        hRet = m_PptApplication.CoCreateInstance( __uuidof(MSPPT::Application), NULL, CLSCTX_SERVER );
        if( FAILED(hRet) || m_PptApplication == NULL )
        {
            if (m_PptApplication)
            {
                m_PptApplication.Release();
                m_PptApplication = NULL;
            }
            return;
        }
    }
    try
    {
        m_PptPresentation = m_PptApplication->GetActivePresentation();
        m_PptSlideShowWindow = m_PptPresentation->GetSlideShowWindow();
        m_PptSlideshowView = m_PptSlideShowWindow->GetView();

        GetCurPptIndex(m_PptSlideshowView,m_iPPTBeforeChangePageIndex);
    }
    catch( ... )
    {
        m_PptPresentation = NULL;
        m_PptSlideShowWindow = NULL;
        m_PptSlideshowView = NULL;
        m_PptApplication.Release();
        m_PptApplication = NULL;
        hRet = E_FAIL;
    }
    m_PptPresentation = NULL;
    m_PptSlideShowWindow = NULL;
    m_PptSlideshowView = NULL;
    m_PptApplication.Release();
    m_PptApplication = NULL;

}



// PPT页面转化时设置相关数据  // 1 -- previous 2 -- next
void HHOfficeDoc::SetAfterPPTPreAndNext( int iChangeType )
{
    if ( m_iPPTBeforeChangePageIndex != m_iPPTCurrentPageIndex )
    {
        DWORD64 tempSlideNetID = CheckPageIndexIsExisted( m_iPPTCurrentPageIndex );
        if ( tempSlideNetID )
        {

            int TargetPos = -1;

        }
        else
        {
            //CHHHelperFunction::GetAppDatePath(_T("Temp"));
            //CString strImageFileName = g_Presentation->m_strAppTempPath;
            //strImageFileName = strImageFileName + _T("PPT_") + CHHHelperFunction::DWORD64ToString(CHHHelperFunction::GetNetUniqueID()) + _T(".") + _T("_EMBED.jpg");//_T("_EMBED.png");

        }
    }
}

DWORD64 HHOfficeDoc::CheckPageIndexIsExisted( int PPTPageIndex )
{
    return 0;
}


// SetPPTShowPageByIndex 根据index，将PPT定位到该页
void HHOfficeDoc::SetPPTShowPageByIndex( int index )
{
    /// 判断是否需要定位到指定的PPT页面
    if ( m_iPPTCurrentPageIndex == index )
        return;/// 如果通过上下翻页已经将PPT翻到了该页，则不做PPTgoto操作

    HRESULT hRet( E_FAIL );
    if ( NULL == m_PptApplication )
    {
        //CoInitialize( NULL );
        hRet = m_PptApplication.CoCreateInstance( __uuidof(MSPPT::Application), NULL, CLSCTX_SERVER );
        if( FAILED(hRet) || m_PptApplication == NULL )
        {
            //::CoUninitialize();
            if (m_PptApplication)
            {
                m_PptApplication.Release();
                m_PptApplication = NULL;
            }

            return;
        }
    }
    try
    {
        m_PptPresentation = m_PptApplication->GetActivePresentation();
        m_PptSlideShowWindow = m_PptPresentation->GetSlideShowWindow();
        m_PptSlideshowView = m_PptSlideShowWindow->GetView();
        m_PptSlideshowView->GotoSlide( index, msoFalse );
        GetCurPptIndex(m_PptSlideshowView,m_iPPTCurrentPageIndex);
    }
    catch(...)
    {
    }
    m_PptSlideshowView = NULL;
    m_PptSlideShowWindow = NULL;
    m_PptPresentation = NULL;
    m_PptApplication.Release();
    m_PptApplication = NULL;
}

void HHOfficeDoc::GetCurPptIndex(MSPPT::SlideShowViewPtr	pPptSlideshowView,int& index)
{
    index=-1;
    if(pPptSlideshowView)
    {
        index = pPptSlideshowView->GetCurrentShowPosition();

        if(index>0)			return;


        index = pPptSlideshowView->GetCurrentShowPosition();
    }
}
BOOL  HHOfficeDoc::InsertPpt(const QString& strFilename,const QRect& InputRect, HWND pHwndPpt )
{
    return Insertnormalppt( strFilename, InputRect, pHwndPpt );
    //add by wxb,2014/1/24
//    if (!m_hPPTShowWndHWnd)
//        return Insertnormalppt(strFilename,InputRect,pHwndPpt);
//    //end
//    else
//    {
//        HRESULT hRet( E_FAIL );
//        if ( NULL == m_PptApplication )
//        {
//            //CoInitialize( NULL );
//            hRet = m_PptApplication.CoCreateInstance( __uuidof(MSPPT::Application), NULL, CLSCTX_SERVER );
//            if( FAILED(hRet) || NULL == m_PptApplication )
//            {
//                //::CoUninitialize();
//                if (m_PptApplication)
//                {
//                    m_PptApplication.Release();
//                    m_PptApplication = NULL;
//                }
//                return FALSE;
//            }
//        }
//        try{
//            m_PptPresentation = m_PptApplication->GetActivePresentation();
//            m_PptSlideShowWindow = m_PptPresentation->GetSlideShowWindow();
//            m_PptSlideshowView = m_PptSlideShowWindow->GetView();
//            int index = m_PptSlideshowView->GetCurrentShowPosition();

//            QRect rect = InputRect;

//            return InsertPptLast(strFilename,index,rect);
//        }
//        catch(...)
//        {
//            if (m_PptApplication)
//            {
//                m_PptApplication.Release();
//                m_PptApplication = NULL;
//            }
//            return FALSE;
//        }
//    }
}
BOOL HHOfficeDoc::Insertnormalppt(const QString& strFilename,const QRect& InputRect, HWND pHwndPpt )
{
	//	HRESULT hr(E_FAIL);
	//	QPoint ptShapeTopLeft = InputRect.topLeft();
	//	QPoint ptShapeCenterPoint = InputRect.center();

	//	SetCursorPos(ptShapeCenterPoint.rx(), ptShapeCenterPoint.ry());  // 这里是屏幕坐标
	//	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	//	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	//	Sleep(20);

	//    if (!connectPPT())
	//	{
	//        qDebug()<<"ConnectPPt Failed!";
	//		if (m_PptApplication)
	//		{
	//			m_PptApplication.Release();
	//			m_PptApplication = NULL;
	//		}
	//		return FALSE;
	//	}
	//    qDebug()<<"ConnectPPT Success!";

	//	try
	//	{
	//		m_PptDocumentWindow = m_PptApplication->GetActiveWindow();

	//        qDebug()<<"HHOfficeDoc::Insertnormalppt-----m_PptDocumentWindow";
	//		float Left = m_PptDocumentWindow->PointsToScreenPixelsX(0.0);
	//		float Top = m_PptDocumentWindow->PointsToScreenPixelsY(0.0);
	//		m_PptView = m_PptDocumentWindow->GetView();
	//        qDebug()<<"HHOfficeDoc::Insertnormalppt-----m_PptView";
	//		m_PptSlide = m_PptView->GetSlide();
	//        qDebug()<<"HHOfficeDoc::Insertnormalppt-----m_PptSldie";
	//		m_PptShapes = m_PptSlide->GetShapes();
	//        qDebug()<<"HHOfficeDoc::Insertnormalppt-----m_pptShapes";

	//		float PptShowPercentage = (float)m_PptView->GetZoom() / 100.0;

	//		BSTR bsname = SysAllocString((OLECHAR*)strFilename.data());

	//		float fLeft = Left - 15;
	//		float fTop = Top - 15;

	//        Left = (float)((InputRect.left() - Left) / PptShowPercentage * 3 / 4 );
	//        Top = (float)((InputRect.top() - Top) / PptShowPercentage * 3 / 4 );

	//        float Width = (float)(InputRect.width() / PptShowPercentage * 3 / 4);
	//        float Height = (float)(InputRect.height() / PptShowPercentage * 3 / 4);

	//		MSPPT::ShapePtr	PptShape = m_PptShapes->AddPicture(_bstr_t(bsname), msoFalse, msoTrue, Left, Top, Width, Height);
	//		m_PptShape = m_PptShapes->AddPicture(_bstr_t(bsname), msoFalse, msoTrue, Left, Top, Width, Height);
	//		PptShape->Delete();

	//	}
	//	catch (...)
	//	{
	//		return FALSE;
	//	}
	//	return TRUE;
	float fScalePix = 1.0;
	float fPixToPoints = 0.75;
	try
	{
		SetProcessDPIAware();
		HDC hdcScreen = ::GetDC(NULL);
		float fScreenWidth = ::GetDeviceCaps(hdcScreen, LOGPIXELSX);
		float& fScale = fScalePix;
		fScale = fScreenWidth / 96.0;
		if (fScale - 2.0 > -1e-4)
		{
			fScale = 2.0;
		}
		else
		{
			fScale = 1.0;
		}

		QRect tempRect = InputRect;
		tempRect.setLeft(InputRect.left() * fScale);
		tempRect.setTop(InputRect.top() * fScale);
		tempRect.setRight(InputRect.right() * fScale);
		tempRect.setBottom(InputRect.bottom() * fScale);

		const_cast<QRect&>(InputRect) = tempRect;

		fPixToPoints = 72.0 / fScreenWidth;
	}
	catch (...)
	{
		return FALSE;
	}
	if (!connectPPTApp())
		return FALSE;

	//    QAxObject *window = axPptApp->querySubObject("ActiveWindow");
	//    if( !window )
	//        return FALSE;

	bool bSlideShowMode = true;
	int  nShowPosition = -1;
	float  fPercent = 0;
	float  fLeft = 0;
	float  fTop = 0;
	float  fWidth = 0;
	float  fHeight = 0;
	int screenX = InputRect.left();
	int screenY = InputRect.top();

	QAxObject *presentation = axPptApp->querySubObject("ActivePresentation");
	if (!presentation)
		return FALSE;
	QAxObject *slideShowWindow = presentation->querySubObject("SlideShowWindow");
	if (slideShowWindow)
	{
		bSlideShowMode = true;
	}
	else
	{
		bSlideShowMode = false;
	}

	if (bSlideShowMode)
	{
		float fScale = fPixToPoints;
		float fInverseScale = 1.0 / fScale;

		fPercent = getPPTShowPercentage(bSlideShowMode);
		QDesktopWidget* desktopWidget = QApplication::desktop();
		QRect screenRect = desktopWidget->screenGeometry();

		QAxObject *master = presentation->querySubObject("SlideMaster");
		float fSlideWidth = (master->property("Width").toFloat())*fPercent / 100 * fInverseScale;
		float fSlideHeight = (master->property("Height").toFloat())*fPercent / 100 * fInverseScale;
		float fSlideLeft = (screenRect.width() * fScalePix - fSlideWidth) / 2;
		float fSlideTop = (screenRect.height() * fScalePix - fSlideHeight) / 2;

		fLeft = ((float)screenX - fSlideLeft)*fScale * 100 / fPercent;
		fTop = ((float)screenY - fSlideTop)*fScale * 100 / fPercent;
		fWidth = InputRect.width()*fScale * 100 / fPercent;
		fHeight = InputRect.height()*fScale * 100 / fPercent;

		QAxObject *view = slideShowWindow->querySubObject("View");
		nShowPosition = view->dynamicCall("CurrentShowPosition(void)").toInt();
		QAxObject *slides = presentation->querySubObject("Slides");
		QAxObject *slide = slides->querySubObject("Item (int)", nShowPosition);
		if (slide)
		{
			QAxObject *shapes = slide->querySubObject("Shapes");
			QVariantList params;
			params.push_back(QVariant(strFilename));
			params.push_back(QVariant(false));
			params.push_back(QVariant(true));
			params.push_back(QVariant(fLeft));
			params.push_back(QVariant(fTop));
			params.push_back(QVariant(fWidth));
			params.push_back(QVariant(fHeight));
			addShapePictureWithSpecialProcess(shapes, params);
		}
	}
	else
	{
		QAxObject *activeWindow = axPptApp->querySubObject("ActiveWindow");
		int nType = activeWindow->property("ViewType").toInt();
		if (nType == 9)
		{
			if (!m_bPPTFocusState)
			{
				m_bPPTFocusState = true;
				activeWindow->setProperty("ViewType", 1);
				activeWindow->setProperty("ViewType", 9);
			}
			fPercent = getPPTShowPercentage(bSlideShowMode);
			QAxObject *master = presentation->querySubObject("SlideMaster");
			int fSlideWidth = (master->property("Width").toInt())*fPercent / 100 * 4 / 3;
			int fSlideHeight = (master->property("Height").toInt())*fPercent / 100 * 4 / 3;
			int fLeft = activeWindow->dynamicCall("PointsToScreenPixelsX(int)", 0).toInt();
			int fTop = activeWindow->dynamicCall("PointsToScreenPixelsY(int)", 0).toInt();

			int fLeft1 = activeWindow->dynamicCall("PointsToScreenPixelsX(int)", 100).toInt() - fLeft;
			float fScale = 1.0 / (float)fLeft1  * fPercent;
			if (screenX > fLeft - 100 && screenX < fLeft + fSlideWidth * fScalePix + 100 && screenY > fTop - 100 && screenY < fTop + fSlideHeight * fScalePix + 100)
			{
				QAxObject *view = activeWindow->querySubObject("View");
				QAxObject *slide = view->querySubObject("Slide");
				QAxObject *shapes = slide->querySubObject("Shapes");
				fLeft = ((float)screenX - fLeft)*fScale * 100 / fPercent + 2;
				fTop = ((float)screenY - fTop)*fScale * 100 / fPercent + 2;
				fWidth = InputRect.width()*fScale * 100 / fPercent;
				fHeight = InputRect.height()*fScale * 100 / fPercent;

				QVariantList params;
				params.push_back(QVariant(strFilename));
				params.push_back(QVariant(false));
				params.push_back(QVariant(true));
				params.push_back(QVariant(fLeft));
				params.push_back(QVariant(fTop));
				params.push_back(QVariant(fWidth));
				params.push_back(QVariant(fHeight));
				addShapePictureWithSpecialProcess(shapes, params);
			}

		}
	}
	disConnectPPTApp();
	return TRUE;
}

// 判断新页是否需要插入在最后
BOOL HHOfficeDoc::PPTIndextIsInMiddle( int nPos, DWORD64& dNetID, DWORD64& dStartNetID )
{
        return FALSE;

}


BOOL HHOfficeDoc::ConnectVisio()
{
    short cmdid=1661;//MSVISIO::VisUICmds.visCmdDrawingTools; 1946,viscmdshapehand 1772, SetAddMarkup,1744,OptionsGotoDrawing,1077,OptionsEditDrawing,1074,InkTool,1661
    if ( NULL != m_VisioApp )
    {
        m_VisioApp->DoCmd(cmdid);
        if (m_hVisioWndHWnd)
            SetForegroundWindow(m_hVisioWndHWnd);

        return TRUE;
    }


    CLSID clsid;
    CLSIDFromProgID(L"Visio.Application", &clsid);
    try
    {
        IUnknown *pUnk;
        HRESULT hr = GetActiveObject(clsid, NULL, (IUnknown**)&pUnk);

        DWORD dr= GetLastError();

        if (hr == S_OK)
        {
            IDispatch *pDisp;
            hr = pUnk->QueryInterface(IID_IDispatch, (void **)&pDisp);
            dr= GetLastError();
            pUnk->Release();

            CComQIPtr<MSVISIO::IVApplication> Application(pDisp);
            ATLASSERT(Application);
            m_VisioApp = NULL;
            Application->QueryInterface( __uuidof(MSVISIO::IVApplication), (void**)&m_VisioApp );
            dr= GetLastError();
            ATLASSERT(m_VisioApp);
            if ( NULL == m_VisioApp )
                return FALSE;

            pDisp->Release();

            m_VisioApp->DoCmd(cmdid);
            if (m_hVisioWndHWnd)
                SetForegroundWindow(m_hVisioWndHWnd);


            return TRUE;
        }
    }
    catch(...)
    {
        return FALSE;
    }

    if( !m_VisioApp )
        return FALSE;
    else
        return TRUE;
}

BOOL HHOfficeDoc::DisConnectVisio()
{
    short cmdid=1219;//MSVISIO::VisUICmds.visCmdDrawingTools; 1102,viscmdshapehand 1772, SetAddMarkup,1744,OptionsGotoDrawing,1077,OptionsEditDrawing,1074,InkTool,1661,EditSelectSpecial,1026,DRPointerTool,1219

    try
    {
        if ( NULL != m_VisioApp )
        {
            m_VisioApp->DoCmd(cmdid);

            m_VisioApp.Release();
            m_VisioApp = NULL;
        }
    }
    catch(...)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL HHOfficeDoc::ConnectPDF()
{
    if(m_pdfAcroApp)
    {
        _bstr_t bstrTool( "Ink" );
        m_pdfAcroApp->SetActiveTool( bstrTool, 1 );
    }
    else
    {
        HRESULT _hr = S_OK;

        CLSID cls;
        CLSIDFromProgID( CComBSTR( "AcroExch.App" ), &cls );
        //CComPtr<XPDF::CAcroApp> pdfAcroApp;
        CoCreateInstance( cls, NULL, CLSCTX_ALL , __uuidof(XPDF::CAcroApp), (void**)&m_pdfAcroApp );
        //_hr = pdfAcroApp->Show();
        _bstr_t bstrTool( "Ink" );
        m_pdfAcroApp->SetActiveTool( bstrTool, 1 );

    }

    return TRUE;
}

BOOL HHOfficeDoc::DisConnectPDF()
{

    if (m_pdfAcroApp)
    {
        _bstr_t bstrTool( "Hand" );
        m_pdfAcroApp->SetActiveTool( bstrTool, 1 );
        return TRUE;
    }
    return FALSE;

    return TRUE;
}

BOOL HHOfficeDoc::InsertOffice( const QString& strFilename,const QRect& InputRect )
{
    BOOL bRet = FALSE;
    HWND pHndOffice;
    POINT pt;
    pt.x =InputRect.center().rx();
    pt.y = InputRect.center().ry();

    pHndOffice = ::WindowFromPoint( pt );
    if (pHndOffice == NULL)
    {
        return bRet;
    }

    /// 得到窗口的名称
    TCHAR szClassName[255];
    ::GetClassName(pHndOffice,szClassName,254);
    QString strWhichOffice((QChar*)szClassName);

	if (_tcscmp(szClassName, _T("_WwG")) == 0 )//"word";
    {

        bRet = InsertWord(strFilename,InputRect,pHndOffice);
    }
	else if (_tcscmp(szClassName, _T("paneClassDC")) == 0 || _tcscmp(szClassName, _T("mdiClass")) == 0 || _tcscmp(szClassName, _T("screenClass")) == 0)
    {
        bRet = InsertPpt(strFilename,InputRect,pHndOffice);
    }
	else if (_tcscmp(szClassName, _T("EXCEL7")) == 0 )//"excel";
    {
        bRet = InsertExcel(strFilename,InputRect,pHndOffice);
    }
    /// 嵌入
	else if (_tcscmp(szClassName, _T("VISIOG")) == 0)//"visio";
    {
        //bRet = Insertvisio(strFilename,InputRect, pHndOffice);
    }

    return bRet;
}


BOOL HHOfficeDoc::InsertOfficeEx(const QString& strFilename,const QRect& InputRect)
{
    HWND pHndOffice;
    POINT pt;
    pt.x = InputRect.center().rx();
    pt.y = InputRect.center().ry();
    //POINT pt=InputRect.TopLeft();
    //POINT pt=InputRect.BottomRight();

    pt.x+=12;

    pHndOffice = ::WindowFromPoint( pt);//InputRect.CenterPoint() );
    if (pHndOffice == NULL)
    {

        return FALSE;
    }

    //::SendMessage(pHndOffice,WM_COMMAND,WM_KILLFOCUS,0);


    /// 得到窗口的名称
    TCHAR szClassName[255]={0};
    ::GetClassName(pHndOffice,szClassName,254);
    //CString strWhichOffice = szClassName;
    BOOL bRet = FALSE;

    /// 嵌入
    //if (szClassName == _T("_WwG"))//"word";
	if (_tcscmp(szClassName, _T("_WwG")) == 0)
    {

        bRet = InsertWord(strFilename,InputRect, pHndOffice);
    }

	else if (_tcscmp(szClassName, _T("paneClassDC")) == 0 || _tcscmp(szClassName, _T("mdiClass")) == 0 || _tcscmp(szClassName, _T("screenClass")) == 0 )
    {

        bRet = InsertPpt(strFilename,InputRect, pHndOffice );
    }
	else if (_tcscmp(szClassName, _T("EXCEL7")) == 0 )//"excel";
    {

        bRet = InsertExcel(strFilename,InputRect, pHndOffice);
    }
	else if (_tcscmp(szClassName, _T("EXCEL6")) == 0 )//"excel";
    {
        bRet = InsertExcel(strFilename,InputRect,pHndOffice);
    }
    /// 嵌入
	else if (_tcscmp(szClassName, _T("VISIOG")) == 0 )//"visio";
    {
        //bRet = Insertvisio(strFilename,InputRect, pHndOffice);
    }

    else if (WhichOffice( pHndOffice ) != NONOFFICE)
    {


        /// 嵌入
        bRet = InsertOffice(strFilename,InputRect);

        SetWindowPos(pHndOffice, HWND_NOTOPMOST, 0, 0, 0, 0,
            SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOOWNERZORDER);
    }

    return bRet;
}

int HHOfficeDoc::getPPTShowPercentage(bool bSlideShowMode)
{
    int nPercent = 100;
    if(bSlideShowMode)
    {
        QAxObject *activePresentation = axPptApp->querySubObject("ActivePresentation");
        QAxObject *slideShowWindow = activePresentation->querySubObject("SlideShowWindow");
        QAxObject *view = slideShowWindow->querySubObject("View");
        nPercent = view->dynamicCall("Zoom(void)").toInt();
        view->disableMetaObject();
        slideShowWindow->disableMetaObject();
        activePresentation->disableMetaObject();
    }
    else
    {
        QAxObject *activeWindow = axPptApp->querySubObject("ActiveWindow");
        QAxObject *view = activeWindow->querySubObject("View");
        nPercent = view->dynamicCall("Zoom(void)").toInt();
        view->disableMetaObject();
        activeWindow->disableMetaObject();
    }
    return nPercent;
}

//WPS
//QString HHOfficeDoc::isWPSWord( HWND hwnd )
//{
//    TCHAR szCaptionName[ 255 ] = { 0 };
//    ::GetWindowText( hwnd, szCaptionName, 254 );
//    if( _tcsstr( szCaptionName, _T("WPS 文字") ))
//    {
//        m_bIsWPS = true;
//        return "word";
//    }
//    return "";
//}

//QString HHOfficeDoc::isWPSExcel( HWND hwnd )
//{
//    TCHAR szCaptionName[ 255 ] = { 0 };
//    ::GetWindowText( hwnd, szCaptionName, 254 );
//    if( _tcsstr( szCaptionName, _T("WPS 表格") ))
//    {
//        m_bIsWPS = true;
//        return "excel";
//    }
//    return "";
//}

//QString HHOfficeDoc::isWPSPPT( HWND hwnd )
//{
//    TCHAR szCaptionName[ 255 ] = { 0 };
//    ::GetWindowText( hwnd, szCaptionName, 254 );
//    if( _tcsstr( szCaptionName, _T("WPS 演示") ))
//    {
//        m_bIsWPS = true;
//        m_hPPTNormalWndHWnd = hwnd;
//        return "ppt";
//    }
//    return "";
//}

//QString HHOfficeDoc::isWPSPPTPlaying( HWND hwnd )
//{
//    TCHAR szClassName[ 255 ] = { 0 };
//    ::GetClassName( hwnd, szClassName, 254 );
//    if( _tcscmp( szClassName, _T("QWidget") ) == 0 )
//    {
//        HWND next = ::GetNextWindow( hwnd, GW_HWNDNEXT );
//        while( next )
//        {
//            if( isWPSPPT(next).isEmpty() )
//                next = ::GetWindow( next, GW_HWNDNEXT );
//            else
//            {
//                m_bIsWPS = true;
//                m_hPPTShowWndHWnd = hwnd;
//                return "pptplaying";
//            }

//        }
//    }
//    return "";
//}

//bool HHOfficeDoc::connectWPSWord()
//{
//    //"{000209ff-0000-4b30-a977-d214852036ff}"
//    std::vector< HANDLE > vecHandle;
//    PROCESSENTRY32 pro32;
//    HANDLE hProcessSnapShot = ::CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
//    pro32.dwSize = sizeof( PROCESSENTRY32 );
//    if( hProcessSnapShot == INVALID_HANDLE_VALUE )
//        return false;
//    while( ::Process32Next( hProcessSnapShot, &pro32 ) )
//    {
//        if( _tcscmp( pro32.szExeFile, _T("wps.exe") ) == 0 )
//        {
//            vecHandle.push_back( hProcessSnapShot );
//        }
//    }

//    axWPSWord = new QAxObject("kwps.Application");
//    QString uuid = axWPSWord->control() + "&";
//    qDebug()<<uuid<<endl;
//    axWPSWord->setControl(uuid);

//    hProcessSnapShot = ::CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
//    if( hProcessSnapShot == INVALID_HANDLE_VALUE )
//        return false;
//    while( ::Process32Next( hProcessSnapShot, &pro32 ) )
//    {
//        if( _tcscmp( pro32.szExeFile, _T("wps.exe") ) == 0 )
//        {
//            if( vecHandle.size() == 0 )
//            {
//                m_hWPS = hProcessSnapShot;
//                break;
//            }
//            else
//            {
//                std::vector<HANDLE>::iterator it = find( vecHandle.begin(), vecHandle.end(), hProcessSnapShot );
//                if( it == vecHandle.end() )
//                {
//                    m_hWPS = hProcessSnapShot;
//                    break;
//                }
//            }
//        }
//    }
//    return true;
//}

//bool HHOfficeDoc::disConnectWPSWord()
//{
//    ::TerminateProcess( m_hWPS, 0 );
//    axWPSWord->disableMetaObject();
//    axWPSWord->deleteLater();
//    axWPSWord->clear();
//    delete axWPSWord;
//    axWPSWord = NULL;
//    return true;
//}

//BOOL HHOfficeDoc::InsertWPSWord(const QString &strFilename, const QRect &InputRect, HWND pHwndWord)
//{
//    if( axWPSWord == NULL )
//    {
//        if( !connectWPSWord() )
//            return FALSE;
//    }

//    POINT pt;
//    pt.x = InputRect.left();
//    pt.y = InputRect.top();
//    pHwndWord = ::WindowFromPoint( pt );
//    ::PostMessage( pHwndWord, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM( InputRect.left(), InputRect.top()));
//    PostMessage(pHwndWord, WM_MOUSEMOVE, 0, MAKELPARAM( InputRect.left(), InputRect.top()));
//    ::PostMessage( pHwndWord, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM( InputRect.left(), InputRect.top()));

//    float fPercent = getWPSWordShowPercentage();
//    float fLeft = 0;
//    float fTop = 0;
//    float fWidth = (float)InputRect.width()*3/4 * 100/fPercent;
//    float fHeight = (float)InputRect.height()*3/4 * 100/fPercent;

//    QAxObject *documents = axWPSWord->querySubObject("ActiveDocument");

//    if( documents )
//    {
//        QAxObject *selection = axWPSWord->querySubObject("Selection");
//        if( selection )
//        {
//            int nPageNum = selection->dynamicCall("Information(int)",3).toInt();
//            QAxObject *range = documents->querySubObject("GoTo (int,int,int)",1,1,nPageNum);
//            if( range )
//            {
//                QAxObject *activeWindow = documents->querySubObject("ActiveWindow");
//                QVariantList params;
//                params.push_back(fLeft);
//                params.push_back(fTop);
//                params.push_back(fWidth);
//                params.push_back(fHeight);
//                params.push_back(range->asVariant());
//                activeWindow->dynamicCall("GetPoint(int&,int&,int&,int&,QAxBase::asVariant())",params);
//                fLeft = params.value(0).toFloat();
//                fTop = params.value(1).toFloat();
//                qDebug()<<"fLeft = "<<fLeft<<endl;
//                qDebug()<<"fTop = "<<fTop<<endl;
//                QAxObject *view = activeWindow->querySubObject("View");
//                bool displayBound = view->dynamicCall("DisplayPageBoundaries(void)").toBool();
//                float fMoveY;
//                if( !displayBound )
//                {
//                    QAxObject *pageSetup = documents->querySubObject("PageSetup");
//                    float topMarign = pageSetup->property("TopMarign").toFloat();
//                    float bottomMarign = pageSetup->property("BottomMarign").toFloat();
//                    fMoveY = (((float)InputRect.top() - fTop)*3/4 * 100/fPercent) + topMarign + bottomMarign - 6*fPercent/100;
//                }
//                else
//                {
//                    fMoveY = ((float)InputRect.top() - fTop)*3/4 * 100/fPercent;
//                }
//                float fMoveX = ((float)InputRect.left() - fLeft)*3/4 * 100/fPercent;

//                QAxObject *shapes = documents->querySubObject("Shapes");
//                shapes->dynamicCall("AddPicture(QString,bool,bool,float,float,float,float,QAxBase::asVariant())",strFilename,false,true,fMoveX,fMoveY,fWidth,fHeight,range->asVariant());
//            }
//        }
//    }
//    else
//    {
//        ::TerminateProcess( m_hWPS, 0 );
//        axWPSWord = NULL;
//        InsertWPSWord( strFilename, InputRect );

//    }
//    return TRUE;
//}

//int HHOfficeDoc::getWPSWordShowPercentage()
//{
//    int nPercent = 100;
//    QAxObject *documents = axWPSWord->querySubObject("ActiveDocument");
//    if( documents )
//    {
//        QAxObject *activeWindow = documents->querySubObject("ActiveWindow");
//        QAxObject *view = activeWindow->querySubObject("view");
//        QAxObject *zoom = view->querySubObject("Zoom");
//        nPercent = zoom->property("Percentage").toInt();
//        zoom->disableMetaObject();
//        view->disableMetaObject();
//        activeWindow->disableMetaObject();
//        documents->disableMetaObject();
//    }
//    return nPercent;
//}


//bool HHOfficeDoc::connectWPSExcel()
//{
//    axWPSExcel = new QAxObject("ket.Application");
//    QString uuid = axWPSExcel->control() + "&";
//    axWPSExcel->setControl(uuid);
//    return true;
//}

//bool HHOfficeDoc::disConnectWPSExcel()
//{
//    axWPSExcel->disableMetaObject();
//    axWPSExcel->deleteLater();
//    axWPSExcel->clear();
//    delete axWPSExcel;
//    axWPSExcel = NULL;
//    return true;
//}

//BOOL HHOfficeDoc::InsertWPSExcel(const QString &strFilename, const QRect &InputRect, HWND pHwndExcel)
//{
//    if( axWPSExcel == NULL )
//    {
//        if( !connectWPSExcel() )
//            return FALSE;
//    }
//    float fPercent = getWPSExcelShowPercentage();
//    QAxObject *activeWidnow = axWPSExcel->querySubObject("ActiveWindow");   //ActiveWindow
//    float fLeft = activeWidnow->dynamicCall("PointsToScreenPixelsX(int)",0).toInt();
//    float fTop = activeWidnow->dynamicCall("PointsToScreenPixelsY(int)",0).toInt();
//    qDebug()<<"fLeft = "<<fLeft;
//    qDebug()<<"fTop  = "<<fTop;
//    fLeft = ((float)InputRect.left() - fLeft)*3/4 * 100/fPercent;
//    fTop = ((float)InputRect.top() - fTop)*3/4 *100/fPercent;

//    if( fLeft > 0 && fTop > 0 )
//    {
//        float fWidth = (float)InputRect.width()*3/4 * 100/fPercent;
//        float fHeight = (float)InputRect.height()*3/4 * 100/fPercent;
//        QAxObject *sheet = axWPSExcel->querySubObject("ActiveSheet");
//        QAxObject *shapes = sheet->querySubObject("Shapes");
//        shapes->dynamicCall("AddPicture(const QString&,bool,bool,float,float,float,float).Select",strFilename,false,true,fLeft,fTop,fWidth,fHeight);
//    }
//    return TRUE;
//}

//int HHOfficeDoc::getWPSExcelShowPercentage()
//{
//    int nPercent = 100;
//    QAxObject *activeWindow = axWPSExcel->querySubObject("ActiveWindow");
//    nPercent = activeWindow->dynamicCall("Zoom(void)").toInt();
//    activeWindow->disableMetaObject();
//    return nPercent;
//}


//bool HHOfficeDoc::connectWPSPpt()
//{
//    axWPSPpt = new QAxObject("kwpp.Application");
//    QString uuid = axWPSPpt->control() + "&";
//    axWPSPpt->setControl(uuid);
//    m_bWPSPPTFocusState = false;
//    return true;
//}

//bool HHOfficeDoc::disConnectWPSPpt()
//{
//    axWPSPpt->disableMetaObject();
//    axWPSPpt->deleteLater();
//    axWPSPpt->clear();
//    delete axWPSPpt;
//    axWPSPpt = NULL;
//    return true;
//}

//BOOL HHOfficeDoc::InsertWPSPpt(const QString &strFilename, const QRect &InputRect, HWND pHwndPpt)
//{
//    if( axWPSPpt == NULL )
//    {
//        if( !connectWPSPpt() )
//            return FALSE;
//    }

//    bool bIsPlaying = false;

//    QAxObject *presentation = axWPSPpt->querySubObject("ActivePresentation");
//    QAxObject *slideShowWindow = presentation->querySubObject("SlideShowWindow");
//    if( slideShowWindow )
//    {
//        bIsPlaying = true;
//    }

//    float fPercent = getWPSPptShowPercentage( bIsPlaying );
//    qDebug()<<"fPercent = "<<fPercent<<endl;
//    qDebug()<<"m_fLeft = "<<m_fLeft<<endl;
//    qDebug()<<"m_fTop = "<<m_fTop<<endl;
//    if( bIsPlaying )
//    {
////        float fLeft = (float)InputRect.left() * 3/4 * 100/fPercent;
////        float fTop = (float)InputRect.top() * 3/4 * 100/fPercent;
//        QAxObject* pageSetup = presentation->querySubObject( "PageSetup" );
//        int pageSlideSize = pageSetup->property("SlideSize").toInt();
//        if( pageSlideSize != 7 )
//            pageSetup->setProperty( "SlideSize", 7 );
//        qDebug()<<"pageSetup SlideSize = "<<pageSetup->property("SlideSize").toInt();
//        float fLeft  = (float)InputRect.left() - slideShowWindow->dynamicCall("left").toFloat()*4/3*fPercent/100;
//        float fTop = (float)InputRect.top() - slideShowWindow->dynamicCall("top").toFloat()*4/3*fPercent/100;
//        float fWidth = InputRect.width()*3/4*100/fPercent;
//        float fHeight = InputRect.height()*3/4*100/fPercent;
//        QAxObject *view = slideShowWindow->querySubObject("View");
//        QAxObject *slide = view->querySubObject("Slide");
//        if( slide )
//        {
//            QAxObject *master = presentation->querySubObject("SlideMaster");
//            qDebug()<<"master width = "<<master->property("Width").toFloat()<<endl;
//            qDebug()<<"master height = "<<master->property("Height").toFloat()<<endl;
//            QAxObject *shapes = slide->querySubObject("Shapes");
//            shapes->dynamicCall("AddPicture(const QString&,bool,bool,float,float,float,float)",strFilename,false,true,fLeft*3/4*100/fPercent,fTop*3/4*100/fPercent,fWidth,fHeight);
//            int index = slide->dynamicCall("SlideIndex").toInt();
//            view->dynamicCall("Exit(void)");
//            ::PostMessage( m_hPPTNormalWndHWnd, WM_KEYDOWN, (WPARAM)VK_F5, 0 );
//            presentation = axWPSPpt->querySubObject("ActivePresentation");
//            slideShowWindow = presentation->querySubObject("SlideShowWindow");
//            view = slideShowWindow->querySubObject("View");
//            view->dynamicCall("GotoSlide(int,bool)",index,false);

//        }
//        pageSetup->setProperty( "SlideSize", pageSlideSize );
//    }
//    else
//    {
//        QAxObject *activeWindow = axWPSPpt->querySubObject("ActiveWindow");
//        int nType = activeWindow->property("ViewType").toInt();
//        if( nType == 9 )
//        {
//            if( !m_bWPSPPTFocusState )
//            {
//                m_bWPSPPTFocusState = true;

//                activeWindow->setProperty("ViewType",1);
//                activeWindow->setProperty("ViewType",9);
//            }
//            int fLeft = activeWindow->dynamicCall("PointsToScreenPixelsX(int)",0).toInt();
//            int fTop = activeWindow->dynamicCall("PointsToScreenPixelsY(int)",0).toInt();

//            QAxObject *view = activeWindow->querySubObject("View");
//            QAxObject *slide = view->querySubObject("Slide");
//            QAxObject *shapes = slide->querySubObject("Shapes");
////            fLeft = ((float)InputRect.left() - fLeft) * 3/4 * 100/fPercent;
////            fTop = ((float)InputRect.top() - fTop) * 3/4 * 100/fPercent;
//            fLeft = ((float)InputRect.left() - m_fLeft - 5 ) * 3/4 * 100/fPercent;
//            fTop = ((float)InputRect.top() - m_fTop - 3 ) * 3/4 * 100/fPercent;
//            float fWidth = (float)InputRect.width() * 3/4 * 100/fPercent;
//            float fHeight = (float)InputRect.height() * 3/4 * 100/fPercent;
//            shapes->dynamicCall("AddPicture(const QString&,bool,bool,float,float,float,float)",strFilename,false,true,fLeft,fTop,fWidth,fHeight);
//        }
//    }

//    disConnectWPSPpt();
//    return TRUE;
//}

//int HHOfficeDoc::getWPSPptShowPercentage( bool bIsPlaying )
//{
//    int nPercent = 100;
//    if( bIsPlaying )
//    {
//        //100% 1280----720
//        QAxObject *presentation = axWPSPpt->querySubObject("ActivePresentation");
//        QAxObject *slideShowWindow = presentation->querySubObject("SlideShowWindow");
//        nPercent = slideShowWindow->dynamicCall("Width").toFloat() * 4/3 * 100 / 1280;
//        qDebug()<<slideShowWindow->dynamicCall("Width").toInt()<<endl;
//        slideShowWindow->disableMetaObject();
//        presentation->disableMetaObject();
//    }
//    else
//    {
//        if( m_fLeft != 0 || m_fTop !=0 || m_fWPSPPTPercent != 100 )
//        {
//            return m_fWPSPPTPercent;
//        }

//        QAxObject *windows = axWPSPpt->querySubObject("Windows");
//        int count = windows->dynamicCall("Count").toInt();

//        qDebug()<<"count = "<<count;
//        for( int i = 1; i <= count; i++ )
//        {
//            QAxObject *firstWindow = windows->querySubObject("Item(int)",1);
//            firstWindow->dynamicCall("Activate(void)");
//            QAxObject *view = firstWindow->querySubObject("View");
//    //        QAxObject *activeWindow = axWPSPpt->querySubObject("ActiveWindow");
//    //        QAxObject *view = activeWindow->querySubObject("View");
//            nPercent = view->dynamicCall("Zoom(void)").toInt();
//            m_fWPSPPTPercent = nPercent;
//            m_fLeft = firstWindow->dynamicCall("PointsToScreenPixelsX(int)",0).toFloat();
//            m_fTop = firstWindow->dynamicCall("PointsToScreenPixelsY(int)",0).toFloat();
//            qDebug()<<"nPercent = "<<nPercent;
//            qDebug()<<"m_Left = "<<m_fLeft;
//            qDebug()<<"m_fTop = "<<m_fTop;
//        }
//        QAxObject *firstWindow = windows->querySubObject("Item(int)",1);
//        firstWindow->dynamicCall("Activate(void)");
//        QAxObject *view = firstWindow->querySubObject("View");
////        QAxObject *activeWindow = axWPSPpt->querySubObject("ActiveWindow");
////        QAxObject *view = activeWindow->querySubObject("View");
//        nPercent = view->dynamicCall("Zoom(void)").toInt();
//        m_fWPSPPTPercent = nPercent;
//        m_fLeft = firstWindow->dynamicCall("PointsToScreenPixelsX(int)",0).toFloat();
//        m_fTop = firstWindow->dynamicCall("PointsToScreenPixelsY(int)",0).toFloat();
//        view->disableMetaObject();
//        qDebug()<<"m_fWPSPPTPercent = "<<m_fWPSPPTPercent<<endl;
//        qDebug()<<"m_fLeft = "<<m_fLeft<<endl;
//        qDebug()<<"m_fTop = "<<m_fTop<<endl;
////        activeWindow->disableMetaObject();
//        firstWindow->disableMetaObject();
//        windows->disableMetaObject();
//    }
//    return nPercent;
//}

//bool HHOfficeDoc::setWPSPPTNext()
//{
//    if( axWPSPpt == NULL )
//    {
//        if( !connectWPSPpt() )
//            return false;
//    }
//    QAxObject *presentation = axWPSPpt->querySubObject("ActivePresentation");
//    QAxObject *slideShowWindow = presentation->querySubObject("SlideShowWindow");
//    if( !slideShowWindow )
//        return false;
//    QAxObject *view = slideShowWindow->querySubObject("View");
//    view->dynamicCall("Next(void)");
//    view->disableMetaObject();
//    slideShowWindow->disableMetaObject();
//    presentation->disableMetaObject();
//    return true;
//}

//bool HHOfficeDoc::setWPSPPTPrevious()
//{
//    if( axWPSPpt == NULL )
//    {
//        if( !connectWPSPpt() )
//            return false;
//    }
//    QAxObject *presentation = axWPSPpt->querySubObject("ActivePresentation");
//    QAxObject *slideShowWindow = presentation->querySubObject("SlideShowWindow");
//    if( !slideShowWindow )
//        return false;
//    QAxObject *view = slideShowWindow->querySubObject("View");
//    view->dynamicCall("Previous(void)");
//    view->disableMetaObject();
//    slideShowWindow->disableMetaObject();
//    presentation->disableMetaObject();
//    return true;
//}

//bool HHOfficeDoc::setWPSPPtEnd()
//{
//    if( axWPSPpt == NULL )
//    {
//        if( !connectWPSPpt() )
//            return false;
//    }

//    QAxObject *presentation = axWPSPpt->querySubObject("ActivePresentation");
//    QAxObject *slideShowWindow = presentation->querySubObject("SlideShowWindow");
//    if( !slideShowWindow )
//        return false;
//    QAxObject *view = slideShowWindow->querySubObject("View");
//    view->dynamicCall("Exit(void)");
//    view->disableMetaObject();
//    slideShowWindow->disableMetaObject();
//    presentation->disableMetaObject();
//    return true;
//}

//int HHOfficeDoc::getWPSPPTPlagingIndex()
//{
//    if( axWPSPpt == NULL )
//    {
//        if( !connectWPSPpt() )
//            return -1;
//    }
//    QAxObject *presentation = axWPSPpt->querySubObject("ActivePresentation");
//    if( !presentation )
//        return -1;
//    QAxObject *slideShowWindow = presentation->querySubObject("SlideShowWindow");
//    if( !slideShowWindow )
//        return -1;
//    QAxObject *view = slideShowWindow->querySubObject("View");
//    QAxObject *slide = view->querySubObject("Slide");
//    if( slide )
//    {
//        int nPosition = slide->dynamicCall("SlideIndex").toInt();
//        slide->disableMetaObject();
//        slideShowWindow->disableMetaObject();
//        presentation->disableMetaObject();
//        return nPosition;
//    }
//    else
//    {
//        QAxObject *slides = presentation->querySubObject("Slides");
//        int nPosition = slides->dynamicCall("Count").toInt();
//        slides->disableMetaObject();
//        view->disableMetaObject();
//        slideShowWindow->disableMetaObject();
//        presentation->disableMetaObject();
//        return nPosition + 1;
//    }
//    return -1;
//}

QString HHOfficeDoc::isWPSPPT( HWND hwnd )
{
    TCHAR szCaptionName[ 255 ] = { 0 };
    ::GetWindowText( hwnd, szCaptionName, 254 );
    if( _tcsstr( szCaptionName, _T("WPS 演示") ))
    {
        m_hPPTNormalWndHWnd = hwnd;
        return "wpsppt";
    }
    return "";
}

QString HHOfficeDoc::isWPSPPTPlaying( HWND hwnd )
{
    TCHAR szClassName[ 255 ] = { 0 };
    ::GetClassName( hwnd, szClassName, 254 );
    if( _tcscmp( szClassName, _T("QWidget") ) == 0 )
    {
        TCHAR szCaptionName[ 255 ] = { 0 };
        ::GetWindowText( hwnd, szCaptionName, 254 );
        if( _tcsstr( szCaptionName, _T("WPS") ))
        {
            HWND next = ::GetNextWindow( hwnd, GW_HWNDNEXT );
            while( next )
            {
                if( isWPSPPT(next).isEmpty() )
                    next = ::GetWindow( next, GW_HWNDNEXT );
                else
                {
                    m_hPPTShowWndHWnd = hwnd;
                    return "wpspptplaying";
                }
            }
        }
    }
    return "";
}

bool HHOfficeDoc::connectWPSPpt()
{
    axWPSPpt = new QAxObject("kwpp.Application");
    QString uuid = axWPSPpt->control() + "&";
    axWPSPpt->setControl(uuid);
    return true;
}

bool HHOfficeDoc::disConnectWPSPpt()
{
    axWPSPpt->disableMetaObject();
    axWPSPpt->deleteLater();
    axWPSPpt->clear();
    delete axWPSPpt;
    axWPSPpt = NULL;
    return true;
}

bool HHOfficeDoc::setWPSPPTNext()
{
    if( axWPSPpt == NULL )
    {
        if( !connectWPSPpt() )
            return false;
    }
    QAxObject *presentation = axWPSPpt->querySubObject("ActivePresentation");
    QAxObject *slideShowWindow = presentation->querySubObject("SlideShowWindow");
    if( !slideShowWindow )
        return false;
    QAxObject *view = slideShowWindow->querySubObject("View");
    view->dynamicCall("Next(void)");
    view->disableMetaObject();
    slideShowWindow->disableMetaObject();
    presentation->disableMetaObject();
    return true;
}

bool HHOfficeDoc::setWPSPPTPrevious()
{
    if( axWPSPpt == NULL )
    {
        if( !connectWPSPpt() )
            return false;
    }
    QAxObject *presentation = axWPSPpt->querySubObject("ActivePresentation");
    QAxObject *slideShowWindow = presentation->querySubObject("SlideShowWindow");
    if( !slideShowWindow )
        return false;
    QAxObject *view = slideShowWindow->querySubObject("View");
    view->dynamicCall("Previous(void)");
    view->disableMetaObject();
    slideShowWindow->disableMetaObject();
    presentation->disableMetaObject();
    return true;
}

bool HHOfficeDoc::setWPSPPtEnd()
{
    if( axWPSPpt == NULL )
    {
        if( !connectWPSPpt() )
            return false;
    }

    QAxObject *presentation = axWPSPpt->querySubObject("ActivePresentation");
    QAxObject *slideShowWindow = presentation->querySubObject("SlideShowWindow");
    if( !slideShowWindow )
        return false;
    QAxObject *view = slideShowWindow->querySubObject("View");
    view->dynamicCall("Exit(void)");
    view->disableMetaObject();
    slideShowWindow->disableMetaObject();
    presentation->disableMetaObject();
    return true;
}

bool HHOfficeDoc::setWPSPenType( QString strType )
{
    if( axWPSPpt == NULL )
    {
        if( !connectWPSPpt() )
            return false;
    }

    QAxObject *presentation = axWPSPpt->querySubObject("ActivePresentation");
    QAxObject *slideShowWindow = presentation->querySubObject("SlideShowWindow");
    if( !slideShowWindow )
        return false;
    QAxObject *view = slideShowWindow->querySubObject("View");

    if( strType == "pen" )
        view->setProperty( "PointerType", "ppSlideShowPointerPen" );
    else if( strType == "eraser" )
        view->setProperty( "PointerType", "ppSlideShowPointerEraser" );
    else if( strType == "select" )
        view->setProperty( "PointerType", "ppSlideShowPointerArrow" );
    view->disableMetaObject();
    slideShowWindow->disableMetaObject();
    presentation->disableMetaObject();
    return true;
}

int HHOfficeDoc::getWPSPPTPlagingIndex()
{
    if( axWPSPpt == NULL )
    {
        if( !connectWPSPpt() )
            return -1;
    }
    QAxObject *presentation = axWPSPpt->querySubObject("ActivePresentation");
    if( !presentation )
        return -1;
    QAxObject *slideShowWindow = presentation->querySubObject("SlideShowWindow");
    if( !slideShowWindow )
        return -1;
    QAxObject *view = slideShowWindow->querySubObject("View");
    QAxObject *slide = view->querySubObject("Slide");
    if( slide )
    {
        int nPosition = slide->dynamicCall("SlideIndex").toInt();
        slide->disableMetaObject();
        slideShowWindow->disableMetaObject();
        presentation->disableMetaObject();
        return nPosition;
    }
    else
    {
        QAxObject *slides = presentation->querySubObject("Slides");
        int nPosition = slides->dynamicCall("Count").toInt();
        slides->disableMetaObject();
        view->disableMetaObject();
        slideShowWindow->disableMetaObject();
        presentation->disableMetaObject();
        return nPosition + 1;
    }
    return -1;
}
