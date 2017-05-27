#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4.h>

class Camera
{
private:
    QVector3D position;
    QVector3D rotation;
    float distance;

public:
    Camera();
    QMatrix4x4 GetMatrix();

    QVector3D getPosition() noexcept {return position;}
    QVector3D getRotation() noexcept {return rotation;}
    float getPositionX() noexcept {return position.x();}
    float getPositionY() noexcept {return position.y();}
    float getPositionZ() noexcept {return position.z();}
    float getRotationX() noexcept {return rotation.x();}
    float getRotationY() noexcept {return rotation.y();}
    float getRotationZ() noexcept {return rotation.z();}
    float getDistance() noexcept {return distance;}
    void setPosition(QVector3D value) noexcept {position = value;}
    void setRotation(QVector3D value) noexcept {rotation = value;}
    void setPositionX(float value) noexcept {position.setX(value);}
    void setPositionY(float value) noexcept {position.setY(value);}
    void setPositionZ(float value) noexcept {position.setZ(value);}
    void setRotationX(float value) noexcept {rotation.setX(value);}
    void setRotationY(float value) noexcept {rotation.setY(value);}
    void setRotationZ(float value) noexcept {rotation.setZ(value);}
    void setDistance(float value) noexcept {distance = value;}
};

#endif // CAMERA_H
