#include "player.h"


Player::Player()
{
    accelerate = 0;
    maxspeed = 0.15;
    acceleration = 0.01;
    friction = 1.01;
    direction = QVector2D(0,0);
    agility = 0.2;
    maxturn = 10;
    rotation = QVector2D(0,0);
}

void Player::init(OBJManager* objManager, TexturesManager* texturesManager, QOpenGLShaderProgram* shader)
{
    DrawableObject::init(shader, objManager->getModel(":/Objects/Content/spaceship.obj"), texturesManager->getTexture(":/Textures/drone"));
}

void Player::logic(int deltaTime)
{
    direction += rotation;
    rotation /= 1.2;
    if (abs(rotation.x()) < 0.01) rotation.setX(0);
    if (abs(rotation.y()) < 0.01) rotation.setY(0);
    if (direction.x() > 360) direction.setX(direction.x() - 360);
    else if (direction.x() < 0) direction.setX(direction.x() + 360);
    if (direction.y() > 360) direction.setY(direction.y() - 360);
    else if (direction.y() < 0) direction.setY(direction.y() + 360);
    accelerate = max(accelerate / 1.01 - 0.005, 0.0);

    QMatrix4x4 roll = QMatrix4x4();
    QMatrix4x4 pitch = QMatrix4x4();
    QMatrix4x4 yaw = QMatrix4x4();
    roll.rotate(direction.x(), 1, 0, 0);
    pitch.rotate(direction.y(), 0, 1, 0);
    QMatrix4x4 rm = roll * pitch * yaw;

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
