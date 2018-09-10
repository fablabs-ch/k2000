#ifndef STATUS_H
#define STATUS_H

#include <Arduino.h>
#include "pressure.h"
#include "carrier.h"

#define STATUS_DELAY_MS 100

class Status
{
    public:
        Status(Stream *serial, int *weightGrPtr, Carrier *carrier, Pressure *pressure);

        void run(unsigned long dtMs);

    private:
    int fps;
        unsigned long acc;
        Stream *serial;
        int *weightGrPtr;
        Carrier *carrier;
        Pressure *pressure;
};

#endif
