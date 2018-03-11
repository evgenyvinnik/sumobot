#include "MotorsControl.h"
#include "LineSensors.h"
#include "DistanceSensors.h"
#include "UltraSoundSensors.h"

long loopCounter = 0;
long currentTime = 0;

MotorsControl motorsControl;
LineSensors lineSensors;
DistanceSensors distanceSensors;
UltraSoundSensors ultraSoundSensors;

void setup() {
  Serial.begin(9600); // initialize serial communication @ 9600 baud

  motorsControl.initMotors();
  lineSensors.initSensors();
  motorsControl.goForward(MotorsControl::maxSpeedValue/2);
}

void loop() {
  loopCounter++;
  currentTime = millis();

  lineSensors.processSensors(currentTime);
  motorsControl.adjustDirectionIfGettingOutOfArea(lineSensors, currentTime);
//  motorsControl.processUserInput();
  ultraSoundSensors.processSensors(currentTime);
}
