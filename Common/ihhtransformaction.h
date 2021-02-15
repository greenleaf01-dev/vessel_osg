#ifndef IHHTRANSFORMACTION_H
#define IHHTRANSFORMACTION_H
#include <QObject>

class IHHTransformAction {
public:
    virtual ~IHHTransformAction(){}
    virtual void setParameters( QString type, QVariant value ) = 0;// 设置参数
    virtual QVariant getParameters( QString type ) = 0;
    virtual void revert() = 0;
    virtual QString getActionType() = 0;
    virtual void performTransformActionStart( IHHTransformAction *masterAction ) = 0;
    virtual void performTransformActionMove( IHHTransformAction *masterAction ) = 0;
    virtual void performTransformActionEnd( IHHTransformAction *masterAction ) = 0;
    virtual void performTouchStart(QPointF point, QVariantMap param) = 0;
    virtual void performTouchMove(QPointF point, QVariantMap param) = 0 ;
    virtual void performTouchEnd(QPointF point, QVariantMap param) = 0;
    virtual int getHandle() = 0 ;
};

Q_DECLARE_INTERFACE( IHHTransformAction, "com.hht.qtWhiteBoard.IHHTransformAction/1.0" )
Q_DECLARE_METATYPE( IHHTransformAction* )

#endif // IHHTRANSFORMACTION_H
