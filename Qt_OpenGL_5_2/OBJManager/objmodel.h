#ifndef OBJMODEL_H
#define OBJMODEL_H

#include "OBJLoader/objloader.h"

class OBJModel
{
private:
    QString name;
    OBJLoader data;

public:
    OBJModel(QString name, OBJLoader data);

    QString GetName();
    OBJLoader GetData();
};

#endif // OBJMODEL_H
