#ifndef HHBUTTON_H
#define HHBUTTON_H

#include "hhmodeinfodata.h"
#include <QDomElement>

class HHButton
{
public:
    HHButton();
    void readFromXml(QDomElement xml);
    QString getContent();
    int     getID();

private:
    HHModeInfoData      m_writeMode;
    HHModeInfoData      m_mouseMode;
    HHModeInfoData      m_functionMode;

    QString             m_strType;
    int                 m_nId;
    bool                m_bCanCustom;
    bool                m_bAppModeDifferent;
};

#endif // HHBUTTON_H
