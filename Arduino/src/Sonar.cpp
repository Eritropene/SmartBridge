#include "Sonar.h"
#include <Arduino.h>

Sonar::Sonar(int trig, int echo) {
    trigPin = trig;
    echoPin = echo;
}

Sonar::Sonar(int trig, int echo, float newVs) {
    trigPin = trig;
    echoPin = echo;
    vs = newVs;
}

float Sonar::getDistance()
{
    /* invio impulso */
    digitalWrite(trigPin,LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin,LOW);
    
    /* ricevi l’eco */
    float tUS = pulseIn(echoPin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t*vs;
    return d;
}