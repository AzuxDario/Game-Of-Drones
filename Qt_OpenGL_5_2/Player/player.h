#ifndef PLAYER_H
#define PLAYER_H

#define _USE_MATH_DEFINES

#include <QVector>
#include "DrawableObject.h"
#include "OBJManager/objmanager.h"
#include "TexturesManager/texturesmanager.h"
#include <cmath>

class Player : public DrawableObject
{
private:

public:
    Player();

    void init(OBJManager* objManager, TexturesManager* texturesManager, QOpenGLShaderProgram* shader);
    void logic(int deltaTime);
    void draw(Camera camera, Light light, QMatrix4x4 pMatrix);
    void input(Qt::Key key);

    float accelerate;
    float friction;
    float maxspeed;
    float acceleration;
    float agility;
    float maxturn;
    QVector2D direction;
    QVector2D rotation;

public:
    float getAccelerate() noexcept {return accelerate;}
};

#endif
