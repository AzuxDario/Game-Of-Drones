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
public:
    EnvGenerator();
    ~EnvGenerator();

    void Init(OBJManager* objManager, TexturesManager* texturesManager, QOpenGLShaderProgram* shader);
    void Logic(QVector3D playerPosition, int deltaTime);
    void Draw(Camera camera, Light light, QMatrix4x4 pMatrix);

    QVector<DrawableObject*> GetObjects();
    void RemoveObject(DrawableObject* object);
    void RemoveObjects(QVector<DrawableObject*> objectsToRemove);
private:
    float GetRandomNumberWithNegatives(float to);

    OBJManager* objManager;
    TexturesManager* texturesManager;
    QOpenGLShaderProgram* shader;
    QVector<DrawableObject*> objects;

    int generatorDistance;
    int maxPlanetoidsCount;
    float maxPlanetoidsRotationSpeed;
    float maxPlanetoidsMoveSpeed;
};

#endif // ENVGENERATOR_H
