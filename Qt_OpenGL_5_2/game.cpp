#include "game.h"

Game::Game()
{
    lastFrameTime = QDateTime::currentMSecsSinceEpoch();
}

void Game::Draw(QOpenGLShaderProgram &shader)
{
    for (int i = 0; i < ImmovableObjects.size();i++)
    {
        //ImmovableObjects[i].Draw();
    }
    for (int i = 0; i < MovableObjects.size();i++)
    {
        //MovableObjects[i].Draw();
    }
}

void Game::Step()
{

}

void Game::Move()
{
    for (int i = 0; i < MovableObjects.size();i++)
    {
        //MovableObjects[i].Position += MovableObjects[i].Motion;
    }
}

void Game::initializeGame(QOpenGLShaderProgram* shader)
{
    loadModels();
    loadTextures();
    createEnviroment(shader);
}

void Game::render(Camera camera, Light light, QMatrix4x4 pMatrix)
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glDisable(GL_CULL_FACE);
    skybox.Draw(camera, light, pMatrix);
    f->glEnable(GL_CULL_FACE);

    envGenerator.Draw(camera, light, pMatrix);
    star.Draw(camera, light, pMatrix);
}

void Game::logic(Camera camera)
{
    int deltaTime = QDateTime::currentMSecsSinceEpoch() - lastFrameTime;
    lastFrameTime = QDateTime::currentMSecsSinceEpoch();

    envGenerator.RemoveObjects(physics.CheckCollisions(&star, envGenerator.GetObjects()));

    envGenerator.Logic(camera.getPosition(), deltaTime);
    star.Logic(deltaTime);

}

void Game::loadModels()
{
    QVector<QString> modelsToLoad;
    modelsToLoad.push_back(":/Objects/skybox");
    modelsToLoad.push_back(":/Objects/planetoid");
    modelsToLoad.push_back(":/Objects/star");
    objManager.LoadAll(modelsToLoad);
}

void Game::loadTextures()
{
    QVector<QString> texturesToLoad;
    texturesToLoad.push_back(":/Textures/skybox");
    texturesToLoad.push_back(":/Textures/planetoid");
    texturesToLoad.push_back(":/Textures/star");
    texturesManager.LoadAll(texturesToLoad);
}

void Game::createEnviroment(QOpenGLShaderProgram* shader)
{
    envGenerator.Init(&objManager, &texturesManager, shader);

    skybox.Init(shader, objManager.GetModel(":/Objects/skybox"),
                        texturesManager.GetTexture(":/Textures/skybox"));
    skybox.getLightProperties().setAmbientColor(255,255,255,0);
    skybox.getLightProperties().setSpecularReflection(0);

    star.Init(shader, objManager.GetModel(":/Objects/star"),
                      texturesManager.GetTexture(":/Textures/star"));
    star.getLightProperties().setAmbientColor(255,255,255,0);
    star.getRotationSpeed().setY(0.007f);
}
