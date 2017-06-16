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
    QMatrix4x4 getMatrix();

    QVector3D getPosition() noexcept {return position;}
    QVector3D getRotation() noexcept {return rotation;}
    void setPosition(QVector3D value) noexcept {position = value;}
    void setPosition(float x, float y, float z) noexcept {position.setX(x); position.setY(y); position.setZ(z);}
    void setRotation(QVector3D value) noexcept {rotation = value;}
    void setRotation(float x, float y, float z) noexcept {rotation.setX(x); rotation.setY(y); rotation.setZ(z);}
};

#endif // LIGHT_H
