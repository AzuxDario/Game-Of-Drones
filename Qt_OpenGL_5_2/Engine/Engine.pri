INCLUDEPATH += Engine
DEPENDPATH += Engine
SOURCES += \
        $$PWD/game.cpp \
		$$PWD/Textures/texturedata.cpp \
		$$PWD/Textures/texturesmanager.cpp \
		$$PWD/Objects/drawableobject.cpp \
		$$PWD/Objects/ObjectsLoader/OBJLoader.cpp \
		$$PWD/Objects/ObjectsManager/objmanager.cpp \
		$$PWD/Objects/ObjectsManager/objmodel.cpp
HEADERS += \
        $$PWD/game.h \
		$$PWD/Textures/texturedata.h \
		$$PWD/Textures/texturesmanager.h \
		$$PWD/Objects/drawableobject.h \
		$$PWD/Objects/ObjectsLoader/OBJLoader.h \
		$$PWD/Objects/ObjectsLoader/FaceData.h \
		$$PWD/Objects/ObjectsManager/objmanager.h \
		$$PWD/Objects/ObjectsManager/objmodel.h

include(Camera/Camera.pri)
include(Light/Light.pri)
include(Physics/Physics.pri)