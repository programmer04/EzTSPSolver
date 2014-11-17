#-------------------------------------------------
#
# Project created by QtCreator 2014-11-08T20:39:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EzTSPSolver_1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graph.cpp \
    delegate.cpp

HEADERS  += mainwindow.h \
    graph.h \
    delegate.h

FORMS    += mainwindow.ui
