#pragma once

#include <QObject>

enum AutoSaveOperate{
    AUTOSAVE_NONE,
    AUTOSAVE_CREATE,
    AUTOSAVE_OPEN,
    AUTOSAVE_SAVE,
    AUTOSAVE_SAVEAS,
    AUTOSAVE_CLOSE_WINDOW
};


class IHHPreFrameController;
class IHHPresentationData;
class IHHPreDataOperate
{
public:
    virtual ~IHHPreDataOperate(){}
    virtual QObject *getObject() = 0;

    virtual void cloudOpen(QString sFilePath) = 0; //���̴�
    virtual void localOpen(QString sFilePath, bool bIsRecovery = false) = 0; //���ش�
    virtual void cloudSave(QString sFilePath, bool bSaveAgain, bool bSaveAs = false) = 0; //���̱���
    virtual void localSave(QString sFilePath, bool bAutoSave, bool bSaveAs = false) = 0; //���ر���
    virtual void localExport(QString sFilePath) = 0; //����(png/pdf)������
    virtual void cloudExport(QString sFilePath, bool bSaveAgain) = 0; //����(png/pdf)������
    virtual void cloudSaveAndOpen(QString sSaveFilePath, bool bSaveAgain, QString sOpenFilePath) = 0; //���浽����֮����ĵ�
    virtual void localSaveAndOpen(QString sSaveFilePath, QString sOpenFilePath) = 0; //���浽����֮����ĵ�
    virtual void cloudSaveAndCreate(QString sSaveFilePath, bool bSaveAgain) = 0; //���浽����֮���½��ĵ�
    virtual void localSaveAndCreate(QString sSaveFilePath) = 0; //���浽����֮���½��ĵ�
    virtual void cloudSaveAndClose(QString sSaveFilePath, bool bSaveAgain) = 0; //���浽����֮��ر����
    virtual void localSaveAndClose(QString sSaveFilePath) = 0; //���浽����֮��ر����
    virtual void createFile() = 0; //�����ĵ�
    virtual void closeFile() = 0; //�ر��ĵ�
    virtual QJsonObject TerminateCurLocalTask() = 0; //��ֹ��ǰ��ʱ����(���ر��棬���ص���)
    virtual void terminateAutoSave(AutoSaveOperate operate) = 0;            //��ֹ�Զ�����

};
Q_DECLARE_INTERFACE(IHHPreDataOperate, "com.hht.qtWhiteBoard.IHHPreDataOperate/1.0")
Q_DECLARE_METATYPE(IHHPreDataOperate*)
