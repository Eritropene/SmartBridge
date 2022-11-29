#include <Arduino.h>
#include "Scheduler.h"
#include "LedControlTask.h"

Scheduler sch(2);

void setup() {
  //init MSgService
  MsgService.init();
  //create basic components
  Servo* servoMotor = new Servo();
  servoMotor->attach(9);
  Task* wlct = new WaterLevelControlTask(new Led(7), new Led(6), new Button(8), new Potentiometer(A0), servoMotor, new Sonar(10, 11), new LiquidCrystal_I2C(0x27, 16, 2));
  Task* lct = new LedControlTask(new Led(2), new PirSensor(3), new LightSensor(A1,0.7), (WaterLevelControlTask*)wlct);
  //create scheduler
  sch.addTask(lct);
  sch.addTask(wlct);
}

void loop() {
  //run scheduling
  sch.executeTasks();
}