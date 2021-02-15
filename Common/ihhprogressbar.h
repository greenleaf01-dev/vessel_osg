#pragma once

#include <QObject>

class IHHProgressBar
{
public:
    virtual ~IHHProgressBar(){}
    virtual QObject *getObject() = 0;

    virtual void showProgressBar(QString sMessage, QString sTitle = "") = 0; //��ʾ������ sTitle:�ڿζԻ��������
    virtual void updateProgressBar(int value) = 0; //���½�������Ϣ
    virtual void endProgressBar() = 0; //���ؽ�����

    //���º����Ǳ��ڿ��л�ʱ���ú���
    virtual void setBusyStatus(bool bFlg) = 0;
    virtual bool getIsBusy() = 0;
    virtual int getCurProgressValue() = 0; //���Ӹýӿڵ�ԭ�򣺱��ڿ��л�ʱ��������ý��������ٷ����µ�valueֵ����ô�л��󣬽���ֵ��Ϊ0
    virtual void setCurProgressValue(int nValue) = 0;
    virtual void setWidgetVisible(bool bVisible) = 0;
    //˵�����������ı�����������showProgressBar()ʱ���룬���Ǳ��ڿ��л�ʱ�����ڽ��ղ���showProgressBar���������˽����Ᵽ��
    virtual QString getMessage() = 0;
    virtual QString getTitle() = 0;
    virtual void setMessage(QString sMessage) = 0;
    virtual void setTitle(QString sTitle) = 0;

};

Q_DECLARE_INTERFACE(IHHProgressBar, "com.hht.qtWhiteBoard.IHHProgressBar/1.0")
Q_DECLARE_METATYPE(IHHProgressBar*)
