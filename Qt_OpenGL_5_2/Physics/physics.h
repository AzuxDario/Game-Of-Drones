#ifndef PHYSICS_H
#define PHYSICS_H

#include <QVector>

#include "DrawableObject.h"

class Physics
{
private:

public:
    Physics();

    QVector<DrawableObject*> checkCollisions(DrawableObject* base, QVector<DrawableObject*> objects);
};

#endif
