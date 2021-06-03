/*
PRODUCER - CONSUMER PROBLEM

SOLUTION TYPE B - USING SEMAPHORE
    version b03: 2 fast producers, 1 slow consumer
*/


#include <iostream>
#include <queue>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;



struct GlobalSemaphore {
    sem_t fillCount;    // item produced
    sem_t emptyCount;   // remaining space in queue

    void init(int fillCount, int emptyCount) {
        sem_init(&this->fillCount, 0, fillCount);
        sem_init(&this->emptyCount, 0, emptyCount);
    }

    void destroy() {
        sem_destroy(&fillCount);
        sem_destroy(&emptyCount);
    }

    void waitFillCount() {
        sem_wait(&fillCount);
    }

    void waitEmptyCount() {
        sem_wait(&emptyCount);
    }

    void postFillCount() {
        sem_post(&fillCount);
    }

    void postEmptyCount() {
        sem_post(&emptyCount);
    }
};



struct GlobalArg {
    queue<int> *pqProduct;
    GlobalSemaphore *psem;
    int dataAddFactor = 0;
};



void* producer(void *voidArg) {
    auto arg = (GlobalArg*)voidArg;
    auto pqProduct = arg->pqProduct;
    auto psem = arg->psem;

    int i = 1;

    for (;; ++i) {
        psem->waitEmptyCount();

        pqProduct->push(i + arg->dataAddFactor);

        psem->postFillCount();
    }

    pthread_exit(nullptr);
    return (void*)0;
}



void *consumer(void *voidArg) {
    auto arg = (GlobalArg*)voidArg;
    auto pqProduct = arg->pqProduct;
    auto psem = arg->psem;

    int data;

    for (;;) {
        psem->waitFillCount();

        data = pqProduct->front();
        pqProduct->pop();

        cout << "consumer " << data << endl;
        sleep(1);

        psem->postEmptyCount();
    }

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    pthread_t pidProduder[2];
    pthread_t pidConsumer;

    queue<int> qProduct;
    GlobalSemaphore sem;
    sem.init(0, 4);

    GlobalArg globalArg;
    globalArg.pqProduct = &qProduct;
    globalArg.psem = &sem;

    int ret = 0;

    GlobalArg globalArg0, globalArg1;
    globalArg0 = globalArg1 = globalArg;
    globalArg0.dataAddFactor = 0;
    globalArg1.dataAddFactor = 1000;

    ret = pthread_create(&pidProduder[0], nullptr, producer, (void*)&globalArg0);
    ret = pthread_create(&pidProduder[1], nullptr, producer, (void*)&globalArg1);
    ret = pthread_create(&pidConsumer, nullptr, consumer, (void*)&globalArg);

    pthread_join(pidProduder[0], nullptr);
    pthread_join(pidProduder[1], nullptr);
    pthread_join(pidConsumer, nullptr);

    return 0;
}
