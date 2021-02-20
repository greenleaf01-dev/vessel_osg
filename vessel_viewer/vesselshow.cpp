// Win32Project1.cpp : 定义控制台应用程序的入口点。
//

#include <windows.h>
#include <GL/glu.h>
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
#include <QString>
#include <QCoreApplication>
#include <QDir>
#include <QMessageBox>
#include "vessel_show.h"
static std::vector<osg::ref_ptr<osg::Material>>  vecMaterial; 
static float s_fLength = 6.0;


bool b_isNew = true;
bool b_showOld = true;
bool b_showNew = true;
bool b_showText = true;
const osg::Vec4 colorOld = { 1.0,0.5,0.2f,1.0 };
const osg::Vec4 colorNew = { 1.0,1.0,1.0,1.0 };
int nTransDis = 0;

std::wstring s_strLabel;
std::wstring s_strX = L"X";
std::wstring s_strY = L"Y";
std::wstring s_strZ = L"Z";



void setMaterial(osg::ref_ptr<osg::Group> root, const osg::Vec4& vecColor)
{
	//设置材质
	osg::ref_ptr<osg::Material> material = new osg::Material;
	//设置正面散射颜色
	material->setDiffuse(osg::Material::FRONT, vecColor);
	//设置正面镜面颜色
	material->setSpecular(osg::Material::FRONT, osg::Vec4(1.0, 0.0, 0.0, 1.0));
	//设置正面指数
	material->setShininess(osg::Material::FRONT, 90.0);
	material->setColorMode(osg::Material::AMBIENT);
	root->getOrCreateStateSet()->setAttribute(material.get());
}

osg::Geode* createCornidateText(const osg::Vec3& pos, const std::wstring& content, float size, const osg::Vec4& vecColor)
{
	osg::ref_ptr<osgText::Text> text = new osgText::Text;
	text->setCharacterSize(size);
	text->setAxisAlignment(osgText::TextBase::SCREEN);
	text->setPosition(pos);
	text->setText(content.c_str());
	text->setColor(vecColor);

	text->setDataVariance(osg::Object::DYNAMIC);

	osg::ref_ptr<osg::Geode>  geode = new osg::Geode();
	geode->addDrawable(text);

	return geode.release();
}


static osg::ref_ptr<osg::MatrixTransform> createCylinder(const osg::Vec3 &from, const osg::Vec3 &to, float radius)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();
	osg::ref_ptr<osg::ShapeDrawable> cylinder = new osg::ShapeDrawable();
	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints();

	hints->setDetailRatio(0.8f);
	osg::Vec3 cylCenter = (to + from) / 2;		//得到柱心
	float height = (to - from).length();		//得到长度
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
	setMaterial(geode, cylinder->getColor());
	osg::Matrix mRotate, mTrans;
	mRotate.makeRotate(osg::Vec3f(0.0f, 0.0f, 1.0f), to - from);
	mTrans.makeTranslate(cylCenter);
	mt->setMatrix(mRotate*mTrans);
	mt->addChild(geode.get());
	mt->setDataVariance(osg::Object::DYNAMIC);
	return mt.get();
}


osg::ref_ptr<osg::MatrixTransform> createCoordinateCylinder(const osg::Vec3 &from, const osg::Vec3 &to, float radius, osg::Vec4& vecColor)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();
	osg::ref_ptr<osg::ShapeDrawable> cylinder = new osg::ShapeDrawable();
	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints();

	hints->setDetailRatio(0.8f);
	osg::Vec3 cylCenter = (to + from) / 2;		//得到柱心
	float height = (to - from).length();		//得到长度
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

osg::ref_ptr<osg::MatrixTransform> createCone(const osg::Vec3 &from, const osg::Vec3 &to, float radius, osg::Vec4& vecColor)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();
	osg::ref_ptr<osg::ShapeDrawable> cone = new osg::ShapeDrawable();
	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints();

	hints->setDetailRatio(0.8f);
	osg::Vec3 cylCenter = (to + from) / 2;		//得到柱心
	float height = (to - from).length();		//得到长度
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
	osg::Vec4 vecColorX = {0.8f,1.0f,0.0f,1.0f}; 
	auto nodeX = createCoordinateCylinder(osg::Vec3(0, 0, 0), osg::Vec3(s_fLength, 0, 0), s_fLength *0.05, vecColorX);
	auto nodeX1 = createCone(osg::Vec3(s_fLength, 0, 0), osg::Vec3(s_fLength  * 1.2, 0, 0), s_fLength *0.08, vecColorX);
	
	osg::ref_ptr<osg::Geode>  geoTextX = createCornidateText(osg::Vec3(s_fLength  * 1.2, 0, 0),s_strX,1.5, vecColorX);

	osg::ref_ptr<osg::Group> node_x = new osg::Group();
	node_x->addChild(nodeX);
	node_x->addChild(nodeX1);
	node_x->addChild(geoTextX);
	setMaterial(node_x, vecColorX);

	osg::Vec4 vecColorY = { 0.5f,0.9f,0.0f,1.0f };
	auto nodeY = createCoordinateCylinder(osg::Vec3(0, 0, 0), osg::Vec3(0.0, s_fLength, 0), s_fLength *0.05,vecColorY);
	auto nodeY1 = createCone(osg::Vec3(0.0, s_fLength, 0), osg::Vec3(0.0, s_fLength * 1.2, 0), s_fLength *0.08, vecColorY);
	osg::ref_ptr<osg::Geode>  geoTextY = createCornidateText(osg::Vec3(0.0, s_fLength * 1.2, 0), s_strY, 1.5, vecColorY);

	osg::ref_ptr<osg::Group> node_Y = new osg::Group();
	node_Y->addChild(nodeY);
	node_Y->addChild(nodeY1);
	node_Y->addChild(geoTextY);
	setMaterial(node_Y, vecColorY);

	osg::Vec4 vecColorZ = { 0.0f,0.5f,0.9f,1.0 };
	auto nodeZ = createCoordinateCylinder(osg::Vec3(0, 0, 0), osg::Vec3(0.0, 0.0, s_fLength), s_fLength *0.05, vecColorZ);
	auto nodeZ1 = createCone(osg::Vec3(0.0, 0.0, s_fLength), osg::Vec3(0.0, 0.0, s_fLength  * 1.2), s_fLength *0.08, vecColorZ);
	osg::ref_ptr<osg::Geode>  geoTextZ = createCornidateText(osg::Vec3(0.0, 0.0, s_fLength  * 1.2), s_strZ, 1.5, vecColorZ);

	osg::ref_ptr<osg::Group> node_Z = new osg::Group();
	node_Z->addChild(nodeZ);
	node_Z->addChild(nodeZ1);
	node_Z->addChild(geoTextZ);
	setMaterial(node_Z, vecColorZ);

	osg::ref_ptr<osg::Group> node_group = new osg::Group();
	node_group->addChild(node_x);
	node_group->addChild(node_Y);
	node_group->addChild(node_Z);

	osg::Multisample* pms = new osg::Multisample;
	pms->setSampleCoverage(1, true);
	node_group->getOrCreateStateSet()->setAttributeAndModes(pms, osg::StateAttribute::ON);
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


