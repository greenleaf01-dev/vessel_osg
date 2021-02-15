#include "hhmath.h"
#include "qmath.h"
#include "hhtoolhelper.h"

HHMath::HHMath()
{

}

QPointF* HHMath::getInterSectPtOfLines( float pX1, float pY1, float pX2, float pY2,
                                       float qX1, float qY1, float qX2, float qY2, int type )  {
    float a1, b1,c1, a2, b2,  c2, data1, data2,data3, t, s;
    a1 = pX2 - pX1;	b1 = qX1 - qX2;	c1 = qX1 - pX1;
    a2 = pY2 - pY1;	b2 = qY1 - qY2;	c2 = qY1 - pY1;
    data1 = a1 * b2 - a2 * b1;

    /// 两条直线平行
    if( qAbs( data1 ) < EMIN )
        return NULL;
    data2 = c1 * b2 - c2 * b1;
    data3 = c1 * a2 - c2 * a1;
    t = data2 / data1;
    s = - data3 / data1;
    QPointF* inter = new QPointF();
    inter->rx() = ( pX2 - pX1 ) * t + pX1;
    inter->ry() = ( pY2 - pY1 ) * t + pY1;
    /// 1:line
    /// 2:arrow
    /// 3:segment
    if( type == 2 || type == 3 ) {
        if( t < 0 )
            return NULL;
        if( s < 0 )
            return NULL;
    }
    if( type == 3 ) {
        if( 1 < t )
            return NULL;
        if( 1 < s )
            return NULL;
    }
    return inter;
}


QVariantMap HHMath::getLeftRightInterSectPtOfLineAndCircle( float pX1, float pY1, float pX2,
                                                            float pY2, float qX1, float qY1, float radius){

    QPointF ptVert  = getVerticalPt( pX1, pY1, pX2, pY2, qX1, qY1 );
    float dis  = qSqrt( ( ptVert.rx() - qX1 ) * ( ptVert.rx() - qX1 ) + ( ptVert.ry() - qY1 ) * ( ptVert.ry() - qY1 ) );


    QVariantMap  variantMap;

    if( qAbs( radius - dis ) <= EMIN ) {
        variantMap.insert( "left", ptVert );
        variantMap.insert( "right", ptVert );
        return variantMap;
     }

    if( radius < dis )
        return variantMap;

    /// 得到圆心和垂足连线同圆的交点
    QPointF ptOnCircle = getPtAccordBaseDistance( qX1, qY1, ptVert.rx(), ptVert.ry(), radius );
    /// 求旋转角度
    float angle  = qAcos( dis / radius );
    /// 求解两个交点
    QMatrix matrix = HHToolHelper::rotate2( angle, QPointF( qX1, qY1 ) );
    QMatrix matrix1 = matrix.translate( ptOnCircle.rx(), ptOnCircle.ry() );
    QPointF ptInter1( matrix1.dx(), matrix1.dy() );
    //float r1  = getRate( pX1, pY1, pX2, pY2, ptInter1.rx(), ptInter1.ry() );
    matrix = HHToolHelper::rotate2( - angle, QPointF( qX1, qY1 ) );

    QMatrix matrix2 = matrix.translate( ptOnCircle.rx(), ptOnCircle.ry() );
    QPointF ptInter2( matrix2.dx(), matrix2.dy() );;
    //float r2  = getRate( pX1, pY1, pX2, pY2, ptInter2.rx(), ptInter2.ry() );
    /// 保证r1的数值小
    variantMap.insert( "left", ptInter1 );
    variantMap.insert( "right", ptInter2 );
    return variantMap;
}

float HHMath::getRate( float pX1 , float pY1 , float pX2, float pY2 , float qX1 , float qY1  )  {
    float dis1  = pX2 - pX1;
    float dis2  = qX1 - pX1;
    if( qAbs( dis1 ) <= EMIN ) {
        dis1 = pY2 - pY1;
        dis2 = qY1 - pY1;
    }
    return dis2 / dis1;
}


QVariantMap HHMath::getInterSectPtOfLineAndCircle( float pX1, float pY1, float pX2,

                                                   float pY2, float qX1, float qY1, float radius, int type ){
    QPointF ptVert  = getVerticalPt( pX1, pY1, pX2, pY2, qX1, qY1 );
    float dis  = qSqrt( ( ptVert.rx() - qX1 ) * ( ptVert.rx() - qX1 ) + ( ptVert.ry() - qY1 ) * ( ptVert.ry() - qY1 ) );


    QVariantMap  variantMap;
    if( radius < dis )
        return variantMap;

    if( qAbs( radius - dis ) <= EMIN ) {
        variantMap.insert( "near", ptVert );
        variantMap.insert( "far", ptVert );
        return variantMap;
     }

    /// 得到圆心和垂足连线同圆的交点
    QPointF ptOnCircle = getPtAccordBaseDistance( qX1, qY1, ptVert.rx(), ptVert.ry(), radius );
    /// 求旋转角度
    float angle  = qAcos( dis / radius );
    /// 求解两个交点
    QMatrix matrix = HHToolHelper::rotate2( angle, QPointF( qX1, qY1 ) );
    QMatrix matrix1 = matrix.translate( ptOnCircle.rx(), ptOnCircle.ry() );
    QPointF ptInter1( matrix1.dx(), matrix1.dy() );
    float r1  = getRate( pX1, pY1, pX2, pY2, ptInter1.rx(), ptInter1.ry() );
    matrix = HHToolHelper::rotate2( - angle, QPointF( qX1, qY1 ) );

    QMatrix matrix2 = matrix.translate( ptOnCircle.rx(), ptOnCircle.ry() );
    QPointF ptInter2( matrix2.dx(), matrix2.dy() );;
    float r2  = getRate( pX1, pY1, pX2, pY2, ptInter2.rx(), ptInter2.ry() );

    /// 保证r1的数值小
    if( r2 < r1 ) {
        float temp1  = r1;
        r1 = r2;
        r2 = temp1;

        QPointF temp2  = ptInter1;
        ptInter1 = ptInter2;
        ptInter2 = temp2;
    }
    ///
    if( type == 2 ) {
        if( r1 < 0 && r2 < 0 )
            return variantMap;
        if( r1 < 0 && 0 <= r2 ) {
            variantMap.insert( "near", ptInter2 );
            variantMap.insert( "far", NULL );
            return variantMap;
        }

        if( 0 <= r1 ) {
            variantMap.insert( "near", ptInter1 );
            variantMap.insert( "far", ptInter2 );
            return variantMap;
        }
    }

    return variantMap;
}

