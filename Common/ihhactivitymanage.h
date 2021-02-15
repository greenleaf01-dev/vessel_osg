#ifndef IHHACTIVITY_H
#define IHHACTIVITY_H

#include <QJsonObject>
#include <QVector>
#include "classactivity\ihhframeActivitycontroller.h"
#include "ihhprimitiveItem.h"

// Item位置
struct ItemPos {
	QString strID;
	int xPos;
	int yPos;
};

#if 1
// 屏幕类型
enum SCREEN_TYPE {
	//
	SCREEN_1920_1080,
	SCREEN_4K,
	SCREEN_1280_720,
};
#endif

//
struct MatchItem
{
	QString strID;
	QString strTxt;
};

//
struct ActivityMatch
{
	//
	MatchItem Container;
	QVector<MatchItem> vMaterials;
};

//
struct ItemInfo
{
	// 文本背景图片
	QString strBackFile;

	// 热区图片
	QString strHotFile;
	QString strHotoffset;

	// 大小
	QRectF rect;

	// 文本内容
	QString strTxt;

	// 文本属性
	QString strFontSize;
	QString strFontFamily;
	QString strFontColor;
	QString strFontAlign;
	QString strOffsetup;
};

//
struct TempletInfo {
	//
	QString strBack;		// 背景色("#****") or 背景图片
	QString strIndex;
	QString strTemplateName;

	// Material 
	ItemInfo ItemInfoMaterial;

	// Container
	ItemInfo ItemInfoContainer;
};

//
struct DelItem
{
	QString strID;
	IHHPrimitiveItem* item;
};

class IHHActivityManage {
public:
    virtual ~IHHActivityManage() {}

    // ==================== load/save ========================
    // 加载jsonObj数据，生成ActivityItem
    virtual void load(QJsonObject& jsonObj) = 0;

    // 保存ActivityItem到jsonObj
    virtual void save(QJsonObject& jsonObj) = 0;

    // 设置Json数据
    virtual void setData(QJsonObject& jsonObj) = 0;

    // 获得Json数据
    virtual void getData(QJsonObject& jsonObj) = 0;

    // ==================== match ========================
    // 检查match
    virtual bool check(QString strContainerID, QString strMaterialID) = 0;

    // 从Json生成Match数据
    virtual void setMatchData(QJsonObject& jsonObj) = 0;

    // 从Match数据生成Json
    virtual void getMatchData(QJsonObject& jsonObj) = 0;

	// 设置计时
	virtual void setCountdown(bool bCountdown) = 0;

	// 获取计时
	virtual bool getCountdown() = 0;

	// 设置计时时间
	virtual void setCountdownTime(int nTime) = 0;

	// 获取计时时间
	virtual int getCountdownTime() = 0;

    // ==================== 模板 ========================
    // 根据模板Json修改Slide和ActivityItem属性
    virtual void setTempletData(QJsonObject& jsonObj) = 0;

    // 根据Slide和ActivityItem属性生成模板数据
    virtual void getTempletData(QJsonObject& jsonObj) = 0;

	// 获取模板索引
	virtual QString getTempletIndex() = 0;

	// ==================== 声音 ========================
	// 设置声音
	virtual void setAudio(bool bAudio) = 0;

	// 声音
	virtual bool getAudio() = 0;

	// ==================== 布局 ========================

	// 布局
	virtual void arrangeItems() = 0;

	// 设置Items位置
	virtual void restoreMaterialItemPos() = 0;

	// 获得Items位置
    virtual void recordMaterialItemPos() = 0;

	//获取备份位置
	virtual void setBakMaterialItemPos(QVector<ItemPos> &vItemPos) = 0;
	virtual void getBakMaterialItemPos(QVector<ItemPos> &vItemPos) = 0;

    // ==================== 参数 ========================
    // 获取Activity类型
    virtual QString getType() = 0;

	// 获取ActivityItem的大小
	virtual QSizeF getItemSize() = 0;

	// 获取Material
	virtual IHHPrimitiveItem * getMaterialItem(QString strID) = 0;

    // 设置IHHFrameActivityController
    virtual void setControler(IHHFrameActivityController *pController) = 0;

	// 获取IHHFrameActivityController
    virtual IHHFrameActivityController *getController() = 0;

    // 获取Material和containter
    virtual QVector<IHHPrimitiveItem*> getItems() = 0;

	// 趣味竞赛专用.
	// 获取所有组对错item.(0 error, 1 correct)
	virtual QList<QList<QPair<int,IHHPrimitiveItem*>>> getAllItemLists() = 0;
	// 被授课切换绘制对象背景和组背景.
	virtual void setTeachMode(bool) = 0;
	virtual bool isTeachMode() = 0;

	virtual void setContainerHaveItems(QMap<QString, QStringList> map) = 0;
	virtual void getContainerHaveItems(QMap<QString, QStringList> &map) = 0;
};
#endif // IHHACTIVITY_H
