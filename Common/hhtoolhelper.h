#ifndef HHTOOLHELPER_H
#define HHTOOLHELPER_H

#include <QString>
#include <QUuid>
#include <QPointF>
#include <QMatrix>
#include <QRectF>
#include <QRect>
#include <QPolygon>
#include <QPolygonF>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVariantMap>
#include <QDateTime>
#include <QColor>
#include <QGraphicsItem>
#include <QDir>
#include <QFile>
#include "qmath.h"
#include "math.h"

#include "ihhprimitiveitem.h"


#define EMIN    1E-6
#define PI      3.1415926

class HHToolHelper
{
public:
    static IHHPrimitiveItem* qGraphisItemToPrimitiveItem( QGraphicsItem* qItem ) {
        return qvariant_cast< IHHPrimitiveItem* >( qItem->data( 0 ) );
    }

    static QGraphicsItem* primitiveItemToQGraphisItem( IHHPrimitiveItem* item ) {
        return qobject_cast< QGraphicsItem* >( item->getObject() );
    }

    static QSize getSizeFromProportion( QString strProportion ) {
        if( strProportion == "16:9" )
            return QSize( 1920, 1080 );
        else if( strProportion == "16:10" )
            return QSize( 1920, 1200 );
        else if( strProportion == "4:3" )
            return QSize( 1920, 1440 );
        else
            return QSize( 1920, 1080 );
    }

    static QString getProportionFromSize( QSize size ) {
        if( size == QSize( 1920, 1080 ) )
            return "16:9";
        else if( size == QSize( 1920, 1200 ) )
            return "16:10";
        else if( size == QSize( 1920, 1440 ) )
            return "4:3";
        else
            return "16:9";
    }

    static QString getObjectID() {
        static int adjustID = 1;
        qint64 time = QDateTime::currentMSecsSinceEpoch();
        adjustID ++;
        time = time + adjustID;
        return QString::number( time );
    }

    static QSize getMinDisSize( QRectF rect ) {
        float rate = rect.width() / rect.height();
        float rate43 = 1.3333f;
        float rate1610 = 1.6f;
        float rate169 = 1.7777f;

        float rate1 = qAbs( rate - rate43 );
        float rate2 = qAbs( rate - rate169 );
        float rate3 = qAbs( rate - rate1610 );

        if( rate1 < rate2 ) {
            if( rate1 < rate3 )
                return QSize( 1440, 1080 );
            else
                return QSize( 1728, 1080 );
        } else {
            if( rate2 < rate3 )
                return QSize( 1920, 1080 );
            else
                return QSize( 1728, 1080 );
        }
    }

    static QMatrix computeMatrixAccordTwoRectF( QRectF source, QRectF target ) {
        float xRate = target.width() / source.width();
        float yRate = target.height() / source.height();
        float rate = xRate;
        if( yRate < rate )
            rate = yRate;
        QMatrix scaleMatrix;
        scaleMatrix.scale( rate, rate );
        QPointF pt = scaleMatrix.map( source.center() );
        QMatrix translateMatrix;
        translateMatrix.translate( target.center().x() - pt.x(), target.center().y() - pt.y() );
        return scaleMatrix * translateMatrix;
    }

    static QRectF computeSameRateRange( QRectF source, QRectF target ) {
        float xRate = target.width() * 1.0 / source.width();
        float yRate = target.height() * 1.0 / source.height();
        float rate = xRate;
        if( yRate < rate )
            rate = yRate;
        float rangeWidth = source.width() * rate;
        float rangeHeight = source.height() * rate;
        float x = ( target.width() - rangeWidth ) / 2 + target.left();
        float y = ( target.height() - rangeHeight ) / 2 + target.top();
        return QRectF( x, y, rangeWidth, rangeHeight );
    }

    static QRectF computeSameRateRangeMax( QRectF source, QRectF target ) {
        float xRate = target.width() * 1.0 / source.width();
        float yRate = target.height() * 1.0 / source.height();
        float rate = xRate;
        if( yRate > rate )
            rate = yRate;
        float rangeWidth = source.width() * rate;
        float rangeHeight = source.height() * rate;
        float x = ( target.width() - rangeWidth ) / 2 + target.left();
        float y = ( target.height() - rangeHeight ) / 2 + target.top();
        return QRectF( x, y, rangeWidth, rangeHeight );
    }


