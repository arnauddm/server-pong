#-------------------------------------------------
#
# Project created by QtCreator 2016-11-06T17:49:47
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console


TARGET = serveurPingPong
TEMPLATE = app


SOURCES += main.cpp \
    serverwindow.cpp \
    paddle.cpp

HEADERS  += \
    serverwindow.hpp \
    paddle.hpp

FORMS    +=
