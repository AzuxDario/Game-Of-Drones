#ifndef LIGHT_H
#define LIGHT_H

#include <QMatrix4x4.h>

class Light
{
public:
    Light();
    QVector3D GetMatrix();

    double Alpha;
    double Beta;
};

#endif // LIGHT_H
