#pragma once
#include <QObject>
#include <QWidget>

class IHHThumbnailView{
public:
     ~IHHThumbnailView(){}
    virtual QWidget *           getWidget() = 0;
    virtual void                init(const QVariantMap &params) = 0;
};
Q_DECLARE_INTERFACE( IHHThumbnailView, "com.hht.qtWhiteBoard.IHHThumbnailView/1.0" )
Q_DECLARE_METATYPE( IHHThumbnailView* )