    static QJsonArray getJsonArray( QStringList list ) {
        QJsonArray array;
        for( int i = 0 ; i < list.size() ; i ++ ) {
            array.push_back( list[ i ] );
        }
        return array;
    }

    static QJsonArray getJsonArray( QString str1 ) {
        QJsonArray array;
        array.push_back( str1 );
        return array;
    }

    static QJsonArray getJsonArray( QString str1, QString str2 ) {
        QJsonArray array;
        array.push_back( str1 );
        array.push_back( str2 );
        return array;
    }

    static QJsonArray getJsonArray( QString str1, QString str2, QString str3 ) {
        QJsonArray array;
        array.push_back( str1 );
        array.push_back( str2 );
        array.push_back( str3 );
        return array;
    }

    static QRect rectFToRect( QRectF rect ) {
        return QRect( rect.left(), rect.top(), rect.width(), rect.height() );
    }

    static QPolygon polyFToPoly( QPolygonF poly ) {
        QPolygon qp;
        int size = poly.size();
        for( int i = 0 ; i < size ; i ++ )
            qp.push_back( QPoint( poly[ i ].x(), poly[ i ].y() ) );
        return qp;
    }

    static float angleOfLine( float xStart, float yStart, float xEnd, float yEnd, bool bTranToDescartes ) {
        if( bTranToDescartes ) {
            yStart = - yStart;
            yEnd = - yEnd;
        }
        double dAngle = 0;
        if( xStart == xEnd ) {
            if( yStart > yEnd )
                dAngle = PI * 3 / 2;
            if( yStart < yEnd )
                dAngle = PI / 2;
        } else {
            float k = ( yEnd - yStart ) / ( xEnd - xStart );
            float angle = atan( k );
            if( angle > 0 ) {
                if( yStart < yEnd )
                    dAngle = angle;
                else if( yStart > yEnd )
                    dAngle = angle + PI;
            } else if( angle == 0 ) {
                if( xStart > xEnd )
                    dAngle = PI;
                else if( xStart < xEnd )
                    dAngle = 0;
            } else {
                if( yStart > yEnd )
                    dAngle = angle + 2 * PI;
                else if( yStart < yEnd )
                    dAngle = angle + PI;
            }
        }
        return ( float )dAngle;
    }

    static QPointF getPtAccordBaseDistance( float baseX, float baseY, float desX, float desY, float r ) {
        float dis = sqrtf( ( baseX - desX ) * ( baseX - desX ) + ( baseY - desY ) * ( baseY - desY ) );
        float rate = r / dis;
        return QPointF( rate * ( desX - baseX ) + baseX, rate * ( desY - baseY ) + baseY );
    }

    static QPointF getPtAccordDesDistance( float baseX, float baseY, float desX, float desY, float r  ) {
        float dis = sqrtf( ( baseX - desX ) * ( baseX - desX ) + ( baseY - desY ) * ( baseY - desY ) );
        float rate = ( r + dis ) / dis;
        return QPointF( rate * ( desX - baseX ) + baseX, rate * ( desY - baseY ) + baseY );
    }

    static float getVerticalDis( float startX, float startY, float endX, float endY, float x, float y ) {
        float A = endY - startY;
        float B = startX - endX;
        float C = ( endX - startX ) * endY - ( endY - startY ) * endX;
        float D = A * y - B * x;
        float temp1 = A * A + B * B;
        float temp2 = A * C + B * D;
        float temp3 = A * D - B * C;
        if( fabs( temp1 ) <= EMIN )
            return 0;
        else {
            float vertX = - temp2 / temp1;
            float vertY = temp3 / temp1;
            return sqrtf( ( vertX - x ) * ( vertX - x ) + ( vertY - y ) * ( vertY - y) );
        }
    }

    static QPointF getVerticalPt( float startX, float startY, float endX, float endY, float x, float y ) {
        float A = endY - startY;
        float B = startX - endX;
        float C = ( endX - startX ) * endY - ( endY - startY ) * endX;
        float D = A * y - B * x;
        float temp1 = A * A + B * B;
        float temp2 = A * C + B * D;
        float temp3 = A * D - B * C;
        if( fabs( temp1 ) <= EMIN )
            return QPointF( startX, startY );
        else {
            float vertX = - temp2 / temp1;
            float vertY = temp3 / temp1;
            return QPointF( vertX, vertY );
        }
    }

