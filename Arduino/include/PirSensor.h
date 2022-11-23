#ifndef __PIRSENSOR__
#define __PIRSENSOR__

class PirSensor {

    int pin;

    public:
    /* Crea un oggetto di un sensore PIR */
    PirSensor(int pin);

    bool getSignal();
};

#endif