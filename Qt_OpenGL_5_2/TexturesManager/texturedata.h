#ifndef TEXTUREDATA_H
#define TEXTUREDATA_H

#include <QString>
#include <QOpenGLTexture>

class TextureData
{
public:
    TextureData(QString name, QOpenGLTexture* texture);

    QString GetName();
    QOpenGLTexture* GetTexture();

private:
    QString name;
    QOpenGLTexture* texture;
};

#endif // TEXTUREDATA_H
