INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
HEADERS += \
        $$PWD/crypt.h \
        $$PWD/ioapi.h \
        $$PWD/JlCompress.h \
        $$PWD/quaadler32.h \
        $$PWD/quachecksum32.h \
        $$PWD/quacrc32.h \
        $$PWD/quagzipfile.h \
        $$PWD/quaziodevice.h \
        $$PWD/quazipdir.h \
        $$PWD/quazipfile.h \
        $$PWD/quazipfileinfo.h \
        $$PWD/quazip_global.h \
        $$PWD/quazip.h \
        $$PWD/quazipnewinfo.h \
        $$PWD/unzip.h \
        $$PWD/zip.h \
    $$PWD/zlib-1.2.3/crc32.h \
    $$PWD/zlib-1.2.3/deflate.h \
    $$PWD/zlib-1.2.3/inffast.h \
    $$PWD/zlib-1.2.3/inffixed.h \
    $$PWD/zlib-1.2.3/inflate.h \
    $$PWD/zlib-1.2.3/inftrees.h \
    $$PWD/zlib-1.2.3/trees.h \
    $$PWD/zlib-1.2.3/zconf.h \
    $$PWD/zlib-1.2.3/zconf.in.h \
    $$PWD/zlib-1.2.3/zlib.h \
    $$PWD/zlib-1.2.3/zutil.h \
    $$PWD/QuaZipFile2.h

SOURCES += $$PWD/qioapi.cpp \
           $$PWD/JlCompress.cpp \
           $$PWD/quaadler32.cpp \
           $$PWD/quacrc32.cpp \
           $$PWD/quagzipfile.cpp \
           $$PWD/quaziodevice.cpp \
           $$PWD/quazip.cpp \
           $$PWD/quazipdir.cpp \
           $$PWD/quazipfile.cpp \
           $$PWD/quazipfileinfo.cpp \
           $$PWD/quazipnewinfo.cpp \
           $$PWD/unzip.c \
           $$PWD/zip.c \
    $$PWD/zlib-1.2.3/adler32.c \
    $$PWD/zlib-1.2.3/compress.c \
    $$PWD/zlib-1.2.3/crc32.c \
    $$PWD/zlib-1.2.3/deflate.c \
    $$PWD/zlib-1.2.3/gzio.c \
    $$PWD/zlib-1.2.3/infback.c \
    $$PWD/zlib-1.2.3/inffast.c \
    $$PWD/zlib-1.2.3/inflate.c \
    $$PWD/zlib-1.2.3/inftrees.c \
    $$PWD/zlib-1.2.3/minigzip.c \
    $$PWD/zlib-1.2.3/trees.c \
    $$PWD/zlib-1.2.3/uncompr.c \
    $$PWD/zlib-1.2.3/zutil.c \
    $$PWD/QuaZipFile2.cpp

DISTFILES += \
    $$PWD/../../zlib-1.2.3/zlib.3
