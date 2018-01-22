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
include(Entity/Entity.pri)

SOURCES += main.cpp\
        widget.cpp \
    EnvGenerator/envgenerator.cpp \
    telemetry.cpp \
    Player/player.cpp \
    timeconverter.cpp

HEADERS  += widget.h \
    EnvGenerator/envgenerator.h \
    telemetry.h \
    Player/player.h \
    timeconverter.h

RESOURCES += \
    resources.qrc

DISTFILES +=
