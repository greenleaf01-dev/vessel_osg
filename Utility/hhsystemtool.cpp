#include "hhsystemtool.h"


#ifdef WIN32

#include <objbase.h>
#include <tchar.h>
#include <ShellAPI.h>


LPFN_ISWOW64PROCESS CDisableWow64FsRedirection::fnIsWow64Process = NULL;
LPFN_WOW64DISABLEWOW64FSREDIRECTION CDisableWow64FsRedirection::fnWow64DisableWow64FsRedirection = NULL;
LPFN_WOW64REVERTWOW64FSREDIRECTION CDisableWow64FsRedirection::fnWow64RevertWow64FsRedirection = NULL;

CDisableWow64FsRedirection::CDisableWow64FsRedirection()
{
    oldValue  = NULL;
    bDisabled = FALSE;
    bIsWOW64  = IsWow64Process();

    if (bIsWOW64)// we run under WOW64
    {
        bDisabled = DisableWow64FsRedirection(&oldValue);
    }
}

CDisableWow64FsRedirection::~CDisableWow64FsRedirection()
{
    if (bDisabled) RevertWow64FsRedirection(oldValue);
}

BOOL CDisableWow64FsRedirection::IsEnableUAC()
{
    BOOL isEnableUAC = FALSE;
    OSVERSIONINFO osversioninfo;
    ZeroMemory(&osversioninfo, sizeof(osversioninfo));
    osversioninfo.dwOSVersionInfoSize = sizeof(osversioninfo);

    if (GetVersionEx(&osversioninfo))
    {
        if (osversioninfo.dwMajorVersion > 5)// window vista or windows server 2008 or later operating system
        {
            HKEY hKEY = NULL;
            DWORD dwType = REG_DWORD;
            DWORD dwEnableLUA = 0;
            DWORD dwSize = sizeof(DWORD);
            LONG status = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System\\"),
                0, KEY_READ, &hKEY);

            if (ERROR_SUCCESS == status)
            {
                status = RegQueryValueEx(hKEY, _T("EnableLUA"), NULL, &dwType,	(BYTE*)&dwEnableLUA, &dwSize);
                if (ERROR_SUCCESS == status)
                {
                    isEnableUAC = (dwEnableLUA == 1) ? TRUE : FALSE;
                }

                RegCloseKey(hKEY);
            }
        }
    }
    return isEnableUAC;
}

BOOL CDisableWow64FsRedirection::IsWow64Process(HANDLE hProcess/* = NULL*/)
{
    if (NULL == fnIsWow64Process)
    {
        fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(
            GetModuleHandle(_T("kernel32")), "IsWow64Process");
    }

    if (fnIsWow64Process)
    {
        BOOL bIsWow64 = FALSE;
        if (fnIsWow64Process(hProcess? hProcess : GetCurrentProcess(), &bIsWow64))
        {
            return bIsWow64;
        }
    }

    return FALSE;
}

BOOL CDisableWow64FsRedirection::DisableWow64FsRedirection(PVOID* pOldValue)
{
    if (NULL == fnWow64DisableWow64FsRedirection)
    {
        HMODULE hK32lib = GetModuleHandle(_T("kernel32"));
        if (hK32lib)
        {
            fnWow64DisableWow64FsRedirection = (LPFN_WOW64DISABLEWOW64FSREDIRECTION)GetProcAddress(
                hK32lib, "Wow64DisableWow64FsRedirection");
            fnWow64RevertWow64FsRedirection  = (LPFN_WOW64REVERTWOW64FSREDIRECTION)GetProcAddress(
                hK32lib, "Wow64RevertWow64FsRedirection");
        }
    }

    if (fnWow64DisableWow64FsRedirection)
    {
        return fnWow64DisableWow64FsRedirection(pOldValue);
    }

    return FALSE;
}

BOOL CDisableWow64FsRedirection::RevertWow64FsRedirection(PVOID OldValue)
{
    if (NULL == fnWow64RevertWow64FsRedirection)
    {
        fnWow64RevertWow64FsRedirection = (LPFN_WOW64REVERTWOW64FSREDIRECTION)GetProcAddress(
            GetModuleHandle(_T("kernel32")), "Wow64RevertWow64FsRedirection");
    }

    if (fnWow64RevertWow64FsRedirection)
    {
        return fnWow64RevertWow64FsRedirection(OldValue);
    }

    return FALSE;
}

