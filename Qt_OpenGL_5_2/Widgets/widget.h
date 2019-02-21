#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QMouseEvent>
#include <QOpenGLTexture>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QProgressBar>
#include <QApplication>
#include <QDesktopWidget>

#include "Engine/game.h"
#include "Addons/telemetry.h"
#include "Input/keyboardmanager.h"
#include "Sound/musicplayer.h"
#include "Addons/timeconverter.h"

class Widget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

private:
    //Shader progrem
    QOpenGLShaderProgram shaderProgram;

    //Game timers to render game and update layout
    QTimer paintTimer;
    QTimer layoutTimer;

    //Game specific objects
    Telemetry telemetry;
    Game game;
    KeyboardManager keyboardManager;
    MusicPlayer musicPlayer;

    //Layout elements
    QGridLayout* gridLayout;
    QGridLayout* gridMenuLayout;
    QLabel *gameTitleLabel;
    QLabel *fpsCounterLabel;
    QLabel *timerLabel;
    QLabel *speedLabel;
    QLabel *enginePowerLabel;
    QLabel *shipInfo;
    QLabel *gameInfoLabel;
    QPushButton *startGameButton;
    QPushButton *restartGameButton;
    QPushButton *closeGameButton;
    QProgressBar *speedProgressBar;
    QProgressBar *enginePowerProgressBar;

    //Layout css
    QString cssLabels;
    QString cssButtons;
    QString cssProgressBars;

    //Objects to calculate ingame time
    QTime playGameTimer;
    int miliSecondsFromStart;
    bool addFromTimer;

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

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void loadShaders();
    void makeConnection();
    void createLayout();
    void initializeSoundtrack();
    void toggleMenuVisibility(bool value);
    void toggleInGameLayoutVisibility(bool value);
    void initializeTimers();

private slots:
    void mouseTimerTimeout();
    void updateLayout();
    void showEndGameInfo(QString message);
};

#endif // WIDGET_H
