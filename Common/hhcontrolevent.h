#ifndef HHCONTROLEVENT_H
#define HHCONTROLEVENT_H

#include <QEvent>
#include <QVariantMap>

class HHControlEvent : public QEvent
{
public:
    inline HHControlEvent(QEvent::Type type,const QVariantMap & param) : QEvent(type){m_param = param;}
    inline ~HHControlEvent(){}
    inline QVariantMap getParam(){return m_param;}
    //inline void setParam(QVariantMap param){m_param = param;}
private:
    QVariantMap m_param;
};

#endif
