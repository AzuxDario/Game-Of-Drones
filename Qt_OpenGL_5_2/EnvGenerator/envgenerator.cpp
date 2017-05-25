#include "envgenerator.h"

EnvGenerator::EnvGenerator()
{

}

void EnvGenerator::Init(OBJManager* objManager, QOpenGLShaderProgram* shader)
{
    this->objManager = objManager;
    this->shader = shader;
}

void EnvGenerator::Logic()
{

}

void EnvGenerator::Draw(Camera camera, Light light, QMatrix4x4 pMatrix)
{

}
