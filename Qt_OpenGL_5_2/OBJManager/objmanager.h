#ifndef OBJMANAGER_H
#define OBJMANAGER_H

#include <QVector>
#include "objmodel.h"

class OBJManager
{
public:
    OBJManager();

    void LoadAll(QVector<QString> files);
    OBJModel* GetModel(QString name);

private:
    QVector<OBJModel*> models;
};

#endif // OBJMANAGER_H
