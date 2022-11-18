#ifndef __PIRSENSOR__
#define __PIRSENSOR__

class PirSensor {

    int pin;

    public:

    PirSensor(int pin);

    bool getSignal();
};

#endif