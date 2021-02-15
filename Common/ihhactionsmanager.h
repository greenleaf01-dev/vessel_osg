#pragma once

#include <QObject>

class QAction;
class QString;
class IHHAction;

//add by wangyan 2018-01-17 start
class IHHActionsManager {
public:
    virtual ~IHHActionsManager(){}
    virtual IHHAction* getAction( QString strID) = 0;// 得到Action
    virtual void addAction( IHHAction *action ) = 0;// 增加Action
};

Q_DECLARE_INTERFACE( IHHActionsManager, "com.hht.qtWhiteBoard.IHHActionsManager/1.0" )
Q_DECLARE_METATYPE( IHHActionsManager* )
// add by wangyan end
