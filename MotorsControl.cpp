#include "MotorsControl.h"
#include "Arduino.h"

//Define L298N Dual H-Bridge Motor Controller Pins
void MotorsControl::initMotors() {
  pinMode(dir1PinA, OUTPUT);
  pinMode(dir2PinA, OUTPUT);
  pinMode(speedPinA, OUTPUT);
  pinMode(dir1PinB, OUTPUT);
  pinMode(dir2PinB, OUTPUT);
  pinMode(speedPinB, OUTPUT);
}

//Keyboard Controls:
//
// Left-side wheels (motor 1):
// 1 - forward;
// 2 - stop;
// 3 - backwards.
//
// Right side wheels (motor 2):
// 4 - forward;
// 5 - stop;
// 6 - backwards.
void MotorsControl::processUserInput() {
  if (Serial.available() <= 0) return;

  int inByte = Serial.read();
  switch (inByte) {
    case '1':
      leftSideMotorSetForwardSpeed(maxSpeedValue);
      break;
  
    case '2':
      leftSideMotorStop();
      break;
  
    case '3':
      leftSideMotorSetBackwardsSpeed(maxSpeedValue);
      break;
  
    case '4':
      rightSideMotorSetForwardSpeed(maxSpeedValue);
      break;
  
    case '5':
      rightSideMotorStop();
      break;
  
    case '6':
      rightSideMotorSetBackwardsSpeed(maxSpeedValue);
      break;
  
    default:
      stopAllMotors(); // turn all motors off if an unmapped key is pressed
  }
}

void MotorsControl::leftSideMotorSetForwardSpeed(int speed) {
  analogWrite(speedPinA, speed); //Sets speed variable via PWM
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);
  Serial.println("Left-side wheels (motor 1) forward");
  Serial.println("   ");
}


void MotorsControl::leftSideMotorSetBackwardsSpeed(int speed) {
  analogWrite(speedPinA, speed);
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);
  Serial.println("Left-side wheels (motor 1) backwards");
  Serial.println("");
}

void MotorsControl::leftSideMotorStop() {
  analogWrite(speedPinA, 0);
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);
  Serial.println("Left-side wheels (motor 1) stop");
  Serial.println("   ");
}

void MotorsControl::rightSideMotorSetForwardSpeed(int speed) {
  analogWrite(speedPinB, speed);
  digitalWrite(dir1PinB, HIGH);
  digitalWrite(dir2PinB, LOW);
  Serial.println("Right-side wheels (motor 2) forward");
  Serial.println("   ");
}

void MotorsControl::rightSideMotorSetBackwardsSpeed(int speed) {
  analogWrite(speedPinB, speed);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
  Serial.println("Right-side wheels (motor 2) backwards");
  Serial.println("   ");
}

void MotorsControl::rightSideMotorStop() {
  analogWrite(speedPinB, 0);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
  Serial.println("Right-side wheels (motor 2) stop");
  Serial.println("   ");
}

void MotorsControl::stopAllMotors() {
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, LOW);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, LOW);
}
