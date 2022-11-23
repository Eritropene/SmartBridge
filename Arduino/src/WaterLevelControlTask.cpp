#include "WaterLevelControlTask.h"
#include <Arduino.h>

void WaterLevelControlTask::tick () {
    switch (state)
    {
    case NORMAL:
        /* code */
        break;
    
    case PRE_ALARM:
        break;

    case ALARM:
        break;
    }
}

void WaterLevelControlTask::alarmState() {
    state = ALARM;
    alarmStateControl = AUTO;
}