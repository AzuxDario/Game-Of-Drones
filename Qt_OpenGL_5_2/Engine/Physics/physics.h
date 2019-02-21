#ifndef PHYSICS_H
#define PHYSICS_H

#include <QVector>

#include "Engine/Objects/drawableobject.h"

class Physics
{
private:

public:
    Physics();

    bool checkCollisions(DrawableObject* base, DrawableObject* object);
    QVector<DrawableObject*> checkCollisions(DrawableObject* base, QVector<DrawableObject*> objects);
};

#endif
