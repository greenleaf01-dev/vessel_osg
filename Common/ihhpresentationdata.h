#ifndef IHHPRESENTATIONDATA_H
#define IHHPRESENTATIONDATA_H
#include <QObject>

class IHHModel;
class IHHPresentation;

class IHHPresentationData {
public:
    virtual ~IHHPresentationData(){}

    virtual QObject* getObject() = 0;

    //设置文档
    virtual void setPresentation(IHHPresentation *pPresentation) = 0;
    virtual IHHPresentation * getPresentation() = 0;

    //设置Model
    virtual void setModel(IHHModel *pModel) = 0;
    virtual IHHModel * getModel() = 0;

    //设置文件名
    virtual void setFileName(QString sFileName) = 0;
    virtual QString getFileName() = 0;

    //设置文件全路径
    virtual void setFileFullPath(QString sFilePath) = 0;
    virtual QString getFileFullPath() = 0;

    //文件存储类型:本地/云盘
    virtual void setFileStoreType(bool bIsCloud) = 0;
    virtual bool getFileStoreType() = 0;

    //设置是否是编辑状态
    virtual void setEditStatus(bool bEdit) = 0;
    virtual bool getEditStatus() = 0;

    //新建文件/打开文件时清空数据
    virtual void clearData() = 0;

    //新建/打开/保存文件时，文档改变
    virtual void currentPresentationChanged(QString sOpeType) = 0;

    // 设置m_bLoading标志
    virtual void setLoading(bool bLoading) = 0;

    // 是否正在加载数据
    virtual bool isLoading() = 0;

    // 设置m_bSaving标志
    virtual void setSaving(bool bSaving) = 0;

    // 设置m_bAutoSaving标志
    virtual void setAutoSaving(bool bAutoSaving) = 0;

    // 是否正在保存
    virtual bool isSaving() = 0;

    // 是否正在自动保存
    virtual bool isAutoSaving() = 0;

};


Q_DECLARE_INTERFACE( IHHPresentationData, "com.hht.qtWhiteBoard.IHHPresentationData/1.0" )
Q_DECLARE_METATYPE( IHHPresentationData* )

#endif // IHHPRESENTATIONDATA_H
