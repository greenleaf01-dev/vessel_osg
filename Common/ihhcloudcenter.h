#pragma once
#include <QObject>
#include <QJsonObject>
#include "Windows.h"
//add by hangaowei 2018-02-6 start
typedef void (CALLBACK *CheckUserInfoCallBack)(bool flag);//true false
typedef void (CALLBACK *SubmitOpinionCallBack)(bool flag);//true false
typedef void (CALLBACK *FileForShareCodeCallBack)(bool flag,double progress);//flag是否成功,progress进度
class IHHFrameMediaController;
class IHHCloudOperatorManager
{
public:
    ~IHHCloudOperatorManager(){}
    virtual QObject *getObject() = 0;
    virtual void saveUserFeedBack(QString ContactInfo,QString options,QString uid)= 0;
    virtual void saveUserFeedBack(QString appKey,QString appName,QString ContactInfo,QString options,QString uid)= 0;
    virtual void saveUserFeedBack(QString appKey,QString appName,QString ContactInfo,QString options,QString uid,SubmitOpinionCallBack OpinionCallBack)= 0;
    virtual void insertResDownload(QString fileUrl,QString localDir,QString fileName)= 0;
    virtual void checkUserInfoLegality(QString uid,QString token)= 0;
    virtual void checkUserInfoLegality(QString uid,QString token,CheckUserInfoCallBack checkUserInfoCallBack)= 0;
};
class IHHUserActionManager {
public:
    ~IHHUserActionManager(){}
    virtual QObject *getObject() = 0;
    virtual void AddActionByQueue(QString eventid,QJsonObject customJsonContent)= 0;
    virtual void AddActionByQueue(QJsonObject ActionObject)= 0;
    virtual void AddActionByQueue(QString eventid,QString customJsonContent)= 0;
};
class IHmCloudComm{
public:
    ~IHmCloudComm(){}
    virtual QObject *getObject() = 0;
    virtual void uploadingFileUpgrade(bool bReplace,QString localPath,QString remotePath) = 0;//fid
    virtual void uploadingFile(bool bReplace,const QString& localpath,const QString& fid, const QString& bucket) = 0;
    virtual void getFileAndFolderInfo(QString fid) = 0;
    virtual void downloadFile(const QString& type, const QString& strfUrl,const QString& strTmpPath, const QString& F_ID) = 0;
    virtual void stopDownloadFile() = 0;
    virtual void stopUploadingFile() = 0;
    virtual void checkOverwrite(QString bucket,QString strfUrl, QString strTmpPath) = 0;
    virtual void uploadingFileByList(QJsonObject infos) = 0;
    virtual void downloadFileByList(QJsonArray fileList) = 0;
    virtual void stopDownloadFileList() = 0;
    virtual void stopUploadingFileList() = 0;
    virtual void createFolder(QString pfid,QString foldername)=0;
};
class IHHShareClassFileManager
{
public:
    ~IHHShareClassFileManager(){}
    virtual QObject *getObject() = 0;
    virtual void UploadFileForShareCodeByCurl(QString JsonString,FileForShareCodeCallBack shareCodeCallBack)= 0;
    virtual void UploadFileForShareCode(QJsonObject fileParams)= 0;
    virtual void onUploadFileImages(QJsonObject fileParams)= 0;
    virtual void onUploadFileInfoDB(QJsonObject fileParams)= 0;
    virtual void onCheckFileIsUpload(QString md5)= 0;
    virtual void onSetCodePath(QString _CodePath)= 0;
    virtual void onDeleteWork()= 0;
};
class IHHCloudManager {
public:
    ~IHHCloudManager(){}
    virtual QObject *getObject() = 0;
    virtual IHHUserActionManager *getUserActionManager() = 0;//QString appKey,QString appName,QString appVersion
    virtual IHHUserActionManager *getUserActionManager(QString appKey,QString appName,QString appVersion,QString uid) = 0;
    virtual IHmCloudComm *getCloudComm() = 0;
    virtual void dealHiteBoardLoginOperator(QString type,QString params) = 0;
    virtual QString getUserInfo(QString type) = 0;//type: uid,subjectName,gradeName,studySectionSubject,token,subjectID,userName,userAvator,previousUid
    virtual void setCurrentInfo(QString type,QString value) = 0;//获取临时与用户有关的信息
    virtual QString getCurrentInfo(QString type) = 0;
    virtual void getLoginWindow(double m_windowScale) = 0;
    virtual void setLoginWidgetParent(QWidget *LoginWidgetParent)= 0;
    virtual void getLoginWindow(double m_windowScale,QWidget *m_PreAndTeaching) = 0;
    virtual void setFrameMediaController(IHHFrameMediaController *m_FrameMediaController)= 0;
    virtual void UploadConfig(QString FilePath,QString version) = 0;//上传文件路径，请求版本
    virtual void DownloadConfig(QString FilePath,QString version) = 0;//下载到文件路径，请求版本
    virtual IHHCloudOperatorManager *getCloudOperatorManager(QString appKey,QString appName) = 0;
    virtual IHHShareClassFileManager *getShareClassFileManager(QString appKey,QString appName) = 0;
    virtual void setUserInfo(QString m_strUserInfo)= 0;
    virtual void parseInsertResInfo(QString InsertResType,QString InsertResTemp,QString InsertInfo) = 0;//预处理资源信息
};
// add by hangaowei end

