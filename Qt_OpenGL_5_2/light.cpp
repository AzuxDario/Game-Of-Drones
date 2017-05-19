#include "light.h"

Light::Light()
{

}

QMatrix4x4 Light::GetMatrix()
{
    QMatrix4x4 mMatrix;
    mMatrix.setToIdentity();
    mMatrix.translate(Position);
    mMatrix.rotate(Rotation.x(), 1, 0, 0);
    mMatrix.rotate(Rotation.y(), 0, 1, 0);
    mMatrix.rotate(Rotation.z(), 0, 0, 1);
    mMatrix.scale(0.1);

    return mMatrix;
}
