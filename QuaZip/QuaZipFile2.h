#ifndef QUAZIPFILE2_H
#define QUAZIPFILE2_H
#include "quazipfile.h"

class QUAZIP_EXPORT QuaZipFile2 : public QuaZipFile
{
public:
    QuaZipFile2(const QString& zipName, const QString& fileName,
                QuaZip::CaseSensitivity cs =QuaZip::csDefault, QObject *parent =NULL);
public:
    virtual bool isSequential() const;
};

#endif // QUAZIPFILE2_H
