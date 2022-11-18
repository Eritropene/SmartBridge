#include "LedControlTask.h"

LedControlTask::LedControlTask (Led* displayLed, PirSensor* pirSensor, LightSensor* lSensor) {
    led = displayLed;
    pir = pirSensor;
    lightSensor = lSensor;
}

void LedControlTask::tick() {
    switch (state) {
    case LED_OFF:
        /* code */
        break;
    
    case LED_ON:
        
        break;

    case LED_SHUTDOWN:

        break;
    
    default:
        break;
    }
}

void LedControlTask::LedOnState() {
    led->turnOn();
    state = LED_ON;
}

/*Passa allo stato di attesa prima di spegnere il LED*/
void LedControlTask::LedShutdownState() {
    state = LED_SHUTDOWN;
}

/*Passa allo stato di LED spento*/
void LedControlTask::LedOffState() {
    led->turnOff();
    state = LED_OFF;
}