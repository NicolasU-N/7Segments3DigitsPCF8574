#include "PWM.h"
#include "LTC4624.h"
#include <TaskScheduler.h> //https://github.com/arkhipenko/TaskScheduler

LTC4624 Mylcd; //initialize LCD

Scheduler runner;

void t0Callback();

Task t0(7, TASK_FOREVER, &t0Callback, &runner, true); //every 7 milliseconds

//------------------------------------------------------------ TASKS
void t0Callback() {
  Mylcd.lcdScan();
}

void setup() {
  Serial.begin(115200);
 
  // Init PWM PINS
  PWMInit();
  PWMOn();
  setDutyPWMPB1(0);
  setDutyPWMPB2(0);
  setDutyPWMPB3(0);
  setDutyPWMPD3(0);

  Mylcd.lcdInit();
  Mylcd.setDutyCycleLcd(255);

  Mylcd.lcdPrint(0, "123");

  Mylcd.lcdDot(0, 0);
  Mylcd.lcdDot(1, 0);
  Mylcd.lcdDot(2, 0);

  runner.startNow();  // set point-in-time for scheduling start
}


void loop() {
  runner.execute();
}
