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
    void Logic();
    void Draw(Camera camera, Light light, QMatrix4x4 pMatrix);

private:
    OBJManager* objManager;
    QOpenGLShaderProgram* shader;

    QVector<DrawableObject*> objects;
};

#endif // ENVGENERATOR_H
