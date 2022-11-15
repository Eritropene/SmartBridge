#ifndef __TASK__
#define __TASK__

/*Rappresenta un Task eseguibile dallo Scheduler*/
class Task {

    unsigned long t = 0;
    
private:
    bool canRun();

public:
    /*L'azione da eseguire quando il task e' attivo*/
    virtual void action() = 0;

    /*Blocca l'esecuzione del task per @time millisecondi*/
    void sleep(unsigned long time);

    /*Esegue il task. Questo metodo viene chiamato dallo Scheduler a ogni ciclo*/
    void run();
};

#endif