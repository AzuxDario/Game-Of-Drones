#ifndef LIGHT_H
#define LIGHT_H

#include <QMatrix4x4.h>

class Light
{
private:

    QVector3D position;
    QVector3D rotation;

public:

    Light();
    QMatrix4x4 GetMatrix();

    QVector3D getPosition() noexcept {return position;}
    QVector3D getRotation() noexcept {return rotation;}
    void setPosition(QVector3D value) noexcept {position = value;}
    void setRotation(QVector3D value) noexcept {rotation = value;}
};

#endif // LIGHT_H
