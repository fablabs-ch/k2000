#ifndef SERVOS_H
#define SERVOS_H

#include <Arduino.h>
#include <Servo.h>
#include "constants.h"

class Servos
{
    public:
        Servos();

        void init();

        void run(unsigned long dtMs);

        void open(int index);

        void close(int index);

        void set(int servoId, int aperturePercent);

        int getServoPosMm(int servoId);

    private:
        int servo_pins[NBSERVOS] = { 3, 4, 5, 6, 7, 8};
        int servo_max[NBSERVOS] = { 170, 175, 180, 180, 180, 180};
        int servo_close[NBSERVOS] = { 180, 180, 180, 180, 180, 180}; //value set when close
        int servo_open[NBSERVOS] = { 0,0,0,0,0,0}; // value set when open
        int servo_posMm[NBSERVOS]  = {40, 120, 140, 160, 180, 200};
        Servo servo[NBSERVOS];
        unsigned long nextRelax[NBSERVOS];
        unsigned long nextRelaxAngle[NBSERVOS];
};

#endif
