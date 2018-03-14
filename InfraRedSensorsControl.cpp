#include "InfraRedSensorsControl.h"
#include "Arduino.h"

void InfraRedSensorsControl::init() {
  pinMode(distanceSensorLeftPin, INPUT);
  pinMode(distanceSensorRightPin, INPUT);
  pinMode(distanceSensorRearLeftPin, INPUT);
  pinMode(distanceSensorRearRightPin, INPUT);
}

void InfraRedSensorsControl::readValues(long currentTime) {
  if(currentTime - sensorTimeLastRead > sensorReadingInterval) {
    detectedLeft      = analogRead(distanceSensorLeftPin)      < 50 ? true : false;
    detectedRight     = analogRead(distanceSensorRightPin)     < 50 ? true : false;
    detectedRearLeft  = analogRead(distanceSensorRearLeftPin)  < 50 ? true : false;
    detectedRearRight = analogRead(distanceSensorRearRightPin) < 50 ? true : false;

    Serial.print("Time: "); Serial.println(currentTime);
    if(currentTime - timeLastPrinted > printingInterval) printValues();
    sensorTimeLastRead = millis();
  }
}

void InfraRedSensorsControl::printValues() {
  Serial.print("Left infrared sensor, object detected: "); Serial.println(detectedLeft);
  Serial.print("Right infrared sensor, object detected: "); Serial.println(detectedRight);
  Serial.print("Rear Left infrared sensor, object detected: "); Serial.println(detectedRearLeft);
  Serial.print("Rear Right infrared sensor, object detected: "); Serial.println(detectedRearRight);
  timeLastPrinted = millis();
}

