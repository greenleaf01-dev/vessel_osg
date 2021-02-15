#ifndef HHSOLUTION_H
#define HHSOLUTION_H

#include <QVector>
#include "hhbutton.h"

class HHSolution
{
public:
    HHSolution();
    void readFromXML(QDomElement xml);
    QString getBtnContent(int mBtnID);

public:
    int     m_nID;
    bool    m_bSymmetry;//是否左右对称
    int     m_nLeftStart;//左边按钮开始序号
    int     m_nRightStart;//右边按钮开始序号
    int     m_nCustomBtnNum;//可定制按钮个数
    int     m_nBtnNumPerRowInEditerDlg;//编辑框每行按键个数

    QVector<int>        m_vecCustomBtnIndexes; //可定制按钮的ID
    QVector<HHButton>   m_vecBtns;//方案中按钮信息集合
};

#endif // HHSOLUTION_H
