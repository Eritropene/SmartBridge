#include <Arduino.h>
#include "Scheduler.h"
#include "LedControlTask.h"

Scheduler sch(2);

void setup() {
  //init MSgService
  MsgService.init();
  //create basic components
  Task* lct = new LedControlTask(new Led(2), new PirSensor(3), new LightSensor(A1,0.7));

  //create scheduler
  sch.addTask(lct);
}

void loop() {
  //run scheduling
  sch.executeTasks();
}