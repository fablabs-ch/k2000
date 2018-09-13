#include "scale.h"

Scale::Scale(HX711* hx711): hx711(hx711){
}

void Scale::init(){
    this->hx711->set_scale(CALIBRATION_FACTOR);
}

float Scale::getGramme(){
    return this->gramme;
}

void Scale::tare(){
    this->hx711->tare(1);
}

void Scale::run(unsigned long dtMs){
    if(this->hx711->is_ready()){
        this->gramme = this->hx711->get_units(1);
    }
}

