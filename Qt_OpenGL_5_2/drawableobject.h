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
#include "OBJLoader/objloader.h"
#include "lightproperties.h"
#include "OBJManager/objmodel.h"

class DrawableObject : protected QOpenGLFunctions
{
private:
    QVector3D position;
    QVector3D rotation;
    QVector3D scale;

    QMatrix4x4 pMatrix;
    QOpenGLShaderProgram* cubeShaderProgram;
    QOpenGLTexture *texture;
    QVector<QVector3D> verticesData;
    QVector<QVector3D> normalsData;
    QVector<QVector2D> textureCoordsData;
    QOpenGLBuffer graphicCardBuffer;

    LightProperties lightProperties;

    int numberOfVerticles;
    float radius;

public:
    DrawableObject();
    ~DrawableObject();

    void init(QOpenGLShaderProgram* shader, OBJModel* model, QOpenGLTexture* texture);
    void logic(int deltaTime);
    void draw(Camera camera, Light light, QMatrix4x4 pMatrix);

    LightProperties& getLightProperties() noexcept {return lightProperties;}
    QVector3D& getPosition() noexcept {return position;}
    QVector3D& getRotation() noexcept {return rotation;}
    QVector3D& getScale() noexcept {return scale;}
    QVector3D& getMoveSpeed() noexcept {return moveSpeed;}
    QVector3D& getRotationSpeed() noexcept {return rotationSpeed;}
    float getRadius() noexcept {return radius;}

    void setRadius(float value) noexcept {radius = value;}
    void setPosition(QVector3D value) noexcept {position = value;}

    QVector3D moveSpeed;
    QVector3D rotationSpeed;

private:
    void getVerticlesData(OBJLoader data);
    void calculateRadius();
    void initializeGraphicBuffer();
    void assignTexture(QOpenGLTexture* texture);
};

#endif // DRAWABLEOBJECT_H
