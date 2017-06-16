#include "camera.h"

Camera::Camera()
{
    cameraPosition = QVector3D(10,10,10);
    distance = QVector3D(5,0,-20);
    upVector = QVector3D(1,0,0);
    cameraDirection = QVector3D(0,0,0);
}

QMatrix4x4 Camera::GetMatrix()
{
    QMatrix4x4 vMatrix;

    vMatrix.lookAt(cameraPosition, targetPosition, upVector);
    return vMatrix;
}

void Camera::update(QVector3D target, QVector3D direction)
{
    targetPosition = target;
    QMatrix4x4 cameraTransformation, upTrans;

    if (reset)
    {
        cameraDirection.setX(std::min(std::max(cameraDirection.x() / 25, (float)-180.0),(float)180.0));
        cameraDirection.setY(std::min(std::max(cameraDirection.y() / 25, (float)-180.0),(float)180.0));
        cameraDirection.setZ(std::min(std::max(cameraDirection.y() / 25, (float)-180.0),(float)180.0));
    }

    cameraTransformation.translate(target.x(), target.y(), target.z());
    cameraTransformation.rotate(direction.x() + cameraDirection.x(), 1, 0, 0);
    cameraTransformation.rotate(direction.y() + cameraDirection.y(), 0, 1, 0);
    cameraTransformation.rotate(direction.z() + cameraDirection.z(), 0, 0, 1);

    upTrans.rotate(direction.x(), 1, 0, 0);
    upTrans.rotate(direction.y(), 0, 1, 0);
    upTrans.rotate(direction.z(), 0, 0, 1);

    upVector = upTrans * QVector3D(1,0,0);

    QVector3D cameraEye = cameraTransformation * distance ;
    QVector3D cameraMove = cameraEye - cameraPosition;
    float dist = cameraMove.length() + 20;
    cameraMove *= std::min(dist / 100, (float)0.99);

    cameraPosition += cameraMove;
}
