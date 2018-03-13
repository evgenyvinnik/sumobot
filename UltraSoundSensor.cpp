#include "UltraSoundSensor.h"
#include "Arduino.h"

UltraSoundSensor::UltraSoundSensor(const char* name, int triggerPin, int echoPin) {
  this->name = name;
  this->triggerPin = triggerPin;
  this->echoPin = echoPin;
}

void UltraSoundSensor::initPins() {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void UltraSoundSensor::sendPing(long currentTime) {
  if(currentTime - ultraSoundSensorTimeLastRead > ultraSoundSensorReadingInterval) {
    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(5);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    // Read the signal from the sensor: a HIGH pulse whose
    // duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    duration = pulseIn(echoPin, HIGH, 60000); // timeout each 60ms, as full 4 meter distance is measured in less than 30ms.
    distanceCm = duration * 0.0343/2;  // Speed of sound = 0.0343cm/microsec
    if(distanceCm<0 || distanceCm>400) distanceCm = 0;

    if(currentTime - timeLastPrinted > printingInterval) printValues();
    ultraSoundSensorTimeLastRead = millis();
  }
}

void UltraSoundSensor::printValues() {
  Serial.print(this->name); Serial.print(" sonar cm: "); Serial.println(distanceCm);
  timeLastPrinted = millis();
}

