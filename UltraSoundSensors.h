#ifndef HEADER_ULTRASOUND_SENSORS
#define HEADER_ULTRASOUND_SENSORS

/* Ultrasonic sensor Pins:
    VCC: +5VDC
    Trig : Trigger (INPUT) - Pin11
    Echo: Echo (OUTPUT) - Pin 12
    GND: GND
*/

class UltraSoundSensors {
  public:
    const int triggerPin = 4;
    const int echoPin = 3;
    static const int ultraSoundSensorReadingInterval = 100; // 100ms
    long duration, distanceCm, distanceInches;
    long ultraSoundSensorTimeLastRead = 0;
    long timeLastRead = 0, timeLastPrinted = 0;
    static const long printingInterval = 1000; // 1 sec

    void initSensors();
    void processSensors(long currentTime);
    void printValues();
};
   
#endif
