#pragma once

#include <QObject>

class IHHProgressBar
{
public:
    virtual ~IHHProgressBar(){}
    virtual QObject *getObject() = 0;

    virtual void showProgressBar(QString sMessage, QString sTitle = "") = 0; //显示进度条 sTitle:授课对话框标题用
    virtual void updateProgressBar(int value) = 0; //更新进度条信息
    virtual void endProgressBar() = 0; //隐藏进度条

    //以下函数是备授课切换时调用函数
    virtual void setBusyStatus(bool bFlg) = 0;
    virtual bool getIsBusy() = 0;
    virtual int getCurProgressValue() = 0; //增加该接口的原因：备授课切换时，如果正好进度条不再发送新的value值，那么切换后，进度值会为0
    virtual void setCurProgressValue(int nValue) = 0;
    virtual void setWidgetVisible(bool bVisible) = 0;
    //说明：进度条的标题文字是在showProgressBar()时传入，但是备授课切换时，存在接收不到showProgressBar的情况，因此将标题保存
    virtual QString getMessage() = 0;
    virtual QString getTitle() = 0;
    virtual void setMessage(QString sMessage) = 0;
    virtual void setTitle(QString sTitle) = 0;

};

Q_DECLARE_INTERFACE(IHHProgressBar, "com.hht.qtWhiteBoard.IHHProgressBar/1.0")
Q_DECLARE_METATYPE(IHHProgressBar*)
