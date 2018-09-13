#include "servos.h"

Servos::Servos(){
}

void Servos::init(){
    for (int i = 0; i < NBSERVOS; i++){
        this->nextRelax[i] = 0;
        this->servo[i].attach(this->servo_pins[i]);
        this->close(i);
    }
}

void Servos::close(int index){
    this->set(index, this->servo_close[index]);
}

void Servos::open(int index){
    this->set(index, this->servo_open[index]);
}

void Servos::set(int index, int percent){
    percent = constrain(percent, 0, 100);
    int angle = map(percent, 0, 100, 0, 180);
    this->servo[index].write(angle);
    this->nextRelax[index] = 1500;
    int relax = 5;
    this->nextRelaxAngle[index] = percent > 50 ? min(servo_max[index], angle-relax) : angle + relax;
}

void  Servos::run(unsigned long dtMs){
    for(int i=0; i < NBSERVOS; i++){
        unsigned long relaxDelay = this->nextRelax[i];
        if(relaxDelay>0){
            this->nextRelax[i] -= min(relaxDelay, dtMs);
            if(this->nextRelax[i]==0){
            Serial.print("Relax servo=");
            Serial.print(i);
            Serial.print(" angle=");
            Serial.println(this->nextRelaxAngle[i]);
                // we hit delay, we must relax the servo
                this->servo[i].write(this->nextRelaxAngle[i]);
            }
        }
    }
}

int Servos::getServoPosMm(int servoId){
    return this->servo_posMm[servoId];
}
