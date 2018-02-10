#include "cocktail-serial.h"

CocktailSerial::CocktailSerial(Stream *stream) : stream(stream)
{
}

void CocktailSerial::registerFunctions(FN_CALLBACK homeFunc, FN_CALLBACK tareFunc, FN_CALLBACK fillFunc, FN_CALLBACK moveFunc, FN_CALLBACK servoFunc)
{
    this->homeFunc = homeFunc;
    this->tareFunc = tareFunc;
    this->fillFunc = fillFunc;
    this->moveFunc = moveFunc;
    this->servoFunc = servoFunc;
}

// TODO: why run? could we not use prinln from serial?
void CocktailSerial::run()
{
    if (stream)
    {
        while (stream->available())
        {
            char c = stream->read();
            if (c == '\r')
            {
                //ignore
            }
            else if (c == '\n')
            {
                anaylseLine(buffer);
                buffer = String();
            }
            else
            {
                buffer += c;
            }
        }
    }
}

void CocktailSerial::anaylseLine(String &line)
{
    if (line.length())
    {
        char cmd = line.charAt(0);
        bool called = false;

        int firstIndex = line.length() > 1 ? 1 : -1; // first ':' always at second char, otherwise there is no ':'
        int secondIndex = line.indexOf(':', firstIndex + 1);
        int thirdIndex = line.indexOf(':', secondIndex + 1);
        int arg1 = -1;
        int arg2 = -1;
        int arg3 = -1;

        if (firstIndex != -1)
        {
            arg1 = line.substring(firstIndex + 1, secondIndex).toInt();
        }
        if (secondIndex != -1)
        {
            arg2 = line.substring(secondIndex + 1, thirdIndex).toInt();
        }
        if (thirdIndex != -1)
        {
            arg3 = line.substring(thirdIndex + 1).toInt();
        }

        switch (cmd)
        {
        case 'h':
            called = this->call(this->homeFunc);
            break;
        case 't':
            called = this->call(this->tareFunc);
            break;
        case 'f':
            called = this->call(this->fillFunc, arg1, arg2, arg3);
            break;
        case 'm':
            called = this->call(this->moveFunc, arg1);
            break;
        case 'a':
            called = this->call(this->servoFunc, arg1, arg2);
            break;
        }

        if (!called)
        {
            stream->print("e:unknown:");
            stream->println(line);
        }else{
            // print the same command line to indicate that we received it correctly
            stream->println(line);
        }
    }
}

bool CocktailSerial::call(FN_CALLBACK func, int arg1, int arg2, int arg3)
{
    if (func)
    {
        func(arg1, arg2, arg3);
        return true;
    }
    return false;
}
