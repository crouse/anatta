#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T12:58:20
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network
QT       += xlsx

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = anatta
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    pics.qrc
