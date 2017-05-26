#include "physics.h"

Physics::Physics()
{

}

QVector<DrawableObject*> Physics::CheckCollisions(DrawableObject* base, QVector<DrawableObject*> objects)
{
    QVector<DrawableObject*> detectedCollisions;
    float baseRadius = base->GetRadius();

    for(int i=0; i<objects.size(); i++)
    {
        float objectRadius = objects[i]->GetRadius();
        float distance = base->GetPosition().distanceToPoint(objects[i]->GetPosition());

        if(distance <= baseRadius + objectRadius)
            detectedCollisions.push_back(objects[i]);
    }

    return detectedCollisions;
}
