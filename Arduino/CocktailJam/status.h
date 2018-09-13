#ifndef STATUS_H
#define STATUS_H

#include <Arduino.h>
#include "pressure.h"
#include "carrier.h"
#include "scale.h"

#define STATUS_DELAY_MS 100

class Status
{
    public:
        Status(Stream *serial, Scale *scale, Carrier *carrier, Pressure *pressure);

        void run(unsigned long dtMs);

    private:
    int fps;
        unsigned long acc;
        Stream *serial;
        Scale *scale;
        Carrier *carrier;
        Pressure *pressure;
};

#endif
