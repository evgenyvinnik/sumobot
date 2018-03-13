#include "MotorsControl.h"
#include "LineSensors.h"
#include "DistanceSensors.h"
#include "UltraSoundSensor.h"

long loopCounter = 0;
long currentTime = 0;

MotorsControl motorsControl;
LineSensors lineSensors;
DistanceSensors distanceSensors;
UltraSoundSensor frontSonar("Front", FRONT_TRIGGER, FRONT_ECHO);
UltraSoundSensor rearSonar("Rear", REAR_TRIGGER, REAR_ECHO);

void setup() {
  Serial.begin(9600); // initialize serial communication @ 9600 baud

  motorsControl.initMotors();
  lineSensors.initSensors();
  motorsControl.goForward(MotorsControl::maxSpeedValue/2);
  frontSonar.initPins();
  rearSonar.initPins();
}

void loop() {
  loopCounter++;
  currentTime = millis();

//  lineSensors.processSensors(currentTime);
  motorsControl.adjustDirectionIfGettingOutOfArea(lineSensors, currentTime);
//  motorsControl.processUserInput();
  frontSonar.sendPing(currentTime);
  rearSonar.sendPing(currentTime);
}
