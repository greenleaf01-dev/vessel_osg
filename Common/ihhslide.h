#ifndef IHHSLIDE_H
#define IHHSLIDE_H
#include <QObject>
#include <QVariantMap>
#include <QVector>
#include <QGraphicsItem>
#include <QString>
#include <QVariant>
#include <QJsonObject>
#include "ihhcurtainitem.h"
#include "ihhactivitymanage.h"

//
#include "ihhimagecollectionx.h"

class IHHPresentation;
class IHHPrimitiveItem;
class IHHItemAnimationsSlideManager;
class HHCommand;

// 特效类型 - strType
// "EFFECT_NO"			   - 无
// "EFFECT_NEWSEXPRESS"    - 新闻快报
// "EFFECT_SCALE"          - 缩放
// "EFFECT_UNCOVER"        - 揭开
// "EFFECT_CUTOUT"         - 切出
// "EFFECT_FADEOUT"        - 淡出
// "EFFECT_PROMOTE"        - 推进
// "EFFECT_COVER";         - 覆盖

// 特效方向 - strDirection
// "NO"						- 无
// "UP"						- 向上
// "DOWN"					- 向下
// "LEFT"					- 向左
// "RIGHT"					- 向右
// "LEFTUP"					- 左上
// "LEFTDOWN"				- 左下
// "RIGHTUP"				- 右上
// "RIGHTDOWN"				- 右下
// "SMOOTH"					- 平滑淡出
// "BLACKMID"				- 黑中淡出
// "ENLARGE"				- 放大
// "NARROW"					- 缩小

// 页面特效
struct Effect {
	//
	QString strType;		// 特效类型
	int nTime;				// 持续时间
	QString strDirection;	// 特效方向
};

class IHHSlide {
public:
	virtual ~IHHSlide() {}

	//
	virtual IHHSlide* clone() = 0;

	// 增加Item
	virtual void addPrimitiveItem(IHHPrimitiveItem *item, bool bCmd = true) = 0;
	
	//
	virtual void deleteItems(QVector< IHHPrimitiveItem* > items) = 0;
	virtual void updatePrimitiveItems(QVector< IHHPrimitiveItem* > items, QVariantMap param) = 0;
	//virtual void setParameters(QString type, QVariant value) = 0;
	//virtual QVariant getParameters(QString type) = 0;
	virtual QVector< IHHPrimitiveItem* > getItems() = 0;
	virtual QVector< IHHPrimitiveItem* > getItemsByID(QStringList list) = 0;
	virtual void saveToImage(QString strName, QRectF rangeRect, int width, int height, QString imgType) = 0;
	virtual QObject* getObject() = 0;
	virtual IHHPresentation* getPresentation() = 0;

	// ================================ Load/Save Item ===================================
	// Save - 外部调用
	virtual void getJSONObj(QJsonObject& jsonObj) = 0;
	
	// Load - 外部调用
	virtual void fromJSONObj(QJsonObject& jsonObj) = 0;

    virtual void fromJSONObj2(QJsonObject& jsonObj) = 0;
	
	// 设置用于LoadData()的缓存数据
	virtual void setJsonData(QJsonObject& jsonData) = 0;

	// 加载Slide内部缓存数据 - m_jsonData
	virtual void LoadData() = 0;

	// ================================ 获取Item =================================
	// 根据区域选择Item
	virtual QList< QGraphicsItem* > getQItemsByPath(QPainterPath path, QVariantMap param) = 0;

	// 获得QPainterPath中Items
	virtual QVector< IHHPrimitiveItem* > getItems(QPainterPath *path) = 0;

	// 删除QPainterPath中Items
	virtual void deleteItems(QPainterPath *path) = 0;

	// ================================ 选中Item =================================

	// 增加新选中的Item
	virtual void appendSelItems(QVector< IHHPrimitiveItem* > & items) = 0;

	// 用新选中的Item替换原来选中的Item
	virtual void replaceSelItems(QVector< IHHPrimitiveItem* > & items) = 0;

	// 从新选中的Item中移除Item
	virtual void removeSelItems(QVector< IHHPrimitiveItem* > & items) = 0;

	// 获取选中的Items	
	// 返回值：当前选中Item
	virtual QVector< IHHPrimitiveItem* > & getSelItems() = 0;

