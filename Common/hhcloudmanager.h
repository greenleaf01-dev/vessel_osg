#ifndef HHCLOUDMANAGER_H
#define HHCLOUDMANAGER_H

#include <QObject>
#include <QTimer>
#include <QVariant>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include "ihhcloudcenter.h"
class HHUserInfoAndOperator;
class HmCloudCommon;
class HHUserActionManager;
class HHShareClassFile;
class HHCloudOperatorManager;
class HHConfigOperator;
class HHShareClassFileManager;
class IHHFrameMediaController;
class MainWindowPreAndTeaching;
class HHLocalSocketClient;
class HHLocalSocketServer;
#include "cloudcenter_global.h"
class CLOUDCENTERSHARED_EXPORT HHCloudManager : public QObject, public IHHCloudManager
{
public:
    Q_OBJECT
public:
    explicit HHCloudManager(QObject *parent = nullptr);
    virtual QObject *getObject();
    virtual QString getUserInfo(QString type);
    virtual IHmCloudComm *getCloudComm();
    virtual void getLoginWindow(double m_windowScale);
    virtual void setLoginWidgetParent(QWidget *LoginWidgetParent);
    virtual void getLoginWindow(double m_windowScale,QWidget *m_PreAndTeaching);
    virtual void UploadConfig(QString FilePath,QString version);//上传文件路径，请求版本
    virtual void DownloadConfig(QString FilePath,QString version);//下载到文件路径，请求版本
    virtual IHHUserActionManager *getUserActionManager();
    virtual IHHUserActionManager *getUserActionManager(QString appKey,QString appName,QString appVersion,QString uid);
    virtual void dealHiteBoardLoginOperator(QString type,QString params);
    virtual IHHCloudOperatorManager *getCloudOperatorManager(QString appKey,QString appName);
    virtual void setCurrentInfo(QString type,QString value);//获取临时与用户有关的信息
    virtual QString getCurrentInfo(QString type);
    virtual void setUserInfo(QString m_strUserInfo);
    void initUserInfo(QString m_strUserInfo);//,QString frameUserType,QString frameUserTemp,QString frameSubjectType,QString frameSubjectTemp 初始化用户信息
    virtual void parseInsertResInfo(QString InsertResType,QString InsertResTemp,QString InsertInfo);//预处理资源信息
    void dealLoginoutInfo(QString m_strUserInfo,QString frameUserType,QString frameUserTemp,QString frameSubjectType,QString frameSubjectTemp); //从入口接收预处理退出信息
    void initUserActionAppInfo();
    virtual void setFrameMediaController(IHHFrameMediaController *m_FrameMediaController);
    virtual IHHShareClassFileManager *getShareClassFileManager(QString appKey,QString appName);
    void setWidgetScale(double widgetScale);
    void initUserActionAppInfo(QString appKey,QString appName,QString appVersion,QString uid);
    QString getAppKey();
    QString getAppName();
    QString getAppVersion();
    QString getUid();
    QString getLibrarydir();
    void setLibrarydir(QString dir);
    void Log(QString txtPath,QString message);
    void getUserInfoBySocket();
    void closeLoginWindow();
public:
   static HHCloudManager *getInstance();

signals:
    void sigStateChanged(QString, QVariant, QVariant);
    void sigLoginStateChanged(bool);//true登陆 false 退出
    void sigDownloadConfigResult(bool bExit,bool bSuccess);
    void sigUploadConfigResult(bool bSuccess);
    void sigSocketDataReceived(QString userInfo);


    /*云盘*/
    void signalFileCosStatus(int nRet, const QString& bucket);
    void resultReady(int nRet, const QString& strFileUrl);
    void sglgetFileAndFolderInfo(QJsonObject);
    void sglHttpNetError(QString);
    void sglHttpRequestFinish(QString , QJsonObject, QString);
    void sglHttpAuthenticateError();//当计算机时间与标准时间相差很远时提示授权失败
    void sglHttpConnectError(int);
    void signalDownloadFinished(int);
    void slgdownloadtimeout();//下载超时
    void slghttptimeout();//http get 超时

protected slots:
    // come from main GUI App
    void sltStateChanged(QString, QVariant, QVariant);
    void sltDownloadConfigResult(bool bExit,bool bSuccess);
    void sltUploadConfigResult(bool bSuccess);
    void sltgoToEntranceForLogin( QString type,QString jsonObj);

    void sltDataReceived(QString userInfo);
    void sltSocketResult(int result);
    void sltUserInfoClientConnect(QString type);
private:
    HHUserInfoAndOperator *m_userinfoAndOperator;
    HmCloudCommon  *m_CloudComm;
    HHUserActionManager *m_userActionManager;
    HHShareClassFile *m_shareClassFile;
    HHCloudOperatorManager *m_hhcloudoperator;
    HHShareClassFileManager *m_hhShareClassFileManager;
    HHConfigOperator *m_hhconfigoperator;
    QString appKey;
    QString appName;
    QString appVersion;
    int uploadSize;
    QString uid;
    IHHFrameMediaController *m_FrameMediaController;
    double m_widgetScale;
    QString m_Librarydir;//SDK类库目录
    QWidget *m_LoginWidgetParent;

    HHLocalSocketClient *m_hhlocalsocketClient;

    HHLocalSocketServer *m_localSocketServer;
};
extern "C"
{
__declspec(dllexport) void __stdcall initLibraryDir(char* dir);
__declspec(dllexport)  void  __stdcall initUserActionAppInfo(char* appKey,char* appName,char* appVersion,char* m_uid);
__declspec(dllexport)   void __stdcall  AddUserActionByQueue(char* eventid,char* customJsonContent);
__declspec(dllexport)  void  __stdcall submitOpinions(char* content,char* userinfo,char* uid,SubmitOpinionCallBack OpinionCallBack);
__declspec(dllexport)   void  __stdcall UploadFileForShareCode(char* JsonContent,FileForShareCodeCallBack shareCodeCallBack);
__declspec(dllexport)   void  __stdcall checkUserinfoLegality(char* uid,char* token,CheckUserInfoCallBack checkUserInfoCallBack);

}
#endif // HHCLOUDMANAGER_H
