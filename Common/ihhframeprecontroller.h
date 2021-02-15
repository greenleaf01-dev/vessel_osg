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
    virtual void terminateSaving() = 0;//add by zhangjinlu 2018/03/27 文件保存过程中，关闭软件，终止文件保存
    virtual void terminateUploading() = 0;//add by zhangjinlu 2018/04/11 文件上传到云盘过程中，关闭软件，终止文件上传
    virtual void terminateDownloading() = 0;//add by zhangjinlu 2018/04/11 文件从云盘下载过程中，关闭软件，终止文件下载
    virtual void closeFile() = 0;
    virtual void openFile(const QString &sFileName = "") = 0;

    // 撤销
    virtual void editUnDo() = 0;
};
Q_DECLARE_INTERFACE(IHHFramePreController, "com.hht.qtWhiteBoard.IHHFramePreController/1.0")
Q_DECLARE_METATYPE(IHHFramePreController*)
