#include "Led.h"
#include <Arduino.h>

Led::Led(int pin) {
    this->pin = pin;
    pinMode(pin, OUTPUT);
    isOn = false;
}

void Led::turnOn() {
    digitalWrite(this->pin, HIGH);
    isOn = true;
}

void Led::turnOff() {
    digitalWrite(this->pin, LOW);
    isOn = false;
}

void Led::setBlinkPeriod(long period) {
    this->blinkPeriod = period;
}

void Led::blink() {
    if (t <= millis()) {
        t = millis() + blinkPeriod;
        if (isOn) {
            turnOff();
        } else {
            turnOn();
        }
    }
}