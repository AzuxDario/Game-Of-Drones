#include "texturedata.h"

TextureData::TextureData(QString name, QOpenGLTexture* texture)
{
    this->name = name;
    this->texture = texture;
}

QString TextureData::getName()
{
    return name;
}

QOpenGLTexture* TextureData::getTexture()
{
    return texture;
}
