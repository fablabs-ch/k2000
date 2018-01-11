#ifndef SERIAL_H
#define SERIAL_H

#include <Arduino.h>

typedef void (*FN_CALLBACK)(int, int, int);

/**
 * This class parse the serial commands
 * See https://github.com/fablabs-ch/bar-o-matic/wiki/Protocol-Rpi---Arduino
 */
class CocktailSerial
{
  public:
    CocktailSerial(Stream *stream);

    void registerFunctions(FN_CALLBACK homeFunc, FN_CALLBACK tareFunc, FN_CALLBACK fillFunc);

    void run();

  private:
    void anaylseLine(String &line);
    bool call(FN_CALLBACK func, int arg1 = -1, int arg2 = -1, int arg3 = -1);

    Stream *stream;
    String buffer;

    FN_CALLBACK homeFunc = 0;
    FN_CALLBACK tareFunc = 0;
    FN_CALLBACK fillFunc = 0;
    ;
};

#endif