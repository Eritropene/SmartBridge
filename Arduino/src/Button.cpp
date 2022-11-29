#include "Button.h"
#include <Arduino.h>

Button::Button(int pin) {
    this->pin = pin;
    pinMode(pin, INPUT_PULLUP);
    pressed = false;
}

bool Button::buttonDown() {
    if (isPressed() && press) {
        press = false;
        return true;
    }
    return false;
}

bool Button::isPressed() {
    if (millis() >= t + sensibility) {
        t = millis();
        pressed = !(bool)digitalRead(pin);
    }
    if (!pressed) press = true;
    return pressed;
}

void Button::setSensibility(long millis) {
    this->sensibility = millis;
}