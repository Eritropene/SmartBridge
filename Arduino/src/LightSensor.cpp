#include "LightSensor.h"
#include <Arduino.h>

LightSensor::LightSensor(int pin, float thresholdValue) {
    this->pin = pin;
    threshold = thresholdValue;
}

float LightSensor::getValue() {
    value = analogRead(pin);
    value /= 1024;
    return value;
}

bool LightSensor::isAboveThreshold() {
    return getValue() > threshold;
}

float LightSensor::getThreshold() {
    return threshold;
}