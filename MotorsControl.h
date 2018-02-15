#ifndef HEADER_MOTORS_CONTROL
#define HEADER_MOTORS_CONTROL

#include "LineSensors.h"

class MotorsControl {
  public:
    // Declare L298N Dual H-Bridge Motor Controller directly since there is no library to load
    
    //arduino uno pins
    // Motor 1
    //const int dir1PinA = 2;
    //const int dir2PinA = 3;
    //const int speedPinA = 9; // Needs to be a PWM pin to be able to control motor speed
    
    // Motor 2
    //const int dir1PinB = 4;
    //const int dir2PinB = 5;
    //const int speedPinB = 10; // Needs to be a PWM pin to be able to control motor speed
    
    //arduino mega pins
    // Motor 1, wheels on the left side.
    const int dir1PinA = 30;
    const int dir2PinA = 31;
    const int speedPinA = 6; // Needs to be a PWM pin to be able to control motor speed
    
    // Motor 2, wheels on the right side.
    const int dir1PinB = 32;
    const int dir2PinB = 33;
    const int speedPinB = 5; // Needs to be a PWM pin to be able to control motor speed

    static const int maxSpeedValue = 254;

    void initMotors();
    void processUserInput();

    void goForward(int speed, int duration = 0);
    void goBackward(int speed, int duration = 0);
    void leftSideMotorSetForwardSpeed(int speed);
    void leftSideMotorSetBackwardSpeed(int speed);
    void leftSideMotorStop();
    void rightSideMotorSetForwardSpeed(int speed);
    void rightSideMotorSetBackwardSpeed(int speed);
    void rightSideMotorStop();
    void stopAllMotors();
    int normalizeSpeedValue(int speed);

    void turnRight(int duration);
    void turnLeft(int duration);

    // ensure bot stays within the Sumobot ring
    void adjustDirectionIfGettingOutOfArea(LineSensors lineSensors, long currentTime);

    const int adjustDirectionReverseDuration = 600; //ms
    const int adjustDirectionTurnDuration = 1000; //ms
    const int directionAdjustmentTimeInterval = 100; // 100ms
    long timeDirectionLastAdjusted = 0;
};
   
#endif
