#include "camera.h"

Camera::Camera()
{

}

QMatrix4x4 Camera::GetMatrix()
{
    QMatrix4x4 vMatrix, cameraTransformation;

    cameraTransformation.translate(position.x(), position.y(), position.z());
    cameraTransformation.rotate(rotation.x(), 1, 0, 0);
    cameraTransformation.rotate(rotation.y(), 0, 1, 0);
    cameraTransformation.rotate(rotation.z(), 0, 0, 1);

    QVector3D cameraPosition = cameraTransformation * QVector3D(3, 0, 4);
    QVector3D cameraUpDirection = QVector3D(1, 0, 0);

    vMatrix.lookAt(cameraPosition, position + QVector3D(2, 0, 0), cameraUpDirection);
    return vMatrix;
}
