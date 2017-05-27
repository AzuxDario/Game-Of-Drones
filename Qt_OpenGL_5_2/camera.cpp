#include "camera.h"

Camera::Camera()
{
    distance = 25.5;
}

QMatrix4x4 Camera::GetMatrix()
{
    QMatrix4x4 vMatrix, cameraTransformation;

    cameraTransformation.translate(position.x(), position.y(), position.z());
    cameraTransformation.rotate(rotation.x(), 1, 0, 0);
    cameraTransformation.rotate(rotation.y(), 0, 1, 0);
    cameraTransformation.rotate(rotation.z(), 0, 0, 1);

    QVector3D cameraPosition = cameraTransformation * QVector3D(0, 0, distance);
    QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);

    vMatrix.lookAt(cameraPosition, position, cameraUpDirection);
    return vMatrix;
}
