#include "hhutilityfunctions.h"

#define  TABTIP_KEYBOARD

#include <QDebug>
#include "hhusbdog.h"
#include "hhsystemtool.h"
#include "hotkey/hhhotkeyinfo.h"

#ifdef WIN32
    #include "windows.h"
    #include "WinUser.h"
    #include <atlbase.h>
    #include <windef.h>
    #include <MAPI.h>
    #include <QDir>
    #include <qapplication.h>

#else
#endif

HHUtilityFunctions::HHUtilityFunctions()
{
    m_hotKeyInfo = NULL;
}

HHUtilityFunctions::~HHUtilityFunctions()
{
    if(m_hotKeyInfo)
    {
        delete m_hotKeyInfo;
        m_hotKeyInfo = NULL;
    }
}

bool HHUtilityFunctions::openSystemKeyboard() {

	/// <remarks>	modify Gan Songlin, 2017/10/30 start . </remarks>
#ifdef TABTIP_KEYBOARD
    HSystemTool::openSystemKeyboardTabTip();
#else
	/// <remarks>	modify Gan Songlin, 2017/10/30 end . </remarks>
	HSystemTool::openSystemKeyboard();
#endif
    return true;
}

void HHUtilityFunctions::setSystemParametersInfo( QString id ) {
#ifdef WIN32
    if( id == "SPI_GETFOREGROUNDLOCKTIMEOUT" ) {
        DWORD dwTimeout = -1;
        SystemParametersInfo( SPI_GETFOREGROUNDLOCKTIMEOUT, 0, (LPVOID)&dwTimeout, 0 );
        if( 100 <= dwTimeout ) {
            SystemParametersInfo(SPI_SETFOREGROUNDLOCKTIMEOUT, 0, (LPVOID)0, SPIF_SENDCHANGE | SPIF_UPDATEINIFILE);
            Sleep( 2000 );
        }
    }
#else
#endif
}

void HHUtilityFunctions::setForegroundWindow( WId hWnd ) {
#ifdef WIN32
//        typedef void (WINAPI*PROCSWITCHTOTHISWINDOW)(HWND,BOOL);
//        PROCSWITCHTOTHISWINDOW SwitchToThisWindow;
//        HMODULE hUser32 = GetModuleHandle(L"user32");
//        SwitchToThisWindow = (PROCSWITCHTOTHISWINDOW)GetProcAddress(hUser32,"SwitchToThisWindow");
//        SwitchToThisWindow( ( HWND )hWnd, TRUE );
//        QString str( "Shell_TrayWnd" );
//        SetActiveWindow( FindWindow( ( wchar_t* )str.utf16(), NULL ) );

    HWND hForeWnd = GetForegroundWindow();
    DWORD dwForeID = GetWindowThreadProcessId( hForeWnd, NULL );
    DWORD dwCurID = GetCurrentThreadId();
    AttachThreadInput( dwCurID, dwForeID, TRUE );
    SetWindowPos( ( HWND )hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE );
    AttachThreadInput( dwCurID, dwForeID, FALSE );
//    AttachThreadInput( GetWindowThreadProcessId( ::GetForegroundWindow(), NULL ), GetCurrentThreadId(), TRUE );
//    SetForegroundWindow( ( HWND )hWnd );
//    SetFocus( ( HWND )hWnd );
//    AttachThreadInput( GetWindowThreadProcessId( ::GetForegroundWindow(), NULL ), GetCurrentThreadId(), FALSE );
#else
#endif
}

bool HHUtilityFunctions::getSpacePressState()
{
    bool isPressing = false;
#ifdef WIN32
           isPressing = (GetAsyncKeyState(VK_SPACE) & 0x8000) == 0x8000 ;
#else
#endif
    return isPressing;
}

QString HHUtilityFunctions::hotKey_getOneBtnContent(int nSolutionID, int nBtnID)
{
    if(m_hotKeyInfo == NULL)
        m_hotKeyInfo = new HHHotKeyInfo();

    return m_hotKeyInfo->getOneBtnContent(nSolutionID, nBtnID);
}

