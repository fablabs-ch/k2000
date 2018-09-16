#include "status.h"
#include <Arduino.h>


Status::Status(Stream *serial, Scale *scale, Carrier *carrier, Pressure *pressure, Barman* barman):
serial(serial), scale(scale), carrier(carrier), pressure(pressure), barman(barman){
    this->acc = 0;
}

void Status::run(unsigned long dtMs){
    this->acc += dtMs;
    this->fps ++;
    if(acc>=STATUS_DELAY_MS){
        switch(nextPart){
            case 0:
                this->serial->print("s:");
                this->serial->print(fps);
                break;
            case 1:
                this->serial->print(":");
                this->serial->print(this->barman->getQueueSize());
                break;
            case 2:
                this->serial->print(":");
                this->serial->print(this->carrier->getPositionMm());
                break;
            case 3:
                this->serial->print(":");
                this->serial->print(this->pressure->getCurrentPressure());
                break;
            case 4:
                this->serial->print(":\t");
                this->serial->println(this->scale->getGramme());

                this->fps=0;
                break;
        }

        this->nextPart++;
        if(this->nextPart==STATUS_PART){
            this->nextPart = 0;
        }
        this->acc = 0;

    }
}