	// 清除选中的Items
    virtual void clearSelItems() = 0;

	// ============================== 画缩略图 =================================
	// 向painter画缩略图
	virtual void drawThumnail(QPainter *painter, const QRectF &rect) = 0;

	// 更新rect区域
	virtual void refresh(const QRectF &rect, bool bUpdateThumnail = false) = 0;

	//
	virtual void setClipRect(QRectF rect) = 0;

	// ============================= 背景图 ================================

	// 设置背景颜色
	virtual void setBacColor(QString strBackColor) = 0;

	// 获取背景颜色
	virtual QString getBacColor() = 0;

	// 加载背景文件,生成背景图
    virtual void setBackFile(QString strBackFile,bool isLoad = false) = 0;

	// 设置背景文件MD5文件名
	virtual void setBackMd5File(QString strMd5File) = 0;

	// 获取背景文件MD5文件名
	virtual QString getBackMd5File() = 0;

    //获取背景文件全路径
    virtual QString getBackFilePath() = 0;

    //设置背景文件全路径
    virtual void setBackFilePath(QString path) = 0;

	// 加载背景图片
	virtual void setBackPic(QPixmap pixBack) = 0;

	// 获取背景图片
	virtual QPixmap getBackPic() = 0;

	// ImageCollection
	//virtual void setImageCollection(IHHImageCollectionX *pHImageCollection) = 0;

	// ============================= Slide参数 ================================
	// 是否加载数据
	virtual bool isLoaded() = 0;

	// 设置显示比例
    virtual void changeProportionScale(QPointF point, float xRate, float yRate) = 0;
    virtual void changeProportionTranslate(float xOffset, float yOffset) = 0;

	// 获取Slide的标示ID
	virtual QString getID() = 0;

	// ================= 编辑 ===============
	// copy item
	// 剪切板格式："hhtitem:slide_id;item_id_1,item_id_2,item_id_3"
	virtual bool copyItem() = 0;

	// paste Item
	// 剪切板格式："hhtitem:slide_id;item_id_1,item_id_2,item_id_3"
	// 返回 - 粘贴后生成的Item
	virtual QVector< IHHPrimitiveItem* > pasteItemFromClipboard() = 0;

	// 按坐标位置Paste
	// 剪切板格式："hhtitem:slide_id;item_id_1,item_id_2,item_id_3"
	// pos - paste的位置
	// 返回 - 粘贴后生成的Item
	virtual QVector< IHHPrimitiveItem* > pasteItemFromClipboard(QPoint pos) = 0;

	// paste Item
	// itemsSrc:源item
	// posStart : paste的item从这个起始位置开始排列。当其发生改变时，重新排列。
	// 返回：新生成的paste item
	virtual QVector< IHHPrimitiveItem* > pasteItem(QVector< IHHPrimitiveItem* > &itemsSrc, QPoint posStart) = 0;

	// 布局Paste item.
	// itemPaste:已生成的paste item
	// posStart : paste的item从这个起始位置开始排列。当其发生改变时，重新排列。
	// 返回：布局item的位置
	virtual QPoint arrangePasteItem(IHHPrimitiveItem* itemPaste, QPoint posStart) = 0;

	// cut Item
	// 剪切板格式："hhtitem:slide_id;item_id_1,item_id_2,item_id_3"
	// cut后的剪切板格式: "hhtitem:0;0,0,0" - id都为"0"
	virtual bool cutItem() = 0;

	// 删除Item
	virtual bool deleteItem() = 0;

	// 全选Item
	virtual bool selectAllItem() = 0;

	// 通过ID删除Item
	// id == "ID_ITEM_DELETE_STROKES"  - 删除所有笔迹
	// id == "ID_ITEM_DELETE_ALL"	   - 删除所有item
	virtual void deleteItems(QString id) = 0;

	// 直接创建item，不经过cmd
	virtual void addCreatedItem(IHHPrimitiveItem *item) = 0; // add by weijibin 创建时添加item

	//
	virtual void removeCreatedItem(IHHPrimitiveItem *item) = 0; // add by weijibin 创建时添加item

	// ================= 移动 ===============

	// 移动Item
	// strType = "ID_ITEM_MOVE_UP"		: 向上
	// strType = "ID_ITEM_MOVE_DOWN"	: 向下
	// strType = "ID_ITEM_MOVE_LEFT"	: 向左
	// strType = "ID_ITEM_MOVE_RIGHT"	: 向右
	virtual bool moveItems(QString strType) = 0;

