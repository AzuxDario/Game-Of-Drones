#ifndef GAME_H
#define GAME_H

#define _USE_MATH_DEFINES

#include <QObject>
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
#include "Engine/Physics/physics.h"
#include "drawableobject.h"
#include "camera.h"
#include "light.h"
#include "Player/player.h"
#include "KeyboardManager/keyboardmanager.h"

class Game : public QObject
{
    Q_OBJECT

private:
    QMatrix4x4 projectionMatrix;

    OBJManager objManager;
    TexturesManager texturesManager;
    EnvGenerator envGenerator;
    Physics physics;
    Camera camera;
    Camera hudCamera;
    Light light;

    KeyboardManager* keyboardManager;

    Player player;
    ComputerPlayer enemy;

    DrawableObject skybox;
    DrawableObject star;
    QVector<DrawableObject*> planets;
    QVector<DrawableObject*> otherPlanets;
    DrawableObject arrow;
    DrawableObject target;
    QVector<QVector3D> race;

    long int lastFrameTime;
    int checkCollisionsDefaultTime;
    int checkCollisionsTime;
    bool isGamePaused;
    bool isGameEnded;

signals:
    void endGame(QString message);

public:
    Game();
    void initializeGame(QOpenGLShaderProgram* shader, KeyboardManager* keyboardManager);
    void render();
    void logic();
    void checkCollisions();

    void pause();
    void start();
    void resume();
    void restart();

    bool getIsGamePaused() noexcept {return isGamePaused;}
    bool getIsGameEnded() noexcept {return isGameEnded;}
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
    void Win();
    void Lose();
};

#endif // GAME_H
