#include "player.h"


Player::Player()
{
    direction = QVector2D(0,0);
    speed = 0;
}

void Player::init(OBJManager* objManager, TexturesManager* texturesManager, QOpenGLShaderProgram* shader)
{
    DrawableObject::init(shader, objManager->getModel(":/Objects/drone"), texturesManager->getTexture(":/Textures/drone"));
}

void Player::logic(int deltaTime)
{
    speed = max(speed / 1.01 - 0.01, 0.0);

    moveSpeed.setX(speed * cos(direction.x() * cos(direction.y())));
    moveSpeed.setY(speed * sin(direction.x() * cos(direction.y())));
    moveSpeed.setZ(speed * sin(direction.y()));

    DrawableObject::logic(deltaTime);
}

void Player::draw(Camera camera, Light light, QMatrix4x4 pMatrix)
{
    DrawableObject::draw(camera, light, pMatrix);
}

void Player::input(Qt::Key key)
{
    switch(key)
    {
        case(Qt::Key::Key_W):
        {
            speed = 0.1;
            break;
        }
        default:
        {
            break;
        }
    }
}
