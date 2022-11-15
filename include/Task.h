#ifndef __TASK__
#define __TASK__

#include <Arduino.h>

/*Rappresenta un Task eseguibile dallo Scheduler*/
class Task {
private:
    unsigned long t = 0;
    bool canRun() {
        return millis() >= t;
    }
public:
    /*Il task vero e proprio, da implementare*/
    virtual void action() = 0;

    /*Blocca l'esecuzione del task per @time millisecondi*/
    void sleep(unsigned long time) {
        t = millis() + time;
    }

    /*Esegue il task. Questo metodo viene chiamato dallo Scheduler a ogni ciclo*/
    void run() {
        if (canRun()) action();
    }
};

#endif