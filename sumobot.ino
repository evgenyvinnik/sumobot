#include "MotorsControl.h"
#include "LineSensors.h"
#include "InfraRedSensor.h"
#include "UltraSoundSensor.h"

long loopCounter = 0;
long currentTime = 0;

MotorsControl motorsControl;
LineSensors lineSensors;
InfraRedSensor leftIRSensor("Left", LEFT_IR_PIN);
InfraRedSensor rightIRSensor("Right", RIGHT_IR_PIN);
InfraRedSensor rearLeftIRSensor("Rear left", REAR_LEFT_IR_PIN);
InfraRedSensor rearRightIRSensor("Rear right", REAR_RIGHT_IR_PIN);
UltraSoundSensor frontSonar("Front", FRONT_TRIGGER, FRONT_ECHO);
UltraSoundSensor rearSonar("Rear", REAR_TRIGGER, REAR_ECHO);

void setup() {
  Serial.begin(9600); // initialize serial communication @ 9600 baud

  motorsControl.initMotors();
  lineSensors.initSensors();
  motorsControl.goForward(MotorsControl::maxSpeedValue/2);
  leftIRSensor.init();
  rightIRSensor.init();
  rearLeftIRSensor.init();
  rearRightIRSensor.init();
  frontSonar.initPins();
  rearSonar.initPins();
}

void loop() {
  loopCounter++;
  currentTime = millis();

//  lineSensors.processSensors(currentTime);
  motorsControl.adjustDirectionIfGettingOutOfArea(lineSensors, currentTime);
//  motorsControl.processUserInput();
  frontSonar.sendPing(currentTime);
  rearSonar.sendPing(currentTime);
  leftIRSensor.readValue(currentTime);
  rightIRSensor.readValue(currentTime);
  rearLeftIRSensor.readValue(currentTime);
  rearRightIRSensor.readValue(currentTime);
}
