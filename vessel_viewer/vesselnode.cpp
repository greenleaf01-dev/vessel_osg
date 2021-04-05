

#include<osgViewer/Viewer>
#include<osgDB/ReadFile>
#include <osg/Material>
#include <osg/PolygonMode>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>
#include<osg/LineWidth>
#include <osgText/Text>
#include <osgText/Text3D>
#include <osg/ShapeDrawable>
#include <osgUtil/Simplifier>
#include <osg/Texture1D>
#include <osg/Texture2D>
#include <osg/TextureCubeMap>
#include <osg/Depth>
#include <osg/LineStipple>
#include <osg/CullFace>
#include <osg/FrontFace>
#include <osg/Stencil>
#include <osg/ColorMask>
#include <osg/PolygonOffset>
#include <sstream>
#include <osgFX/Outline>
#include <osgGA/GUIEventHandler>
#include <osgUtil/LineSegmentIntersector>
#include <osg/Multisample>
#include <osg/BlendFunc>
#include <osgUtil/SmoothingVisitor>
#include <tuple>
#include <osg/PolygonOffset>
#include <QString>
#include <QDir>

#include "vesselnode.h"

#include "wykobi/wykobi_instantiate.hpp"
#include "wykobi/wykobi.hpp"

namespace SelfSkinVessel
{
static std::vector<osg::ref_ptr<osg::Material>>  vecMaterial;
static double s_fLength = 0.5;
static double s_fMinLength = 0.2;
static const int s_nDevidedCount = 50;
static const double local_Epsilon = 1e-4;
static const double fMaxMul = 1.0;

typedef std::vector<std::pair<std::vector<osg::Vec3>, std::wstring>>  vecSegment;

typedef  std::tuple<std::vector<osg::Vec3>, std::wstring, osg::Vec3> TVesselElementType;
typedef std::vector<TVesselElementType>  vecTupleSegment;


static bool b_isNew = true;
static bool b_showOld = true;
static  bool b_showNew = true;
static bool b_showText = true;
const osg::Vec4 colorOld = { 1.0,0.5,0.2f,1.0 };
const osg::Vec4 colorNew = { 1.0,1.0,1.0,1.0 };
static  int nTransDis = 0;

static std::wstring s_strLabel;
static std::wstring s_strX = L"X";
static std::wstring s_strY = L"Y";
static std::wstring s_strZ = L"Z";

enum eIntersectType
{
    eFailed,
    eParal,
    eSuccess

};

template <typename T>
osg::Vec3 convertWykPtnToOsgVec(const wykobi::point3d<T>& point)
{
    osg::Vec3 tempVec;
    tempVec[0] = point[0];
    tempVec[1] = point[1];
    tempVec[2] = point[2];
    return  tempVec;
}

template <typename T>
wykobi::point3d<T> convertOsgVecToWykPtn(const osg::Vec3& vecPtn)
{
    wykobi::point3d<T> tmpptn = wykobi::degenerate_point3d<T>();
    tmpptn[0] = vecPtn[0];
    tmpptn[1] = vecPtn[1];
    tmpptn[2] = vecPtn[2];
    return  tmpptn;
}

template <typename T>
wykobi::vector3d<T> convertOsgVecToWykVector(const osg::Vec3& vecPtn)
{
    wykobi::vector3d<T>  tmpptn = wykobi::degenerate_vector3d<T>();
    tmpptn[0] = vecPtn[0];
    tmpptn[1] = vecPtn[1];
    tmpptn[2] = vecPtn[2];
    return  tmpptn;
}


template <typename T>
inline bool  isPtnOnPlane(const wykobi::point3d<T>& point, const wykobi::plane<T, 3>& plane)
{
    T lengthMul = fabs(plane.normal.x * point.x + plane.normal.y * point.y + plane.normal.z * point.z + plane.constant);
    return !wykobi::not_equal(lengthMul, T(0.0), T(local_Epsilon));
}




template <typename T>
inline T local_distance(const wykobi::point3d<T>& point, const wykobi::plane<T, 3>& plane)
{
    T length = sqrt(plane.normal.x * plane.normal.x + plane.normal.y * plane.normal.y+ plane.normal.z * plane.normal.z);
    if (!wykobi::not_equal(length, T(0.0), T(local_Epsilon)))
    {
        throw std::exception();
    }

    T lengthMul = fabs(plane.normal.x * point.x + plane.normal.y * point.y + plane.normal.z * point.z + plane.constant);

    return lengthMul / length;
}

template <typename T>
inline wykobi::point3d<T> intersection_point_local(const wykobi::line<T, 3>&  line,
    const wykobi::plane<T, 3>& plane)
{
    const wykobi::vector3d<T> line_vec = line[1] - line[0];
    const T denom =  fabs(dot_product(line_vec, plane.normal));

    wykobi::point3d<T> ipoint = wykobi::degenerate_point3d<T>();

    if (wykobi::not_equal(denom, T(0.0),T(local_Epsilon)))
    {
        const T t = local_distance(line[0], plane) / denom;

        ipoint = line[0] + t * (line[1] - line[0]);
        if (isPtnOnPlane(ipoint, plane))
        {
            return ipoint;
        }

        ipoint = line[0] - t * (line[1] - line[0]);
        if (!isPtnOnPlane(ipoint, plane))
        {
            throw std::exception();
        }
        return ipoint;
    }

    throw std::exception();
}


template <typename T>
bool getTheDistanceBetweenPlanes(const wykobi::plane<T, 3>& planeLeft,
    const wykobi::plane<T, 3>& planeRight,
    const osg::Vec3& ptnLeftCenter,
    T& fDistand)
{
    wykobi::point3d<T> point = convertOsgVecToWykPtn<T>(ptnLeftCenter);
    if (!isPtnOnPlane(point, planeLeft))
    {
        return false;
    }

    auto nomalLeft = convertWykPtnToOsgVec(planeLeft.normal);
    auto nomalRight = convertWykPtnToOsgVec(planeRight.normal);
    auto nomalIntersectedLine = nomalLeft ^ nomalRight;
    if (fabs(nomalIntersectedLine.length()) < local_Epsilon)
    {
        return false;
    }

    //两个面的交线一定与两个面的法线向量相垂直。所以nomalIntersectedLine为交线的法线向量。
    nomalIntersectedLine.normalize();
    //由交线的法线向量和一个面的法线向量组成的面的法线向量  必然与这个面平行  并且与交线方向垂直。
    auto nomalPerToIntersectedLine = nomalIntersectedLine ^ nomalLeft;
    nomalPerToIntersectedLine.normalize();
    nomalPerToIntersectedLine = nomalPerToIntersectedLine * T(2.0);
    //nomalPerToIntersectedLine 为在左平面并且与交线垂直的线段。
    auto ptnVertical = ptnLeftCenter + nomalPerToIntersectedLine;

    wykobi::line<T, 3> line;
    line[0] = point;
    line[1] = convertOsgVecToWykPtn<T>(ptnVertical);

    //计算出圆心到右面的距离，这个距离必须要小于半径。
    auto intersectedPtn = intersection_point_local(line, planeRight);
    auto  length = convertWykPtnToOsgVec(intersectedPtn - point).length();
    fDistand = length;
    return true;
}

template <typename T>
inline  bool modifedThePlaneRadius(const wykobi::plane<T, 3>& planeLeft,
    const wykobi::plane<T, 3>& planeRight,
    const osg::Vec3& ptnLeftCenter,
    const T radius_standand,
    T& radiusModifed)
{
    radiusModifed = radiusModifed;
    if (!wykobi::intersect(planeLeft, planeRight))
    {
        radiusModifed = radius_standand;
        return true;
    }

    T radius = T(0.0);
    if (!getTheDistanceBetweenPlanes(planeLeft, planeRight, ptnLeftCenter, radius))
    {
        return false;
    }

    static const T MaxRadiusLenProp = T(0.75);

    auto lenMax = fabs(radius * MaxRadiusLenProp - local_Epsilon);

    if (lenMax < s_fMinLength)
    {
        radiusModifed = s_fMinLength;
    }
    else if (radius_standand > T(lenMax))
    {
        radiusModifed = T(lenMax);
    }

    return true;
}


bool bGetTheIntersectPtn(const osg::Vec3& posLineBegin, const osg::Vec3& posLineEnd,
    const double& dPlaneConstant, const osg::Vec3& planeNormal,
    osg::Vec3& ptnInsect)
{
    wykobi::point3d<double> pt1;
    pt1[0] = posLineBegin[0];
    pt1[1] = posLineBegin[1];
    pt1[2] = posLineBegin[2];

    wykobi::point3d<double> pt2;
    pt2[0] = posLineEnd[0];
    pt2[1] = posLineEnd[1];
    pt2[2] = posLineEnd[2];

    wykobi::line<double, 3> line;
    line[0] = pt1;
    line[1] = pt2;

    wykobi::plane<double, 3> tPlane;
    tPlane.constant = dPlaneConstant;
    tPlane.normal = { planeNormal[0], planeNormal[1], planeNormal[2] };

    if (wykobi::intersect(tPlane, line))
    {
        auto ptn = intersection_point_local(line, tPlane);
        ptnInsect[0] = ptn[0];
        ptnInsect[1] = ptn[1];
        ptnInsect[2] = ptn[2];
        return true;
    }
    return false;
}

template <typename T>
bool bGetTheIntersectPtn(const osg::Vec3& posLineBegin, const osg::Vec3& posLineEnd,
    wykobi::plane<T, 3> tPlane,
    osg::Vec3& ptnInsect)
{
    wykobi::point3d<T> pt1;
    pt1[0] = posLineBegin[0];
    pt1[1] = posLineBegin[1];
    pt1[2] = posLineBegin[2];

    wykobi::point3d<T> pt2;
    pt2[0] = posLineEnd[0];
    pt2[1] = posLineEnd[1];
    pt2[2] = posLineEnd[2];

    wykobi::line<T, 3> line;
    line[0] = pt1;
    line[1] = pt2;

    try
    {
        if (wykobi::intersect(tPlane, line))
        {
            auto ptn = intersection_point_local(line, tPlane);
            ptnInsect[0] = ptn[0];
            ptnInsect[1] = ptn[1];
            ptnInsect[2] = ptn[2];
            return true;
        }
    }
    catch (std::exception )
    {
        return false;
    }

    return false;
}


bool getTheSegmentRenderPtn(const osg::Vec3& posBegin, const osg::Vec3& posEnd,
    const osg::Vec3& posBeginVector, const osg::Vec3& posEndVector,
    std::vector<osg::Vec3>& vecPtnUp, std::vector<osg::Vec3>& vecPtndown)
{
    if (posBegin == posEnd)
    {
        return false;
    }

    auto fCineRadius = s_fLength;

    //先形成轴向量，也就是连接起止点和终止点的向量。
    osg::Vec3 vecBegToEnd = posEnd - posBegin;
    vecBegToEnd.normalize();

    //用起始半径的向量叉乘轴向量,得到旋转轴
    osg::Vec3 vecCutPlaneNormal = posBeginVector ^ vecBegToEnd;
    auto vecStartRotatedAxis = posBeginVector ^ vecCutPlaneNormal;
    vecCutPlaneNormal.normalize();
    vecStartRotatedAxis.normalize();

    //求出上表面和下表面的两个面的更正半径，并用更正半径取代标准半径。vecStartRotatedAxis为上表面的平面半径。
    auto planeStart = wykobi::make_plane(convertOsgVecToWykPtn<double>(posBegin),
                               convertOsgVecToWykVector<double>(vecStartRotatedAxis));


    osg::Vec3 vecPtnEnToBegin = vecBegToEnd;
    vecPtnEnToBegin.normalize();

    //vecRotEndAxis为底面圆所在的平面的法线向量。
    osg::Vec3 vecRotEndAxis = posEndVector ^ vecPtnEnToBegin;
    /*
    如果 posEndVector 和vecPtnEnToBegin 相垂直，则直接把vecPtnEnToBegin赋值给vecRotEndAxis
    */
    if (fabs(vecRotEndAxis.length()) < local_Epsilon)
    {
        vecRotEndAxis = vecPtnEnToBegin;
    }
    else
    {
        vecRotEndAxis = posEndVector ^ vecRotEndAxis;
        vecRotEndAxis.normalize();
    }
    /*
    确定终止面法线向量的方向 还得确定一个因素
    就是初始面的法线向量和从两个面中心店连线的角度。
    如果角度大于90度 那么终止面的向量和起止面的向量应该小于九十度
    如果角度小于90度 那么终止面和起止面的向量应该大于九十度。
    */
    auto fValueStartPlaneToCerterline = wykobi::dot_product(convertOsgVecToWykVector<double>(vecBegToEnd), convertOsgVecToWykVector<double>(vecStartRotatedAxis));
    bool bShouldSameDirection= false;
    if (fabs(fValueStartPlaneToCerterline) < local_Epsilon)
    {
        return false;
    }

    if (fValueStartPlaneToCerterline < -local_Epsilon)
    {
        bShouldSameDirection = true;
    }

    auto vecEndToBegin = posBegin - posEnd;
    vecEndToBegin.normalize();
    auto fValue = wykobi::dot_product(convertOsgVecToWykVector<double>(vecEndToBegin), convertOsgVecToWykVector<double>(vecRotEndAxis));
    if (fabs(fValue) < local_Epsilon)
    {
        return false;
    }

    if (bShouldSameDirection && fValue  < -local_Epsilon)
    {
        vecRotEndAxis *= -1;
    }
    else if (!bShouldSameDirection && fValue > local_Epsilon)
    {
        vecRotEndAxis *= -1;
    }

    auto planeEnd = wykobi::make_plane(convertOsgVecToWykPtn<double>(posEnd),
        convertOsgVecToWykVector<double>(vecRotEndAxis));

    double fModifiedRadius = fCineRadius;
    if (!modifedThePlaneRadius<double>(planeStart, planeEnd, posBegin, fCineRadius, fModifiedRadius))
    {
        return false;
    }

    fCineRadius = fModifiedRadius;

    //为了保证取点的一致性，必须要保证起始面和终止面的点是一致的才行。通过起始面的默认向量 向终止面以轴方向做直线
    //交点则为目前的终止面的点。

    auto ptnStart = posBeginVector;
    ptnStart.normalize();
    ptnStart += posBegin;
    auto ptnEnd = ptnStart + vecBegToEnd;
    osg::Vec3 ptnIntersect;
    //知道了起止点和终止点，那么求出与终止面的交点。
    if (!bGetTheIntersectPtn(ptnStart, ptnEnd, planeEnd, ptnIntersect))
    {
        return false;
    }

    //求出底面圆心到交点的向量
    auto vecCenterEnd = ptnIntersect - posEnd;
    vecCenterEnd.normalize();
    vecCenterEnd *= fCineRadius;

    std::vector<osg::Vec3> vecPtnStart(s_nDevidedCount);
    std::vector<osg::Vec3> vecPtnEnd(s_nDevidedCount);
    //然后将该向量绕着
    const double fPerRotateAngle = 2.0 *  osg::PI / static_cast<double>(s_nDevidedCount);
    for (int i = 0; i < s_nDevidedCount; ++i)
    {
        double fRotateAngle = fPerRotateAngle * i;
        osg::Matrix matStart;
        matStart.makeRotate(fRotateAngle, vecStartRotatedAxis);

        //下面是把半径向量进行了旋转， 得到了当前点的向量。
        osg::Vec3 vecRotatedRadius = posBeginVector * matStart;
        vecRotatedRadius.normalize();

        //取得当前显示圆上的的点。
        auto vecRendterPtn = vecRotatedRadius * fCineRadius;
        vecPtnStart[i]  = posBegin + vecRendterPtn;


        osg::Matrix matEnd;
        matEnd.makeRotate(fRotateAngle, vecRotEndAxis);

        auto ptnEnd = vecCenterEnd * matEnd;
        ptnEnd.normalize();
        ptnEnd *= fCineRadius;
        vecPtnEnd[i]  = posEnd + ptnEnd;
    }

    vecPtnUp = std::move(vecPtnStart);
    vecPtndown = std::move(vecPtnEnd);
    return true;
}

bool  modifyTheVec(const osg::Vec3& vecStandDard,osg::Vec3& vecModified)
{
    auto fValueStartPlaneToCerterline =
              wykobi::dot_product(convertOsgVecToWykVector<double>(vecStandDard), convertOsgVecToWykVector<double>(vecModified));

    if (fValueStartPlaneToCerterline < -local_Epsilon)
    {
        vecModified *= -1;
        return true;
    }
    return false;
}

//这个函数主要处理如果知道两个面中的一个面，然后求出另外一个面的所有拟合点。
bool getTheSegmentRenderPtn(const osg::Vec3& posBegin, const osg::Vec3& posEnd,
    const osg::Vec3& posEndVector,const std::vector<osg::Vec3>& vecPtnUp, std::vector<osg::Vec3>& vecPtndown)
{
    if (posBegin == posEnd)
    {
        return false;
    }

    if (s_nDevidedCount != vecPtnUp.size())
    {
        return false;
    }

    const osg::Vec3 posBeginVector = vecPtnUp.at(0) - posBegin;
    const osg::Vec3 posSecondVector = vecPtnUp.at(1) - posBegin;
    auto vecStartRotatedAxis = posBeginVector ^ posSecondVector;
    vecStartRotatedAxis.normalize();

    auto fCineRadius = s_fLength;

    //先形成轴向量，也就是连接起止点和终止点的向量。
    osg::Vec3 vecBegToEnd = posEnd - posBegin;
    vecBegToEnd.normalize();

    //求出上表面和下表面的两个面的更正半径，并用更正半径取代标准半径。vecStartRotatedAxis为上表面的平面半径。
    auto planeStart = wykobi::make_plane(convertOsgVecToWykPtn<double>(posBegin),
        convertOsgVecToWykVector<double>(vecStartRotatedAxis));

    osg::Vec3 vecPtnEnToBegin = vecBegToEnd;
    vecPtnEnToBegin.normalize();


    //vecRotEndAxis为底面圆所在的平面的法线向量。
    osg::Vec3 vecRotEndAxis = posEndVector ^ vecPtnEnToBegin;
    vecRotEndAxis = posEndVector ^ vecRotEndAxis;
    vecRotEndAxis.normalize();

    /*
    确定终止面法线向量的方向 还得确定一个因素
    就是初始面的法线向量和从两个面中心店连线的角度。
    如果角度大于90度 那么终止面的向量和起止面的向量应该小于九十度 也就是以同一个方向绕。
    如果角度小于90度 那么终止面和起止面的向量应该大于九十度，也就是以相反的方向绕。

    这里面还有一个问题 就是初始面的法线向量的问题。目前假设法线向量是与轴向量方向相反。但是如果相同怎么办？
    如果和轴向量的方向相同，那么需要将法线向量旋转180度，然后
    */
    auto fValueStartPlaneToCerterline = wykobi::dot_product(convertOsgVecToWykVector<double>(vecBegToEnd), convertOsgVecToWykVector<double>(vecStartRotatedAxis));
    bool bShouldSameDirection = false;
    if (fabs(fValueStartPlaneToCerterline) < local_Epsilon)
    {
        return false;
    }

    if (fValueStartPlaneToCerterline < -local_Epsilon)
    {
        bShouldSameDirection = true;
    }

    auto vecEndToBegin = posBegin - posEnd;
    auto fValue = wykobi::dot_product(convertOsgVecToWykVector<double>(vecEndToBegin), convertOsgVecToWykVector<double>(vecRotEndAxis));
    if (fabs(fValue) < local_Epsilon)
    {
        return false;
    }

    if (bShouldSameDirection &&  fValue < -local_Epsilon)
    {
        vecRotEndAxis *= -1;
    }
    else if (!bShouldSameDirection && fValue > local_Epsilon)
    {
        vecRotEndAxis *= -1;
    }


    auto planeEnd = wykobi::make_plane(convertOsgVecToWykPtn<double>(posEnd),
        convertOsgVecToWykVector<double>(vecRotEndAxis));

    double fModifiedRadius = fCineRadius;
    if (!modifedThePlaneRadius<double>(planeStart, planeEnd, posBegin, fCineRadius, fModifiedRadius))
    {
        return false;
    }

    fCineRadius = fModifiedRadius;

    //为了保证取点的一致性，必须要保证起始面和终止面的点是一致的才行。通过起始面的默认向量 向终止面以轴方向做直线
    //交点则为目前的终止面的点。

    auto ptnStart = posBeginVector;
    ptnStart.normalize();
    ptnStart += posBegin;
    auto ptnEnd = ptnStart + vecBegToEnd;
    osg::Vec3 ptnIntersect;
    //知道了起止点和终止点，那么求出与终止面的交点。
    if (!bGetTheIntersectPtn(ptnStart, ptnEnd, planeEnd, ptnIntersect))
    {
        return false;
    }

    //求出底面圆心到交点的向量
    auto vecCenterEnd = ptnIntersect - posEnd;
    vecCenterEnd.normalize();
    vecCenterEnd *= fCineRadius;

    std::vector<osg::Vec3> vecPtnEnd(s_nDevidedCount);
    //然后将该向量绕着
    const double fPerRotateAngle = 2.0 *  osg::PI / static_cast<double>(s_nDevidedCount);
    for (int i = 0; i < s_nDevidedCount; ++i)
    {
        double fRotateAngle = fPerRotateAngle * i;

        osg::Matrix matEnd;
        matEnd.makeRotate(fRotateAngle, vecRotEndAxis);

        auto ptnEnd = vecCenterEnd * matEnd;
        ptnEnd.normalize();
        ptnEnd *= fCineRadius;
        vecPtnEnd[i] = posEnd + ptnEnd;
    }
    vecPtndown = std::move(vecPtnEnd);
    return true;
}
/*
由于计算出来一个一个面上点未必真是一个面的，必须得加以调整才行。
*/
void adjustThePtnPosition(std::vector<osg::Vec3>& vecPtnUp)
{
    //如果点的数量小于3  一定在一个面上
    if (vecPtnUp.size() <= 3)
    {
        return;
    }

    auto tPlane = wykobi::make_plane(convertOsgVecToWykPtn<double>(vecPtnUp.at(0)),
        convertOsgVecToWykPtn<double>(vecPtnUp.at(1)), convertOsgVecToWykPtn<double>(vecPtnUp.at(2)));

    for (int i = 3 ; i < vecPtnUp.size(); ++i)
    {
        auto ptnTemp = convertOsgVecToWykPtn<double>(vecPtnUp[i]);
        if (!isPtnOnPlane<double>(ptnTemp, tPlane))
        {
            osg::Vec3 ptnIntersected;
            auto ptnEnd = ptnTemp + tPlane.normal;
            auto br = bGetTheIntersectPtn(convertWykPtnToOsgVec(ptnTemp), convertWykPtnToOsgVec(ptnEnd), tPlane, ptnIntersected);
            if (br)
            {
                vecPtnUp[i] = ptnIntersected;
            }
        }
    }

}


void  setLight(osg::ref_ptr<osg::Group> pRoot)
{

    {
        osg::ref_ptr<osg::LightSource> ls = new osg::LightSource();
        ls->setReferenceFrame(osg::LightSource::ABSOLUTE_RF);
        //创建光对象
        osg::ref_ptr<osg::Light> lt = new osg::Light();
        lt->setLightNum(0);
        //设置方向
        lt->setDirection(osg::Vec3(0.0, 0.0, 1.0));
        //设置位置
        lt->setPosition(osg::Vec4(0.0, 0.0, 1.0, 0.0));
        //设置光的颜色
        lt->setDiffuse(osg::Vec4(0.8, 0.8, 0.8, 1.0));//红色的光
        ls->setLight(lt);
        pRoot->addChild(ls);
    }
}

void setNodeLightConfig(osg::Node* pNode)
{
    if (nullptr == pNode)
    {
        return;
    }

    osg::StateSet* stateset = pNode->getOrCreateStateSet();
    stateset->setRenderBinToInherit();
    stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
    stateset->setAttributeAndModes(new osg::BlendFunc, osg::StateAttribute::OFF);
    osg::Material *material = new osg::Material;
    material->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);
    stateset->setAttributeAndModes(material, osg::StateAttribute::ON);
    stateset->setMode(GL_LIGHTING, osg::StateAttribute::ON);
    stateset->setMode(GL_LIGHT0, osg::StateAttribute::ON);
}


