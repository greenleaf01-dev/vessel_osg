#ifndef HHSCENARIOSINGLEAPP_H
#define HHSCENARIOSINGLEAPP_H

#include "hhscenariobaseapp.h"
#include "QtSingleApplication"

class IHHVirtualKeyboard;
class LIB_EXPORT HHScenarioSingleApp : public QtSingleApplication, public HHScenarioBaseApp
{
    Q_OBJECT
public:
    HHScenarioSingleApp( const QString &id, int &argc, char **argv );
    virtual ~HHScenarioSingleApp();
    virtual void initialization(IHHScenarioManager *scenarioManager);// IHHFrame *frame
    bool notify(QObject*obj, QEvent *e);
    void setVirtualKeyboard(IHHVirtualKeyboard *keyboard);

public Q_SLOTS:
    void sltMessageReceived( const QString &message );

private:
    IHHVirtualKeyboard			*m_pVirtualKeyboard;
};

#endif // HHSCENARIOSINGLEAPP_H