    static float getRate( float pX1, float pY1, float pX2, float pY2, float qX1, float qY1 ) {
        float dis1 = pX2 - pX1;
        float dis2 = qX1 - pX1;
        if( fabs( dis1 ) <= EMIN ) {
            dis1 = pY2 - pY1;
            dis2 = qY1 - pY1;
        }
        return dis2 / dis1;
    }

    static QVariantMap getLineAccordTowPt( float x1, float y1, float x2, float y2 ) {
        QVariantMap qm;
        qm[ "A" ] = y2 - y1;
        qm[ "B" ] = x1 - x2;
        qm[ "C" ] = ( x2 - x1 ) * y2 - ( y2 - y1 ) * x2;
        return qm;
    }

    static QVariantMap getLineWithPointAndDirection( float pX1, float pY1, float pX2, float pY2, float qX1, float qY1 ) {
        QPointF start( qX1, qY1 );
        QPointF end;

        float A = pY2 - pY1;
        float B = pX1 - pX2;
        float C = - ( A * start.x() + B * start.y() );

        if( EMIN < fabs( A ) ) {
            end.ry() = start.y() + 20;
            end.rx() = - ( B * end.y() + C ) / A;
        } else {
            end.rx() = start.x() + 20;
            end.ry() = - ( A * end.x() + C ) / B;
        }
        QVariantMap qm;
        qm[ "start" ] = start;
        qm[ "end" ] = end;
        return qm;
    }

    static QRectF inflateRect( QRectF rect, float value ) {
        rect.setLeft( rect.left() - value );
        rect.setTop( rect.top() - value );
        rect.setRight( rect.right() + value );
        rect.setBottom( rect.bottom() + value );
        return rect;
    }

    static float twoPointDistance( QPointF pt1, QPointF pt2 ) {
        float x = pt1.x() - pt2.x();
        float y = pt1.y() - pt2.y();
        return sqrtf( x * x + y * y );
    }

    static QMatrix scale2( float rate1, float rate2, float orgX, float orgY ) {
        QMatrix matrix1;
        matrix1.translate( - orgX, - orgY );
        QMatrix matrix2;
        matrix2.scale( rate1, rate2 );
        QMatrix matrix3;
        matrix3.translate( orgX, orgY );
        QMatrix matrix = matrix1 * matrix2 * matrix3;
        return matrix;
    }

    static QMatrix rotate2( float angle, QPointF point ) {
        QMatrix matrix1;
        matrix1.translate( -point.rx(), -point.ry() );
        QMatrix matrix2;
        matrix2.rotate( angle );
        QMatrix matrix3;
        matrix3.translate( point.rx(), point.ry() );
        QMatrix matrix = matrix1 * matrix2 * matrix3;
        return matrix;
    }


    static QPointF rotate3( float angle, float xPt, float yPt, float xCenter, float yCenter  )  {
            xPt -= xCenter;
            yPt -= yCenter;

            float dcos  = qCos( angle );
            float dsin  = qSin( angle );
            float t  = xPt;
            xPt = t * dcos - yPt * dsin;
            yPt = t * dsin + yPt * dcos;

            xPt += xCenter;
            yPt += yCenter;

            return QPointF( xPt, yPt );
    }

    static QMatrix translation( float offsetX , float offsetY  )  {
        QMatrix temp;
        temp.translate( offsetX, offsetY );
        return temp;
    }

    static QMatrix concat2( QMatrix matrix1 , QMatrix matrix2  )  {
        QMatrix sourceMatrix;
        sourceMatrix = matrix1 * matrix2;
        return sourceMatrix;
    }

    static QMatrix twoRectTransform( QRectF rectOld, QRectF rectNew ) {
        float rangeWidth = rectNew.width();
        float rangeHeight = rectNew.height();
        float centerX = rectNew.center().x();
        float centerY = rectNew.center().y();

        float left = rectOld.left();
        float top = rectOld.top();
        float rate1 = rangeWidth / rectOld.width();
        float rate2 = rangeHeight / rectOld.height();
        float rate = rate1;
        if( rate2 < rate )
            rate = rate2;
        QMatrix matrix1 = scale2( rate, rate, left, top );
        QPointF newCenter = matrix1.map( rectOld.center() );
        QMatrix matrix2;
        matrix2.translate( centerX - newCenter.x(), centerY - newCenter.y() );
        QMatrix matrix = matrix1 * matrix2;
        return matrix;
    }

