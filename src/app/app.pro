#-------------------------------------------------
#
# Project created by QtCreator 2014-11-16T21:07:44
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rosa-cloud
TEMPLATE = app


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    commandrunner.cpp \
    authdialog.cpp \
    spinbox.cpp

HEADERS += \
    mainwindow.h \
    commandrunner.h \
    authdialog.h \
    ../providerdelegate.h \
    provider.h \
    spinbox.h \
    utils.h

FORMS += \
    mainwindow.ui \
    authdialog.ui \
    spinbox.ui

DISTFILES += \
    config.js

RESOURCES += \
    resources.qrc

OTHER_FILES +=

