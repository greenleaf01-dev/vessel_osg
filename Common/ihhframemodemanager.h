/*liuliyan 2017-12-27 add
����ģʽ����ӿ���*/
#ifndef _IHHFRAMEMODEMANAGER_H_
#define _IHHFRAMEMODEMANAGER_H_

#include <QString>

class IHHFrameMode;

class IHHFrameModeManager
{
public:
	IHHFrameModeManager() {}
	~IHHFrameModeManager() {}
	virtual int setFrameMode(const QString& strMode, IHHFrameMode * pFrame) = 0;	//ת��ģʽ
	virtual IHHFrameMode * getFrameMode(const QString& strMode) = 0;				//��ȡ��ǰģʽ����
	virtual QString getFrameMode() = 0;												//��ȡ��ǰ��ģʽ
};

#endif _IHHFRAMEMODEMANAGER_H_
