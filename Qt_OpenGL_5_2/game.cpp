#include "game.h"

Game::Game()
{

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
