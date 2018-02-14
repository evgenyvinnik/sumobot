#include "Arduino.h"
#include "MotorsControl.h"
#include "LineSensors.h"

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

void MotorsControl::goForward(int speed) {
  leftSideMotorSetForwardSpeed(speed);
  rightSideMotorSetForwardSpeed(speed);
}

void MotorsControl::goBackwards(int speed) {
  leftSideMotorSetBackwardsSpeed(speed);
  rightSideMotorSetBackwardsSpeed(speed);
}

void MotorsControl::leftSideMotorSetForwardSpeed(int speed) {
  speed = normalizeSpeedValue(speed);
  analogWrite(speedPinA, speed); //Sets speed variable via PWM
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);
//  Serial.println("Left-side wheels (motor 1) forward");
//  Serial.println("   ");
}

void MotorsControl::leftSideMotorSetBackwardsSpeed(int speed) {
  speed = normalizeSpeedValue(speed);
  analogWrite(speedPinA, speed);
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);
//  Serial.println("Left-side wheels (motor 1) backwards");
//  Serial.println("");
}

void MotorsControl::leftSideMotorStop() {
  analogWrite(speedPinA, 0);
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);
//  Serial.println("Left-side wheels (motor 1) stop");
//  Serial.println("   ");
}

void MotorsControl::rightSideMotorSetForwardSpeed(int speed) {
  speed = normalizeSpeedValue(speed);
  analogWrite(speedPinB, speed);
  digitalWrite(dir1PinB, HIGH);
  digitalWrite(dir2PinB, LOW);
//  Serial.println("Right-side wheels (motor 2) forward");
//  Serial.println("   ");
}

void MotorsControl::rightSideMotorSetBackwardsSpeed(int speed) {
  speed = normalizeSpeedValue(speed);
  analogWrite(speedPinB, speed);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
//  Serial.println("Right-side wheels (motor 2) backwards");
//  Serial.println("   ");
}

void MotorsControl::rightSideMotorStop() {
  analogWrite(speedPinB, 0);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
//  Serial.println("Right-side wheels (motor 2) stop");
//  Serial.println("   ");
}

void MotorsControl::stopAllMotors() {
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, LOW);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, LOW);
}

int MotorsControl::normalizeSpeedValue(int speed) {
  if(speed < 0) speed = 0;
  if(speed > maxSpeedValue) speed = maxSpeedValue;
  return speed;
}

void MotorsControl::reverse(int duration) {
  leftSideMotorSetBackwardsSpeed(maxSpeedValue/2);
  rightSideMotorSetBackwardsSpeed(maxSpeedValue/2);
  delay(duration);
}

void MotorsControl::turnRight(int duration) {
  leftSideMotorSetForwardSpeed(maxSpeedValue/2);
  rightSideMotorSetBackwardsSpeed(maxSpeedValue/2);
  delay(duration);
}

void MotorsControl::turnLeft(int duration) {
  leftSideMotorSetBackwardsSpeed(maxSpeedValue/2);
  rightSideMotorSetForwardSpeed(maxSpeedValue/2);
  delay(duration);
}

// https://www.robolink.com/programming-the-sumo-bot/
// https://www.pololu.com/docs/0J57/7.b
// https://github.com/pololu/zumo-shield/blob/master/ZumoExamples/examples/BorderDetect/BorderDetect.ino
// TODO: don't hardcode the speed, save the previous speed, and restore after the maneuver
// TODO: don't use the delay() - the forever loop should never be stalled (as that makes the whole thing non-realtime),
// use a non-blocking queue of messages (with timestamps on when it should be processed) that is polled in a forever loop
// TODO: ensure that when a maneuver is already in progress another maneuver doesn't start. Use a flag on maneuver_in_progress=true.
void MotorsControl::adjustDirectionIfGettingOutOfArea(LineSensors lineSensors, long currentTime) {
  if(currentTime - timeDirectionLastAdjusted < directionAdjustmentTimeInterval) return;

  // front left sensor detected a white line, reverse and turn to the right
  if (lineSensors.lineSensorIRFrontLeftValue == 0) {
    reverse(adjustDirectionReverseDuration);
    turnRight(adjustDirectionTurnDuration);
    goForward(maxSpeedValue/2);
  }

  // front right sensor detected a white line, reverse and turn to the left
  else if (lineSensors.lineSensorIRFrontRightValue == 0) {
    reverse(adjustDirectionReverseDuration);
    turnLeft(adjustDirectionTurnDuration);
    goForward(maxSpeedValue/2);
  }
  else { // keep going forward
    goForward(maxSpeedValue/2);
  }

  timeDirectionLastAdjusted = millis();
}
