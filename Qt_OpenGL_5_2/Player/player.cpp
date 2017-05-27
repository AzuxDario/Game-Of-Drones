#include "player.h"

Player::Player()
{

}

void Player::Init(OBJManager* objManager, TexturesManager* texturesManager, QOpenGLShaderProgram* shader)
{
    drone.Init(shader, objManager->GetModel(":/Objects/drone"), texturesManager->GetTexture(":/Textures/drone"));
}

void Player::Logic(int deltaTime)
{
    drone.Logic(deltaTime);
}

void Player::Draw(Camera camera, Light light, QMatrix4x4 pMatrix)
{
    drone.Draw(camera, light, pMatrix);
}

void Player::Input(Qt::Key key)
{
    switch(key)
    {
    case(Qt::Key::Key_W):
    {
        drone.getPosition() += QVector3D(1, 0, 0);
        break;
    }
    default:
    {
        break;
    }
    }
}
