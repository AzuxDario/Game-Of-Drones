#include "drawableobject.h"

DrawableObject::DrawableObject() : cubeTexture(0)
{
    cubeTexture = nullptr;
    numberOfVerticles = 0;

    lightProperties.setAmbientColor(QColor(32, 32, 32));
    lightProperties.setDiffuseColor(QColor(128, 128, 128));
    lightProperties.setSpecularColor(QColor(255, 255, 255));
    lightProperties.setAmbientReflection(1);
    lightProperties.setDiffuseReflection(1);
    lightProperties.setSpecularReflection(1);
    lightProperties.setShininess(100);
}

void DrawableObject::Init(QOpenGLShaderProgram* shader, OBJModel* model, QString texture)
{
    initializeOpenGLFunctions();
    cubeShaderProgram = shader;

    OBJLoader data = model->GetData();
    for(unsigned int i=0; i<data.FacesData.size(); i++)
    {
        FaceData face = data.FacesData.at(i);

        verticesData << data.VerticesData.at(face.Vertices.x() - 1)
                     << data.VerticesData.at(face.Vertices.y() - 1)
                     << data.VerticesData.at(face.Vertices.z() - 1);

        normalsData << data.NormalsData.at(face.Normals.x() - 1)
                    << data.NormalsData.at(face.Normals.y() - 1)
                    << data.NormalsData.at(face.Normals.z() - 1);

        textureCoordsData << data.TexturesData.at(face.Textures.x() - 1)
                          << data.TexturesData.at(face.Textures.y() - 1)
                          << data.TexturesData.at(face.Textures.z() - 1);
    }
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

    cubeTexture = new QOpenGLTexture(QImage(texture).mirrored());
    cubeTexture->setMinificationFilter(QOpenGLTexture::Nearest);
    cubeTexture->setMagnificationFilter(QOpenGLTexture::Linear);
}

void DrawableObject::Logic()
{
    position += positionSpeed;
    rotation += rotationSpeed;
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
    cubeTexture->bind();

    cubeShaderProgram->setUniformValue("mvpMatrix", pMatrix * mvMatrix);
    cubeShaderProgram->setUniformValue("mvMatrix", mvMatrix);
    cubeShaderProgram->setUniformValue("normalMatrix", normalMatrix);
    cubeShaderProgram->setUniformValue("lightPosition", vMatrix * light.Position);

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
    cubeTexture->release();
}

void DrawableObject::Draw(QOpenGLShaderProgram &shader)
{

}

LightProperties& DrawableObject::getLightProperties()
{
    return lightProperties;
}

QVector3D& DrawableObject::GetPosition()
{
    return position;
}

QVector3D& DrawableObject::GetRotation()
{
    return rotation;
}

QVector3D& DrawableObject::GetPositionSpeed()
{
    return positionSpeed;
}

QVector3D& DrawableObject::GetRotationSpeed()
{
    return rotationSpeed;
}
