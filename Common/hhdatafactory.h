#ifndef HHDATAFACTORY_H
#define HHDATAFACTORY_H

#include "lib_FoundationPreAndTeaching.h"

class IHHPresentation;
class LIB_FoundationPreAndTeaching_EXPORT HHDataFactory {
public:
    static IHHPresentation*     getIHHPresentation();
};

#endif // HHDATAFACTORY_H
