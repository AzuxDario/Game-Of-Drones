#ifndef TEXTURESMANAGER_H
#define TEXTURESMANAGER_H

#include <QVector>
#include <QImage>
#include <QOpenGLTexture>
#include "texturedata.h"

class TexturesManager
{
public:
    TexturesManager();

    void LoadAll(QVector<QString> files);
    QOpenGLTexture* GetTexture(QString name);

private:
    QVector<TextureData*> textures;
};

#endif // TEXTURESMANAGER_H
