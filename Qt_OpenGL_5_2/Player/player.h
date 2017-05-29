#ifndef PLAYER_H
#define PLAYER_H

#include <QVector>
#include "DrawableObject.h"
#include "OBJManager/objmanager.h"
#include "TexturesManager/texturesmanager.h"
#include <cmath>

class Player
{
private:
    DrawableObject drone;
    GLfloat speed;
    QVector2D direction;

public:
    Player();

    void Init(OBJManager* objManager, TexturesManager* texturesManager, QOpenGLShaderProgram* shader);
    void Logic(int deltaTime);
    void Draw(Camera camera, Light light, QMatrix4x4 pMatrix);
    void Input(Qt::Key key);

    QVector3D& GetPosition() noexcept { return drone.getPosition(); }
    QVector3D& GetRotation() noexcept { return drone.getRotation(); }
};

#endif
