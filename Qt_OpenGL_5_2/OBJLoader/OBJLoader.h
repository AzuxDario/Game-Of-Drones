#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <QVector2D>
#include <QVector3D>
#include <QVector>
#include <QFile>
#include <QTextStream>

#include "FaceData.h"

using namespace std;

class OBJLoader
{
public:
	OBJLoader();
	~OBJLoader();

    bool LoadFromFile(QString fileName);

    QVector<QVector3D> VerticesData;
    QVector<QVector3D> NormalsData;
    QVector<QVector2D> TexturesData;
    vector<FaceData> FacesData;
private:
    QVector<QString> splitByChar(QString line, QChar separator);

    bool parse(QString content);
    bool parseVertices(QString line);
    bool parseTextureCoordinates(QString line);
    bool parseNormals(QString line);
    bool parseFaces(QString line);
};
