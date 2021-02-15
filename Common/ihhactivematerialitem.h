/* 课堂活动-材料接口
   liuliyan 2018-06-04 add
*/
#ifndef _IHHACTIVEMATERIALITEM_H_
#define _IHHACTIVEMATERIALITEM_H_

#include <QObject>

class IHHActiveMaterialItem
{
public:
	//吸附
	virtual void abentsort(const QRectF& rect) = 0;
	// 分类题,错误答案弹回.
	virtual void undoAbentsort(const QRectF& rect) = 0;

	//移到指定位置
	virtual void tanslateAnimal(qreal offsetX, qreal offsetY) = 0;

	// 填空题显示对错.
	virtual void showResult(bool) = 0;
	virtual void hideResult() = 0;
};

Q_DECLARE_INTERFACE(IHHActiveMaterialItem, "com.hht.qtWhiteBoard.IHHActiveMaterialItem/1.0")
Q_DECLARE_METATYPE(IHHActiveMaterialItem*)

#endif//_IHHACTIVEMATERIALITEM_H_
