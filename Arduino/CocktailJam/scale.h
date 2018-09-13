#ifndef SCALE_H
#define SCALE_H

#define CALIBRATION_FACTOR 1980

#include <Arduino.h>
#include <HX711.h>

class Scale
{
    public:
        Scale(HX711* hx711);

        void init();

        void run(unsigned long dtMs);

        float getGramme();

        void tare();

    private:
        HX711* hx711;
        float gramme;

};

#endif
