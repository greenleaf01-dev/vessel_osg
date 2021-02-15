#ifndef HHDATAPROVIDERFACTORY_H
#define HHDATAPROVIDERFACTORY_H

#include "lib_dataprovider.h"

class IHHDataProvider;
class LIB_DATAPROVIDER_EXPORT HHDataProviderFactory {
public:
    static IHHDataProvider*               getLocalFileDataProvider();

private:
    static IHHDataProvider          *m_pLocalFileDataProvider;
};

#endif // HHDATAPROVIDERFACTORY_H
