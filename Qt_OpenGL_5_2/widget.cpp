#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent), cubeTexture(0)
{
    cubeTexture = nullptr;
    alpha = 25;
    beta = -25;
    distance = 2.5;
    changed = false;
    i = 0;
    lightAngle = 0;
    QTimer::singleShot(100,this,SLOT(timeout()));
    textures << ":/texture.png" << ":/obrazek" << ":/nico" << ":/rys" << ":/cat";
}

Widget::~Widget()
{
    if(cubeTexture != nullptr)
    {
        delete cubeTexture;
    }
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
    //Ładowanie shaderów
    cubeShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/lightningvertexshader.vert");
    cubeShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/lightingfragmentshader.fsh");
    cubeShaderProgram.link();
    //vertices << QVector3D(1, 0, -2) << QVector3D(0, 1, -2) << QVector3D(-1, 0, -2);
    cubeVertices << QVector3D(-0.5, -0.5,  0.5) << QVector3D( 0.5, -0.5,  0.5) << QVector3D( 0.5,  0.5,  0.5) // Front
                 << QVector3D( 0.5,  0.5,  0.5) << QVector3D(-0.5,  0.5,  0.5) << QVector3D(-0.5, -0.5,  0.5)
                 << QVector3D( 0.5, -0.5, -0.5) << QVector3D(-0.5, -0.5, -0.5) << QVector3D(-0.5,  0.5, -0.5) // Back
                 << QVector3D(-0.5,  0.5, -0.5) << QVector3D( 0.5,  0.5, -0.5) << QVector3D( 0.5, -0.5, -0.5)
                 << QVector3D(-0.5, -0.5, -0.5) << QVector3D(-0.5, -0.5,  0.5) << QVector3D(-0.5,  0.5,  0.5) // Left
                 << QVector3D(-0.5,  0.5,  0.5) << QVector3D(-0.5,  0.5, -0.5) << QVector3D(-0.5, -0.5, -0.5)
                 << QVector3D( 0.5, -0.5,  0.5) << QVector3D( 0.5, -0.5, -0.5) << QVector3D( 0.5,  0.5, -0.5) // Right
                 << QVector3D( 0.5,  0.5, -0.5) << QVector3D( 0.5,  0.5,  0.5) << QVector3D( 0.5, -0.5,  0.5)
                 << QVector3D(-0.5,  0.5,  0.5) << QVector3D( 0.5,  0.5,  0.5) << QVector3D( 0.5,  0.5, -0.5) // Top
                 << QVector3D( 0.5,  0.5, -0.5) << QVector3D(-0.5,  0.5, -0.5) << QVector3D(-0.5,  0.5,  0.5)
                 << QVector3D(-0.5, -0.5, -0.5) << QVector3D( 0.5, -0.5, -0.5) << QVector3D( 0.5, -0.5,  0.5) // Bottom
                 << QVector3D( 0.5, -0.5,  0.5) << QVector3D(-0.5, -0.5,  0.5) << QVector3D(-0.5, -0.5, -0.5);

    cubeNormals << QVector3D( 0,  0,  1) << QVector3D( 0,  0,  1) << QVector3D( 0,  0,  1) // Front
                << QVector3D( 0,  0,  1) << QVector3D( 0,  0,  1) << QVector3D( 0,  0,  1)
                << QVector3D( 0,  0, -1) << QVector3D( 0,  0, -1) << QVector3D( 0,  0, -1) // Back
                << QVector3D( 0,  0, -1) << QVector3D( 0,  0, -1) << QVector3D( 0,  0, -1)
                << QVector3D(-1,  0,  0) << QVector3D(-1,  0,  0) << QVector3D(-1,  0,  0) // Left
                << QVector3D(-1,  0,  0) << QVector3D(-1,  0,  0) << QVector3D(-1,  0,  0)
                << QVector3D( 1,  0,  0) << QVector3D( 1,  0,  0) << QVector3D( 1,  0,  0) // Right
                << QVector3D( 1,  0,  0) << QVector3D( 1,  0,  0) << QVector3D( 1,  0,  0)
                << QVector3D( 0,  1,  0) << QVector3D( 0,  1,  0) << QVector3D( 0,  1,  0) // Top
                << QVector3D( 0,  1,  0) << QVector3D( 0,  1,  0) << QVector3D( 0,  1,  0)
                << QVector3D( 0, -1,  0) << QVector3D( 0, -1,  0) << QVector3D( 0, -1,  0) // Bottom
                << QVector3D( 0, -1,  0) << QVector3D( 0, -1,  0) << QVector3D( 0, -1,  0);

    cubeTextureCoordinates << QVector2D(0, 0) << QVector2D(1, 0) << QVector2D(1, 1) // Front
                           << QVector2D(1, 1) << QVector2D(0, 1) << QVector2D(0, 0)
                           << QVector2D(0, 0) << QVector2D(1, 0) << QVector2D(1, 1) // Back
                           << QVector2D(1, 1) << QVector2D(0, 1) << QVector2D(0, 0)
                           << QVector2D(0, 0) << QVector2D(1, 0) << QVector2D(1, 1) // Left
                           << QVector2D(1, 1) << QVector2D(0, 1) << QVector2D(0, 0)
                           << QVector2D(0, 0) << QVector2D(1, 0) << QVector2D(1, 1) // Right
                           << QVector2D(1, 1) << QVector2D(0, 1) << QVector2D(0, 0)
                           << QVector2D(0, 0) << QVector2D(1, 0) << QVector2D(1, 1) // Top
                           << QVector2D(1, 1) << QVector2D(0, 1) << QVector2D(0, 0)
                           << QVector2D(0, 0) << QVector2D(1, 0) << QVector2D(1, 1) // Bottom
                           << QVector2D(1, 1) << QVector2D(0, 1) << QVector2D(0, 0);

    cubeTexture = new QOpenGLTexture(QImage(textures[i]).mirrored());
    // Set nearest filtering mode for texture minification
    cubeTexture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    cubeTexture->setMagnificationFilter(QOpenGLTexture::Linear);


    lightSourceShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/coloringvertexshader.vert");
    lightSourceShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/coloringfragmentshader.frag");
    lightSourceShaderProgram.link();

    spotlightVertices << QVector3D(   0,    1,    0) << QVector3D(-0.5,    0,  0.5) << QVector3D( 0.5,    0,  0.5) // Front
                      << QVector3D(   0,    1,    0) << QVector3D( 0.5,    0, -0.5) << QVector3D(-0.5,    0, -0.5) // Back
                      << QVector3D(   0,    1,    0) << QVector3D(-0.5,    0, -0.5) << QVector3D(-0.5,    0,  0.5) // Left
                      << QVector3D(   0,    1,    0) << QVector3D( 0.5,    0,  0.5) << QVector3D( 0.5,    0, -0.5) // Right
                      << QVector3D(-0.5,    0, -0.5) << QVector3D( 0.5,    0, -0.5) << QVector3D( 0.5,    0,  0.5) // Bottom
                      << QVector3D( 0.5,    0,  0.5) << QVector3D(-0.5,    0,  0.5) << QVector3D(-0.5,    0, -0.5);
    spotlightColors << QVector3D(0.2, 0.2, 0.2) << QVector3D(0.2, 0.2, 0.2) << QVector3D(0.2, 0.2, 0.2) // Front
                    << QVector3D(0.2, 0.2, 0.2) << QVector3D(0.2, 0.2, 0.2) << QVector3D(0.2, 0.2, 0.2) // Back
                    << QVector3D(0.2, 0.2, 0.2) << QVector3D(0.2, 0.2, 0.2) << QVector3D(0.2, 0.2, 0.2) // Left
                    << QVector3D(0.2, 0.2, 0.2) << QVector3D(0.2, 0.2, 0.2) << QVector3D(0.2, 0.2, 0.2) // Right
                    << QVector3D(  1,   1,   1) << QVector3D(  1,   1,   1) << QVector3D(  1,   1,   1) // Bottom
                    << QVector3D(  1,   1,   1) << QVector3D(  1,   1,   1) << QVector3D(  1,   1,   1);
}

