#pragma once

#include <QObject>
#include <QJsonObject>

class IHHActivityTempletInfo{
public:
    ~IHHActivityTempletInfo() {}

    virtual QObject *getObject() = 0;

    virtual QJsonObject getTempletInfo() = 0;
    virtual void setTempletInfo(const QJsonObject &info) = 0;

    virtual QString getTempletThumbnail() = 0;
    virtual void setTempletThumbnail(const QString &sPath) = 0;

    virtual QString getTempletName() = 0;
    virtual void setTempletName(const QString &sName) = 0;

    virtual int getIndex() = 0;
    virtual void setIndex(int nIndex) = 0;

    virtual QString getTempletType() = 0;
    virtual void setTempletType(const QString &sType) = 0;

    virtual QString getBackground() = 0;
    virtual void setBackground(const QString &sImg) = 0;

    // 获取容器信息
    virtual QJsonObject getContentInfo() = 0;
    virtual void setContentInfo(const QJsonObject &info) = 0;

    virtual QString getContentPath() = 0;
    virtual void setContentPath(const QString &sPath) = 0;

    virtual QString getContentHotPath() = 0;
    virtual void setContentHotPath(const QString &sPath) = 0;

    virtual int getContentFontSize() = 0;
    virtual void setContentFontSize(const int nSize) = 0;

    virtual QString getContentFontFamily() = 0;
    virtual void setContentFontFamily(const QString &fontFamily) = 0;

    virtual QString getContentFontColor() = 0;
    virtual void setContentFontColor(const QString &sColor) = 0;

    virtual QString getContentFontAlign() = 0;
    virtual void setContentFontAlign(const QString &sAlign) = 0;

    virtual void setHotoffset(QString& offset)= 0;
    virtual QString getHotoffset() = 0;

    // 获取材料信息
    virtual QJsonObject getMaterialInfo() = 0;
    virtual void setMaterialInfo(const QJsonObject &info) = 0;

    virtual QString getMaterialPath() = 0;
    virtual void setMaterialPath(const QString &sPath) = 0;

    virtual int getMaterialFontSize() = 0;
    virtual void setMaterialFontSize(const int nSize) = 0;

    virtual QString getMaterialFontFamily() = 0;
    virtual void setMaterialFontFamily(const QString &sFontFamily) = 0;

    virtual QString getMaterialFontColor() = 0;
    virtual void setMaterialFontColor(const QString &sColor) = 0;

    virtual QString getMaterialFontAlign() = 0;
    virtual void setMaterialFontAlign(const QString &sAlign) = 0;
};
Q_DECLARE_INTERFACE( IHHActivityTempletInfo,
                     "com.hht.qtWhiteBoard.IHHActivityTempletInfo/1.0" )
Q_DECLARE_METATYPE( IHHActivityTempletInfo* )