int HHUtilityFunctions::hotKey_initCurrentSolution(int nSolutionID)
{
    if(m_hotKeyInfo == NULL)
        m_hotKeyInfo = new HHHotKeyInfo();

    return m_hotKeyInfo->initCurrentSolution(nSolutionID);
}

int HHUtilityFunctions::hotKey_getCurrentSolutionID()
{
    if(m_hotKeyInfo == NULL)
        m_hotKeyInfo = new HHHotKeyInfo();
    return m_hotKeyInfo->getCurrentSolutionID();
}

QString HHUtilityFunctions::hotKey_getCurrentBtnContent(int nBtnID)
{
    if(m_hotKeyInfo == NULL)
        m_hotKeyInfo = new HHHotKeyInfo();

    return m_hotKeyInfo->getCurrentBtnContent(nBtnID);
}

bool HHUtilityFunctions::executeExe( QString strOperation, QString strExe, QString strParameters, QString strDirectory ) {
#ifdef WIN32
    HINSTANCE nRet = ShellExecute( NULL, ( wchar_t* )strOperation.utf16(), ( wchar_t* )strExe.utf16(),
                  ( wchar_t* )strParameters.utf16(), ( wchar_t* )strDirectory.utf16(), SW_SHOW );
    qDebug()<<"nRet:"<<nRet;
//                  ( wchar_t* )strParameters.utf16(), NULL, SW_SHOW );
#else
    QProcess process;
    process.startDetached( strExe );
#endif
    return true;
}

void HHUtilityFunctions::togglePressAndHold( WId hWnd ) {
    #define TABLET_DISABLE_PRESSANDHOLD        0x00000001
    #define TABLET_DISABLE_PENTAPFEEDBACK      0x00000008
    #define TABLET_DISABLE_PENBARRELFEEDBACK   0x00000010
    #define TABLET_DISABLE_TOUCHUIFORCEON      0x00000100
    #define TABLET_DISABLE_TOUCHUIFORCEOFF     0x00000200
    #define TABLET_DISABLE_TOUCHSWITCH         0x00008000
    #define TABLET_DISABLE_FLICKS              0x00010000
    #define TABLET_ENABLE_FLICKSONCONTEXT      0x00020000
    #define TABLET_ENABLE_FLICKLEARNINGMODE    0x00040000
    #define TABLET_DISABLE_SMOOTHSCROLLING     0x00080000
    #define TABLET_DISABLE_FLICKFALLBACKKEYS   0x00100000
    #define TABLET_ENABLE_MULTITOUCHDATA       0x01000000
    const DWORD dwHwndTabletProperty =
        TABLET_DISABLE_PRESSANDHOLD | // disables press and hold (right-click) gesture
        TABLET_DISABLE_PENTAPFEEDBACK | // disables UI feedback on pen up (waves)
        TABLET_DISABLE_PENBARRELFEEDBACK | // disables UI feedback on pen button down (circle)
        TABLET_DISABLE_FLICKS; // disables pen flicks (back, forward, drag down, drag up)

#ifdef WIN32
    QString tabletAtom( "MicrosoftTabletPenServiceProperty" );
    ATOM atom = ::GlobalAddAtom( tabletAtom.toStdWString().c_str() );
    ::SetProp( ( HWND )hWnd, tabletAtom.toStdWString().c_str(), reinterpret_cast< HANDLE >( dwHwndTabletProperty ) );
    ::GlobalDeleteAtom( atom );
#else
#endif
}

bool HHUtilityFunctions::checkUsbDog()
{
    HHUsbDog usbDog;
    return usbDog.checkUsbDog();
}

