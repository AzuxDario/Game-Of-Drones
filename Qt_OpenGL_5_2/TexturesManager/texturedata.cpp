#include "texturedata.h"

TextureData::TextureData(QString name, QOpenGLTexture* texture)
{
    this->name = name;
    this->texture = texture;
}

QString TextureData::GetName()
{
    return name;
}

QOpenGLTexture* TextureData::GetTexture()
{
    return texture;
}
