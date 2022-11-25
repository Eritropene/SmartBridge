#include "WaterLevelControlTask.h"
#include <Arduino.h>

WaterLevelControlTask::WaterLevelControlTask(Led* alarmLed, Led* greenLed, Button* button, Potentiometer* pot, Servo* servoMotor, Sonar* sonar, LiquidCrystal_I2C* display) {
    this->alarmLed = alarmLed;
    this->greenLed = alarmLed;
    this->button = button;
    this->pot = pot;
    this->servoMotor = servoMotor;
    this->sonar = sonar;
    this->display = display;

    alarmLed->setBlinkPeriod(1000);
    display->init();
}

void WaterLevelControlTask::tick() {

    if (millis() > measureTimer) {
        measureWaterLevel();
        measureTimer += measureTimeInterval;

        /*LCD print*/
        if (state == PRE_ALARM) {
            lcdPreAlarm();
        } else if (isInAlarmState()) {
            lcdAlarm();
        }
    }

    switch (state)
    {
    case NORMAL:
        if (waterLevel < ALARM_THRESHOLD) {
            alarmState();
        } else if (waterLevel < PRE_ALARM_THRESHOLD) {
            preAlarmState();
        }
        break;
    
    case PRE_ALARM:
        if (waterLevel < ALARM_THRESHOLD) {
            alarmState();
        } else if (waterLevel > PRE_ALARM_THRESHOLD) {
            normalState();
        }
        alarmLed->blink();
        break;

    case ALARM:
        alarmTick();
        if (waterLevel > PRE_ALARM_THRESHOLD) {
            normalState();
        } else if (waterLevel > ALARM_THRESHOLD) {
            preAlarmState();
        }
        break;
    }
}

void WaterLevelControlTask::alarmTick() {

    

    switch (alarmStateControl) {
    case AUTO:
        if (button->buttonDown()) {
            manualPotAlarmState();
        } else if (MsgService.isMsgAvailable()) {
            Msg* msg = MsgService.receiveMsg();
            if (msg->getContent() == "MANUAL") {
                manualSerialAlarmState();
            }
            delete msg;
        } else {
            servoMotor->write((180 - waterLevel * 360));
        }
        break;
    
    case MANUAL_POT:
        if (button->buttonDown()) {

        }
        break;

    case MANUAL_SERIAL:
        break;
    }
}

bool WaterLevelControlTask::isInAlarmState() {
    return state == ALARM;
}

void WaterLevelControlTask::measureWaterLevel() {
    waterLevel = sonar->getDistance();
    String msg = "WATERLEVEL:";
    msg += waterLevel;
    MsgService.sendMsg(msg);
}

void WaterLevelControlTask::alarmState() {
    state = ALARM;
    alarmStateControl = AUTO;
    measureTimeInterval = MEASURE_DELAY_ALARM;
    MsgService.sendMsg("STATE:ALARM");

    display->backlight();
    alarmLed->turnOn();
}

void WaterLevelControlTask::preAlarmState() {
    state = PRE_ALARM;
    measureTimeInterval = MEASURE_DELAY_ALARM;
    MsgService.sendMsg("STATE:PREALARM");

    display->backlight();
    greenLed->turnOn();
    alarmLed->turnOff();
}

void WaterLevelControlTask::normalState() {
    state = NORMAL;
    measureTimeInterval = MEASURE_DELAY_NORMAL;

    display->noBacklight();
    greenLed->turnOn();
    alarmLed->turnOff();

}

void WaterLevelControlTask::lcdPreAlarm() {
    display->setCursor(0, 0);
    display->print("PRE-ALARM       ");
    display->setCursor(0, 1);
    display->print("WL=");
    display->setCursor(3, 1);
    display->print(waterLevel);
}

void WaterLevelControlTask::lcdAlarm() {
    display->setCursor(0, 0);
    display->print("ALARM  angle=");
    display->setCursor(13, 0);
    display->print(motorAngle);
    display->setCursor(0, 1);
    display->print("WL=");
    display->setCursor(3, 1);
    display->print(waterLevel);
}