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

void Game::initializeGame(QOpenGLShaderProgram* shader, KeyboardManager* keyboardManager)
{
    this->keyboardManager = keyboardManager;

    loadModels();
    loadTextures();
    createEnviroment(shader);
    createPlayer(shader);

    //TEST
    player.getPosition().setX(20);
}

void Game::render(Camera& camera, Light& light, QMatrix4x4 pMatrix)
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glDisable(GL_CULL_FACE);
    skybox.Draw(camera, light, pMatrix);
    f->glEnable(GL_CULL_FACE);

    envGenerator.Draw(camera, light, pMatrix);
    star.Draw(camera, light, pMatrix);
    player.Draw(camera, light, pMatrix);
}

void Game::logic(Camera& camera)
{
    input();

    int deltaTime = QDateTime::currentMSecsSinceEpoch() - lastFrameTime;
    lastFrameTime = QDateTime::currentMSecsSinceEpoch();

    envGenerator.RemoveObjects(physics.CheckCollisions(&star, envGenerator.GetObjects()));

    envGenerator.Logic(camera.getPosition(), deltaTime);
    star.Logic(deltaTime);
    player.Logic(deltaTime);
    updateCamera(camera);
}

void Game::loadModels()
{
    QVector<QString> modelsToLoad;
    modelsToLoad.push_back(":/Objects/skybox");
    modelsToLoad.push_back(":/Objects/planetoid");
    modelsToLoad.push_back(":/Objects/star");
    modelsToLoad.push_back(":/Objects/drone");
    objManager.LoadAll(modelsToLoad);
}

void Game::loadTextures()
{
    QVector<QString> texturesToLoad;
    texturesToLoad.push_back(":/Textures/skybox");
    texturesToLoad.push_back(":/Textures/planetoid");
    texturesToLoad.push_back(":/Textures/star");
    texturesToLoad.push_back(":/Textures/drone");
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
    star.getLightProperties().setAmbientReflection(2);
    star.getRotationSpeed().setY(0.007f);
}

void Game::createPlayer(QOpenGLShaderProgram* shader)
{
    player.Init(&objManager, &texturesManager, shader);
}

void Game::KeyPressed(Qt::Key key)
{

}

void Game::KeyReleased(Qt::Key key)
{

}

void Game::updateCamera(Camera& camera)
{
    camera.setPosition(player.getPosition());
    camera.setRotation(player.getRotation());
}

void Game::input()
{
    if(keyboardManager->IsKeyPressed(Qt::Key::Key_W))
        player.getPosition() += QVector3D(0, 0, -0.1);
    if(keyboardManager->IsKeyPressed(Qt::Key::Key_S))
        player.getPosition() += QVector3D(0, 0, 0.1);

    if(keyboardManager->IsKeyPressed(Qt::Key::Key_A))
        player.getPosition() += QVector3D(-0.1, 0, 0);
    if(keyboardManager->IsKeyPressed(Qt::Key::Key_D))
        player.getPosition() += QVector3D(0.1, 0, 0);

    if(keyboardManager->IsKeyPressed(Qt::Key::Key_Q))
        player.getRotation() += QVector3D(-0.4, 0, 0);
    if(keyboardManager->IsKeyPressed(Qt::Key::Key_E))
        player.getRotation() += QVector3D(0.4, 0, 0);
}
