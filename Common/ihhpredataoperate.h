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

    virtual void cloudOpen(QString sFilePath) = 0; //云盘打开
    virtual void localOpen(QString sFilePath, bool bIsRecovery = false) = 0; //本地打开
    virtual void cloudSave(QString sFilePath, bool bSaveAgain, bool bSaveAs = false) = 0; //云盘保存
    virtual void localSave(QString sFilePath, bool bAutoSave, bool bSaveAs = false) = 0; //本地保存
    virtual void localExport(QString sFilePath) = 0; //导出(png/pdf)到本地
    virtual void cloudExport(QString sFilePath, bool bSaveAgain) = 0; //导出(png/pdf)到云盘
    virtual void cloudSaveAndOpen(QString sSaveFilePath, bool bSaveAgain, QString sOpenFilePath) = 0; //保存到云盘之后打开文档
    virtual void localSaveAndOpen(QString sSaveFilePath, QString sOpenFilePath) = 0; //保存到本地之后打开文档
    virtual void cloudSaveAndCreate(QString sSaveFilePath, bool bSaveAgain) = 0; //保存到云盘之后新建文档
    virtual void localSaveAndCreate(QString sSaveFilePath) = 0; //保存到本地之后新建文档
    virtual void cloudSaveAndClose(QString sSaveFilePath, bool bSaveAgain) = 0; //保存到云盘之后关闭软件
    virtual void localSaveAndClose(QString sSaveFilePath) = 0; //保存到本地之后关闭软件
    virtual void createFile() = 0; //创建文档
    virtual void closeFile() = 0; //关闭文档
    virtual QJsonObject TerminateCurLocalTask() = 0; //终止当前耗时操作(本地保存，本地导出)
    virtual void terminateAutoSave(AutoSaveOperate operate) = 0;            //终止自动保存

};
Q_DECLARE_INTERFACE(IHHPreDataOperate, "com.hht.qtWhiteBoard.IHHPreDataOperate/1.0")
Q_DECLARE_METATYPE(IHHPreDataOperate*)
