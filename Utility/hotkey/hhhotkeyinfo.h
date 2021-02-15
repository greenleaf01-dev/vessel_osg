#ifndef HHHOTKEYINFO_H
#define HHHOTKEYINFO_H

#include "hhsolution.h"

class HHHotKeyInfo
{
public:
    HHHotKeyInfo();
    int initCurrentSolution(int nSolutionID);
    QString getOneBtnContent(int nSolutionID, int nBtnID);
    int getCurrentSolutionID();
    QString getCurrentBtnContent(int nBtnID);

private:
    void readFromXml();
    void readSolutions(QDomElement element);

private:
    QVector<HHSolution>     m_vecSolutions;
    QString                 m_xmlFilePath;
    HHSolution              m_currentSolution;
};

#endif // HHHOTKEYINFO_H