void executeLineRender(osg::ref_ptr<osg::Group> pGroup, std::vector<osg::Vec3>& vecPtnUp, std::vector<osg::Vec3>& vecPtndown,
    osg::Vec3 posBegin,osg::Vec3 posEnd)
{
    if (!pGroup.valid())
    {
        return;
    }

    osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array;
    std::copy(vecPtnUp.begin(), vecPtnUp.end(), std::back_inserter(*coords));
    std::copy(vecPtndown.begin(), vecPtndown.end(), std::back_inserter(*coords));

    auto funcInitalUp = [](osg::ref_ptr<osg::Vec3Array> coords,
        osg::ref_ptr<osg::DrawElementsUShort> loopPrimitive, bool bUp)->void
    {
        if (!loopPrimitive.valid() || !coords.valid())
        {
            return;
        }

        int nFirst = 0;
        if (!bUp)
        {
            nFirst = s_nDevidedCount;
        }

        for (size_t i = 0; i < s_nDevidedCount; i++)
        {
            loopPrimitive->push_back(nFirst + i);
        }
    };


    osg::ref_ptr<osg::DrawElementsUShort> loopPrimitivesUp = new osg::DrawElementsUShort(GL_LINE_LOOP);
    funcInitalUp(coords, loopPrimitivesUp, true);

    std::vector<osg::ref_ptr<osg::DrawElementsUShort>> vecMiddleLine;
    for (size_t i = 0; i < s_nDevidedCount; i++)
    {
        osg::ref_ptr<osg::DrawElementsUShort> pPrimitivesDown = new osg::DrawElementsUShort(GL_LINE_STRIP);
        pPrimitivesDown->push_back(i);
        pPrimitivesDown->push_back(i + s_nDevidedCount);
        vecMiddleLine.push_back(pPrimitivesDown);
    }

    osg::ref_ptr<osg::DrawElementsUShort> loopPrimitivesDown = new osg::DrawElementsUShort(GL_LINE_LOOP);
    funcInitalUp(coords, loopPrimitivesDown, false);

    osg::Vec4Array* colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(0.3f, 0.8f, 0.5f, 1.0f));

    osg::Geometry* geom = new osg::Geometry;
    geom->setVertexArray(coords);
    geom->setColorArray(colors, osg::Array::BIND_OVERALL);

    geom->addPrimitiveSet(loopPrimitivesUp.get());
    for (auto iter = vecMiddleLine.begin(); iter != vecMiddleLine.end(); ++iter)
    {
        geom->addPrimitiveSet(iter->get());
    }
    geom->addPrimitiveSet(loopPrimitivesDown.get());

    osg::Geode* geode = new osg::Geode;
    geode->addDrawable(geom);

    pGroup->addChild(geode);

    {
        osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array;
        coords->push_back(posBegin);
        coords->push_back(posEnd);

        osg::Vec4Array* colors = new osg::Vec4Array;
        colors->push_back(osg::Vec4(0.0f, 1.0f, 1.2f, 1.0f));

        osg::Geometry* geom = new osg::Geometry;
        geom->setVertexArray(coords);
        geom->setColorArray(colors, osg::Array::BIND_OVERALL);
        geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2));

        osg::Geode* geode = new osg::Geode;
        geode->addDrawable(geom);
        pGroup->addChild(geode);
    }
}