BOOL CDisableWow64FsRedirection::OpenSystemKeyboard()
{

    TCHAR szSYSDirectory[MAX_PATH];
    GetSystemDirectory(szSYSDirectory, MAX_PATH);

    HINSTANCE ret = 0;
    if (CDisableWow64FsRedirection::IsWow64Process()) // we run under WOW64
    {
        _tcsncat(szSYSDirectory, _TEXT("\\osk.exe"), 128);
        ret = ShellExecute(NULL, _TEXT("open"), _T("explorer"), szSYSDirectory, NULL, SW_SHOW);
    }
    else
    {
        ret = ShellExecute(NULL, _T("open"), _T("osk.exe"), NULL, szSYSDirectory, SW_SHOWNORMAL);
    }

    if ((int)ret > 32)//Execute success!
    {
        for (int i = 0;;i++)
        {
            HWND pWnd = FindWindow(_T("OSKMainClass"), NULL);

            if (pWnd)
            {
                if (IsIconic(pWnd))
                    ShowWindow(pWnd, SW_RESTORE);
                SetWindowPos(pWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
                return TRUE;
            }

            if (i == 10)
            {
                return TRUE;
            }

            Sleep(200);
        }

    }
    return FALSE;
}

BOOL CDisableWow64FsRedirection::CloseSystemKeyboard()
{
    HWND pWnd  = ::FindWindow(_T("OSKMainClass"), NULL);
    if (pWnd)
    {
        PostMessage(pWnd, WM_CLOSE, 0, 0);
        return TRUE;
    }
    return FALSE;
}

BOOL CDisableWow64FsRedirection::OpenSystemKeyboardTabTip()
{
	QString csProcess = "C:\\Program Files\\Common Files\\Microsoft Shared\\ink\\TabTip.exe";
	QString params = "";
	bool ret = ShellExecute(NULL, L"open", (LPCWSTR)csProcess.utf16(), (LPCWSTR)params.utf16(), NULL, SW_SHOWNORMAL);
	Q_ASSERT(ret);
	return ret;

}

BOOL CDisableWow64FsRedirection::CloseSystemKeyboardTabTip()
{
	HWND pWnd = ::FindWindow(_T("IPTip_Main_Window"), NULL);
	if (pWnd)
	{
		PostMessage(pWnd, WM_CLOSE, 0, 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CDisableWow64FsRedirection::OpenSystemCalculator()
{
    TCHAR szSYSDirectory[MAX_PATH];
    GetSystemDirectory(szSYSDirectory, MAX_PATH);

    HINSTANCE ret;
    if (CDisableWow64FsRedirection::IsWow64Process()) // we run under WOW64
    {
        _tcsncat(szSYSDirectory, _T("\\calc.exe"), MAX_PATH);
        ret = ShellExecute(NULL, _T("open"), _T("explorer"), szSYSDirectory, NULL, SW_SHOW);
    }
    else
    {
        ret = ShellExecute(NULL, _T("open"), _T("calc.exe"), NULL, szSYSDirectory, SW_SHOWNORMAL);
    }

    if ((int)ret > 32)//Execute success!
    {
        for (int i = 0;;i++)
        {
            HWND pWnd = FindWindow(_T("CalcFrame"), NULL);

            if (pWnd)
            {
                if (IsIconic(pWnd))
                    ShowWindow(pWnd, SW_RESTORE);
                SetWindowPos(pWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
                return TRUE;
            }

            if (i == 10)
            {
                return TRUE;
            }

            Sleep(200);
        }

    }
    return FALSE;
}

BOOL CDisableWow64FsRedirection::CloseSystemCalculator()
{
    HWND pWnd  = ::FindWindow(_T("CalcFrame"), NULL);
    if (pWnd)
    {
        PostMessage(pWnd, WM_CLOSE, 0, 0);
        return TRUE;
    }

    return FALSE;
}
#endif


#ifdef linux

QProcess HLinuxSystemTool::m_keyboardProcess;
QProcess HLinuxSystemTool::m_calculatorProcess;
Q_PID    HLinuxSystemTool::m_keyboardProcessId = 0;
Q_PID    HLinuxSystemTool::m_calculatorProcessId = 0;

HLinuxSystemTool::HLinuxSystemTool()
{

};


bool HLinuxSystemTool::openSystemKeyboard()
{

    QProcess::execute("pkill -f onboard");

    //m_keyboardProcess.start("/usr/bin/onboard");
    QProcess::startDetached("/usr/bin/onboard");
    m_keyboardProcessId = m_keyboardProcess.pid();
    return true;

}

bool HLinuxSystemTool::openSystemCalculator()
{
    QProcess::execute("pkill -f gcalctool");

    //m_calculatorProcess.start("/usr/bin/gcalctool");
    QProcess::startDetached("/usr/bin/gcalctool");
    m_calculatorProcessId = m_calculatorProcess.pid();
    return true;

}

bool HLinuxSystemTool::closeSystemKeyboard()
{
    if (m_keyboardProcessId != 0)
    {
        m_keyboardProcess.terminate();
        QProcess::execute("pkill -f onboard");
    }
    m_keyboardProcessId = 0;
    return true;
}

bool HLinuxSystemTool::closeSystemCalculator()
{
    if (m_calculatorProcessId != 0)
    {
        m_calculatorProcess.terminate();
        QProcess::execute("pkill -f gcalctool");
    }
    m_calculatorProcessId = 0;
    return true;
}


#endif




HSystemTool::HSystemTool()
{
}

bool HSystemTool::openSystemKeyboard()
{
    bool result =false;
#ifdef Q_OS_MAC
            QProcess process(0);
            process.execute("killall -9 KeyboardViewer");
            process.startDetached("/System/Library/Input Methods/KeyboardViewer.app/Contents/MacOS/KeyboardViewer",QStringList(""));
            result = true;

#endif

#ifdef WIN32
            CDisableWow64FsRedirection::CloseSystemKeyboard();
            CDisableWow64FsRedirection::OpenSystemKeyboard();
            result = true;
#elif linux

            //m_softkeyProc.start(str);
            result = HLinuxSystemTool::openSystemKeyboard();
#endif
    return result;
}

bool HSystemTool::opensystemCalculator()
{
    bool result =false;
#ifdef Q_OS_MAC
               //QProcess process(0);
               //process.execute("killall -9 Calculator");
               //process.startDetached("/Applications/Calculator.app/Contents/MacOS/Calculator",QStringList(""));
               //process.start("/Applications/Calculator.app/Contents/MacOS/Calculator");
               QProcess::execute("killall -9 Calculator");
               QProcess::execute("open -a Calculator"); //open -a
               //result = QProcess::startDetached("/Applications/Calculator.app/Contents/MacOS/Calculator",QStringList(""));

#endif


#ifdef WIN32
               CDisableWow64FsRedirection::CloseSystemCalculator();
               CDisableWow64FsRedirection::OpenSystemCalculator();
               result = true;
#elif linux

               result = HLinuxSystemTool::openSystemCalculator();

#endif
    return result;
}

bool HSystemTool::openSystemKeyboardTabTip()
{
	bool result = false;
#ifdef Q_OS_MAC
	QProcess process(0);
	process.execute("killall -9 KeyboardViewer");
	process.startDetached("/System/Library/Input Methods/KeyboardViewer.app/Contents/MacOS/KeyboardViewer", QStringList(""));
	result = true;
#endif

#ifdef WIN32
	CDisableWow64FsRedirection::CloseSystemKeyboardTabTip();
	CDisableWow64FsRedirection::OpenSystemKeyboardTabTip();
	result = true;
#elif linux

	//m_softkeyProc.start(str);
	result = HLinuxSystemTool::openSystemKeyboard();
#endif
	return result;
}

bool HSystemTool::closeSystemKeyboard()
{
    bool result = false;
#ifdef Q_OS_MAC
            QProcess process;
            process.execute("killall -9 KeyboardViewer");
            result = true;
            //QProcess processCalculator(0);
            //processCalculator.execute("killall -9 Calculator");
#endif


#ifdef WIN32
            CDisableWow64FsRedirection::CloseSystemKeyboard();
            result = true;
#elif linux
            HLinuxSystemTool::closeSystemCalculator();
            result = true;
#endif
    return result;
}


bool HSystemTool::closeSystemCalculator()
{
    bool result = false;
#ifdef Q_OS_MAC
            QProcess processCalculator(0);
            processCalculator.execute("killall -9 Calculator");
            result = true;
#endif


#ifdef WIN32
            CDisableWow64FsRedirection::CloseSystemCalculator();
            result = true;
#elif linux
            HLinuxSystemTool::closeSystemCalculator();
            result = true;
#endif
    return result;
}

bool HSystemTool::closeSystemKeyboardTabTip()
{
	bool result = false;
#ifdef Q_OS_MAC
	QProcess process;
	process.execute("killall -9 KeyboardViewer");
	result = true;
	//QProcess processCalculator(0);
	//processCalculator.execute("killall -9 Calculator");
#endif

#ifdef WIN32
	CDisableWow64FsRedirection::CloseSystemKeyboardTabTip();
	result = true;
#elif linux
	HLinuxSystemTool::closeSystemCalculator();
	result = true;
#endif
	return result;
}

