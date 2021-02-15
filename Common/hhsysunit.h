#ifndef HHSYSUNIT_H
#define HHSYSUNIT_H
#include "utility_global.h"
#include <QScreen>
#include <QApplication>
#include <QDebug>


/*
�����ռ� HHSysUnit����wangxianbing ��2017.12.28ʵ��
���ܣ���һ������λÿ��������ֵ���ܺ�����
	  ���������λ�����е�ÿ������ֵ���ܺ�����
ʹ�÷�����
��������Ҫʹ�õĹ�����Ŀpro�ļ��а���·��
INCLUDEPATH += \
../Common \ ��·�����ļ�����Ӧ������ع����޸ġ���

������ڹ�����Ŀpro��̬�����϶�Ӧ��
LIBS += $$PWD/../Bin/Release/X64/Utility.lib��·�����ļ�����Ӧ������ع����޸ġ���

�������Ҫʹ�õĹ�����cpp�ļ��м���
#include "hhsysunit.h"
using namespace HHSysUnit;
���ɵ��ú����磺
int w = 25.4*getPixsPerMm(); �õ�һӢ�������ֵ��
int fontsize = 18*getPixsPerPound(); �õ�18�������Ӧ������ֵ��

*/
namespace HHSysUnit
{
    //����ÿ���׶�Ӧ���߼������ڵ�ǰ��Ļ�ֱ��ʺ�ϵͳdpi�µĽ�������ֵ
	UTILITYSHARED_EXPORT  float getPixsPerMm();

    //��������ÿ����Ӧ���߼������ڵ�ǰ��Ļ�ֱ��ʺ�ϵͳdpi�µĽ�������ֵ
	UTILITYSHARED_EXPORT float getPixsPerPound();

    //��ȡ��Ļ�ľ��η�Χ������ֵ��
    UTILITYSHARED_EXPORT QRect getScreenRect();

    UTILITYSHARED_EXPORT int getFontSize();
};

#endif // HHSYSUNIT_H
