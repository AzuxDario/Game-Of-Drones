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
#include "lightproperties.h"
#include "OBJManager/objmodel.h"

class DrawableObject : protected QOpenGLFunctions
{
public:
    DrawableObject();
    ~DrawableObject();

    void Init(QOpenGLShaderProgram* shader, OBJModel* model, QString texture);
    void Logic();
    void Draw(Camera camera, Light light, QMatrix4x4 pMatrix);
    void Draw(QOpenGLShaderProgram & shader);
    LightProperties& getLightProperties();

    QVector3D& GetPosition();
    QVector3D& GetRotation();

    QVector3D& GetMoveSpeed();
    QVector3D& GetRotationSpeed();
private:
    QVector3D position;
    QVector3D rotation;

    QVector3D moveSpeed;
    QVector3D rotationSpeed;

    QMatrix4x4 pMatrix;
    QOpenGLShaderProgram* cubeShaderProgram;
    QOpenGLTexture *cubeTexture;
    QVector<QVector3D> verticesData;
    QVector<QVector3D> normalsData;
    QVector<QVector2D> textureCoordsData;
    QOpenGLBuffer graphicCardBuffer;

    LightProperties lightProperties;

    int numberOfVerticles;
};

#endif // DRAWABLEOBJECT_H
