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

    drone.moveSpeed.setZ(-speed * cos(direction.x()));//lewo-prawo
    drone.moveSpeed.setY(speed * sin(direction.x()));//przód-tył
    drone.moveSpeed.setX(-speed * sin(direction.y()));

    drone.getRotation().setX(direction.x() * 180 / M_PI);
    drone.getRotation().setY(direction.y() * 180 / M_PI);

    drone.Logic(deltaTime);


    DrawableObject::logic(deltaTime);
}

void Player::draw(Camera camera, Light light, QMatrix4x4 pMatrix)
{
    DrawableObject::draw(camera, light, pMatrix);
}

void Player::input(Qt::Key key)
{

}
