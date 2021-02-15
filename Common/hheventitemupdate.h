#ifndef HHEVENTITEMUPDATE_H
#define HHEVENTITEMUPDATE_H

#include <QEvent>
#include <QRectF>

class HHEventItemUpdate : public QEvent
{
public:
    inline HHEventItemUpdate(QEvent::Type type,const QRectF & param) : QEvent(type){m_param = param;}
    inline ~HHEventItemUpdate(){}
    inline QRectF getParam(){return m_param;}
private:
    QRectF m_param;
};

#endif
