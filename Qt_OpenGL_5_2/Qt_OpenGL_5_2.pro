#-------------------------------------------------
#
# Project created by QtCreator 2017-03-27T22:45:41
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_OpenGL_5_2
TEMPLATE = app

win32:RC_ICONS += Ikona.ico

SOURCES += main.cpp\
        widget.cpp \
    camera.cpp \
    light.cpp \
    drawableobject.cpp \
    game.cpp \
    lightproperties.cpp \
    EnvGenerator/envgenerator.cpp \
    OBJManager/objmanager.cpp \
    OBJManager/objmodel.cpp \
    OBJLoader/objloader.cpp \
    TexturesManager/texturedata.cpp \
    TexturesManager/texturesmanager.cpp \
    Physics/physics.cpp \
    telemetry.cpp \
    Player/player.cpp \
    KeyboardManager/keyboardmanager.cpp \
    musicplayer.cpp

HEADERS  += widget.h \
    camera.h \
    light.h \
    drawableobject.h \
    game.h \
    lightproperties.h \
    EnvGenerator/envgenerator.h \
    OBJManager/objmanager.h \
    OBJManager/objmodel.h \
    OBJLoader/facedata.h \
    OBJLoader/objloader.h \
    TexturesManager/texturedata.h \
    TexturesManager/texturesmanager.h \
    Physics/physics.h \
    telemetry.h \
    Player/player.h \
    KeyboardManager/keyboardmanager.h \
    musicplayer.h

RESOURCES += \
    resources.qrc

DISTFILES +=
