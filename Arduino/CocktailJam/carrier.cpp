#include "carrier.h"

Carrier::Carrier(BasicStepperDriver* stepper):stepper(stepper){
//TODO move BasicStepperDriver instance creation here
}

void Carrier::init(){
    this->stepper->begin(60, MICROSTEPS);
    this->stepper->disable();
    this->stepper->setSpeedProfile(this->stepper->LINEAR_SPEED, MOTOR_ACCEL_SPEED, MOTOR_DECEL_SPEED);
    pinMode(PIN_HOME, INPUT_PULLUP);
}

void Carrier::move(long targetPosition){
    int steps_to_do = ((targetPosition - this->currentPosition) * STEPS_PER_MM);
    this->stepper->startMove(steps_to_do);
    Serial.print("set pos to ");
    Serial.println(steps_to_do);
    this->stepper->enable();
    this->currentPosition = targetPosition;
}

void Carrier::release(){
    this->stepper->disable();
}

int Carrier::getPositionMm(){
    return this->currentPosition;
}

void Carrier::run(){
    this->stepper->nextAction();
}

void Carrier::homing(){
    this->stepper->enable();
    this->stepper->setRPM(MOTOR_RPM);

    //if already home
    if(digitalRead(PIN_HOME) == LOW){
        this->stepper->startMove(50L * STEPS_PER_MM);
        while(this->stepper->getCurrentState() != this->stepper->STOPPED){
          this->stepper->nextAction();
        }
        this->stepper->startBrake();
        while(this->stepper->getCurrentState() != this->stepper->STOPPED){
          this->stepper->nextAction();
        }
    }

    this->stepper->startMove(-1000L * STEPS_PER_MM);

    //go to home
    while (digitalRead(PIN_HOME) == HIGH && this->stepper->getCurrentState() != this->stepper->STOPPED){
      this->stepper->nextAction();
    }
    this->stepper->startBrake();
    while(this->stepper->getCurrentState() != this->stepper->STOPPED){
      this->stepper->nextAction();
    }

    this->currentPosition = 0;
}

bool Carrier::isMoving(){
    return this->stepper->getCurrentState() != this->stepper->STOPPED;
}
