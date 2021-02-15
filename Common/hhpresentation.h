#ifndef HHPRESENTATION_H
#define HHPRESENTATION_H

#include "lib_global.h"
#include <QJsonArray>
#include <QSize>
#include <QMap>
#include "ihhpresentation.h"

class HHCanvas;
class HHSlide;
class HHCommandPump;
class IHHCommandManager;
class IHHPrimitiveItem;
class LIB_EXPORT HHPresentation : public QObject, public IHHPresentation
{
	Q_OBJECT
		Q_INTERFACES(IHHPresentation)

public:
	HHPresentation();
	virtual ~HHPresentation();

private:
	//Add By Zhaojianbiao  20171018 start
	//存储新建模板信息
	QVariantMap m_pThemeMap;
	//Add By Zhaojianbiao  20171018 end

public:
	// "ID"	- m_strID
	// "PreType"	- m_nPreType
	// "FristThemeInfo"	- m_pThemeMap
	virtual void setParameters(QString type, QVariant value);// 设置参数

	// "type"	- m_nPreType
	// "Name"	- m_strFileName
	// "FristThemeInfo"	- m_pThemeMap
	virtual QVariant getParameters(QString type);// 得到参数

	// 
	virtual QObject* getObject();

	// ================================ Slide属性更新 ==================================
public:
	// 更新Slide
	virtual void updateSlides(QVector< IHHSlide* > slides, QString strType, QString strValue);

	// 重置所有Slide页面漫游matrix
	virtual void resetSlideTransform();

    // 重置所有矩阵
    virtual void resetAllTransform();

	// ================================ Slide操作 ==================================
public:
	// 获得Slide数量
	virtual int getSlideCount();

	// 获取Slide
	virtual IHHSlide* getSlide(int index);

	// 获取Slide索引
	virtual int getSlideIndex(IHHSlide *slide);

	//
	QVector< IHHSlide* > pasteSlides(IHHSlide *refSlide, QVector< IHHSlide* > slides);

	// ================================ Slide操作 (new) ==================================

	// 根据ID获得Slide
	virtual IHHSlide* getSlideByID(QString strID);

	// 参考位于nIndex的Slide，在其后加入Slide
	virtual IHHSlide* addSlideRef(int nIndex);

    // 新建页面：外部传入背景图、背景色
    //virtual IHHSlide* addSlideByBackGround(int nIndex,QString BacColor, QPixmap pixBack);

	// 增加SLide,背景为白色
	IHHSlide *addSlide(int nIndex);

	//
	virtual void addSlide(int nIndex, IHHSlide *pSlide);

	// 新增Slide
	IHHSlide* addSlide();

	// 删除位于nIndex的Slide
	virtual void deleteSlides(QVector<int> vSlides);

	// 根据索引copy Slides
	// 剪切板格式："hhtslide:slide_id_1;slide_id_2,slide_id_3"
	virtual void copySlides(QVector<int> vSlides);

	// 在nIndex之后paste Slides
	// 剪切板格式："hhtslide:slide_id_1;slide_id_2,slide_id_3"
	virtual QVector<IHHSlide*> pasteSlides(int nIndex);

	// cut vSlides
	// 剪切板格式："hhtslide:slide_id_1;slide_id_2,slide_id_3"
	virtual void cutSlides(QVector<int> vSlides);

	// 移动vSlides, 到nIndexTo
	virtual void moveSlides(QVector<int> vSlides, int nIndexTo);

	//
	virtual QString getId();

	// 获取Slides
	virtual QVector< IHHSlide* > getSlides();

	// 移动Slide
	void moveSlide(int from, int to);

	//
	IHHSlide *removeSlide(QString strID);

	//
	virtual void insertSlide(int nIndex, IHHSlide* pSlide);

	// ================================ 互动页 ==================================
	// 增加互动页
	// nType : 互动类型
	// nTemplet : 模板
	// strType : text_match
	// strType : super_classify
	// strType : gap_filling
	// strType : group_competition
	IHHSlide* addActivitySlide(int nIndex, QString strType, QString strTemplet);

private:
	QVector<IHHSlide*> getSlidesByID(QStringList list);
		
//public:
private:
	// 保存Slide	private???
	QVector< IHHSlide* > m_aySlide;

private:
	// 创建新的Slide
	void createSlide(QString strBackColor);

	// ================================ 文件操作 ==================================
public:
	// 打开HHTX文档
	//virtual void fileOpen(QVariantMap param);

	// 保存文档
	//virtual void fileSave(QVariantMap param);

	// 关闭文档
	//virtual void fileColse(QVariantMap param);

	// 新建文档  
	//virtual void fileNew(QVariantMap param);
	virtual void fileNew(HHGlobalDefine::PresentationType type, QString strBackColor);

	// 设置文件名
	virtual void setFileName(QString strName);

	// 获取文件名
	virtual QString getFileName();

	// 是否修改
	virtual void setDirty(bool bDirty);

	// 是否修改
	virtual bool isDirty();

