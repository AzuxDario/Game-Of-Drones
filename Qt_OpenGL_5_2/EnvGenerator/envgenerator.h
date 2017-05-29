#ifndef ENVGENERATOR_H
#define ENVGENERATOR_H

#include <QOpenGLShaderProgram>
#include "OBJManager/objmanager.h"
#include "camera.h"
#include "light.h"
#include "DrawableObject.h"
#include "TexturesManager/texturesmanager.h"

class EnvGenerator
{
private:
    OBJManager* objManager;
    TexturesManager* texturesManager;
    QOpenGLShaderProgram* shader;
    QVector<DrawableObject*> objects;

    float generatorDistance;
    float destroyDistance;
    float fixPositionMultiplier;

    int maxPlanetoidsCount;
    float maxPlanetoidsRotationSpeed;
    float maxPlanetoidsMoveSpeed;

public:
    EnvGenerator();
    ~EnvGenerator();

    void init(OBJManager* objManager, TexturesManager* texturesManager, QOpenGLShaderProgram* shader);
    void logic(QVector3D playerPosition, int deltaTime);
    void draw(Camera camera, Light light, QMatrix4x4 pMatrix);

    QVector<DrawableObject*> GetObjects();
    void removeObject(DrawableObject* object);
    void removeObjects(QVector<DrawableObject*> objectsToRemove);

private:
    float getRandomNumberWithNegatives(float to);
};

#endif // ENVGENERATOR_H
