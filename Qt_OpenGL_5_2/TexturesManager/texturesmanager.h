#ifndef TEXTURESMANAGER_H
#define TEXTURESMANAGER_H

#include <QVector>
#include <QImage>
#include <QOpenGLTexture>
#include "texturedata.h"

class TexturesManager
{
private:
    QVector<TextureData*> textures;

public:
    TexturesManager();

    void LoadAll(QVector<QString> files);
    QOpenGLTexture* GetTexture(QString name);
};

#endif // TEXTURESMANAGER_H
