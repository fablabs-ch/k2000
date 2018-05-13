#include "status.h"
#include <Arduino.h>


Status::Status(Stream *serial, int *weightGrPtr, int *carrierMmPtr, Pressure *pressure): serial(serial), weightGrPtr(weightGrPtr),
    carrierMmPtr(carrierMmPtr), pressure(pressure){
    this->acc = 0;
}

void Status::run(unsigned long dtMs){
    this->acc += dtMs;
    if(acc>=STATUS_DELAY_MS){
        this->serial->print("s:");
        this->serial->print(*this->carrierMmPtr);
        this->serial->print(':');
        this->serial->print(*this->weightGrPtr);
        this->serial->print(':');
        this->serial->println(this->pressure->getCurrentPressure());

        this->acc = 0;
    }
}

