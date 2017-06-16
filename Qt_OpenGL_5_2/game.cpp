#include "game.h"

Game::Game()
{
    lastFrameTime = QDateTime::currentMSecsSinceEpoch();
    checkCollisionsDefaultTime = 10;
    checkCollisionsTime = checkCollisionsDefaultTime;
    isGamePaused = false;
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

    player.getPosition().setZ(-300);
}

void Game::render()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glDisable(GL_CULL_FACE);
    //skybox.draw(camera, light, projectionMatrix);
    f->glEnable(GL_CULL_FACE);

    envGenerator.draw(camera, light, projectionMatrix);
    star.draw(camera, light, projectionMatrix);
    planet1.draw(camera, light, projectionMatrix);
    planet2.draw(camera, light, projectionMatrix);
    planet3.draw(camera, light, projectionMatrix);
    planet4.draw(camera, light, projectionMatrix);
    arrow.draw(camera, light, projectionMatrix);
    player.draw(camera, light, projectionMatrix);
    enemy.draw(camera, light, projectionMatrix);
}

void Game::logic()
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
    modelsToLoad.push_back(":/Objects/arrow");
    modelsToLoad.push_back(":/Objects/spodek");
    objManager.loadAll(modelsToLoad);
}

void Game::loadTextures()
{
    QVector<QString> texturesToLoad;
    texturesToLoad.push_back(":/Textures/skybox");
    texturesToLoad.push_back(":/Textures/planetoid");
    texturesToLoad.push_back(":/Textures/star");
    texturesToLoad.push_back(":/Textures/planet1");
    texturesToLoad.push_back(":/Textures/planet2");
    texturesToLoad.push_back(":/Textures/planet3");
    texturesToLoad.push_back(":/Textures/planet4");
    texturesToLoad.push_back(":/Textures/drone");
    texturesToLoad.push_back(":/Textures/arrow");
    texturesManager.loadAll(texturesToLoad);
}

void Game::createEnviroment(QOpenGLShaderProgram* shader)
{
    envGenerator.init(&objManager, &texturesManager, shader);

    skybox.init(shader, objManager.getModel(":/Objects/skybox"), texturesManager.getTexture(":/Textures/skybox"));
    skybox.getLightProperties().setAmbientColor(255,255,255,0);
    skybox.getLightProperties().setSpecularReflection(0);

    star.setScale(20,20,20);
    star.init(shader, objManager.getModel(":/Objects/star"), texturesManager.getTexture(":/Textures/star"));
    star.getLightProperties().setAmbientColor(255,255,255,0);
    star.getLightProperties().setAmbientReflection(2);
    star.getRotationSpeed().setX(0.05f);
    star.setRotation(0,15,55);

    planet1.setScale(8,8,8);
    planet1.setPosition(0,1500,0);
    planet1.init(shader, objManager.getModel(":/Objects/star"), texturesManager.getTexture(":/Textures/planet1"));
    planet1.getLightProperties().setSpecularReflection(0);
    planet1.getLightProperties().setAmbientReflection(0.5);
    planet1.getLightProperties().setAmbientColor(128,128,128);
    planet1.getLightProperties().setDiffuseReflection(0.8);
    planet1.getLightProperties().setDiffuseColor(192,192,192);
    planet1.getRotationSpeed().setX(0.05f);
    planet1.setRotation(0,15,55);

    planet2.setScale(12,12,12);
    planet2.setPosition(0,5000,1000);
    planet2.init(shader, objManager.getModel(":/Objects/star"), texturesManager.getTexture(":/Textures/planet2"));
    planet2.getLightProperties().setSpecularReflection(0);
    planet2.getLightProperties().setAmbientReflection(0.5);
    planet2.getLightProperties().setAmbientColor(128,128,128);
    planet2.getLightProperties().setDiffuseReflection(0.8);
    planet2.getLightProperties().setDiffuseColor(192,192,192);
    planet2.getRotationSpeed().setX(0.05f);
    planet2.setRotation(0,15,55);

    planet3.setScale(15,15,15);
    planet3.setPosition(0,8000,-500);
    planet3.init(shader, objManager.getModel(":/Objects/star"), texturesManager.getTexture(":/Textures/planet3"));
    planet3.getLightProperties().setSpecularReflection(0);
    planet3.getLightProperties().setAmbientReflection(0.5);
    planet3.getLightProperties().setAmbientColor(128,128,128);
    planet3.getLightProperties().setDiffuseReflection(0.8);
    planet3.getLightProperties().setDiffuseColor(192,192,192);
    planet3.getRotationSpeed().setX(0.05f);
    planet3.setRotation(0,15,55);

    planet4.setScale(12,12,12);
    planet4.setPosition(0,11000,1000);
    planet4.init(shader, objManager.getModel(":/Objects/star"), texturesManager.getTexture(":/Textures/planet4"));
    planet4.getLightProperties().setSpecularReflection(0);
    planet4.getLightProperties().setAmbientReflection(0.5);
    planet4.getLightProperties().setAmbientColor(128,128,128);
    planet4.getLightProperties().setDiffuseReflection(0.8);
    planet4.getLightProperties().setDiffuseColor(192,192,192);
    planet4.getRotationSpeed().setX(0.05f);
    planet4.setRotation(0,15,55);
}

void Game::createPlayer(QOpenGLShaderProgram* shader)
{
    player.init(objManager.getModel(":/Objects/drone"), texturesManager.getTexture(":/Textures/drone"), shader);
}

void Game::createOpponents(QOpenGLShaderProgram* shader)
{
    enemy.init(objManager.getModel(":/Objects/spodek"), texturesManager.getTexture(":/Textures/drone"), shader);
    //arrow.getScale() = QVector3D(0.1,0.1,0.1); //WTF: czemu ustawiasz skalę strzale jak tu jest funkcja opponents?
    enemy.getPosition().setX(180);
    enemy.getLightProperties().setSpecularReflection(0.4);
    enemy.getLightProperties().setAmbientReflection(0.5);
    enemy.getLightProperties().setAmbientColor(96,96,96);
    enemy.getLightProperties().setDiffuseReflection(1);
    enemy.getLightProperties().setDiffuseColor(164,164,164);
}

void Game::createArrow(QOpenGLShaderProgram* shader)
{
    arrow.init(shader, objManager.getModel(":/Objects/arrow"), texturesManager.getTexture(":/Textures/arrow"));
    arrow.setScale(0.08,0.08,0.08);
    arrow.getRotation() = QVector3D(0,90,90);
    //Sprawia, że strzałka nie ma cieni i nie odbija światła
    arrow.getLightProperties().setSpecularReflection(0);
    arrow.getLightProperties().setAmbientReflection(1);
    arrow.getLightProperties().setDiffuseReflection(0);
    arrow.getLightProperties().setAmbientColor(128,128,128); //Ustawia jasność strzałki
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
    isGamePaused = true;
}

void Game::start()
{
    lastFrameTime = QDateTime::currentMSecsSinceEpoch();
    isGamePaused = false;
}

void Game::restart()
{
    lastFrameTime = QDateTime::currentMSecsSinceEpoch();
    player.restoreStartPosition();
    isGamePaused = false;
}
