#include "player.h"
#include <math.h>

Player::Player()
{

}

void Player::Init(OBJManager* objManager, TexturesManager* texturesManager, QOpenGLShaderProgram* shader)
{
    drone.Init(shader, objManager->GetModel(":/Objects/drone"), texturesManager->GetTexture(":/Textures/drone"));

}

void Player::Logic(int deltaTime)
{
    speed = max(speed / 1.01 - 0.01, 0.0);


    drone.moveSpeed.setZ(-speed * cos(direction.x()));//lewo-prawo
    drone.moveSpeed.setY(speed * sin(direction.x()));//przód-tył
    drone.moveSpeed.setX(-speed * sin(direction.y()));

    drone.getRotation().setX(direction.x() * 180 / M_PI);
    drone.getRotation().setY(direction.y() * 180 / M_PI);

    drone.Logic(deltaTime);

}

void Player::Draw(Camera camera, Light light, QMatrix4x4 pMatrix)
{
    drone.Draw(camera, light, pMatrix);
}

void Player::Input(Qt::Key key)
{

}
