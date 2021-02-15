#include "hhclockticket.h"
#include <QDateTime>
#include <QString>
#include <QDebug>
class HHClockTicketPrivate
{
public:
    QString msg;
    qint64  beginTick;
	HHClockTicketPrivate(const QString& msg_)
    {
        msg = msg_;
        beginTick =QDateTime::currentMSecsSinceEpoch();
    }
};

HHClockTicket::HHClockTicket(const QString &msg_)
    :d_ptr(new HHClockTicketPrivate(msg_))
{
}

HHClockTicket::HHClockTicket(const QString &function, qint64 line)
  :d_ptr(new HHClockTicketPrivate(QStringLiteral("%1::%2").arg(function).arg(line) ))
{
}

HHClockTicket::~HHClockTicket()
{
    Q_D(HHClockTicket);
//#ifdef QT_DEBUG
    qDebug() << "HHClockTicket: " << d->msg +"  : " << QDateTime::currentMSecsSinceEpoch() - d->beginTick;
//#endif
}
