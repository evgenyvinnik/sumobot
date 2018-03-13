#include "InfraRedSensor.h"
#include "Arduino.h"

InfraRedSensor::InfraRedSensor(const char* name, int sensorPin) {
  this->name = name;
  this->sensorPin = sensorPin;
}

void InfraRedSensor::init() {
  pinMode(sensorPin, INPUT);
}

void InfraRedSensor::readValue(long currentTime) {
  if(currentTime - sensorTimeLastRead > sensorReadingInterval) {
    detected = analogRead(sensorPin) < 50 ? true : false;
    
    if(currentTime - timeLastPrinted > printingInterval) printValues();
    sensorTimeLastRead = millis();
  }
}

void InfraRedSensor::printValues() {
  Serial.print(name); Serial.print(" infrared sensor, object detected: "); Serial.println(detected);
  timeLastPrinted = millis();
}

