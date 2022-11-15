#include "Task.h"
#include <Arduino.h>

bool Task::canRun() {
    return millis() >= t;
}

void Task::run() {
    if (canRun()) action();
}

void Task::sleep(unsigned long time) {
    t = millis() + time;
}