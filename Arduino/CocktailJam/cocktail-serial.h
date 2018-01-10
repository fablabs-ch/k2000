#ifndef SERIAL_H
#define SERIAL_H

#include <Arduino.h>


typedef void (*FN_CALLBACK)(int, int);

class CocktailSerial {
public:

	CocktailSerial(Stream *stream);

	~CocktailSerial();

private:

	void anaylseLine(String &line);

	Stream* stream;
	String buffer;

	FN_CALLBACK fillFunc;

}

#endif