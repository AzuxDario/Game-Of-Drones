#ifndef TEXTUREDATA_H
#define TEXTUREDATA_H

#include <QString>
#include <QOpenGLTexture>

class TextureData
{
private:
    QString name;
    QOpenGLTexture* texture;

public:
    TextureData(QString name, QOpenGLTexture* texture);

    QString getName();
    QOpenGLTexture* getTexture();
};

#endif // TEXTUREDATA_H
