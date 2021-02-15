#ifndef IHHFRAMEMEDIACONTROLLER_H
#define IHHFRAMEMEDIACONTROLLER_H

#include <QObject>
class IHHPrimitiveItem;

// 界面媒体控制
class IHHFrameMediaController{
public:
    virtual ~IHHFrameMediaController(){}
    virtual QObject *getObject() = 0;

    virtual void insertResource(QString strFile, bool bIsFlash) = 0;

    // 粘贴item
    virtual void pasteItem(QVector<IHHPrimitiveItem*> &item_ver) = 0;

    // 从文件插入图片
    virtual void insertImgForFile() = 0;
    // 从文件插入视频
    virtual void insertVideoForFile() = 0;
    // 从文件音频图片
    virtual void insertAudioForFile() = 0;
    // 从文件文档图片
    virtual void insertDocForFile() = 0;
    //通知授课模式
    virtual void notifyTeachingMode(const QString &sModule) = 0;

};
Q_DECLARE_INTERFACE( IHHFrameMediaController, "com.hht.qtWhiteBoard.IHHFrameMediaController/1.0" )
Q_DECLARE_METATYPE( IHHFrameMediaController* )

#endif // IHHFRAMEMEDIACONTROLLER_H
