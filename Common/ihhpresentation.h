#ifndef IHHPRESENTATION_H
#define IHHPRESENTATION_H
#include <QObject>
#include <QVariantMap>
#include <QVector>
#include <QGraphicsItem>
#include <QString>
#include <QVariant>
#include <QJsonObject>
#include "hhglobaldefine.h"
#include "ihhimagecollection.h"
#include "hhglobaldefine.h"

class IHHCommandManager;
class IHHSlide;
class IHHResourceCollectionX;
class IHHPresentation {
public:
    virtual ~IHHPresentation(){}
    //virtual void fileOpen( QVariantMap param ) = 0;//打开文档
    
	// modify by tianyu 2018.3.14
	virtual void fileNew(HHGlobalDefine::PresentationType type, QString strBackColor) = 0;//新建文档
	// modify by tianyu 2018.3.14

	//
    virtual QVector< IHHSlide* > pasteSlides( IHHSlide *refSlide, QVector< IHHSlide* > slides ) = 0;

	// 更新背景
    virtual void updateSlides( QVector< IHHSlide* > slides, QString strType, QString strValue) = 0;

	//
    virtual int getSlideCount() = 0;
    virtual IHHSlide* getSlide( int index ) = 0;
    virtual int getSlideIndex( IHHSlide *slide ) = 0;
    
	//
	virtual void setParameters( QString type, QVariant value ) = 0;// 设置参数
    virtual QVariant getParameters( QString type ) = 0;// 得到参数
    
	//
	virtual void getJSONObj( QJsonObject& jsonObj ) = 0;// 得到JSON对象
    virtual void fromJSONObj( QJsonObject& jsonObj ) = 0;// 从JSON对象获取数据
    virtual void fromJSONObj2( QJsonObject& jsonObj ) = 0;// 从JSON对象获取数据2

    //
    virtual QObject* getObject() = 0;

    //
    virtual void resetAllTransform() = 0;

    // 设置显示比例
    virtual void setProportion(QString strProportion) = 0;
    virtual void changeProportionScale(QPointF point, float xRate, float yRate) = 0;
    virtual void changeProportionTranslate(float xOffset, float yOffset) = 0;

    // 获得显示比例
    virtual QString getProportion() = 0;

    // 根据索引加载Slide
    virtual bool loadSlide(int nIndex) = 0;

    // 清除数据
    virtual void clearData() = 0;

    // 参考位于nIndex的Slide，在其后加入Slide
    virtual IHHSlide* addSlideRef(int nIndex) = 0;

	// 在nIndex增加Slide
	virtual void insertSlide(int nIndex, IHHSlide* pSlide) = 0;

	//
	virtual void addSlide(int nIndex, IHHSlide *pSlide) = 0;

	// 增加SLide,背景为白色
	virtual IHHSlide *addSlide(int nIndex) = 0;

	// 新建页面：外部传入背景图、背景色
    //virtual IHHSlide* addSlideByBackGround(int nIndex,QString BacColor, QPixmap pixBack) = 0;

    // 删除位于nIndex的Slide
    virtual void deleteSlides(QVector<int> vSlides) = 0;

    // 根据索引copy Slides
    virtual void copySlides(QVector<int> vSlides) = 0;

    // 在nIndex之后paste Slides
    virtual QVector<IHHSlide*> pasteSlides(int nIndex) = 0;

    //
    virtual void cutSlides(QVector<int> vSlides) = 0;

	//
    virtual IHHCommandManager* getCommandManager() = 0;

    // 移动vSlides, 到nIndexTo
    virtual void moveSlides(QVector<int> vSlides, int nIndexTo) = 0;

    virtual QString getId() = 0;

    // 获得书写区
    virtual QRectF getWorkArea() = 0;

    // 设置文件名
    virtual void setFileName(QString strName) = 0;

    // 获取文件名
    virtual QString getFileName() = 0;

    // 是否修改
    virtual void setDirty(bool bDirty) = 0;

	// 是否修改
	virtual bool isDirty() = 0;

	// 获取Slides
	virtual QVector< IHHSlide* > getSlides() = 0;

	// 设置作者
	virtual void setCreator(QString strCreator) = 0;

	// 设置创建时间
	virtual void setDate(QString strDate) = 0;

	// 设置应用程序版本
	virtual void setAppVersion(QString strAppVersion) = 0;

	// 根据ID获得Slide
	virtual IHHSlide* getSlideByID(QString strID) = 0;

	// ================================ 背景图 ==================================
	// 设置缺省背景颜色
	virtual void setDefaultBackColor(QString strBackColor) = 0;

	// ================================ 图片处理 ==================================
	//
    virtual void setResourceCollection(IHHResourceCollectionX *pHImageCollection) = 0;
	
	//
    virtual IHHResourceCollectionX *getResourceCollection() = 0;

	//
	virtual IHHImageCollection *getImageCollection() = 0;

	// ================================ 互动页 ==================================
	// 增加互动页
	// nType == 1 : text_match
	// nType == 2 : super_classify
	// nType == 3 : gap_filling
	// nType == 4 : group_competition
	virtual IHHSlide* addActivitySlide(int nIndex, QString strType, QString strTemplet) = 0;
};


Q_DECLARE_INTERFACE( IHHPresentation, "com.hht.qtWhiteBoard.IHHPresentation/1.0" )
Q_DECLARE_METATYPE( IHHPresentation* )

#endif // IHHTRANSFORMACTION_H
