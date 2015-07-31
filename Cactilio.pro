#-------------------------------------------------
#
# Project created by QtCreator 2015-07-30T19:20:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cactilio
TEMPLATE = app

RC_FILE = cactilio.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    encounter.cpp \
    names.cpp

HEADERS  += mainwindow.h \
    encounter.h \
    names.h \
    parameters.h

FORMS    += mainwindow.ui

RESOURCES += \
    cactilio.qrc


