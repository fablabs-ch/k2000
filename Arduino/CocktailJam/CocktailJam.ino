
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
#include "BasicStepperDriver.h"
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
#include "barman.h"

BasicStepperDriver stepper(MOTOR_STEPS, PIN_STEPPER_DIR, PIN_STEPPER_STEP, PIN_STEPPER_ENABLED);
HX711 hx711(LOAD_CELL_DOUT, LOAD_CELL_CLK); // Initialize loadcell on I2C pins

Carrier carrier(&stepper);
CocktailSerial cocktailSerial(&Serial);
Pressure pressure(PIN_PRESSURE_SENSOR, PIN_PUMP);
Scale scale(&hx711);
Servos servos;
Barman barman(&scale, &carrier, &servos);
Status status(&Serial, &scale, &carrier, &pressure, &barman);

void release(){
    Serial.println("\ni:reset called");
    carrier.release();
}
void moveCarrierToHome(){
    Serial.println("\ni:home called");
    carrier.homing();
}

void moveCarrierToPosition(int distMm){
    Serial.println("\ni:move called");
    carrier.move(distMm);
}

void tareScale(){
    Serial.println("i:tare called");
    scale.tare();        // Reset the scale to zero
    Serial.println("i:ok"); // Send tare confirmation
}
void servoAperture(int servoId, int apertureInPercent){
    servos.set(servoId, apertureInPercent);
}
void emergency(){
    barman.stop();
    servos.closeAll();
    carrier.release();
}
void queue(int servo, int gramme){
    barman.addToQueue(servo, gramme);
}
void start(){
    barman.start();
}
void clear(){
    barman.clear();
}

void setup(){
    Serial.begin(115200);

    pinMode(PIN_PUMP, OUTPUT);
    digitalWrite(PIN_PUMP, LOW);

    int i = 0;
    int j = 4;

    servos.init();
    carrier.init();
    scale.init();
    barman.init();

    cocktailSerial.registerFunctions(
        (void *) moveCarrierToHome,
        (void *)tareScale,
        (void *)moveCarrierToPosition,
        (void *)servoAperture,
        (void*)release,
        (void*)emergency,
        (void*)queue,
        (void*)start,
        (void*)clear);
    Serial.println("\ni:ready");
 }

unsigned long lastLoop = 0;
void loop(){
    unsigned long now = millis();
    unsigned long dtMs = 0;
    if (lastLoop < now) {
        //or else overflow, keep one as delta
        dtMs = now - lastLoop;
    }
    lastLoop = now;

    cocktailSerial.run();
    pressure.run(dtMs);
    servos.run(dtMs);
    carrier.run();
    scale.run(dtMs);
    barman.run(dtMs);
    status.run(dtMs);

}

