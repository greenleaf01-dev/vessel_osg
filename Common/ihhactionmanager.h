#pragma once

#include <QObject>

class QAction;
class QString;
class HHCustomAction;

//add by wangyan 2018-01-17 start
class IHHActionManager {
public:
    virtual ~IHHActionManager(){}
    virtual HHCustomAction* getAction( QString strID) = 0;// 得到Action
    virtual void addAction( HHCustomAction *action ) = 0;// 增加Action
};

Q_DECLARE_INTERFACE( IHHActionManager, "com.hht.qtWhiteBoard.IHHActionManager/1.0" )
Q_DECLARE_METATYPE( IHHActionManager* )
// add by wangyan end
