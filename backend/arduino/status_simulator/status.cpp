#include "status.h"
#include "constants.h"

Status::Status(Terminal* terminal, Scale* scale) : terminal(terminal), scale(scale){
	this->nextPrint = 0;
	this->distMm = -1;
}

void Status::run(unsigned long nowMs){
	if(nowMs>this->nextPrint){
		this->terminal->writeStatus(this->distMm, this->scale->getGramme());
		this->nextPrint = nowMs + STATUS_DELAY_MS;
	}
}

void Status::setDistMm(int value){
	this->distMm = value;
}

