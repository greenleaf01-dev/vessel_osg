#include "hhbutton.h"

HHButton::HHButton()
{
    m_writeMode = HHModeInfoData();
    m_mouseMode = HHModeInfoData();
    m_functionMode = HHModeInfoData();

    m_nId = -1;
    m_strType = QString("AppOnly");
    m_bAppModeDifferent = false;
    m_bCanCustom = false;
}

void HHButton::readFromXml(QDomElement xml)
{
    if(xml.isNull() || xml.tagName() != "Button")
        return;

    m_nId = xml.attribute("ID", "-1").toInt();
//    qDebug()<<"HHButton::readFromXml-----id:"<<m_nId;
    m_strType = xml.attribute("Type", "AppOnly");
    m_bAppModeDifferent = xml.attribute("AppModeDifferent", "0") == "1";
    m_bCanCustom = xml.attribute("CanCustomize", "0") == "1";

    QString strType(""),strContent(""),strTooltip(""),strST("");
    QDomNode node = xml.firstChild();
    while(!node.isNull())
    {
        QDomElement eMode = node.toElement();
        if(!eMode.isNull())
        {
            strType = eMode.attribute("Type", "");
            strContent = eMode.attribute("Content", "");
            strTooltip = eMode.attribute("Tooltip", "");
            strST = eMode.attribute("ShortCut", "");

            QString eModeName = eMode.tagName();
            if("WriteMode" == eModeName)
            {
                m_writeMode.m_content = strContent;
                m_writeMode.m_shortCut = strST;
                m_writeMode.m_toolTip = strTooltip;
                m_writeMode.m_type = strType;

                if(!m_bAppModeDifferent)//不区分
                {
                    m_mouseMode = m_writeMode;
                }
            }
            else if("MouseMode" == eModeName)
            {
                m_mouseMode.m_content = strContent;
                m_mouseMode.m_shortCut = strST;
                m_mouseMode.m_toolTip = strTooltip;
                m_mouseMode.m_type = strType;

                if(!m_bAppModeDifferent)
                {
                    m_writeMode = m_mouseMode;
                }
            }
            else if("Function" == eModeName)
            {
                m_functionMode.m_content = strContent;
                m_functionMode.m_shortCut = strST;
                m_functionMode.m_toolTip = strTooltip;
                m_functionMode.m_type = strType;
            }
        }

        node = node.nextSibling();
    }

//    qDebug()<<"HHButton::readFromXml-----id:"<<m_nId<<"end";
}

QString HHButton::getContent()
{
    return m_writeMode.m_content;
}

int HHButton::getID()
{
    return m_nId;
}

