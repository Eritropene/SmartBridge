#ifndef __LED__
#define __LED__

/*Rappresenta un Led*/
class Led {
    
    int pin;
    unsigned long blinkPeriod = 1000;
    unsigned long t = 0;
    bool isOn;

public:
    /*Crea un Led collegato al pin @pin*/
    Led(int pin);
    /*Accende il Led*/
    void turnOn();
    /*Spegne il Led*/
    void turnOff();
    /*Setta il periodo del blink a @period ms. Default=1000ms*/
    void setBlinkPeriod(long period);
    /*Lampeggia. Da chiamare in loop*/
    void blink();
};

#endif