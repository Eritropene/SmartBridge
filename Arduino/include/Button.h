#ifndef __BUTTON__
#define __BUTTON__ 

/*Rappresenta un pulsante*/
class Button {

    int pin;
    bool pressed;
    bool press = true;
    unsigned long sensibility = 50;
    unsigned long t = 0;

public:
    /*Crea un pulsante sul pin @pin*/
    Button(int pin);
    /*Ritorna true se premuto, false altrimenti*/
    bool isPressed();

    bool buttonDown();
    /*Setta la sensibilita' del debouncer. Default=50ms*/
    void setSensibility(long millis);
};

#endif