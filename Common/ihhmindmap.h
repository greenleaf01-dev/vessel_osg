#ifndef IHHMINDMAP_H
#define IHHMINDMAP_H

#include <QObject>
class MindmapNodeItem;
class IHHMindMapNode
{
public:
    virtual ~IHHMindMapNode(){}
    virtual IHHMindMapNode* clone() = 0;
    virtual QString getNodeID() = 0 ;
    virtual int nodeType()=0;
    virtual MindmapNodeItem* item() const = 0;
};

class IHHMindMap {
public:
    virtual ~IHHMindMap(){}
    virtual void moveUp()=0;
    virtual void moveDown()=0;
    virtual void addHyperlink(QString str)=0;
    virtual QVector<IHHMindMap*> partialClone(QVector<IHHMindMapNode*>& vecMindMap,QRectF rect) = 0;
    virtual void pasteFromNodes(QVector<IHHMindMapNode*>& vecMindMap) = 0;
    virtual QVector<IHHMindMapNode*>  getSelectedNodes() = 0;
    virtual void clearMindMapNodes(QVector<IHHMindMapNode*> vecClearedNode) = 0;
    virtual IHHMindMapNode* getNodeByNodeId(QString strNodeId) = 0;
    virtual void  updateLayout() = 0;
    virtual void setGeneralStyle(int index)=0;
    virtual int getGeneralStyle()=0;

    virtual void setNodeFillColor(QString color)=0;
    virtual QString getNodeFillColor()=0;

    virtual void setNodeBorderColor(QString color)=0;
    virtual QString getNodeBorderColor()=0;

    virtual void setEdgeStyle(int index)=0;
    virtual int getEdgeStyle()=0;

    virtual void setEdgeColor(QString color)=0;
    virtual QString getEdgeColor()=0;

    virtual void setSpreadStyle(int index)=0;
    virtual int getSpreadStyle()=0;

    virtual bool isHaveCustomEdgeColor()=0;
    virtual void setEdgeColorWhenLoad(QString color)=0;
    virtual void setGeneralStyleWhenLoad(int index)=0;

    virtual void processShortCutInItem(QString keyType)=0;
    virtual QVariantMap getCurrentProperty() = 0;
    virtual void propertyChanged(QString str)=0;

    virtual void addShade()=0;
    virtual void addStamp(int type)=0;
    virtual void hideShade()=0;
    virtual void hideStamp()=0;
    virtual bool haveShade()=0;
    virtual bool haveStamp()=0;

    virtual void addEnclosure(QMap<QString ,QString> info,QVector<IHHMindMapNode*> nodes)=0;
    virtual void setTextProperty( QString type, QVariant value ) = 0;

    virtual  void setInterationInfo(QString strInteractiveType,QString strInteractiveValue) = 0;
    virtual QVariant getTextProperty(QString type) = 0;

    virtual QPixmap* exportToImage() = 0;
};
Q_DECLARE_INTERFACE( IHHMindMap, "com.hht.qtWhiteBoard.IHHMindMap/1.0" )
Q_DECLARE_METATYPE( IHHMindMap* )

#endif // IHHMINDMAP_H
