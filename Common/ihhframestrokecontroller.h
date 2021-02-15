#ifndef INTERFACE_STROKE_H
#define INTERFACE_STROKE_H

#include <QObject>
#include <QtPlugin>
#include <QPointF>
#include <QDebug>

#include <vector>
using namespace std;

class QString;
class QJsonValue;
class QVariant;
class QJsonObject;
class IHHCanvas;

class IHHFrameStrokeController;

// Stroke 控制
class IHHFrameStrokeController{
public:
    ~IHHFrameStrokeController() {}

    virtual QObject *getObject() = 0;

    virtual void setCurrentIHHCanvas(IHHCanvas *pIHHCanvas) = 0;

    virtual void setAllPenData( QJsonObject jsonBrush ) = 0;
    virtual QJsonObject getModuleData( QString strID ) = 0;

    // add by fanhongjie 2018-02-07 start
    // 切换为硬笔
    virtual int switchStrokeSmoothPen(const QVariantMap &info) = 0;
    // 切换为智能笔
    virtual int switchGeometryFreehandPen(const QVariantMap &info) = 0;
    // 切换为荧光笔
    virtual int switchFluorescentPen(const QVariantMap &info) = 0;
    // 切换为激光笔
    virtual int switchStrokeLaserPen(const QVariantMap &info) = 0;
    // 切换为软笔
    virtual int switchStrokeBrushPen(const QVariantMap &info) = 0;
    // 切换为手势笔
    virtual int switchStrokeGesturePen(const QVariantMap &info) = 0;
    // 切换为手写识别笔
    virtual int switchTextParaCenterPen(const QVariantMap &info) = 0;
    // 切换为纹理笔
    virtual int switchStrokeTexturePen(const QVariantMap &info) = 0;
    // 切换为竹笔
    virtual int switchStrokePAIPen(const QVariantMap &info) = 0;
    // 切换为图章笔
    virtual int switchStrokeStampPen(const QVariantMap &info) = 0;

    // 切换画笔模式
    virtual int switchStrokeModule(const QString &sItemModule) = 0;
    // 设置笔ModuleData
    virtual int setStrokeModuleData(const QString &sItemModule,
                                   const QJsonObject &info) = 0;
    // 获取笔ModuleData
    virtual int getStrokeModuleData(const QString &sItemModule,
                                   QJsonObject &info) = 0;
    // 获取所有笔ModuleData
    virtual int getStrokesModuleData(QJsonObject &info) = 0;

    // 获取当前笔和ModuleData
    virtual int getCurStrokeModuleData(QString &sItemModule,
                                      QJsonObject &info) = 0;
    // 获取当前笔
    virtual QString getCurrentStrokePen() = 0;

    // add by fanhongjie 2018-02-07 end

    // 初始化笔Module数据
    virtual void initStrokeModuleDataInfo(const QJsonObject &info) = 0;

};

Q_DECLARE_INTERFACE( IHHFrameStrokeController, "com.hht.qtWhiteBoard.IHHFrameStrokeController/1.0" )
Q_DECLARE_METATYPE( IHHFrameStrokeController* )

#endif
