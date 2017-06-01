#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4.h>
#include <cmath>

class Camera
{
private:
    QVector3D targetPosition;
    QVector3D cameraPosition;
    QVector3D upVector;
    QVector3D distance;

public:
    Camera();
    QMatrix4x4 GetMatrix();
    void update(QVector3D target, QVector3D direction);

    QVector3D getDistance() noexcept {return distance;}
    void setDistance(QVector3D value) noexcept {distance = value;}
};

#endif // CAMERA_H
