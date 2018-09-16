#include "carrier.h"

Carrier::Carrier(BasicStepperDriver* stepper):stepper(stepper){
}

void Carrier::init(){
    this->stepper->begin(60, MICROSTEPS);
    this->stepper->disable();
    this->stepper->setSpeedProfile(this->stepper->LINEAR_SPEED, MOTOR_ACCEL_SPEED, MOTOR_DECEL_SPEED);
    pinMode(PIN_HOME, INPUT_PULLUP);
}

void Carrier::move(long targetPosition){
    if(this->stepper->getCurrentState() == this->stepper->STOPPED){
        int steps_to_do = ((targetPosition - this->nextPosition) * STEPS_PER_MM);
        long getTimeForMove(long steps);
        this->stepper->startMove(steps_to_do);
        this->stepper->enable();
        this->nextPosition = targetPosition;
    }else{
        Serial.println("e:carrier:already_moving");
    }
}

void Carrier::release(){
    this->stepper->disable();
}

int Carrier::getPositionMm(){
    return abs((int)(this->nextPosition - this->stepper->getStepsRemaining()*STEPS_PER_MM_REVERSE));
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

    this->nextPosition = 0;
}

bool Carrier::isMoving(){
    return this->stepper->getCurrentState() != this->stepper->STOPPED;
}
