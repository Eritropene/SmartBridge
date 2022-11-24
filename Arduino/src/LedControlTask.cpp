#include "LedControlTask.h"
#include <Arduino.h>

#define shutdownDelay 10000

LedControlTask::LedControlTask (Led* displayLed, PirSensor* pirSensor, LightSensor* lSensor) {
    led = displayLed;
    pir = pirSensor;
    lightSensor = lSensor;
}

void LedControlTask::tick() {

    // Send Light Sensor data to serial every 1 second
    if (millis() > lightLevelSerialPrintTimer) {
        String msg = "LIGHTLEVEL:";
        msg += lightSensor->getValue();
        MsgService.sendMsg(msg);
        lightLevelSerialPrintTimer = millis() + 1000;
    }

    // Switch to correct state if appropriate conditions are met
    switch (state) {
    case LED_OFF:
        if (!lightSensor->isAboveThreshold() && pir->getSignal()) {
            LedOnState();
        }
        break;
    
    case LED_ON:
        if (lightSensor->isAboveThreshold()) {
            LedOffState();
        } else if(!pir->getSignal()) {
            LedShutdownState();
        }
        break;

    case LED_SHUTDOWN:
        if (millis() > shutdownTimer || lightSensor->isAboveThreshold()) {
            LedOffState();
        } else if (pir->getSignal()) {
            LedOnState();
        }
        break;
    }
}

void LedControlTask::LedOnState() {
    led->turnOn();
    state = LED_ON;
    MsgService.sendMsg("LIGHT:ON");
}

/*Passa allo stato di attesa prima di spegnere il LED*/
void LedControlTask::LedShutdownState() {
    shutdownTimer = millis() + shutdownDelay;
    state = LED_SHUTDOWN;
}

/*Passa allo stato di LED spento*/
void LedControlTask::LedOffState() {
    led->turnOff();
    state = LED_OFF;
    MsgService.sendMsg("LIGHT:OFF");
}