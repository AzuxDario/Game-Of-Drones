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

    void loadAll(QVector<QString> files);
    OBJModel* getModel(QString name);
};

#endif // OBJMANAGER_H
