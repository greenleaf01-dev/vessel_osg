#include "hhsolution.h"

HHSolution::HHSolution()
{
    m_nID = -1;
    m_bSymmetry = true;
    m_nLeftStart = 0;
    m_nRightStart = 50;
    m_nCustomBtnNum = 0;
    m_nBtnNumPerRowInEditerDlg = 4;

    m_vecBtns.clear();
    m_vecCustomBtnIndexes.clear();

}

void HHSolution::readFromXML(QDomElement xml)
{
    m_vecBtns.clear();
    if(xml.isNull() || xml.tagName() != "Solution")
    {
        qDebug()<<"HHSolution::readFromXML----------1";
        return;
    }

    m_nID = xml.attribute("ID","-1").toInt();
//    qDebug()<<"HHSolution::readFromXml-----id:"<<m_nID;
    m_bSymmetry = xml.attribute("Symmetry", "0") == "1";
    m_nLeftStart = xml.attribute("LeftSideStart", "0").toInt();
    m_nRightStart = xml.attribute("RightSideStart", "50").toInt();
    m_nCustomBtnNum = xml.attribute("CustomizeBtnNumber", "0").toInt();
    m_nBtnNumPerRowInEditerDlg = xml.attribute("BtnNumPerRowInEditorDlg", "4").toInt();
    if(0 == m_nCustomBtnNum)
    {
        m_vecCustomBtnIndexes.clear();
    }
    else{
//        qDebug()<<"solution id :"<<m_nID<<" m_vecCustomBtnIndexes:";
        QString cbis = xml.attribute("CustomizeBtnIndex","");
        QStringList list = cbis.split(",");
        for(int i=0; i<m_nCustomBtnNum; i++)
        {
            m_vecCustomBtnIndexes.append(list.at(i).toInt());
//            qDebug()<<m_vecCustomBtnIndexes[i];
        }
    }

    QDomNode node = xml.firstChild();
    while (!node.isNull())
    {
        QDomElement eButton = node.toElement();
        if(!eButton.isNull() && eButton.tagName() == "Button")
        {
            HHButton btn ;
            btn.readFromXml(eButton);
            m_vecBtns.append(btn);
        }
        node = node.nextSibling();
    }


//    qDebug()<<"HHSolution::readFromXml-----id:"<<m_nID<<"end";
}

QString HHSolution::getBtnContent(int mBtnID)
{
    QString content("");
    int num = m_vecBtns.size();

    for(int i=0; i<num; i++)
    {
        HHButton btn = m_vecBtns[i];
        if(mBtnID == btn.getID())
        {
            content = btn.getContent();
            return content;
        }
    }

    return content;
}