int HHUtilityFunctions::sendMail(QString filePathName)
{
#ifdef WIN32
    int ret = 1;//发送成功
    if(filePathName.isEmpty())
    {
        return -2;//文件名错误
    }

    HMODULE hlibMAPI = LoadLibrary(L"MAPI32.DLL");
    if(NULL == hlibMAPI)
    {
        return -1;//初始化错误
    }

    LPMAPILOGON lpfnMAPILogon = ( LPMAPILOGON ) GetProcAddress( hlibMAPI, "MAPILogon" );
    LPMAPILOGOFF lpfnMAPILogoff = ( LPMAPILOGOFF ) GetProcAddress( hlibMAPI, "MAPILogoff" );
    LPMAPISENDMAIL lpfnMAPISendMail = ( LPMAPISENDMAIL ) GetProcAddress( hlibMAPI, "MAPISendMail" );

    LHANDLE Mapi;
    if( lpfnMAPILogon( 0,NULL, NULL, MAPI_LOGON_UI, 0, &Mapi ) == SUCCESS_SUCCESS )
    {
        MapiMessage Msg;
        ZeroMemory( &Msg, sizeof( Msg ) );

        //////////////////////文件名转换有问题///////////////////////
        filePathName = filePathName.replace("/","\\");
        QByteArray ba = filePathName.toLocal8Bit();//toUtf8();
//        LPSTR pFileName = (LPSTR)ba.data();
//        LPSTR pFileName = new char[MAX_PATH];
        LPSTR pFileName = (LPSTR)ba.data();

//        qDebug()<<"------sendMail-----pFileName:"<<pFileName;
//        char fnn[] = "C:\\1.hhtx";
//        LPSTR pFileName = (LPSTR)fnn;
        if ( NULL == pFileName )
        {
            lpfnMAPILogoff( Mapi,NULL,0,0 );
            FreeLibrary(hlibMAPI);
            return -2;//文件名错误
        }

        MapiFileDesc FileDesc =
            {
                0,						// ulReserved, must be 0
                0,						// no flags; this is a data file
                ( ULONG )-1,			// position not specified
                pFileName,             	// pathname, if original filename is NULL, this is the filename
                pFileName,					// original filename
                NULL
            }; // MapiFileTagExt unused

        Msg.nFileCount     = 1;                         //文件个数
        Msg.lpFiles        = &FileDesc;                 //文件信息
        int nError = lpfnMAPISendMail( Mapi, NULL, &Msg, MAPI_DIALOG, 0 );
//        qDebug()<<"------sendMail-----nError:"<<nError;
        if ( nError != SUCCESS_SUCCESS && nError != MAPI_USER_ABORT && nError != MAPI_E_LOGIN_FAILURE )
        {
            ret = 0;//发送错误
        }
        lpfnMAPILogoff( Mapi,NULL,0,0 );
    }
    else
    {
        ret = 0;//发送错误
    }

    FreeLibrary(hlibMAPI);

    return ret;
#else
    return 1;
#endif
}

short HHUtilityFunctions::getWinAsyncKeyState(int nVirtKey) {
    return ::GetAsyncKeyState( nVirtKey );
}

bool HHUtilityFunctions::foundEntranceUserOpen()
{
#ifdef WIN32
    QProcess process;
    process.start("tasklist");
    process.waitForFinished();
    QByteArray output =process.readAllStandardOutput();
    QString programs;
    programs.prepend(output);
    if(programs.contains("HiteEntrance.exe")){
        QSettings settings(QSettings::NativeFormat, QSettings::SystemScope,"HiClass","HiClass");
        QString softWareName = settings.value("InstallPath",QVariant()).toString()+"\\";
        QString hiteEntrance=softWareName+"HiteEntrance\\HiteEntrance.exe";
        qDebug()<<"---------------4:"<<hiteEntrance;
        QFile file( hiteEntrance );
        if( file.exists() ) {
            QString params ="boardparams|{\"type\":\"gethhtfile\"}";
            QByteArray  tmp_in (params.toUtf8());
            params = tmp_in.toBase64();

            HHUtilityFunctions uf;
            uf.executeExe( "open", hiteEntrance, params );

            qDebug()<<"------open-----5:"<<hiteEntrance<<"---params:"<<params;
            process.close();
            return true;
        }
    }
    process.close();
    return false;
#else
    return false;
#endif
}
