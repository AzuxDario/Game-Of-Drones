#include "light.h"

Light::Light()
{

}

QVector3D Light::GetMatrix()
{
    QMatrix4x4 lightTransformation;
    lightTransformation.rotate(Alpha, 0, 1, 0);
    lightTransformation.rotate(Beta, 1, 0, 0);

    return lightTransformation * QVector3D(0, 1, 1);
}
