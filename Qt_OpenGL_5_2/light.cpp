#include "light.h"

Light::Light()
{

}

QMatrix4x4 Light::GetMatrix()
{
    QMatrix4x4 mMatrix;
    mMatrix.setToIdentity();
    mMatrix.translate(position);
    mMatrix.rotate(rotation.x(), 1, 0, 0);
    mMatrix.rotate(rotation.y(), 0, 1, 0);
    mMatrix.rotate(rotation.z(), 0, 0, 1);
    mMatrix.scale(0.1);

    return mMatrix;
}
