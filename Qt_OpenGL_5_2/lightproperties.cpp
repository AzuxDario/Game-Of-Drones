#include "lightproperties.h"

LightProperties::LightProperties()
{
    ambientColor.setRgb(32,32,32);
    diffuseColor.setRgb(128, 128, 128);
    specularColor.setRgb(255, 255, 255);
    ambientReflection = 1;
    diffuseReflection = 1;
    specularReflection = 1;
    shininess = 100;
}

