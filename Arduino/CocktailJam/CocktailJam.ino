
/*
 * This Arduino code manages glass moving carrier, led animation and glass infill.
 * Raspberry Pi sends commands through serial and Arduino do the rest.
 *
 * For hardware connection, see schematic: https://github.com/fablabs-ch/bar-o-matic/blob/master/hardware/bar-o-matic_bb.png
 *
 * Ensure to set the correct parameters according to the hardware you have choosen. All constant below marked with * have to be customized to avoid bad behavior.
 *
 * FabLabs-CH for swiss fablabs
 * Copyright (C) 2018  Christophe Cachin & Gaétan Collaud
 */
#include <Arduino.h>
#include <BasicStepperDriver.h>
#include <HX711.h>
#ifdef __AVR__
    #include <avr/power.h>
#endif

#include "constants.h"
#include "cocktail-serial.h";
#include "pressure.h"
#include "status.h"
#include "servos.h"
#include "carrier.h"
#include "scale.h"

BasicStepperDriver stepper(MOTOR_STEPS, PIN_STEPPER_DIR, PIN_STEPPER_STEP, PIN_STEPPER_ENABLED);
HX711 hx711(LOAD_CELL_DOUT, LOAD_CELL_CLK); // Initialize loadcell on I2C pins

Carrier carrier(&stepper);
CocktailSerial cocktailSerial(&Serial);
Pressure pressure(PIN_PRESSURE_SENSOR, PIN_PUMP, 700);
Scale scale(&hx711);
Status status(&Serial, &scale, &carrier, &pressure);
Servos servos;

//=== CARRIER =================================================================================================================================
void reset(){
    Serial.println("i:reset called");
    carrier.release();
}
void moveCarrierToHome()
{
    // Initialize carrier position
    Serial.println("i:home called");
    carrier.homing();
    Serial.println("i:ok"); // Send position confirmation
}

void moveCarrierToPosition(int distMm)
{
    Serial.println("i:move called");
    carrier.move(distMm);
    Serial.println("i:ok");
}

//=== WEIGHT & FILL============================================================================================================================
void tareScale()
{
    Serial.println("i:tare called");
    scale.tare();        // Reset the scale to zero
    Serial.println("i:ok"); // Send tare confirmation
}

void servoAperture(int servoId, int apertureInPercent){
    servos.set(servoId, apertureInPercent);
}

void fillGlass(int distMm, int nServo, int weightGr)
{
////Open Servo x while weight is not equal target weight including glass animation
//    Serial.print("i:fill called, dist=");
//    Serial.print(distMm);
//    Serial.print(", servo=");
//    Serial.print(nServo);
//    Serial.print(", weight=");
//    Serial.println(weightGr);
//
//    // TODO: review why do we move at the end of fill? the moveShouldbe called by server/management code to have function isolation
//   // moveCarrierToPosition(distMm);
//
//    //servos.open(nServo);
//
//    targetWeight = weightGr;
//
//    do
//    {
//        currentWeight = computeCurrentWeight();
////        pixelGlassToDisplay = NBPIXELS_GLASS * currentWeight / targetWeight;              //Calculate which pixel to display according to current weight
////        pixels_glass.setPixelColor(pixelGlassToDisplay, pixels_glass.Color(50, 90, 255)); //Set dark blue color
////        pixels_glass.show();                                                              //Show glass animation
//        loop();
//    } while (currentWeight < targetWeight);
//
//    servos.close(nServo);
}

void setup()
{
    Serial.begin(115200);

    pinMode(PIN_PUMP, OUTPUT);
    digitalWrite(PIN_PUMP, LOW);

    int i = 0;
    int j = 4;


    servos.init();
    carrier.init();
    scale.init();

    cocktailSerial.registerFunctions((void *) moveCarrierToHome, (void *)tareScale, (void *)fillGlass, (void *)moveCarrierToPosition, (void *)servoAperture, (void*)reset);
    Serial.println("i:ready");
 }

unsigned long lastLoop = 0;
void loop()
{
    unsigned long now = millis();
    unsigned long dtMs = 0;
    if (lastLoop < now) {
        //or else overflow, keep one as delta
        dtMs = now - lastLoop;
    }
    lastLoop = now;

    // scale take time, disable it when stepper is running
    scale.enableReading(!carrier.isMoving());

    cocktailSerial.run();
    pressure.run(dtMs);
    servos.run(dtMs);
    carrier.run();
    scale.run(dtMs);
    status.run(dtMs);

}

