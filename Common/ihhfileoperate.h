#pragma once

#include <QObject>
#include <QWidget>

enum CloudOperateType{
    FILE_OPERATE,     //文件操作
    MEDIA_OPERATE,    //media操作
    PICTURE_OPERATE   //右侧面板导入图片
};

enum FileDialogType{
    FILE_OPEN,
    FILE_SAVE,
    FILE_SAVEAS,
    FILE_INSERT,
    FILE_OTHER      //适合需要传入文件名称的类型
};

enum EnumFileResType
{
    TT_MEDIA_AUDIO,          //音频
    TT_MEDIA_MOVIE,          //视频
    TT_MEDIA_PICTURE,        //图片
    TT_MEDIA_FILE,           //文件
    TT_MEDIA_SHEET,          //表格
    TT_MEDIA_FLASH,          //FLASH
    TT_FILE_PDF,             //文件pdf
    TT_FILE_HHTX,            //文件hhtx
    TT_TOOSCREEN_PNG,        //
    TT_TYPE_FILE_PPT,        //文件ppt
    TT_PEN_PATTEN,           //图案
    TT_NULL,                 //使用自定义过滤器参数
};

class IHHProgressBar;

class IHHFileOperate
{
public:
    virtual ~IHHFileOperate(){}
    virtual QObject *getObject() = 0;

    virtual void setParent(QWidget *pParent) = 0;
    virtual void setCloudOperateType(CloudOperateType type) = 0;   //设置当前云操作功能分类
    virtual void setProgressBar(IHHProgressBar *pProgressBar) = 0; //设置进度条指针-备授课场景切换时需要重新设置
    virtual IHHProgressBar *getProgressBar() = 0;                  //取得当前进度条指针
    virtual void showProgressBar(QString sMessage, QString sTitle = "") = 0;  //显示进度条
    virtual void updateProgressBar(int value) = 0;                 //更新进度条进度值
    virtual void endProgressBar() = 0;                             //隐藏进度条
    virtual int showErrorMessageDialog(QString sError, bool bCancelBtn = false) = 0;        //弹出错误信息提示框
    virtual void showErrorMessageToast(QString sError) = 0;        //弹出toast信息

    //打开文件资源管理器
    virtual QJsonObject showFileDialog(FileDialogType sType, QString sFilePath, QWidget *pParent, EnumFileResType eResFileType, const QString& sTitle, \
                                       bool bMutiSel = false, const QString& sPosition="ID_MY_DOCUMENTS",  const QString& sFilter="") = 0;
    //云盘上传文件
    virtual void cloudUpload(const bool& bReplace,const QString& sLocalPath, const QString& sFid) = 0;
    //云盘下载文件
    virtual void cloudDownload(const QString& sType, const QString& sFilePath,
                               const QString& sTmpPath, const QString& sFileName) = 0;

    //云盘下载文件-多文件下载
    virtual void cloudDownloadMultiFiles(const QString& sFilePath) = 0;

    virtual void cloudUploadMultiFiles(const QStringList& slistLocalPath, const QString& sCloudPath) = 0;

    //终止当前云盘操作
    virtual QJsonObject terminateCurCloudTask() = 0;

};
Q_DECLARE_INTERFACE(IHHFileOperate, "com.hht.qtWhiteBoard.IHHFileOperate/1.0")
Q_DECLARE_METATYPE(IHHFileOperate*)