void executeFaceRender(osg::ref_ptr<osg::Group> pGroup, std::vector<osg::Vec3>& vecPtnUp, std::vector<osg::Vec3>& vecPtndown,
    osg::Vec3 posBegin, osg::Vec3 posEnd)
{
    if (!pGroup.valid())
    {
        return;
    }

    if (vecPtnUp.size() != vecPtndown.size())
    {
        return;
    }

    auto ptnCenter = (posBegin + posEnd) * 0.5;

    osg::ref_ptr<osg::Group> pLightGroup = new osg::Group;
    setNodeLightConfig(pLightGroup.get());
    setLight(pLightGroup);

    osg::Vec4Array* colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(1.0f, 0.5f, 0.3f, 1.0f));
    //画出柱体
    {
        osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array(vecPtnUp.size() + vecPtndown.size() + 2);
        for (int i = 0; i < vecPtnUp.size(); ++i)
        {
            (*coords)[i * 2] = vecPtnUp[i];
            (*coords)[i * 2 + 1] = vecPtndown[i];
        }

        (*coords)[vecPtnUp.size() * 2] = *vecPtnUp.begin();
        (*coords)[vecPtnUp.size() * 2 + 1] = *vecPtndown.begin();

        osg::Geometry* geom = new osg::Geometry;
        geom->setVertexArray(coords);
        geom->setColorArray(colors, osg::Array::BIND_OVERALL);
        geom->setVertexArray(coords);

        osg::ref_ptr<osg::DrawElementsUShort> pPrimitivesDown = new osg::DrawElementsUShort(GL_TRIANGLE_STRIP);
        for (int i = 0; i < coords->size(); ++i)
        {
            pPrimitivesDown->addElement(i);
        }
        geom->addPrimitiveSet(pPrimitivesDown);


        osg::ref_ptr<osg::Geode> geode = new osg::Geode();
        geode->addDrawable(geom);
        pLightGroup->addChild(geode);
    }

    //确定上下面
    auto funcInitalFace = [](osg::ref_ptr<osg::Vec3Array> coords,
        osg::ref_ptr<osg::DrawElementsUShort> loopPrimitive)->void
    {
        if (!loopPrimitive.valid() || !coords.valid())
        {
            return;
        }

        for (size_t i = 0; i < s_nDevidedCount; i++)
        {
            loopPrimitive->push_back(i);
        }
    };

    {
        //确定上面的填充效果。

        osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array;
        std::copy(vecPtnUp.begin(), vecPtnUp.end(), std::back_inserter(*coords));

        osg::Geometry* geom = new osg::Geometry;
        geom->setVertexArray(coords);
        geom->setColorArray(colors, osg::Array::BIND_OVERALL);

        auto normal = posBegin - ptnCenter;
        normal.normalize();
        osg::ref_ptr<osg::Vec3Array>  normalVec = new osg::Vec3Array;
        normalVec->push_back(normal);
        geom->setNormalArray(normalVec, osg::Array::BIND_OVERALL);

        osg::ref_ptr<osg::DrawElementsUShort> pPrimitivesDown = new osg::DrawElementsUShort(GL_POLYGON);
        funcInitalFace(coords, pPrimitivesDown);
        geom->addPrimitiveSet(pPrimitivesDown);

        osg::ref_ptr<osg::Geode> geode = new osg::Geode();
        geode->addDrawable(geom);
        pLightGroup->addChild(geode);

        osgUtil::SmoothingVisitor sv;
        pLightGroup->accept(sv);
    }

    {
        //确定下面的填充效果。
        osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array;
        std::copy(vecPtndown.begin(), vecPtndown.end(), std::back_inserter(*coords));

        osg::Geometry* geom = new osg::Geometry;
        geom->setVertexArray(coords);
        geom->setColorArray(colors, osg::Array::BIND_OVERALL);

        auto normal = posEnd - ptnCenter;
        normal.normalize();
        osg::ref_ptr<osg::Vec3Array>  normalVec = new osg::Vec3Array;
        normalVec->push_back(normal);
        geom->setNormalArray(normalVec, osg::Array::BIND_OVERALL);

        osg::ref_ptr<osg::DrawElementsUShort> pPrimitivesDown = new osg::DrawElementsUShort(GL_POLYGON);
        funcInitalFace(coords, pPrimitivesDown);
        geom->addPrimitiveSet(pPrimitivesDown);

        osg::ref_ptr<osg::Geode> geode = new osg::Geode();
        geode->addDrawable(geom);
        pLightGroup->addChild(geode);
    }
    pGroup->addChild(pLightGroup);
}