    static void transformPoints( QMatrix matrix, QVector< QPointF > points, QVector< QPointF >& newPoints ) {
        for( int i = 0 ; i < points.size() ; i ++ )
            newPoints.push_back( matrix.map( points[ i ] ) );
    }

    static void transformBoundingBox( QRectF boundingBox, QMatrix matrix, QVector< QPointF >& points ) {
        points.push_back( boundingBox.topLeft() );
        points.push_back( boundingBox.topRight() );
        points.push_back( boundingBox.bottomRight() );
        points.push_back( boundingBox.bottomLeft() );
        if( !matrix.isIdentity() )
            transformPoints( points, matrix );
    }

    static void transformPoints( QVector< QPointF >& points, QMatrix matrix ) {
        QVector< QPointF > oldPoints = points;
        points.clear();
        for( int i = 0 ; i < oldPoints.size() ; i ++ )
            points.push_back( matrix.map( oldPoints[ i ] ) );
    }

    static QRectF computeBoundingBox2( QVector< QPointF >& points ) {
		if (0 == points.size())
		{
			return QRectF();
		}
		QRectF rect;
        rect.setTopLeft( points[ 0 ] );
        rect.setBottomRight( points[ 0 ] );
        for( int i = 0 ; i < points.size() ; i ++ ) {
            rect.setLeft( fminf( rect.left(), points[ i ].x() ) );
            rect.setRight( fmaxf( rect.right(), points[ i ].x() ) );
            rect.setTop( fminf( rect.top(), points[ i ].y() ) );
            rect.setBottom( fmaxf( rect.bottom(), points[ i ].y() ) );
        }
        return rect;
    }

    static QVariantMap computeTransformPara( QMatrix matrix ) {
        QVariantMap qm;
        QPointF start1( 0, - 1 );
        QPointF end1( 0, 1 );
        QPointF center1 = ( start1 + end1 ) / 2;
        QPointF start2 = matrix.map( start1 );
        QPointF end2 = matrix.map( end1 );
        QPointF center2 = ( start2 + end2 ) / 2;
        float angle = angleOfLine( start2.x(), start2.y(), end2.x(), end2.y(), true ) - angleOfLine( start1.x(), start1.y(), end1.x(), end1.y(), true );
        float dis1 = twoPointDistance( start1, end1 );
        float dis2 = twoPointDistance( start2, end2 );
        qm[ "centerX" ] = center2.x();
        qm[ "centerY" ] = center2.y();
        qm[ "offsetX" ] = center2.x() - center1.x();
        qm[ "offsetY" ] = center2.y() - center1.y();
        qm[ "angle" ] = angle;
        qm[ "scale" ] = dis2 / dis1;
        return qm;
    }

    static QString convertVF2String( QVector< QPointF > points ) {
        QString str;
        for( int i = 0 ; i < points.size() ; i ++ ) {
            QString split = ( i == 0 )?"":",";
            str += split;
            str += QString::number( points.at( i ).x() );
            str += ",";
            str += QString::number( points.at( i ).y() );
        }
        return str;
    }

    static QString convertQC2String( QColor color ) {
        QString str;
        str += QString::number( color.red() ) + ",";
        str += QString::number( color.green() ) + ",";
        str += QString::number( color.blue() );
        return str;
    }

    static QString convert32QC2String( QColor color ) {
        QString str;
        str += QString::number( color.alpha() ) + ",";
        str += QString::number( color.red() ) + ",";
        str += QString::number( color.green() ) + ",";
        str += QString::number( color.blue() );
        return str;
    }

    static QString convertQC2String( long int color32 ) {

        int alpha = color32 >> 24 & 0xFF;
        int red = color32 >> 16 & 0xFF;
        int green = color32 >> 8 & 0xFF;
        int blue = color32 & 0xFF;

        QString str;
        str += QString::number( red ) + ",";
        str += QString::number( green ) + ",";
        str += QString::number( blue ) + ",";
        str += QString::number( alpha );
        return str;
    }





