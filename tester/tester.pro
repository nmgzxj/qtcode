#-------------------------------------------------
#
# Project created by QtCreator 2017-10-12T18:06:11
#
#-------------------------------------------------

QT       += core gui
QT       += xml sql

ICON = logo.icns

#CONFIG += console

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
    xmlconfigreader.cpp \
    treeitem.cpp \
    treemodel.cpp \
    report.cpp \
    setuppages.cpp

HEADERS  += tester.h \
    showwidget.h \
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
    xmlconfigreader.h \
    treeitem.h \
    treemodel.h \
    report.h \
    setuppages.h

FORMS += \
    logindialog.ui \
    report.ui

DISTFILES +=

RESOURCES += \
    logo.qrc
