#ifndef _HHIMAGECOLLECTIONXFACTORY_H_
#define _HHIMAGECOLLECTIONXFACTORY_H_

#include "lib_dataprovider.h"

class IHHImageCollectionX;
class LIB_DATAPROVIDER_EXPORT HHImageCollectionXFactory {
public:
    static IHHImageCollectionX *getImageCollectionX();

private:
    static IHHImageCollectionX *m_pImageCollectionX;
};

#endif // _HHIMAGECOLLECTIONXFACTORY_H_

