#ifndef GAME_H
#define GAME_H

#define _USE_MATH_DEFINES

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QDateTime>
#include <cmath>

#include "OBJManager/objmanager.h"
#include "computerplayer.h"
#include "TexturesManager/texturesmanager.h"
#include "EnvGenerator/EnvGenerator.h"
#include "Physics/physics.h"
#include "drawableobject.h"
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
    Light light;

    KeyboardManager* keyboardManager;

    DrawableObject skybox;
    DrawableObject star;
    DrawableObject arrow;

    long int lastFrameTime;
    int checkCollisionsDefaultTime;
    int checkCollisionsTime;
    bool isGamePaused;

public:
    Game();
    Player player;
    ComputerPlayer enemy;
    QVector<DrawableObject> DrawableObjects;
    void initializeGame(QOpenGLShaderProgram* shader, KeyboardManager* keyboardManager);
    void render(Camera& camera, QMatrix4x4 pMatrix);
    void logic(Camera& camera);
    void checkCollisions();

    void pause();
    void start();
    void restart();

    void setIsGamePaused(bool value) noexcept {isGamePaused = value;}
    bool getIsGamePaused() noexcept {return isGamePaused;}
    float getPlayerAccelerate() noexcept {return player.getAccelerate();}
    float getPlayerSpeed() noexcept { return player.moveSpeed.length();}


private:

    void loadModels();
    void loadTextures();
    void createEnviroment(QOpenGLShaderProgram* shader);
    void createPlayer(QOpenGLShaderProgram* shader);
    void createArrow(QOpenGLShaderProgram* shader);
    void createOpponents(QOpenGLShaderProgram* shader);
    void updateCamera(Camera& camera);
    void input();
};

#endif // GAME_H
