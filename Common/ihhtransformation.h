#ifndef IHHTRANSFORMATION_H
#define IHHTRANSFORMATION_H

#include <QObject>
#include <QDomDocument>

class IHHApplication;
class IHHTransformation {
public:
    virtual ~IHHTransformation(){}
    virtual void initialization( IHHApplication *app ) = 0;
    /**
     *  转换文档json格式数据从.hht文件的xml格式数据中
     * @param source XML 文档对应的xml
     * @param param Object 目前只有文件路径，其他参数待定。
     * @return Object
     */
    virtual QJsonObject getPresJSONFromHHT( QDomElement source, QJsonObject param ) = 0;
    /**
     * 转换页面json格式数据从.hht文件的xml格式数据中
     * @param source XML 页面对应的xml
     * @param param Object 目前只有文件路径，其他参数待定。
     * @return Object
     */
    virtual QJsonObject getSlideJSONFromHHT( QDomElement source, QJsonObject param ) = 0;
    /**
     * 转换对象json格式数据从.hht文件的xml格式数据中
     * @param source XML 对象对应的xml
     * @param param Object 目前只有文件路径，其他参数待定。
     * @return Object
     */
    virtual QJsonObject getItemJSONFromHHT( QDomElement source, QJsonObject param ) = 0;

    virtual QDomDocument getPresHHTXFromJSON( QDomDocument source, QJsonObject param ) = 0;
    virtual QDomDocument getSlideHHTXFromJSON( QDomDocument source, QJsonObject param ) = 0;
    virtual QDomElement getItemHHTXFromJSON( QDomElement source, QJsonObject param ) = 0;
    virtual QJsonObject getPresJSONFromHHTX( QDomElement source, QJsonObject param ) = 0;
    virtual QJsonObject getSlideJSONFromHHTX( QDomElement source, QJsonObject param ) = 0;
    virtual QJsonObject getItemJSONFromHHTX( QDomElement source, QJsonObject param ) = 0;

    virtual QVariantMap getPresJSONFromPPT( QString fileName) = 0;
    virtual QVariantMap getSlideJSONFromPPT( void* pSlide, QString strDir ) = 0;
    virtual QJsonObject getItemJSONFromPPT( void* pItem, QString strDir ) = 0;

    virtual QDomDocument getPresIWBFromJSON( QDomDocument source, QJsonObject object ) = 0;
    virtual QDomElement getSlideIWBFromJSON( QDomDocument& source, QJsonObject object ) = 0;
    virtual QDomElement getItemIWBFromJSON( QDomDocument& source, QJsonObject object ) = 0;

    virtual QJsonObject getPresJSONFromIWB( QDomElement source, QJsonObject object ) = 0;
    virtual QJsonObject getSlideJSONFromIWB( QDomElement root, QDomElement source, QJsonObject object ) = 0;
    virtual QJsonObject getItemJSONFromIWB( QDomElement source, QJsonObject object ) = 0;
};

Q_DECLARE_INTERFACE( IHHTransformation, "com.hht.qtWhiteBoard.IHHTransformation/1.0" )
Q_DECLARE_METATYPE( IHHTransformation* )

#endif // IHHTRANSFORMATION_H
