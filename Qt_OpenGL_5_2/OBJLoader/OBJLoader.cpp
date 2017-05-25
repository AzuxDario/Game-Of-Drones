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
    QVector<QString> tokens = splitByChar(content, '\n');
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
    QVector<QString> tokens = splitByChar(line, ' ');
	if (tokens.size() < 4)
		return false;

	char *e;

    QVector3D vData;
    vData.setX(strtod(tokens[1].toUtf8().constData(), &e));
    vData.setY(strtod(tokens[2].toUtf8().constData(), &e));
    vData.setZ(strtod(tokens[3].toUtf8().constData(), &e));

    verticesData.push_back(vData);
	return true;
}

bool OBJLoader::parseTextureCoordinates(QString line)
{
    QVector<QString> tokens = splitByChar(line, ' ');
	if (tokens.size() < 3)
		return false;

	char *e;

    QVector2D vData;
    vData.setX(strtod(tokens[1].toUtf8().constData(), &e));
    vData.setY(strtod(tokens[2].toUtf8().constData(), &e));

    textureCoordsData.push_back(vData);
	return true;
}

bool OBJLoader::parseNormals(QString line)
{
    QVector<QString> tokens = splitByChar(line, ' ');
	if (tokens.size() < 4)
		return false;

	char *e;

    QVector3D vData;
    vData.setX(strtod(tokens[1].toUtf8().constData(), &e));
    vData.setY(strtod(tokens[2].toUtf8().constData(), &e));
    vData.setZ(strtod(tokens[3].toUtf8().constData(), &e));

    normalsData.push_back(vData);
	return true;
}

bool OBJLoader::parseFaces(QString line)
{
    QVector<QString> tokens = splitByChar(line, ' ');
	if (tokens.size() < 4)
		return false;

	FaceData fData;
	char *e;

    QVector<QString> subTokens = splitByChar(tokens[1], '/');
    fData.Vertices.setX(strtod(subTokens[0].toUtf8().constData(), &e));
    fData.Textures.setX(strtod(subTokens[1].toUtf8().constData(), &e));
    fData.Normals.setX(strtod(subTokens[2].toUtf8().constData(), &e));

	subTokens = splitByChar(tokens[2], '/');
    fData.Vertices.setY(strtod(subTokens[0].toUtf8().constData(), &e));
    fData.Textures.setY(strtod(subTokens[1].toUtf8().constData(), &e));
    fData.Normals.setY(strtod(subTokens[2].toUtf8().constData(), &e));

	subTokens = splitByChar(tokens[3], '/');
    fData.Vertices.setZ(strtod(subTokens[0].toUtf8().constData(), &e));
    fData.Textures.setZ(strtod(subTokens[1].toUtf8().constData(), &e));
    fData.Normals.setZ(strtod(subTokens[2].toUtf8().constData(), &e));

    facesData.push_back(fData);
	return true;
}

QVector<QString> OBJLoader::splitByChar(QString line, QChar separator)
{
    QVector<QString> result;

    QString expression = "(";
    expression += separator;
    expression += ")";

    QRegExp regexExpression(expression);
    QStringList lines = line.split(regexExpression);

    for(int i=0; i<lines.size(); i++)
    {
        result.push_back(lines[i]);
    }

	return result;
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
