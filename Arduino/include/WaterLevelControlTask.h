#ifndef __WLCTASK__
#define __WLCTASK__
#include "Task.h"
#include "Potentiometer.h"
#include "Led.h"
#include "Button.h"
#include "Sonar.h"
#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

#define MEASURE_DELAY_NORMAL 1000
#define MEASURE_DELAY_ALARM 500
#define PRE_ALARM_THRESHOLD 1.0
#define ALARM_THRESHOLD 0.5

enum WaterLevelControlState {NORMAL, PRE_ALARM, ALARM};
enum AlarmStateControl {AUTO, MANUAL_POT, MANUAL_SERIAL};

class WaterLevelControlTask: public Task {
private:

    unsigned int measureTimeInterval = MEASURE_DELAY_NORMAL;
    unsigned long measureTimer = 0;
    float waterLevel = 0;
    int motorAngle = 0;

    WaterLevelControlState state;
    AlarmStateControl alarmStateControl;

    Led* alarmLed;
    Led* greenLed;
    Button* button;
    Potentiometer* pot;
    Servo* servoMotor;
    Sonar* sonar;
    LiquidCrystal_I2C* display;

    void measureWaterLevel();

    void lcdPreAlarm();

    void lcdAlarm();

public:
    WaterLevelControlTask(Led* alarmLed, Led* greenLed, Button* button, Potentiometer* pot, Servo* servoMotor, Sonar* sonar, LiquidCrystal_I2C* display);

    void normalState();

    void preAlarmState();

    void alarmState();

    void autoAlarmState();

    void manualPotAlarmState();

    void manualSerialAlarmState();

    void tick();

    void alarmTick();

    bool isInAlarmState();
};

#endif