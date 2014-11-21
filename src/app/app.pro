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
    filedownloader.cpp \
    authdialog.cpp \
    providermodel.cpp

HEADERS += \
    mainwindow.h \
    commandrunner.h \
    filedownloader.h \
    authdialog.h \
    providermodel.h

FORMS += \
    mainwindow.ui \
    authdialog.ui

