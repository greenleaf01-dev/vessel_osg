//手写识别笔
#ifndef HHTEXTPARACENTERSTROKEACTION_H
#define HHTEXTPARACENTERSTROKEACTION_H

#include "lib_hhcontrolleraction_global.h"
#include "HHBaseCustomAction.h"

class IHHFrameStrokeController;

class HHCONTROLLERACTIONSHARED_EXPORT HHTextParaCenterStrokeAction : public HHBaseCustomAction
{
    Q_OBJECT
    Q_PROPERTY(QColor Color READ color WRITE setColor)
    Q_PROPERTY(bool Bold READ bold WRITE setBold)
    Q_PROPERTY(bool UnderLine READ underLine WRITE setUnderLine)
    Q_PROPERTY(bool Italic READ italic WRITE setItalic)
    Q_PROPERTY(QString Align READ align WRITE setAlign)
    Q_PROPERTY(int HWPixelSize READ pixelSize WRITE setHWPixelSize)
    Q_PROPERTY(QString HWTime READ time WRITE setHWTime)
    Q_PROPERTY(QString Font READ font WRITE setFont)
    Q_PROPERTY(QString Lang READ lang WRITE setLang NOTIFY signalLangPropertyChang)

public:
    explicit HHTextParaCenterStrokeAction(
            IHHFrameStrokeController *pIHHController,
            QObject *parent = nullptr);

    QColor color();
    void setColor(const QColor &color);

    bool bold();
    void setBold(bool bold);

    bool underLine();
    void setUnderLine(bool bUnderLine);

    bool italic();
    void setItalic(bool bItalic);

    QString align();
    void setAlign(const QString &sAlign);

    int pixelSize();
    void setHWPixelSize(int nSize);

    QString time();
    void setHWTime(const QString &sTime);

    QString font();
    void setFont(const QString &sFont);

    QString lang();
    void setLang(const QString &sLang);

    virtual void setPropertyInfo(const QJsonObject &info);
    virtual QJsonObject propertyInfo();

    virtual void setCanvas(IHHCanvas *pIHHCanvas);

    virtual void triggerAction(const QJsonObject &info);


signals:
    void signalLangPropertyChang(const QString &sLang);

public slots:
private slots:
    void slotTriggered(bool);

private:
    void loadDefaultInfo();

private:
    IHHFrameStrokeController                *m_pIHHController;
    QColor                                   m_color;
    bool                                     m_bBold;
    bool                                     m_bUnderLine;
    bool                                     m_bItalic;
    QString                                  m_sAlign;
    int                                      m_nHWPixelSize;
    QString                                  m_sHWTime;
    QString                                  m_sFont;
    QString                                  m_sLang;
};

#endif // HHTEXTPARACENTERSTROKEACTION_H
