#ifndef HHCONTROLLERFACTORY_H
#define HHCONTROLLERFACTORY_H

#include "lib_ControlCenter.h"

class IHHEventCache;
class IHHEventFillter;
class LIB_CONTROLCENTER_EXPORT HHControllerFactory {
public:
    static IHHEventCache*               getHHEventCache();
    static IHHEventFillter*             getHHEventFilter();
};

#endif // HHCONTROLLERFACTORY_H
