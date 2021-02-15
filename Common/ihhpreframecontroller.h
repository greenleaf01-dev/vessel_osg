#pragma once

#include <QObject>
class IHHPresentationData;

class IHHPreFrameController
{
public:
    virtual ~IHHPreFrameController(){}
    virtual QObject *getObject() = 0;

    virtual void setPresentationData(IHHPresentationData  *presData) = 0;
    virtual void closeWindow(bool bFlg=false) = 0; //�ر����
    virtual QJsonObject askSaving() = 0;
    virtual QJsonObject askTerminateCurTask(QString sType) = 0; //�Ƿ�Ҫ��ֹ��ǰ����
    virtual void closeTerminateDialog() = 0; //�ر���ֹ�Ի���(�ڹر����֮ǰ������ֹ�Ի���û�йر�)
    virtual QJsonObject openOldVersionSoftware() = 0;
};
Q_DECLARE_INTERFACE(IHHPreFrameController, "com.hht.qtWhiteBoard.IHHPreFrameController/1.0")
Q_DECLARE_METATYPE(IHHPreFrameController*)
