#include "lightproperties.h"

LightProperties::LightProperties()
{
    ambientColor = QColor(32, 32, 32);
    diffuseColor = QColor(128, 128, 128);
    specularColor = QColor(255, 255, 255);
    ambientReflection = 1;
    diffuseReflection = 1;
    specularReflection = 1;
    shininess = 100;
}

