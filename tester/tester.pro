#-------------------------------------------------
#
# Project created by QtCreator 2017-10-12T18:06:11
#
#-------------------------------------------------

QT       += core gui
QT       += xml sql

#ICON = logo.ico

#CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tester
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

#DEFINES += QT_NO_WARNING_OUTPUT
DEFINES += QT_NO_DEBUG_OUTPUT

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += _FILE_OFFSET_BITS=64 _LARGE_FILE

SOURCES += main.cpp\
        tester.cpp \
    showwidget.cpp \
    setup.cpp \
    logindialog.cpp \
    userfile.cpp \
    statisticresult.cpp \
    user.cpp \
    xmlconfigreader.cpp \
    report.cpp \
    setuppages.cpp \
    userdb.cpp

HEADERS  += tester.h \
    showwidget.h \
    setup.h \
    logindialog.h \
    userfile.h \
    user.h \
    xmlconfigreader.h \
    treemodel.h \
    report.h \
    setuppages.h \
    userdb.h

FORMS += \
    logindialog.ui \
    report.ui

DISTFILES +=



RESOURCES += \
    logo.qrc
win32-g++ {
    LIBS += -lopengl32
}
win32-msvc*{
    LIBS += opengl32.lib
}
