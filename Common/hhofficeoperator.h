#ifndef HHOFFICEOPERATOR_H
#define HHOFFICEOPERATOR_H

#include "utility_global.h"
#include <QObject>
#include <QRect>
#include <QThread>
#include <QJsonArray>

class HHOfficeOperator;
class OfficeThread : public QThread {
    Q_OBJECT
public:
    OfficeThread( HHOfficeOperator *mainwindow );
    void run();

public:
    bool                m_bPause;
    bool                m_bStop;
    HHOfficeOperator    *m_mainwindow;
};

class HHOfficeDoc;
class QWidget;
class OfficeThread;
class UTILITYSHARED_EXPORT HHOfficeOperator : public QObject {
    Q_OBJECT
public:
    HHOfficeOperator(bool bExport);
    HHOfficeOperator( QRect rect, QWidget *whiteboard );
    virtual ~HHOfficeOperator();
    void startDetect();
    void stopDetect();
    void embedImage( QString strFile, QRect rectEmbeded, QString strDoc = "" );
    void setPPTPlayingNext();
    void setPPTPlayingPrevious();
    void setPPTPlayingEnd();
    void setWPSPPTPlayingPenType( QString strType );

    bool exportPPT(QString fileName, QStringList picList);
    bool exportPDF(QString fileName, QStringList picList);
    bool exportWORD(QString fileName, QStringList picList);
    bool exportHTML(QString fileName, QStringList picList);
    bool exportImage(QString fileName, QStringList picList);
    bool exportEXCEL(QString fileName, QStringList picList);

    bool connectWPS();
    bool connectOffice();
    bool exportWPSWord( QString fileName, QStringList picList );
    bool exportWPSExcel( QString fileName, QStringList picList );
    bool exportWPSPpt( QString fileName, QStringList picList );

    QStringList importPPT(QString fileName, QString saveDir);
    QVariantMap importPPT2(QString fileName );
    QVariantMap getJSONFromPPTSlide(void* pSlide, QString strDir);
    QJsonObject getItemJson(void* pItem, QString strDirList);
    void closePPTPresentation(void* presentation);

	//Add by wangxianbing,2018/1/10 尝试关闭ppt进程。
	void closePPTApp();

    // Add By Fanhj
    void getPPTPageInfo(QString &sPageInfo);
    void setPPTPenInfo(const QString &sPenType,
                       const QVariantMap &args);
    bool getPPTThumbnail(QStringList &lResultFile,
                         const QString &sPath,
                         const QString sImgType = QString("png"),
                         const QSize imgSize = QSize(180, 110));
    // Add End

Q_SIGNALS:
    void sigHaveOffice( QString officeType );
    void sigPPTPlayingSlideIndex( int index );
    void sigRefreshPPTPlaying();

public Q_SLOTS:
    void sltDetectOffice();
    void sltRefreshPPTPlaying();

private:
    OfficeThread            *m_timer;
    HHOfficeDoc             *m_doc;
    QRect                   m_rect;
    QWidget                 *m_whiteboard;
    QString                 m_strDocumentType;
    bool                    m_bExport;
};

#endif // HHOFFICEOPERATOR_H
