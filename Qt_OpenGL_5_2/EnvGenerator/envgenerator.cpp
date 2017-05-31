#include "envgenerator.h"

EnvGenerator::EnvGenerator()
{
    generatorDistance = 100;
    destroyDistance = 100;
    fixPositionMultiplier = 2.0f;

    maxPlanetoidsCount = 200;
    maxPlanetoidsRotationSpeed = 0.15f;
    maxPlanetoidsMoveSpeed = 0.025f;
}

EnvGenerator::~EnvGenerator()
{
    for(int i=0; i<objects.size(); i++)
    {
        delete objects[i];
    }

    objects.clear();
}

void EnvGenerator::init(OBJManager* objManager, TexturesManager* texturesManager,
                        QOpenGLShaderProgram* shader)
{
    this->objManager = objManager;
    this->texturesManager = texturesManager;
    this->shader = shader;
}

void EnvGenerator::logic(QVector3D playerPosition, int deltaTime)
{
    for(int i=objects.size() - 1; i >= 0; i--)
    {
        float distance = objects[i]->getPosition().distanceToPoint(playerPosition);
        if(distance >= destroyDistance)
        {
            objects[i]->getPosition().setX(playerPosition.x() + (rand() % (int)(destroyDistance * 2)) - destroyDistance);
            objects[i]->getPosition().setY(playerPosition.y() + (rand() % (int)(destroyDistance * 2)) - destroyDistance);
            objects[i]->getPosition().setZ(playerPosition.z() + (rand() % (int)(destroyDistance * 2)) - destroyDistance);

            continue;
        }

        objects[i]->logic(deltaTime);
    }

    while(objects.size() < maxPlanetoidsCount)
    {
        DrawableObject* planetoid = new DrawableObject();
        planetoid->init(shader, objManager->getModel(":/Objects/planetoid"), texturesManager->getTexture(":/Textures/planetoid"));
        planetoid->getLightProperties().setSpecularReflection(0);
        planetoid->getLightProperties().setAmbientReflection(0.5);
        planetoid->getLightProperties().setAmbientColor(64,64,64);
        planetoid->getLightProperties().setDiffuseReflection(0.8);
        planetoid->getLightProperties().setDiffuseColor(192,192,192);

        planetoid->getRotationSpeed().setX(getRandomNumberWithNegatives(maxPlanetoidsRotationSpeed));
        planetoid->getRotationSpeed().setY(getRandomNumberWithNegatives(maxPlanetoidsRotationSpeed));
        planetoid->getRotationSpeed().setZ(getRandomNumberWithNegatives(maxPlanetoidsRotationSpeed));

        planetoid->getMoveSpeed().setX(getRandomNumberWithNegatives(maxPlanetoidsMoveSpeed));
        planetoid->getMoveSpeed().setY(getRandomNumberWithNegatives(maxPlanetoidsMoveSpeed));
        planetoid->getMoveSpeed().setZ(getRandomNumberWithNegatives(maxPlanetoidsMoveSpeed));

        bool posSet = false;
        while(!posSet || planetoid->getPosition().distanceToPoint(QVector3D(0, 0, 0)) >= generatorDistance)
        {
            planetoid->getPosition().setX(getRandomNumberWithNegatives(destroyDistance));
            planetoid->getPosition().setY(getRandomNumberWithNegatives(destroyDistance));
            planetoid->getPosition().setZ(getRandomNumberWithNegatives(destroyDistance));

            posSet = true;
        }

        planetoid->getPosition() += QVector3D(playerPosition);
        objects.push_back(planetoid);
    }
}

void EnvGenerator::draw(Camera camera, Light light, QMatrix4x4 pMatrix)
{
    for(int i=0; i<objects.size(); i++)
    {
        objects[i]->draw(camera, light, pMatrix);
    }
}

float EnvGenerator::getRandomNumberWithNegatives(float to)
{
    int sign = 2 * (rand() % 2) - 1;
    return sign * (float)rand() / (float)(RAND_MAX / to);
}

QVector<DrawableObject*> EnvGenerator::GetObjects()
{
    return objects;
}

void EnvGenerator::removeObject(DrawableObject* object)
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

void EnvGenerator::removeObjects(QVector<DrawableObject*> objectsToRemove)
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
