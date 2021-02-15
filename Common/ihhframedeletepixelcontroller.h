#pragma once

#include <QObject>
#include <QVariant>

class QString;
class IHHCanvas;

// Delete Pixel控制
class IHHFrameDeletePixelController {
public:
    ~IHHFrameDeletePixelController() {}

    virtual void setCurrentIHHCanvas(IHHCanvas *pIHHCanvas) = 0;

    virtual QObject *getObject() = 0;

    virtual void setParameters(const QString &sType, const QVariant &value) = 0;
    virtual QVariant getParameters(const QString &sType) const = 0;

    virtual void setParameters(const QVariantMap &valMap) = 0;
    virtual QVariantMap getParameters() const = 0;

    virtual void createPixelDelete() = 0;
    // 清页
    virtual void clearAllInfo() = 0;
    // 清除笔迹
    virtual void clearItemStrokes() = 0;

    // 初始化橡皮数据
    virtual void initDeletePixelModuleDataInfo(const QVariantMap &info) = 0;
};

Q_DECLARE_INTERFACE(IHHFrameDeletePixelController, "com.hht.qtWhiteBoard.IHHFrameDeletePixelController/1.0")
Q_DECLARE_METATYPE( IHHFrameDeletePixelController* )
