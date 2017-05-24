#-------------------------------------------------
#
# Project created by QtCreator 2017-03-27T22:45:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_OpenGL_5_2
TEMPLATE = app

win32:RC_ICONS += Ikona.ico

SOURCES += main.cpp\
        widget.cpp \
    camera.cpp \
    light.cpp \
    drawableobject.cpp \
    OBJLoader/OBJLoader.cpp \
    movableobject.cpp \
    game.cpp \
    lightproperties.cpp

HEADERS  += widget.h \
    camera.h \
    light.h \
    drawableobject.h \
    OBJLoader/FaceData.h \
    OBJLoader/OBJLoader.h \
    movableobject.h \
    game.h \
    lightproperties.h

RESOURCES += \
    resources.qrc

DISTFILES +=