void Widget::resizeGL(int width, int height)
{
    if (height == 0)
    {
        height = 1; //Aby nie dzielić przez zero
    }
    pMatrix.setToIdentity();
    pMatrix.perspective(60.0, (float) width / (float) height, 0.001, 1000);
    glViewport(0, 0, width, height);
}

void Widget::paintGL()
{
    if(changed == true)
    {
        delete cubeTexture;
        cubeTexture = nullptr;
        cubeTexture = new QOpenGLTexture(QImage(textures[i]).mirrored());
        // Set nearest filtering mode for texture minification
        cubeTexture->setMinificationFilter(QOpenGLTexture::Nearest);

        // Set bilinear filtering mode for texture magnification
        cubeTexture->setMagnificationFilter(QOpenGLTexture::Linear);
        changed = false;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 mMatrix;
    QMatrix4x4 vMatrix;

    QMatrix4x4 cameraTransformation;

    cameraTransformation.rotate(alpha, 0, 1, 0);
    cameraTransformation.rotate(beta, 1, 0, 0);

    QVector3D cameraPosition = cameraTransformation * QVector3D(0, 0, distance);
    QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);

    vMatrix.lookAt(cameraPosition, QVector3D(0, 0, 0), cameraUpDirection);

    //! [5]
        mMatrix.setToIdentity();

    QMatrix4x4 mvMatrix;
    mvMatrix = vMatrix * mMatrix;

    QMatrix3x3 normalMatrix;
    normalMatrix = mvMatrix.normalMatrix();

    QMatrix4x4 lightTransformation;
    lightTransformation.rotate(lightAngle, 0, 1, 0);

    QVector3D lightPosition = lightTransformation * QVector3D(0, 1, 1);

    cubeShaderProgram.bind();
    cubeTexture->bind();

    cubeShaderProgram.setUniformValue("mvpMatrix", pMatrix * mvMatrix);
    cubeShaderProgram.setUniformValue("mvMatrix", mvMatrix);
    cubeShaderProgram.setUniformValue("normalMatrix", normalMatrix);
    cubeShaderProgram.setUniformValue("lightPosition", vMatrix * lightPosition);

    cubeShaderProgram.setUniformValue("ambientColor", QColor(32, 32, 32));
    cubeShaderProgram.setUniformValue("diffuseColor", QColor(128, 128, 128));
    cubeShaderProgram.setUniformValue("specularColor", QColor(255, 255, 255));
    cubeShaderProgram.setUniformValue("ambientReflection", (GLfloat) 4.0);
    cubeShaderProgram.setUniformValue("diffuseReflection", (GLfloat) 4.0);
    cubeShaderProgram.setUniformValue("specularReflection", (GLfloat) 1.0);
    cubeShaderProgram.setUniformValue("shininess", (GLfloat) 100.0);
    cubeShaderProgram.setUniformValue("texture", 0);


    cubeShaderProgram.setAttributeArray("vertex", cubeVertices.constData());
    cubeShaderProgram.enableAttributeArray("vertex");
    cubeShaderProgram.setAttributeArray("normal", cubeNormals.constData());
    cubeShaderProgram.enableAttributeArray("normal");
    cubeShaderProgram.setAttributeArray("textureCoordinate", cubeTextureCoordinates.constData());
    cubeShaderProgram.enableAttributeArray("textureCoordinate");

    glDrawArrays(GL_TRIANGLES, 0, cubeVertices.size());

    cubeShaderProgram.disableAttributeArray("vertex");
    cubeShaderProgram.disableAttributeArray("normal");
    cubeShaderProgram.disableAttributeArray("textureCoordinate");

    cubeShaderProgram.release();
    cubeTexture->release();

    mMatrix.setToIdentity();
    mMatrix.translate(lightPosition);
    mMatrix.rotate(lightAngle, 0, 1, 0);
    mMatrix.rotate(45, 1, 0, 0);
    mMatrix.scale(0.1);

    lightSourceShaderProgram.bind();

    lightSourceShaderProgram.setUniformValue("mvpMatrix", pMatrix * vMatrix * mMatrix);

    lightSourceShaderProgram.setAttributeArray("vertex", spotlightVertices.constData());
    lightSourceShaderProgram.enableAttributeArray("vertex");

    lightSourceShaderProgram.setAttributeArray("color", spotlightColors.constData());
    lightSourceShaderProgram.enableAttributeArray("color");

    glDrawArrays(GL_TRIANGLES, 0, spotlightVertices.size());

    lightSourceShaderProgram.disableAttributeArray("vertex");

    lightSourceShaderProgram.disableAttributeArray("color");

    lightSourceShaderProgram.release();
    //! [5]
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
        alpha -= deltaX;
        while (alpha < 0)
        {
            alpha += 360;
        }
        while (alpha >= 360)
        {
            alpha -= 360;
        }
        beta -= deltaY;
        while (beta < 0)
        {
            beta += 360;
        }
        while (beta >= 360)
        {
            beta -= 360;
        }
//        beta -= deltaY;
//        if (beta < -90)
//        {
//            beta = -90;
//        }
//        if (beta > 90)
//        {
//            beta = 90;
//        }
        update();
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
            distance *= 1.1;
        } else if (delta > 0)
        {
            distance *= 0.9;
        }
        update();
    }
    event->accept();
}

void Widget::timeout()
{
    lightAngle += 1;
    while (lightAngle >= 360) {
        lightAngle -= 360;
    }
    update();
    QTimer::singleShot(100, this,SLOT(timeout()));
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_1:
            if(i != 0)
            {
                i = 0;
                changed = true;
            }
            break;
        case Qt::Key_2:
            if(i != 1)
            {
                i = 1;
                changed = true;
            }
            break;
        case Qt::Key_3:
            if(i != 2)
            {
                i = 2;
                changed = true;
            }
            break;
        case Qt::Key_4:
            if(i != 3)
            {
                i = 3;
                changed = true;
            }
        break;
        case Qt::Key_5:
            if(i != 4)
            {
                i = 4;
                changed = true;
            }
        break;
    }
}
