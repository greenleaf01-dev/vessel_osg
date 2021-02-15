/*liuliyan 2017-12-19 add
�ο��߽ӿ���*/
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
	
	//���ο���
	virtual int paint(QPainter *pPainter, QRectF rect) = 0;	
	//mousePress��touchBegin
	virtual int down(const QPointF& pos) = 0;
	//mouseMove��touchUpdate
	virtual int move(const QPointF& pos) = 0;
	//mouseRelease��touchEnd
	virtual int up(const QPointF& pos) = 0;
	//����canvas����
	virtual int setCanvas(IHHCanvas *canvas) = 0;
	//��ȡ�����״
	virtual QVariantMap getCursor(const QPointF& pos) = 0;
	//��ȡ�ο��������б�
        virtual bool  getParametersLine(qreal& hPos, qreal& vPos) = 0;
	//���òο����Ƿ��ڿ���״̬
	virtual int  setEnable(bool bEnable) = 0;
	//�жϹ���Ƿ��ڲο�����
	virtual int isPickByPoint(const QPointF& pos) = 0;
	//���òο����ϵĹ��ͼ��·��
	virtual void setImageDir(const QString& strImageDir) = 0;
        virtual int revert() = 0;
};
Q_DECLARE_INTERFACE( IHHParamtersLine, "com.hht.qtWhiteBoard.IHHParamtersLine/1.0" )
Q_DECLARE_METATYPE( IHHParamtersLine* )

#endif _IHHPARAMTERSLINE_H_
