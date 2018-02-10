#ifndef TERMINAL_H
#define TERMINAL_H

#include "Arduino.h"

typedef void (*INT_FN_CALLBACK)(int);
typedef void (*VOID_FN_CALLBACK)();

class Terminal {
public:
	Terminal(Stream *stream);
	~Terminal();

	void run();

	void writeStatus(int distMm, int weightGr);


	VOID_FN_CALLBACK ptrHomeCommand;
	VOID_FN_CALLBACK ptrTareCommand;
	INT_FN_CALLBACK ptrMoveCommand;

private:
	Stream *stream;

	String buffer;

	void anaylseLine(String &line);

};

#endif
