#include "texturesmanager.h"

TexturesManager::TexturesManager()
{

}

void TexturesManager::loadAll(QVector<QString> files)
{
    for(int i=0; i<files.size(); i++)
    {
        TextureData* data = new TextureData(files[i], new QOpenGLTexture(QImage(files[i]).mirrored()));
        textures.push_back(data);
    }
}

QOpenGLTexture* TexturesManager::getTexture(QString name)
{
    for(int i=0; i<textures.size(); i++)
    {
        if(textures[i]->getName() == name)
            return textures[i]->getTexture();
    }

    return NULL;
}
