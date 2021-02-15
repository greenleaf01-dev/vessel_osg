/* 课堂活动-容器接口
   liuliyan 2018-06-04 add
*/
#ifndef _IHHACTIVECONTAINERITEM_H_
#define _IHHACTIVECONTAINERITEM_H_

#include <QObject>

class IHHActiveContainerItem
{
public:
	//设置热区背景图片
	virtual void setHotBackground(const QString& strImagePathName) = 0;

	//设置热区初始化图片
	virtual void setInitHotBackground(const QImage& img, const QSize& initSize) = 0;

	//获取热区大小
	virtual QRectF getHotRect() = 0;

	//播放动画
	virtual void playAnimal(int count = 1) = 0;

        // 播放动画过程中切换备课.
        virtual void stopAnimal() = 0;

	//显示热区
	virtual void showHotRect(const QImage  &img) = 0;

	//隐藏热区
	virtual void hideHotRect() = 0;

	//设置热区偏移量
	virtual void setHotOffset(qreal hotOffset) = 0;

	// 填空题专用(获取内部填空的Container保持manager和controller结构复用).
	// controller调用(获取整个container后调用以获取其内维护内部的填空container).
	virtual QList<IHHActiveContainerItem *> getContainers() = 0;
	
	// 填空题专用(内部填空的Container中获取匹配答案的ID).
	virtual QString getContainerID() = 0;

	// 填空题专用.修改文本.
	virtual void setContainerData(const QJsonObject& json) = 0;
	
};

Q_DECLARE_INTERFACE(IHHActiveContainerItem, "com.hht.qtWhiteBoard.IHHActiveContainerItem/1.0")
Q_DECLARE_METATYPE(IHHActiveContainerItem*)

#endif//_IHHACTIVECONTAINERITEM_H_
