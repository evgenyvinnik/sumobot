//Keyboard Controls:
//
// 1 -Motor 1 Left
// 2 -Motor 1 Stop
// 3 -Motor 1 Right
//
// 4 -Motor 2 Left
// 5 -Motor 2 Stop
// 6 -Motor 2 Right

// Declare L298N Dual H-Bridge Motor Controller directly since there is not a library to load.

//arduino uno
// Motor 1
//int dir1PinA = 2;
//int dir2PinA = 3;
//int speedPinA = 9; // Needs to be a PWM pin to be able to control motor speed

// Motor 2
//int dir1PinB = 4;
//int dir2PinB = 5;
//int speedPinB = 10; // Needs to be a PWM pin to be able to control motor speed

//arduino mega
// Motor 1
int dir1PinA = 30;
int dir2PinA = 31;
int speedPinA = 6; // Needs to be a PWM pin to be able to control motor speed

// Motor 2
int dir1PinB = 32;
int dir2PinB = 33;
int speedPinB = 5; // Needs to be a PWM pin to be able to control motor speed

int pwm_value = 254;

// Sensors ----------------------------------------------------

// IR Line sensors, digital pins
const int lineSensorIRFrontRightPin = 8;
const int lineSensorIRFrontLeftPin  = 9;
const int lineSensorIRRearRightPin  = 10;
const int lineSensorIRRearLeftPin   = 11;
int lineSensorIRFrontRightValue     = 0;
int lineSensorIRFrontLeftValue      = 0;
int lineSensorIRRearRightValue      = 0;
int lineSensorIRRearLeftValue       = 0;

// Infrared sensor
int infraredSensorPin = 0;
int infraredSensorValue = 0;

long loopCounter = 0;

void setup() { // Setup runs once per reset
  // initialize serial communication @ 9600 baud:
  Serial.begin(9600);
  Serial.println("Start");

  initMotors();
  initSensors();
}

void initMotors() {
  //Define L298N Dual H-Bridge Motor Controller Pins
  pinMode(dir1PinA, OUTPUT);
  pinMode(dir2PinA, OUTPUT);
  pinMode(speedPinA, OUTPUT);
  pinMode(dir1PinB, OUTPUT);
  pinMode(dir2PinB, OUTPUT);
  pinMode(speedPinB, OUTPUT);
}

void initSensors() {
  pinMode(lineSensorIRFrontRightPin, INPUT);
  pinMode(lineSensorIRFrontLeftPin,  INPUT);
  pinMode(lineSensorIRRearRightPin,  INPUT);
  pinMode(lineSensorIRRearLeftPin,   INPUT);
}

void loop() {
  loopCounter++;
  readSensors(loopCounter);

  controlMotors();
}

void readSensors(long loopCounter) {
  if (loopCounter % 5000 == 0) {
    infraredSensorValue = analogRead(infraredSensorPin);
    Serial.println(infraredSensorValue);
  }

  if(loopCounter % 15000 == 0) {
    lineSensorIRFrontRightValue = digitalRead(lineSensorIRFrontRightPin);
    lineSensorIRFrontLeftValue = digitalRead(lineSensorIRFrontLeftPin);
    lineSensorIRRearRightValue = digitalRead(lineSensorIRRearRightPin);
    lineSensorIRRearLeftValue = digitalRead(lineSensorIRRearLeftPin);

    Serial.print("lineSensorIRFrontRightValue = ");
    Serial.println(lineSensorIRFrontRightValue);

    Serial.print("lineSensorIRFrontLeftValue = ");
    Serial.println(lineSensorIRFrontLeftValue);

    Serial.print("lineSensorIRRearRightValue = ");
    Serial.println(lineSensorIRRearRightValue);

    Serial.print("lineSensorIRRearLeftValue = ");
    Serial.println(lineSensorIRRearLeftValue);
  }
}

void controlMotors() {
  if (Serial.available() <= 0) return;

  int inByte = Serial.read();
  switch (inByte) {

    //______________Motor 1______________

  case '1': // Motor 1 Forward
    analogWrite(speedPinA, pwm_value); //Sets speed variable via PWM
    digitalWrite(dir1PinA, LOW);
    digitalWrite(dir2PinA, HIGH);
    Serial.println("Motor 1 Forward"); // Prints out “Motor 1 Forward” on the serial monitor
    Serial.println("   "); // Creates a blank line printed on the serial monitor
    break;

  case '2': // Motor 1 Stop (Freespin)
    analogWrite(speedPinA, 0);
    digitalWrite(dir1PinA, LOW);
    digitalWrite(dir2PinA, HIGH);
    Serial.println("Motor 1 Stop");
    Serial.println("   ");
    break;

  case '3': // Motor 1 Reverse
    analogWrite(speedPinA, pwm_value);
    digitalWrite(dir1PinA, HIGH);
    digitalWrite(dir2PinA, LOW);
    Serial.println("Motor 1 Reverse");
    Serial.println("   ");
    break;

    //______________Motor 2______________

  case '4': // Motor 2 Forward
    analogWrite(speedPinB, pwm_value);
    digitalWrite(dir1PinB, LOW);
    digitalWrite(dir2PinB, HIGH);
    Serial.println("Motor 2 Forward");
    Serial.println("   ");
    break;

  case '5': // Motor 1 Stop (Freespin)
    analogWrite(speedPinB, 0);
    digitalWrite(dir1PinB, LOW);
    digitalWrite(dir2PinB, HIGH);
    Serial.println("Motor 2 Stop");
    Serial.println("   ");
    break;

  case '6': // Motor 2 Reverse
    analogWrite(speedPinB, pwm_value);
    digitalWrite(dir1PinB, HIGH);
    digitalWrite(dir2PinB, LOW);
    Serial.println("Motor 2 Reverse");
    Serial.println("   ");
    break;

  default:
    // turn all the connections off if an unmapped key is pressed:
    for (int thisPin = 2; thisPin < 11; thisPin++) {
      digitalWrite(thisPin, LOW);
    }
  }
}
