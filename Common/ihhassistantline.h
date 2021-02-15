/*liuliyan 2017-12-19 add
辅助线接口类*/
#ifndef _IHHASSISTANTLINE_H_
#define _IHHASSISTANTLINE_H_

#include <QPainter>
#include <QVector>
#include <QCursor>
#include <QRectF>

class IHHTransformAction;
class IHHPrimitiveItem;
class IHHCanvas;
class IHHAssistantLine
{
public:
	IHHAssistantLine(){}
	~IHHAssistantLine(){}
	
	//画辅助线
	virtual int paint(QPainter *pPainter, QRectF rect) = 0;
	//IHHPrimitiveItem 对象被按下
    virtual int down(IHHTransformAction* actions, QVector<IHHPrimitiveItem*>& itemList, const QPointF& pos = QPointF()) = 0;
	//IHHPrimitiveItem 对象被移动
    virtual QPointF move(IHHTransformAction* actions, QVector<IHHPrimitiveItem*>& itemList, const QPointF& pos = QPointF()) = 0;
	//IHHPrimitiveItem 对象被释放
    virtual int up(IHHTransformAction* actions, QVector<IHHPrimitiveItem*>& itemList, const QPointF& pos = QPointF()) = 0;
	//设置canvas
	virtual int setCanvas(IHHCanvas *canvas) = 0;
	//获取光标形状
	virtual QCursor getCursor(const QPointF& pos) = 0;
	//设置辅助线颜色名称
	virtual void setAssistantColorName(const QString& strColorName) = 0;
	//设置辅助线是否可用
	virtual int  setEnable(bool bEnable) = 0;

    //add by weijibin 2018.2.6 start
    // creating  AssistantLine
    virtual int downWhenCreating(QVector<IHHPrimitiveItem*>& itemList) = 0;
    virtual int moveWhenCreating(QVector<IHHPrimitiveItem*>& itemList) = 0;
    virtual int upWhenCreating(QVector<IHHPrimitiveItem*>& itemList) = 0;
    //add by weijibin 2018.2.6 end

    virtual void revert() = 0;
	
};
Q_DECLARE_INTERFACE( IHHAssistantLine, "com.hht.qtWhiteBoard.IHHAssistantLine/1.0" )
Q_DECLARE_METATYPE( IHHAssistantLine* )

#endif _IHHASSISTANTLINE_H_
