#include "barman.h"

Barman::Barman(Scale* scale, Carrier* carrier, Servos* servos) : scale(scale), carrier(carrier), servos(servos){
}

void Barman::init(){
}

void Barman::start(){
    this->state = IDLE;
}

void Barman::run(unsigned long dtMs){
    if(this->delayUntilNextAction>0){
        this->delayUntilNextAction -= min(this->delayUntilNextAction, dtMs);
        return;
    }
    if(this->state == IDLE && this->queueSize==0){
        return; // nothing to do
    }
    if(this->state == WAIT_FOR_START){
        return;
    }

    if(this->state == IDLE){
        // start doing stuff
        this->currentItem = this->popFromQueue();
        int positionMm = this->servos->getServoPosMm(this->currentItem.servo);
        this->carrier->move(positionMm);
        this->state = MOVING;
        Serial.print("moveTo ");
        Serial.println(this->currentItem.servo);
    }

    if(this->state == MOVING && !this->carrier->isMoving()){
        this->state = FILLING;
        this->delayUntilNextAction = 2000;
    }

    if(this->state == FILLING){
        if(this->queueSize==0){
            this->state = WAIT_FOR_START;
            this->carrier->move(0);
        }else{
            this->state = IDLE;
        }
    }
}

QueueItem Barman::popFromQueue(){
    if(this->queueSize==0){
        return {
            servo: -1,
            gramme: -1
        };
    }
    QueueItem item = this->queue[0];
    for(int i=0; i<this->queueSize;i++){
        this->queue[i] = this->queue[i+1];
    }
    this->queueSize--;
    return item;
}

void Barman::addToQueue(int servo, int gramme){
    if(this->queueSize>=QUEUE_SIZE){
        Serial.println("Max queue reached");
    }else{
        this->queue[this->queueSize] = {servo, gramme};
        this->queueSize++;
        Serial.print("QueueSize: ");
        Serial.println(this->queueSize);
    }
}

int Barman::getQueueSize(){
    return this->queueSize;
}
