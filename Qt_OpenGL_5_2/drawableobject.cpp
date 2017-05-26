#include "drawableobject.h"

DrawableObject::DrawableObject() : texture(0)
{
    texture = nullptr;
    numberOfVerticles = 0;
}

DrawableObject::~DrawableObject()
{

}

void DrawableObject::Init(QOpenGLShaderProgram* shader, OBJModel* model, QOpenGLTexture* texture)
{
    initializeOpenGLFunctions();
    cubeShaderProgram = shader;

    OBJLoader data = model->GetData();
    int facesCount = data.GetFacesData().size();

    for(int i=0; i<facesCount; i++)
    {
        FaceData face = data.GetFacesData().at(i);

        verticesData << data.GetVerticesData().at(face.Vertices.x() - 1)
                     << data.GetVerticesData().at(face.Vertices.y() - 1)
                     << data.GetVerticesData().at(face.Vertices.z() - 1);

        normalsData << data.GetNormalsData().at(face.Normals.x() - 1)
                    << data.GetNormalsData().at(face.Normals.y() - 1)
                    << data.GetNormalsData().at(face.Normals.z() - 1);

        textureCoordsData << data.GetTextureCoordsData().at(face.Textures.x() - 1)
                          << data.GetTextureCoordsData().at(face.Textures.y() - 1)
                          << data.GetTextureCoordsData().at(face.Textures.z() - 1);
    }

    float max = 0;
    float min = 0;

    for(int i=0; i<verticesData.size(); i++)
    {
        max = qMax(max, qMax(qMax(verticesData[i].x(), verticesData[i].y()), verticesData[i].z()));
        min = qMin(min, qMin(qMin(verticesData[i].x(), verticesData[i].y()), verticesData[i].z()));
    }

    radius = qMax(abs(max), abs(min));

    numberOfVerticles = verticesData.count(); //Ilość werteksów, ilość normalnych i punktów tekstury jest taka sama

    graphicCardBuffer.create();
    graphicCardBuffer.bind();
    graphicCardBuffer.allocate(numberOfVerticles * (3 + 3 + 2) * sizeof(GLfloat));

    int offset = 0;
    graphicCardBuffer.write(offset, verticesData.constData(), numberOfVerticles * 3 * sizeof(GLfloat));
    offset += numberOfVerticles * 3 * sizeof(GLfloat);
    graphicCardBuffer.write(offset, normalsData.constData(), numberOfVerticles * 3 * sizeof(GLfloat));
    offset += numberOfVerticles * 3 * sizeof(GLfloat);
    graphicCardBuffer.write(offset, textureCoordsData.constData(), numberOfVerticles * 2 * sizeof(GLfloat));

    graphicCardBuffer.release();

    this->texture = texture;
    this->texture->setMinificationFilter(QOpenGLTexture::Nearest);
    this->texture->setMagnificationFilter(QOpenGLTexture::Linear);
}

void DrawableObject::Logic(int deltaTime)
{
    position += (moveSpeed * deltaTime);
    rotation += (rotationSpeed * deltaTime);
}

void DrawableObject::Draw(Camera camera, Light light, QMatrix4x4 pMatrix)
{
    QMatrix4x4 vMatrix = camera.GetMatrix();
    QMatrix4x4 mvMatrix = vMatrix;

    mvMatrix.translate(position.x(), position.y(), position.z());
    mvMatrix.rotate(rotation.x(), 1, 0, 0);
    mvMatrix.rotate(rotation.y(), 0, 1, 0);
    mvMatrix.rotate(rotation.z(), 0, 0, 1);

    QMatrix3x3 normalMatrix;
    normalMatrix = mvMatrix.normalMatrix();

    cubeShaderProgram->bind();
    texture->bind();

    cubeShaderProgram->setUniformValue("mvpMatrix", pMatrix * mvMatrix);
    cubeShaderProgram->setUniformValue("mvMatrix", mvMatrix);
    cubeShaderProgram->setUniformValue("normalMatrix", normalMatrix);
    cubeShaderProgram->setUniformValue("lightPosition", vMatrix * light.getPosition());

    cubeShaderProgram->setUniformValue("ambientColor", lightProperties.getAmbientColor());
    cubeShaderProgram->setUniformValue("diffuseColor", lightProperties.getDiffuseColor());
    cubeShaderProgram->setUniformValue("specularColor", lightProperties.getSpecularColor());
    cubeShaderProgram->setUniformValue("ambientReflection", lightProperties.getAmbientReflection());
    cubeShaderProgram->setUniformValue("diffuseReflection", lightProperties.getDiffuseReflection());
    cubeShaderProgram->setUniformValue("specularReflection", lightProperties.getSpecularReflection());
    cubeShaderProgram->setUniformValue("shininess", lightProperties.getShininess());
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
    texture->release();
}

void DrawableObject::Draw(QOpenGLShaderProgram &shader)
{

}

