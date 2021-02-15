#ifndef IHHSPECIALITEMMANAGER_H
#define IHHSPECIALITEMMANAGER_H

#include <QObject>
#include <QJsonObject>

class IHHCurtainItem;
class IHHSpecialItemsManager {
public:
    virtual ~IHHSpecialItemsManager(){}
    virtual void addMathLine( QString type, QJsonObject jObj, QMatrix matrix, QPointF start, QPointF end) = 0;
    virtual void addMathEllipse( QJsonObject jObj, QMatrix matrix, QRectF box, float angleDegree) = 0;
    virtual void addMathCircle( QJsonObject jObj, QMatrix matrix, QRectF box) = 0;
    virtual void addMathArc(int nArrowNum, int nKindType,QJsonObject jObj, QMatrix matrix, QRectF box, float startAngleDegree, float sweepAngleDegree) = 0;
    virtual void addMathRectangle( QJsonObject jObj, QMatrix matrix, QRectF rect) = 0;
    virtual void addMathAngle( QJsonObject jObj, QMatrix matrix, QPointF start, QPointF end, QPointF center) = 0;
    virtual void addMathTriangle( QJsonObject jObj, QMatrix matrix, QPointF start, QPointF two, QPointF three) = 0;
    virtual void addMathParallelogram( QJsonObject jObj, QMatrix matrix, QPointF leftTop, QPointF rightTop, QPointF rightBottom, QPointF leftBottom) = 0;
    virtual void addMathPolyline( QJsonObject jObj, QMatrix matrix, QString strPts) = 0;
    // ================================ 工具 =================================
    // 增加工具
    virtual void addToolWidget(QWidget *tool) = 0;

    // 删除工具
    virtual void removeToolWidget(QWidget *tool) = 0;
    //设置工具父窗口
    virtual void setToolParent(QWidget* parent) = 0;

    //
    //virtual void addGeneralTool(IHHPrimitiveItem *tool) = 0;		// - 以后不再使用

    //
    // ================================ 幕布 =================================
    // 增加幕布
    virtual void addCurtianItem(IHHCurtainItem *curtian) = 0;

    // 删除幕布
    virtual void removeCurtianItem(IHHCurtainItem *curtian) = 0;

    // 获取幕布
    virtual QVector< IHHCurtainItem* > & getCurtianItem() = 0;

    // 幕布是否存在
    virtual bool isCurtianExist() = 0;
};
Q_DECLARE_INTERFACE( IHHSpecialItemsManager, "com.hht.qtWhiteBoard.IHHSpecialItemsManager/1.0" )
Q_DECLARE_METATYPE( IHHSpecialItemsManager* )

#endif // IHHSPECIALITEMMANAGER_H
