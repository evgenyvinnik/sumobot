#ifndef HEADER_IR_SENSOR
#define HEADER_IR_SENSOR

#define LEFT_IR_PIN       8
#define RIGHT_IR_PIN      9
#define REAR_LEFT_IR_PIN  10
#define REAR_RIGHT_IR_PIN 11

class InfraRedSensor {
  public:
    const char* name;
    int sensorPin; // Infrared sensor, analog pin
    static const int sensorReadingInterval = 100; // 100ms
    bool detected = false;
    long sensorTimeLastRead = 0;
    int timeLastPrinted = 0;
    static const long printingInterval = 1000; // 1 sec

    InfraRedSensor(const char* name, int sensorPin);
    void init();
    void readValue(long currentTime);
    void printValues();
};
   
#endif