     static QString convertQM2String( QMatrix matrix ) {
        QString str;
        str += QString::number( matrix.m11() ) + ",";
        str += QString::number( matrix.m12() ) + ",";
        str += QString::number( matrix.m21() ) + ",";
        str += QString::number( matrix.m22() ) + ",";
        str += QString::number( matrix.dx() ) + ",";
        str += QString::number( matrix.dy() );
        return str;
    }

     static QStringList findFiles( QString strDir )
     {
         QStringList fileList;
         QDir dir(strDir);
         if( !dir.exists() )
             return fileList;
         QFileInfoList info = dir.entryInfoList();
         if( info.size() <= 0 )
             return fileList;
         for( int i = 0; i < info.size(); i++ )
         {
             if( info.at(i).fileName() != "." && info.at(i).fileName() != ".." )
                 fileList.push_back(info.at(i).fileName());
         }
         return fileList;
     }

     // QString >> QJson
     static QJsonObject getJsonObjectFromString(const QString jsonString)
     {
         QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toLocal8Bit().data());
         if( jsonDocument.isNull() ){
     //        qDebug()<< "===> please check the string "<< jsonString.toLocal8Bit().data();
         }
         QJsonObject jsonObject = jsonDocument.object();
         return jsonObject;
     }

     // QJson >> QString
     static QString getStringFromJsonObject(const QJsonObject& jsonObject)
     {
         return QString(QJsonDocument(jsonObject).toJson());
     }


     // get menu intersection of multi items
     static QVector< HHEditProperty > getProperty_intersection(QVector< IHHPrimitiveItem* > items, int level)
     {                
         QVector< HHEditProperty > vecIntersection;
         QMap<QString, HHEditProperty> mapTmp;

         vecIntersection.clear();
         mapTmp.clear();

         if(items.count()<1)
             return vecIntersection;

         int nItemsCount = items.count();
         for(int k=0; k<nItemsCount; k++)
         {
             IHHPrimitiveItem *priItem = items.at(k);

             QVector< HHEditProperty > itemPropertys_0 = priItem->getProperty(level);
             int nCount = itemPropertys_0.count();

             for (int j = 0; j < nCount; ++j)
             {
                 HHEditProperty editProperty = itemPropertys_0.at(j);
                 mapTmp.insertMulti(editProperty.id, editProperty);
             }
         }

         // QMap auto sort in order, so must not use map order
         IHHPrimitiveItem *priItem = items.at(0);

         QVector< HHEditProperty > itemPropertys_0 = priItem->getProperty(level);
         int nCount = itemPropertys_0.count();

         for (int j = 0; j < nCount; ++j)
         {
             HHEditProperty editProperty = itemPropertys_0.at(j);

             QString strID = editProperty.id;
             int nTmpCount = mapTmp.count(strID);

             if(nTmpCount == nItemsCount)
             {
                 vecIntersection.append(editProperty);
             }
         }

         return vecIntersection;
     }

     // get right uiproperty intersection of multi items
     static QVector< HHEditProperty > getUIProperty_intersection(QVector< IHHPrimitiveItem* > items, int level)
     {
         QVector< HHEditProperty > vecIntersection;
         QMap<QString, HHEditProperty> mapTmp;

         vecIntersection.clear();
         mapTmp.clear();

         if(items.count()<1)
             return vecIntersection;

         int nItemsCount = items.count();
         for(int k=0; k<nItemsCount; k++)
         {
             IHHPrimitiveItem *priItem = items.at(k);

             QVector< HHEditProperty > itemPropertys_0 = priItem->getUIProperty(level);
             int nCount = itemPropertys_0.count();

             for (int j = 0; j < nCount; ++j)
             {
                 HHEditProperty editProperty = itemPropertys_0.at(j);
                 mapTmp.insertMulti(editProperty.id, editProperty);
             }
         }

         // QMap auto sort in order, so must not use map order
         IHHPrimitiveItem *priItem = items.at(0);

         QVector< HHEditProperty > itemPropertys_0 = priItem->getUIProperty(level);
         int nCount = itemPropertys_0.count();

         for (int j = 0; j < nCount; ++j)
         {
             HHEditProperty editProperty = itemPropertys_0.at(j);

             QString strID = editProperty.id;
             int nTmpCount = mapTmp.count(strID);

             if(nTmpCount == nItemsCount)
             {
                 vecIntersection.append(editProperty);
             }
         }

         return vecIntersection;
     }

};

#endif
