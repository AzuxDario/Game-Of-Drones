INCLUDEPATH += Engine
DEPENDPATH += Engine
SOURCES += \
        $$PWD/game.cpp
HEADERS += \
        $$PWD/game.h

include(Camera/Camera.pri)
include(Light/Light.pri)
include(Physics/Physics.pri)
include(Textures/Textures.pri)
include(Objects/Objects.pri)