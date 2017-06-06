#include "drawableobject.h"

DrawableObject::DrawableObject() : texture(0)
{
    position = QVector3D(0.0,0.0,0.0);
    rotation = QVector3D(0.0,0.0,0.0);
    moveSpeed = QVector3D(0.0,0.0,0.0);
    rotationSpeed = QVector3D(0.0,0.0,0.0);
    texture = nullptr;
    numberOfVerticles = 0;
}

DrawableObject::~DrawableObject()
{

}

void DrawableObject::getVerticlesData(OBJLoader data)
{
    int facesCount = data.getFacesData().size();

    for(int i=0; i<facesCount; i++)
    {
        FaceData face = data.getFacesData().at(i);

        QVector3D v1 = data.getVerticesData().at(face.vertices.x() - 1);
        QVector3D v2 = data.getVerticesData().at(face.vertices.y() - 1);
        QVector3D v3 = data.getVerticesData().at(face.vertices.z() - 1);

        verticesData << v1 << v2 << v3 ;

        QVector3D normal = QVector3D::normal(v1, v2, v3);

        normalsData << normal << normal << normal;

        //normalsData << data.getNormalsData().at(face.normals.x() - 1)
        //            << data.getNormalsData().at(face.normals.y() - 1)
        //            << data.getNormalsData().at(face.normals.z() - 1);

        //normalsData =

        textureCoordsData << data.getTextureCoordsData().at(face.textures.x() - 1)
                          << data.getTextureCoordsData().at(face.textures.y() - 1)
                          << data.getTextureCoordsData().at(face.textures.z() - 1);
    }
}

void DrawableObject::calculateRadius()
{
    float max = 0;
    float min = 0;

    for(int i=0; i<verticesData.size(); i++)
    {
        max = qMax(max, qMax(qMax(verticesData[i].x(), verticesData[i].y()), verticesData[i].z()));
        min = qMin(min, qMin(qMin(verticesData[i].x(), verticesData[i].y()), verticesData[i].z()));
    }

    radius = qMax(abs(max), abs(min));
}

void DrawableObject::initializeGraphicBuffer()
{
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
}

void DrawableObject::assignTexture(QOpenGLTexture* texture)
{
    this->texture = texture;
    this->texture->setMinificationFilter(QOpenGLTexture::Nearest);
    this->texture->setMagnificationFilter(QOpenGLTexture::Linear);
}

void DrawableObject::init(QOpenGLShaderProgram* shader, OBJModel* model, QOpenGLTexture* texture)
{
    initializeOpenGLFunctions();

    cubeShaderProgram = shader;
    OBJLoader data = model->getData();
    getVerticlesData(data);
    calculateRadius();
    numberOfVerticles = verticesData.count(); //Ilość werteksów, ilość normalnych i punktów tekstury jest taka sama
    initializeGraphicBuffer();
    assignTexture(texture);
}

void DrawableObject::logic(int deltaTime)
{
    position += (moveSpeed * ((float)deltaTime / 16.0));
    rotation += (rotationSpeed * ((float)deltaTime / 16.0));
}

void DrawableObject::draw(Camera camera, Light light, QMatrix4x4 pMatrix)
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
