#include "Sonar.h"
#include <Arduino.h>

Sonar::Sonar(int trig, int echo) {
    pinMode(trig, OUTPUT);
    pinMode(echo, OUTPUT);
    trigPin = trig;
    echoPin = echo;
}

Sonar::Sonar(int trig, int echo, float newVs) {
    pinMode(trig, OUTPUT);
    pinMode(echo, OUTPUT);
    trigPin = trig;
    echoPin = echo;
    vs = newVs;
}

/* Returns the distance in meters*/
float Sonar::getDistance()
{
    /* Send pulse */
    digitalWrite(trigPin,LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin,LOW);
    
    /* Get echo */
    float tUS = pulseIn(echoPin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t*vs;
    return d;
}