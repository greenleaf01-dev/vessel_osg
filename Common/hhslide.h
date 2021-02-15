#ifndef HHSLIDE_H
#define HHSLIDE_H

#include "lib_global.h"
#include "hhspecialitemsmanager.h"
#include "ihhslidedirectoperator.h"
#include <QGraphicsScene>
#include <QVariantList>
#include "ihhslide.h"
#include "ihhactivitymanage.h"
#include "hhitemsoperator.h"

class QJsonObject;
class QRectF;
class IHHPrimitiveItem;
class HHPresentation;
class QLabel;
class QGraphicsPixmapItem;

//class TreeModel;
class HHItemEffects;

// 
class HHSelectCenter;
class IHHTransformAction;

class QFileSystemWatcher;

// 
struct PastePath {
	//
	IHHPrimitiveItem *item;
	int nMoveX;
	int nMoveY;
	bool bChange;
};

// nType == 0 : normal
// nType == 1 : text_match
// nType == 2 : super_classify
// nType == 3 : gap_filling
// nType == 4 : group_competition
enum SLIDE_TYPE {
	SLIDE_NORMAL,
	SLIDE_TXTMATCH,
	SLIDE_SUPERCLASSIFY,
	SLIDE_GAPFILLING,
	SLIDE_GROUPCOMPETITION
};



