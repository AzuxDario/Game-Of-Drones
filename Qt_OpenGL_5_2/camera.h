#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4.h>

class Camera
{
public:
    Camera();
    QMatrix4x4 GetMatrix();

    QVector3D Position;
    QVector3D Rotation;

    double Distance;
};

#endif // CAMERA_H
