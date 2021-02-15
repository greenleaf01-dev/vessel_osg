#ifndef HHPRESENTATIONPREANDTEACHING_H
#define HHPRESENTATIONPREANDTEACHING_H

#include "../Common/hhpresentation.h"
#include "lib_FoundationPreAndTeaching.h"

class HHSlide;
class IHHModel;
class HHPresentationPreandteaching : public HHPresentation
{
    Q_OBJECT
    Q_INTERFACES( IHHPresentation )

public:
	HHPresentationPreandteaching() {};
	virtual ~HHPresentationPreandteaching() {};

	virtual HHSlide* createSlide(HHPresentation *pHHPresentation);

    // added for Pre and teaching
    void importPPT( QString fileName );
    void exportIWBFile( QString filePath );
    void importIWB( QString fileName );

public Q_SLOTS:
    void importPPTSuccess( QJsonObject&, IHHModel* );
    void importIWBSuccess( QJsonObject&, IHHModel* );

public:
    //Add by Zhaojianbiao -- 20171117 start
    //主题模板数据处理
private:

    //QString useThemeInfo(HHSlide *pSlide, QJsonObject &param);
     //end
};
#endif // HHPRESENTATION_H
