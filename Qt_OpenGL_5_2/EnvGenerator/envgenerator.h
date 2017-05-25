#ifndef ENVGENERATOR_H
#define ENVGENERATOR_H

#include <QOpenGLShaderProgram>
#include "OBJManager/objmanager.h"
#include "camera.h"
#include "light.h"
#include "DrawableObject.h"

class EnvGenerator
{
public:
    EnvGenerator();
    ~EnvGenerator();

    void Init(OBJManager* objManager, QOpenGLShaderProgram* shader);
    void Logic(QVector3D playerPosition, int deltaTime);
    void Draw(Camera camera, Light light, QMatrix4x4 pMatrix);

private:
    float GetRandomWithNegatives(float to);

    OBJManager* objManager;
    QOpenGLShaderProgram* shader;
    QVector<DrawableObject*> objects;

    int generatorDistance;
    int maxPlanetoidsCount;
    float maxPlanetoidsRotationSpeed;
    float maxPlanetoidsMoveSpeed;
};

#endif // ENVGENERATOR_H
