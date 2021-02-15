#ifndef IHHMINDMAPHELPER_H
#define IHHMINDMAPHELPER_H

#include <QObject>

class IHHPrimitiveItem;
class IHHMindMapHelper
{
public:
    virtual QObject* getObject() = 0;
    virtual bool isNeedCopy() = 0;
    virtual bool isNeedCut() = 0;
    virtual bool isPasteMindMap(QString str) = 0;

    virtual void copyItem() = 0;
    virtual void cutItem() = 0;
    virtual void pastItem(QString str) = 0;

    virtual bool isNeedShortCut()=0;
    virtual void processShortCut(QString keyType) =0;

};
Q_DECLARE_INTERFACE(IHHMindMapHelper, "com.hht.qtWhiteBoard.IHHMindMapHelper/1.0")
Q_DECLARE_METATYPE(IHHMindMapHelper*)

#endif
