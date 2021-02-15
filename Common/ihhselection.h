#ifndef IHHTSELECTION_H
#define IHHTSELECTION_H
#include <QObject>
#include <QVariantMap>
#include <QVector>
#include <QGraphicsItem>
class  IHHSelection
{
public:
        virtual ~IHHSelection() {}
        virtual void setSizeInfo(const QVariantMap &mapSizeInfo) = 0;
        virtual void setSelectionVisible(bool bVisible) = 0;
        virtual bool getSelectionVisible() = 0;
        virtual void informHandlePosChanged() = 0 ;
        virtual QVector<QGraphicsItem*> getHandleItemVector() = 0;
        virtual void item_paint(QPainter *painter,bool bSingleSelecton = true)= 0;
};

Q_DECLARE_INTERFACE( IHHSelection, "com.hht.qtWhiteBoard.IHHSelection/1.0" )
Q_DECLARE_METATYPE( IHHSelection* )

#endif // IHHTRANSFORMACTION_H
