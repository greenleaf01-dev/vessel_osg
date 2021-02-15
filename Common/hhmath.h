#ifndef HHMATH_H
#define HHMATH_H

#include "QPointF"
#include "QVariantMap"

#define  EMIN 1E-6

class HHMath
{
public:
    HHMath();

public:
    static QPointF* getInterSectPtOfLines( float pX1, float pY1, float pX2, float pY2,
                                           float qX1, float qY1, float qX2, float qY2, int type );

    static QVariantMap getLeftRightInterSectPtOfLineAndCircle( float pX1, float pY1, float pX2,
                                                                float pY2, float qX1, float qY1, float radius);


    static QVariantMap getInterSectPtOfLineAndCircle( float pX1, float pY1, float pX2,
                                                                float pY2, float qX1, float qY1, float radius, int type );

    static QPointF getPtAccordBaseDistance( float baseX , float baseY , float desX, float desY, float r  );

    static QPointF getPtAccordDesDistance(  float baseX , float baseY , float desX, float desY, float r  );

    static QPointF getVerticalPt( float startX, float startY, float endX, float endY, float x , float y  );


    static float getRate( float pX1 , float pY1 , float pX2, float pY2 , float qX1 , float qY1  );

    static float  angleOfLine( float xStart , float yStart , float xEnd , float yEnd , bool bTranToDescartes  );

    static float twoPtDistance( float xStart, float yStart, float xEnd, float yEnd );
    static float twoPtDistance( QPointF start, QPointF end );

    static float getAngleOfTwoLine( float xStart, float yStart, float xEnd1, float yEnd1, float xEnd2, float yEnd2 );

};

#endif // HHMATH_H
