#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLTexture>
#include <QTimer>

class Widget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

private:
    QVector<QString> textures;

    QMatrix4x4 pMatrix;

    QOpenGLShaderProgram lightingShaderProgram;
    QVector<QVector3D> cubeVertices;
    QVector<QVector3D> cubeNormals;
    QVector<QVector2D> cubeTextureCoordinates;
    QOpenGLTexture *cubeTexture;
    QOpenGLShaderProgram coloringShaderProgram;
    QVector<QVector3D> spotlightVertices;
    QVector<QVector3D> spotlightColors;
    double lightAngle;

    int i;
    bool changed;
    double alpha;
    double beta;
    double distance;
    QPoint lastMousePosition;

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
    void timeout();
    void keyPressEvent(QKeyEvent *event);
};

#endif // WIDGET_H
