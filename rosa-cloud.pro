#-------------------------------------------------
#
# Project created by QtCreator 2014-11-16T21:07:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rosa-cloud
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    authdialog.cpp

HEADERS  += mainwindow.h \
    authdialog.h

FORMS    += mainwindow.ui \
    authdialog.ui

OTHER_FILES += \
    README.md
