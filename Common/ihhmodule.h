#pragma once
#include <QObject>

class IHHModule {
public:
    virtual ~IHHModule(){}
    virtual void setParameters( QString type, QVariant value ) = 0;// 设置参数
    virtual QVariant getParameters( QString type ) = 0;

    virtual void setModuleData(QVariantMap param) = 0;  // added by xuxia, 2018/02/05
    virtual QVariantMap getModuleData() = 0;            // added by xuxia, 2018/02/05
    virtual QString getModuleID() = 0;
    virtual QString getModuleCreateItemID() = 0;
    virtual void setModuleCreateItemID( QString strItemID ) = 0;
    virtual IHHModule* cloneModule() = 0;
    virtual QObject* getObject() = 0;
    virtual QCursor getCursor() = 0;

    virtual void performTouchStart( QPointF point, QVariantMap param ) = 0;// 处理Touch Start事件
    virtual void performTouchMove( QPointF point, QVariantMap param ) = 0;// 处理Touch Move事件
    virtual void performTouchEnd( QPointF point, QVariantMap param ) = 0;// 处理Touch End事件
    virtual void revert( QVariantMap param ) = 0;
    virtual int isSupportMultiPen( QString itemID ) = 0;
};

Q_DECLARE_INTERFACE( IHHModule, "com.hht.qtWhiteBoard.IHHModule/1.0" )
Q_DECLARE_METATYPE( IHHModule* )
