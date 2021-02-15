#ifndef HHCONTROLACTIONSFACTORY_H
#define HHCONTROLACTIONSFACTORY_H

#include "hhscenariocontrolactions_global.h"
#include <QObject>
class IHHControllerManager;
class IHHPresentationData;
class IHHAction;
class IHHPreDataOperate;
class IHHConfigManager;
class IHHCloudManager;
class IHHPreFrameController;
class IHHCanvas;
class IHHScenario;
class IHHPopupWindowController;
class IHHSwitchModuleController;
class IHHTeachingPopWindowController;
class QMenu;
class IHHFileOperate;
class IHHScenarioManager;
class HHTeachingToolbar;
class IHHPresentation;
class IHHMediaHelper;
class IHHMindMapHelper;
class IHHItemAnimationController;
class IHHActionsManager;
class IHHTextHelper;
class IHHFramePluginsController;
class IHHTextHelper;
class IHHDataController;
class IHHActionManager;

class HHSCENARIOCONTROLACTIONSSHARED_EXPORT HHControlActionsFactory : public QObject
{
    Q_OBJECT
public:
	static IHHTextHelper		*getTextHelper(IHHScenario *&curScenario, IHHFramePluginsController *pluginsCtrl, QObject *parent = nullptr);
    static IHHControllerManager *getControllerManager(QObject *pObj = nullptr);
    static IHHPresentationData  *getIHHPresentationData(QObject *pObj = nullptr);
    static IHHFileOperate       *getFileOperate(IHHCloudManager *pCloudManager,
                                             QObject *parent = nullptr);
    static IHHPreDataOperate    *getPreDataOperate(IHHScenario *&curScenario,
                                                   IHHConfigManager *pConfigManager,
                                                   IHHCloudManager  *pCloudManager,
                                                   IHHActionsManager *pActionManager,
                                                   IHHFileOperate *pFileOperate,
                                                   QObject *parent = nullptr);
    //文档操作优化新架构用
    static IHHPreDataOperate    *getPresDataOperate(IHHScenario *&curScenario,
                                                   IHHConfigManager *pConfigManager,
                                                   IHHCloudManager *pCloudManager,
                                                   IHHActionsManager *pActionManager,
                                                   IHHFileOperate *pFileOperate,
                                                   IHHDataController* pDataCtrl,
                                                   QObject *parent = nullptr);
    static IHHAction            *getCloseWindowAction(IHHScenario *&curScenario,
                                                         IHHPreDataOperate *pDataOperate,
                                                         IHHFileOperate *pFileOperate,
                                                         QObject *parent = nullptr);
    static IHHAction            *getInitCreateFileAction(IHHScenario *&curScenario,
                                                         IHHPreDataOperate *pDataOperate,
                                                         QObject *parent = nullptr);
    static IHHAction            *getCreateFileAction(IHHScenario *&curScenario,
                                                     IHHPreDataOperate *pDataOperate,
                                                     IHHFileOperate *pFileOperate,
                                                     QObject *parent = nullptr);
    static IHHAction            *getInitOpenFileAction(IHHScenario *&curScenario,
                                                       IHHPreDataOperate *pDataOperate,
                                                       QObject *parent = nullptr);
    static IHHAction            *getOpenFileAction(IHHScenario *&curScenario,
                                                   IHHPreDataOperate *pDataOperate,
                                                   IHHFileOperate *pFileOperate,
                                                   QObject *parent = nullptr);
    static IHHAction            *getSaveFileAction(IHHScenario *&curScenario,
                                                    IHHPreDataOperate *pDataOperate,
                                                    IHHCloudManager  *pCloudManager,
                                                   IHHFileOperate *pFileOperate,
                                                    QObject *parent = nullptr);
    static IHHAction            *getSaveAsFileAction(IHHScenario *&curScenario,
                                                     IHHPreDataOperate *pDataOperate,
                                                     IHHFileOperate *pFileOperate,
                                                     QObject *parent = nullptr);
    static IHHAction            *getAutoSaveAction(IHHScenario *&curScenario,
                                                   IHHPreDataOperate *pDataOperate,
                                                   QObject *parent = nullptr);

