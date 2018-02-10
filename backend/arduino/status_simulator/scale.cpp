#include "scale.h"


Scale::Scale(HX711* hx711):hx711(hx711){
	hx711->set_scale(1953.f);
}

int Scale::getGramme(){
	long sum = 0;
	for(int i=0; i<SCALE_FILTER_SIZE; i++){
		sum += this->average[i];
	}
	return sum/SCALE_FILTER_SIZE;
}

void Scale::tare(){
	this->hx711->tare();
}


void Scale::run(unsigned long nowMs){
	this->averageIndex++;
	if(this->averageIndex>=SCALE_FILTER_SIZE){
		this->averageIndex=0;
	}
	this->average[this->averageIndex] = this->hx711->get_units(1);
}
