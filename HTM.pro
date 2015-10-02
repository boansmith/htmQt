#-------------------------------------------------
#
# Project created by QtCreator 2015-05-30T17:35:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HTM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cell.cpp \
    dendritesegment.cpp \
    column.cpp \
    synapse.cpp \
    inputelement.cpp \
    Organiser.cpp \
    Watcher.cpp \
    htmGlobal.cpp

HEADERS  += mainwindow.h \
    cell.h \
    dendritesegment.h \
    column.h \
    synapse.h \
    inputelement.h \
    Organiser.h \
    Watcher.h \
    htmGlobal.h

FORMS    += mainwindow.ui
