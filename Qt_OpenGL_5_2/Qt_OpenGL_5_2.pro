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

include(Engine/Engine.pri)
include(Sound/Sound.pri)
include(Input/Input.pri)

SOURCES += main.cpp\
        widget.cpp \
    EnvGenerator/envgenerator.cpp \
    OBJManager/objmanager.cpp \
    OBJManager/objmodel.cpp \
    OBJLoader/objloader.cpp \
    telemetry.cpp \
    Player/player.cpp \
    computerplayer.cpp \
    timeconverter.cpp

HEADERS  += widget.h \
    EnvGenerator/envgenerator.h \
    OBJManager/objmanager.h \
    OBJManager/objmodel.h \
    OBJLoader/facedata.h \
    OBJLoader/objloader.h \
    telemetry.h \
    Player/player.h \
    computerplayer.h \
    timeconverter.h

RESOURCES += \
    resources.qrc

DISTFILES +=
