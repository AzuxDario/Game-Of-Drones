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


public:
    Player();

    void Init(OBJManager* objManager, TexturesManager* texturesManager, QOpenGLShaderProgram* shader);
    void Logic(int deltaTime);
    void Draw(Camera camera, Light light, QMatrix4x4 pMatrix);
    void Input(Qt::Key key);

    QVector3D& GetPosition() noexcept { return drone.getPosition(); }
    QVector3D& GetRotation() noexcept { return drone.getRotation(); }

    GLfloat speed = 0;
    float maxspeed = 0.4;
    QVector2D direction = QVector2D(M_PI/2,0);
    QVector2D rotation = QVector2D(0,0);
};

#endif
