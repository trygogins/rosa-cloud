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
    src/main.cpp \
    src/mainwindow.cpp \
    src/commandrunner.cpp \
    src/filedownloader.cpp \
    src/authdialog.cpp \
    src/providermodel.cpp

HEADERS += \
    src/mainwindow.h \
    src/commandrunner.h \
    src/filedownloader.h \
    src/authdialog.h \
    src/providermodel.h

FORMS += \
    src/mainwindow.ui \
    src/authdialog.ui

OTHER_FILES += \
    README.md
