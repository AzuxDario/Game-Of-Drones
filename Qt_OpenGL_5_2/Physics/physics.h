#ifndef PHYSICS_H
#define PHYSICS_H

#include <QVector>

#include "DrawableObject.h"

class Physics
{
public:
    Physics();

    QVector<DrawableObject*> CheckCollisions(DrawableObject* base, QVector<DrawableObject*> objects);
};

#endif
