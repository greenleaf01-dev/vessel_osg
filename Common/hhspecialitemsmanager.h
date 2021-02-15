#ifndef HHSPECIALITEMMANAGER_H
#define HHSPECIALITEMMANAGER_H

#include "ihhspecialitemsmanager.h"
#include "ihhcurtainitem.h"
#include "ihhprimitiveitem.h"
#include <QGraphicsItem>
#include <QJsonArray>
#include <QWidget>
#include <QDebug>
#include <QApplication>
#include "ihhpresentation.h"

// 幕布 Z-序
#define ZORDER_CURTAIN 50000
// 选择控制点 Z-序
#define ZORDER_SELECTION 40000

//
class IHHPrimitiveItem;
class TemplateSpecialItemManagerHelper
{
public:
    TemplateSpecialItemManagerHelper() ;
    void getItem(const QString& str, const QJsonObject& jobj, IHHPrimitiveItem*& item) ;
};

class IHHPresentation;
template< class T >
class HHSpecialItemManager : public IHHSpecialItemsManager
{
    Q_INTERFACES( IHHSpecialItemsManager )

public:
    HHSpecialItemManager() {
    }

    virtual ~HHSpecialItemManager() {
        // 释放工具
        QVector<QWidget*>::iterator iterTool;
        for (iterTool = m_tools.begin(); iterTool != m_tools.end(); iterTool++)
        {
            //
            delete *iterTool;
        }
    }

public:
    void addItem2Selected(T *slide,IHHPrimitiveItem *item){
        if(slide&&item){
            slide->addPrimitiveItem( item );
            //加入选择态。
            QVector<IHHPrimitiveItem*> items;
            items.append(item);
            slide->replaceSelItems( items);
        }
    }

	// ================================ 工具和智能笔产生item ============================================
    virtual void addMathLine(QString type, QJsonObject jObj, QMatrix matrix, QPointF start, QPointF end) {
        Q_UNUSED( matrix );

        T *slide = static_cast< T* >( this );

        IHHPrimitiveItem *item = 0;
        QJsonObject tempObject;
        _helper.getItem( type, tempObject, item );
        if( item == NULL )
            return;

        qreal sx = start.x(), sy = start.y(), ex = end.x(), ey = end.y();
        jObj[ "Discipline_xCreate" ] = QString("%1").arg( ( sx + ex ) / 2 );
        jObj[ "Discipline_yCreate" ] = QString("%1").arg( ( sy + ey ) / 2 );
        QJsonArray qa;
        qa.push_back( ex );
        qa.push_back( ey );
        qa.push_back( sx );
        qa.push_back( sy );
        jObj[ "Control" ] = qa;

        if("HHMath2DSegmentWith1Arrow" == type)
            jObj[ "ArtObj_ArrowType" ] = QString::number(1);
        else if("HHMath2DSegmentWith2Arrow" == type)
            jObj[ "ArtObj_ArrowType" ] = QString::number(2);

        item->fromJSONObj( jObj );
        slide->addPrimitiveItem( item );
    }

    virtual void addMathEllipse(QJsonObject jObj, QMatrix matrix, QRectF box, float angleDegree) {
        Q_UNUSED( matrix );

        T *slide = static_cast< T* >( this );

        IHHPrimitiveItem *item = 0;
        QJsonObject tempObject;
        _helper.getItem( "HHMath2DEllipse", tempObject, item );
        if( item == NULL )
            return;

        float centerX = box.center().x(), centerY = box.center().y();
        float changX = box.left(), changY = centerY;
        float duanX = centerX, duanY = box.bottom();

        jObj[ "Discipline_xCreate" ] = QString("%1").arg( centerX );
        jObj[ "Discipline_yCreate" ] = QString("%1").arg( centerY );
        QJsonArray qa;
        qa.push_back( changX );
        qa.push_back( changY );
        qa.push_back( duanX );
        qa.push_back( duanY );
        jObj[ "Control" ] = qa;
        item->fromJSONObj(jObj);

        angleDegree = -angleDegree;
        item->setParameters( "Angle", angleDegree );
        item->processItemRotateInform();

    //    matrix = matrix * HHToolHelper::rotate2(angleDegree, QPointF(centerX,centerY));
        slide->addPrimitiveItem( item );
    }

    virtual void addMathCircle( QJsonObject jObj, QMatrix matrix, QRectF box) {
        Q_UNUSED( matrix );

        T *slide = static_cast< T* >( this );

        IHHPrimitiveItem *item = 0;
        QJsonObject tempObject;
        _helper.getItem( "HHMath2DCircle", tempObject, item );
        if( item == NULL )
            return;

        qreal centerX = box.center().x(), centerY = box.center().y();
        qreal cX = box.right(), cY = centerY;

        jObj["ArtObj_Display"] = QString::number( 0 );
        jObj[ "Discipline_xCreate" ] = QString("%1").arg( centerX );
        jObj[ "Discipline_yCreate" ] = QString("%1").arg( centerY );
        QJsonArray qa;
        qa.push_back( cX );
        qa.push_back( cY );
        jObj[ "Control" ] = qa;

        item->fromJSONObj(jObj);
        slide->addPrimitiveItem( item );
    }

