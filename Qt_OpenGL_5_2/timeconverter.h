#ifndef TIMECONVERTER_H
#define TIMECONVERTER_H

#include "QString"

class TimeConverter
{
public:
    TimeConverter();
    static QString toQStringFromMsec(int miliSeconds);
};

#endif // TIMECONVERTER_H
