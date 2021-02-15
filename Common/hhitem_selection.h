#ifndef HHITEM_SELECTION_H
#define HHITEM_SELECTION_H

#define RADIUS 5
#define MENUDIS 4
#define EXTENDLEN 20

#include "lib_global.h"
#include "ihhselection.h"
#include <QGraphicsItem>

class HHSlide;
class QPainter;
class HHPrimitiveItem;

class LIB_EXPORT HHItem_Selection:public IHHSelection
{
public:
	HHItem_Selection( HHPrimitiveItem *item );
    virtual ~HHItem_Selection();

public:
    QVariant itemSelectionGetParameters( QString type );
	QMatrix getDownMatrix();
	float getAngleFromStart();
protected: 
    //
	virtual void processSelfPenProperty(QPen& pen);
protected:
    bool                    m_bInit;
       
    HHPrimitiveItem         *m_pItem;
	
	//*/
	QPointF    m_ptnRevolve;
	QPointF    m_ptnMenuScene;
public:
    void setSizeInfo( const QVariantMap &mapSizeInfo );
	QVariantMap getSizeInfo() const; 
    //QPointF getMenuButton();

protected:
	//    
    QString m_strItemType;  // added by xuxia, 2017/11/07.
	
	// ================================== paint ====================================
public:
	// 选择框绘制
	virtual void item_paint(QPainter *painter, bool bSingleSelecton = true);
	
	//
    virtual void itemSelectionPaint(QPainter *painter, bool bSingleSelecton = true);
	
	//
	void itemSelectionRefresh();

	// 选择框是否可见
	virtual bool getSelectionVisible();
	
	// 设置选择框可见
	virtual void setSelectionVisible(bool bVisible);

protected:
	QPointF m_ptDown;
	double m_fPreWidth;
	double m_fPreHeight;

	// 
	int m_nSmallRadius;				// 控制点小半径
	int m_nNormalRadius;			// 控制点半径
	int m_nRotateHandleRadius;		// 旋转控制点的半径
	int m_nRotateHandleDistance;	// 旋转控制柄的长度

	//
	float m_fBitmapWidthInScene;
	float m_fBitmapHeightInScene;

	// 是否显示边框连线
	bool m_bShowBoundary;

	// 是否显示
	bool m_bVisible;

private:
	/*/TTQX-zhaozhengze-重绘函数中去掉虚函数。
	绘制边框
	/*/
	virtual void drawOuterLine(QPainter *painter, QSet<int>& setTrans, QMatrix& painterMatrix);

	// ================================== menu ====================================
public:
	// 获取menu的位置区域
	QRectF getRightMenuButtonArea() const;

	bool isPickMenuButton(QPointF point, QMatrix mat = QMatrix());
	/*/TTQX-zhaozhengze-处理item光标问题。
	/*/
	bool isPickMenuButtonInShowing(QPointF point);

protected:
	//
	void intialMenuPixmap();

	// 加载menu图片
	QPixmap getMenuPixmap(QString file);

	//
    virtual void initialShowProp(bool flag = true);

protected:
	/*/TTQX-zhaozhengze-处理item光标问题。
	保留1 在最终的显示坐标系下的所有的handle
	2 保留右上角菜单按钮的位置。
	/*/

	// 右上角菜单按钮的位置
	QPointF m_ptnMenuShowingPtn;

	//liuliyan 2017-11-10 modified start
	//包围框右上角下拉按钮的菜单图标
	QPixmap m_menuPix;

	//包围框右上角下拉按钮的锁定图标
	QPixmap m_lockInPix;

	//包围框右上角下拉按钮的拖动克隆图标
	QPixmap m_InfiniteClonePix;

	//liuliyan 2017-11-10 modified end
	//TTQX-zhaozhengze添加隐藏按钮
	QPixmap m_HidePix;

protected:
	// 菜单按钮的宽度
	int m_nMenuButtonWidth;

	// 是否显示 - 菜单按钮
	bool m_bShowMenuButton;			

