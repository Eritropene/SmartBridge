#include "Button.h"
#include <Arduino.h>

Button::Button(int pin) {
    this->pin = pin;
    pinMode(pin, INPUT);
    pressed = false;
}

bool Button::isPressed() {
    if (millis() > t + sensibility) {
        t = millis();
        pressed = (bool)digitalRead(pin);
    }
    return pressed;
}

void Button::setSensibility(long millis) {
    this->sensibility = millis;
}