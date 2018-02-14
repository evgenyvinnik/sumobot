#ifndef HEADER_DISTANCE_SENSORS
#define HEADER_DISTANCE_SENSORS

class DistanceSensors {
  public:
    // Infrared sensor, analog pin
    const int infraredSensorPin = 0;
    static const int infraredSensorReadingInterval = 500; // 500ms
    int infraredSensorValue = 0;
    long infraredSensorTimeLastRead = 0;

    void processSensors(long currentTime);
};
   
#endif
