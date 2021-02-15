#ifndef HHOFFICEDOC_H
#define HHOFFICEDOC_H

#include <atlbase.h>
/* open this para will make the release version error,don't no why.
#include <atlcom.h>
#include <atlctl.h>
#include <atlsafe.h>
using namespace ATL;
*/
#include <QString>
#include <QRect>
#include <QAxObject>
#include <QApplication>
#include <QDesktopWidget>
#include <QJsonObject>

#pragma warning(disable: 4772)

#import "./ImportFile/MSO.DLL" rename("RGB","MSORGB"),rename("DocumentProperties","MSODocumentProperties"),rename_namespace("Office")\
    auto_rename\
    auto_search
using namespace Office;

#import "./ImportFile/VBE6EXT.olb" rename_namespace("VBE6") \
    auto_rename\
    auto_search

using namespace VBE6;

//WORD
#import "./ImportFile/MSWORD.OLB" rename("FindText","WORDFindText"),rename("ExitWindows","WORDExitWindows"), rename_namespace("MSWord")\
    auto_rename\
    auto_search
//EXCEL
#import "./ImportFile/EXCEL9.OLB" rename("IFont","MSExcelIFont"),rename("IPicture","MSExcelIPicture"),rename("ReplaceText","ExcelReplaceText"),rename("CopyFile","ExcelCopyFile"),rename("RGB","ExcelRGB"),rename("DialogBox","DialogBoxEx"),rename_namespace("MSExcel")\
    auto_rename\
    auto_search
//PPT
#import "./ImportFile/MSPPT9.OLB" rename("RGB","PPTRGB"),rename_namespace("MSPPT")\
    auto_rename\
    auto_search

#import "./ImportFile/Acrobat.dll" rename("RGBA","PDFRGB"),rename_namespace("XPDF")\
    auto_rename\
    auto_search

#import "./ImportFile/VISLIB.DLL" rename("RGB","VISIORGB"),rename_namespace("MSVISIO")\
    auto_rename\
    auto_search

enum OFFICETYPE {NONOFFICE,ISMSWORD,ISMSPPT,ISMSEXCEL};

class HHOfficeDoc
{
public:
    HHOfficeDoc();
    ~HHOfficeDoc();

public:
    QString getDocumentTypeFromTopWindows( HWND hwndWhiteBoard );
	bool    embedPPT(QString strFilename, QRect InputRect);
    bool    embedPPTPlaying( QString strFilename, QRect InputRect );
    bool    embedExcel( QString strFilename, QRect InputRect );
    bool    embedWord( QString strFilename, QRect InputRect );
    QString getDocumentTypeFromPoint( int x, int y );
    bool    setPPTPrevious();
    bool	setPPTNext( bool &bIsEnd );
    bool	setPPTEnd();
    int     getPPTPlayingIndex();

    //导出PPT文件
    bool    exportPPT(QString fileName, QStringList picList);
    bool    exportPDF(QString fileName, QStringList picList);
    bool    exportWORD(QString fileName, QStringList picList);
    bool    exportEXCEL(QString fileName, QStringList picList);
    bool    exportHTML(QString fileName, QStringList picList);
    bool    exportImage(QString fileName, QStringList picList);

    QStringList importPPT(QString fileName, QString saveDir);
    QVariantMap importPPT2( QString fileName );
    QVariantMap getJSONFromPPTSlide( void* pSlide, QString strDir );
    int     getTypeFromPPTItem( void* pItem );
    QJsonObject getPictureJSON( void* pItem, QString strDir );
	QJsonObject getTextEditJSON(void* pItem, QString strDir);
	/*/TTQX-zhaozhengze-ppt导入视频和音频
	/*/
	QJsonObject getMediaJSON(void* pItem, QString strDir,QString strUnCompressPath,QString strSlideIndex);
	//*/
    void closePPTPresentation( void* pItem );

	//Add by wangxianbing,2018/1/10 尝试关闭ppt进程。
	void closePPTApp();

    // Add By Fanhj 2017-11-03
    bool    getPPTPageInfo(QString &sPageInfo);
    bool    setPPTPenInfo(const QString &sPageInfo, const QVariantMap &args);
    bool    getPPTThumbnail(QStringList &lResultFile,
                            const QString &sPath,
                            const QSize imgSize,
                            const QString sImgType);
    // Add End

private:
    static BOOL CALLBACK GetDesktopWindow( HWND hwnd, LPARAM lParam );
    QString getDocumentTypeFromHWND( HWND hwnd );
    QString filterDocumentType( HWND hwndWhiteBoard, HWND hwnd, QString strFilter );
    QString isVisio( HWND hwnd );
    QString isExcel( HWND hwnd );
    QString isWord( HWND hwnd );
    QString isPPT( HWND hwnd );
    QString isPPTPlaying( HWND hwnd );

