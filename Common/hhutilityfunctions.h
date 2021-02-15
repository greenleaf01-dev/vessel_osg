#ifndef HHUTILITYFUNCTIONS_H
#define HHUTILITYFUNCTIONS_H

#include "utility_global.h"
#include <QObject>
#include <QWidget>
#include <QSettings>
class QString;
class HHHotKeyInfo;
class UTILITYSHARED_EXPORT HHUtilityFunctions : public QObject
{
    Q_OBJECT
public:
    HHUtilityFunctions();
    ~HHUtilityFunctions();

public:
    int sendMail(QString filePathName);
    bool executeExe( QString strOperation, QString strExe, QString strParameters, QString strDirectory = QString::null );
    void togglePressAndHold( WId hWnd );
    bool checkUsbDog();
    bool openSystemKeyboard();
    void setForegroundWindow( WId hWnd );
    void setSystemParametersInfo( QString id );
    bool foundEntranceUserOpen();
    static short getWinAsyncKeyState(int nVirtKey);

    /*
     键盘空格键是否正在按下
     */
    bool getSpacePressState();

    QString hotKey_getOneBtnContent(int nSolutionID, int nBtnID);
    int hotKey_initCurrentSolution(int nSolutionID);
    int hotKey_getCurrentSolutionID();
    QString hotKey_getCurrentBtnContent(int nBtnID);
private:
    HHHotKeyInfo            *m_hotKeyInfo;
};

#endif // HHUTILITYFUNCTIONS_H
