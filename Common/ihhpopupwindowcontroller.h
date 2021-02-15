#pragma once

#include <QObject>
class IHHConfigManager;
class IHHCloudManager;
class IHHActionsManager;

class IHHPopupWindowController
{
public:
    virtual ~IHHPopupWindowController(){}
    virtual QObject *getObject() = 0;

    virtual void setIHHConfigManager(IHHConfigManager* manager) = 0;
    virtual void setIHHCloudManager(IHHCloudManager* manager) = 0;
    virtual void setIHHActionsManager(IHHActionsManager* manager) = 0;

    virtual void showSettingWidget() = 0;

    virtual void showShapeSelectWidget(QVariantMap param) = 0;

    virtual void showFeedBackWidget() = 0;

    virtual void showAboutWidget() = 0;

    virtual void showToolWidget() = 0;

    virtual void showCanvasScaleWidget(QVariantMap param) = 0;

    virtual void showSlideScaleWidget(QVariantMap param) = 0;

    virtual void showRoamingWidget(QVariantMap param) = 0;

    virtual void showTeachingMethodWidget(QVariantMap param) = 0;

    virtual void showMediaSelectWidget(QVariantMap param) = 0;

    virtual void showLinkDlg(bool cancelFlag) = 0;

    virtual void showMindmapWidget(QVariantMap param) = 0;

    virtual void selectAllSlides() = 0;
};
Q_DECLARE_INTERFACE(IHHPopupWindowController, "com.hht.qtWhiteBoard.IHHPopupWindowController/1.0")
Q_DECLARE_METATYPE(IHHPopupWindowController*)
