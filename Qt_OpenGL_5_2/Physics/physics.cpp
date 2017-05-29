#include "physics.h"

Physics::Physics()
{

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

QVector<DrawableObject*> Physics::checkCollisionsMultiple(QVector<DrawableObject*> objects)
{
    QVector<DrawableObject*> detectedCollisions;

    return detectedCollisions;
}
