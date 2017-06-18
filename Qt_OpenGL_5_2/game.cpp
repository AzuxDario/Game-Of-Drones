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
    createRace(shader);
    createEnviroment(shader);
    createPlayer(shader);
    createOpponents(shader);
}

void Game::render()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glDisable(GL_CULL_FACE);
    skybox.draw(camera, light, projectionMatrix);
    f->glEnable(GL_CULL_FACE);

    envGenerator.draw(camera, light, projectionMatrix);
    star.draw(camera, light, projectionMatrix);
    for(int i = 0; i <= 8; i++)
    {
        planets[i]->draw(camera, light, projectionMatrix);
    }
    for(int i = 0; i <= 6; i++)
    {
        otherPlanets[i]->draw(camera, light, projectionMatrix);
    }

    player.draw(camera, light, projectionMatrix);
    enemy.draw(camera, light, projectionMatrix);
    if (player.currentTarget >= 0)
    {
        target.draw(camera, light, projectionMatrix);
        arrow.draw(hudCamera, light, projectionMatrix);
    }
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
    for(int i = 0; i <= 8; i++)
    {
        planets[i]->logic(deltaTime);
    }
    for(int i = 0; i <= 6; i++)
    {
        otherPlanets[i]->logic(deltaTime);
    }
    player.logic(deltaTime);

    if (enemy.currentTarget >= 0 && enemy.currentTarget < race.size())
    {
        enemy.logic(deltaTime, race[enemy.currentTarget]);
    }
    else
    {
        enemy.currentTarget = -1;
        enemy.logic(deltaTime, enemy.getPosition());
    }


    if (player.currentTarget >= 0 && player.currentTarget < race.length())
    {
        QVector3D diff = player.getPosition() - race[player.currentTarget];
        float len = diff.length();
        if (len < 100)
        {
            player.currentTarget++;
            if (player.currentTarget >= race.size())
            {
                player.currentTarget = -1;
                if (enemy.currentTarget >= 0) Win();
                else Lose();

            }
            else target.setPosition(race[player.currentTarget].x(), race[player.currentTarget].y(), race[player.currentTarget].z());
        }
        else
        {
            //float size = std::min(std::max(len / 100, (float)1.0),(float)100.0);
            //target.setScale(QVector3D(size,size,size));

            QVector3D dixx = camera.getTransMatrix().mapVector(QVector3D(0,0,10));

            arrow.setRotation(180 + (std::atan2(diff.z(),diff.y())-std::atan2(dixx.z(),dixx.y())) * 180 / M_PI, 90, 90);
        }
        arrow.getPosition() = QVector3D(8,0,10);//camera.getPosition() + camera.getTransMatrix().mapVector(QVector3D(2,0,10));
    }
    if (enemy.currentTarget >= 0 && enemy.currentTarget < race.size())
    {
        QVector3D diff = enemy.getPosition() - race[enemy.currentTarget];
        float len = diff.length();
        if (len < 100)
        {
            enemy.currentTarget++;
            if (enemy.currentTarget >= race.size()) enemy.currentTarget = -1;
        }
    }

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
    texturesToLoad.push_back(":/Textures/planet5");
    texturesToLoad.push_back(":/Textures/planet6");
    texturesToLoad.push_back(":/Textures/planet7");
    texturesToLoad.push_back(":/Textures/planet8");
    texturesToLoad.push_back(":/Textures/planet9");
    texturesToLoad.push_back(":/Textures/planet10");
    texturesToLoad.push_back(":/Textures/planet11");
    texturesToLoad.push_back(":/Textures/planet12");
    texturesToLoad.push_back(":/Textures/planet13");
    texturesToLoad.push_back(":/Textures/planet14");
    texturesToLoad.push_back(":/Textures/planet15");
    texturesToLoad.push_back(":/Textures/planet16");
    texturesToLoad.push_back(":/Textures/drone");
    texturesToLoad.push_back(":/Textures/arrow");
    texturesToLoad.push_back(":/Textures/Content/target.png");
    texturesManager.loadAll(texturesToLoad);
}