	// 清除数据
	virtual void clearData();

private:
	// 文档名
	QString m_strFileName;

	// 文档类型 
	// HHT =  0x0,
	// HHTX = 0x1 
	int m_nPreType;
	
protected:
	// 文档标识 private???
	QString m_strID;

private:
	// 文档是否修改 private???
	bool m_bDirty;
	
	// ================================ Load/Save ==================================
public:
	// 外部调用 - Save
	virtual void getJSONObj(QJsonObject& jsonObj);// 得到JSON对象

	// 外部调用 - 加载main.xml中信息
    virtual void fromJSONObj(QJsonObject& jsonObj);// 从JSON对象获取数据

    virtual void fromJSONObj2( QJsonObject& jsonObj );// 从JSON对象获取数据2

	// 根据索引加载Slide数据
	virtual bool loadSlide(int nIndex);

	// 设置作者
	virtual void setCreator(QString strCreator);

	// 设置创建时间
	virtual void setDate(QString strDate);

	// 设置应用程序版本
	virtual void setAppVersion(QString strAppVersion);

private:
	// 只创建不加载Slide
	void loadSlides(QJsonObject& jsonObj);

    //创建slides
    void creatSlides(QJsonObject& jsonObj);

	// 存储全部文档的Json数据 - 在打开文档时一次加载进来
	//QJsonObject   m_data;

	// 作者
	QString m_strCreator;

	// 创建时间
	QString m_strDateCrate;

	// 修改时间
	QString m_strDateModified;
	
	// 数据格式版本
	QString m_strVersion;

	// 应用程序版本
	QString m_strVersionApp;

	// ================================ 命令操作 ==================================
public:
	// 命令泵  private???
	HHCommandPump *m_cmdPump;

	// 获取m_cmdPump
	virtual IHHCommandManager* getCommandManager();

	// ================================ 显示 ==================================
public:
	// 设置显示比例
	virtual void setProportion(QString strProportion);
    virtual void changeProportionScale(QPointF point, float xRate, float yRate);
    virtual void changeProportionTranslate(float xOffset, float yOffset);

	// 获得显示比例
	virtual QString getProportion();

	// 获得书写区
	QRectF getWorkArea();

	// 设置书写区
	void setWorkArea(QRectF rect);

private:
	// 显示比例
	QString m_strProportion;

	// 书写区
	QRectF m_rectWorkArea;

	// 根据显示比例获得书写区大小
	QSize getSizeFromProportion(QString strProportion);

	// ================================ 图片处理 ==================================
public:
	//
    virtual void setResourceCollection(IHHResourceCollectionX *pResourceCollection);
	
	//
    virtual IHHResourceCollectionX *getResourceCollection();

	//
	virtual IHHImageCollection *getImageCollection();

private:
	//
	IHHImageCollection *m_pImageCollection;

	//
    IHHResourceCollectionX *m_pResourceCollection;

	// ================================ 背景图 ==================================
public:
	// 设置缺省背景颜色
	virtual void setDefaultBackColor(QString strBackColor);

private:
	// 缺省背景颜色
	QString m_strDefaultBackColor;

	// ================================ 信号 ==================================
Q_SIGNALS:
	// 发出切换Slide的信号，由HHCanvas响应 - HHCanvas::sltPreActiveSlide(IHHPresentation *pre)
	// connect( m_pPre, SIGNAL( sigPreActiveSlide( IHHPresentation*, IHHSlide* ) ), (HHCanvas*)this, SLOT( sltPreActiveSlide( IHHPresentation*, IHHSlide* ) ) );
    void sigPreActiveSlide(IHHSlide*);

	// Slide增删改查发出信号
	// nType = 0 : update all slide
	// nType = 1 : 增加;	vSlides: 新加入Slide的索引数组
	// nType = 2 : 删除;	vSlides: 删除Slide的索引数组
	// nType = 3 : 特效;	vSlides: 特效Slide的索引数组
	// nType = 4 : 删除前;	vSlides: 删除Slide的索引数组前发出信号
	void signalChange(int nType, QVector<int> vSlides);

	// 数据文件加载完毕后发出信号
	// nIndex : Slide索引
	void signalLoaded(int nIndex);

    // 文档准备完毕
    void signalPreReady(int nIndex);

	// remove by tioanyu 2018.7.20
	// 清除数据前发出信号
	//void signalDataClear();
	// - remove by tioanyu 2018.7.20

	// Slide属性(比如：背景，特效)变化时信号
	// nType = 0 : 背景
	// nType = 1 : 特效
	void signalSlidePropChanged(int nType);

	// 文档变化(比例)时发出信号
    void signalProportionChanged();
	
	// HHPresentation析构时发出信号
	//void sigPreDetach(IHHPresentation*);
	// - remove by tioanyu 2018.7.20
	
	// 命令栈变化时发出信号
	// int nUndoSize - 命令栈undo大小
	// int nRedoSize - 命令栈Redo大小
	void signalCmdPumpChanged(int nUndoSize, int nRedoSize);
};

#endif // HHPRESENTATION_H
