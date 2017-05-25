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

#include "camera.h"
#include "light.h"
#include "OBJManager/objmanager.h"
#include "drawableobject.h"
#include "game.h"
#include "EnvGenerator/EnvGenerator.h"

class Widget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

private:
    QMatrix4x4 projectionMatrix;

    QOpenGLShaderProgram cubeShaderProgram;
    QOpenGLShaderProgram lightSourceShaderProgram;
    QVector<QVector3D> spotlightVertices;
    QVector<QVector3D> spotlightColors;

    int numSpotlightVertices;
    QOpenGLBuffer spotlightBuffer;

    QPoint lastMousePosition;
    QTimer paintTimer;

    Camera camera;
    Light light;
    OBJManager objManager;
    DrawableObject skybox;
    EnvGenerator envGenerator;

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    QSize sizeHint() const;
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

public slots:
    void keyPressEvent(QKeyEvent *event);
};

#endif // WIDGET_H
