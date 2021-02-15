#ifndef _HHRESCOLLECTIONXFACTORY_H_
#define _HHRESCOLLECTIONXFACTORY_H_

#include "lib_dataprovider.h"

class IHHResourceCollectionX;
class LIB_DATAPROVIDER_EXPORT HHResCollectionXFactory {
public:
    static IHHResourceCollectionX *getResCollectionX();

private:
    static IHHResourceCollectionX *m_pResCollectionX;
};

#endif // _HHRESCOLLECTIONXFACTORY_H_
