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
public:
    Player player;
    ComputerPlayer enemy;

private:
    QMatrix4x4 projectionMatrix;

    OBJManager objManager;
    TexturesManager texturesManager;
    EnvGenerator envGenerator;
    Physics physics;
    Camera camera;
    Light light;

    KeyboardManager* keyboardManager;

    DrawableObject skybox;
    DrawableObject star;
    QVector<DrawableObject*> planets;
    DrawableObject arrow;
    DrawableObject target;
    QVector<QVector3D> race;

    long int lastFrameTime;
    int checkCollisionsDefaultTime;
    int checkCollisionsTime;
    bool isGamePaused;

public:
    Game();
    void initializeGame(QOpenGLShaderProgram* shader, KeyboardManager* keyboardManager);
    void render();
    void logic();
    void checkCollisions();

    void pause();
    void start();
    void restart();

    bool getIsGamePaused() noexcept {return isGamePaused;}
    QMatrix4x4& getProjectionMatrixRef() noexcept {return projectionMatrix;}
    Camera& getCameraRef() noexcept {return camera;}
    float getPlayerAccelerate() noexcept {return player.getAccelerate();}
    float getPlayerSpeed() noexcept { return player.moveSpeed.length();}


private:
    void loadModels();
    void loadTextures();
    void createEnviroment(QOpenGLShaderProgram* shader);
    void createPlayer(QOpenGLShaderProgram* shader);
    void createRace(QOpenGLShaderProgram* shader);
    void createOpponents(QOpenGLShaderProgram* shader);
    void input();
};

#endif // GAME_H
