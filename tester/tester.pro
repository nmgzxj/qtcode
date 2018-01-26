#-------------------------------------------------
#
# Project created by QtCreator 2017-10-12T18:06:11
#
#-------------------------------------------------

QT       += core gui
QT       += xml sql

RESOURCES += logo.qrc

ICON = logo.icns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tester
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


SOURCES += main.cpp\
        tester.cpp \
    showwidget.cpp \
    about.cpp \
    setup.cpp \
    util.cpp \
    logindialog.cpp \
    progressdlg.cpp \
    gencode.cpp \
    xmlstreamreader.cpp \
    userfile.cpp \
    rule.cpp \
    statisticresult.cpp \
    user.cpp \
    xmlconfigreader.cpp

HEADERS  += tester.h \
    showwidget.h \
    about.h \
    setup.h \
    util.h \
    logindialog.h \
    connection.h \
    progressdlg.h \
    gencode.h \
    xmlstreamreader.h \
    userfile.h \
    rule.h \
    statisticresult.h \
    user.h \
    xmlconfigreader.h

FORMS += \
    logindialog.ui

DISTFILES +=

RESOURCES += \
    logo.qrc
