#ifndef PRESSURE_H
#define PRESSURE_H

#include <Arduino.h>

// in pression unit
#define TARGET_PRESSURE_HYSTERESIS 100
#define TARGET_PRESSURE 600

class Pressure
{
    public:
        Pressure(int pinPressionSensor, int pinPump);

        void run(unsigned long dtMs);

        long getCurrentPressure();

    private:
        int pinPressure;
        int pinPump;
        long currentPressure = -1;
        int targetPressureStop;
        int targetPressureStart;

        double readPressure();

};

#endif
