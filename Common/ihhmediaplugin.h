#ifndef IHHMEDIAPLUGIN_H
#define IHHMEDIAPLUGIN_H

#include <QObject>

class IHHPrimitiveItem;
class IHHResourceCollectionX;

class IHHMediaPlugin
{
public:
    virtual IHHPrimitiveItem *createVideoItem(QRectF rtPlayer, QString sFilePath, IHHResourceCollectionX* conllect, qint64 iDuration) = 0;
    virtual IHHPrimitiveItem *createAudioItem(QRectF rtPlayer, QString sFilePath, IHHResourceCollectionX* conllect, qint64 iDuration) = 0;
    virtual IHHPrimitiveItem *createFlashItem(QRectF rtPosSize, QString sFilePath, IHHResourceCollectionX* conllect, bool isSubjectFlash, bool isSimulationFlash) = 0;
    virtual IHHPrimitiveItem *createImageItem(QRectF rtPosSize, QString sFilePath, IHHResourceCollectionX* conllect, QVariantMap vmImgData) = 0;
    virtual IHHPrimitiveItem *createDocItem(QRectF rtPosSize, double dPPIScale, QString sFilePath, IHHResourceCollectionX* conllect)  =0;

};
Q_DECLARE_INTERFACE(IHHMediaPlugin, "com.hht.qtWhiteBoard.IHHMediaPlugin/1.0")
Q_DECLARE_METATYPE(IHHMediaPlugin*)

#endif // IHHMEDIAPLUGIN_H
