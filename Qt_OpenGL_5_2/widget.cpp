#include "widget.h"

Widget::Widget(QWidget *parent) : QOpenGLWidget(parent)
{
    lastFrameTime = QDateTime::currentMSecsSinceEpoch();
    fpsCounterLabel = new QLabel("FPS: infinity",this);
    fpsCounterLabel->setStyleSheet("color:white;padding:8px;margin:10px;background-color: rgba(0,84,210,0.5);border: 1px solid rgba(0,94,220,0.6); border-radius: 10px;");
    fpsCounterLabel->setMinimumWidth(100);
    fpsCounterLabel->setAlignment(Qt::AlignLeft);

}

Widget::~Widget()
{

}

QSize Widget::sizeHint() const
{
    return QSize(640, 480);
}

void Widget::initializeGL()
{
    initializeOpenGLFunctions(); //Odpala funkcję OpenGL'a. Bez tego wywala aplikację zanim ją ujrzysz.
    glEnable(GL_DEPTH_TEST); //Sprawi, że będą wyświetlane tylko te obiekty, które sa bliżej kamery
    glEnable(GL_CULL_FACE); //Obiekty będą renderowane tylko na przedniej stronie
    glClearColor(0,0,0,0); //Ustawienie koloru tła

    QVector<QString> modelsToLoad;
    modelsToLoad.push_back(":/Objects/skybox");
    modelsToLoad.push_back(":/Objects/planetoid");
    modelsToLoad.push_back(":/Objects/star");
    objManager.LoadAll(modelsToLoad);

    QVector<QString> texturesToLoad;
    texturesToLoad.push_back(":/Textures/skybox");
    texturesToLoad.push_back(":/Textures/planetoid");
    texturesToLoad.push_back(":/Textures/star");
    texturesManager.LoadAll(texturesToLoad);

    //Ładowanie shaderów
    cubeShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/LightningVertexShader");
    cubeShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/LightningFragmentShader");
    cubeShaderProgram.link();

    lightSourceShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/ColoringVertexShader");
    lightSourceShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/ColoringFragmentShader");
    lightSourceShaderProgram.link();

    envGenerator.Init(&objManager, &texturesManager, &cubeShaderProgram);

    skybox.Init(&cubeShaderProgram, objManager.GetModel(":/Objects/skybox"),
                                    texturesManager.GetTexture(":/Textures/skybox"));
    skybox.getLightProperties().setAmbientColor(255,255,255,0);
    skybox.getLightProperties().setSpecularReflection(0);

    star.Init(&cubeShaderProgram, objManager.GetModel(":/Objects/star"),
                                  texturesManager.GetTexture(":/Textures/star"));
    star.getLightProperties().setAmbientColor(255,255,255,0);
    star.GetRotationSpeed().setY(0.007f);

    light.Position.setZ(2);

    connect(&paintTimer, SIGNAL(timeout()), this, SLOT(update()));
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

    glDisable(GL_CULL_FACE);
    skybox.Draw(camera, light, projectionMatrix);
    glEnable(GL_CULL_FACE);

    envGenerator.Draw(camera, light, projectionMatrix);
    star.Draw(camera, light, projectionMatrix);
}

void Widget::logic()
{
    int deltaTime = QDateTime::currentMSecsSinceEpoch() - lastFrameTime;
    lastFrameTime = QDateTime::currentMSecsSinceEpoch();

    envGenerator.RemoveObjects(physics.CheckCollisions(&star, envGenerator.GetObjects()));

    envGenerator.Logic(camera.Position, deltaTime);
    star.Logic(deltaTime);

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
        float cameraRotY = camera.Rotation.y();
        cameraRotY -= deltaX;

        while (cameraRotY < 0)
        {
            cameraRotY += 360;
        }
        while (cameraRotY >= 360)
        {
            cameraRotY -= 360;
        }
        camera.Rotation.setY(cameraRotY);

        float cameraRotX = camera.Rotation.x();
        cameraRotX -= deltaY;

        while (cameraRotX < 0)
        {
            cameraRotX += 360;
        }
        while (cameraRotX >= 360)
        {
            cameraRotX -= 360;
        }
        camera.Rotation.setX(cameraRotX);

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
            camera.Distance *= 1.1;
        }
        else if (delta > 0)
        {
            camera.Distance *= 0.9;
        }

        //update();
    }

    event->accept();
}

void Widget::keyPressEvent(QKeyEvent *event)
{

}
