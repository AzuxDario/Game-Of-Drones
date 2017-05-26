#include "objloader.h"

OBJLoader::OBJLoader()
{

}

OBJLoader::~OBJLoader()
{

}

bool OBJLoader::LoadFromFile(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
		return false;

    QTextStream stream(&file);
    QString content = stream.readAll();

    return parse(content);
}

bool OBJLoader::parse(QString content)
{
    QVector<QString> tokens = std::move(content.split('\n').toVector());
    for (int i = 0; i < tokens.length(); i++)
	{
        QString line = tokens.at(i);
        QChar lineType = line[0];
        QChar lineSubType = line[1];

        if(lineType == '#')
        {
            continue;
        }
        else if(lineType == 'v')
        {
            bool result;
            if (lineSubType == 't')
                result = parseTextureCoordinates(line);
            else if (lineSubType == 'n')
                result = parseNormals(line);
            else
                result = parseVertices(line);

            if (!result)
            {
                verticesData.clear();
                normalsData.clear();
                textureCoordsData.clear();
                facesData.clear();

                return false;
            }
        }
        else if(lineType == 'f')
        {
            parseFaces(line);
        }
    }

	return true;
}

bool OBJLoader::parseVertices(QString line)
{
    QVector<QString> tokens = std::move(line.split(' ').toVector());
	if (tokens.size() < 4)
		return false;

    QVector3D vData;
    vData.setX(tokens[1].toFloat());
    vData.setY(tokens[2].toFloat());
    vData.setZ(tokens[3].toFloat());

    verticesData.push_back(vData);
	return true;
}

bool OBJLoader::parseTextureCoordinates(QString line)
{
    QVector<QString> tokens = std::move(line.split(' ').toVector());
	if (tokens.size() < 3)
		return false;

    QVector2D vData;
    vData.setX(tokens[1].toFloat());
    vData.setY(tokens[2].toFloat());

    textureCoordsData.push_back(vData);
	return true;
}

bool OBJLoader::parseNormals(QString line)
{
    QVector<QString> tokens = std::move(line.split(' ').toVector());
	if (tokens.size() < 4)
		return false;

    QVector3D vData;
    vData.setX(tokens[1].toFloat());
    vData.setY(tokens[2].toFloat());
    vData.setZ(tokens[3].toFloat());

    normalsData.push_back(vData);
	return true;
}

bool OBJLoader::parseFaces(QString line)
{
    QVector<QString> tokens = std::move(line.split(' ').toVector());
	if (tokens.size() < 4)
		return false;

	FaceData fData;

    QVector<QString> subTokens = std::move(tokens[1].split('/').toVector());
    fData.Vertices.setX(subTokens[0].toFloat());
    fData.Textures.setX(subTokens[1].toFloat());
    fData.Normals.setX(subTokens[2].toFloat());

    subTokens = std::move(tokens[2].split('/').toVector());
    fData.Vertices.setY(subTokens[0].toFloat());
    fData.Textures.setY(subTokens[1].toFloat());
    fData.Normals.setY(subTokens[2].toFloat());

    subTokens = std::move(tokens[3].split('/').toVector());
    fData.Vertices.setZ(subTokens[0].toFloat());
    fData.Textures.setZ(subTokens[1].toFloat());
    fData.Normals.setZ(subTokens[2].toFloat());

    facesData.push_back(fData);
	return true;
}

QVector<QVector3D> OBJLoader::GetVerticesData()
{
    return verticesData;
}

QVector<QVector3D> OBJLoader::GetNormalsData()
{
    return normalsData;
}

QVector<QVector2D> OBJLoader::GetTextureCoordsData()
{
    return textureCoordsData;
}

QVector<FaceData> OBJLoader::GetFacesData()
{
    return facesData;
}
