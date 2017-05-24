#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H
#include "drawableobject.h"


class MovableObject : public DrawableObject
{
public:
    MovableObject();
    QVector3D Motion;
};

#endif // MOVABLEOBJECT_H
