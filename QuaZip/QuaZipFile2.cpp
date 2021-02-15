#include "QuaZipFile2.h"

QuaZipFile2::QuaZipFile2(const QString &zipName, const QString &fileName, QuaZip::CaseSensitivity cs, QObject *parent)
    :QuaZipFile(zipName,fileName,cs,parent)
{ 
}

bool QuaZipFile2::isSequential() const
{
	return false;
}

