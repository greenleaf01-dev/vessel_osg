#ifndef DOCUMENTTOOL_GLOBAL_H
#define DOCUMENTTOOL_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LIB_STATIC_UTILITY
    #define UTILITYSHARED_EXPORT
#else
    /**
     * When building a DLL with MSVC, QUAZIP_BUILD must be defined.
     * qglobal.h takes care of defining Q_DECL_* correctly for msvc/gcc.
     */
    #if defined(UTILITY_LIBRARY)
        #define UTILITYSHARED_EXPORT Q_DECL_EXPORT
    #else
        #define UTILITYSHARED_EXPORT Q_DECL_IMPORT
    #endif
#endif // LIB_STATIC_GESTURE

#include <vector>
#include <QString>
typedef std::vector<std::vector<std::pair<float, float> > >  TInputStrokes;
typedef std::vector<std::pair<float, float> > TInputStroke;
typedef std::pair<float, float> TInputPoint;
class TCandidate
{
public:
	TCandidate() :first(-1), last(-1){}
	int first;
	int last;
	QString text;
};

typedef std::vector<TCandidate> TCandidates;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef unsigned long       DWORD;

#define MAKELANGID(p, s)       ((((WORD  )(s)) << 10) | (WORD  )(p))
#define PRIMARYLANGID(lgid)    ((WORD  )(lgid) & 0x3ff)
#define SUBLANGID(lgid)        ((WORD  )(lgid) >> 10)

#define HWR_RESULT_SPLIT QString("$split$")

#define RE_VERIFY_RETURN0(condition)			if (!(condition)) return
#define RE_VERIFY_RETURN(retValue, condition)	if (!(condition)) return retValue
#define RE_VERIFY_EXECUTE(condition, fun)		if (condition) fun
enum eRecogEngineType{ eMSType, eFranceType, eDefaultType };
#endif // UTILITY_GLOBAL_H
