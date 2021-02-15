#pragma once

#include <QList>
//特效
struct AnimationInfo
{
    QString strItemID;      //Item标识

    int     iIndex;         //序列索引
    QString strID;          //动画标识
    QString strName;        //特效名称
    QString strElemName;    //元素名称

    QString strTrigSorc;    //触发源
    QString strTrigTime;      //触发时机（0下一页，1同上一动画同时 2上一动画结束）
    QString strAnimaType;     //动画类型（0入，1动作，2出）
    bool    bIsSelected = false;    //是否被选中
};

//触发源Item
struct TriggerSourceItem
{

    AnimationInfo animt;
    QList<AnimationInfo> lstAnimationItem;
};
//根据触发源分类
struct TriggerSource
{
   QString strTriggerSource;
   QString strID;
   int     playIndex = 0;
   QList<TriggerSourceItem> lstSourceItem;
};

//QList<TriggerSource> lst;
