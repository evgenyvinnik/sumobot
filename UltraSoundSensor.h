#ifndef HEADER_ULTRASOUND_SENSOR
#define HEADER_ULTRASOUND_SENSOR

#define FRONT_TRIGGER 2
#define FRONT_ECHO    3
#define REAR_TRIGGER  12
#define REAR_ECHO     13

class UltraSoundSensor {
  public:
    const char* name;
    int triggerPin;
    int echoPin;
    static const int ultraSoundSensorReadingInterval = 100; // 100ms
    long duration, distanceCm, distanceInches;
    long ultraSoundSensorTimeLastRead = 0;
    long timeLastRead = 0, timeLastPrinted = 0;
    static const long printingInterval = 1000; // 1 sec

    UltraSoundSensor(const char* name, int triggerPin, int echoPin);
    void initPins();
    void sendPing(long currentTime);
    void printValues();
};
   
#endif
