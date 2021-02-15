#pragma once

#include <QMap>
#include <QVariantMap>

class QAction;
class QObject;
class QString;
class QJsonObject;
class HHCustomAction;

// 界面用户行为统计控制
class IHHFrameUserActionController{
public:
    ~IHHFrameUserActionController() {}

    virtual QObject * getObject() = 0;

    virtual void addUserAction(const QString &sActionID) = 0;
    virtual void actionFilter(HHCustomAction *pCustomAction) = 0;
    virtual void addUserAction(const QString &sActionID,
                               const QVariantMap &userInfo) = 0;
    virtual void scenarioChanged(const QVariantMap &infoMap) = 0;
    virtual void initActionFilterInfo(const QVariantMap &filterInfoMap) = 0;

    // 通过App内部ID获取用户行为事件
    virtual QString getUserActionID(const QString &sAppKey) = 0;

    // 通过文件加载用户行为事件
    virtual int loadingUserActionInfo(const QString &sFileName) = 0;
};

Q_DECLARE_INTERFACE( IHHFrameUserActionController,
                     "com.hht.qtWhiteBoard.IHHFrameUserActionController/1.0" )
Q_DECLARE_METATYPE( IHHFrameUserActionController* )
