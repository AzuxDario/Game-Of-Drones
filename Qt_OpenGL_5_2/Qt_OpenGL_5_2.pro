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
    movableobject.cpp \
    game.cpp \
    lightproperties.cpp \
    EnvGenerator/envgenerator.cpp \
    OBJManager/objmanager.cpp \
    OBJManager/objmodel.cpp \
    OBJLoader/objloader.cpp

HEADERS  += widget.h \
    camera.h \
    light.h \
    drawableobject.h \
    movableobject.h \
    game.h \
    lightproperties.h \
    EnvGenerator/envgenerator.h \
    OBJManager/objmanager.h \
    OBJManager/objmodel.h \
    OBJLoader/facedata.h \
    OBJLoader/objloader.h

RESOURCES += \
    resources.qrc

DISTFILES +=
