#ifndef __POT__
#define __POT__

/* Rappresenta un potenziometro */
class Potentiometer {

    int pin;

public:
    /* Crea un potenziometro sul pin @pin */
    Potentiometer(int pin);
    /* Il valore letto dal potenziometro. E' compreso tra 0 e 1 inclusi */
    double getValue();

};

#endif