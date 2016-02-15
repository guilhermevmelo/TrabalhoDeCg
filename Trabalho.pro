#-------------------------------------------------
#
# Project created by QtCreator 2016-02-13T12:03:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Trabalho
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    vector.cpp \
    ray.cpp \
    camera.cpp \
    color.cpp \
    light.cpp \
    sphere.cpp \
    object.cpp \
    plane.cpp \
    triangle.cpp \
    cube.cpp \
    congresso.cpp \
    objreader.cpp

HEADERS  += mainwindow.h \
    vector.h \
    ray.h \
    camera.h \
    color.h \
    light.h \
    sphere.h \
    object.h \
    plane.h \
    triangle.h \
    cube.h \
    congresso.h \
    objreader.h

FORMS    += mainwindow.ui
