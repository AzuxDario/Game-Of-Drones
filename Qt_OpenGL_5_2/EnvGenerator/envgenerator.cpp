#include "envgenerator.h"

EnvGenerator::EnvGenerator()
{
    generatorDistance = 50;
    maxPlanetoidsCount = 400;
    maxPlanetoidsRotationSpeed = 0.05f;
    maxPlanetoidsMoveSpeed = 0.005f;
}

EnvGenerator::~EnvGenerator()
{
    for(int i=0; i<objects.size(); i++)
    {
        delete objects[i];
    }

    objects.clear();
}

void EnvGenerator::Init(OBJManager* objManager, TexturesManager* texturesManager,
                        QOpenGLShaderProgram* shader)
{
    this->objManager = objManager;
    this->texturesManager = texturesManager;
    this->shader = shader;
}

void EnvGenerator::Logic(QVector3D playerPosition, int deltaTime)
{
    for(int i=objects.size() - 1; i >= 0; i--)
    {
        float distance = objects[i]->GetPosition().distanceToPoint(playerPosition);
        if(distance > generatorDistance * 1.5f)
        {
            delete objects[i];
            objects.remove(i);

            continue;
        }

        objects[i]->Logic(deltaTime);
    }

    while(objects.size() < maxPlanetoidsCount)
    {
        DrawableObject* planetoid = new DrawableObject();
        planetoid->Init(shader, objManager->GetModel(":/Objects/planetoid"), texturesManager->GetTexture(":/Textures/planetoid"));
        planetoid->getLightProperties().setSpecularReflection(0);
        planetoid->getLightProperties().setAmbientReflection(0.5);
        planetoid->getLightProperties().setDiffuseReflection(0.8);

        planetoid->GetRotationSpeed().setX(GetRandomNumberWithNegatives(maxPlanetoidsRotationSpeed));
        planetoid->GetRotationSpeed().setY(GetRandomNumberWithNegatives(maxPlanetoidsRotationSpeed));
        planetoid->GetRotationSpeed().setZ(GetRandomNumberWithNegatives(maxPlanetoidsRotationSpeed));

        planetoid->GetMoveSpeed().setX(GetRandomNumberWithNegatives(maxPlanetoidsMoveSpeed));
        planetoid->GetMoveSpeed().setY(GetRandomNumberWithNegatives(maxPlanetoidsMoveSpeed));
        planetoid->GetMoveSpeed().setZ(GetRandomNumberWithNegatives(maxPlanetoidsMoveSpeed));

        planetoid->GetPosition().setX(GetRandomNumberWithNegatives(generatorDistance));
        planetoid->GetPosition().setY(GetRandomNumberWithNegatives(generatorDistance));
        planetoid->GetPosition().setZ(GetRandomNumberWithNegatives(generatorDistance));

        while(planetoid->GetPosition().distanceToPoint(playerPosition) <= generatorDistance)
        {
            planetoid->GetPosition() *= 1.1f;
        }

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

float EnvGenerator::GetRandomNumberWithNegatives(float to)
{
    int sign = 2 * (rand() % 2) - 1;
    return sign * (float)rand() / (float)(RAND_MAX / to);
}

QVector<DrawableObject*> EnvGenerator::GetObjects()
{
    return objects;
}

void EnvGenerator::RemoveObject(DrawableObject* object)
{
    for(int i=0; i<objects.size(); i++)
    {
        if(objects[i] == object)
        {
            delete objects[i];
            objects.remove(i);

            break;
        }
    }
}

void EnvGenerator::RemoveObjects(QVector<DrawableObject*> objectsToRemove)
{
    for(int i=0; i<objects.size(); i++)
    {
        for(int q=0; q<objectsToRemove.size(); q++)
        {
            if(objects[i] == objectsToRemove[q])
            {
                delete objects[i];
                objects.remove(i);

                break;
            }
        }
    }
}
