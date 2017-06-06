#include "camera.h"

Camera::Camera()
{
    cameraPosition = QVector3D(10,10,10);
    distance = QVector3D(20,0,-50);
    upVector = QVector3D(1,0,0);
}

QMatrix4x4 Camera::GetMatrix()
{
    QMatrix4x4 vMatrix;

    QVector3D cameraUpDirection = QVector3D(1, 0, 0);

    vMatrix.lookAt(cameraPosition, targetPosition, upVector);
    return vMatrix;
}

void Camera::update(QVector3D target, QVector3D direction)
{
    targetPosition = target;
    QMatrix4x4 cameraTransformation, upTransformation;

    cameraTransformation.translate(target.x(), target.y(), target.z());
    cameraTransformation.rotate(direction.x(), 1, 0, 0);
    cameraTransformation.rotate(direction.y(), 0, 1, 0);
    cameraTransformation.rotate(direction.z(), 0, 0, 1);

    upTransformation.rotate(direction.x(), 1, 0, 0);
    upTransformation.rotate(direction.y(), 0, 1, 0);
    upTransformation.rotate(direction.z(), 0, 0, 1);

    upVector = upTransformation * QVector3D(1,0,0);

    QVector3D cameraEye = cameraTransformation * distance;
    QVector3D cameraMove = cameraEye - cameraPosition;
    float dist = cameraMove.length() + 20;
    cameraMove *= std::min(dist / 100, (float)0.99);

    cameraPosition += cameraMove;
}
