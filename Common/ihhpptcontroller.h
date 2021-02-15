#ifndef _IHHPPTCONTROLLER_H_
#define _IHHPPTCONTROLLER_H_

#include <QString>
#include <QMap>

#ifndef NOUSE_BITMAP
#include <QPixmap>
#endif
#include <QObject>
#include <QSize>

typedef struct _tagThumbnai
{
        QString path;
#ifndef NOUSE_BITMAP
        QPixmap pixmap;
        QString strMd5;
#endif

}Thumbnai;

class IHHPptController{
public:
	IHHPptController() {}
	~IHHPptController() {}

        static  IHHPptController* GetInstance();

        /* runApp:启动程序
	 * strExePathName:应用程序全路径
	 * args:启动参数
	*/
        virtual void	runApp(const QString& strExePathName , const QStringList& args) = 0;

        /* stopApp:退出指定程序
	 * strExePathName:应用程序全路径
	 * args:启动参数
	*/	
        virtual void	stopApp(const QString& strExePathName, const QStringList& args) = 0;

	/* findProcess:查找指定程序名的进程是否存在
	 * szExeName:程序名
	 * 返回：true: 进程存在 false:进程不存在
	*/
        virtual bool findProcess(const QString& szExeName) = 0;


	/* moniPptChange:监控ppt变化
	 * bMonitor:是否启动ppt信息变化监听定时器
	*/
        virtual void	moniPptChange(bool bMonitor = false) = 0;

	/* isPptPlaying判断ppt程序是否处于幻灯片播放状态
	   hPlayWnd:播放窗口句柄
	*/			
        virtual int	isPptPlaying(long *hPlayWnd) = 0;

	
	/* putSlideCommand:指挥幻灯片做指定的动作
	 * strId:操作标志字符串
	 * strParams:设置参数
	*/
        virtual int	putSlideCommand(const QString& strId, const QString& strParams) = 0;

	/* putSlideCommand:获取幻灯片的当前指定信息
	 * strId:获取信息标志字符串
	 * strParams:幻灯片的当前指定信息
	 * 返回：true-获取成功 false-获取失败
	*/	
        virtual bool	getSlideCurrentInfo(const QString& strId, QString& strParams) = 0;

	/* getCurrentPage 获取当前播放幻灯片的序号
	 * 返回：当前播放幻灯片的序号
	*/
        virtual int	getCurrentPage() = 0;

	/* getCurrentPage 获取当前活动ppt文档的幻灯片的总数
	 * 返回：当前活动ppt文档的幻灯片的总数
	*/
        virtual int	getTotalPage() = 0;
	
	/* next下一页
	 * 返回：当前活动ppt文档的下一页页码
	*/
        virtual int	next() = 0;

	/* preview上一页
	 * 返回：当前活动ppt文档的上一页页码
	*/
        virtual int	preview() = 0;
	
	
	/* getThunmbnailList 创建并获取所有幻灯片的缩略图列表（包括序号，图片路径及对应的QPixmap对象
	 * thunmbList:获取到的缩列图信息
	 * imageType：缩略图类型
	 * imageType：生成路径
	 * size：大小
	*/
        virtual int	getThunmbnailList(QMap<int, Thumbnai>& thunmbList,
                        const QString& imageType = QString("png"),
                        const QString& strThumbPath = QString(),
                        const QSize size = QSize(180, 110)) = 0;

	/* createAssistantThumbnail 创建并获取指定序号段的幻灯片的缩略图列表（包括序号，图片路径及对应的QPixmap对象
	 * thunmbList:获取到的缩列图信息
	 * imageType：缩略图类型
	 * imageType：生成路径
	 * size：大小
	 * startNo：开始序号
	 * endNo：结束序号
	 * 返回: 生成的缩略图的个数
	*/
        virtual int	createSegmentThumbnail(const QString& imageType = QString("png"),
                const QString& strThumbPath = QString()
                , const QSize size = QSize(180, 110), int startNo = 0, int endNo = 0) = 0;
	
	/* getPlayWnd 获取当前播放幻灯片的句柄
	 * 返回：当前播放幻灯片的句柄
	*/
        virtual int	getPlayWnd() = 0;
 
};

#endif //_IHHPPTCONTROLLER_H_

