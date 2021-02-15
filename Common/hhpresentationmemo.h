#ifndef HHPRESENTATIONMEMO_H
#define HHPRESENTATIONMEMO_H

#include "lib_FoundationPreAndTeaching.h"
#include "hhpresentation.h"

class LIB_FoundationPreAndTeaching_EXPORT HHPresentationMemo : public HHPresentation
{
    Q_OBJECT
    Q_INTERFACES( IHHPresentation )

public:
    HHPresentationMemo();
    virtual ~HHPresentationMemo();

public:
    virtual void fileNew( QVariantMap param );
    virtual IHHSlide* addSlide( IHHSlide *refSlide, QJsonObject param );

};

#endif // HHPRESENTATIONMEMO_H
