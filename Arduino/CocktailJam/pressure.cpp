#include "pressure.h"

Pressure::Pressure(int pinPressure, int pinPump, int targetPressure): pinPressure(pinPressure),
    pinPump(pinPump), targetPressure(targetPressure){
    this->targetPressureStart = targetPressure-TARGET_PRESSURE_HYSTERESIS;
    this->targetPressureStop = targetPressure+TARGET_PRESSURE_HYSTERESIS;
}

long Pressure::getCurrentPressure(){
    return this->currentPressure;
}

void Pressure::run(unsigned long dtMs){
    this->currentPressure = readPressure();
    if(this->currentPressure<this->targetPressureStart){
        digitalWrite(this->pinPump, HIGH);
    }
    if(this->currentPressure>this->targetPressureStop){
        digitalWrite(this->pinPump, LOW);
    }
}

double Pressure::readPressure(){
	double adc0 = (double)analogRead(this->pinPressure);
	double erreurV = -0.17;
	double vout = adc0 * 0.004883 + erreurV;
	double pressure = (vout * 0.2 - 0.04) *1111.111111111;
    return pressure;
}
