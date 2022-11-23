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

enum WaterLevelControlState {NORMAL, PRE_ALARM, ALARM};
enum AlarmState {AUTO, MANUAL_POT, MANUAL_SERIAL};

class WaterLevelControlTask: public Task {
public:
    WaterLevelControlTask(Led* alarmLed, Led* greenLed, Button* button, Potentiometer* pot, Servo* servoMotor, Sonar* sonar, LiquidCrystal_I2C* display);

    void normalState();

    void preAlarmState();

    void alarmState();

    void autoAlarmState();

    void manualPotAlarmState();

    void manualSerialAlarmState();


};

#endif