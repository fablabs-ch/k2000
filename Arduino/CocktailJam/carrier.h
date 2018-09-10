#ifndef CARRIER_H
#define CARRIER_H

#include <Arduino.h>
#include <BasicStepperDriver.h>

#include "constants.h"

class Carrier
{
    public:
        Carrier(BasicStepperDriver* stepper);

        void init();

        void run();

        void homing();

        void move(long positionMm);

        int getPositionMm();

        void release();

    private:
        BasicStepperDriver* stepper;

        int currentPosition = -1;
};

#endif
