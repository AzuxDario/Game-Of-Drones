#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <QDateTime>

class Telemetry
{
public:
    Telemetry();

    void Logic();
    int GetFPS();
private:
    int currentFPS;
    int lastFPS;
    int lastUpdate;
};

#endif // TELEMETRY_H
