#ifndef IHHPRESENTATIONCONTROLLER_H
#define IHHPRESENTATIONCONTROLLER_H
#define FILEOPERATOR

#include <QString>
#include <QObject>
#include <QVector>
#include <memory>
#include "hhglobaldefine.h"

class IHmCloudComm;
class IHHPresentation;
class IHHCanvas;
class IHHModel;
class IHHPresentationController
{
public:
    virtual ~IHHPresentationController(){}
    virtual QObject* getObject() = 0;
        //modify by zhangjinlu 2018/03/26 start���ӵ�ǰ�û�,����ʱ����Ϣ,�Ƿ��ǹ��������α����־
        virtual IHHPresentation * fileSave(QString fileName, bool bSaveAgain, QString userName, QString saveTime, IHHCanvas * canvas,
		IHHPresentation * currentpres, IHHModel *model, IHmCloudComm * cloudComm) = 0;
        virtual void terminateSaving() = 0;//�����������ֹ���涯��
        //modify by zhangjinlu 2018/03/26 end
        virtual IHHPresentation * fileOpen(bool oldSave, IHHPresentation * oldPres, QString savePath
		, QString openPath,
		IHHCanvas * canvas,
		IHHModel *model
		, IHmCloudComm * cloudComm) = 0;

	// modify by tianyu 2018.3.14
	//virtual IHHPresentation * fileNew(QString Proportion, HHGlobalDefine::PresentationType type, IHHPresentation * oldpres, IHHPresentation * newPres, IHHCanvas * canvas) = 0;
	virtual IHHPresentation * fileNew(QString Proportion, QString strBackColor, HHGlobalDefine::PresentationType type, IHHPresentation * oldpres, IHHPresentation * newPres, IHHCanvas * canvas) = 0;
	// modify by tianyu 2018.3.14
	
	virtual void fileExport(QString fileName,IHHCanvas * canvas,IHHPresentation * currentPre,IHmCloudComm * cloudComm) = 0;
    virtual void fileClose(IHHPresentation * pres,IHHCanvas * canvas)=0;
    virtual void setParentObj(QObject * parent)=0;

	// �ο�λ��nIndex��Slide����������Slide
	virtual void addSlideRef(IHHPresentation *pIHHPresentation, IHHCanvas *pIHHCanvas) = 0;

	// ɾ��λ��nIndex��Slide
	virtual void deleteSlide(IHHPresentation *pIHHPresentation) = 0;

	// ��������copy Slides
	virtual void copySlides(IHHPresentation *pIHHPresentation) = 0;

	// ��nIndex֮��paste Slides
	virtual void pasteSlides(IHHPresentation *pIHHPresentation, IHHCanvas *pIHHCanvas) = 0;

	// cut vSlides
	virtual void cutSlides(IHHPresentation *pIHHPresentation) = 0;

	// ����ѡ���Slide
	virtual void setSlidesSel(QVector<int> &vSlidesSel) = 0;

	// undo
	virtual void undoCommand(IHHPresentation *pIHHPresentation) = 0;

	// redo
	virtual void redoCommand(IHHPresentation *pIHHPresentation) = 0;

	// �ƶ�vSlides, ��nIndexTo
	virtual void moveSlides(IHHPresentation *pIHHPresentation, int nIndexTo) = 0;
};
Q_DECLARE_INTERFACE( IHHPresentationController, "com.hht.qtWhiteBoard.IHHPresentationController/1.0" )
Q_DECLARE_METATYPE( IHHPresentationController* )

#endif // IHHFILEOPERATORCONTROLLER_H
