#include "envgenerator.h"

EnvGenerator::EnvGenerator()
{
    generatorDistance = 500;
    maxPlanetoidsCount = 150;
    maxPlanetoidsRotationSpeed = 4;
    maxPlanetoidsMoveSpeed = 0.6f;
}

EnvGenerator::~EnvGenerator()
{
    for(int i=0; i<objects.size(); i++)
    {
        delete objects[i];
    }

    objects.clear();
}

void EnvGenerator::Init(OBJManager* objManager, QOpenGLShaderProgram* shader)
{
    this->objManager = objManager;
    this->shader = shader;
}

void EnvGenerator::Logic(QVector3D playerPosition)
{
    for(int i=objects.size() - 1; i >= 0; i--)
    {
        float distance = objects[i]->GetPosition().distanceToPoint(playerPosition);
        if(distance > generatorDistance)
        {
            delete objects[i];
            objects.remove(i);
            continue;
        }

        objects[i]->Logic();
    }

    while(objects.size() < maxPlanetoidsCount)
    {
        DrawableObject* planetoid = new DrawableObject();
        planetoid->Init(shader, objManager->GetModel(":/Objects/planetoid"), ":/Textures/planetoid-texture");

        planetoid->GetRotationSpeed().setX(GetRandomWithNegatives(maxPlanetoidsRotationSpeed));
        planetoid->GetRotationSpeed().setY(GetRandomWithNegatives(maxPlanetoidsRotationSpeed));
        planetoid->GetRotationSpeed().setZ(GetRandomWithNegatives(maxPlanetoidsRotationSpeed));

        planetoid->GetMoveSpeed().setX(GetRandomWithNegatives(maxPlanetoidsMoveSpeed));
        planetoid->GetMoveSpeed().setY(GetRandomWithNegatives(maxPlanetoidsMoveSpeed));
        planetoid->GetMoveSpeed().setZ(GetRandomWithNegatives(maxPlanetoidsMoveSpeed));

        planetoid->GetPosition().setX(GetRandomWithNegatives(generatorDistance));
        planetoid->GetPosition().setY(GetRandomWithNegatives(generatorDistance));
        planetoid->GetPosition().setZ(GetRandomWithNegatives(generatorDistance));

        objects.push_back(planetoid);
    }
}

void EnvGenerator::Draw(Camera camera, Light light, QMatrix4x4 pMatrix)
{
    for(int i=0; i<objects.size(); i++)
    {
        objects[i]->Draw(camera, light, pMatrix);
    }
}

float EnvGenerator::GetRandomWithNegatives(float to)
{
    int sign = 2 * (rand() % 2) - 1;
    return sign * (float)rand() / (float)(RAND_MAX / to);
}
