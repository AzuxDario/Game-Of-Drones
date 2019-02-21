#ifndef OBJMODEL_H
#define OBJMODEL_H

#include "Engine/Objects/ObjectsLoader/OBJLoader.h"

class OBJModel
{
private:
    QString name;
    OBJLoader data;

public:
    OBJModel(QString name, OBJLoader data);

    QString getName();
    OBJLoader getData();
};

#endif // OBJMODEL_H
