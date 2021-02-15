#pragma once

#include <QObject>

class IHHFramePreController
{
public:
    virtual ~IHHFramePreController(){}
    virtual QObject *getObject() = 0;

    virtual void createFile() = 0;
    virtual void saveFile() = 0;
    virtual void saveAsFile() = 0;
    virtual void terminateSaving() = 0;//add by zhangjinlu 2018/03/27 �ļ���������У��ر��������ֹ�ļ�����
    virtual void terminateUploading() = 0;//add by zhangjinlu 2018/04/11 �ļ��ϴ������̹����У��ر��������ֹ�ļ��ϴ�
    virtual void terminateDownloading() = 0;//add by zhangjinlu 2018/04/11 �ļ����������ع����У��ر��������ֹ�ļ�����
    virtual void closeFile() = 0;
    virtual void openFile(const QString &sFileName = "") = 0;

    // ����
    virtual void editUnDo() = 0;
};
Q_DECLARE_INTERFACE(IHHFramePreController, "com.hht.qtWhiteBoard.IHHFramePreController/1.0")
Q_DECLARE_METATYPE(IHHFramePreController*)
