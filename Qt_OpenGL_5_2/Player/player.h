#ifndef PLAYER_H
#define PLAYER_H

#include <QVector>
#include "DrawableObject.h"
#include "OBJManager/objmanager.h"
#include "TexturesManager/texturesmanager.h"

class Player
{
public:
    Player();

    void Init(OBJManager* objManager, TexturesManager* texturesManager, QOpenGLShaderProgram* shader);
    void Logic(int deltaTime);
    void Draw(Camera camera, Light light, QMatrix4x4 pMatrix);
    void Input(Qt::Key key);

    QVector3D& getPosition() noexcept { return drone.getPosition(); }
private:
    DrawableObject drone;
};

#endif
