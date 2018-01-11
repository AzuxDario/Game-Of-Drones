#include "physics.h"

Physics::Physics()
{

}

bool Physics::checkCollisions(DrawableObject* base, DrawableObject* object)
{
    QVector<DrawableObject*> listOfObjects;
    listOfObjects.push_back(object);

    return checkCollisions(base, listOfObjects).count() > 0;
}

QVector<DrawableObject*> Physics::checkCollisions(DrawableObject* base, QVector<DrawableObject*> objects)
{
    QVector<DrawableObject*> detectedCollisions;
    float baseRadius = base->getRadius();

    for(int i=0; i<objects.size(); i++)
    {
        if(base == objects[i])
            continue;

        float objectRadius = objects[i]->getRadius();
        float distance = base->getPosition().distanceToPoint(objects[i]->getPosition());

        if(distance <= baseRadius + objectRadius)
            detectedCollisions.push_back(objects[i]);
    }

    return detectedCollisions;
}
