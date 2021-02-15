#ifndef HSYSTEMTOOL_H
#define HSYSTEMTOOL_H

#include <QtCore/QProcess>

#ifdef WIN32
#define _UNICODE
#include <windows.h>
#include <tchar.h>

typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS)(HANDLE, PBOOL);
typedef BOOL (WINAPI *LPFN_WOW64DISABLEWOW64FSREDIRECTION)(PVOID*);
typedef BOOL (WINAPI *LPFN_WOW64REVERTWOW64FSREDIRECTION)(PVOID);

class CDisableWow64FsRedirection
{
public:
    CDisableWow64FsRedirection();
    ~CDisableWow64FsRedirection();

    static BOOL IsEnableUAC();
    static BOOL IsWow64Process(HANDLE hProcess = NULL);
    static BOOL DisableWow64FsRedirection(PVOID* pOldValue);
    static BOOL RevertWow64FsRedirection(PVOID OldValue);
    static BOOL OpenSystemKeyboard();
    static BOOL CloseSystemKeyboard();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Opens system keyboard tab tip. </summary>
	///
	/// <remarks>	Gan Songlin, 2017/10/30. </remarks>
	///
	/// <returns>	True if it succeeds, false if it fails. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static BOOL OpenSystemKeyboardTabTip();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Closes system keyboard tab tip. </summary>
	///
	/// <remarks>	Gan Songlin, 2017/10/30. </remarks>
	///
	/// <returns>	True if it succeeds, false if it fails. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static BOOL CloseSystemKeyboardTabTip();
    static BOOL OpenSystemCalculator();
    static BOOL CloseSystemCalculator();

public:
    BOOL bIsWOW64;
    BOOL bDisabled;
protected:
    LPVOID oldValue;
    static LPFN_ISWOW64PROCESS fnIsWow64Process;
    static LPFN_WOW64DISABLEWOW64FSREDIRECTION fnWow64DisableWow64FsRedirection;
    static LPFN_WOW64REVERTWOW64FSREDIRECTION  fnWow64RevertWow64FsRedirection;
};
#endif


#ifdef linux

   class HLinuxSystemTool
   {
   public:
       HLinuxSystemTool();
       static bool openSystemKeyboard();
       static bool openSystemCalculator();
       static bool closeSystemKeyboard();
       static bool closeSystemCalculator();
   private:
       static QProcess m_keyboardProcess;
       static QProcess m_calculatorProcess;
       //startDetached
       //qint64 * pid = 0

       static Q_PID m_keyboardProcessId;
       static Q_PID m_calculatorProcessId;
   };

#endif


class HSystemTool
{
public:
    HSystemTool();
    static bool openSystemKeyboard();
	static bool opensystemCalculator();
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Opens system keyboard ex. </summary>
	///
	/// <remarks>	Gan Songlin, 2017/10/30. </remarks>
	///
	/// <returns>	True if it succeeds, false if it fails. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static bool openSystemKeyboardTabTip();
    static bool closeSystemKeyboard();
    static bool closeSystemCalculator();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Opens system keyboard tab tip. </summary>
	///
	/// <remarks>	Gan Songlin, 2017/10/30. </remarks>
	///
	/// <returns>	True if it succeeds, false if it fails. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static bool closeSystemKeyboardTabTip();
};

#endif // HSYSTEMTOOL_H
