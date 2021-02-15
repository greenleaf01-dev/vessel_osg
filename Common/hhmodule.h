#ifndef HHMODULE_H
#define HHMODULE_H

#include "lib_global.h"
#include "hhplugin.h"
#include "ihhmodule.h"
#include <QVariantMap>
#include <QMatrix>
#include <QWidget>
#include <QGraphicsEffect>

class HHModule;
class LIB_EXPORT HHDrawingWidget : public QWidget
{
public:
    HHDrawingWidget( QWidget* pParent, HHModule *module, bool bTool );
    virtual ~HHDrawingWidget();

public:
    void        hideLater();
    void        stopHide();
    void        showAccordWhetherHidden();
    int         m_nTimer;
    QPixmap     *m_pTempPix;
    bool        m_bTool;
    HHModule    *m_pModule;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    virtual void timerEvent(QTimerEvent *event);
};

class IHHCanvas;
class LIB_EXPORT HHModule : public QObject, public IHHModule {
    Q_OBJECT
    Q_INTERFACES( IHHModule )

public:
    HHModule();
    virtual ~HHModule();

protected:
    QString                 m_strModuleID;
    QString                 m_strItemID;
    IHHPrimitiveItem        *m_pItem;
    IHHCanvas               *m_pICanvas;
    QVariantMap             m_param;
    HHDrawingWidget         *m_pTempWidget;
    QPixmap                 *m_pTempPix;
    QVariantMap             m_moduleData;
    QCursor                 m_cursor;

protected:
    void resetTempPix();
    void createDrawWidget( QWidget *parent, HHModule *module, bool bTools );

public:
    virtual void setParameters( QString type, QVariant value );
    virtual QVariant getParameters( QString type );
    virtual void performTouchStart( QPointF point, QVariantMap param );
    virtual void performTouchMove( QPointF point, QVariantMap param );
    virtual void performTouchEnd( QPointF point, QVariantMap param );
    virtual void revert( QVariantMap param );
    virtual int isSupportMultiPen( QString itemID );
    virtual void drawItems( QPainter *painter, QRectF rect );
    virtual void setModuleData( QVariantMap param );
    virtual QVariantMap getModuleData();
    virtual QString getModuleID();
    virtual QString getModuleCreateItemID();
    virtual void setModuleCreateItemID( QString strItemID );
    virtual IHHModule* cloneModule();
    virtual QObject* getObject();
    virtual QCursor getCursor();

protected:
    virtual HHPlugin* getPlugin();
    virtual void performLButtonDownHelper( QPointF point, QVariantMap param );
    virtual void performLButtonMoveHelper( QPointF point, QVariantMap param );
    virtual void performLButtonUpHelper( QPointF point, QVariantMap param );
    virtual void createItem( QString itemID, QVariantMap param );

signals:
    void sigAddItemToSelection( IHHPrimitiveItem *item );
};

#endif
