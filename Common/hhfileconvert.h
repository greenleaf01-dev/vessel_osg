#ifndef HHFILECONVERT_H
#define HHFILECONVERT_H

#include <QProcess>
#include <QVector>
#include "utility_global.h"

class UTILITYSHARED_EXPORT HHFileConvert : public QProcess {
    Q_OBJECT
public:
    HHFileConvert( QString strPath );

Q_SIGNALS:
    void sigFinishedConvert( QString source, QString dest );

public Q_SLOTS:
    void sltFinished( int exitCode );

public:
    void convertImage( QString source, QString dest );
    void convertVideo( QString source, QString dest );

private:
    QString             m_source;
    QString             m_dest;
    QString             m_path;
};

#endif // HHFILECONVERT_H
