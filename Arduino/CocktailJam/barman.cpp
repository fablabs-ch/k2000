#include "barman.h"

Barman::Barman(Scale* scale, Carrier* carrier, Servos* servos) : scale(scale), carrier(carrier), servos(servos){
}

void Barman::init(){
}

void Barman::start(){
    this->state = NEXT_DRINK;
}
void Barman::stop(){
    this->state = WAIT_FOR_START;
    this->clear();
}
void Barman::clear(){
    this->queueSize = 0;
}

void Barman::run(unsigned long dtMs){
    if(this->delayUntilNextAction>0){
        // wait for the action to be done
        this->delayUntilNextAction -= min(this->delayUntilNextAction, dtMs);
        return;
    }
    if(this->state == WAIT_FOR_START){
        return;

    }else if(this->state == NEXT_DRINK){
        // start doing stuff
        this->currentItem = this->popFromQueue();
        int positionMm = this->servos->getServoPosMm(this->currentItem.servo);
        this->carrier->move(positionMm);
        this->state = MOVING;

    }else if(this->state == MOVING){
        if(!this->carrier->isMoving()){
            // drink has arrived
            this->delayUntilNextAction = 200;
            this->state = FILLING_START;
        }

    }else if(this->state == FILLING_START){
        this->targetGramme = this->scale->getGramme() + this->currentItem.gramme;
        this->servos->open(this->currentItem.servo);
        this->state = FILLING_IN_PROGRESS;
//        this->delayUntilNextAction = 2000;

    }else if(this->state == FILLING_IN_PROGRESS){
        if(this->scale->getGramme()>=this->targetGramme){
            this->servos->close(this->currentItem.servo);
            // wait for last drop
            this->delayUntilNextAction = 2000;
            this->state = FILLING_END;
        }

    }else if(this->state == FILLING_END){
        if(this->queueSize==0){
            this->state = WAIT_FOR_START;
            this->carrier->move(0);
        }else{
            // next drink
            this->state = NEXT_DRINK;
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