    static IHHAction            *getCopyItemAction(IHHMindMapHelper*mindmaphelper,IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getPasteItemAction(IHHMindMapHelper*mindmaphelper,
		IHHMediaHelper *mediaHelper,
		IHHTextHelper *pTextHelper, 
		IHHScenario *&curScenario,QObject *parent = nullptr);
    //add by wangpan 2018/6/22 pasteitem to Cursor position
    static IHHAction            *getPasteItemActionPos(IHHMindMapHelper*mindmaphelper,IHHMediaHelper *mediaHelper, IHHTextHelper *pTextHelper, IHHScenario *&curScenario,QObject *parent = nullptr);
    //add end

    static IHHAction            *getCtrlVAction(IHHScenario *&curScenario, IHHTextHelper *pTextHelper, QObject *parent = nullptr);

    static IHHAction            *getDeleteItemAction(IHHMindMapHelper*mindmaphelper,IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getDeleteAllItemAction(IHHScenario *&curScenario,IHHSwitchModuleController *pController,QObject *parent = nullptr);

    static IHHAction            *getDeleteStrokesItemAction(IHHScenario *&curScenario,IHHSwitchModuleController *pController,QObject *parent = nullptr);

    static IHHAction            *getCutItemAction(IHHMindMapHelper*mindmaphelper,IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getZOrderPreItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getZOrderNextItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getZOrderTopItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getZOrderBottomItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getRotateLeftItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getRotateRightItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getAlignLeftItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getAlignHCenterItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getAlignRightItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getAlignTopItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getAlignVCenterItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getAlignBottomItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getAlignHJustifyItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getAlignVJustifyItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getMoveUpItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getMoveDownItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getMoveLeftItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getMoveRightItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getFlipAction(QMenu *subMenu,QObject *parent = nullptr);

    static IHHAction            *getFlipVerticalItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getFlipHorizontalItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getMirrorAction(QMenu *subMenu,QObject *parent = nullptr);

    static IHHAction            *getMirrorTopItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getMirrorBottomItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getMirrorLeftItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getMirrorRightItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getUndoAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getRedoAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getLockItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getUnLockItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getGroupItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getUnGroupItemAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getDragCloneAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getCancelDragCloneAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getEditWordAction(IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getSelectAllItemAction(IHHSwitchModuleController *pController,
                                                        IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getItemPropertyChangeAction(IHHScenario *&curScenario,
                                                             QObject *parent = nullptr);
    static IHHAction            *getSlidePropertyChangeAction(IHHScenario *&curScenario,
                                                             QObject *parent = nullptr);
    static IHHAction            *getTextBoxAction(IHHSwitchModuleController *pController, QObject *parent = nullptr);

    static IHHAction            *getShowSettingAction(IHHPopupWindowController *popupCtrl,
                                                      QObject *parent = nullptr);

    static IHHAction            *getShowAboutWidgetAction(IHHPopupWindowController *popupCtrl,
                                                      QObject *parent = nullptr);

    static IHHAction            *getToolWidgetAction(IHHPopupWindowController *popupCtrl,
                                                      QObject *parent = nullptr);

    static IHHAction            *getShowFeedBackWidgetAction(IHHPopupWindowController *popupCtrl,
                                                      QObject *parent = nullptr);

    static IHHAction            *getCanvasScaleWidgetAction(IHHPopupWindowController *popupCtrl,
                                                      QObject *parent = nullptr);

    static IHHAction            *getSlideScaleWidgetAction(IHHPopupWindowController *popupCtrl,
                                                      QObject *parent = nullptr);

    static IHHAction            *getRoamingWidgetAction(IHHPopupWindowController *popupCtrl,
                                                      QObject *parent = nullptr);

    static IHHAction            *getTeachingMethodWidgetAction(IHHPopupWindowController *popupCtrl,
                                                      QObject *parent = nullptr);

    static IHHAction            *getShowSlideAction(IHHScenario *&curScenario,
                                                    QObject *parent = nullptr);

    static IHHAction            *getNewSlideAction(IHHScenario *&curScenario,IHHConfigManager* config,
                                                    QObject *parent = nullptr);

    static IHHAction            *getNextSlideAction(IHHScenario *&pIHHScenario,IHHItemAnimationController* ctrl,
                                                    IHHControllerManager* manager,QObject *parent = nullptr);

    static IHHAction            *getPreSlideAction(IHHScenario *&pIHHScenario,IHHItemAnimationController* ctrl,
                                                    IHHControllerManager* manager,QObject *parent = nullptr);

    static IHHAction            *getMindMapMoveAction(IHHScenario *&curScenario,QString id,QObject *parent = nullptr);

    static IHHAction            *getTeachMainMenuAction(IHHTeachingPopWindowController *controller,QObject * parent);

    static IHHAction            *getPreparingAction(QString strID, IHHScenarioManager *pIHHScenarioManager);

    static IHHAction            *getTeachingAction(QString strID, IHHScenarioManager *pIHHScenarioManager);

    static IHHAction            *getShowTeachMoreWindowAction(IHHTeachingPopWindowController *controller,QObject *parent);

    static IHHAction            *getShowTeachPenBoxAction(IHHTeachingPopWindowController *controller,QObject *parent);

    static IHHAction            *getShowTeachThumbViewAction(HHTeachingToolbar *TeachingToolbar, IHHTeachingPopWindowController *controller, QObject *parent);

    static IHHAction            *getShowTeachEraserBoxAction(IHHTeachingPopWindowController *controller,QObject *parent);

    static IHHAction            *getShowTeachRoverBoxAction(IHHTeachingPopWindowController *controller,QObject *parent);

    static IHHAction            *getShowTeachCustomizeBoxAction(IHHTeachingPopWindowController *controller,QObject *parent);

    static IHHAction            *getShowHideMainToolBarAction(IHHTeachingPopWindowController *controller);

    static IHHAction            *getShowFileShareBoxAction(IHHTeachingPopWindowController *controller,QObject *parent);

    static IHHAction            *getShowCancelLinkAction(IHHPopupWindowController *controller,QObject *parent = nullptr);

    static IHHAction            *getShowLinkAction(IHHPopupWindowController *controller,QObject *parent = nullptr);

    static IHHAction            *getShowEditLinkAction(IHHPopupWindowController *controller,QObject *parent = nullptr);

    static IHHAction            *getLoadHiteVKAction(QWidget *window, IHHConfigManager *cfgManager, QObject *parent);

    static IHHAction            *getLoadHitebridgeAction(QWidget *canvas, IHHConfigManager *cfgManager, QObject *parent);

    static IHHAction            *getLoadHiteCameraAction(QWidget *canvas, IHHCloudManager *cldManager,IHHConfigManager *cfgManager, QObject *parent);

    static IHHAction            *getShortCutDeleteAction(IHHScenario *&curScenario,QObject *parent = nullptr);
    static IHHAction            *getShortCutCopyAction(IHHScenario *&curScenario,QObject *parent = nullptr);
    static IHHAction            *getShortCutPasterAction(IHHScenario *&curScenario,IHHTextHelper* pTextHelper, 
		QObject *parent = nullptr);
    static IHHAction            *getShortCutSelectAllAction(IHHScenario *&curScenario,QObject *parent = nullptr);
    static IHHAction            *getShortCutCutAction(IHHScenario *&curScenario,QObject *parent = nullptr);
    static IHHAction            *getShortCutKeyDownAction(IHHMindMapHelper*mindmaphelper,IHHScenario *&curScenario,QObject *parent = nullptr);
    static IHHAction            *getShortCutKeyUpAction(IHHMindMapHelper*mindmaphelper,IHHScenario *&curScenario,QObject *parent = nullptr);
    static IHHAction            *getShortCutKeyLeftAction(IHHMindMapHelper*mindmaphelper,IHHScenario *&curScenario,QObject *parent = nullptr);
    static IHHAction            *getShortCutKeyRightAction(IHHMindMapHelper*mindmaphelper,IHHScenario *&curScenario,QObject *parent = nullptr);
    static IHHAction            *getShortCutPageDownAction(IHHScenario *&curScenario,QObject *parent = nullptr);
    static IHHAction            *getShortCutPageUpAction(IHHScenario *&curScenario,QObject *parent = nullptr);
    static IHHAction            *getShortCutNewPageAction(IHHMindMapHelper*mindmaphelper,IHHScenario *&curScenario,QObject *parent = nullptr);
    static IHHAction            *getShortCutCtrlPlusAction(IHHScenario *&curScenario,QObject *parent = nullptr);
    static IHHAction            *getShortCutCtrlMinusAction(IHHScenario *&curScenario,QObject *parent = nullptr);
    static IHHAction            *getShortCutF5Action(IHHScenario *&curScenario,IHHFileOperate *pFileOperate,QObject *parent = nullptr);
    static IHHAction            *getShortCutShiftF5Action(IHHScenario *&curScenario,IHHFileOperate *pFileOperate,QObject *parent = nullptr);
    static IHHAction            *getShortCutKeyESCAction(IHHScenario *&curScenario,IHHFileOperate *pFileOperate,QObject *parent = nullptr);
    static IHHAction            *getShortCutKeyTabAction(IHHMindMapHelper*mindmaphelper,IHHScenario *&curScenario,QObject *parent = nullptr);
    static IHHAction            *getShortCutBackSpaceAction(IHHMindMapHelper*mindmaphelper,IHHScenario *&curScenario,QObject *parent = nullptr);

    static IHHAction            *getCopySlideAction(IHHScenario *& presentation);
    static IHHAction            *getCutSlideAction(IHHScenario *&presentation);
    static IHHAction            *getPasteSlideAction(IHHScenario *& presentation);
    static IHHAction            *getDeleteSlideAction(IHHScenario *& presentation);
    static IHHAction            *getMoveUpSlideAction(IHHScenario *& presentation);
    static IHHAction            *getMoveDownSlideAction(IHHScenario *&presentation);
    static IHHAction            *getMoveTopSlideAction(IHHScenario *& presentation);
    static IHHAction            *getMoveBottomSlideAction(IHHScenario *&presentation);

    // 获取通用工具
    static IHHAction            *getGeneralToolAction(IHHFileOperate *pFileOperate, IHHMediaHelper *pIHHMediaHelper,
                                                      IHHScenario *&scenario, IHHActionsManager *am,
                                                      QObject *parent = nullptr);
    static IHHAction            *getCustomShortCutKeyAction(IHHConfigManager * CM
                                                            ,IHHActionsManager *AM, QObject * parent = nullptr );

    static IHHAction            *getShowMinMaxAction(IHHScenario **scenario,QObject * parent = nullptr);

};

#endif // HHCONTROLACTIONSFACTORY_H