/**
 * 在线上，根据到base点距离确定点
 * @param baseX {Number} 开始点的x坐标
 * @param baseY {Number} 开始点的y坐标
 * @param desX {Number} 结束点的x坐标
 * @param desY {Number} 结束点的y坐标
 * @param r {Number} 距离
 * @return {Point} 点
 */
QPointF HHMath::getPtAccordBaseDistance( float baseX , float baseY , float desX, float desY, float r  ) {

    float dis  = qSqrt( ( baseX - desX ) * ( baseX - desX ) + ( baseY - desY ) * ( baseY - desY ) );
    float rate  = r / dis;
    QPointF point( rate * ( desX - baseX ) + baseX, rate * ( desY - baseY ) + baseY  );
    return point;
}

/**
     * 在线上，根据到des点距离确定点
     * @param baseX {Number} 开始点的x坐标
     * @param baseY {Number} 开始点的y坐标
     * @param desX {Number} 结束点的x坐标
     * @param desY {Number} 结束点的y坐标
     * @param r {Number} 距离
     * @return {Point} 点
     */
QPointF HHMath::getPtAccordDesDistance(  float baseX , float baseY , float desX, float desY, float r  )  {
    float dis  = qSqrt( ( baseX - desX ) * ( baseX - desX ) + ( baseY - desY ) * ( baseY - desY ) );
    float rate  =( r + dis ) / dis;
    QPointF point( rate * ( desX - baseX ) + baseX, rate * ( desY - baseY ) + baseY  );
    return point;
}


QPointF HHMath::getVerticalPt( float startX, float startY, float endX, float endY, float x , float y  )  {
    float A  = endY - startY;
    float B  = startX - endX;
    float C  = ( endX - startX ) * endY - ( endY - startY ) * endX;
    float D  = A * y - B * x;
    float temp1  = A * A + B * B;
    float temp2  = A * C + B * D;
    float temp3  = A * D - B * C;
    if( qAbs( temp1 ) <= EMIN )
        return QPointF( startX, startY );
    else {
        float vertX  = - temp2 / temp1;
        float vertY  = temp3 / temp1;
        return QPointF( vertX, vertY );
    }
}


float  HHMath::angleOfLine( float xStart , float yStart , float xEnd , float yEnd , bool bTranToDescartes  )  {
    if( bTranToDescartes ) {
        yStart = - yStart;
        yEnd = - yEnd;
    }
    float dAngle  = 0;
    if( xStart == xEnd )
    {
        if( yStart > yEnd )
            dAngle = M_PI * 3 / 2;
        if( yStart < yEnd )
            dAngle = M_PI / 2;
    } else {
        float k  = ( yEnd - yStart ) / ( xEnd - xStart );
        float angle  = qAtan( k );
        if( angle > 0 )
        {
            if( yStart < yEnd )
                dAngle = angle;
            else if( yStart > yEnd )
                dAngle = angle + M_PI;
        }
        else if( angle == 0 )
        {
            if( xStart > xEnd )
                dAngle = M_PI;
            else if( xStart < xEnd )
                dAngle = 0;
        }
        else
        {
            if( yStart > yEnd )
                dAngle = angle + 2 *M_PI;
            else if( yStart < yEnd )
                dAngle = angle + M_PI;
        }
    }
    return dAngle;
}

float HHMath::twoPtDistance( float xStart, float yStart, float xEnd, float yEnd )
{
    float xIncre = xEnd - xStart;
    float yIncre = yEnd - yStart;
    return sqrtf( xIncre * xIncre + yIncre * yIncre );
}


float HHMath::twoPtDistance( QPointF start, QPointF end )
{
    float xIncre = end.rx() - start.rx();
    float yIncre = end.ry() - start.ry();
    return sqrtf( xIncre * xIncre + yIncre * yIncre );
}


float HHMath::getAngleOfTwoLine(float xStart, float yStart, float xEnd1, float yEnd1, float xEnd2, float yEnd2)
{
    float A = twoPtDistance( xStart, yStart, xEnd1, yEnd1 );
    float B = twoPtDistance( xStart, yStart, xEnd2, yEnd2 );
    float C = twoPtDistance( xEnd1, yEnd1, xEnd2, yEnd2 );
    float plus = 0.0;

    if( EMIN < abs( A * B ) )
        plus = ( A * A + B * B - C * C ) / ( 2 * A * B );
    else
        plus = 1;

    if( 1 <= plus )
        return 0;
    else if( plus <= - 1 )
        return PI;
    else
        return acosf( plus );
}
