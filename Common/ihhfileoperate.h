#pragma once

#include <QObject>
#include <QWidget>

enum CloudOperateType{
    FILE_OPERATE,     //�ļ�����
    MEDIA_OPERATE,    //media����
    PICTURE_OPERATE   //�Ҳ���嵼��ͼƬ
};

enum FileDialogType{
    FILE_OPEN,
    FILE_SAVE,
    FILE_SAVEAS,
    FILE_INSERT,
    FILE_OTHER      //�ʺ���Ҫ�����ļ����Ƶ�����
};

enum EnumFileResType
{
    TT_MEDIA_AUDIO,          //��Ƶ
    TT_MEDIA_MOVIE,          //��Ƶ
    TT_MEDIA_PICTURE,        //ͼƬ
    TT_MEDIA_FILE,           //�ļ�
    TT_MEDIA_SHEET,          //���
    TT_MEDIA_FLASH,          //FLASH
    TT_FILE_PDF,             //�ļ�pdf
    TT_FILE_HHTX,            //�ļ�hhtx
    TT_TOOSCREEN_PNG,        //
    TT_TYPE_FILE_PPT,        //�ļ�ppt
    TT_PEN_PATTEN,           //ͼ��
    TT_NULL,                 //ʹ���Զ������������
};

class IHHProgressBar;

class IHHFileOperate
{
public:
    virtual ~IHHFileOperate(){}
    virtual QObject *getObject() = 0;

    virtual void setParent(QWidget *pParent) = 0;
    virtual void setCloudOperateType(CloudOperateType type) = 0;   //���õ�ǰ�Ʋ������ܷ���
    virtual void setProgressBar(IHHProgressBar *pProgressBar) = 0; //���ý�����ָ��-���ڿγ����л�ʱ��Ҫ��������
    virtual IHHProgressBar *getProgressBar() = 0;                  //ȡ�õ�ǰ������ָ��
    virtual void showProgressBar(QString sMessage, QString sTitle = "") = 0;  //��ʾ������
    virtual void updateProgressBar(int value) = 0;                 //���½���������ֵ
    virtual void endProgressBar() = 0;                             //���ؽ�����
    virtual int showErrorMessageDialog(QString sError, bool bCancelBtn = false) = 0;        //����������Ϣ��ʾ��
    virtual void showErrorMessageToast(QString sError) = 0;        //����toast��Ϣ

    //���ļ���Դ������
    virtual QJsonObject showFileDialog(FileDialogType sType, QString sFilePath, QWidget *pParent, EnumFileResType eResFileType, const QString& sTitle, \
                                       bool bMutiSel = false, const QString& sPosition="ID_MY_DOCUMENTS",  const QString& sFilter="") = 0;
    //�����ϴ��ļ�
    virtual void cloudUpload(const bool& bReplace,const QString& sLocalPath, const QString& sFid) = 0;
    //���������ļ�
    virtual void cloudDownload(const QString& sType, const QString& sFilePath,
                               const QString& sTmpPath, const QString& sFileName) = 0;

    //���������ļ�-���ļ�����
    virtual void cloudDownloadMultiFiles(const QString& sFilePath) = 0;

    virtual void cloudUploadMultiFiles(const QStringList& slistLocalPath, const QString& sCloudPath) = 0;

    //��ֹ��ǰ���̲���
    virtual QJsonObject terminateCurCloudTask() = 0;

};
Q_DECLARE_INTERFACE(IHHFileOperate, "com.hht.qtWhiteBoard.IHHFileOperate/1.0")
Q_DECLARE_METATYPE(IHHFileOperate*)
