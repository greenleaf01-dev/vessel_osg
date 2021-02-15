#pragma once

#include <QObject>

class QWidget;

class IHHCustomBaseUI{
public:
     ~IHHCustomBaseUI(){}
    virtual QObject * getObject() = 0;

    virtual QVariant getParameters(const QString &sType) = 0;

    virtual void init(const QVariantMap &params) = 0;
    virtual void retranslateUi() = 0;

    virtual void setAutoHide(bool bHide) = 0;
    virtual bool isAutoHided() = 0;

    virtual void setMoveableFlg(bool bMoveFlg) = 0;
    virtual bool isMoveAbled() = 0;
    virtual void setMoveHeight(int nHeight) = 0;

    virtual void addWidget(QWidget *pItemUI) = 0;

    virtual void setDropShadowEffectColor(const QColor &color) = 0;
    virtual void setBorderFrameStyle(const QString &styleSheet) = 0;

    virtual void setIconFilePath(const QString &sFilePath) = 0;
    virtual QString getIconFilePath() = 0;

    virtual double getScaleFactory() = 0;
};

Q_DECLARE_INTERFACE( IHHCustomBaseUI, "com.hht.qtWhiteBoard.IHHCustomBaseUI/1.0" )
Q_DECLARE_METATYPE( IHHCustomBaseUI* )