    void deleteTempPicture(QStringList picList);
    bool createHtmlFile(QString fileName, QStringList relativePicList);
    QString createLocalDir(QString sUpDir, QString sPath);  //创建本地图片保存的文件夹

private:
    //ppt
    HWND								m_hPPTShowWndHWnd;
    float								m_PptVersion;
    CComPtr< MSPPT::_Application >      m_PptApplication;
    MSPPT::_PresentationPtr				m_PptPresentation;
    MSPPT::SlideShowWindowPtr			m_PptSlideShowWindow;
    MSPPT::SlideShowViewPtr				m_PptSlideshowView;
    MSPPT::SlidesPtr					m_PptSlides;
    MSPPT::_SlidePtr					m_PptSlide;
    MSPPT::_MasterPtr					m_PptMaster;
    MSPPT::ShapesPtr					m_PptShapes;
    MSPPT::ShapePtr						m_PptShape;
    bool	connectPPT();
    bool    disConnectPPT();
//    BOOL    ConnectPPT();
//    BOOL    DisConnectPPT();
    bool connectPPTApp();
    bool disConnectPPTApp();

    bool            m_bPPTFocusState;
public:
    int getPPTShowPercentage(bool bSlideShowMode);

private:
    //excel

    HWND								m_hExcelShowWndHWnd;
	HWND								m_hWordShowWndHWnd;
	HWND								m_hPPTNormalWndHWnd;
    CComPtr<MSExcel::_Application>      m_ExcelApp;
    float								m_ExcelVersion;
    MSExcel::_WorksheetPtr              m_ExcelWorksheet;
    MSExcel::WindowPtr  			    m_ExcelWindow;
    MSExcel::ShapesPtr  			    m_ExcelShapes;
    MSExcel::ShapePtr					m_ExcelShape;
    MSExcel::_WorkbookPtr               m_pWorkBook;
    Office::_CommandBarsPtr             m_OfficeCmdBars;
    Office::CommandBarPtr               m_OfficeCmdBar;
    Office::CommandBarControlsPtr       m_OfficeCmdBarControls;
    Office::CommandBarControlPtr        m_OfficeCmdBarControl;
    bool connectExcel();
    bool disConnectExcel();


private:// ppt
	BOOL	InsertPpt(const QString& strFilename, const QRect& InputRect, HWND pHwndPpt = NULL);
	/// 插入
	BOOL	InsertPptLast(const QString & strFilename, const int & index, QRect& InputRect);
	float	GetPptShowPercentage(BOOL bSlideShowMode = FALSE);
	void    SetPPTPageIndexBrforeChange();

	void    SetAfterPPTPreAndNext(int iChangeType);
	DWORD64 CheckPageIndexIsExisted(int PPTPageIndex);
	//int     CheckPageIndexIsExisted( CHHSlide * Slide );

	void    SetPPTShowPageByIndex(int index);

	void    GetCurPptIndex(MSPPT::SlideShowViewPtr	pPptSlideshowView, int& index);
	BOOL	Insertnormalppt(const QString& strFilename, const QRect& InputRect, HWND pHwndPpt = NULL);

	/// 判断新页是否需要插入在最后
	BOOL	PPTIndextIsInMiddle(int nPos, DWORD64& dNetID, DWORD64& dStartNetID);

	/// Office变量
	int									m_iPPTCurrentPageIndex;
	/// 翻页前的Index
	int									m_iPPTBeforeChangePageIndex;

	MSPPT::PresentationsPtr				m_PptPresentations;

	MSPPT::DocumentWindowPtr			m_PptDocumentWindow;
	MSPPT::ViewPtr						m_PptView;
	MSPPT::SlideShowSettingsPtr			m_PptSlideShowSettings;

	//////////////////////////////////////////////////////////////////////////////////////////////
    /// 挂接Excel
    BOOL	ConnectExcel();
    /// 断接Excel
    BOOL	DisConnectExcel();
    float	GetExcelShowPercentage();
    void	ExcelUndoClear();
    BOOL	InsertExcel(const QString& strFilename,const QRect& InputRect,HWND pHwndExcel = NULL);


    //////////////////////////////////////////////////////////////////////////////////////////////
    /// 挂接Word
    BOOL	ConnectWord();
    /// 断接Word
    BOOL	DisConnectWord();
    void	AdjustWordOptions(BOOL bRestore = FALSE) ;
    BOOL	InsertWord(const QString& strFilename,const QRect& InputRect,HWND pHwndWord = NULL);

