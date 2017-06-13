#include "game.h"

Game::Game()
{
    lastFrameTime = QDateTime::currentMSecsSinceEpoch();
    checkCollisionsDefaultTime = 10;
    checkCollisionsTime = checkCollisionsDefaultTime;
}

void Game::initializeGame(QOpenGLShaderProgram* shader, KeyboardManager* keyboardManager)
{
    this->keyboardManager = keyboardManager;

    loadModels();
    loadTextures();
    createArrow(shader);
    createEnviroment(shader);
    createPlayer(shader);
    createOpponents(shader);

    player.getPosition().setZ(-20);
}

void Game::render(Camera& camera, Light& light, QMatrix4x4 pMatrix)
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glDisable(GL_CULL_FACE);
    skybox.draw(camera, light, pMatrix);
    f->glEnable(GL_CULL_FACE);

    envGenerator.draw(camera, light, pMatrix);
    star.draw(camera, light, pMatrix);
    arrow.draw(camera, light, pMatrix);
    player.draw(camera, light, pMatrix);
    enemy.draw(camera, light, pMatrix);
}

void Game::logic(Camera& camera)
{
    input();

    int deltaTime = QDateTime::currentMSecsSinceEpoch() - lastFrameTime;
    lastFrameTime = QDateTime::currentMSecsSinceEpoch();

    envGenerator.removeObjects(physics.checkCollisions(&star, envGenerator.GetObjects()));
    skybox.setPosition(player.getPosition());

    checkCollisions();

    envGenerator.logic(player.getPosition(), deltaTime);
    star.logic(deltaTime);
    player.logic(deltaTime);
    enemy.logic(deltaTime);

    arrow.getPosition() = (player.getPosition() + QVector3D(10,0,0));


    camera.update(player.getPosition(), player.getRotation());
}

void Game::checkCollisions()
{
    if(--checkCollisionsTime > 0)
        return;

    if(physics.checkCollisions(&star, &player))
    {
        //TODO collision player-star
    }

    QVector<DrawableObject*> planetoids = physics.checkCollisions(&player, envGenerator.GetObjects());
    if(planetoids.count() > 0)
    {
        //TODO collision player-planetoide
    }

    checkCollisionsTime = checkCollisionsDefaultTime;
}

void Game::loadModels()
{
    QVector<QString> modelsToLoad;
    modelsToLoad.push_back(":/Objects/skybox");
    modelsToLoad.push_back(":/Objects/planetoid");
    modelsToLoad.push_back(":/Objects/star");
    modelsToLoad.push_back(":/Objects/drone");
    modelsToLoad.push_back(":/Objects/Content/arrow.obj");
    modelsToLoad.push_back(":/Objects/Content/spodek.obj");
    objManager.loadAll(modelsToLoad);
}

void Game::loadTextures()
{
    QVector<QString> texturesToLoad;
    texturesToLoad.push_back(":/Textures/skybox");
    texturesToLoad.push_back(":/Textures/planetoid");
    texturesToLoad.push_back(":/Textures/star");
    texturesToLoad.push_back(":/Textures/drone");
    texturesManager.loadAll(texturesToLoad);
}

void Game::createEnviroment(QOpenGLShaderProgram* shader)
{
    envGenerator.init(&objManager, &texturesManager, shader);

    skybox.init(shader, objManager.getModel(":/Objects/skybox"),
                        texturesManager.getTexture(":/Textures/skybox"));
    skybox.getLightProperties().setAmbientColor(255,255,255,0);
    skybox.getLightProperties().setSpecularReflection(0);

    star.init(shader, objManager.getModel(":/Objects/star"),
                      texturesManager.getTexture(":/Textures/star"));
    star.getLightProperties().setAmbientColor(255,255,255,0);
    star.getLightProperties().setAmbientReflection(2);
    star.getRotationSpeed().setY(0.007f);
}

void Game::createPlayer(QOpenGLShaderProgram* shader)
{
    player.init(objManager.getModel(":/Objects/drone"), texturesManager.getTexture(":/Textures/drone"), shader);
}

void Game::createOpponents(QOpenGLShaderProgram* shader)
{
    enemy.init(objManager.getModel(":/Objects/Content/spodek.obj"), texturesManager.getTexture(":/Textures/drone"), shader);
    arrow.getScale() = QVector3D(0.1,0.1,0.1);
    enemy.getPosition().setX(30);
}

void Game::createArrow(QOpenGLShaderProgram* shader)
{
    arrow.init(shader, objManager.getModel(":/Objects/Content/arrow.obj"), texturesManager.getTexture(":/Textures/drone"));
    arrow.getScale() = QVector3D(0.1,0.1,0.1);
    arrow.getRotation() = QVector3D(0,90,90);
}


void Game::input()
{
    if(keyboardManager->isKeyPressed(Qt::Key::Key_W) || keyboardManager->isKeyPressed(Qt::Key::Key_Up))
    {
        player.rotation.setY(max(player.rotation.y() - player.agility, -player.maxturn));
    }
    if(keyboardManager->isKeyPressed(Qt::Key::Key_S) || keyboardManager->isKeyPressed(Qt::Key::Key_Down))
    {
        player.rotation.setY(min(player.rotation.y() + player.agility, player.maxturn));
    }


    if(keyboardManager->isKeyPressed(Qt::Key::Key_A) || keyboardManager->isKeyPressed(Qt::Key::Key_Left))
    {
        player.rotation.setX(min(player.rotation.x() + player.agility, player.maxturn));
    }

    if (keyboardManager->isKeyPressed(Qt::Key::Key_D) || keyboardManager->isKeyPressed(Qt::Key::Key_Right))
    {
        player.rotation.setX(max(player.rotation.x() - player.agility, -player.maxturn));
    }


    if(keyboardManager->isKeyPressed(Qt::Key::Key_Q))
    {

    }

    if(keyboardManager->isKeyPressed(Qt::Key::Key_E))
    {

    }

    if(keyboardManager->isKeyPressed(Qt::Key::Key_Space))
    {
        player.accelerate = min(player.accelerate + player.acceleration, player.maxspeed);
    }
}

void Game::pause()
{

}

void Game::resume()
{
    lastFrameTime = QDateTime::currentMSecsSinceEpoch();
}

void Game::restart()
{
    lastFrameTime = QDateTime::currentMSecsSinceEpoch();
    player.restoreStartPosition();
}
