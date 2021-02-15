/*liuliyan 2017-12-19 add
参考线接口类*/
#ifndef _IHHPARAMTERSLINE_H_
#define _IHHPARAMTERSLINE_H_

#include <QVector>
#include <QCursor>
#include <QRectF>
#include <QVariantMap>

class IHHTransformAction;
class IHHPrimitiveItem;
class IHHCanvas;

#define PARAMTERPICK_DIFF 5

class IHHParamtersLine
{
public:
	IHHParamtersLine(){}
	~IHHParamtersLine(){}
	
	//画参考线
	virtual int paint(QPainter *pPainter, QRectF rect) = 0;	
	//mousePress或touchBegin
	virtual int down(const QPointF& pos) = 0;
	//mouseMove或touchUpdate
	virtual int move(const QPointF& pos) = 0;
	//mouseRelease或touchEnd
	virtual int up(const QPointF& pos) = 0;
	//设置canvas对象
	virtual int setCanvas(IHHCanvas *canvas) = 0;
	//获取光标形状
	virtual QVariantMap getCursor(const QPointF& pos) = 0;
	//获取参考线数据列表
        virtual bool  getParametersLine(qreal& hPos, qreal& vPos) = 0;
	//设置参考线是否处于可用状态
	virtual int  setEnable(bool bEnable) = 0;
	//判断光标是否在参考线上
	virtual int isPickByPoint(const QPointF& pos) = 0;
	//设置参考线上的光标图像路径
	virtual void setImageDir(const QString& strImageDir) = 0;
        virtual int revert() = 0;
};
Q_DECLARE_INTERFACE( IHHParamtersLine, "com.hht.qtWhiteBoard.IHHParamtersLine/1.0" )
Q_DECLARE_METATYPE( IHHParamtersLine* )

#endif _IHHPARAMTERSLINE_H_
