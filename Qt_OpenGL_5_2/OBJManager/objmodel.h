#ifndef OBJMODEL_H
#define OBJMODEL_H

#include "OBJLoader/objloader.h"

class OBJModel
{
public:
    OBJModel(QString name, OBJLoader data);

    QString GetName();
    OBJLoader GetData();

private:
    QString name;
    OBJLoader data;
};

#endif // OBJMODEL_H
