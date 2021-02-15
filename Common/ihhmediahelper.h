#ifndef IHHMEDIAHELPER_H
#define IHHMEDIAHELPER_H

#include <QObject>

class IHHPrimitiveItem;
class IHHActionsManager;
class IHHMediaHelper
{
public:
    virtual QObject* getObject() = 0;

    virtual void createVideoItem(QString, QVariantMap) = 0;
    virtual void createAudioItem(QString, QVariantMap) = 0;
    virtual void createImageItem(QString, QVariantMap = QVariantMap()) = 0;
    virtual void createDocItem(QString, QVariantMap) = 0;
	virtual void createFlashItem(QString, bool, bool) = 0;

	virtual void setLastItemPosIndex(int) = 0;
    virtual void setActionsManage(IHHActionsManager*) = 0;

	virtual void setMediaItemUI(IHHPrimitiveItem*) = 0;
	virtual void switchModule(bool) = 0;
    virtual void presentionChanged() = 0;
    virtual void hideImageView() = 0;

	virtual void setParentWidget(QWidget*) = 0;
};
Q_DECLARE_INTERFACE(IHHMediaHelper, "com.hht.qtWhiteBoard.IHHMediaHelper/1.0")
Q_DECLARE_METATYPE(IHHMediaHelper*)

#endif // IHHMEDIAHELPER_H
