#include "objmanager.h"

OBJManager::OBJManager()
{

}

void OBJManager::loadAll(QVector<QString> files)
{
    for(int i=0; i<files.size(); i++)
    {
        OBJLoader loader;
        bool result = loader.LoadFromFile(files[i]);

        if(result)
            models.push_back(new OBJModel(files[i], loader));
    }
}

OBJModel* OBJManager::getModel(QString name)
{
    for(int i=0; i<models.size(); i++)
    {
        if(models[i]->getName() == name)
            return models[i];
    }

    return NULL;
}