void testTheSegmentRenderPtn()
{
    osg::Vec3 posBegin = {10,0,100};
    osg::Vec3 posBeginVector = { -10,10,40 };

    osg::Vec3 posEnd = { 50,-70,9};
    osg::Vec3 posEndVector = { -10,5,-80 };


    std::vector<osg::Vec3> vecPtnUp;
    std::vector<osg::Vec3> vecPtndown;

    auto bF = getTheSegmentRenderPtn(posBegin, posEnd,
        posBeginVector, posEndVector, vecPtnUp, vecPtndown);


    if (!bF)
    {
        return;
    }

    adjustThePtnPosition(vecPtnUp);
    adjustThePtnPosition(vecPtndown);

    osg::ref_ptr<osg::Group> pGroup = new osg::Group;
    executeLineRender(pGroup, vecPtnUp, vecPtndown, posBegin, posEnd);
    executeFaceRender(pGroup, vecPtnUp, vecPtndown, posBegin, posEnd);

    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
    viewer->setUpViewInWindow(100, 100, 800, 800);
    viewer->setLightingMode(osgViewer::Viewer::NO_LIGHT);
    viewer->setSceneData(pGroup);
    viewer->run();
}

/*
这个函数作用是得到初始的点的一个平面上的向量，用这个向量作为整个vessel
识别的起始向量。获得方法是
1 起始点为起始平面上的点， 起始平面的法线向量为轴向量。
2 通过上面两给条件构造起始平面。
3 然后随便找到一个不是起始点的点，通过这个点对平面作垂线，求出与平面的交点。
4 通过交点和起止点的向量，则是我们要求的起始平面上的向量，作为整个vessel的起始向量。

*/

bool getStartAndEndVector(osg::Vec3& ptnStart, osg::Vec3& ptnStartEnd,osg::Vec3& vecOut)
{
    auto vecPlaneNormal = ptnStartEnd - ptnStart;
    vecPlaneNormal.normalize();

    auto planeStart = wykobi::make_plane(convertOsgVecToWykPtn<double>(ptnStart),
        convertOsgVecToWykVector<double>(vecPlaneNormal));


    osg::Vec3 ptnOtherPtn = ptnStart + osg::Vec3(10.0, 0.0, 100);
    osg::Vec3 ptnOnPlane = ptnOtherPtn;
    osg::Vec3 vecOutTemp;
    int n = 0;
    while (true)
    {
        if (!isPtnOnPlane<double>(convertOsgVecToWykPtn<double>(ptnOtherPtn), planeStart))
        {
            static const double  s_defaultValue = 5.0;
            osg::Vec3 ptnVecEnd = ptnOnPlane + vecPlaneNormal * 5.0;
            osg::Vec3 ptnIntersected;
            if (bGetTheIntersectPtn<double>(ptnOtherPtn, ptnVecEnd, planeStart, ptnIntersected))
            {
                ptnOnPlane = ptnIntersected;
            }
        }

        vecOutTemp = ptnOnPlane - ptnStart;
        if (fabs(vecOutTemp.length())>  local_Epsilon)
        {
            break;
        }
        ++n;
        ptnOtherPtn = ptnStart + osg::Vec3(10.0, 10.0 * n, 100);
        ptnOnPlane = ptnOtherPtn;
    }


    vecOut = vecOutTemp;
    vecOut.normalize();
    return true;
}
bool getTheStartVector(std::vector<osg::Vec3>& vecVesselData,osg::Vec3& vecStart)
{
    if (vecVesselData.size() < 2)
    {
        return false;
    }

    auto ptnStart = *vecVesselData.begin();
    auto ptnStartEnd = *(vecVesselData.begin() + 1);
    return getStartAndEndVector(ptnStart,ptnStartEnd, vecStart);
}

bool getTheEndVector(std::vector<osg::Vec3>& vecVesselData, osg::Vec3& vecStart)
{
    if (vecVesselData.size() < 2)
    {
        return false;
    }

    auto ptnStart = *vecVesselData.rbegin();
    auto ptnStartEnd = *(vecVesselData.rbegin() + 1);
    return getStartAndEndVector(ptnStart, ptnStartEnd, vecStart);
}
/*
只计算除了第一个点和最后一个点其他点的切线向量。
*/
bool getCommonPtnVector(std::vector<osg::Vec3>& vecVesselData,const int nPtnPos,osg::Vec3& posVector)
{
    if (vecVesselData.size() < 2)
    {
        return false;
    }

    if (nPtnPos < 1)
    {
        return  getTheStartVector(vecVesselData, posVector);
    }

    if (nPtnPos >= vecVesselData.size() - 1)
    {
        return  getTheEndVector(vecVesselData, posVector);
    }

    auto ptnStart = vecVesselData.at(nPtnPos - 1);
    auto ptnCurrent = vecVesselData.at(nPtnPos);
    auto ptnEnd = vecVesselData.at(nPtnPos + 1);

    auto vec1 = ptnStart - ptnCurrent;
    auto vec2 = ptnEnd - ptnCurrent;
    auto vec3 = vec1 + vec2;
    vec3.normalize();
    posVector = vec3;
    return true;
}
osg::Node* createVesselData(std::vector<osg::Vec3>& vecVesselData)
{
    if (vecVesselData.size() < 2)
    {
        return nullptr;
    }

    auto funcCreateRenderNode = [](std::vector<osg::Vec3>& vecPtnUp,
                                    std::vector<osg::Vec3>& vecPtndown,
                                    osg::Vec3& posBegin,
                                    osg::Vec3& posEnd,
                                    osg::Group* pGroup)->void
    {
        if (nullptr == pGroup)
        {
            return;
        }

        adjustThePtnPosition(vecPtnUp);
        adjustThePtnPosition(vecPtndown);
        executeLineRender(pGroup, vecPtnUp, vecPtndown, posBegin, posEnd);
        executeFaceRender(pGroup, vecPtnUp, vecPtndown, posBegin, posEnd);
    };

    osg::ref_ptr<osg::Group> pGroup = new osg::Group;

    for(auto iter = vecVesselData.begin(); iter != vecVesselData.end() - 1 ; ++iter)
    {
        osg::Vec3 vecBegin;
        int nStartPos = iter - vecVesselData.begin();
        if (!getCommonPtnVector(vecVesselData, nStartPos, vecBegin))
        {
            return nullptr;
        }

        osg::Vec3 vecEnd;
        int nEndPos = iter - vecVesselData.begin() + 1;
        if (!getCommonPtnVector(vecVesselData, nEndPos, vecEnd))
        {
            return nullptr;
        }

        std::vector<osg::Vec3> vecPtnUp;
        std::vector<osg::Vec3> vecPtndown;

        auto bF = getTheSegmentRenderPtn(*iter, *(iter + 1),
            vecBegin, vecEnd, vecPtnUp, vecPtndown);
        if (!bF)
        {
            return nullptr;
        }

        funcCreateRenderNode(vecPtnUp, vecPtndown,
            *iter, *(iter + 1), pGroup);
    }
    return pGroup.release();
}


/*
这个函数依然是按照传统的方法把每一个小线段都做一个gemoetry进行渲染，
这么做肯定没有问题，但是会导致大量的内存浪费。所以需要写一个新函数：
testRealityVesselPtnVector()
*/
void testVesselPtnVector()
{

    std::vector<osg::Vec3> vecRenderVertex;

    osg::Vec3 posBegin = { 10,0,100 };
    osg::Vec3 posMiddle = { 40,20,10 };
    osg::Vec3 posMiddle2 = { 30,-20,9 };
    osg::Vec3 posMiddle3 = { 80,10,90 };
    osg::Vec3 posMiddle4 = { -80,70,20 };
    osg::Vec3 posMiddle5 = { 50,10,-20 };
    osg::Vec3 posEnd = { -20,40,19 };

    vecRenderVertex.push_back(posBegin);
    vecRenderVertex.push_back(posMiddle);
    vecRenderVertex.push_back(posMiddle2);
    vecRenderVertex.push_back(posMiddle3);
    vecRenderVertex.push_back(posMiddle4);
    vecRenderVertex.push_back(posMiddle5);
    vecRenderVertex.push_back(posEnd);

    auto pGroup = createVesselData(vecRenderVertex);

    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
    viewer->setUpViewInWindow(100, 100, 800, 800);
    viewer->setLightingMode(osgViewer::Viewer::NO_LIGHT);
    viewer->setSceneData(pGroup);
    viewer->run();

}

/*
testRealityVesselPtnVector()
函数需要做的是对血管数据进行进一步的优化。
依然对一个segment进行测试，而不是整个血管。整个血管需要
进一步编写代码测试。
优化的方法如下：
1 每个segment都只用一个geometry来实现  所以每个segment都可以需要实现两个geometry， 线体和面体。
   这两个体差不多同样的逻辑，所以可以用同一份数据。

2 进行绘制的时候，如果两个线段用同一个面，则这个面上的点 只需要计算一次，如果其他线段还需要
   该点，则直接取出。

3  将所有这些点都塞到一个数组里，然后自己组建primitiveset，进行坐标的指定。指定方法在相关代码里详细阐述。

原则就是 geomoetry越少越少  而相同的顶点越少越好。
*/


