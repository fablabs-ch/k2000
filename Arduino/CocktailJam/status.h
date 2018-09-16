#ifndef STATUS_H
#define STATUS_H

#include <Arduino.h>
#include "pressure.h"
#include "carrier.h"
#include "scale.h"
#include "barman.h"

/**
 * Splitting status in multiple part to avoid blocking too much time
 */

#define STATUS_PART 5
#define STATUS_DELAY_MS 50/STATUS_PART

class Status
{
    public:
        Status(Stream *serial, Scale *scale, Carrier *carrier, Pressure *pressure, Barman* barman);

        void run(unsigned long dtMs);

    private:
        int fps;
        int nextPart=0;
        unsigned long acc;
        Stream *serial;
        Scale *scale;
        Carrier *carrier;
        Pressure *pressure;
        Barman *barman;
};

#endif
