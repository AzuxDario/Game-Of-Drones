#include "objmodel.h"

OBJModel::OBJModel(QString name, OBJLoader data)
{
    this->name = name;
    this->data = data;
}

QString OBJModel::GetName()
{
    return name;
}

OBJLoader OBJModel::GetData()
{
    return data;
}
