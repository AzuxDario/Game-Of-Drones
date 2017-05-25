#include "texturesmanager.h"

TexturesManager::TexturesManager()
{

}

void TexturesManager::LoadAll(QVector<QString> files)
{
    for(int i=0; i<files.size(); i++)
    {
        TextureData* data = new TextureData(files[i], new QOpenGLTexture(QImage(files[i]).mirrored()));
        textures.push_back(data);
    }
}

QOpenGLTexture* TexturesManager::GetTexture(QString name)
{
    for(int i=0; i<textures.size(); i++)
    {
        if(textures[i]->GetName() == name)
            return textures[i]->GetTexture();
    }

    return NULL;
}
