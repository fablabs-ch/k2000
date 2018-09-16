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

    void registerFunctions(
        FN_CALLBACK homeFunc,
        FN_CALLBACK tareFunc,
        FN_CALLBACK moveFunc,
        FN_CALLBACK servoFunc,
        FN_CALLBACK releaseFunc,
        FN_CALLBACK emergencyFunc,
        FN_CALLBACK queueFunc,
        FN_CALLBACK startFunc,
        FN_CALLBACK clearFunc);

    void run();

  private:
    void anaylseLine(String &line);
    bool call(FN_CALLBACK func, int arg1 = -1, int arg2 = -1, int arg3 = -1);

    Stream *stream;
    String buffer;

    FN_CALLBACK homeFunc = 0;
    FN_CALLBACK tareFunc = 0;
    FN_CALLBACK moveFunc = 0;
    FN_CALLBACK servoFunc = 0;
    FN_CALLBACK releaseFunc = 0;
    FN_CALLBACK emergencyFunc = 0;
    FN_CALLBACK queueFunc = 0;
    FN_CALLBACK startFunc = 0;
    FN_CALLBACK clearFunc = 0;
};

#endif
