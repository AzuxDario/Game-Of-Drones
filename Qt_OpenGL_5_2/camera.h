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
    QVector3D cameraDirection;
    bool reset = false;

public:
    Camera();
    QMatrix4x4 GetMatrix();
    void update(QVector3D target, QVector3D direction);

    QVector3D getDistance() noexcept {return distance;}
    void setDistance(QVector3D value) noexcept {distance = value;}
    QVector3D getDirection() noexcept {return cameraDirection;}
    void setDirection(QVector3D value) noexcept {cameraDirection = value; reset = false;}
    void addToDirection(int x = 0, int y = 0, int z = 0) noexcept {cameraDirection.setX(cameraDirection.x()+x);cameraDirection.setY(cameraDirection.y()+y);cameraDirection.setZ(cameraDirection.z()+z);reset = false;}
    void resetCamera()noexcept{ reset = true;}
};

#endif // CAMERA_H
