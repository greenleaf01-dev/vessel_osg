#ifndef IHHCOVERLAYER_H
#define IHHCOVERLAYER_H

#include <QObject>
#include <QPainter>

// 1.蒙层功能接口类.
class IHHCoverLayer
{
public:
    // controller 备授课切换.
    virtual void resetWipePath() = 0;
    virtual void setTipText(QString) = 0;
	virtual void setWipeState(bool) = 0;
	virtual bool getWipeState() = 0;

    // connand 获取当前path.
    virtual QPainterPath getUndoWipePath() = 0;
    virtual QPainterPath getWipePathConst() const = 0;

    // 生成Path: 上一个点 当前点 橡皮宽度.
    virtual void wipeCoverLayer(QPointF, QPointF, int) = 0;
    // 设置path: 由command转换QGraphicsItem并调用其update.
    virtual void undoWipeCoverLayer(QPainterPath) = 0;
    virtual void redoWipeCoverLayer(QPainterPath) = 0;

    // 供 子Item 调用.
    virtual void setCoverLayerSlcted(bool bSelected) = 0;
    virtual bool getCoverLayerSlcted() const = 0;
    virtual bool isCovered() const = 0;

    virtual void paintCoverLayer(QPainter* painter, QRectF rtFBox, QMatrix mtrxFlip = QMatrix()) = 0;
};
Q_DECLARE_INTERFACE(IHHCoverLayer, "com.hht.qtWhiteBoard.IHHCoverLayer/1.0")
Q_DECLARE_METATYPE(IHHCoverLayer*)

#endif // IHHCOVERLAYER_H
