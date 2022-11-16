#ifndef __BUTTON__
#define __BUTTON__

/*Rappresenta un pulsante*/
class Button {

    int pin;
    bool pressed;
    long sensibility = 50;
    long t;

public:
    /*Crea un pulsante sul pin @pin*/
    Button(int pin);
    /*Ritorna true se premuto, false altrimenti*/
    bool isPressed();
    /*Setta la sensibilita' del debouncer. Default=50ms*/
    void setSensibility(long millis);
};

#endif