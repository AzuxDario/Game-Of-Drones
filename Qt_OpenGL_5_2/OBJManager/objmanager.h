#ifndef OBJMANAGER_H
#define OBJMANAGER_H

#include <QVector>
#include "objmodel.h"

class OBJManager
{
private:
    QVector<OBJModel*> models;

public:
    OBJManager();

    void LoadAll(QVector<QString> files);
    OBJModel* GetModel(QString name);
};

#endif // OBJMANAGER_H
