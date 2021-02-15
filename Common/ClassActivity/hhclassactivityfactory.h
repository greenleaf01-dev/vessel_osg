#ifndef HHCLASSACTIVITYFACTORY_H
#define HHCLASSACTIVITYFACTORY_H

#include "hhclassactivity_global.h"

class IHHClassActivityPrepareController;
class IHHClassActivityTeachingController;
class IHHCanvas;
class QObject;

class HHCLASSACTIVITYSHARED_EXPORT HHClassActivityFactory
{
public:
    static IHHClassActivityPrepareController *createPrepareActivityController(
            IHHCanvas *pIHHCanvas, QObject *parent = nullptr);

    static IHHClassActivityTeachingController *createTeachingActivityController(
            QObject *parent = nullptr);

private:
    static IHHClassActivityPrepareController            *m_pIHHPreActivityCtl;
    static IHHClassActivityTeachingController           *m_pIHHTeachingActivityCtl;

};

#endif // HHCLASSACTIVITYFACTORY_H
