#include "widget.h"

Widget::Widget(QWidget *parent) : QOpenGLWidget(parent)
{
    timer.start();

    cssFpsAndTimer = "font-size:30px;color:white;padding:8px;margin:10px;background-color: rgba(0,84,210,0.5);border: 1px solid rgba(0,94,220,0.6); border-radius: 10px;";

    fpsCounterLabel = new QLabel("FPS: 00");
    fpsCounterLabel->setStyleSheet(cssFpsAndTimer);
    //fpsCounterLabel->setMinimumWidth(200);
    fpsCounterLabel->setAlignment(Qt::AlignLeft);
    timerLabel = new QLabel("Czas: 00:00.00");
    timerLabel->setStyleSheet(cssFpsAndTimer);
    //timerLabel->setMinimumWidth(300);
    timerLabel->setAlignment(Qt::AlignRight);
    shipInfo = new QLabel("Informacje o statku<br/>Nazwa statku: スーパー宇宙船<br/>Prędkość: infinity<br/>Pancerz: infinity/NaN<br/>Dopalacz: NaN/NaN");
    shipInfo->setAlignment(Qt::AlignCenter);;
    shipInfo->setStyleSheet(cssFpsAndTimer);
    shipInfo->setMinimumSize(800,300);
    shipInfo->setMaximumSize(800,300);
    startGame = new QPushButton("Start!",this);
    startGame->setStyleSheet(cssFpsAndTimer);
    gridLayout = new QGridLayout(this);
    gridLayout->addWidget(fpsCounterLabel,0,0,Qt::AlignTop | Qt::AlignLeft);
    gridLayout->addWidget(timerLabel,0,2,Qt::AlignTop | Qt::AlignRight);
    gridLayout->addWidget(startGame,1,1);
    gridLayout->addWidget(shipInfo,2,1,Qt::AlignBottom);
    gridLayout->setColumnStretch(0,0.1);
    gridLayout->setColumnStretch(1,1.8);
    gridLayout->setColumnStretch(2,0.1);

    //musicPlayer.setSong("qrc:/Music/song");
    //musicPlayer.play(QMediaPlaylist::CurrentItemInLoop);
}

Widget::~Widget()
{

}

QSize Widget::sizeHint() const
{
    return QSize(640, 480);
}

void Widget::loadShaders()
{
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/LightningVertexShader");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/LightningFragmentShader");
    shaderProgram.link();
}

void Widget::initializeGL()
{
    initializeOpenGLFunctions(); //Odpala funkcję OpenGL'a. Bez tego wywala aplikację zanim ją ujrzysz.
    glEnable(GL_DEPTH_TEST); //Sprawi, że będą wyświetlane tylko te obiekty, które sa bliżej kamery
    glEnable(GL_CULL_FACE); //Obiekty będą renderowane tylko na przedniej stronie
    glClearColor(0,0,0,0); //Ustawienie koloru tła

    loadShaders(); //Ładowanie shaderów
    game.initializeGame(&shaderProgram, &keyboardManager);

    connect(&paintTimer, SIGNAL(timeout()), this, SLOT(update()));
    paintTimer.setTimerType(Qt::PreciseTimer);
    paintTimer.start(14);
}

void Widget::resizeGL(int width, int height)
{
    if (height == 0)
    {
        height = 1; //Aby nie dzielić przez zero
    }

    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(60.0, (float) width / (float) height, 0.001, 1000);
    glViewport(0, 0, width, height);
}

void Widget::paintGL()
{
    logic();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    game.render(camera, light, projectionMatrix);

    updateTime();
}

void Widget::logic()
{
    game.logic(camera);

    fpsCounterLabel->setText("FPS: " + QString::number(telemetry.getFPS()));
    telemetry.logic();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    event->accept();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
}

void Widget::wheelEvent(QWheelEvent *event)
{
    event->accept();
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    Qt::Key key = (Qt::Key)event->key();

    keyboardManager.keyPressed(key);

    if(event->key() == Qt::Key_Escape)
    {
        QApplication::quit();
    } 

    event->accept();
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    Qt::Key key = (Qt::Key)event->key();

    keyboardManager.keyReleased(key);

    event->accept();
}

void Widget::updateTime()
{
    QString min, sec, mSec;
    int timeElapsed = timer.elapsed();
    int minutes = timeElapsed / 60000;
    timeElapsed -= minutes * 60000;
    int seconds = timeElapsed / 1000;
    timeElapsed -=seconds * 1000;
    if(minutes<10)
    {
        min = "0" + QString::number(minutes);
    }
    else
    {
        min = QString::number(minutes);
    }
    if(seconds<10)
    {
        sec = "0" + QString::number(seconds);
    }
    else
    {
        sec = QString::number(seconds);
    }
    if(timeElapsed<10)
    {
        mSec = "00" + QString::number(timeElapsed);
    }
    else if(timeElapsed<100)
    {
        mSec = "0" + QString::number(timeElapsed);
    }
    else
    {
        mSec = QString::number(timeElapsed);
    }

    timerLabel->setText("Czas: "+min+":"+sec+"."+mSec);
}
