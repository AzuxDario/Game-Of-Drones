#ifndef GAME_H
#define GAME_H
#include <qopenglshaderprogram.h>
#include "drawableobject.h"
#include "movableobject.h"

class Game
{
public:
    Game();

    QVector<DrawableObject> ImmovableObjects;
    QVector<MovableObject> MovableObjects;

    static Game Current;
    void Draw(QOpenGLShaderProgram & shader);
    //Zmiana pozycji
    void Move();
    //AI, sterowanie itp.
    void Step();
};

#endif // GAME_H
