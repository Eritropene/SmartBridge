#include "WaterLevelControlTask.h"
#include <Arduino.h>

WaterLevelControlTask::WaterLevelControlTask(Led* alarmLed, Led* greenLed, Button* button, Potentiometer* pot, Servo* servoMotor, Sonar* sonar, LiquidCrystal_I2C* display) {
    this->alarmLed = alarmLed;
    this->greenLed = greenLed;
    this->button = button;
    this->pot = pot;
    this->servoMotor = servoMotor;
    this->sonar = sonar;
    this->display = display;

    alarmLed->setBlinkPeriod(1000);
    display->init();

    normalState();

    //messages
    MsgService.sendMsg("WL1:PRE_ALARM_THRESHOLD");
    MsgService.sendMsg("WL2:ALARM_THRESHOLD");
}

void WaterLevelControlTask::tick() {

    //water level measure timer
    if (millis() > measureTimer) {
        measureWaterLevel();
        measureTimer += measureTimeInterval;

        /*LCD print*/
        if (state == PRE_ALARM) {
            lcdPreAlarm();
        } else if (isInAlarmState()) {

        //send msg
        String msg = "MOTOR:";
        msg += motorAngle;
        MsgService.sendMsg(msg);
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
        if (button->buttonDown()) { //button pressed -> Manual Potentiometer
            manualPotAlarmState();
        } else if (MsgService.isMsgAvailable()) { //msg -> Manual Serial
            Msg* msg = MsgService.receiveMsg();
            if (msg->getContent() == "MANUAL") {
                manualSerialAlarmState();
            }
            delete msg;
        }
        //calculate angle
        motorAngle = (int)(180 - (waterLevel/ALARM_THRESHOLD) * 180);
        break;
    
    case MANUAL_POT:
        if (button->buttonDown()) { //button -> Auto
            autoAlarmState();
        }

        //calculate angle
        motorAngle = (int)(180 * pot->getValue());
        break;

    case MANUAL_SERIAL:
        if (MsgService.isMsgAvailable()) { //msg -> Auto
            Msg* msg = MsgService.receiveMsg();
            if (msg->getContent() == "AUTO") {
                autoAlarmState();
            } else if (msg->getContent()[0] == 'M') { // ex. "M:96"
                //calculate angle
                motorAngle = msg->getContent().substring(2).toInt();
            }
            delete msg;
        }
        break;
    }

    //move motor by angle
    servoMotor->write(motorAngle);
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
    autoAlarmState();
    measureTimeInterval = MEASURE_DELAY_ALARM;
    MsgService.sendMsg("STATE:ALARM");

    display->backlight();
    alarmLed->turnOn();
    greenLed->turnOff();
}

void WaterLevelControlTask::preAlarmState() {
    state = PRE_ALARM;
    measureTimeInterval = MEASURE_DELAY_PREALARM;
    MsgService.sendMsg("STATE:PREALARM");

    display->backlight();
    greenLed->turnOn();
    alarmLed->turnOff();
}

void WaterLevelControlTask::normalState() {
    state = NORMAL;
    measureTimeInterval = MEASURE_DELAY_NORMAL;
    MsgService.sendMsg("STATE:NORMAL");


    display->noBacklight();
    greenLed->turnOn();
    alarmLed->turnOff();

}

void WaterLevelControlTask::autoAlarmState() {
    alarmStateControl = AUTO;
    MsgService.sendMsg("AS:AUTO");
}

void WaterLevelControlTask::manualPotAlarmState() {
    alarmStateControl = MANUAL_POT;
    MsgService.sendMsg("AS:MPOT");
}

void WaterLevelControlTask::manualSerialAlarmState() {
    alarmStateControl = MANUAL_SERIAL;
    MsgService.sendMsg("AS:MSER");
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