#ifndef HEADER_LINE_SENSORS
#define HEADER_LINE_SENSORS

// Infra-red line sensors, digital pins
// Value when black surface: 1, LED is OFF.
// Value when white line encountered: 0, LED is ON.
class LineSensors {
  public:
    static const long readingInterval = 50; // 50ms
    static const long printingInterval = 1000; // 1 sec
    long timeLastRead = 0, timeLastPrinted = 0;

    const int lineSensorIRFrontRightPin = 8;
    const int lineSensorIRFrontLeftPin  = 9;
    const int lineSensorIRRearRightPin  = 10;
    const int lineSensorIRRearLeftPin   = 11;

    int lineSensorIRFrontRightValue     = 1;
    int lineSensorIRFrontLeftValue      = 1;
    int lineSensorIRRearRightValue      = 1;
    int lineSensorIRRearLeftValue       = 1;

    void initSensors();
    void processSensors(long currentTime);
    
    void readSensors();
    void printValues();
};

#endif
