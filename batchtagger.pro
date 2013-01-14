#-------------------------------------------------
#
# Project created by QtCreator 2013-01-12T15:56:07
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = batchtagger
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
INCLUDEPATH = /usr/include
LIBS += -lkdecore -ltag
SOURCES += main.cpp
