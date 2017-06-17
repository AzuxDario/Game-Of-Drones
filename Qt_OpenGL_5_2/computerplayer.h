#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "Player/player.h"
#include <cmath>

using namespace std;

class ComputerPlayer : public Player
{
public:
    ComputerPlayer();
    void logic(int deltaTime, QVector3D target);
};

#endif // COMPUTERPLAYER_H
