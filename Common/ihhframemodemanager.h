/*liuliyan 2017-12-27 add
窗口模式管理接口类*/
#ifndef _IHHFRAMEMODEMANAGER_H_
#define _IHHFRAMEMODEMANAGER_H_

#include <QString>

class IHHFrameMode;

class IHHFrameModeManager
{
public:
	IHHFrameModeManager() {}
	~IHHFrameModeManager() {}
	virtual int setFrameMode(const QString& strMode, IHHFrameMode * pFrame) = 0;	//转换模式
	virtual IHHFrameMode * getFrameMode(const QString& strMode) = 0;				//获取当前模式对象
	virtual QString getFrameMode() = 0;												//获取当前课模式
};

#endif _IHHFRAMEMODEMANAGER_H_