void Game::createEnviroment(QOpenGLShaderProgram* shader)
{
    envGenerator.init(&objManager, &texturesManager, shader);

    skybox.init(shader, objManager.getModel(":/Objects/skybox"), texturesManager.getTexture(":/Textures/skybox"));
    skybox.getLightProperties().setAmbientColor(255,255,255,0);
    skybox.getLightProperties().setSpecularReflection(0);
    skybox.setScale(500,500,500);

    star.setScale(200,200,200);
    star.init(shader, objManager.getModel(":/Objects/star"), texturesManager.getTexture(":/Textures/star"));
    star.getLightProperties().setAmbientColor(255,255,255,0);
    star.getLightProperties().setAmbientReflection(2);
    star.getRotationSpeed().setX(0.05f);
    star.setRotation(0,15,55);

    for(int i = 0; i <= 8; i++)
    {
        planets.push_back(new DrawableObject);
        planets[i]->init(shader, objManager.getModel(":/Objects/star"), texturesManager.getTexture(":/Textures/planet"+QString::number(i+1)));
        planets[i]->getLightProperties().setSpecularReflection(0);
        planets[i]->getLightProperties().setAmbientReflection(0.5);
        planets[i]->getLightProperties().setAmbientColor(128,128,128);
        planets[i]->getLightProperties().setDiffuseReflection(0.8);
        planets[i]->getLightProperties().setDiffuseColor(192,192,192);
        planets[i]->getRotationSpeed().setX(0.05f);
        planets[i]->setRotation(0,15,55);
    }
    //Merkury
    planets[0]->setScale(22,22,22);
    planets[0]->setPosition(0,0,12000);
    //Wenus
    planets[1]->setScale(28,28,28);
    planets[1]->setPosition(0,1500,20000);
    //Ziemia
    planets[2]->setScale(44,44,44);
    planets[2]->setPosition(0,-1000,32000);
    //Mars
    planets[3]->setScale(40,40,40);
    planets[3]->setPosition(0,2000,44000);
    //Jowisz
    planets[4]->setScale(84,84,84);
    planets[4]->setPosition(0,-1500,62000);
    //Saturn
    planets[5]->setScale(60,60,60);
    planets[5]->setPosition(0,2000,90000);
    //Uran
    planets[6]->setScale(50,50,50);
    planets[6]->setPosition(0,-1000,120000);
    //Neptun
    planets[7]->setScale(36,36,36);
    planets[7]->setPosition(0,1500,140000);
    //Pluton
    planets[8]->setScale(16,16,16);
    planets[8]->setPosition(0,0,156000);

    for(int i = 0; i <= 6; i++)
    {
        otherPlanets.push_back(new DrawableObject);
        otherPlanets[i]->init(shader, objManager.getModel(":/Objects/star"), texturesManager.getTexture(":/Textures/planet"+QString::number(i+10)));
        otherPlanets[i]->getLightProperties().setSpecularReflection(0);
        otherPlanets[i]->getLightProperties().setAmbientReflection(0.5);
        otherPlanets[i]->getLightProperties().setAmbientColor(128,128,128);
        otherPlanets[i]->getLightProperties().setDiffuseReflection(0.8);
        otherPlanets[i]->getLightProperties().setDiffuseColor(192,192,192);
        otherPlanets[i]->getRotationSpeed().setX(0.05f);
        otherPlanets[i]->setRotation(0,15,55);
    }

    otherPlanets[0]->setScale(60,60,60);
    otherPlanets[0]->setPosition(0,70000,-5000);

    otherPlanets[1]->setScale(70,70,70);
    otherPlanets[1]->setPosition(0,-65000,-15000);

    otherPlanets[2]->setScale(50,50,50);
    otherPlanets[2]->setPosition(0,-35000,-5000);

    otherPlanets[3]->setScale(55,55,55);
    otherPlanets[3]->setPosition(0,45000,-30000);

    otherPlanets[4]->setScale(60,60,60);
    otherPlanets[4]->setPosition(0,25000,-60000);

    otherPlanets[5]->setScale(35,35,35);
    otherPlanets[5]->setPosition(0,-15000,-35000);

    otherPlanets[6]->setScale(30,30,30);
    otherPlanets[6]->setPosition(0,-5000,-15000);
}

void Game::createPlayer(QOpenGLShaderProgram* shader)
{
    player.init(objManager.getModel(":/Objects/drone"), texturesManager.getTexture(":/Textures/drone"), shader);
}

void Game::createOpponents(QOpenGLShaderProgram* shader)
{
    enemy.init(objManager.getModel(":/Objects/spodek"), texturesManager.getTexture(":/Textures/drone"), shader);
    //arrow.getScale() = QVector3D(0.1,0.1,0.1);
    //WTF: czemu ustawiasz skalę strzale jak tu jest funkcja opponents?
    //bo kopiowałem :)
    enemy.setPosition(1600,-15,0);
    enemy.getLightProperties().setSpecularReflection(0.4);
    enemy.getLightProperties().setAmbientReflection(0.5);
    enemy.getLightProperties().setAmbientColor(96,96,96);
    enemy.getLightProperties().setDiffuseReflection(1);
    enemy.getLightProperties().setDiffuseColor(164,164,164);
}

void Game::createRace(QOpenGLShaderProgram* shader)
{
    //create checkpoints
    race.push_back(QVector3D(1600,0,500));
    race.push_back(QVector3D(1600,50,1200));
    race.push_back(QVector3D(1600,150,1500));
    race.push_back(QVector3D(1600,150,2000));
    race.push_back(QVector3D(1600,50,2800));

    //create_target
    target.init(shader, objManager.getModel(":/Objects/star"), texturesManager.getTexture(":/Textures/Content/target.png"));
    target.setPosition(race[0]);
    target.setScale(2,2,2);
    target.getLightProperties().setSpecularReflection(0);
    target.getLightProperties().setAmbientReflection(1);
    target.getLightProperties().setDiffuseReflection(0);
    target.getLightProperties().setAmbientColor(255,255,255); //Ustawia jasność strzałki

    //arrow
    arrow.init(shader, objManager.getModel(":/Objects/arrow"), texturesManager.getTexture(":/Textures/arrow"));
    arrow.setScale(0.08,0.08,0.08);
    arrow.getRotation() = QVector3D(0,90,90);
    //Sprawia, że strzałka nie ma cieni i nie odbija światła
    arrow.getLightProperties().setSpecularReflection(0);
    arrow.getLightProperties().setAmbientReflection(1);
    arrow.getLightProperties().setDiffuseReflection(1);
    arrow.getLightProperties().setAmbientColor(160,160,160); //Ustawia jasność strzałki
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

void Game::Win()
{
    isGameEnded = true;
    endGame(QString("Wygrałeś!"));
}

void Game::Lose()
{
    isGameEnded = true;
    endGame(QString("Przegrałeś!"));
}

void Game::pause()
{
    isGamePaused = true;
}

void Game::start()
{
    lastFrameTime = QDateTime::currentMSecsSinceEpoch();
    isGamePaused = false;
    isGameEnded = false;
}

void Game::resume()
{
    lastFrameTime = QDateTime::currentMSecsSinceEpoch();
    isGamePaused = false;
}

void Game::restart()
{
    lastFrameTime = QDateTime::currentMSecsSinceEpoch();
    player.restoreStartPosition();
    isGamePaused = false;
    isGameEnded = false;
}
