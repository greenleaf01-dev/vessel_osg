#ifndef HHBASEAPP_H
#define HHBASEAPP_H

#include "lib_global.h"
#include <QJsonObject>

class IHHFrame;
class IHHApplication;
class IHHFrame;

class LIB_EXPORT HHBaseApp
{
public:
    HHBaseApp();
    virtual ~HHBaseApp();
    virtual void initialization( IHHFrame *frame );
    IHHApplication* getApplication();

protected:
    IHHApplication              *m_pApp;

public:
    QJsonObject                 m_params;
    QJsonObject     processArguments( QString param );
};

#endif // HHBASEAPP_H
