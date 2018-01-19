INCLUDEPATH += Engine
DEPENDPATH += Engine
SOURCES += \
        $$PWD/game.cpp \
        $$PWD/Physics/physics.cpp \
		$$PWD/Camera/camera.cpp \
		$$PWD/Light/light.cpp \
		$$PWD/Light/lightproperties.cpp \
		$$PWD/Textures/texturedata.cpp \
		$$PWD/Textures/texturesmanager.cpp \
		$$PWD/Objects/drawableobject.cpp
HEADERS += \
        $$PWD/game.h \
        $$PWD/Physics/physics.h \
		$$PWD/Camera/camera.h \
		$$PWD/Light/light.h \
		$$PWD/Light/lightproperties.h\
		$$PWD/Textures/texturedata.h \
		$$PWD/Textures/texturesmanager.h \
		$$PWD/Objects/drawableobject.h

