#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <QVector2D>
#include <QVector3D>
#include <QVector>
#include <QFile>
#include <QTextStream>

#include "facedata.h"

using namespace std;

class OBJLoader
{
private:
    QVector<QVector3D> verticesData;
    QVector<QVector3D> normalsData;
    QVector<QVector2D> textureCoordsData;
    QVector<FaceData> facesData;

public:
    OBJLoader();
    ~OBJLoader();

    bool LoadFromFile(QString fileName);

    QVector<QVector3D> GetVerticesData() noexcept {return verticesData;}
    QVector<QVector3D> GetNormalsData() noexcept {return normalsData;}
    QVector<QVector2D> GetTextureCoordsData() noexcept {return textureCoordsData;}
    QVector<FaceData> GetFacesData() noexcept {return facesData;}
private:
    bool parse(QString content);
    bool parseVertices(QString line);
    bool parseTextureCoordinates(QString line);
    bool parseNormals(QString line);
    bool parseFaces(QString line);
};
