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

        /* runApp:��������
	 * strExePathName:Ӧ�ó���ȫ·��
	 * args:��������
	*/
        virtual void	runApp(const QString& strExePathName , const QStringList& args) = 0;

        /* stopApp:�˳�ָ������
	 * strExePathName:Ӧ�ó���ȫ·��
	 * args:��������
	*/	
        virtual void	stopApp(const QString& strExePathName, const QStringList& args) = 0;

	/* findProcess:����ָ���������Ľ����Ƿ����
	 * szExeName:������
	 * ���أ�true: ���̴��� false:���̲�����
	*/
        virtual bool findProcess(const QString& szExeName) = 0;


	/* moniPptChange:���ppt�仯
	 * bMonitor:�Ƿ�����ppt��Ϣ�仯������ʱ��
	*/
        virtual void	moniPptChange(bool bMonitor = false) = 0;

	/* isPptPlaying�ж�ppt�����Ƿ��ڻõ�Ƭ����״̬
	   hPlayWnd:���Ŵ��ھ��
	*/			
        virtual int	isPptPlaying(long *hPlayWnd) = 0;

	
	/* putSlideCommand:ָ�ӻõ�Ƭ��ָ���Ķ���
	 * strId:������־�ַ���
	 * strParams:���ò���
	*/
        virtual int	putSlideCommand(const QString& strId, const QString& strParams) = 0;

	/* putSlideCommand:��ȡ�õ�Ƭ�ĵ�ǰָ����Ϣ
	 * strId:��ȡ��Ϣ��־�ַ���
	 * strParams:�õ�Ƭ�ĵ�ǰָ����Ϣ
	 * ���أ�true-��ȡ�ɹ� false-��ȡʧ��
	*/	
        virtual bool	getSlideCurrentInfo(const QString& strId, QString& strParams) = 0;

	/* getCurrentPage ��ȡ��ǰ���Żõ�Ƭ�����
	 * ���أ���ǰ���Żõ�Ƭ�����
	*/
        virtual int	getCurrentPage() = 0;

	/* getCurrentPage ��ȡ��ǰ�ppt�ĵ��Ļõ�Ƭ������
	 * ���أ���ǰ�ppt�ĵ��Ļõ�Ƭ������
	*/
        virtual int	getTotalPage() = 0;
	
	/* next��һҳ
	 * ���أ���ǰ�ppt�ĵ�����һҳҳ��
	*/
        virtual int	next() = 0;

	/* preview��һҳ
	 * ���أ���ǰ�ppt�ĵ�����һҳҳ��
	*/
        virtual int	preview() = 0;
	
	
	/* getThunmbnailList ��������ȡ���лõ�Ƭ������ͼ�б�������ţ�ͼƬ·������Ӧ��QPixmap����
	 * thunmbList:��ȡ��������ͼ��Ϣ
	 * imageType������ͼ����
	 * imageType������·��
	 * size����С
	*/
        virtual int	getThunmbnailList(QMap<int, Thumbnai>& thunmbList,
                        const QString& imageType = QString("png"),
                        const QString& strThumbPath = QString(),
                        const QSize size = QSize(180, 110)) = 0;

	/* createAssistantThumbnail ��������ȡָ����ŶεĻõ�Ƭ������ͼ�б�������ţ�ͼƬ·������Ӧ��QPixmap����
	 * thunmbList:��ȡ��������ͼ��Ϣ
	 * imageType������ͼ����
	 * imageType������·��
	 * size����С
	 * startNo����ʼ���
	 * endNo���������
	 * ����: ���ɵ�����ͼ�ĸ���
	*/
        virtual int	createSegmentThumbnail(const QString& imageType = QString("png"),
                const QString& strThumbPath = QString()
                , const QSize size = QSize(180, 110), int startNo = 0, int endNo = 0) = 0;
	
	/* getPlayWnd ��ȡ��ǰ���Żõ�Ƭ�ľ��
	 * ���أ���ǰ���Żõ�Ƭ�ľ��
	*/
        virtual int	getPlayWnd() = 0;
 
};

#endif //_IHHPPTCONTROLLER_H_

