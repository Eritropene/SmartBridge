#ifndef __TASK__
#define __TASK__

/*Rappresenta un Task eseguibile dallo Scheduler*/
class Task {
public:
    /*Esegue il task. Questo metodo viene chiamato dallo Scheduler a ogni ciclo*/
    virtual void tick() = 0;
};

#endif