#ifndef HHCLOCKTICKET_H
#define HHCLOCKTICKET_H
#include <QObject>
#include <QScopedPointer>
#include "utility_global.h"

class HHClockTicketPrivate;

class UTILITYSHARED_EXPORT HHClockTicket :public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HHClockTicket)
public:
    HHClockTicket(const QString& msg = QString());
     HHClockTicket(const QString& function, qint64 line);
    ~HHClockTicket();
protected:
    QScopedPointer<HHClockTicketPrivate> d_ptr;
};

#endif // HHCLOCKTICKET_H
