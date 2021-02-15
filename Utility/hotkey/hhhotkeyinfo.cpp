#include "hhhotkeyinfo.h"
#include <QtWidgets/QApplication>
#include <QFile>

HHHotKeyInfo::HHHotKeyInfo()
{
    m_vecSolutions.clear();
    m_xmlFilePath = "hotkey/UnifiedDevice.xml";
    m_currentSolution = HHSolution();

    readFromXml();
}

int HHHotKeyInfo::initCurrentSolution(int nSolutionID)
{
    HHSolution solution;
    if(m_vecSolutions.isEmpty())
        return m_currentSolution.m_nID;

    int num = m_vecSolutions.size();
    for(int i=0; i<num; i++)
    {
        solution = m_vecSolutions[i];
        if(nSolutionID == solution.m_nID)
        {
            break;
        }
    }
    m_currentSolution = solution;
    return m_currentSolution.m_nID;
}

void HHHotKeyInfo::readFromXml()
{
    QDomDocument doc("doc");
    QFile xmlFile( ":/" +  m_xmlFilePath );
//    QFile xmlFile(m_xmlFilePath);

    if(!xmlFile.exists())
        qDebug()<<"xml file no exists"<<xmlFile.fileName();
    if(!xmlFile.open(QIODevice::ReadOnly))
    {
        qDebug()<<"xml file open failed!";
        return;
    }

    if(!doc.setContent(&xmlFile))
    {
        qDebug()<<"xml file setcontent QDomDocument failed!";
        xmlFile.close();
        return;
    }
    xmlFile.close();

    QDomElement docRoot = doc.documentElement();//<Root>
    QDomNode node = docRoot.firstChild();
    while (!node.isNull())
    {
        QDomElement element = node.toElement();
        if(!element.isNull())
        {
            if(element.tagName() == "Solutions")//<Solutions>
            {
                readSolutions(element);
            }
        }

        node = node.nextSibling();
    }

}

void HHHotKeyInfo::readSolutions(QDomElement element)
{
    m_vecSolutions.clear();
    if(element.isNull() || "Solutions" != element.tagName())
        return;

    QDomNode node = element.firstChild();
    while (!node.isNull())
    {
        QDomElement eSolution = node.toElement();
        if(!eSolution.isNull() && eSolution.tagName() == "Solution")
        {
            HHSolution solution;
            solution.readFromXML(eSolution);
            m_vecSolutions.append(solution);
        }

        node = node.nextSibling();
    }
}

QString HHHotKeyInfo::getOneBtnContent(int nSolutionID, int nBtnID)
{
    QString btnContent("");
//    HHSolution slt;
    int sltID = initCurrentSolution(nSolutionID);
    if(sltID == nSolutionID)
    {
        btnContent = m_currentSolution.getBtnContent(nBtnID);
    }

    return btnContent;
}

int HHHotKeyInfo::getCurrentSolutionID()
{
    return m_currentSolution.m_nID;
}

QString HHHotKeyInfo::getCurrentBtnContent(int nBtnID)
{
    return m_currentSolution.getBtnContent(nBtnID);
}
