#pragma once
#include <QObject>
#include <QWidget>

class IHHImageViewer{
public:
    ~IHHImageViewer(){}
    virtual QWidget *           getWidget() = 0;
    virtual void                init(const QVariantMap &params) = 0;
    virtual void                setImageViewConfig(const QString &sFlieID,
                                                   const QString &sFilePath,
                                                   const QString &sFileType) = 0;
    virtual QString             getFIleID() = 0;
    virtual void                setDistributeText(QString sText) = 0;
    virtual void                setBtnIsShow(bool bIsShow) = 0;
};
Q_DECLARE_INTERFACE( IHHImageViewer, "com.hht.qtWhiteBoard.IHHImageViewer/1.0" )
Q_DECLARE_METATYPE( IHHImageViewer* )