osg::Node* createSegmentData(std::vector<osg::Vec3>& vecVesselData,std::vector<osg::Vec3>& vecAllPtn)
{
    if (vecVesselData.size() < 2)
    {
        return nullptr;
    }

    //先获得所有的数据点。
    /*
    具体方法是：由于上一个线段和下一线段必然有一个相同点，所以这个相同点记住即可。
    */
    static const int s_tempAdd = 10;
    vecAllPtn.reserve(vecVesselData.size() * s_nDevidedCount + s_tempAdd);

    std::vector<osg::Vec3> vecStorePtn;
    osg::ref_ptr<osg::Group> pGroup = new osg::Group;
    for (auto iter = vecVesselData.begin(); iter != vecVesselData.end() - 1; ++iter)
    {
        if (0 == vecStorePtn.size())
        {  //如果存储点数量为0，说明当前需要计算两个面的点。
            osg::Vec3 vecBegin;
            int nStartPos = iter - vecVesselData.begin();
            if (!getCommonPtnVector(vecVesselData, nStartPos, vecBegin))
            {
                return nullptr;
            }

            osg::Vec3 vecEnd;
            int nEndPos = iter - vecVesselData.begin() + 1;
            if (!getCommonPtnVector(vecVesselData, nEndPos, vecEnd))
            {
                return nullptr;
            }

            std::vector<osg::Vec3> vecPtnUp;
            std::vector<osg::Vec3> vecPtndown;

            auto bF = getTheSegmentRenderPtn(*iter, *(iter + 1),
                vecBegin, vecEnd, vecPtnUp, vecPtndown);
            if (!bF)
            {
                return nullptr;
            }

            adjustThePtnPosition(vecPtnUp);
            adjustThePtnPosition(vecPtndown);

            std::copy(vecPtnUp.begin(), vecPtnUp.end(),std::back_inserter(vecAllPtn));
            std::copy(vecPtndown.begin(), vecPtndown.end(), std::back_inserter(vecAllPtn));
            std::copy(vecPtndown.begin(), vecPtndown.end(), std::back_inserter(vecStorePtn));
        }
        else if (s_nDevidedCount  == vecStorePtn.size())
        {
            //如果当前存储点已经存在，说明初始面的点已经算出来了。只需要算结束面就可以了。
        //	getTheSegmentRenderPtn(const osg::Vec3& posBegin, const osg::Vec3& posEnd,
            //	const osg::Vec3& posEndVector, const std::vector<osg::Vec3>& vecPtnUp, std::vector<osg::Vec3>& vecPtndown)
            osg::Vec3 vecEnd;
            int nEndPos = iter - vecVesselData.begin() + 1;
            if (!getCommonPtnVector(vecVesselData, nEndPos, vecEnd))
            {
                return nullptr;
            }

            std::vector<osg::Vec3> vecPtndown;
            if (!getTheSegmentRenderPtn(*iter, *(iter + 1), vecEnd, vecStorePtn, vecPtndown))
            {
                return nullptr;
            }

            adjustThePtnPosition(vecPtndown);
            std::copy(vecPtndown.begin(), vecPtndown.end(), std::back_inserter(vecAllPtn));
            for (int i = 0; i < vecStorePtn.size(); ++i)
            {
                vecStorePtn[i] = vecPtndown[i];
            }
        }
        else
        {
            return nullptr;
        }

    }
    return pGroup.release();
}



osg::Node* executeSegmentLineRender(osg::ref_ptr<osg::Vec3Array> coords)
{

    if (!coords.valid())
    {
        return nullptr;
    }

    if (coords->size() == 0  || coords->size() % s_nDevidedCount != 0 )
    {
        return nullptr;
    }

    //分两次 第一次获取每个面的边缘形成一条线。也就是loop
    std::vector<osg::ref_ptr<osg::DrawElementsUShort>> vecLoopLine;
    int nLoopCount = coords->size() / s_nDevidedCount;
    for (size_t i = 0 ; i < nLoopCount;  ++i)
    {
        osg::ref_ptr<osg::DrawElementsUShort> loopPrimitivesUp = new osg::DrawElementsUShort(GL_LINE_LOOP);
        for (size_t j = 0; j < s_nDevidedCount; j++)
        {
            loopPrimitivesUp->push_back(i * s_nDevidedCount + j);
        }
        vecLoopLine.push_back(loopPrimitivesUp);
    }
    // 第二次获取中间线。
    std::vector<osg::ref_ptr<osg::DrawElementsUShort>> vecMiddleLine;
    for (size_t i = 0; i < nLoopCount - 1; ++i)
    {
        for (size_t j = 0; j < s_nDevidedCount; j++)
        {
            osg::ref_ptr<osg::DrawElementsUShort> linePrimitives = new osg::DrawElementsUShort(GL_LINE_STRIP);
            linePrimitives->push_back(i * s_nDevidedCount + j);
            linePrimitives->push_back((i + 1) * s_nDevidedCount + j);
            vecMiddleLine.push_back(linePrimitives);
        }
    }

    osg::Vec4Array* colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(0.3f, 0.8f, 0.5f, 1.0f));

    osg::Geometry* geom = new osg::Geometry;
    geom->setVertexArray(coords);
    geom->setColorArray(colors, osg::Array::BIND_OVERALL);

    for (auto iter = vecLoopLine.begin(); iter != vecLoopLine.end(); ++iter)
    {
        geom->addPrimitiveSet(iter->get());
    }

    for (auto iter = vecMiddleLine.begin(); iter != vecMiddleLine.end(); ++iter)
    {
        geom->addPrimitiveSet(iter->get());
    }

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(geom);
    osg::ref_ptr<osg::Group>  pGroup = new osg::Group;
    pGroup->addChild(geode);

    return pGroup.release();
}

osg::Node* executeSegmentCenterLineRender(std::vector<osg::Vec3>& vecRenderVertex)
{
    if (0 == vecRenderVertex.size())
    {
        return nullptr;
    }

    osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array;
    std::copy(vecRenderVertex.begin(),vecRenderVertex.end(),std::back_inserter(*coords));

    osg::Vec4Array* colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(1.0f, 0.2f, 0.7f, 1.0f));

    osg::Geometry* geom = new osg::Geometry;
    geom->setVertexArray(coords);
    geom->setColorArray(colors, osg::Array::BIND_OVERALL);

    osg::ref_ptr<osg::DrawElementsUShort> linePrimitives = new osg::DrawElementsUShort(GL_LINE_STRIP);
    for (int i = 0 ; i < coords->size(); ++i)
    {
        linePrimitives->push_back(i);
    }

    geom->addPrimitiveSet(linePrimitives.get());
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(geom);
    return  geode.release();
}
/*
该函数主要获得面的法线向量，前两个是面上的两个向量，最后一个是
衡量向量，必须方向得和这个衡量向量一致才行。
*/
osg::Vec3 getFaceNormal(const osg::Vec3& vector1, const osg::Vec3& vector2,const osg::Vec3& vecCompare)
{
    auto vecNormal = vector1 ^ vector2;
    auto fDot = vecNormal * vecCompare;
    if (fabs(fDot) < local_Epsilon)
    {
        throw std::exception();
    }

    if (fDot < -local_Epsilon)
    {
        vecNormal *= -1;
    }

    vecNormal.normalize();
    return vecNormal;
}

osg::Geometry* createFaceGeomery(osg::ref_ptr<osg::Vec3Array> coords,osg::Vec3& vecNormal)
{
    osg::Geometry* geomStartFace = new osg::Geometry;

    osg::Vec4Array* colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(1.0f, 0.6f, 0.1f, 1.0f));

    geomStartFace->setVertexArray(coords);
    geomStartFace->setColorArray(colors, osg::Array::BIND_OVERALL);

    osg::ref_ptr<osg::Vec3Array>  normalFaceVec = new osg::Vec3Array;
    normalFaceVec->push_back(vecNormal);
    geomStartFace->setNormalArray(normalFaceVec, osg::Array::BIND_OVERALL);

    return geomStartFace;
}

osg::Vec3Array*  getTheNormalPerVertex(osg::ref_ptr<osg::Vec3Array> coords, const std::vector<osg::Vec3>& vecRenderVertex)
{
    int nLoopCount = coords->size() / s_nDevidedCount;
    if (nLoopCount != vecRenderVertex.size())
    {
        return nullptr;
    }
    osg::ref_ptr<osg::Vec3Array> vecNormals = new osg::Vec3Array;
    for (size_t i = 0; i < nLoopCount - 1; ++i)
    {
        auto ptnCenter = (vecRenderVertex.at(i) + vecRenderVertex.at(i + 1)) * 0.5;
        for (size_t j = 0; j < s_nDevidedCount; j++)
        {
            auto ptnCurrent = coords->at(i * s_nDevidedCount + j);
            auto ptnVec = ptnCurrent - ptnCenter;
            ptnVec.normalize();
            vecNormals->push_back(ptnVec);
        }
    }

    auto ptnCenter = (vecRenderVertex.at(nLoopCount - 2) + vecRenderVertex.at(nLoopCount - 1)) * 0.5;
    for (size_t j = 0; j < s_nDevidedCount; j++)
    {
        auto ptnCurrent = coords->at((nLoopCount - 1) * s_nDevidedCount + j);
        auto ptnVec = ptnCurrent - ptnCenter;
        ptnVec.normalize();
        vecNormals->push_back(ptnVec);
    }
    return vecNormals.release();

}

osg::Geometry* createCylinderGeomery(osg::ref_ptr<osg::Vec3Array> coords, const std::vector<osg::Vec3>& vecRenderVertex)
{
    osg::ref_ptr<osg::Geometry> geomCylinder = new osg::Geometry;

    osg::Vec4Array* colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(0.8f, 0.2f, 0.7f, 1.0f));

    geomCylinder->setVertexArray(coords);
    geomCylinder->setColorArray(colors, osg::Array::BIND_OVERALL);

    //osg::ref_ptr<osg::Vec3Array> coordsNormal = getTheNormalPerVertex(coords, vecRenderVertex);
    //if (coordsNormal->size() != coords->size())
    //{
    //	return nullptr;
    //}
    //geomCylinder->setNormalArray(coordsNormal, osg::Array::BIND_PER_VERTEX);
    return geomCylinder.release();
}


