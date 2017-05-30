#include "objmodel.h"

OBJModel::OBJModel(QString name, OBJLoader data)
{
    this->name = name;
    this->data = data;
}

QString OBJModel::getName()
{
    return name;
}

OBJLoader OBJModel::getData()
{
    return data;
}
