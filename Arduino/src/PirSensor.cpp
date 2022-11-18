#include "PirSensor.h"
#include <Arduino.h>

PirSensor::PirSensor(int pin) {
    this->pin = pin;
}

bool PirSensor::getSignal() {
    return (bool)digitalRead(pin);
}