#ifndef HHSINGLEAPP_H
#define HHSINGLEAPP_H

#include "hhbaseapp.h"
#include "QtSingleApplication"

class IHHVirtualKeyboard;

class LIB_EXPORT HHSingleApp : public QtSingleApplication, public HHBaseApp
{
    Q_OBJECT

public:
    HHSingleApp( const QString &id, int &argc, char **argv );
    virtual ~HHSingleApp();
    virtual void initialization( IHHFrame *frame );
    bool notify(QObject*obj, QEvent *e);
    void setVirtualKeyboard(IHHVirtualKeyboard *keyboard);

public Q_SLOTS:
    void sltMessageReceived( const QString &message );

private:
    IHHVirtualKeyboard			*m_pVirtualKeyboard;
};

#endif // HHSINGLEAPP_H
