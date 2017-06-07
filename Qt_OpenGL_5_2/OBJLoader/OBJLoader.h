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

    QVector<QVector3D> getVerticesData() noexcept {return verticesData;}
    QVector<QVector3D> getNormalsData() noexcept {return normalsData;}
    QVector<QVector2D> getTextureCoordsData() noexcept {return textureCoordsData;}
    QVector<FaceData> getFacesData() noexcept {return facesData;}

    bool isNormalsLoaded() noexcept {return normalsData.size() == 0 ? false : true;}

private:
    bool parse(QString content);
    bool parseVertices(QString line);
    bool parseTextureCoordinates(QString line);
    bool parseNormals(QString line);
    bool parseFaces(QString line);
};
