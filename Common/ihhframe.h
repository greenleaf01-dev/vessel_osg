#ifndef IHHFRAME_H
#define IHHFRAME_H

#include <QObject>
class IHHCanvas;
class IHHFramePreController;
class IHHFrameMediaController;
class IHHFrameDeviceController;
class IHHFrameGeneralToolController;
class IHHFrameCanvasController;
class IHHFrameItemController;
class IHHFrameSlideController;
class IHHIceWhiteBoardManger;
class IHHFrameTextBoxController;
class IHHFrameUserActionController;
class IHHCloudManager;
class IHHConfigManager;
class IHHFrameDeletePixelController;
class IHHFrameSubjectController;
class IHHFrameStrokeController;
class IHHFrameShapeController;
class IHHFrameMindMapController;
class IHHActionManager;

class IHHFrame {
public:
    virtual ~IHHFrame(){}
    virtual QObject* getObject() = 0;
    virtual void setParameters( QString type, QVariant value ) = 0;// 设置参数
    virtual QVariant getParameters( QString type ) = 0;
    virtual IHHCanvas* getIHHCanvas() = 0;

    // 是否忙
    virtual bool isBusy() = 0;
    // 播放课件
    virtual bool play(int nPage) = 0;
    // 停止课件播放
    virtual bool stop() = 0;

    // 切换模式
    virtual void switchMode(QString sMode) = 0;

    // 获取文档控制
    virtual IHHFramePreController *getPreController() = 0;

    // 获取媒体控制
    virtual IHHFrameMediaController *getMediaController() = 0;

    // 获取设备控制
    virtual IHHFrameDeviceController *getDeviceController() = 0;

    // 获取通用工具控制
    virtual IHHFrameGeneralToolController *getGeneralToolController() = 0;

    // 获取Canvas控制
    virtual IHHFrameCanvasController *getCanvasController() = 0;

    // 获取Item控制
    virtual IHHFrameItemController *getItemController() = 0;

    // 获取Slide控制
    virtual IHHFrameSlideController *getSlideController() = 0;

    // 获取Ice控制
    virtual IHHIceWhiteBoardManger *getIceWhiteBoardManger() = 0;

    // 获取TextBox控制
    virtual IHHFrameTextBoxController *getTexBoxController() = 0;

    // 获取用户行为统计控制
    virtual IHHFrameUserActionController *getUserActionController() = 0;

    virtual IHHCloudManager *getCloudManger() = 0;

    virtual IHHConfigManager *getConfigManger() = 0;

    virtual IHHFrameDeletePixelController *getDeletePixelController() = 0;

    virtual IHHFrameSubjectController *getSubjectController() = 0;
    // 获取笔控制
    virtual IHHFrameStrokeController *getStrokeController() = 0;
    //获取形状设置
    virtual IHHFrameShapeController *getShapeController() = 0;

    // 获取思维导图控制
    virtual IHHFrameMindMapController *getMindMapController() = 0;

    // 获取中心界面
    virtual QWidget *getCentralWidget() = 0;

    // 获取ActionManager
    virtual IHHActionManager *getActionManager() = 0;

};
Q_DECLARE_INTERFACE( IHHFrame, "com.hht.qtWhiteBoard.IHHFrame/1.0" )
Q_DECLARE_METATYPE( IHHFrame* )

#endif // IHHFRAME_H
