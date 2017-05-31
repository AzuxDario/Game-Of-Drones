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

    QVector3D cameraMove = (cameraTransformation * QVector3D(0, 0, -distance)) - cameraPosition;
    float dist = cameraMove.length() + 20;
    cameraMove *= std::min(dist / 5, (float)0.99);
    QVector3D cameraUpDirection = QVector3D(1, 0, 0);

    cameraPosition += cameraMove;

    vMatrix.lookAt(cameraPosition, position, cameraUpDirection);
    return vMatrix;
}
