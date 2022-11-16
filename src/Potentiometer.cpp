#include "Potentiometer.h"
#include <Arduino.h>

Potentiometer::Potentiometer(int pin) {
    this->pin = pin;
}

double Potentiometer::getValue() {
    return ((double)analogRead(pin))/1024;
}