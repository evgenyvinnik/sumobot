#include "UltraSoundSensors.h"
#include "Arduino.h"

void UltraSoundSensors::initSensors() {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void UltraSoundSensors::processSensors(long currentTime) {
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
      duration = pulseIn(echoPin, HIGH);
     
      // convert the time into a distance
      distanceCm = (duration / 2) / 29.1;
      distanceInches = (duration / 2) / 74; 

      ultraSoundSensorTimeLastRead = millis();
  }
  if(currentTime - timeLastPrinted > printingInterval) {
    printValues();
  }
}


void UltraSoundSensors::printValues() {
  Serial.print("ultraSound distance cm: ");
  Serial.println(distanceCm);
  
  timeLastPrinted = millis();
}