osg::Node* executeSegmentFaceRender(osg::ref_ptr<osg::Vec3Array> coords, const std::vector<osg::Vec3>& vecRenderVertex,osg::Vec3& vecStart, osg::Vec3& vecEnd)
{
    if (!coords.valid())
    {
        return nullptr;
    }

    if (coords->size() == 0 || coords->size() % s_nDevidedCount != 0)
    {
        return nullptr;
    }

    osg::ref_ptr<osg::Group> pLightGroup = new osg::Group;
    setNodeLightConfig(pLightGroup.get());
    setLight(pLightGroup);

    /*
    这个函数主要完成了对血管的体绘制。绘制的方法是：
    1 只绘制血管的前后两个面。 中间面不绘制。
    2 对于中间面 依然采用三角片的方式渲染。
    */

    //绘制上面和下面：
    osg::ref_ptr<osg::DrawElementsUShort> pPrimitivesStartFace = new osg::DrawElementsUShort(GL_POLYGON);
    for (auto iter = coords->begin(); iter != coords->begin() + s_nDevidedCount; ++iter)
    {
        pPrimitivesStartFace->push_back(iter - coords->begin());
    }

    auto vecStartFace =
                 getFaceNormal(*coords->begin() - *(coords->begin() + 1),
                     *coords->begin() - *(coords->begin() + 2), vecStart);

    auto pGeoStartFace = createFaceGeomery(coords,vecStartFace);
    if (nullptr == pGeoStartFace)
    {
        return nullptr;
    }
    pGeoStartFace->addPrimitiveSet(pPrimitivesStartFace);

    osg::ref_ptr<osg::DrawElementsUShort> pPrimitivesEndFace = new osg::DrawElementsUShort(GL_POLYGON);
    for (auto iter = coords->rbegin(); iter != coords->rbegin() + s_nDevidedCount; ++iter)
    {
        pPrimitivesEndFace->push_back(coords->size() - (iter - coords->rbegin()) - 1);
    }

    auto vecEndFace =
        getFaceNormal(*coords->rbegin() - *(coords->rbegin() + 1),
            *coords->rbegin() - *(coords->rbegin() + 2), vecEnd);

    auto pGeoEndFace = createFaceGeomery(coords, vecEndFace);
    if (nullptr == pGeoEndFace)
    {
        return nullptr;
    }
    pGeoEndFace->addPrimitiveSet(pPrimitivesEndFace);

    osg::ref_ptr<osg::Geode> pNodeStartFace = new osg::Geode;
    pNodeStartFace->addDrawable(pGeoStartFace);
    osg::ref_ptr<osg::Geode> pNodeEndFace = new osg::Geode;
    pNodeEndFace->addDrawable(pGeoEndFace);

    //下面开始进行中间体的绘制。
    int nLoopCount = coords->size() / s_nDevidedCount;
    if (nLoopCount != vecRenderVertex.size())
    {
        return nullptr;
    }
    std::vector<osg::ref_ptr<osg::DrawElementsUShort>> vecCylinder;
    for (size_t i = 0; i < nLoopCount - 1; ++i)
    {
        osg::ref_ptr<osg::DrawElementsUShort> loopPrimitivesUp = new osg::DrawElementsUShort(GL_TRIANGLE_STRIP);
        for (size_t j = 0; j < s_nDevidedCount; j++)
        {
            loopPrimitivesUp->push_back(j + i * s_nDevidedCount);
            loopPrimitivesUp->push_back(j + (i + 1) * s_nDevidedCount);
        }
        loopPrimitivesUp->push_back(i * s_nDevidedCount);
        loopPrimitivesUp->push_back((i + 1) * s_nDevidedCount);
        vecCylinder.push_back(loopPrimitivesUp);
    }

    auto pGeoCylinder = createCylinderGeomery(coords, vecRenderVertex);
    for (auto iter = vecCylinder.begin(); iter != vecCylinder.end(); ++iter)
    {
        pGeoCylinder->addPrimitiveSet(iter->get());
    }

    osg::ref_ptr<osg::Geode> pGeometryCylinder = new osg::Geode;
    pGeometryCylinder->addDrawable(pGeoCylinder);
    pLightGroup->addChild(pGeometryCylinder);

    osgUtil::SmoothingVisitor sv;
    pLightGroup->accept(sv);

    pLightGroup->addChild(pNodeStartFace);
    pLightGroup->addChild(pNodeEndFace);

    return pLightGroup.release();

}

void testRealityVesselPtnVector()
{
    std::vector<osg::Vec3> vecRenderVertex;

    osg::Vec3 posBegin = { 38.8967f,5.17257f,31.217f };
    osg::Vec3 posMiddle = {41.882f,5.12847f,31.5106f};
    osg::Vec3 posMiddle2 = { 43.6896f,5.10178f,31.6883f };
    osg::Vec3 posMiddle3 = { -80.f,5.f,9.f };
    osg::Vec3 posMiddle4 = { 8.f,7.f,20.f };
    osg::Vec3 posMiddle5 = { 50.f,100.f,-20.f };
    osg::Vec3 posEnd = { -20.f,40.f,19.f };

    vecRenderVertex.push_back(posBegin);
    vecRenderVertex.push_back(posMiddle);
    vecRenderVertex.push_back(posMiddle2);
    //vecRenderVertex.push_back(posMiddle3);
    //vecRenderVertex.push_back(posMiddle4);
    //vecRenderVertex.push_back(posMiddle5);
    //vecRenderVertex.push_back(posEnd);

    /*osg::Vec3 posBegin = { 0,0,10 };
    osg::Vec3 posBeginVector = { -10,10,0 };

    osg::Vec3 posEnd = { 0,0,0 };
    osg::Vec3 posEndVector = { -10,10,0 };

    vecRenderVertex.push_back(posEnd);
    vecRenderVertex.push_back(posBegin);*/

    std::vector<osg::Vec3> vecAllPtn;
    createSegmentData(vecRenderVertex, vecAllPtn);

    osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array;
    std::copy(vecAllPtn.begin(), vecAllPtn.end(), std::back_inserter(*coords));

    osg::ref_ptr<osg::Node> pNodeLine = executeSegmentLineRender(coords);
    if (!pNodeLine.valid())
    {
        return;
    }

    osg::ref_ptr<osg::Node> pNodeCenterLine = executeSegmentCenterLineRender(vecRenderVertex);
    if (!pNodeCenterLine.valid())
    {
        return;
    }

    auto vecStart = *(vecRenderVertex.begin()) - *(vecRenderVertex.begin() + 1);
    auto vecEnd = *(vecRenderVertex.rbegin()) - *(vecRenderVertex.rbegin() + 1);

    osg::ref_ptr<osg::Node> pNodeFaceData =
           executeSegmentFaceRender(coords, vecRenderVertex,vecStart,vecEnd);

    if (!pNodeFaceData.valid())
    {
        return;
    }

    osg::ref_ptr<osg::Group>  root = new osg::Group;
    //root->addChild(pNodeLine);
    //root->addChild(pNodeCenterLine);
    root->addChild(pNodeFaceData);

    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
    viewer->setUpViewInWindow(100, 100, 800, 800);
    viewer->setLightingMode(osgViewer::Viewer::NO_LIGHT);
    viewer->setSceneData(root);
    viewer->run();
}



osg::Geode* createCornidateText(const osg::Vec3& pos, const std::wstring& content, double size, const osg::Vec4& vecColor)
{
    osg::ref_ptr<osgText::Text> text = new osgText::Text;
    text->setCharacterSize(size * 0.2);
    text->setAxisAlignment(osgText::TextBase::SCREEN);
    text->setPosition(pos);
    text->setText(content.c_str());
    text->setColor(vecColor);

    osg::ref_ptr<osgText::Font> font = osgText::readRefFontFile("fonts/arial.ttf");
    text->setFont(font);
		
    text->setDataVariance(osg::Object::DYNAMIC);
    text->setBackdropType(osgText::Text::OUTLINE);
    text->setBackdropImplementation(osgText::Text::POLYGON_OFFSET);
    text->setBackdropOffset(0.05f);
    text->setBackdropColor(osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));

    osg::ref_ptr<osg::Geode>  geode = new osg::Geode();
    geode->addDrawable(text);

    return geode.release();
}


osg::ref_ptr<osg::MatrixTransform> createCylinder(const osg::Vec3 &from, const osg::Vec3 &to, double radius)
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();
    osg::ref_ptr<osg::ShapeDrawable> cylinder = new osg::ShapeDrawable();
    osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints();

    hints->setDetailRatio(0.8f);
    osg::Vec3 cylCenter = (to + from) / 2;		//得到柱心
    double height = (to - from).length();		//得到长度
    cylinder = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0.0, 0.0, 0.0), radius, height), hints.get());
    if (b_isNew)
    {
        cylinder->setColor(osg::Vec4(255.0 / 255, 228.0 / 255, 181.0 / 255, 1.0f));
    }
    else
    {
        cylinder->setColor(osg::Vec4(1.0, 0.0, 0.0, 1.0f));
    }
    //鹿皮鞋色
    geode->setDataVariance(osg::Object::DYNAMIC);
    cylinder->setDataVariance(osg::Object::DYNAMIC);

    geode->addDrawable(cylinder.get());
    osg::Matrix mRotate, mTrans;
    mRotate.makeRotate(osg::Vec3f(0.0f, 0.0f, 1.0f), to - from);
    mTrans.makeTranslate(cylCenter);
    mt->setMatrix(mRotate*mTrans);
    mt->addChild(geode.get());
    mt->setDataVariance(osg::Object::DYNAMIC);
    return mt.get();
}


osg::ref_ptr<osg::MatrixTransform> createCoordinateCylinder(const osg::Vec3 &from, const osg::Vec3 &to, double radius, osg::Vec4& vecColor)
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();
    osg::ref_ptr<osg::ShapeDrawable> cylinder = new osg::ShapeDrawable();
    osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints();

    hints->setDetailRatio(0.8f);
    osg::Vec3 cylCenter = (to + from) / 2;		//得到柱心
    double height = (to - from).length();		//得到长度
    cylinder = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0.0, 0.0, 0.0), radius, height), hints.get());
    cylinder->setColor(vecColor);
    //鹿皮鞋色
    geode->setDataVariance(osg::Object::DYNAMIC);
    cylinder->setDataVariance(osg::Object::DYNAMIC);

    geode->addDrawable(cylinder.get());
    osg::Matrix mRotate, mTrans;
    mRotate.makeRotate(osg::Vec3f(0.0f, 0.0f, 1.0f), to - from);
    mTrans.makeTranslate(cylCenter);
    mt->setMatrix(mRotate*mTrans);
    mt->addChild(geode.get());
    mt->setDataVariance(osg::Object::DYNAMIC);
    return mt.get();
}

osg::ref_ptr<osg::MatrixTransform> createCone(const osg::Vec3 &from, const osg::Vec3 &to, double radius, osg::Vec4& vecColor)
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();
    osg::ref_ptr<osg::ShapeDrawable> cone = new osg::ShapeDrawable();
    osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints();

    hints->setDetailRatio(0.8f);
    osg::Vec3 cylCenter = (to + from) / 2;		//得到柱心
    double height = (to - from).length();		//得到长度
    cone = new osg::ShapeDrawable(new osg::Cone(osg::Vec3(0.0, 0.0, 0.0), radius, height), hints.get());
    cone->setColor(vecColor);
    //鹿皮鞋色
    geode->setDataVariance(osg::Object::DYNAMIC);
    cone->setDataVariance(osg::Object::DYNAMIC);

    geode->addDrawable(cone.get());
    osg::Matrix mRotate, mTrans;
    mRotate.makeRotate(osg::Vec3f(0.0f, 0.0f, 1.0f), to - from);
    mTrans.makeTranslate(cylCenter);
    mt->setMatrix(mRotate*mTrans);
    mt->addChild(geode.get());
    mt->setDataVariance(osg::Object::DYNAMIC);
    return mt.get();
}

