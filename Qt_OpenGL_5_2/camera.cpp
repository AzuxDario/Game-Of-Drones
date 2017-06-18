#include "camera.h"

Camera::Camera()
{
    cameraPosition = QVector3D(0,0,-10);
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
    QMatrix4x4 trans, upTrans;
    transM = QMatrix4x4();


    if (reset)
    {
        cameraDirection.setX(std::min(std::max(cameraDirection.x() / 25, (float)-180.0),(float)180.0));
        cameraDirection.setY(std::min(std::max(cameraDirection.y() / 25, (float)-180.0),(float)180.0));
        cameraDirection.setZ(std::min(std::max(cameraDirection.y() / 25, (float)-180.0),(float)180.0));
    }

    trans.translate(target.x(), target.y(), target.z());
    transM.rotate(direction.x() + cameraDirection.x(), 1, 0, 0);
    transM.rotate(direction.y() + cameraDirection.y(), 0, 1, 0);
    transM.rotate(direction.z() + cameraDirection.z(), 0, 0, 1);

    trans *= transM;

    upTrans.rotate(direction.x(), 1, 0, 0);
    upTrans.rotate(direction.y(), 0, 1, 0);
    upTrans.rotate(direction.z(), 0, 0, 1);

    upVector = upTrans * QVector3D(1,0,0);

    QVector3D cameraEye = trans * distance;
    QVector3D cameraMove = cameraEye - cameraPosition;
    //Powoduję chorobę kamery, nie mam litości jej tak mordować
    //qDebug() << "----------------------------";
    //qDebug() << "Before: " << cameraMove.x() << " " << cameraMove.y() << " " << cameraMove.z();
    //float dist = cameraMove.length() + 20;
    //cameraMove *= std::min(dist / 100, (float)0.99);
    //qDebug() << "After: " << cameraMove.x() << " " << cameraMove.y() << " " << cameraMove.z();
    //qDebug() << "Dist: " << dist;


    cameraPosition = cameraEye;
}
