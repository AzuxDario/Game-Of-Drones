#include "computerplayer.h"

ComputerPlayer::ComputerPlayer()
{
    acceleration = 0.01;
    maxspeed = 0.05;

}

void ComputerPlayer::logic(int deltaTime, QVector3D target)
{
    if (currentTarget >= 0)
    {
        QVector3D diff = getPosition() - target;
        float len = diff.length();
        if (len < 100)
        {
            currentTarget++;
        }

        float dir = atan2(diff.z(),diff.y()) + M_PI/2;
        direction.setX(dir * 180 / M_PI );
        //accelerate = min(accelerate + acceleration, maxspeed);
        dir -=direction.x() * M_PI / 180;
        if (dir > 0)
        {
            //rotation.setX(max(maxturn, dir));
            if (dir < M_PI / 2)
            {
                accelerate = min(accelerate + acceleration, maxspeed);
            }
            else
            {
                accelerate = max((float)0.0,accelerate/100-(float)0.1);
            }
        }
        else
        {
            //rotation.setX(min(-maxturn, dir));
            if (dir > -M_PI / 2)
            {
                accelerate = min(accelerate + acceleration, maxspeed);
            }
            else
            {
                accelerate = max((float)0.0,accelerate/100-(float)0.1);
            }
        }
    }
    else
    {
        rotation.setX(0);
        rotation.setY(0);
        accelerate = max((float)0.0,accelerate/100-(float)0.1);
    }

    Player::logic(deltaTime);
}
