#include "servos.h"

Servos::Servos(){
}

void Servos::init(){
    for (int i = 0; i < NBSERVOS; i++){
        this->nextRelax[i] = 0;
        this->servo[i].attach(this->servo_pins[i]);
        this->close(i); // start with all servos closed
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
    int angle = map(percent, 0, 100, 180, 0);
    this->servo[index].write(angle);
    this->nextRelax[index] = 1500;
    int relax = 5;
    this->nextRelaxAngle[index] = angle > currentAngle[index] ? min(servo_max[index], angle-relax) : angle + relax;
    this->currentAngle[index] = angle;
}

void  Servos::run(unsigned long dtMs){
    for(int i=0; i < NBSERVOS; i++){
        unsigned long relaxDelay = this->nextRelax[i];
        if(relaxDelay>0){
            this->nextRelax[i] -= min(relaxDelay, dtMs);
            if(this->nextRelax[i]==0){
//                Serial.print("Relax servo=");
//                Serial.print(i);
//                Serial.print(" angle=");
//                Serial.println(this->nextRelaxAngle[i]);

                // we hit delay, we must relax the servo

                int angle = this->nextRelaxAngle[i];
                this->servo[i].write(angle);
                this->currentAngle[i] = angle;
            }
        }
    }
}

int Servos::getServoPosMm(int servoId){
    return this->servo_posMm[servoId];
}

void Servos::closeAll(){
    for(int i=0; i<NBSERVOS; i++){
        this->close(i);
    }
}