	// ================= 镜像 ===============
	// 镜像Item
	// strType = "ID_HH_ITEM_MIRROR_TOP"	: 向上镜像
	// strType = "ID_HH_ITEM_MIRROR_BOTTOM" : 向下镜像
	// strType = "ID_HH_ITEM_MIRROR_LEFT"	: 向左镜像
	// strType = "ID_HH_ITEM_MIRROR_RIGHT"	: 向右镜像
	virtual bool mirrorItems(QString strType) = 0;

	// ================= 翻转 ===============

	// 翻转Item
	// strType = "ID_ITEM_FLIP_HOR"	: 水平
	// strType = "ID_ITEM_FLIP_VER"	: 垂直
	virtual bool flipItems(QString strType) = 0;

	// ================= 锁定 ===============
	// 锁定Item
	virtual int lockItem() = 0;

	// 取消锁定Item
	virtual int unlockItem() = 0;

	// ================= z-order ===============

	// z-order Items
	// strType = "ID_HH_ITEM_EDIT_ZORDER_TOP"		: z-top
	// strType = "ID_HH_ITEM_EDIT_ZORDER_BOTTOM"	: z-bottom
	// strType = "ID_HH_ITEM_EDIT_ZORDER_PRE"		: z-up Item
	// strType = "ID_HH_ITEM_EDIT_ZORDER_NEXT"		: z-down Item
	virtual bool zorderItems(QString strType) = 0;

	// ================= 组合 ===============
	// 组合Item
	virtual int groupItem() = 0;

	// 取消组合Item
	virtual int ungroupItem() = 0;

	// ================= 对齐 ===============

	// 对齐Item
	// strType = "ID_AlignLeft"		: 左对齐
	// strType = "ID_AlignRight"	: 右对齐
	// strType = "ID_AlignHCenter"	: 左右居中
	// strType = "ID_AlignHJustify"	: 水平等距
	// strType = "ID_AlignTop"		: 向上对齐
	// strType = "ID_AlignBottom"	: 向下对齐
	// strType = "ID_AlignVCenter"	: 上下居中
	// strType = "ID_AlignVJustify"	: 垂直等距Item
	virtual bool alignItems(QString strType) = 0;

	// ================= 左右转 ===============
	// 转动items
	virtual bool rotateItems(float fAngle) = 0;

	// ================================ 幕布 =================================
	// 增加幕布
	virtual void addCurtianItem(IHHCurtainItem *curtian) = 0;

	// 删除幕布
	virtual void removeCurtianItem(IHHCurtainItem *curtian) = 0;

	// 获取幕布
	virtual QVector< IHHCurtainItem* > & getCurtianItem() = 0;

	// 幕布是否存在
	virtual bool isCurtianExist() = 0;

	// ============================= 页面特效 ================================
	// 设置特效
	virtual void setEffect(Effect effect) = 0;

	// 取得特效
	virtual Effect getEffect() = 0;

	// ============================= item特效 ================================
    virtual IHHItemAnimationsSlideManager* getAnimationSlideManager() = 0;
    virtual void setAnimationSlideManager(IHHItemAnimationsSlideManager* manager) = 0;
    //设置item名称
    virtual void setItemName(IHHPrimitiveItem* item) = 0;

	// ============================= 页面漫游 ================================
public:
	// 设置页面漫游matrix
	virtual void setMatrix(QMatrix matrix) = 0;

	// 获得页面漫游matrix
	virtual QMatrix getMatrix() = 0;

	// 重置页面漫游matrix
	virtual void resetMatrix() = 0;

    // 处理item 内部生成的命令
    virtual void addItemsLocalCommand(HHCommand *cmd) = 0;

	// ============================= 课堂活动 ================================
	// 获取课堂互动
	virtual IHHActivityManage *getActivityManage() = 0;

	// 0 - normal slide
	// 1 - activity slide
	virtual int getType() = 0;
};

Q_DECLARE_INTERFACE(IHHSlide, "com.hht.qtWhiteBoard.IHHSlide/1.0" )
Q_DECLARE_METATYPE(IHHSlide*)

#endif // IHHSLIDE_H
