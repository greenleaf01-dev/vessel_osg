#ifndef HHCLASSACTIVITYACTIONFACTORY_H
#define HHCLASSACTIVITYACTIONFACTORY_H

#include "hhscenariocontrolactions_global.h"

class QWidget;
class QObject;
class IHHAction;
class IHHClassActivityHelper;
class IHHClassActivityPrepareController;
class IHHScenario;
class IHHFileOperate;

class HHSCENARIOCONTROLACTIONSSHARED_EXPORT HHClassActivityActionFactory
{
public:
    // 获取课堂互动Helper
    static IHHClassActivityHelper *getClassActivityHelper(
            IHHClassActivityPrepareController *pIHHCtrl,
            IHHFileOperate *pIHHFileOper,
            QWidget *parent = nullptr);

    // 获取课堂互动比对数据Action
    static IHHAction *getModifyActivityMatchDataAction(
            IHHClassActivityHelper *pIHHActivityHelper,
            QObject *parent = nullptr);

    // 获取课堂互动模板Action
    static IHHAction *getModifyActivityTempletAction(
            IHHClassActivityPrepareController *pIHHCtl,
            QObject *parent = nullptr);

    // 填空题题干字号改变改变material尺寸.
    static IHHAction *getGapFillingFontSizeChangeAction(
            IHHScenario *&pCurScenario,
            QObject *parent = nullptr);

    static IHHAction *getShowActivityUIAction(
            IHHClassActivityHelper *pIHHActivityHelper,
            QObject *parent = nullptr);
	static IHHAction *getReplaceItemBackgroundAction(const QString& strId,
		IHHClassActivityHelper *pIHHActivityHelper, IHHFileOperate *pIHHFileOper,
		QObject *parent = nullptr);
};

#endif // HHCLASSACTIVITYACTIONFACTORY_H
