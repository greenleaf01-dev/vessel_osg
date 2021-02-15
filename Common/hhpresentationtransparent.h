#ifndef HHPRESENTATIONTRANSPARENT_H
#define HHPRESENTATIONTRANSPARENT_H

#include "lib_FoundationTransparent.h"
#include "hhpresentation.h"

class LIB_FoundationTransparent_EXPORT HHPresentationTransparent : public HHPresentation
{
    Q_OBJECT
    Q_INTERFACES( IHHPresentation )

public:
    HHPresentationTransparent();
    virtual ~HHPresentationTransparent();

public:
    virtual void fileNew( QVariantMap param );
    virtual IHHSlide* addSlide( IHHSlide *refSlide, QJsonObject param );
};

#endif // HHPRESENTATIONTRANSPARENT_H
