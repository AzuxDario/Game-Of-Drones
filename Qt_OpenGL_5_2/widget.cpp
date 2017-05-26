#include "widget.h"

Widget::Widget(QWidget *parent) : QOpenGLWidget(parent)
{
    fpsCounterLabel = new QLabel("FPS: 00");
    fpsCounterLabel->setStyleSheet("color:white;padding:8px;margin:10px;background-color: rgba(0,84,210,0.5);border: 1px solid rgba(0,94,220,0.6); border-radius: 10px;");
    fpsCounterLabel->setMinimumWidth(100);
    fpsCounterLabel->setMaximumSize(100,50);
    fpsCounterLabel->setAlignment(Qt::AlignLeft);
    timer = new QLabel("00:00:00");
    timer->setStyleSheet("color:white;padding:8px;margin:10px;background-color: rgba(0,84,210,0.5);border: 1px solid rgba(0,94,220,0.6); border-radius: 10px;");
    timer->setMinimumWidth(100);
    timer->setMaximumSize(100,50);
    timer->setAlignment(Qt::AlignRight);
    dummy = new QLabel();
    gridLayout = new QGridLayout(this);
    gridLayout->addWidget(fpsCounterLabel,0,0,Qt::AlignTop);
    gridLayout->addWidget(timer,0,2,Qt::AlignTop);
    gridLayout->addWidget(dummy,2,1,Qt::AlignBottom);
    gridLayout->setColumnStretch(0,0.1);
    gridLayout->setColumnStretch(1,1.8);
    gridLayout->setColumnStretch(2,0.1);

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
    cubeShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/LightningVertexShader");
    cubeShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/LightningFragmentShader");
    cubeShaderProgram.link();

    //lightSourceShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/ColoringVertexShader");
    //lightSourceShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/ColoringFragmentShader");
    //lightSourceShaderProgram.link();
}

void Widget::initializeGL()
{
    initializeOpenGLFunctions(); //Odpala funkcję OpenGL'a. Bez tego wywala aplikację zanim ją ujrzysz.
    glEnable(GL_DEPTH_TEST); //Sprawi, że będą wyświetlane tylko te obiekty, które sa bliżej kamery
    glEnable(GL_CULL_FACE); //Obiekty będą renderowane tylko na przedniej stronie
    glClearColor(0,0,0,0); //Ustawienie koloru tła

    loadShaders(); //Ładowanie shaderów
    game.initializeGame(&cubeShaderProgram);

    light.getPosition().setZ(2);

    connect(&paintTimer, SIGNAL(timeout()), this, SLOT(update()));
    paintTimer.setTimerType(Qt::PreciseTimer);
    paintTimer.start(15);
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
}

void Widget::logic()
{
    game.logic(camera);

    fpsCounterLabel->setText("FPS: " + QString::number(telemetry.GetFPS()));
    telemetry.Logic();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    lastMousePosition = event->pos();
    event->accept();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    int deltaX = event->x() - lastMousePosition.x();
    int deltaY = event->y() - lastMousePosition.y();
    if (event->buttons() & Qt::LeftButton)
    {
        float cameraRotY = camera.getRotationY();
        cameraRotY -= deltaX;

        while (cameraRotY < 0)
        {
            cameraRotY += 360;
        }
        while (cameraRotY >= 360)
        {
            cameraRotY -= 360;
        }
        camera.setRotationY(cameraRotY);

        float cameraRotX = camera.getRotationX();
        cameraRotX -= deltaY;

        while (cameraRotX < 0)
        {
            cameraRotX += 360;
        }
        while (cameraRotX >= 360)
        {
            cameraRotX -= 360;
        }
        camera.setRotationX(cameraRotX);

        //update();
    }
    lastMousePosition = event->pos();
    event->accept();
}

void Widget::wheelEvent(QWheelEvent *event)
{
    int delta = event->delta();
    if (event->orientation() == Qt::Vertical)
    {
        if (delta < 0)
        {
            camera.setDistance(camera.getDistance() * 1.1);
        }
        else if (delta > 0)
        {
            camera.setDistance(camera.getDistance() * 0.9);
        }

        //update();
    }

    event->accept();
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        QApplication::quit();
    }
}
