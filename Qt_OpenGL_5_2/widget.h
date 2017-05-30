#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLTexture>
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QApplication>

#include "camera.h"
#include "light.h"
#include "OBJManager/objmanager.h"
#include "drawableobject.h"
#include "game.h"
#include "EnvGenerator/EnvGenerator.h"
#include "TexturesManager/texturesmanager.h"
#include "Physics/physics.h"
#include "telemetry.h"
#include "KeyboardManager/keyboardmanager.h"
#include "musicplayer.h"

class Widget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

private:
    QMatrix4x4 projectionMatrix;

    QOpenGLShaderProgram shaderProgram;
    QTimer paintTimer;

    Camera camera;
    Light light;
    Telemetry telemetry;
    Game game;
    KeyboardManager keyboardManager;
    MusicPlayer musicPlayer;

    QGridLayout* gridLayout;
    QGridLayout* gridMenuLayout;
    QLabel *fpsCounterLabel;
    QLabel *timerLabel;
    QLabel *shipInfo;
    QPushButton *startGameButton;
    QPushButton *closeGameButton;

    QTime timer;
    QString cssFpsAndTimer;
    bool menuIsActive;

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    QSize sizeHint() const;

public slots:

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void startGame();
    void pauseGame();
    void closeGame();

protected:

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void logic();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:

    void loadShaders();
    void updateTime();
    void makeConnection();
    void createLayout();
};

#endif // WIDGET_H
