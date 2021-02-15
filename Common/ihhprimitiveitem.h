#ifndef IHHTPRIMITIVEITEM_H
#define IHHTPRIMITIVEITEM_H
#include <QObject>
#include <QVariantMap>
#include <QVector>
#include <QGraphicsItem>
#include <QPixmap>
#include <QSet>
#include <QPointF>
#include <QJsonObject>
#include <QPainterPath>
#include <QThread>
#include <QString>
#include "hhglobaldefine.h"

class IHHTransformAction;
class IHHSelection;
class IHHItemAnimationManager;

class IHHPrimitiveItem {
public:
    virtual ~IHHPrimitiveItem(){}
    virtual IHHSelection* getItemSelectionPtr() = 0;
    virtual QRectF getBoundingBox() = 0;
    virtual  void setVerticalFlip() = 0;
    virtual  void setHorizonFlip() = 0;
    virtual int isAcceptMousePressEvent( QPointF pt ) = 0;
    virtual int isAcceptMouseReleaseEvent( QPointF pt ) = 0;
    virtual void setParameters( QString type, QVariant value ) = 0;// 设置参数
    virtual QVariant getParameters( QString type ) = 0;// 得到参数
    virtual void getJSONObj( QJsonObject& jsonObj ) = 0;// 得到JSON对象
    virtual void fromJSONObj( QJsonObject& jsonObj ) = 0;// 从JSON对象获取数据
    virtual QObject* getObject() = 0;
    virtual void startCreate( QPointF point, QVariantMap param ) = 0;
    virtual void creating( QPointF point, QVariantMap param ) = 0;
    virtual void endCreate( QPointF point, QVariantMap param ) = 0;
    virtual QString isPickAdjusters( QPointF point ) = 0;
    virtual bool isPickByPoint( QPointF pos, QVariantMap param  ) = 0;
    virtual bool isPickByPath( QPainterPath path, QVariantMap param ) = 0;
    virtual void processSelectionalPathAfterSelected(QPainterPath path) = 0;  // add by weijibin used by MindMap
    virtual QSet<int> getSupportTransform() = 0;
    virtual QMatrix getDataMatirx() = 0;
    virtual void setTransformInfo( float fAngle, QMatrix matrix, QRectF rect ) = 0;
    // used in context menu
    virtual QVector< HHEditProperty > getProperty( int level ) = 0;

    // used in right panel to show and set item's properties
    virtual QVector< HHEditProperty > getUIProperty( int level ) = 0;   // added by xuxia. 2017/11/02.

    virtual QPixmap* exportToImage() = 0;
    virtual IHHPrimitiveItem* clone() = 0;
    //add by lijunfeng 2017.11.19 start
    virtual IHHTransformAction* performTouchStart( QPointF point, QVariantMap param ) = 0;
    virtual IHHTransformAction* performTouchMove( QPointF point, QVariantMap param ) = 0;
    virtual IHHTransformAction* performTouchEnd( QPointF point, QVariantMap param ) = 0;
    virtual void setBlankCursor() = 0;
    virtual void restoreCursor() = 0;
    //add by lijunfeng end

    //add by weijibin 2017.11.29 start
    virtual IHHTransformAction* performTouchGetAction( QPointF point, QVariantMap param ) = 0;
    virtual IHHTransformAction* performTouchSetAction( QString strAction, QPointF point, QVariantMap param ) = 0;
    virtual IHHTransformAction* getTransformAction() = 0;
    //add by weijibin 2017.11.29  end
    virtual QVariantMap getCursor(QPointF ptn, QMatrix mat) = 0 ;
    virtual void  translate(float xOffset, float yOffset) = 0;
    virtual void  rotate(QPointF ptnCenter, float fAngle) = 0;
    virtual void  scale(QPointF ptnRef, float fScaleX, float fScaleY) = 0;
    virtual void  paintInCreatePhrase( QPainter *painter, QRectF rect ) = 0;
    virtual void  processItemRotateInform() = 0;
    virtual bool  isRightMenuSupportable(QPointF ptn) = 0;
    virtual void  processRightKey(QPointF ptn,bool isSingle) = 0;
    virtual void  setEditalbe(bool bEditalbe) = 0;
	virtual void  updateItemRegion() = 0;
	virtual void  hyperlinkItemPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;
    virtual IHHItemAnimationManager* getAnimationManager() = 0;
	virtual bool  attempScale(QPointF ptnRef, float fScaleX, float fScaleY) = 0;
	
	// remove by tianyu 2018.8.9
	//virtual void clearResource() = 0;
	//virtual void reloadResource() = 0;
	//virtual bool hasClearResource() = 0;
	// - remove by tianyu 2018.8.9

	//
	virtual void setCanExecute(const QString &sType, bool) = 0;
    virtual bool isCanExecute(const QString &sType) = 0;

    virtual void moveToTheThread(QThread *t) = 0;
    virtual void changeProportionScale(QPointF point, float xRate, float yRate) = 0;
};
Q_DECLARE_INTERFACE( IHHPrimitiveItem, "com.hht.qtWhiteBoard.IHHPrimitiveItem/1.0" )
Q_DECLARE_METATYPE( IHHPrimitiveItem* )
Q_DECLARE_METATYPE( QList< IHHPrimitiveItem* > )
Q_DECLARE_METATYPE( QVector< IHHPrimitiveItem* > )

#endif // IHHTRANSFORMACTION_H
