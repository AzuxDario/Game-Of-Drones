#include "camera.h"

Camera::Camera()
{
    Distance = 2.5;
}

QMatrix4x4 Camera::GetMatrix()
{
    QMatrix4x4 vMatrix, cameraTransformation;

    cameraTransformation.translate(Position.x(), Position.y(), Position.z());
    cameraTransformation.rotate(Rotation.x(), 1, 0, 0);
    cameraTransformation.rotate(Rotation.y(), 0, 1, 0);
    cameraTransformation.rotate(Rotation.z(), 0, 0, 1);

    QVector3D cameraPosition = cameraTransformation * QVector3D(0, 0, Distance);
    QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);

    vMatrix.lookAt(cameraPosition, QVector3D(0, 0, 0), cameraUpDirection);
    return vMatrix;
}
