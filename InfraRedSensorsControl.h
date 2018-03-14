#ifndef HEADER_IR_SENSORS_CONTROL
#define HEADER_IR_SENSORS_CONTROL

class InfraRedSensorsControl {
  public:
    const int distanceSensorLeftPin      = 8;
    const int distanceSensorRightPin     = 9;
    const int distanceSensorRearLeftPin  = 10;
    const int distanceSensorRearRightPin = 11;
   
    bool detectedLeft      = false;
    bool detectedRight     = false;
    bool detectedRearLeft  = false;
    bool detectedRearRight = false;

    static const int sensorReadingInterval = 100; // 100ms
    long sensorTimeLastRead = 0;
    int timeLastPrinted = 0;
    static const long printingInterval = 1000; // 1 sec

    void init();
    void readValues(long currentTime);
    void printValues();
};
   
#endif