    virtual void addMathArc(int nArrowNum, int nKindType, QJsonObject jObj, QMatrix matrix, QRectF box, float startAngleDegree, float sweepAngleDegree) {
        Q_UNUSED( matrix );

        T *slide = static_cast< T* >( this );

        IHHPrimitiveItem *item = 0;
        QJsonObject tempObject;
		//jObj: QJsonObject({"FillColor":{"Alpha":1,"Solid":16711680},"IsFill":"0","LineColor":{"Alpha":1,"Solid":16711680},"LineWidth":"2"})

        //added by wangxianbing,to fix bug:[B180323-093]【白板软件+对象属性】量角器画出弧时，在右侧属性面板改为扇形时，右侧属性面板显示默认有红色填充，但是对象没有填充；建议没有填充，和学科里的扇形保持一致，没有填充
        jObj.remove("FillColor");

        if(fabs( sweepAngleDegree) >360)
        {
            _helper.getItem( "HHMath2DCircle", jObj, item );
            if( item == NULL )
                return;
            float centerX = box.center().x(), centerY = box.center().y();
            float cX = box.right(), cY = centerY;

            jObj["ArtObj_Display"] = QString::number( 0 );
            jObj[ "Discipline_xCreate" ] = QString("%1").arg( centerX );
            jObj[ "Discipline_yCreate" ] = QString("%1").arg( centerY );
            QJsonArray qa;
            qa.push_back( cX );
            qa.push_back( cY );
            jObj[ "Control" ] = qa;
        }
        else
        {
            _helper.getItem( "HHMath2DNewArc", jObj, item );
            if( item == NULL )
                return;

            jObj["StartAngle"] = QString("%1").arg(startAngleDegree);//角度360
            jObj["SweepAngle"] = QString("%1").arg(sweepAngleDegree);
            jObj["Discipline_xCreate"] = QString::number(0);
            jObj["Discipline_yCreate"] = QString::number(0);

            //  modified by weijibin 2018.2.5  start
            //  m_ArcRect
            jObj[ "BoundingBoxArc" ] = QString("%1").arg( box.left() )+ ","
                                        + QString("%1").arg( box.top() )+ ","
                                        + QString("%1").arg( box.right() )+ ","
                                        + QString("%1").arg( box.bottom() );
            //  modified by weijibin 2018.2.5  end
            jObj["KindType"] = QString("%1").arg(nKindType);
            if(1 == nArrowNum)
                jObj[ "ArrowNum" ] = QString::number(1);
            else if(2 == nArrowNum)
                jObj[ "ArrowNum" ] = QString::number(2);
        }
        item->fromJSONObj( jObj );
        item->setParameters("ArtObj_Center","1");
        slide->addPrimitiveItem( item );
    }

    virtual void addMathRectangle( QJsonObject jObj, QMatrix matrix, QRectF rect) {
        Q_UNUSED( matrix );

        T *slide = static_cast< T* >( this );

        IHHPrimitiveItem *item = 0;
        QJsonObject tempObject;
        _helper.getItem( "HHMath2DRectangle", tempObject, item );
        if( item == NULL )
            return;

        jObj[ "Discipline_xCreate" ] = QString("%1").arg( rect.left() );
        jObj[ "Discipline_yCreate" ] = QString("%1").arg( rect.top() );
        QJsonArray qa;
        qa.push_back( rect.right() );
        qa.push_back( rect.top() );
        qa.push_back( rect.left() );
        qa.push_back( rect.bottom() );
        jObj[ "Control" ] = qa;

        item->fromJSONObj( jObj );
        slide->addPrimitiveItem( item );
    }

    virtual void addMathAngle( QJsonObject jObj, QMatrix matrix, QPointF start, QPointF end, QPointF center) {
        Q_UNUSED( matrix );

        T *slide = static_cast< T* >( this );

        IHHPrimitiveItem *item = 0;
        QJsonObject tempObject;
        _helper.getItem( "HHMath2DAngle", tempObject, item );
        if( item == NULL )
            return;

        jObj[ "Discipline_xCreate" ] = QString("%1").arg( center.x() );
        jObj[ "Discipline_yCreate" ] = QString("%1").arg( center.y() );
        QJsonArray qa;
        qa.push_back( end.x() );
        qa.push_back( end.y() );
        qa.push_back( start.x() );
        qa.push_back( start.y() );
        jObj[ "Control" ] = qa;
        item->fromJSONObj( jObj );
        slide->addPrimitiveItem( item );
    }

