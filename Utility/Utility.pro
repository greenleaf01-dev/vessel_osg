QT       += core widgets  xml

TARGET = Utility
TEMPLATE = lib


DEFINES += QT_MESSAGELOGCONTEXT

INCLUDEPATH += \
    ImportFile \
    ../Common \
    ./VO/edk/C/include \
    ./

SOURCES += \
    lib_dpi_sacle.cpp\
    hhtextrecognizer.cpp \
    MSRecogEngine.cpp \
    RecogEngine.cpp \
    VORecogEngine.cpp \
    VO/certificates/MyCertificate.c.c \
    VO/edk/C/src/MyScriptEngine-dlHelper.c \
    VO/edk/C/src/MyScriptEngine-strerror.c \
    VO/edk/C/src/MyScriptEngine-strtype.c \
    VO/edk/C/src/MyScriptHWR-strCandidateFlag.c \
    VO/edk/C/src/MyScriptHWR-strTagType.c \
    hhutilityfunctions.cpp \
    hhusbdog.cpp \
    hhsystemtool.cpp \
    RecognitionResults.cpp \
    hotkey/hhbutton.cpp \
    hotkey/hhhotkeyinfo.cpp \
    hotkey/hhmodeinfodata.cpp \
    hotkey/hhsolution.cpp \
    hhclockticket.cpp


HEADERS += \
    ../Common/hhfileconvert.h \
    ../Common/hhtextrecognizer.h \
    ../Common/hhofficeoperator.h \
    ../Common/hhutilityfunctions.h \
    ../Common/Math_RecogEngine.h \
    ../Common/lib_dpi_sacle.h \
    HZRecog.h \
    MSRecogEngine.h \
    RecogEngine.h \
    RecognitionResults.h \
    VORecogEngine.h \
    VO/certificates/MyCertificate.h \
    VO/edk/C/include/c/MyScriptEngine.h \
    VO/edk/C/include/c/MyScriptEngineOptions.h \
    VO/edk/C/include/c/MyScriptHWR.h \
    VO/edk/C/include/c/MyScriptInkSearch.h \
    VO/edk/C/include/c/MyScriptTrainer.h \
    VO/edk/C/include/c/std/stdbool.h \
    VO/edk/C/include/c/std/stddef.h \
    VO/edk/C/include/c/std/stdint.h \
    VO/edk/C/src/MyScriptEngine-strerror.h \
    VO/edk/C/src/MyScriptEngine-strtype.h \
    VO/edk/C/src/MyScriptHWR-strCandidateFlag.h \
    VO/edk/C/src/MyScriptHWR-strTagType.h \
    hhusbdog.h \
    hhsystemtool.h \
    hotkey/hhbutton.h \
    hotkey/hhhotkeyinfo.h \
    hotkey/hhmodeinfodata.h \
    hotkey/hhsolution.h \
    hhclockticket.h


win32:{
    QT       += winextras

    INCLUDEPATH += \
         wtl90_4035/Include \
         ..\QuaZip

    DEFINES += UTILITY_LIBRARY
    DEFINES += _AFXDLL
    QT       += axcontainer
    DISTFILES += \
        VO/edk/C/lib/MyScriptEngine.def
    QMAKE_CFLAGS_RELEASE -= -Zc:strictStrings
    QMAKE_CXXFLAGS_RELEASE -= -Zc:strictStrings
    QMAKE_CFLAGS -= -Zc:strictStrings
    QMAKE_CXXFLAGS -= -Zc:strictStrings

    HEADERS += \
        MSRecogEngine.h \
        hhofficedoc.h   \
        ImportFile/except.h \
        ../Common/hhsysunit.h

    SOURCES += \
        Chem_RecogEngine.cpp\
        Math_RecogEngine.cpp\
        hhofficedoc.cpp \
        hhofficeoperator.cpp \
        hhfileconvert.cpp \
        ImportFile/except.cpp \
        ImportFile/pdflib.cpp   \
        hhsysunit.cpp


    contains(DEFINES, WIN64):{

    }
    else:{
        CONFIG(release, debug|release):{
            DESTDIR = $$PWD/../Bin/Release/X86
            LIBS += $$PWD/ImportFile/pdflib.lib\
                    $$PWD/../Bin/Release/X86/GdiPlus.lib\
                    $$PWD/../Bin/Release/X86/strmiids.lib\
                    $$PWD/../Bin/Release/X86/QuaZip.lib
        }
        else:CONFIG(debug, debug|release):{
            DESTDIR = $$PWD/../Bin/Debug/X86
            LIBS += $$PWD/ImportFile/pdflib.lib\
                    $$PWD/../Bin/Debug/X86/GdiPlus.lib\
                    $$PWD/../Bin/Debug/X86/strmiids.lib\
                    $$PWD/../Bin/Debug/X86/QuaZipd.lib
        }
    }
}

RESOURCES += \
    res.qrc

