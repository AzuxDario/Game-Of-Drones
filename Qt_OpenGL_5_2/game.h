#ifndef GAME_H
#define GAME_H
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QDateTime>

#include "OBJManager/objmanager.h"
#include "TexturesManager/texturesmanager.h"
#include "EnvGenerator/EnvGenerator.h"
#include "Physics/physics.h"
#include "drawableobject.h"
#include "movableobject.h"
#include "camera.h"
#include "light.h"
#include "Player/player.h"
#include "KeyboardManager/keyboardmanager.h"

class Game
{
private:

    OBJManager objManager;
    TexturesManager texturesManager;
    EnvGenerator envGenerator;
    Physics physics;
    Player player;
    KeyboardManager* keyboardManager;

    DrawableObject skybox;
    DrawableObject star;

    long int lastFrameTime;

public:
    Game();

    QVector<DrawableObject> DrawableObjects;
    void initializeGame(QOpenGLShaderProgram* shader, KeyboardManager* keyboardManager);
    void render(Camera& camera, Light& light, QMatrix4x4 pMatrix);
    void logic(Camera& camera);
    void draw(QOpenGLShaderProgram & shader);
    //Zmiana pozycji
    void move();
    //AI, sterowanie itp.
    void step();

private:

    void loadModels();
    void loadTextures();
    void createEnviroment(QOpenGLShaderProgram* shader);
    void createPlayer(QOpenGLShaderProgram* shader);
    void updateCamera(Camera& camera);
    void input();
};

#endif // GAME_H
