#include "envgenerator.h"

EnvGenerator::EnvGenerator()
{

}

void EnvGenerator::Init(OBJManager* objManager, QOpenGLShaderProgram* shader)
{
    this->objManager = objManager;
    this->shader = shader;

    DrawableObject test;
    test.Init(shader, objManager->GetModel(":/Objects/planetoid"), ":/Textures/planetoid-texture");
    objects.push_back(test);
}

void EnvGenerator::Logic()
{

}

void EnvGenerator::Draw(Camera camera, Light light, QMatrix4x4 pMatrix)
{
    for(int i=0; i<objects.size(); i++)
    {
        objects[i].Draw(camera, light, pMatrix);
    }
}
