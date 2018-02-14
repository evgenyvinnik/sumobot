#include "MotorsControl.h"
#include "LineSensors.h"
#include "DistanceSensors.h"

long loopCounter = 0;
long currentTime = 0;

MotorsControl motorsControl;
LineSensors lineSensors;
DistanceSensors distanceSensors;

void setup() {
  Serial.begin(9600); // initialize serial communication @ 9600 baud

  motorsControl.initMotors();
  lineSensors.initSensors();
}

void loop() {
  loopCounter++;
  currentTime = millis();

  motorsControl.processUserInput();
  lineSensors.processSensors(currentTime);
//  distanceSensors.processSensors(currentTime);
}

