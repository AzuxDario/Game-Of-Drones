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
#include <QProgressBar>
#include <QApplication>
#include <QDesktopWidget>

#include "camera.h"
#include "OBJManager/objmanager.h"
#include "drawableobject.h"
#include "game.h"
#include "EnvGenerator/EnvGenerator.h"
#include "TexturesManager/texturesmanager.h"
#include "Physics/physics.h"
#include "telemetry.h"
#include "KeyboardManager/keyboardmanager.h"
#include "musicplayer.h"
#include "timeconverter.h"

class Widget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

private:
    QMatrix4x4 projectionMatrix;

    QOpenGLShaderProgram shaderProgram;
    QTimer paintTimer;
    QTimer layoutTimer;

    Camera camera;
    Telemetry telemetry;
    Game game;
    KeyboardManager keyboardManager;
    MusicPlayer musicPlayer;

    QGridLayout* gridLayout;
    QGridLayout* gridMenuLayout;
    QLabel *fpsCounterLabel;
    QLabel *timerLabel;
    QLabel *speedLabel;
    QLabel *enginePowerLabel;
    QLabel *shipInfo;
    QPushButton *startGameButton;
    QPushButton *restartGameButton;
    QPushButton *closeGameButton;
    QProgressBar *speedProgressBar;
    QProgressBar *enginePowerProgressBar;

    QTime playGameTimer;
    int miliSecondsFromStart;
    QString cssLabels;
    QString cssButtons;
    QString cssProgressBars;
    bool menuIsActive;
    QTimer mouseTimer;
    QPoint mousePos;

signals:
    void updateSpeedProgressBar(int value);
    void updateEnginePowerProgressBar(int value);


public:
    Widget(QWidget *parent = 0);
    ~Widget();
    QSize sizeHint() const;

public slots:

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void startGame();
    void pauseGame();
    void restartGame();
    void closeGame();

protected:

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void logic();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:

    void loadShaders();
    void updateTimeLabel();
    void makeConnection();
    void createLayout();
    void initializeSoundtrack();
    void toggleMenuVisibility(bool value);
    void toggleInGameLayoutVisibility(bool value);
private slots:
    void mouseTimerTimeout();
    void updateLayout();
};

#endif // WIDGET_H
