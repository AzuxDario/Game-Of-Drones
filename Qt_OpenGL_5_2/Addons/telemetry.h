#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <QDateTime>

class Telemetry
{
private:
    int currentFPS;
    int lastFPS;
    int lastUpdate;

public:
    Telemetry();

    void logic();
    int getFPS() noexcept {return lastFPS;}
};

#endif // TELEMETRY_H
