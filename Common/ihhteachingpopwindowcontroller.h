#pragma once
#include <QObject>

class IHHConfigManager;
class IHHCloudManager;
class IHHActionsManager;
class IHHScenario;
class IHHControllerManager;

class IHHTeachingPopWindowController
{
public:
    virtual void setIHHConfigManager(IHHConfigManager* manager) = 0;
    virtual void setIHHCloudManager(IHHCloudManager* manager) = 0;
    virtual void setIHHActionsManager(IHHActionsManager* manager) = 0;
    virtual void setIHHControllerManager(IHHControllerManager *manager) = 0;
    virtual void showMainMenu(QVariantMap param) = 0;
    virtual void showMoreWindow(QVariantMap param) = 0;
    virtual void showThumbView(QWidget *TeachingToolbar,QVariantMap param) = 0;
    virtual void showEraserBox(QVariantMap param) = 0;
    virtual void showRoverBox(QVariantMap paran) = 0;
    virtual void showCustumizeBox(QVariantMap param) = 0;
    virtual void showFileShareBox(QVariantMap param) = 0;
    virtual void showPenBox(QVariantMap param) = 0;
    virtual void hideMainToolBar() = 0;
    virtual void ShowMainToolBar() = 0;
    virtual void changeRoveType( QString strType ) = 0; //切换页面漫游方式 by zhangjinlu 20180801
    virtual void updateIndexPageInfo() = 0;
};
Q_DECLARE_INTERFACE(IHHTeachingPopWindowController, "com.hht.qtWhiteBoard.IHHTeachingPopWindowController/1.0")
Q_DECLARE_METATYPE(IHHTeachingPopWindowController*)
