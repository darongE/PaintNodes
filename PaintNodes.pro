QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PaintNodes
TEMPLATE = app

DESTDIR = ../bin

SOURCES += main.cpp \
    UScene3D.cpp \
    mainwindow.cpp

HEADERS  += \
    UScene3D.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    paintNodes.qrc
