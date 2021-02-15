#ifndef HHWindowDelegate_H
#define HHWindowDelegate_H

#include <QWidget>
#include <QVariantMap>
#include <QThread>
#include <QObject>
#include <QObjectList>
#include <QVBoxLayout>

class HHWindowDelegate;

class IHHApplication;
class HHFrame;
class IHHFrame;
class IHHSlide;
class IHHCanvas;
class HHController;
class IHHController;
class IHHPrimitiveItem;

class MenuDynamic;

class HHWindowDelegate : public QObject
{
    Q_OBJECT
public:
    friend class HHController;

    HHWindowDelegate( QWidget *parent = 0 );
    virtual ~HHWindowDelegate();

    virtual void setIHHFrame(IHHFrame *pIHHFrame, IHHApplication *pIHHApp);
    virtual void setCentralWidget(QWidget *w);
    virtual void showWindow( QString strMode );
    virtual void hideWindow( QString strMode );
    virtual void switchSlide( IHHSlide *slide );
    virtual void initWindow();

    virtual IHHCanvas* getCanvas();
    virtual HHController* getController();
    virtual QWidget* getCentralWidget();
    virtual IHHSlide* getSlide( QString id );
    virtual QVariantMap getParam();
    virtual bool isBusy();

    HHController            *m_pController;
    QVariantMap             m_param;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Seach item by identifier. </summary>
	///
	/// <remarks>	gsl, 2017/8/17. </remarks>
	///
	/// <param name="list">	The list. </param>
	///
	/// <returns>	null if it fails, else a QVector&lt;IHHPrimitiveItem* &gt; </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	QVector< IHHPrimitiveItem* > seachItemByID(const QStringList & list);

	HHFrame * getHHFrame() const { return m_pHHFrame; }
	void setHHFrame(HHFrame * val) { m_pHHFrame = val; }

signals:
    void signalClickButton(QString strID, QVariantMap params);

public slots:
    virtual bool clickButton(QString strID, QVariantMap param);

	virtual void slotSetItemsPropety(QVector< IHHPrimitiveItem* > itemsSelected, QString strID, QVariantMap param);
private slots:

    bool clickMenuAction(QString strID, QVariantMap param);
    bool slotProcessCommand(QString strID, QVariantMap param);
    void slotAboutToHide();

protected:
    HHFrame         *m_pHHFrame;
    IHHApplication  *m_pIHHApp;

private slots:
    QPoint getShowTopLeft_Menu(QRectF rectW, QVariantMap param);

private:
    QWidget *m_pWidget;

    // selected objects
    QVector< IHHPrimitiveItem* >    items_Selected;
    //add by wangpeng
    QVector< IHHPrimitiveItem* >    m_itemsForGroupAndLock;
};

#endif
