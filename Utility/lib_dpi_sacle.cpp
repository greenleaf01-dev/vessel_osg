#include "lib_dpi_sacle.h"
#include <QScreen>
#include <QApplication>
#include <atlbase.h>
#define _ATL_NO_HOSTING  1
#include <atlwin.h>
#undef _ATL_NO_HOSTING
/*
增加这个函数的目的主要是为了获得当前系统的dpi的比例。由于用到了win32函数，所以
放到utility里面。
*/
float getDpiScaleFactor()
{
    QScreen *srn = QApplication::screens().at(0);
    qreal dotsPerInch = (qreal)srn->logicalDotsPerInch();
	return dotsPerInch / 96.0;
//	SetProcessDPIAware();
//	HDC hdcScreen = ::GetDC(NULL);
//	float fScreenWidth = ::GetDeviceCaps(hdcScreen, LOGPIXELSX);
//	float fScale = fScreenWidth / 96.0;
//    fScale = fScreenWidth / 96.0;
//    ::ReleaseDC(NULL,hdcScreen);
//	return fScale;
}