osg::ref_ptr<osg::ShapeDrawable> createOneBNode(const osg::Vec3& center, float size)
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
	QString path;
	QDir dir;
	path = dir.currentPath();
    QString  strFilePath = path + "\\VesselData\\config.txt";
	std::string strConfigFilePath = strFilePath.toStdString();
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

typedef std::vector<std::pair<std::vector<osg::Vec3>,std::wstring>>  vecSegment;

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

		 std::vector<float> vecTemp;
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
				 float fValue = std::stof(sTmp);
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

osgText::Text* createText(const osg::Vec3& pos, const std::wstring& content, float size)
{
	osg::ref_ptr<osgText::Text> text = new osgText::Text;
	if (!b_showText)
	{
		return text.release();
	}
	text->setCharacterSize(size);
	text->setAxisAlignment(osgText::TextBase::SCREEN);
	text->setPosition(pos);
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
			geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);
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
		
		osg::ref_ptr<osg::Geode> geode = new osg::Geode();
		geode->addChild(text);

		osg::ref_ptr<osg::ShapeDrawable> drawGeom = createOneBNode(*iter->first.rbegin(), 1.0f);
		geode->addChild(drawGeom);
		geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);
		nodeSegment->addChild(geode);
		group->addChild(nodeSegment);
	}

	root->addChild(group.get());
	root->setDataVariance(osg::Object::DYNAMIC);
	return root;
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
		lt->setDirection(osg::Vec3(0.0, 0.0, -1.0));
		//设置位置
		lt->setPosition(osg::Vec4(0.0, 0.0, 1.0, 0.0));
		//设置光的颜色
		lt->setDiffuse(osg::Vec4(0.8, 0.8, 0.8, 1.0));//红色的光
		ls->setLight(lt);
		pRoot->addChild(ls);
	}

	//{
	//	osg::ref_ptr<osg::LightSource> ls = new osg::LightSource();
	//	ls->setReferenceFrame(osg::LightSource::ABSOLUTE_RF);
	//	//创建光对象
	//	osg::ref_ptr<osg::Light> lt = new osg::Light();
	//	lt->setLightNum(1);
	//	//设置方向
	//	lt->setDirection(osg::Vec3(0.0, -1.0, 0.0));	
	//	//设置位置
	//	lt->setPosition(osg::Vec4(0.0, -100, 0.0, 0.0));
	//	//设置光的颜色
	//	lt->setDiffuse(osg::Vec4(0.8, 0.8, 0.8, 1.0));//红色的光
	//	ls->setLight(lt);
	//	pRoot->addChild(ls);
	//}
}


namespace Vessel
{
	osg::Node* GetVesselRootNode()
	{   
		QString path;
		QDir dir;
		path = dir.currentPath();
		osg::ref_ptr<osg::Group> root = new osg::Group();
		parseConfig();

		typedef std::tuple<float, float, float>  vesselPtn;
        QString strOldLeftSeg = path + "\\VesselData\\old_left_Segment.txt";
		std::string strOldFilePath = strOldLeftSeg.toStdString();

        QString strNewLeftSeg = path + "\\VesselData\\new_left_Segment.txt";
        std::string strNewFilePath = strNewLeftSeg.toStdString();

		if (b_showOld)
		{
			b_isNew = false;
			root->addChild(getTheVesselData(strOldFilePath).get());
		}

		if (b_showNew)
		{
			osg::Matrix mTrans;
			mTrans.makeTranslate(osg::Vec3f((float)nTransDis, 0.0f, 0.0f));

			osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();
			b_isNew = true;
			mt->setMatrix(mTrans);
			mt->addChild(getTheVesselData(strNewFilePath).get());
			root->addChild(mt);
		}

		root->addChild(makeCoordinate());
		root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);
		root->getOrCreateStateSet()->setMode(GL_LIGHT0, osg::StateAttribute::ON);
		//root->getOrCreateStateSet()->setMode(GL_LIGHT1, osg::StateAttribute::ON);

		setLight(root);
		return root.release();
	}
}
