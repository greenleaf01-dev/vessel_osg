#ifndef IHHSCENARIO_H
#define IHHSCENARIO_H

#include <QObject>
#include <QWidget>

class IHHPresentationData;
class IHHActionsManager;
class IHHControllerManager;
class IHHConfigManager;
class IHHCloudManager;
class IHHCanvas;
class IHHPreFrameController;

//根据触发源分类
struct HHScenarioData
{
   IHHPresentationData* preData =NULL;
   QString curPenMoudle ="ID_ITEM_STROKE_CHALK";
};

class IHHScenario{
public:
    ~IHHScenario() {}

    virtual void initScenario(QJsonObject param,IHHPresentationData* data) = 0;
    virtual void showScenario(QJsonObject param) = 0;
    virtual void hideScenario() = 0;

    //数据签入、签出
    virtual void checkInScenario(HHScenarioData data) = 0;
    virtual HHScenarioData checkOutScenario() = 0;

    //ActionManage设置、获取
    virtual void setActionManager(IHHActionsManager *pActionManager) = 0;
    virtual IHHActionsManager* getActionManager() = 0;

    //ControllManage设置、获取
    virtual void setControllerManager(IHHControllerManager *pCtrlManager) = 0;
    virtual IHHControllerManager* getControllerManager() = 0;

    //ConfigManage设置、获取
    virtual void setConfigManager(IHHConfigManager *pConfigManager) = 0;
    virtual IHHConfigManager* getConfigManager() = 0;

    //CloudManage 设置
    virtual void setCloudManager(IHHCloudManager *pCloudManager) = 0;

    //获取场景ID
    virtual QString getScenarioID() = 0;

    //获取当前场景Canvas
    virtual IHHCanvas* getIHHCanavs() = 0;

    //获得场景中主窗口
    virtual QWidget* getMainUI() = 0;

    virtual IHHPreFrameController* getPreFrameCtrl() = 0;
    virtual IHHPresentationData* getPreData() = 0;

    //接受命令行参数
    virtual void receiveCommandLine(QJsonObject param) = 0;
};
Q_DECLARE_INTERFACE( IHHScenario, "com.hht.qtWhiteBoard.IHHScenario/1.0" )
Q_DECLARE_METATYPE( IHHScenario* )

#endif // IHHFRAMEITEMCONTROLLER_H
