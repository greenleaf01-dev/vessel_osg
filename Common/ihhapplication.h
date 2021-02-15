#ifndef IHHAPPLICATION_H
#define IHHAPPLICATION_H

#include <QObject>

class QApplication;
class IHHFrame;
class IHHPlugins;
class IHHModelFactory;
class IHHTransformation;
class IHHGeneralToolFactory;
class IHHApplication {
public:
    virtual ~IHHApplication(){}
    virtual void initialization( QApplication *app, IHHFrame *frame ) = 0;
    virtual void setParameters( QString type, QVariant value ) = 0;// 设置参数
    virtual QVariant getParameters( QString type ) = 0;// 得到参数
    virtual IHHPlugins* getPlugins() = 0;// 插件的集合。设置插件这一个层次，主要是为了接收界面、数据等发过来的事件，使得处理可以分开层次，
    virtual IHHModelFactory* getModelFactory() = 0;
    virtual IHHTransformation* getTrans() = 0;
    virtual IHHFrame* getFrame() = 0;
    virtual IHHGeneralToolFactory* getGeneralToolFactory() = 0;

    virtual void switchLauguage(const QString & newLanguage) = 0;

};
Q_DECLARE_INTERFACE( IHHApplication, "com.hht.qtWhiteBoard.IHHApplication/1.0" )
Q_DECLARE_METATYPE( IHHApplication* )

#endif // IHHAPPLICATION_H
