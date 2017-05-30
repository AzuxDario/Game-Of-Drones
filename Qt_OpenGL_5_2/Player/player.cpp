#include "player.h"


Player::Player()
{
    speed = 0;
    maxspeed = 0.4;
    direction = QVector2D(M_PI/2,0);
    rotation = QVector2D(0,0);
}

void Player::init(OBJManager* objManager, TexturesManager* texturesManager, QOpenGLShaderProgram* shader)
{
    DrawableObject::init(shader, objManager->getModel(":/Objects/drone"), texturesManager->getTexture(":/Textures/drone"));
}

void Player::logic(int deltaTime)
{
    speed = max(speed / 1.01 - 0.01, 0.0);

    moveSpeed.setZ(-speed * cos(direction.x()));//lewo-prawo
    moveSpeed.setY(speed * sin(direction.x()));//przód-tył
    moveSpeed.setX(-speed * sin(direction.y()));

    getRotation().setX(direction.x() * 180 / M_PI);
    getRotation().setY(direction.y() * 180 / M_PI);

    DrawableObject::logic(deltaTime);
}

void Player::draw(Camera camera, Light light, QMatrix4x4 pMatrix)
{
    DrawableObject::draw(camera, light, pMatrix);
}

void Player::input(Qt::Key key)
{

}
