#pragma once

#include <QObject>
class IHHPresentationData;

class IHHPreFrameController
{
public:
    virtual ~IHHPreFrameController(){}
    virtual QObject *getObject() = 0;

    virtual void setPresentationData(IHHPresentationData  *presData) = 0;
    virtual void closeWindow(bool bFlg=false) = 0; //关闭软件
    virtual QJsonObject askSaving() = 0;
    virtual QJsonObject askTerminateCurTask(QString sType) = 0; //是否要终止当前操作
    virtual void closeTerminateDialog() = 0; //关闭终止对话框(在关闭软件之前，若终止对话框没有关闭)
    virtual QJsonObject openOldVersionSoftware() = 0;
};
Q_DECLARE_INTERFACE(IHHPreFrameController, "com.hht.qtWhiteBoard.IHHPreFrameController/1.0")
Q_DECLARE_METATYPE(IHHPreFrameController*)