osg::Group* makeCoordinate()
{
    osg::Vec4 vecColorX = {200,100,0,1.0};
    auto nodeX = createCoordinateCylinder(osg::Vec3(0, 0, 0), osg::Vec3(s_fLength, 0, 0), s_fLength *0.05, vecColorX);
    auto nodeX1 = createCone(osg::Vec3(s_fLength, 0, 0), osg::Vec3(s_fLength  * 1.2, 0, 0), s_fLength *0.08, vecColorX);

    osg::ref_ptr<osg::Geode>  geoTextX = createCornidateText(osg::Vec3(s_fLength  * 1.2, 0, 0),s_strX,1.5, vecColorX);

    osg::ref_ptr<osg::Group> node_x = new osg::Group();
    node_x->addChild(nodeX);
    node_x->addChild(nodeX1);
    node_x->addChild(geoTextX);

    osg::Vec4 vecColorY = { 100.0,200.0,10.0,1.0 };
    auto nodeY = createCoordinateCylinder(osg::Vec3(0, 0, 0), osg::Vec3(0.0, s_fLength, 0), s_fLength *0.05,vecColorY);
    auto nodeY1 = createCone(osg::Vec3(0.0, s_fLength, 0), osg::Vec3(0.0, s_fLength * 1.2, 0), s_fLength *0.08, vecColorY);
    osg::ref_ptr<osg::Geode>  geoTextY = createCornidateText(osg::Vec3(0.0, s_fLength * 1.2, 0), s_strY, 1.5, vecColorY);

    osg::ref_ptr<osg::Group> node_Y = new osg::Group();
    node_Y->addChild(nodeY);
    node_Y->addChild(nodeY1);
    node_Y->addChild(geoTextY);

    osg::Vec4 vecColorZ = { 0.0,100.0,200.0,1.0 };
    auto nodeZ = createCoordinateCylinder(osg::Vec3(0, 0, 0), osg::Vec3(0.0, 0.0, s_fLength), s_fLength *0.05, vecColorZ);
    auto nodeZ1 = createCone(osg::Vec3(0.0, 0.0, s_fLength), osg::Vec3(0.0, 0.0, s_fLength  * 1.2), s_fLength *0.08, vecColorZ);
    osg::ref_ptr<osg::Geode>  geoTextZ = createCornidateText(osg::Vec3(0.0, 0.0, s_fLength  * 1.2), s_strZ, 1.5, vecColorZ);

    osg::ref_ptr<osg::Group> node_Z = new osg::Group();
    node_Z->addChild(nodeZ);
    node_Z->addChild(nodeZ1);
    node_Z->addChild(geoTextZ);

    osg::ref_ptr<osg::Group> node_group = new osg::Group();
    node_group->addChild(node_x);
    node_group->addChild(node_Y);
    node_group->addChild(node_Z);

    node_group->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    osg::Material* mat = new osg::Material();
    mat->setColorMode(osg::Material::ColorMode::AMBIENT_AND_DIFFUSE);
    node_group->getOrCreateStateSet()->setAttribute(mat);
    /*osg::Multisample* pms = new osg::Multisample;
    pms->setSampleCoverage(1, true);
    node_group->getOrCreateStateSet()->setAttributeAndModes(pms, osg::StateAttribute::ON);*/
    return node_group.release();
}


static osg::Node* getParentNode(osg::Node* pNode,std::string& strName)
{
    if (nullptr != pNode)
    {
        return nullptr;
    }
    auto parentList = pNode->getParentalNodePaths();
    for (auto iter  = parentList.begin(); iter  != parentList.end(); ++iter)
    {
        osg::Node* node = iter->empty() ? 0 : iter->back();
        if (nullptr != node  && "drawingNode" == node->getName())
        {
            return node;
        }
    }

    return nullptr;
}


class flagSelectDeleteVisitor
    : public osg::NodeVisitor
{
public:

    flagSelectDeleteVisitor()
        : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN) {
    }

    virtual void apply(osg::Geode & geode)
    {
        std::string strNodeName = geode.getName();
        if (std::string::npos == strNodeName.find("drawingNode"))
        {
            return;
        }
        geode.getOrCreateStateSet()->clear();
    }

    virtual void apply(osg::Node & node)
    {
        std::string strNodeName = node.getName();
        if (std::string::npos == strNodeName.find("drawingNode"))
        {
            traverse(node);
            return;
        }
        node.getOrCreateStateSet()->clear();
        traverse(node);
    }

    virtual void apply(osg::Group & node)
    {
        std::string strNodeName = node.getName();
        if (std::string::npos == strNodeName.find("drawingNode"))
        {
            traverse(node);
            return;
        }

        node.getOrCreateStateSet()->clear();
        traverse(node);
    }
};


