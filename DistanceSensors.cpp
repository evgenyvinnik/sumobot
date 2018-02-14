#include "DistanceSensors.h"
#include "Arduino.h"

void DistanceSensors::processSensors(long currentTime) {
  if(currentTime - infraredSensorTimeLastRead > infraredSensorReadingInterval) {
    infraredSensorValue = analogRead(infraredSensorPin);
    Serial.println(infraredSensorValue);

    infraredSensorTimeLastRead = millis();
  }
}

