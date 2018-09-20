#ifndef BARMAN_H
#define BARMAN_H

#define QUEUE_SIZE 5

#include <Arduino.h>
#include "scale.h"
#include "carrier.h"
#include "servos.h"

typedef struct{
    int servo;
    int gramme;
} QueueItem;

enum QueueState{
    WAIT_FOR_START,
    NEXT_DRINK,
    MOVING,
    FILLING_START,
    FILLING_IN_PROGRESS,
    FILLING_END
};

class Barman
{
    public:
        Barman(Scale* scale, Carrier* carrier, Servos* servos);

        void init();

        void run(unsigned long dtMs);

        void start();
        void stop();
        void clear();

        void addToQueue(int servo, int gramme);
        QueueItem popFromQueue();
        int getQueueSize();

    private:
        Scale* scale;
        Carrier* carrier;
        Servos* servos;

        QueueItem queue[QUEUE_SIZE];
        int queueSize = 0;
        int targetGramme = 0;

        unsigned long delayUntilNextAction = 0;
        QueueItem currentItem;
        QueueState state = WAIT_FOR_START;

};

#endif
