#pragma once

#include <QObject>

class QWidget;

// 界面通用工具控制
class IHHFrameGeneralToolController{
public:
    ~IHHFrameGeneralToolController(){}
    virtual QObject *getObject() = 0;

    virtual void getGeneraTool(const QString &sToolID,
                               const QVariantMap &args,
                               QWidget *parent = 0) = 0;
};

Q_DECLARE_INTERFACE( IHHFrameGeneralToolController,
                     "com.hht.qtWhiteBoard.IHHFrameGeneralToolController/1.0" )
Q_DECLARE_METATYPE( IHHFrameGeneralToolController* )
