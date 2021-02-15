#ifndef HHMODEINFODATA_H
#define HHMODEINFODATA_H

#include <QString>
#include <QDebug>

class HHModeInfoData
{
public:
    HHModeInfoData();

public:
    QString     m_type;
    QString     m_content;
    QString     m_toolTip;
    QString     m_shortCut;
};

#endif // HHMODEINFODATA_H
