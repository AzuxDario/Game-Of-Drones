#include "player.h"


Player::Player()
{
    accelerate = 0;
    maxspeed = 0.15;
    acceleration = 0.01;
    friction = 1.01;
    direction = QVector3D(0,0,0);
    agility = 0.2;
    maxturn = 10;
    rotation = QVector2D(0,0);

    getScale() = QVector3D(0.3f, 0.3f, 0.3f);

    getLightProperties().setSpecularReflection(0.4);
    getLightProperties().setAmbientReflection(0.5);
    getLightProperties().setAmbientColor(96,96,96);
    getLightProperties().setDiffuseReflection(1);
    getLightProperties().setDiffuseColor(164,164,164);

}

void Player::init(OBJModel* model, QOpenGLTexture* texture, QOpenGLShaderProgram* shader)
{
    DrawableObject::init(shader, model, texture);
}

void Player::logic(int deltaTime)
{
    //direction.setX(direction.x() + (rotation.x() * cos(direction.y()* M_PI / 180) + rotation.y() * sin(direction.z() * M_PI / 180)));
    //direction.setY(direction.y() + (rotation.y() * cos(direction.z()* M_PI / 180) + rotation.x() * sin(direction.y() * M_PI / 180)));
    //direction.setZ(direction.z() + (rotation.x() * sin(direction.y()* M_PI / 180) + rotation.y() * sin(direction.z() * M_PI / 180)));

    QMatrix4x4 mm = QMatrix4x4();

    //mm.rotate(direction.x(), 1, 0, 0);
    //mm.rotate(direction.y(), 0, 1, 0);
    mm.rotate(direction.z(), 0, 0, 1);

    direction += QVector3D(mm.mapVector(rotation.toVector3D()));

    rotation /= 1.2;
    if (abs(rotation.x()) < 0.01) rotation.setX(0);
    if (abs(rotation.y()) < 0.01) rotation.setY(0);
    if (direction.x() > 360) direction.setX(direction.x() - 360);
    else if (direction.x() < 0) direction.setX(direction.x() + 360);
    if (direction.y() > 360) direction.setY(direction.y() - 360);
    else if (direction.y() < 0) direction.setY(direction.y() + 360);
    if (direction.z() > 360) direction.setZ(direction.y() - 360);
    else if (direction.z() < 0) direction.setZ(direction.y() + 360);
    accelerate = max(accelerate / 1.01 - 0.005, 0.0);

    QMatrix4x4 rm = QMatrix4x4();

    rm.rotate(direction.x(), 1, 0, 0);
    rm.rotate(direction.y(), 0, 1, 0);
    rm.rotate(direction.z(), 0, 0, 1);

    QVector3D movement = rm.mapVector(QVector3D(0,0,accelerate));

    moveSpeed = (moveSpeed / friction) + movement;

    QVector3D dv = rm.mapVector(QVector3D(0,1,0));

    getRotation().setX(direction.x());
    getRotation().setY(direction.y());
    getRotation().setZ(direction.z());

    //getRotation().setX(atan2(dv.z(), dv.y()) * 180 / M_PI);
    //getRotation().setZ(atan2(sqrt(pow(dv.z(),2) + pow(dv.y(),2)),dv.x()) * 180 / M_PI);

    DrawableObject::logic(deltaTime);
}

void Player::draw(Camera camera, Light light, QMatrix4x4 pMatrix)
{
    DrawableObject::draw(camera, light, pMatrix);
}

void Player::input(Qt::Key key)
{

}

void Player::restoreStartPosition()
{
    //Restore start position and rotation
    setPosition(QVector3D(0.0,0.0,-200.0));
    setRotation(QVector3D(0.0,0.0,0.0));

    //Restore start speed
    //I don't know what I reset. I try to stop it.
    accelerate = 0.0;
    direction = QVector2D(0,0);
    rotation = QVector2D(0,0);
    moveSpeed = QVector3D(0,0,0);
    rotationSpeed = QVector3D(0,0,0);
}
