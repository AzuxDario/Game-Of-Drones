#include "player.h"


Player::Player()
{
    direction = QVector2D(0,0);
    speed = 0;
}

void Player::Init(OBJManager* objManager, TexturesManager* texturesManager, QOpenGLShaderProgram* shader)
{
    DrawableObject::Init(shader, objManager->GetModel(":/Objects/drone"), texturesManager->GetTexture(":/Textures/drone"));
}

void Player::Logic(int deltaTime)
{
    speed = max(speed / 1.01 - 0.01, 0.0);

    moveSpeed.setX(speed * cos(direction.x() * cos(direction.y())));
    moveSpeed.setY(speed * sin(direction.x() * cos(direction.y())));
    moveSpeed.setZ(speed * sin(direction.y()));

    DrawableObject::Logic(deltaTime);
}

void Player::Draw(Camera camera, Light light, QMatrix4x4 pMatrix)
{
    DrawableObject::Draw(camera, light, pMatrix);
}

void Player::Input(Qt::Key key)
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
