#ifndef HHSYSUNIT_H
#define HHSYSUNIT_H
#include "utility_global.h"
#include <QScreen>
#include <QApplication>
#include <QDebug>


/*
命名空间 HHSysUnit，由wangxianbing 于2017.12.28实现
功能：其一，物理单位每毫米像素值功能函数。
	  其二，物理单位字体中的每磅像素值功能函数。
使用方法：
首先在需要使用的工程项目pro文件中包含路径
INCLUDEPATH += \
../Common \ （路径，文件名对应项由相关工程修改。）

其次再在工程项目pro静态链接上对应库
LIBS += $$PWD/../Bin/Release/X64/Utility.lib（路径，文件名对应项由相关工程修改。）

最后在需要使用的工程类cpp文件中加入
#include "hhsysunit.h"
using namespace HHSysUnit;
即可调用函数如：
int w = 25.4*getPixsPerMm(); 得到一英寸的像素值。
int fontsize = 18*getPixsPerPound(); 得到18磅字体对应的像素值。

*/
namespace HHSysUnit
{
    //计算每毫米对应的逻辑坐标在当前屏幕分辨率和系统dpi下的近似像素值
	UTILITYSHARED_EXPORT  float getPixsPerMm();

    //计算字体每磅对应的逻辑坐标在当前屏幕分辨率和系统dpi下的近似像素值
	UTILITYSHARED_EXPORT float getPixsPerPound();

    //获取屏幕的矩形范围（像素值）
    UTILITYSHARED_EXPORT QRect getScreenRect();

    UTILITYSHARED_EXPORT int getFontSize();
};

#endif // HHSYSUNIT_H
