#ifndef STATUS_H
#define STATUS_H

#include "terminal.h"
#include "scale.h"

class Status {
public:
	Status(Terminal *terminal, Scale* scale);

	void setDistMm(int value);
	void setWeightGr(int value);

	void run(unsigned long nowMs);

private:
	Terminal *terminal;
	Scale* scale;
	unsigned long nextPrint;

	int distMm;

};

#endif
