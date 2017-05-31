#include "player.h"


Player::Player()
{
    accelerate = 0;
    maxspeed = 0.2;
    acceleration = 0.02;
    friction = 1.4;
    direction = QVector2D(0,0);
}

void Player::init(OBJManager* objManager, TexturesManager* texturesManager, QOpenGLShaderProgram* shader)
{
    DrawableObject::init(shader, objManager->getModel(":/Objects/drone"), texturesManager->getTexture(":/Textures/drone"));
}

void Player::logic(int deltaTime)
{
    accelerate = max(accelerate / 1.01 - 0.005, 0.0);

    QMatrix4x4 rm = QMatrix4x4();
    rm.rotate(direction.x(), 1, 0, 0);
    rm.rotate(direction.y(), 0, 1, 0);
    QVector3D movement = rm.mapVector(QVector3D(0,0,accelerate));

    moveSpeed = (moveSpeed / friction) + movement;

    getRotation().setX(direction.x());
    getRotation().setY(direction.y());

    DrawableObject::logic(deltaTime);
}

void Player::draw(Camera camera, Light light, QMatrix4x4 pMatrix)
{
    DrawableObject::draw(camera, light, pMatrix);
}

void Player::input(Qt::Key key)
{

}