class CPickHandler :public osgGA::GUIEventHandler
{
public:
    CPickHandler(osgViewer::Viewer *viewer) :mViewer(viewer) {}
    virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
    {
        switch (ea.getEventType())
        {
            case osgGA::GUIEventAdapter::PUSH:
            {
              if (ea.getButtonMask() & osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
              {
                  if (ea.getButton() == 1)
                  {
                      osg::ref_ptr<osgViewer::View> view = dynamic_cast<osgViewer::View*>(&aa);
                      if (!view) return false;
                      Pick(ea.getX(), ea.getY());//可通过事件ea获得鼠标点击的坐标
                  }
              }
              else if (ea.getButtonMask() & osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
              {
                  flagSelectDeleteVisitor  visitNode;
                  visitNode.apply(*mViewer->getSceneData());
              }
              return true;
            }
        }
        return false;
    }
protected:
    void Pick(double x, double y)
    {
        try
        {
            osgUtil::LineSegmentIntersector::Intersections intersections;//声明一个相交测试的结果集
            if (mViewer->computeIntersections(x, y, intersections))//利用view的computerIntersection函数来测试屏幕与场景相交结果存入到结果集中
            {
                if (intersections.size() > 0 )
                {
                    osgUtil::LineSegmentIntersector::Intersections::iterator hitr = intersections.begin();
                    for (; hitr != intersections.end(); ++hitr)
                    {
                        bool bBreak = false;
                        for (auto iter = hitr->nodePath.begin(); iter != hitr->nodePath.end(); ++iter)
                        {
                            osg::Node* node = *iter;
                            if (nullptr != node  && "drawingNode" == node->getName())
                            {
                                osg::ref_ptr<osg::Material> material = new osg::Material;
                                osg::Vec4 redColor(0.5, 0.5, 0.5, 1.0);
                                material->setAmbient(osg::Material::FRONT, redColor);
                                material->setDiffuse(osg::Material::FRONT, redColor);
                                material->setColorMode(osg::Material::EMISSION);
                                node->getOrCreateStateSet()->setAttributeAndModes(material, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
                                //vecMaterial.push_back(material);
                                bBreak = true;
                                break;
                            }
                        }

                        if (bBreak)
                        {
                            break;
                        }
                    }
                }
            }
        }
        catch (...)
        {
            int a = 0;
        }
    }
    osgViewer::Viewer *mViewer;
};

osg::ref_ptr<osg::ShapeDrawable> createOneBNode(const osg::Vec3& center, double size)
{
    osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints();
    hints->setDetailRatio(1.0f);
    osg::ref_ptr<osg::ShapeDrawable> oneShape = new osg::ShapeDrawable(new osg::Sphere(center, size), hints.get());

    if (b_isNew)
    {
        oneShape->setColor(osg::Vec4(65.0 / 255, 105.0 / 255, 225.0 / 255, 1.0));
    }
    else
    {
        oneShape->setColor(osg::Vec4(1.0, 0.2,0, 1.0));
    }

    oneShape->setDataVariance(osg::Object::DYNAMIC);
    return oneShape.release();
}


void parseConfig()
{
    std::string strConfigFilePath = "config.txt";
    std::wstring strLine;
    std::wifstream infile;
    infile.open(strConfigFilePath);
    if (!infile.is_open())
    {
        return;
    }


    std::vector<int> vecTemp;
    while (std::getline(infile, strLine))
    {
        std::wistringstream istr(strLine);
        while (!istr.eof())
        {
            std::wstring sTmp;
            istr >> sTmp;

            try
            {
                int iValue = std::stoi(sTmp);
                vecTemp.push_back(iValue);
            }
            catch (...)
            {
                s_strLabel = sTmp;
                break;
            }
        }
        break;
    }

    if (vecTemp.size() > 0 )
    {
        if (vecTemp[0] == 0)
        {
            b_showOld = false;
        }
        else
        {
            b_showOld = true;
        }
    }

    if (vecTemp.size() > 1)
    {
        if (vecTemp[1] == 0)
        {
            b_showNew = false;
        }
        else
        {
            b_showNew = true;
        }
    }


    if (vecTemp.size() > 2)
    {
        if (vecTemp[2] >= 0)
        {
            if (0 == vecTemp[2])
            {
                b_showText = false;
            }
            else
            {
                b_showText = true;
            }
        }
    }

    if (vecTemp.size() > 3)
    {
        if (vecTemp[3] >= 0)
        {
            nTransDis = vecTemp[3];
        }
    }



}



void parseTheTreeData(vecSegment& vecSegment,std::string& strFileName)
{
    std::wifstream infile;
    infile.open(strFileName);
    if(!infile.is_open())
    {
       return;
    }

     const std::wstring strSeparate = L"************";
     std::wstring strLine;

     std::vector<osg::Vec3> vecLSeg;

     std::wstring strLabel;
     while (std::getline(infile, strLine))
     {
         const std::wstring strSegmentLabel = L"the segment label is";
         const std::wstring strSegmentLength = L"The segement length";

         auto nLabelPos = strLine.find(strSegmentLabel);
         auto nLengthPos = strLine.find(strSegmentLength);
         if (nLabelPos != std::string::npos && nLengthPos != std::string::npos)
         {
             int nSize = nLengthPos - nLabelPos - strSegmentLabel.size();
             strLabel = strLine.substr(nLabelPos + strSegmentLabel.size(), nSize);
             strLabel.erase(std::remove(strLabel.begin(), strLabel.end(), L' '), strLabel.end());
             if (strLabel.empty())
             {
                 strLabel = s_strLabel;
             }
             continue;
         }

         auto nPos = strLine.find(L"vertex data:");
         if (nPos == std::string::npos)
         {
             nPos = strLine.find(strSeparate);
             if (nPos != std::wstring::npos)
             {
                 if (vecLSeg.size() > 0)
                 {
                     vecSegment.push_back(std::make_pair(vecLSeg, strLabel));
                     vecLSeg.clear();
                 }
             }
             continue;
         }

         std::wistringstream istr(strLine);

         std::vector<double> vecTemp;
         while (!istr.eof())
         {
             std::wstring sTmp;
             istr >> sTmp;
             if (L"vertex" == sTmp)
             {
                 continue;
             }
             //data:
             if (L"data:" == sTmp)
             {
                 continue;
             }

             try
             {
                 double fValue = std::stof(sTmp);
                 vecTemp.push_back(fValue);
             }
             catch (...)
             {
                 break;
             }
         }

         if (3 != vecTemp.size())
         {
             return;
         }

         osg::Vec3 vec(vecTemp[0], vecTemp[1], vecTemp[2]);
         vecLSeg.push_back(vec);
     }

     if (vecLSeg.size() > 0)
     {
         vecSegment.push_back(std::make_pair(vecLSeg, strLabel));
     }

    infile.close();
}

osgText::Text* createText(const osg::Vec3& pos, const std::wstring& content, double size)
{
    osg::ref_ptr<osgText::Text> text = new osgText::Text;
    if (!b_showText)
    {
        return text.release();
    }
    text->setCharacterSize(size);
    text->setAxisAlignment(osgText::TextBase::SCREEN);
    text->setPosition(pos + osg::Vec3(s_fLength * 5,0,0));
    text->setText(content.c_str());

    if (b_isNew)
    {
        text->setColor(colorNew);
    }
    else
    {
        text->setColor(colorOld);
    }

    text->setDataVariance(osg::Object::DYNAMIC);

    osg::ref_ptr<osgText::Font> font = osgText::readRefFontFile("fonts/arial.ttf");
    text->setFont(font);

    text->setBackdropType(osgText::Text::OUTLINE);
    text->setBackdropImplementation(osgText::Text::POLYGON_OFFSET);
    text->setBackdropOffset(0.05f);
    text->setBackdropColor(osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));
    return text.release();
}

osg::ref_ptr<osg::Group> getTheVesselData(std::string strFilePath)
{
    osg::ref_ptr<osg::Group> root = new osg::Group();
    osg::ref_ptr<osg::Group> group = new osg::Group();

    vecSegment  vecShowSegment;
    parseTheTreeData(vecShowSegment, strFilePath);
    for (auto iter = vecShowSegment.begin(); iter != vecShowSegment.end();
        ++iter)
    {
        if (iter->first.size() == 0)
        {
            continue;
        }

        if (iter->first.size() == 1)
        {
            osg::ref_ptr<osgText::Text> text =
                createText(*iter->first.begin(), iter->second, 1);
            text->setDataVariance(osg::Object::DYNAMIC);

            osg::ref_ptr<osg::ShapeDrawable> drawGeom =
                               createOneBNode(*iter->first.rbegin(), 1.0f);
            drawGeom->setDataVariance(osg::Object::DYNAMIC);

            osg::ref_ptr<osg::Geode> geode = new osg::Geode();
            geode->setName("drawingNode");
            geode->addDrawable(text);
            geode->addDrawable(drawGeom);
            geode->setDataVariance(osg::Object::DYNAMIC);
            group->addChild(geode);
            continue;
        }

        osg::ref_ptr<osg::Group> nodeSegment = new osg::Group();
        nodeSegment->setName("drawingNode");
        nodeSegment->setDataVariance(osg::Object::DYNAMIC);
        for (auto iterVertex = iter->first.begin(); iterVertex != iter->first.end();
            ++iterVertex)
        {
            auto iterVertexNext = iterVertex + 1;
            if (iterVertexNext == iter->first.end())
            {
                continue;
            }
            auto ptnBegin = *(iterVertex);
            auto ptnEnd = *(iterVertexNext);
            osg::ref_ptr<osg::MatrixTransform> mt = createCylinder(ptnBegin, ptnEnd, 0.1f);
            nodeSegment->addChild(mt);
        }

        osg::Vec3 posText = *(iter->first.begin() + (int)(iter->first.size() * 0.5));
        osg::ref_ptr<osgText::Text> text =
                       createText(posText, iter->second, 1);
        nodeSegment->addChild(text);

        osg::ref_ptr<osg::ShapeDrawable> drawGeom = createOneBNode(*iter->first.rbegin(), 1.0f);
        nodeSegment->addChild(drawGeom);

        group->addChild(nodeSegment);
    }

    root->addChild(group.get());
    root->setDataVariance(osg::Object::DYNAMIC);
    return root;
}



void deleteTheSingleData(vecSegment&  vecShowSegment)
{
    if (0 == vecShowSegment.size())
    {
        return;
    }

    for (auto iter = vecShowSegment.begin(); iter != vecShowSegment.end();)
    {
        if (iter->first.size() > 1)
        {
            for (auto iter_inner = iter->first.begin(); iter_inner != iter->first.end() - 1; )
            {
                auto vecTmp  = *iter_inner - *(iter_inner + 1);
                if (vecTmp.length() < s_fMinLength)
                {
                    iter_inner = iter->first.erase(iter_inner);
                }
                else
                {
                    ++iter_inner;
                }
            }
        }

        if (iter->first.size() <= 1)
        {
            iter = vecShowSegment.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

void  getTheSelfSkinVesselVector(std::string strFilePath, vecTupleSegment& vecTupleSegment)
{
    vecTupleSegment.clear();
    vecSegment  vecShowSegment;
    parseTheTreeData(vecShowSegment, strFilePath);
    deleteTheSingleData(vecShowSegment);

    for (auto iter = vecShowSegment.begin(); iter != vecShowSegment.end();
        ++iter)
    {
        if (iter->first.size() == 0)
        {
            continue;
        }

        if (iter->first.size() == 1)
        {
            continue;
        }
        osg::Vec3 posText = *(iter->first.begin() + (int)(iter->first.size() * 0.5));
        vecTupleSegment.push_back(std::make_tuple(iter->first, iter->second, posText));
    }
}



osg::Group* testRealityVesselPtnVector(TVesselElementType& vessekElement)
{
    std::vector<osg::Vec3>& temp_vecRenderVertex = std::get<0>(vessekElement);
    if (0 == temp_vecRenderVertex.size())
    {
        return nullptr;
    }

    std::vector<osg::Vec3> vecRenderVertex;
    auto funcFillPtnVec = [&vecRenderVertex](osg::Vec3 vec)-> void
    {
        osg::Vec3 vecTemp = vec * fMaxMul;
        vecRenderVertex.push_back(vecTemp);
    };

    std::for_each(temp_vecRenderVertex.begin(), temp_vecRenderVertex.end(), funcFillPtnVec);

    std::vector<osg::Vec3> vecAllPtn;
    createSegmentData(vecRenderVertex, vecAllPtn);

    osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array;
    std::copy(vecAllPtn.begin(), vecAllPtn.end(), std::back_inserter(*coords));

    osg::ref_ptr<osg::Node> pNodeLine = executeSegmentLineRender(coords);
    if (!pNodeLine.valid())
    {
        return nullptr;
    }

    osg::ref_ptr<osg::Node> pNodeCenterLine = executeSegmentCenterLineRender(vecRenderVertex);
    if (!pNodeCenterLine.valid())
    {
        return nullptr;
    }

    auto vecStart = *(vecRenderVertex.begin()) - *(vecRenderVertex.begin() + 1);
    auto vecEnd = *(vecRenderVertex.rbegin()) - *(vecRenderVertex.rbegin() + 1);

    osg::ref_ptr<osg::Node> pNodeFaceData =
        executeSegmentFaceRender(coords, vecRenderVertex, vecStart, vecEnd);

    if (!pNodeFaceData.valid())
    {
        return nullptr;
    }


    osg::ref_ptr<osgText::Text> text =
        createText(std::get<2>(vessekElement), std::get<1>(vessekElement), 2);
    text->setDataVariance(osg::Object::DYNAMIC);
    osg::ref_ptr<osg::Geode> geodeText = new osg::Geode;
    geodeText->addDrawable(text);

    osg::ref_ptr<osg::Group>  root = new osg::Group;

    //pNodeLine->getOrCreateStateSet()->setAttributeAndModes(new osg::PolygonOffset(0.5, 0.5));
  //  root->addChild(pNodeCenterLine);
    root->addChild(pNodeFaceData);
    root->addChild(geodeText);
  //  root->addChild(pNodeLine);
    return root.release();
}

osg::Group* getSelfSkinVesselData(std::string strFilePath)
{
    vecTupleSegment vecTupleSmt;
    getTheSelfSkinVesselVector(strFilePath, vecTupleSmt);

    osg::ref_ptr<osg::Group> root = new osg::Group;
    for (auto iter = vecTupleSmt.begin(); iter != vecTupleSmt.end(); ++iter)
    {
        osg::Group* pGroup = testRealityVesselPtnVector(*iter);
        if (nullptr  == pGroup)
        {
            return nullptr;
        }
        root->addChild(pGroup);
    }

    return root.release();
}




void testSelfSkinVessel()
{
    parseConfig();

    typedef std::tuple<double, double, double>  vesselPtn;
    std::string strOldFilePath("old_left_Segment.txt");
    std::string strNewFilePath("new_left_Segment.txt");
    osg::ref_ptr<osg::Group> root = new osg::Group();
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
    viewer->setUpViewInWindow(100, 100, 1080, 960);

    if (b_showOld)
    {
        b_isNew = false;
        root->addChild(getSelfSkinVesselData(strOldFilePath));
    }

    if (b_showNew)
    {
        osg::Matrix mTrans;
        mTrans.makeTranslate(osg::Vec3f((double)nTransDis, 0.0f, 0.0f));

        osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();
        b_isNew = true;
        mt->setMatrix(mTrans);
        mt->addChild(getSelfSkinVesselData(strNewFilePath));
        root->addChild(mt);
    }

    root->addChild(makeCoordinate());
    root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);
    root->getOrCreateStateSet()->setMode(GL_LIGHT0, osg::StateAttribute::ON);
    setLight(root);

    viewer->setSceneData(root.get());
    viewer->addEventHandler(new CPickHandler(viewer));
    viewer->setLightingMode(osg::View::NO_LIGHT);

    osg::ref_ptr< osg::DisplaySettings > displaySettings = new osg::DisplaySettings;
    displaySettings->setNumMultiSamples(8);
    viewer->setDisplaySettings(displaySettings.get());
    viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
    viewer->run();
}

osg::Node*  getTheSelfSkinNode()
{
    parseConfig();
    QString path;
    QDir dir;
    path = dir.currentPath();

    QString strOldLeftSeg = path + "\\VesselData\\old_left_Segment.txt";
    std::string strOldFilePath = strOldLeftSeg.toStdString();

    QString strNewLeftSeg = path + "\\VesselData\\new_left_Segment.txt";
    std::string strNewFilePath = strNewLeftSeg.toStdString();

    osg::ref_ptr<osg::Group> root = new osg::Group();
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
    viewer->setUpViewInWindow(100, 100, 1080, 960);

    if (b_showOld)
    {
        b_isNew = false;
        root->addChild(getSelfSkinVesselData(strOldFilePath));
    }

    if (b_showNew)
    {
        osg::Matrix mTrans;
        mTrans.makeTranslate(osg::Vec3f((double)nTransDis, 0.0f, 0.0f));

        osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();
        b_isNew = true;
        mt->setMatrix(mTrans);
        mt->addChild(getSelfSkinVesselData(strNewFilePath));
        root->addChild(mt);
    }

    root->addChild(makeCoordinate());
    root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);
    root->getOrCreateStateSet()->setMode(GL_LIGHT0, osg::StateAttribute::ON);
    setLight(root);
    return root.release();
}
}