    virtual void addMathParallelogram( QJsonObject jObj, QMatrix matrix, QPointF leftTop, QPointF rightTop, QPointF rightBottom, QPointF leftBottom) {
        Q_UNUSED( matrix );

        T *slide = static_cast< T* >( this );

        IHHPrimitiveItem *item = 0;
        QJsonObject tempObject;
        _helper.getItem( "HHMath2DParallelogram", tempObject, item );
        if( item == NULL )
            return;

    //    rightTop.ry() = leftTop.y();
    //    leftTop.ry() = rightTop.y();
    //    rightBottom.ry() = leftBottom.y();
        float centerX, centerY;
        centerX = (qMin(leftTop.x(), leftBottom.x()) + qMax(rightTop.x(), rightBottom.x()))/2;
        centerY = (qMin(leftTop.y(), rightTop.y()) + qMax(leftBottom.y(), rightBottom.y()))/2;

        jObj[ "Discipline_xCreate" ] = QString("%1").arg( centerX );
        jObj[ "Discipline_yCreate" ] = QString("%1").arg( centerY );
        QJsonArray qa;
        qa.push_back( (rightTop.x() + rightBottom.x())/2 );
        qa.push_back( centerY );
        qa.push_back( centerX );
        qa.push_back( (leftBottom.y() + rightBottom.y())/2 );
        qa.push_back( leftTop.x() );
        qa.push_back( leftTop.y() );
        jObj[ "Control" ] = qa;
        jObj[ "BoundingBox" ] = QString("%1").arg( qMin(leftTop.x(), leftBottom.x()) )+ ","
                                    + QString("%1").arg( qMin(leftTop.y(), rightTop.y()) )+ ","
                                    + QString("%1").arg( qMax(rightTop.x(), rightBottom.x()) )+ ","
                                    + QString("%1").arg( qMax(leftBottom.y(), rightBottom.y()) );

        item->fromJSONObj( jObj );
        slide->addPrimitiveItem( item );
    }

    virtual void addMathTriangle( QJsonObject jObj, QMatrix matrix, QPointF start, QPointF two, QPointF three) {
        Q_UNUSED( matrix );

        T *slide = static_cast< T* >( this );

        IHHPrimitiveItem *item = 0;
        QJsonObject tempObject;
        _helper.getItem( "HHMath2DTriangle", tempObject, item );
        if( item == NULL )
            return;

        jObj[ "Discipline_xCreate" ] = QString("%1").arg( start.x() );
        jObj[ "Discipline_yCreate" ] = QString("%1").arg( start.y() );
        QJsonArray qa;
        qa.push_back( start.x() );
        qa.push_back( start.y() );
        qa.push_back( two.x() );
        qa.push_back( two.y() );
        qa.push_back( three.x() );
        qa.push_back( three.y() );
        jObj[ "Control" ] = qa;

        item->fromJSONObj( jObj );
        slide->addPrimitiveItem( item );
    }

    virtual void addMathPolyline( QJsonObject jObj, QMatrix matrix, QString strPts) {
        Q_UNUSED( matrix );

        T *slide = static_cast< T* >( this );

        IHHPrimitiveItem *item = 0;
        QJsonObject tempObject;
        _helper.getItem( "HHMath2DPolyline", tempObject, item );
        if( item == NULL )
            return;

        jObj["XYValue"] = strPts;
        jObj[ "Discipline_xCreate" ] = QString::number( 0 );
        jObj[ "Discipline_yCreate" ] = QString::number( 0 );

        item->fromJSONObj( jObj );
        slide->addPrimitiveItem( item );
    }

    virtual void setToolParent(QWidget* parent)
    {
        for(int i = 0; i < m_tools.count(); i++)
        {
            if(m_tools.at(i))
            {
//                QWidget *pCurtParent = m_tools.at(i)->parentWidget();
//                if(pCurtParent)
//                {
//                    pCurtParent->removeEventFilter(m_tools.at(i));
//                }

                m_tools.at(i)->setParent(parent);
                parent->installEventFilter(m_tools.at(i));
            }
        }
    }
protected:
    // 保存工具（三角板，直尺，量角器，圆规）
    QVector< QWidget* > m_tools;

protected:
    // ================ 工具（三角板，直尺，量角器，圆规） =================
    // 增加工具
    virtual void addToolWidget(QWidget *tool) {
        m_tools.push_back(tool);
    }

    // 删除工具
    virtual void removeToolWidget(QWidget *tool) {
        QVector<QWidget*>::iterator iter;
        for (iter = m_tools.begin(); iter != m_tools.end(); )
        {
            if (*iter == tool) {
                //
                iter = m_tools.erase(iter);
            }
            else {
                //
                iter++;
            }
        }
    }


    //
    void showTools() {
        int size = m_tools.size();
        for (int i = 0; i < size; i++) {
            m_tools[i]->show();
        }
    }

    //
    void hideTools() {
        int size = m_tools.size();
        for (int i = 0; i < size; i++) {
            m_tools[i]->hide();
        }
    }
    TemplateSpecialItemManagerHelper _helper;
};

#endif // HHSPECIALITEMMANAGER_H