// ========================= HHSlide ============================
// 向外发出的信号(signals):
// Item选择变化时： void selectionChanged();
//
class HHCanvas;
class LIB_EXPORT HHSlide : public QGraphicsScene,
        public IHHSlide, public IHHSlideDirectOperator,
        public HHSpecialItemManager< HHSlide >,
        public HHItemsOperator< HHSlide >
{
    Q_OBJECT
    Q_INTERFACES( IHHSlide IHHSpecialItemsManager IHHSlideDirectOperator IHHItemsOperator )

public:
	// nType == 0 : normal
	// nType == 1 : text_match
	// nType == 2 : super_classify
	// nType == 3 : gap_filling
	// nType == 4 : group_competition
    HHSlide(HHPresentation *pHHPresentation, int nType, QString strIndex = "");

	// copy构造
	HHSlide(const HHSlide &obj);

    virtual ~HHSlide();

	// 克隆新的Slide
    virtual IHHSlide* clone();
	
public:
    virtual QObject* getObject();
    
	// ================================ 选择 ===================================
public:
	
	// 增加新选中的Item
	virtual void appendSelItems(QVector< IHHPrimitiveItem* > & items);

	// 用新选中的Item替换原来选中的Item
	virtual void replaceSelItems(QVector< IHHPrimitiveItem* > & items);
	
	// 从新选中的Item中移除Item
	virtual void removeSelItems(QVector< IHHPrimitiveItem* > & items);

	// 获取选中的Items	
	// 返回值：当前选中Item
	virtual QVector< IHHPrimitiveItem* > & getSelItems();
	
	// 清除选中的Items
	virtual void clearSelItems();

    // 判断是否在选择中
    bool isInSelItems( IHHPrimitiveItem *item );

private:
	//
	HHSelectCenter *m_pSelectCenter;

	// ================ 选择 - 外包框 =================
public:
	// 由HHCanvas::drawForeground(QPainter *painter, const QRectF &rect)调用
	// 绘制选中item的HHItem_Selection线框 
    void paintSelection( QPainter *painter );

	// 由HHCanvas::sltActiveSlide(IHHSlide *slide)调用
	// 通知HHItem_Selection发生改变  ???
    void informSelectedHandlePosChanged();		

private:
	// 当选择item发生变化时调用
	// 根据选择Item增加选择控制点Item - 位于HHPrimitiveItem - HHItem_Selection - CSelectSprite
	void addSelection();

	// 当选择item发生变化时调用
	// 根据选择Item删除选择控制点Item - 位于HHPrimitiveItem - HHItem_Selection - CSelectSprite
	void removeSelection();
	    
	// ================================ Load/Save Item ===================================
public:
	// 设置页面属性
	//void setProperty(QJsonObject& jsonObj, bool bLoad);
		
	// Save - 外部调用
	virtual void getJSONObj(QJsonObject& jsonObj);

	// Load - 外部调用
	virtual void fromJSONObj(QJsonObject& jsonObj);

    virtual void fromJSONObj2(QJsonObject& jsonObj);

	// 是否加载数据
	bool isLoaded();

	// 标示数据是否加载
	void setLoaded(bool bLoaded);

	// 设置用于LoadData()的缓存数据
	virtual void setJsonData(QJsonObject& jsonData);

private:
	// 加载Slide内部缓存数据 - m_jsonData
	virtual void LoadData();

	// 删除所有Items
	void clearData();

	// remove by tianyu 2018.8.9
	// reload所有Items资源
    //void reloadItemResource( QVector< IHHPrimitiveItem* >& needClearItems );

	// clear所有Items资源
    //void clearItemResource( QVector< IHHPrimitiveItem* > needClearItems );
	// - remove by tianyu 2018.8.9

	// 数据是否全部被加载
	bool m_bLoaded;

	// 数据Slide是否全部被加载
	bool m_bSlidesLoaded;

	// Json数据 - 调用LoadData时加载
	QJsonObject m_jsonData;

private:
	// 获取Item索引
	int getIndex();	

	// Item索引	
	int	m_nItemIndex;

private:
	// 加载Items
	void LoadItems(QJsonObject& jsonObj);

	// ================================ Item绘制 ===================================
public:
	virtual void drawItems(QPainter *painter, int numItems, QGraphicsItem *items[], const QStyleOptionGraphicsItem options[], QWidget *widget = 0);
    void realDrawItems( QPainter *painter, int numItems, QGraphicsItem *items[],
                             const QStyleOptionGraphicsItem options[],
                             QWidget *widget, QRectF rectUpdate );
	// ================================ Item属性更新 ===================================
public:
	// 更新Item属性
	virtual void updatePrimitiveItems(QVector< IHHPrimitiveItem* > items, QVariantMap param);

	// 更新Item缩放、旋转、移动属性
	virtual void updateGeometryItems(QVector< IHHPrimitiveItem* > items, QVariantList param);

	// 缩放 - 更新Item
    virtual void updateScaleItems(QVector< IHHPrimitiveItem* > items, QVector<QPointF> refs,float xScale,float yScale);
    
	// 移动 - 更新Item
	virtual void updateTranslateItems(QVector< IHHPrimitiveItem* > items, float xOffset, float yOffset);
    
	// 旋转 - 更新Item
	virtual void updateRotateItems(QVector< IHHPrimitiveItem* > items, QVector<QPointF> refs, float angle);

    // 控制点 - 更新Item
    virtual void updateAdjusterItems(QVector< IHHPrimitiveItem* > items, QString type,QPointF pre, QPointF cur);
	
	// ================================ Item操作 ===================================
public:
	// ================= 增删改查Item ===============
	// 获取Item
    virtual QVector< IHHPrimitiveItem* > getItems();

	// 通过ID获得Item
    virtual QVector< IHHPrimitiveItem* > getItemsByID(QStringList list);

	// 增加Item
	virtual void addPrimitiveItem(IHHPrimitiveItem *item, bool bCmd = true);

	// 删除Item
	virtual void deleteItems(QVector< IHHPrimitiveItem* > items);

	// 通过ID删除Item
	// id == "ID_ITEM_DELETE_STROKES"  - 删除所有笔迹
	// id == "ID_ITEM_DELETE_ALL"	   - 删除所有item
	virtual void deleteItems(QString id);
	
	// 点选Item
    IHHPrimitiveItem* getItemByPoint(QPointF pos, QVariantMap param);
	
	// 根据区域选择Item
	virtual QList< QGraphicsItem* > getQItemsByPath(QPainterPath path, QVariantMap param);
	
	// 与getItems区别
	QList< QGraphicsItem* > getTopQItems( bool bWantInvisible );

	// 根据类型和宽高获取符合条件的元素列表
	//int getSameItems(const QString& strFilterType, qreal width, qreal height, QList<IHHPrimitiveItem*> & sameItems);
	
	// 获得QPainterPath中Items
	QVector< IHHPrimitiveItem* > getItems(QPainterPath *path);

	// 删除QPainterPath中Items
    void deleteItems(QPainterPath *path);

	// ================= QGraphicsItem处理 ===============
	// 不通过HHCommandItemNew,增加item - 注意：最终以QGraphicsItem插入，不可以被选中
	virtual void addCreatedItem(IHHPrimitiveItem *item);

	// 
	virtual void removeCreatedItem(IHHPrimitiveItem *item);

	// ================= 编辑 ===============
	// copy item
	// 剪切板格式："hhtitem:slide_id;item_id_1,item_id_2,item_id_3"
	virtual bool copyItem();


    // ============== slide 添加 item 内部命令到命令栈中 =======
    virtual void addItemsLocalCommand(HHCommand *cmd);

	// ================= 编辑 - paste ===============
public:
	// paste Item
	// 剪切板格式："hhtitem:slide_id;item_id_1,item_id_2,item_id_3"
	// 返回 - 粘贴后生成的Item
	virtual QVector< IHHPrimitiveItem* > pasteItemFromClipboard();

	// 按坐标位置Paste
	// 剪切板格式："hhtitem:slide_id;item_id_1,item_id_2,item_id_3"
	// pos - paste的位置
	// 返回 - 粘贴后生成的Item
	virtual QVector< IHHPrimitiveItem* > pasteItemFromClipboard(QPoint pos);

	// paste Item
	// itemsSrc:源item
	// posStart : paste的item从这个起始位置开始排列。当其发生改变时，重新排列。
	// 返回：新生成的paste item
	virtual QVector< IHHPrimitiveItem* > pasteItem(QVector< IHHPrimitiveItem* > &itemsSrc, QPoint posStart);

	// 布局Paste item.
	// itemPaste:已生成的paste item
	// posStart : paste的item从这个起始位置开始排列。当其发生改变时，重新排列。
	// 返回：布局item的位置
	virtual QPoint arrangePasteItem(IHHPrimitiveItem* itemPaste, QPoint posStart);

private:
	//
	QPoint m_posOld;

	// 第一次Paste 
	bool m_bFirst;

	// 获取左上角item的坐标
	void getTopLeftItemPos(QVector< IHHPrimitiveItem* > &items, int &xPos, int &yPos);

	// 从系统剪切板获取要Paste的item
	bool getPasteItemFromclipboard(QVector< IHHPrimitiveItem* > &itemsPaste);

	//
	// Paste偏移
	int m_nMoveX;
	int m_nMoveY;

	// Paste路径
	QVector<PastePath*> m_vPastePath;

	// items发生变化时，更新Paste路径
	void updatePastePath(QVector<IHHPrimitiveItem *> items);

	// 在Paste路径中查找变化的item
	PastePath* findPastePathChanged();

	// 在Paste路径中item是否发生变化
	bool findPastePath(QVector<IHHPrimitiveItem *> items);
	
	// 清除Paste路径
	void clearPastePath();

	// 设置itemsPaste到Paste路径
	void setPastePath(QVector< IHHPrimitiveItem* > itemsPaste);

	// 从源Item，按一定步长Paste
	QVector< IHHPrimitiveItem* > PasteItem(QVector< IHHPrimitiveItem* > &itemsSource);
	//void PasteItemByStep(QVector< IHHPrimitiveItem* > &itemsSource, int moveX, int moveY, QVector< IHHPrimitiveItem* > &itemsDest);

	// 在鼠标位置Paste
	void PasteItemByPos(QVector< IHHPrimitiveItem* > &itemsSource, int xPos, int yPos, QVector< IHHPrimitiveItem* > &itemsDest);

	//
	void transPasteItem(QVector< IHHPrimitiveItem* > &itemsPaste, int x, int y);

	// ================= 编辑 - cut,delete, selectall ... ===============
public:
	// cut Item
	// 剪切板格式："hhtitem:slide_id;item_id_1,item_id_2,item_id_3"
	// cut后的剪切板格式: "hhtitem:0;0,0,0" - id都为"0"
	virtual bool cutItem();

	// 删除Item
	virtual bool deleteItem();

	// 全选Item
	virtual bool selectAllItem();

private:
	// 过滤item
	// 过滤规则： 锁定、克隆、隐藏和一般item, 不能共存
	//bool filterItemsSelect(QVector< IHHPrimitiveItem* > itemsSrc, QVector< IHHPrimitiveItem* > &itemsDest);

	// 过滤item
	// 过滤规则： 锁定、克隆、隐藏和一般item, 不能共存
	QVector< IHHPrimitiveItem* > filterItemsSelect(QVector< IHHPrimitiveItem* > vItems);

	// 过滤item的excute：
	// 过滤规则： "AllowCopy == false"、"AllowCut == false"、"AllowDelete == false"
	QVector< IHHPrimitiveItem* > filterItemsExcute(QString strFilter, QVector< IHHPrimitiveItem* > vItems);

    // ================= 移动 ===============
public:
    // 移动Item
    // strType = "ID_ITEM_MOVE_UP"		: 向上
    // strType = "ID_ITEM_MOVE_DOWN"	: 向下
    // strType = "ID_ITEM_MOVE_LEFT"	: 向左
    // strType = "ID_ITEM_MOVE_RIGHT"	: 向右
    virtual bool moveItems(QString strType);

    // ================= 镜像 ===============
    // 镜像Item
    // strType = "ID_HH_ITEM_MIRROR_TOP"	: 向上镜像
    // strType = "ID_HH_ITEM_MIRROR_BOTTOM" : 向下镜像
    // strType = "ID_HH_ITEM_MIRROR_LEFT"	: 向左镜像
    // strType = "ID_HH_ITEM_MIRROR_RIGHT"	: 向右镜像
    virtual bool mirrorItems(QString strType);

	// ================= ??? ===============
	// 显示Item外包框
	void showItemBox(QVector< IHHPrimitiveItem* > items);

	// 隐藏Item外包框
	void hideItemBox(QVector< IHHPrimitiveItem* > items);

    // ================= 翻转 ===============
    // 翻转Item
    // strType = "ID_ITEM_FLIP_HOR"	: 水平
    // strType = "ID_ITEM_FLIP_VER"	: 垂直
    virtual bool flipItems(QString strType);

    // ================= z-order ===============
    // z-order Items
    // strType = "ID_HH_ITEM_EDIT_ZORDER_TOP"		: z-top
    // strType = "ID_HH_ITEM_EDIT_ZORDER_BOTTOM"	: z-bottom
    // strType = "ID_HH_ITEM_EDIT_ZORDER_PRE"		: z-up Item
    // strType = "ID_HH_ITEM_EDIT_ZORDER_NEXT"		: z-down Item
    virtual bool zorderItems(QString strType);

    // ================= 组合 ===============
    // 组合Item
    virtual int groupItem();

    // 取消组合Item
    virtual int ungroupItem();

    // ================= 锁定 ===============
    // 锁定Item
    int lockItem();

    // 取消锁定Item
    int unlockItem();

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
    virtual bool alignItems(QString strType);

    // ================= 左右转 ===============

    // 转动items
    virtual bool rotateItems(float fAngle);

	// ================= bind canvas =================
	// 关联canvas
	void attachCanvas(bool bAttach);

	// ================================ 幕布 =================================
public:
	// 增加幕布
	void addCurtianItem(IHHCurtainItem *curtian);

	// 删除幕布
	void removeCurtianItem(IHHCurtainItem *curtian);

	// 获取幕布
	QVector< IHHCurtainItem* > & getCurtianItem();

	// 幕布是否存在
	bool isCurtianExist();

private:
	//
    QVector< IHHCurtainItem* > m_curtianItems;

	// ============================= 缩略图 ================================
public:
	// 向painter画缩略图
	virtual void drawThumnail(QPainter *painter, const QRectF &rect);

	// 保存为图片
	void saveToImage(QString strName, QRectF rangeRect, int width, int height, QString imgType);

	// 更新rect区域 - 替换indirectChangeContent
	void refresh(const QRectF &rect, bool bUpdateThumnail = false);

    //
    virtual void setClipRect( QRectF rect );

    virtual void translate( float xOffset, float yOffset );
    virtual void scale( QPointF ptCenter, float xRate, float yRate );
    virtual void rotate( QPointF ptCenter, float degree );
		
private:
	//
	void drawItemsOnThumnail(QPainter *painter, int numItems, QGraphicsItem *items[], const QStyleOptionGraphicsItem options[], QWidget *widget = 0);

	// 向painter画缩略图
	virtual void renderThumnail(QPainter *painter, const QRectF &target = QRectF(), const QRectF &source = QRectF(), Qt::AspectRatioMode aspectRatioMode = Qt::IgnoreAspectRatio);

	// ============================= 背景图 ================================
public:
	// 加载背景图
	//void loadBackgroudImage();

	// 设置背景颜色
	virtual void setBacColor(QString strBackColor);

	// 获取背景颜色
	virtual QString getBacColor();

	// 加载背景文件,生成背景图
    virtual void setBackFile(QString strBackFile,bool isLoad = false);

    //获取背景文件全路径
    virtual QString getBackFilePath();

    //设置背景文件全路径
    virtual void setBackFilePath(QString path);

	// 设置背景文件MD5文件名
	virtual void setBackMd5File(QString strMd5File);

	// 获取背景文件MD5文件名
	virtual QString getBackMd5File();

	// 加载背景图片
	virtual void setBackPic(QPixmap pixBack);

	// 获取背景图片
	virtual QPixmap getBackPic();

	// 绘制背景
	virtual void drawBackground(QPainter *painter, const QRectF &rect);

	// 绘制前景
	virtual void drawForeground(QPainter *painter, const QRectF &rect);

	//
public slots:
	//
	void slotCreateImageResp(const QString &file, const QString &md5File, const QPixmap &pix);

private:

	// 背景图
	QPixmap m_pixBack;				// TODO: private:

	// 页面工作区的背景
	QColor m_colorBack;
	
	// 背景颜色
	QString m_strBackColor;

    // add by wang.yan 2018.08.04 :兼容老课件处理
    QString m_strBackFile;
    bool    m_isLoadSlide;
    //add end

	// 背景MD5文件
	QString m_strMd5File;

	//
    QRectF m_rectClip;
    QRectF m_rectClipDrawItems;

	//
	QRectF computeUniformRange(QRectF target, float width, float height);

	// ???
	QMatrix computeMatrixAccordTwoRectF(QRectF source, QRectF target);

	// ============================= 页面特效 ================================
public:
	// 设置特效
	virtual void setEffect(Effect effect);

	// 取得特效
	virtual Effect getEffect();

private:
	// 特效
	Effect m_effect;

	// ============================= item特效 ================================、
public:
	//获取对象特效ordermanager
	virtual IHHItemAnimationsSlideManager* getAnimationSlideManager();

	//设置对象特效ordermanager
	virtual void setAnimationSlideManager(IHHItemAnimationsSlideManager *manager);

private:
	// item特效
    IHHItemAnimationsSlideManager* m_animationManager;

	// ============================= 页面漫游 ================================
public:
	// 设置页面漫游matrix
	virtual void setMatrix(QMatrix matrix);

	// 获得页面漫游matrix
	virtual QMatrix getMatrix();

	// 重置页面漫游matrix
	virtual void resetMatrix();

public:	// ???private
	// 页面漫游matrix
	QMatrix m_matrix;

	// ============================= 课堂活动 ================================
public:
	//
	virtual IHHActivityManage *getActivityManage();

	// 0 - normal slide
	// >= 1 - activity slide
	virtual int getType();

private:
	// 课堂活动
	IHHActivityManage* m_pActivity;

	// 0 - normal slide
	// >=1 - activity slide
	int m_nType;

	// ============================= Slide参数 ================================
public:
	// Presentation指针 - private???
	HHPresentation *m_pPres;
    virtual IHHPresentation* getPresentation();

    virtual void changeProportionScale(QPointF point, float xRate, float yRate);
    virtual void changeProportionTranslate(float xOffset, float yOffset);

	// 获取Slide的标示ID
	virtual QString getID();

	// 设置Slide的标示ID
	void setID(QString strID);

private:
	// Slide标识ID 
	QString m_strID;

    // ========================add by wangyan item名称处理 start ============================
public:
    //设置item名称
    virtual void setItemName(IHHPrimitiveItem* item);
private:
    int m_nTextboxNum = 0;
    int m_nShapeNum = 0;
    int m_nImageNum = 0;
    int m_nFlashNum = 0;
    int m_nVedioNum = 0;
    int m_nAudioNum = 0;
    int m_nDocNum = 0;
    int m_nStrokeNum = 0;
    int m_nSubjectNum = 0;
    int m_nGroupNum = 0;
    int m_nContainer = 0;
    int m_nMaterial = 0;
    int m_nMindMap = 0;

	// ============================= Slide信号 ================================
signals:
	// remove by tianyu 2018.7.25
	// 视频截图图片收集器.
	//void signalImageEditor(QVariantMap);

	// Item属性变化时信号
	//void signalItemPropChanged();
	// - remove by tianyu 2018.7.25

	// ============================= slot ================================
#if 0
	public Q_SLOTS:
	// // Slide发生变化
	void slotChanged(const QList<QRectF> &region);
#endif
};

#endif // HHSLIDE_H
