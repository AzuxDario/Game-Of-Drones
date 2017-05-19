#ifndef LIGHT_H
#define LIGHT_H

#include <QMatrix4x4.h>

class Light
{
public:
    Light();
    QMatrix4x4 GetMatrix();

    QVector3D Position;
    QVector3D Rotation;
};

#endif // LIGHT_H
