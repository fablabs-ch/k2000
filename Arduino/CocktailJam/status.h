#ifndef STATUS_H
#define STATUS_H

#include <Arduino.h>
#include "pressure.h"

#define STATUS_DELAY_MS 100

class Status
{
    public:
        Status(Stream *serial, int *weightGrPtr, int *carrierMmPtr, Pressure *pressure);

        void run(unsigned long dtMs);

    private:
        unsigned long acc;
        Stream *serial;
        int *weightGrPtr;
        int *carrierMmPtr;
        Pressure *pressure;
};

#endif
