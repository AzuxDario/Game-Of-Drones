#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

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
#include "OBJLoader/OBJLoader.h"

class DrawableObject : protected QOpenGLFunctions
{
public:
    DrawableObject();
    void Init(QOpenGLShaderProgram* shader, QString objFile, QString texture);
    void Draw(Camera camera, Light light, QMatrix4x4 pMatrix);
    void Draw(QOpenGLShaderProgram & shader);

    QVector3D Position;
    QVector3D Rotation;
    float SpecularReflection;
private:
    QMatrix4x4 pMatrix;
    QOpenGLShaderProgram* cubeShaderProgram;
    QOpenGLTexture *cubeTexture;
    QVector<QVector3D> cubeVertices;
    QVector<QVector3D> cubeNormals;
    QVector<QVector2D> textureCoords;
    QOpenGLBuffer graphicCardBuffer;

    OBJLoader objLoader;

    int numberOfVerticles;
};

#endif // DRAWABLEOBJECT_H