    float								m_WordVersion;
    MSWord::WindowPtr			   		m_WordWindow;
    MSWord::_DocumentPtr				m_WordDocument;
    MSWord::ViewPtr						m_WordView;
    MSWord::OptionsPtr                  m_WordOptions;
    MSWord::ZoomPtr						m_WordZoom;
    MSWord::ShapesPtr				   	m_WordShapes;
    MSWord::ShapePtr					m_WordShape;
    MSWord::RangePtr					m_WordRange;
    MSWord::SelectionPtr				m_WordSelection;
    MSWord::WrapFormatPtr				m_WordWrapFormat;
    MSWord::PanePtr                     m_WordPane;
    //////////////////////////////////////////////////////////////////////////////////////////////
    BOOL ConnectVisio();
    BOOL DisConnectVisio();
    HWND								m_hVisioWndHWnd;
    //////////////////////////////////////////////////////////////////////////////////////////////
    BOOL	ConnectPDF();
    BOOL	DisConnectPDF();
    HWND								m_hPdfWndHWnd;
    //////////////////////////////////////////////////////////////////////////////////////////////

    static BOOL CALLBACK GetAnyDesktopWindow(HWND hwnd, LPARAM lParam);
    OFFICETYPE    WhichOffice( HWND& pWndOffice );
    BOOL	InsertOffice(const QString& strFilename,const QRect& InputRect);
    BOOL	InsertOfficeEx(const QString& strFilename,const QRect& InputRect);

//public:

//    bool    m_bIsWPS;
//    bool    connectWPSWord();
//    bool    connectWPSExcel();
//    bool    connectWPSPpt();
//    bool    disConnectWPSWord();
//    bool    disConnectWPSExcel();
//    bool    disConnectWPSPpt();
//    QString isWPSWord( HWND hwnd );
//    QString isWPSExcel( HWND hwnd );
//    QString isWPSPPT( HWND hwnd );
//    QString isWPSPPTPlaying( HWND hwnd );
//    BOOL	InsertWPSWord( const QString& strFilename, const QRect& InputRect, HWND pHwndWord = NULL );
//    BOOL    InsertWPSExcel( const QString& strFilename, const QRect& InputRect, HWND pHwndExcel = NULL );
//    BOOL    InsertWPSPpt( const QString& strFilename, const QRect& InputRect, HWND pHwndPpt = NULL );
//    int     getWPSWordShowPercentage();
//    int     getWPSExcelShowPercentage();
//    int     getWPSPptShowPercentage( bool bIsPlaying );
//    bool    setWPSPPTPrevious();
//    bool    setWPSPPTNext();
//    bool    setWPSPPtEnd();
//    int     getWPSPPTPlagingIndex();
//private:
//    bool        m_bWPSPPTFocusState;
//    QAxObject   *axWPSWord;
//    QAxObject   *axWPSExcel;
//    QAxObject   *axWPSPpt;
//    HANDLE      m_hWPS;
//    float       m_fWPSPPTPercent;
//    float       m_fLeft;
//    float       m_fTop;

public:
    QString isWPSPPT( HWND hwnd );
    QString isWPSPPTPlaying( HWND hwnd );
    QAxObject* axWPSPpt;
    bool    connectWPSPpt();
    bool    disConnectWPSPpt();
    bool    setWPSPPTNext();
    bool    setWPSPPTPrevious();
    bool    setWPSPPtEnd();
    bool    setWPSPenType( QString strType );
    int     getWPSPPTPlagingIndex();
    QAxObject* m_axWPSWord;
    bool    connectWPSWord();
    bool    disConnetWPSWord();
    bool    exportWPSWord( QString fileName, QStringList picList );
    QAxObject* m_axWPSExcel;
    bool    connectWPSExcel();
    bool    disConnectWPSExcel();
    bool    exportWPSExcel( QString fileName, QStringList picList );
    bool    exportWPSPpt( QString fileName, QStringList picList );

    QAxObject* axPptApp;

    // Add By Fanhj 2017-11-03

    bool    getWPSPPTPageInfo(QString &sPageInfo);
    bool    setWPSPPTPenInfo(const QString &sPageType, const QVariantMap &args);
    bool    getWPSPPTThumbnail(QStringList &lResultFile,
                         const QString &sPath,
                         const QString sImgType,
                         const QSize imgSize);
    // Add End

};

#endif // HHOFFICEDOC_H
