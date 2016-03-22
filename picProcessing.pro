#-------------------------------------------------
#
# Project created by QtCreator 2015-12-21T16:25:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = picProcessing
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    BMP.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    BMP.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui
