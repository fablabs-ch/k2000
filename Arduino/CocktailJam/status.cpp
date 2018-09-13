#include "status.h"
#include <Arduino.h>


Status::Status(Stream *serial, Scale *scale, Carrier *carrier, Pressure *pressure): serial(serial), scale(scale),
    carrier(carrier), pressure(pressure){
    this->acc = 0;
}

void Status::run(unsigned long dtMs){
    this->acc += dtMs;
    this->fps ++;
    if(acc>=STATUS_DELAY_MS){
        this->serial->print("s:");
        this->serial->print(this->carrier->getPositionMm());
        this->serial->print(':');
        this->serial->print(this->scale->getGramme());
        this->serial->print(':');
        this->serial->print(this->pressure->getCurrentPressure());
        this->serial->print(":\tfps\t");
        this->serial->println(fps);
        this->fps=0;

        this->acc = 0;
    }
}

