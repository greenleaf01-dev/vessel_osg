/* 课堂活动item
   liuliyan 2018-06-04 add
*/
#ifndef _IHHACTIVEITEM_H_
#define _IHHACTIVEITEM_H_

#include <QString>
#include <QImage>

class IHHActiveItem
{
public:
	IHHActiveItem(){}
	~IHHActiveItem(){}
	
	//设置背景图片
	virtual void setBackground(const QString& strBackImagePath) = 0;
	
	//获取背景图片
	virtual QString getBackgroundPath() = 0;
	virtual QImage getBackgroundImage() = 0;
	
	//设置item数据
	virtual void setAllData(QJsonObject &info) = 0;
	
	//设置模板数据
	virtual void setTemplateData(QJsonObject &info) = 0;

	//设置文本内容
	virtual void setText(const QString& strText) = 0;
	
	//获取文本内容
	virtual QString getText() = 0;

        //记录当前boundingbox
        virtual void recordBoundingRect() = 0;

        //恢复上一次记录的boundingbox
        virtual void restoreBoundingRect() = 0;

        //显示对象
        virtual void show() = 0;

        //隐藏对象
        virtual void hide() = 0;

        //设置显示标志
        virtual void setShowEnable(bool showEnable) = 0;

        //获取显示标志
        virtual bool getShowEnable() = 0;
};

Q_DECLARE_INTERFACE(IHHActiveItem, "com.hht.qtWhiteBoard.IHHActiveItem/1.0")
Q_DECLARE_METATYPE(IHHActiveItem*)
Q_DECLARE_METATYPE(QList< IHHActiveItem* >)
Q_DECLARE_METATYPE(QVector< IHHActiveItem* >)

#endif//_IHHACTIVEITEM_H_
