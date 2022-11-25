#ifndef __LCTASK__
#define __LCTASK__
#include <Task.h>
#include <LightSensor.h>
#include <Led.h>
#include <PirSensor.h>

enum LedControlState {LED_ON, LED_OFF, LED_SHUTDOWN};

/*Rappresenta un Task eseguibile dallo Scheduler*/
class LedControlTask: public Task {

    LedControlState state;
    Led* led;
    PirSensor* pir;
    LightSensor* lightSensor;
    unsigned long shutdownTimer;
    unsigned long lightLevelSerialPrintTimer = 0;

public:
    /*Constructor, parametri sono il led, sensore PIR, e sensore di luce*/
    LedControlTask(Led* displayLed, PirSensor* pirSensor, LightSensor* lightSensor);

    /*Esegue il task. Questo metodo viene chiamato dallo Scheduler a ogni ciclo*/
    void tick();

private:
    /*Passa allo stato di LED acceso*/
    void LedOnState();

    /*Passa allo stato di attesa prima di spegnere il LED*/
    void LedShutdownState();

    /*Passa allo stato di LED spento*/
    void LedOffState();
};

#endif