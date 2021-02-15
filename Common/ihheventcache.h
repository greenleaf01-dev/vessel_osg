/*************************************************
Copyright:honghe-tech
Author: mike.heng
Date:2017-12-28
Description:事件缓存接口
**************************************************/

#ifndef _IHHEVENTCACHE_H_
#define _IHHEVENTCACHE_H_

#include <QTouchEvent>
#include "hhtouchpoint.h"

class IHHCanvas;
//
//事件缓存与转发；在IHHCanvas：：outFillterEvent中调用； IHHEventCache：：onEvent;缓存后通过调用IHHCanvas的相关方法转发。
//
class IHHEventCache
{
public:
    virtual void setLongPressPopupMenuEnable( bool bEnable ) = 0;
    virtual int setCanvas(IHHCanvas *canvas) = 0;
    virtual int onTouchEventCache(QTouchEvent *touchEvent,HHTouchPoint& point) = 0;
    virtual void release() = 0;
};
Q_DECLARE_INTERFACE( IHHEventCache, "com.hht.qtWhiteBoard.IHHEventCache/1.0" )
Q_DECLARE_METATYPE( IHHEventCache* )

#endif// _IHHEVENTCACHE_H_
