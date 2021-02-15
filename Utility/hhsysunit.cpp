#include "hhsysunit.h"
//#include "lib_dpi_sacle.h"


namespace HHSysUnit {
	//计算每毫米对应的逻辑坐标在当前屏幕分辨率和系统dpi下的近似像素值
	float getPixsPerMm() {
		QScreen* pscreen = QGuiApplication::primaryScreen();
		if (pscreen) {
			//获取屏幕的矩形范围（像素值）
			QRect rt1 = pscreen->geometry();

			//获取每英寸的逻辑点（或像素）值,多用于font点尺寸的转换。
			qreal ldp = pscreen->logicalDotsPerInch();
			qreal ldpx = pscreen->logicalDotsPerInchX();
			qreal ldpy = pscreen->logicalDotsPerInchY();

			int xscreenwidth = rt1.width();
			int yscreenheight = rt1.height();

			//计算出水平垂直英寸数值
			float xinch = xscreenwidth*1.0 / ldpx;
			float yinch = yscreenheight*1.0 / ldpy;
			//计算屏幕的对角线英寸数值
			float finch = sqrtf(xinch*xinch + yinch*yinch);

			//计算屏幕对角线的长度值（像素）
			float len = sqrtf(xscreenwidth*xscreenwidth + yscreenheight*yscreenheight);

			//计算出屏幕dpi
			float screendpi = len / finch;

			//计算出系统dpi与屏幕dpi的比值
			float physicunit = ldp*1.0 / screendpi;

			//将该比值乘以（ldp/25.4：每毫米对应的像素值：物理尺寸）得到每毫米对应的逻辑坐标在该分辨率和系统dpi下的近似像素值
			physicunit *= ldp / 25.4;

            //float fScaleDpi = getDpiScaleFactor();
            float fScale = ldp / 96.0;
            physicunit = physicunit/fScale;

			return physicunit;
		}
		else
			return 96 / 25.4;
	}

	float getPixsPerPound() {
		//1磅=25.4mm/72
		return getPixsPerMm()*25.4 / 72;
	}

    QRect getScreenRect() {
        QRect rt;
        QScreen* pscreen = QGuiApplication::primaryScreen();
        if (pscreen) {
            //获取屏幕的矩形范围（像素值）
            rt = pscreen->geometry();
        }
        return rt;
    }

    int getFontSize(){

        QRectF rect=getScreenRect();
        int nWidth = rect.width();
        if (nWidth >= 3840)
            return 6;
        return 8;
    }
}
