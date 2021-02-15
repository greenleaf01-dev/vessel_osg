#-------------------------------------------------
#
# Project created by QtCreator 2020-11-08T14:59:41
#
#-------------------------------------------------

QT       += widgets
QT       += widgets core gui
QT       += core gui
QT       += opengl
QT       += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vessel_viewer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        viewerwidget.cpp \
        osgspheresegment.cpp

HEADERS += \
        mainwindow.h \
        viewerwidget.h \
        osgspheresegment.cpp

FORMS += \
        mainwindow.ui

INCLUDEPATH += \
    ../Common \
    ..\OsgFile\include\
    ..\OsgFile\bin\
    ..\OsgFile\include\
    ./3dtoolDialog


HEADERS	+= \
    3dtoolDialog/hh3dtoolswidget.h \
    3dtoolDialog/hhpanelwithnail.h \
    3dtoolDialog/hh3dtoolspanel.h \
    3dtoolDialog/src_toolbar/hhtoolbarbuttonpanel.h

SOURCES	+= \
    3dtoolDialog/hh3dtoolswidget.cpp \
    3dtoolDialog/hhpanelwithnail.cpp \
    3dtoolDialog/hh3dtoolspanel.cpp \
    3dtoolDialog/src_toolbar/hhtoolbarbuttonpanel.cpp

win32:{
    contains(DEFINES, WIN64):{
    }
    else:{
        CONFIG(release, debug|release):{
            DESTDIR = $$PWD/../Bin/Release/X86
            LIBS += opengl32.lib
            LIBS += glu32.lib
            LIBS += User32.lib
            LIBS += gdi32.lib
            LIBS += advapi32.lib
            LIBS += Qt5OpenGL.lib
            LIBS += opengl32.lib
            LIBS += $$PWD/../OsgFile/lib/osgQt.lib
            LIBS += $$PWD/../OsgFile/lib/osgWidget.lib
            LIBS += $$PWD/../OsgFile/lib/osgViewer.lib
            LIBS += $$PWD/../OsgFile/lib/osgGA.lib
            LIBS += $$PWD/../OsgFile/lib/osgText.lib
            LIBS += $$PWD/../OsgFile/lib/osgDB.lib
            LIBS += $$PWD/../OsgFile/lib/osgUtil.lib
            LIBS += $$PWD/../OsgFile/lib/osgText.lib
            LIBS += $$PWD/../OsgFile/lib/osg.lib
            LIBS += $$PWD/../OsgFile/lib/OpenThreads.lib
            LIBS += $$PWD/../OsgFile/lib/osgParticle.lib
            LIBS += $$PWD/../OsgFile/lib/osgSim.lib
        }

        else:CONFIG(debug, debug|release):{
            DESTDIR = $$PWD/../Bin/Debug/X86
            LIBS += opengl32.lib
            LIBS += glu32.lib
            LIBS += User32.lib
            LIBS += gdi32.lib
            LIBS += advapi32.lib
            LIBS += Qt5OpenGLd.lib
            LIBS += opengl32.lib

            LIBS += $$PWD/../OsgFile/lib/osgQtd.lib
            LIBS += $$PWD/../OsgFile/lib/osgWidgetd.lib
            LIBS += $$PWD/../OsgFile/lib/osgViewerd.lib
            LIBS += $$PWD/../OsgFile/lib/osgGAd.lib
            LIBS += $$PWD/../OsgFile/lib/osgTextd.lib
            LIBS += $$PWD/../OsgFile/lib/osgDBd.lib
            LIBS += $$PWD/../OsgFile/lib/osgUtild.lib
            LIBS += $$PWD/../OsgFile/lib/osgTextd.lib
            LIBS += $$PWD/../OsgFile/lib/osgd.lib
            LIBS += $$PWD/../OsgFile/lib/OpenThreadsd.lib
            LIBS += $$PWD/../OsgFile/lib/osgParticled.lib
            LIBS += $$PWD/../OsgFile/lib/osgSimd.lib
           }
    }
}
