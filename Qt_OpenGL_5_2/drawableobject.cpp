#include "drawableobject.h"

DrawableObject::DrawableObject() : cubeTexture(0)
{
    cubeTexture = nullptr;
    SpecularReflection = 1;
    numberOfVerticles = 0;
}

void DrawableObject::Init(QOpenGLShaderProgram* shader, QString objFile, QString texture)
{
    initializeOpenGLFunctions();

    if(!objLoader.LoadFromFile(objFile))
        return;

    cubeShaderProgram = shader;

    for(unsigned int i=0; i<objLoader.FacesData.size(); i++)
    {
        FaceData face = objLoader.FacesData.at(i);

        cubeVertices << objLoader.VerticesData.at(face.Vertices.x() - 1)
                     << objLoader.VerticesData.at(face.Vertices.y() - 1)
                     << objLoader.VerticesData.at(face.Vertices.z() - 1);

        cubeNormals << objLoader.NormalsData.at(face.Normals.x() - 1)
                    << objLoader.NormalsData.at(face.Normals.y() - 1)
                    << objLoader.NormalsData.at(face.Normals.z() - 1);

        textureCoords << objLoader.TexturesData.at(face.Textures.x() - 1)
                       << objLoader.TexturesData.at(face.Textures.y() - 1)
                       << objLoader.TexturesData.at(face.Textures.z() - 1);
    }
    numberOfVerticles = cubeVertices.count(); //Ilość werteksów, ilość normalnych i punktów tekstury jest taka sama

    graphicCardBuffer.create();
    graphicCardBuffer.bind();
    graphicCardBuffer.allocate(numberOfVerticles * (3 + 3 + 2) * sizeof(GLfloat));

    int offset = 0;
    graphicCardBuffer.write(offset, cubeVertices.constData(), numberOfVerticles * 3 * sizeof(GLfloat));
    offset += numberOfVerticles * 3 * sizeof(GLfloat);
    graphicCardBuffer.write(offset, cubeNormals.constData(), numberOfVerticles * 3 * sizeof(GLfloat));
    offset += numberOfVerticles * 3 * sizeof(GLfloat);
    graphicCardBuffer.write(offset, textureCoords.constData(), numberOfVerticles * 2 * sizeof(GLfloat));

    graphicCardBuffer.release();

    cubeTexture = new QOpenGLTexture(QImage(texture).mirrored());
    cubeTexture->setMinificationFilter(QOpenGLTexture::Nearest);
    cubeTexture->setMagnificationFilter(QOpenGLTexture::Linear);
}

void DrawableObject::Draw(Camera camera, Light light, QMatrix4x4 pMatrix)
{
    QMatrix4x4 vMatrix = camera.GetMatrix();
    QMatrix4x4 mvMatrix = vMatrix;

    mvMatrix.translate(Position.x(), Position.y(), Position.z());
    mvMatrix.rotate(Rotation.x(), 1, 0, 0);
    mvMatrix.rotate(Rotation.y(), 0, 1, 0);
    mvMatrix.rotate(Rotation.z(), 0, 0, 1);

    QMatrix3x3 normalMatrix;
    normalMatrix = mvMatrix.normalMatrix();

    cubeShaderProgram->bind();
    cubeTexture->bind();

    cubeShaderProgram->setUniformValue("mvpMatrix", pMatrix * mvMatrix);
    cubeShaderProgram->setUniformValue("mvMatrix", mvMatrix);
    cubeShaderProgram->setUniformValue("normalMatrix", normalMatrix);
    cubeShaderProgram->setUniformValue("lightPosition", vMatrix * light.Position);

    cubeShaderProgram->setUniformValue("ambientColor", QColor(32, 32, 32));
    cubeShaderProgram->setUniformValue("diffuseColor", QColor(128, 128, 128));
    cubeShaderProgram->setUniformValue("specularColor", QColor(255, 255, 255));
    cubeShaderProgram->setUniformValue("ambientReflection", (GLfloat) 4.0);
    cubeShaderProgram->setUniformValue("diffuseReflection", (GLfloat) 4.0);
    cubeShaderProgram->setUniformValue("specularReflection", (GLfloat) SpecularReflection);
    cubeShaderProgram->setUniformValue("shininess", (GLfloat) 100.0);
    cubeShaderProgram->setUniformValue("texture", 0);

    graphicCardBuffer.bind();
    int offset = 0;
    cubeShaderProgram->setAttributeBuffer("vertex", GL_FLOAT, offset, 3, 0);
    cubeShaderProgram->enableAttributeArray("vertex");
    offset += numberOfVerticles * 3 * sizeof(GLfloat);
    cubeShaderProgram->setAttributeBuffer("normal", GL_FLOAT, offset, 3, 0);
    cubeShaderProgram->enableAttributeArray("normal");
    offset += numberOfVerticles * 3 * sizeof(GLfloat);
    cubeShaderProgram->setAttributeBuffer("textureCoordinate", GL_FLOAT, offset, 2, 0);
    cubeShaderProgram->enableAttributeArray("textureCoordinate");
    graphicCardBuffer.release();

    glDrawArrays(GL_TRIANGLES, 0, numberOfVerticles);

    cubeShaderProgram->disableAttributeArray("vertex");
    cubeShaderProgram->disableAttributeArray("normal");
    cubeShaderProgram->disableAttributeArray("textureCoordinate");

    cubeShaderProgram->release();
    cubeTexture->release();
}

void DrawableObject::Draw(QOpenGLShaderProgram &shader)
{

}
