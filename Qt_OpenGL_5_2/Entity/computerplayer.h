#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <cmath>

#include "Entity/player.h"

using namespace std;

class ComputerPlayer : public Player
{
public:
    ComputerPlayer();
    void logic(int deltaTime, QVector3D target);
};

#endif // COMPUTERPLAYER_H
