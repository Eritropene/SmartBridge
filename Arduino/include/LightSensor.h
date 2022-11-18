#ifndef __LIGHTSENSOR__
#define __LIGHTSENSOR__

class LightSensor {

    int pin;
    float value;
    float threshold;

    public:

    LightSensor(int pin, float thresholdValue);

    float getValue();

    bool isAboveThreshold();
};

#endif