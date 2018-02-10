#ifndef SCALE_H
#define SCALE_H

#include "HX711.h"

#define SCALE_FILTER_SIZE 2

class Scale {
public:
	Scale(HX711* hx711);

	int getGramme();
	void tare();

	void run(unsigned long nowMs);

private:
	HX711* hx711;

	int averageIndex=0;
	int average[SCALE_FILTER_SIZE];

};

#endif
