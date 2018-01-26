#include "timeconverter.h"

TimeConverter::TimeConverter()
{

}

QString TimeConverter::toQStringFromMsec(int miliSeconds)
{
    QString min, sec, mSec;
    int timeElapsed = miliSeconds;
    int minutes = timeElapsed / 60000;
    timeElapsed -= minutes * 60000;
    int seconds = timeElapsed / 1000;
    timeElapsed -=seconds * 1000;
    if(minutes<10)
    {
        min = "0" + QString::number(minutes);
    }
    else
    {
        min = QString::number(minutes);
    }
    if(seconds<10)
    {
        sec = "0" + QString::number(seconds);
    }
    else
    {
        sec = QString::number(seconds);
    }
    if(timeElapsed<10)
    {
        mSec = "00" + QString::number(timeElapsed);
    }
    else if(timeElapsed<100)
    {
        mSec = "0" + QString::number(timeElapsed);
    }
    else
    {
        mSec = QString::number(timeElapsed);
    }

    return QString(min+":"+sec+"."+mSec);
}
