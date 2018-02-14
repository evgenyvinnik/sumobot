#include "LineSensors.h"
#include "Arduino.h"

void LineSensors::initSensors() {
  pinMode(lineSensorIRFrontRightPin, INPUT);
  pinMode(lineSensorIRFrontLeftPin,  INPUT);
  pinMode(lineSensorIRRearRightPin,  INPUT);
  pinMode(lineSensorIRRearLeftPin,   INPUT);
}

void LineSensors::processSensors(long currentTime) {
  if(currentTime - timeLastRead > readingInterval) {
    readSensors();
    printValues();
  }
}

void LineSensors::readSensors() {
  lineSensorIRFrontRightValue = digitalRead(lineSensorIRFrontRightPin);
  lineSensorIRFrontLeftValue = digitalRead(lineSensorIRFrontLeftPin);
  lineSensorIRRearRightValue = digitalRead(lineSensorIRRearRightPin);
  lineSensorIRRearLeftValue = digitalRead(lineSensorIRRearLeftPin);

  timeLastRead = millis();
}

void LineSensors::printValues() {
  Serial.print("lineSensorIRFrontRightValue = ");
  Serial.println(lineSensorIRFrontRightValue);

  Serial.print("lineSensorIRFrontLeftValue = ");
  Serial.println(lineSensorIRFrontLeftValue);

  Serial.print("lineSensorIRRearRightValue = ");
  Serial.println(lineSensorIRRearRightValue);

  Serial.print("lineSensorIRRearLeftValue = ");
  Serial.println(lineSensorIRRearLeftValue);

  Serial.println();
}

