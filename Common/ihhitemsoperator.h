#ifndef IHHITEMSOPERATOR_H
#define IHHITEMSOPERATOR_H

#include <QObject>

class IHHItemsOperator {
public:
        virtual ~IHHItemsOperator() {}
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
};

Q_DECLARE_INTERFACE(IHHItemsOperator, "com.hht.qtWhiteBoard.IHHItemsOperator/1.0" )
Q_DECLARE_METATYPE(IHHItemsOperator*)

#endif // IHHITEMSOPERATOR_H
