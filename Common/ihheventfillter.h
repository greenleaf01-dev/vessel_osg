/*************************************************
Copyright:honghe-tech
Author: mike.heng
Date:2017-12-25
Description:事件过滤接口
**************************************************/
#ifndef _IHHEVENTFIFLLTER_H_
#define _IHHEVENTFIFLLTER_H_

#include <QObject>
#include <QMouseEvent>
#include <QTouchEvent>
#include "hhtouchpoint.h"

class IHHCanvas;
//
//事件过滤后通过 IHHCanvas：：outFillterEvent输出，并在其实现中调用事件缓存
//
class IHHEventFillter
{
public:
    /*************************************************
    Function:       //  setCanvas
    Description:    // 设置画布
    Input:          // 输入参数说明，包括每个参数的作
                    // 用、取值说明及参数间关系。
    Output:         // 对输出参数的说明。
    Return:         // 0成功：非0为错误码
    Others:         // 其它说明
    *************************************************/
    virtual int setCanvas(IHHCanvas *canvas) = 0;
	
    /*************************************************
    Function:       //  onTouchEvent
    Description:    // 视图事件
    Input:          // mouseEvent 事件对象指针
                    // 用、取值说明及参数间关系。
    Output:         // 对输出参数的说明。
    Return:         // true:false
    Others:         // 其它说明：详细信息参照Qt文档
    *************************************************/
    virtual bool onTouchEvent(QTouchEvent *touchEvent) = 0;
    virtual void resetTouch0EventForPopupMenu( QTouchEvent *touchEvent, HHTouchPoint& touchPoint ) = 0;

    /*************************************************
    Function:       //  onMousePressEvent
    Description:    // 鼠标按下事件
    Input:          // mouseEvent 事件对象指针
                    // 用、取值说明及参数间关系。
    Output:         // 对输出参数的说明。
    Return:         // true:false
    Others:         // 其它说明：详细信息参照Qt文档
    *************************************************/
    virtual void onMousePressEvent(QMouseEvent *mouseEvent) = 0;

    /*************************************************
    Function:       //  onMouseMoveEvent
    Description:    // 鼠标移动事件
    Input:          // event 事件对象指针
                    // 用、取值说明及参数间关系。
    Output:         // 对输出参数的说明。
    Return:         // void
    Others:         // 其它说明 ：详细信息参照Qt文档
    *************************************************/
    virtual void onMouseMoveEvent(QMouseEvent *mouseEvent) = 0;

    /*************************************************
    Function:       //  onMouseReleaseEvent
    Description:    // 鼠标释放事件
    Input:          // mouseEvent 事件对象指针
                    // 用、取值说明及参数间关系。
    Output:         // 对输出参数的说明。
    Return:         // void
    Others:         // 其它说明：详细信息参照Qt文档
    *************************************************/
    virtual void onMouseReleaseEvent(QMouseEvent *mouseEvent) = 0;


    /*************************************************
    Function:       //  onMouseDoubleClickEvent
    Description:    // 鼠标双击事件
    Input:          // mouseEvent 事件对象指针
                    // 用、取值说明及参数间关系。
    Output:         // 对输出参数的说明。
    Return:         // void
    Others:         // 其它说明：详细信息参照Qt文档
    *************************************************/
    virtual void onMouseDoubleClickEvent(QMouseEvent *mouseEvent) = 0;

    virtual void release() = 0;

    virtual void resetEnvironment() = 0;
};
Q_DECLARE_INTERFACE( IHHEventFillter, "com.hht.qtWhiteBoard.IHHEventFillter/1.0" )
Q_DECLARE_METATYPE( IHHEventFillter* )

#endif//
