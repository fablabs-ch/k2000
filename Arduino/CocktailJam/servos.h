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

        void closeAll();

    private:
        int servo_close[NBSERVOS] = { 0, 0, 0, 0, 0, 0}; //value set when close (in percent)
        int servo_open[NBSERVOS] = { 40,50,100,100,100,100 }; // value set when open (in percent)
        int servo_posMm[NBSERVOS]  = {15, 35, 65, 95, 180, 200}; // in mm

        int servo_pins[NBSERVOS] = { 3, 4, 5, 6, 7, 8};
        int servo_max[NBSERVOS] = { 170, 175, 180, 180, 180, 180}; // in degree

        Servo servo[NBSERVOS];
        unsigned long nextRelax[NBSERVOS];
        unsigned long nextRelaxAngle[NBSERVOS];
        unsigned long currentAngle[NBSERVOS];
};

#endif