	// ================================== sprite ====================================
public:
	virtual QVector<QGraphicsItem*> getHandleItemVector();
	virtual QVector<QGraphicsItem*> getControlHandleItemVector();

	//
	void  processVisibleSet();
	void  processCloneSet();
	void  processLockSet();

protected:
	QGraphicsItem* m_pSelectSprite;

	// ============================== 同步item和Sprite = ===============================
public:
	//
	virtual void informHandlePosChanged();
	
	// 
	void computerSelectionData();
	
	//
	void reComputerHanlderPos();

	//private:
public:	// ??? CGeoSegmentSelection ???priavate
		/*
		* m_ayContainerPts m_ayRealPts
		* 保存包围框控制点坐标，从左上角（0）顺时针保存，最上端旋转按钮在最后一个（8）， 9是菜单按钮
		* m_ayRealPts中值为对象变换实际点，m_ayContainerPts为包围框上点一般比m_ayRealPts靠外1
		*          8
		* 0        1       2
		* 7                3
		* 6        5       4
		*/
	QVector< QPointF > m_ayContainerPts;

protected:
	//
	QVector< QPointF > m_ayRealPts;

private:
	//
	void computeContainerPts(QRectF rect, QMatrix matrix, QVector< QPointF >& pts);

	// ================================ BottomCur ====================================
public:
	virtual bool isPickBottomCurItem(QPointF point);

protected:
	QGraphicsItem*      m_pSelectBottomCur;

	// ================================== Transform ====================================
public:
	// 开始Translate、Rotate、Scale
	virtual void itemSelectionStartTransform(int handleID, float xDown, float yDown);
	
	// 结束Translate、Rotate、Scale
	virtual void itemSelectionEndTransform(float xNew, float yNew);

	// Translate
	virtual void itemSelectionTranslate(float xNew, float yNew);
	void itemSelectionTranslate(QVariant param);

	// Rotate
	virtual float itemSelectionRotate(float xNew, float yNew);
	virtual void itemSelectionRotate(QVariant param);
	
	/*/TTQX-zhaozhengze-文本框的scale操作有问题。
	/*/
	// Scale
	virtual float itemSelectionScale(int handleID, float xNew, float yNew);
	virtual void itemSelectionScale(QVariant param);

	// ???
	void itemSelectionActionTransform(QVariantMap param);

	// 等比缩放
	void setOnlyEqualScaleFlag(bool bEqual);

//private:
protected:
	// 处理等比缩放
	virtual float processEqualRatioScale(float xNewWidth, float yNewHeight, QPointF ptRef);
	
	// 处理非等比缩放
	virtual float processUnEqualRatioScale(float xNewWidth, float yNewHeight, QPointF ptRef);

private:
	bool m_bOnlyEqualScale;

//private:
public: // ???private
	float m_xTransformStart;
	float m_yTransformStart;
	float m_xTransformLenToStart;
	float m_yTransformLenToStart;
	QPointF m_ptRef;
	
    float m_xPre;
    float m_yPre;
    float m_xPreScale;
    float m_yPreScale;
    /*
     * m_fDownAngle         初始倾斜角度
     * m_fStepAngle         增量角度
     * m_fRotateAngle       总共角度
     * m_ptCenter           旋转中心
     */
    float m_fDownAngle;
    float m_fStepAngle;
    float m_fRotateAngle;
    QPointF m_ptCenter;
    /*
     * m_ptOffset           偏移量
     */
    QPointF m_ptOffset;
    /*
     * m_ptScale            放缩比
     */
    QPointF m_ptScale;
	QPointF m_ptScaleToStart;
    QMatrix m_matrixDown;
    int m_nHandleID;

	// ================================== Pick ====================================
public:
	int isPickHandler(QPointF point, bool bIncludeDirect = true, QMatrix mat = QMatrix());

private:	
	QPointF getRotatePoint(QMatrix matrix);
};

#endif // HHITEMSELECTION_H
 
