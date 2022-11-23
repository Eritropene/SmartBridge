#ifndef __SONAR__
#define __SONAR__

class Sonar {

    int trigPin;
    int echoPin;
    float vs = 331.45 + 0.62*20;
    

public:
    Sonar(int trig, int echo);
    
    Sonar(int trig, int echo, float vs);

    float getDistance();
};

#endif