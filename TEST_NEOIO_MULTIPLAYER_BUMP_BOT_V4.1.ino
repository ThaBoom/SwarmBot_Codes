// SWARM BOTS: 
// MULTI PLAYER RECEIVER CODE
// NEOPIXEL REMOTE ACTIVATION
// BUMP CODE 
// See SwarmBots.online for more info // 

//Pin numbers definition
const int motorEnableLeft = 9;
const int motorForwardLeft = 7;
const int motorBackLeft = 8;
const int motorEnableRight = 11;
const int motorForwardRight = 12;
const int motorBackRight = 10;
const int trigPinFront = A1;
const int echoPinFront = 2;
const int trigPinLeft = 3;
const int echoPinLeft = 4;
const int trigPinRight = 5;
const int echoPinRight = 6;
const int irPin = A0;
const int NEOIO = A4;

//RGB LED pins
const int LEDred = 13;
const int LEDgreen = A2;
const int LEDblue = A3;

//Variables for the Motors
const int leftMotorSpeed = 255;
const int rightMotorSpeed = 255;
const int delayTime = 150;

//Variables for Ultrasonic Sensors
long durationFront;
int distanceFront;
long durationLeft;
int distanceLeft;
long durationRight;
int distanceRight;
const int minFrontDistance = 30;
const int minSideDistance = 20;
const int stuckDistance = 10;

//Variables for IR Sensor
#include <IRremote.h>
IRrecv irrecv(irPin);
decode_results results;
boolean stopFlag = false;

//Control IR numbers
const long ACTIVATION = 16761405;
const long botSTOP_R = 16724175;
const long botSTOP_G = 16718055;
const long botSTOP_B = 16743045;
const long botSTOP_RB = 16716015;
const long botSTOP_RG = 16726215;
const long botSTOP_BG = 16734885;
const long BUMP_LEFT = 16753245;
const long STALL = 16769565;
const long BUMP_RIGHT = 16736925;


////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

void stopCar_RED () {
  digitalWrite(motorForwardLeft, LOW);
  digitalWrite(motorBackLeft, LOW);
  digitalWrite(motorForwardRight, LOW);
  digitalWrite(motorBackRight, LOW);
  analogWrite(motorEnableLeft, 0);
  analogWrite(motorEnableRight, 0);
  digitalWrite(LEDblue, LOW);
  digitalWrite(LEDgreen, LOW);
  digitalWrite(LEDred, HIGH);
  digitalWrite(NEOIO, LOW);
}

void stopCar_GREEN () {
  digitalWrite(motorForwardLeft, LOW);
  digitalWrite(motorBackLeft, LOW);
  digitalWrite(motorForwardRight, LOW);
  digitalWrite(motorBackRight, LOW);
  analogWrite(motorEnableLeft, 0);
  analogWrite(motorEnableRight, 0);
  digitalWrite(LEDblue, LOW);
  digitalWrite(LEDgreen, HIGH);
  digitalWrite(LEDred, LOW);
  digitalWrite(NEOIO, LOW);
}

void stopCar_BLUE () {
  digitalWrite(motorForwardLeft, LOW);
  digitalWrite(motorBackLeft, LOW);
  digitalWrite(motorForwardRight, LOW);
  digitalWrite(motorBackRight, LOW);
  analogWrite(motorEnableLeft, 0);
  analogWrite(motorEnableRight, 0);
  digitalWrite(LEDblue, HIGH);
  digitalWrite(LEDgreen, LOW);
  digitalWrite(LEDred, LOW);
  digitalWrite(NEOIO, LOW);
}

void stopCar_RED_BLUE () {
  digitalWrite(motorForwardLeft, LOW);
  digitalWrite(motorBackLeft, LOW);
  digitalWrite(motorForwardRight, LOW);
  digitalWrite(motorBackRight, LOW);
  analogWrite(motorEnableLeft, 0);
  analogWrite(motorEnableRight, 0);
  digitalWrite(LEDblue, HIGH);
  digitalWrite(LEDgreen, LOW);
  digitalWrite(LEDred, HIGH);
  digitalWrite(NEOIO, LOW);
}
void stopCar_RED_GREEN () {
  digitalWrite(motorForwardLeft, LOW);
  digitalWrite(motorBackLeft, LOW);
  digitalWrite(motorForwardRight, LOW);
  digitalWrite(motorBackRight, LOW);
  analogWrite(motorEnableLeft, 0);
  analogWrite(motorEnableRight, 0);
  digitalWrite(LEDblue, LOW);
  digitalWrite(LEDgreen, HIGH);
  digitalWrite(LEDred, HIGH);
  digitalWrite(NEOIO, LOW);
}
void stopCar_BLUE_GREEN () {
  digitalWrite(motorForwardLeft, LOW);
  digitalWrite(motorBackLeft, LOW);
  digitalWrite(motorForwardRight, LOW);
  digitalWrite(motorBackRight, LOW);
  analogWrite(motorEnableLeft, 0);
  analogWrite(motorEnableRight, 0);
  digitalWrite(LEDblue, HIGH);
  digitalWrite(LEDgreen, HIGH);
  digitalWrite(LEDred, LOW);
  digitalWrite(NEOIO, LOW);
}



/////////////////////////////////////////////////

void goForwardFull () {
  digitalWrite(motorForwardLeft, HIGH);
  digitalWrite(motorBackLeft, LOW);
  digitalWrite(motorForwardRight, HIGH);
  digitalWrite(motorBackRight, LOW);
  analogWrite(motorEnableLeft, leftMotorSpeed);
  analogWrite(motorEnableRight, rightMotorSpeed);
  digitalWrite(LEDblue, HIGH); 
  digitalWrite(LEDgreen, HIGH);
  digitalWrite(LEDred, HIGH);
  digitalWrite(NEOIO, HIGH);
}

void goLeft () {
  digitalWrite(motorForwardLeft, LOW);
  digitalWrite(motorBackLeft, LOW);
  digitalWrite(motorForwardRight, HIGH);
  digitalWrite(motorBackRight, LOW);
  analogWrite(motorEnableLeft, 0);
  analogWrite(motorEnableRight, rightMotorSpeed);
  digitalWrite(LEDblue, LOW);
  digitalWrite(LEDgreen, HIGH);
  digitalWrite(LEDred, LOW);
  digitalWrite(NEOIO, HIGH);
}

void goRight () {
  digitalWrite(motorForwardLeft, HIGH);
  digitalWrite(motorBackLeft, LOW);
  digitalWrite(motorForwardRight, LOW);
  digitalWrite(motorBackRight, LOW);
  analogWrite(motorEnableLeft, leftMotorSpeed);
  analogWrite(motorEnableRight, 0);
  digitalWrite(LEDblue, LOW);
  digitalWrite(LEDgreen, HIGH);
  digitalWrite(LEDred, LOW);
  digitalWrite(NEOIO, HIGH);
}

void goBack () {
  digitalWrite(motorForwardLeft, LOW);
  digitalWrite(motorBackLeft, HIGH);
  digitalWrite(motorForwardRight, LOW);
  digitalWrite(motorBackRight, HIGH);
  analogWrite(motorEnableLeft, leftMotorSpeed);
  analogWrite(motorEnableRight, rightMotorSpeed);
  digitalWrite(LEDblue, HIGH);
  digitalWrite(LEDgreen, LOW);
  digitalWrite(LEDred, LOW);
  digitalWrite(NEOIO, HIGH);
}

//////////////////////////////////////////////////
///////////////////////////////////////////////////

void sensorRead () {
  //Read front sensor value
  digitalWrite(trigPinFront, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinFront, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinFront, LOW);
  durationFront = pulseIn(echoPinFront, HIGH);
  distanceFront = durationFront * 0.034 / 2;
  
  //Read left sensor value
  digitalWrite(trigPinLeft, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinLeft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinLeft, LOW);
  durationLeft = pulseIn(echoPinLeft, HIGH);
  distanceLeft = durationLeft * 0.034 / 2;
 
  //Read right sensor value
  digitalWrite(trigPinRight, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinRight, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinRight, LOW);
  durationRight = pulseIn(echoPinRight, HIGH);
  distanceRight = durationRight * 0.034 / 2;

//  Serial.print("Left Sensor: ");
//  Serial.println(distanceLeft);
//  Serial.print("Right Sensor: ");
//  Serial.println(distanceRight);
//  Serial.print("Front Sensor: ");
//  Serial.println(distanceFront);


}


void setup() {
  pinMode(motorEnableLeft, OUTPUT);
  pinMode(motorForwardLeft, OUTPUT);
  pinMode(motorBackLeft, OUTPUT);
  pinMode(motorEnableRight, OUTPUT);
  pinMode(motorForwardRight, OUTPUT);
  pinMode(motorBackRight, OUTPUT);
  pinMode(trigPinFront, OUTPUT);
  pinMode(echoPinFront, INPUT);
  pinMode(trigPinLeft, OUTPUT);
  pinMode(echoPinLeft, INPUT);
  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);
  pinMode(LEDred, OUTPUT);
  pinMode(LEDgreen, OUTPUT);
  pinMode(LEDblue, OUTPUT);
  pinMode(NEOIO, OUTPUT);
  irrecv.enableIRIn();
  Serial.begin(9600);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


void loop() {
  sensorRead();
  Serial.println(results.value);
  if (irrecv.decode(&results)) {
    irrecv.resume();
  }

  if (results.value == ACTIVATION) {  // BOT ACTIVATION 
      stopFlag = false;
    if ((distanceFront <= minFrontDistance) || (distanceLeft <= minSideDistance) || (distanceRight <= minSideDistance)) {
      if ((distanceLeft < stuckDistance) || (distanceRight < stuckDistance) || (distanceFront < stuckDistance)) {
        goBack();
        delay(1.5*delayTime);
      }
      else if ((distanceFront <= minFrontDistance) && (distanceLeft <= minSideDistance) && (distanceRight <= minSideDistance)) {
        goBack();
        delay(1.5*delayTime);
      }
      else if (distanceLeft > distanceRight ) {
        goLeft();
        delay(delayTime);
      }
      else if (distanceLeft <= distanceRight) {
        goRight();
        delay(delayTime);
      }
      else
        goForwardFull();
    }
    else
      goForwardFull();
  }
  else if ((results.value == botSTOP_R) && (stopFlag == false)) {//BUTTON 1
    stopCar_RED();
    stopFlag = true;
}
  else if ((results.value == botSTOP_G) && (stopFlag == false)) {//BUTTON 2
    stopCar_GREEN();
    stopFlag = true;
}
  else if ((results.value ==botSTOP_B ) && (stopFlag == false)) {//BUTTON 3
    stopCar_BLUE();
    stopFlag = true;
}
  else if ((results.value == botSTOP_RB) && (stopFlag == false)) {//BUTTON 4
    stopCar_RED_BLUE();
    stopFlag = true;
}
  else if ((results.value == botSTOP_RG) && (stopFlag == false)) {//BUTTON 5
    stopCar_RED_GREEN();
    stopFlag = true;
}
  else if ((results.value == botSTOP_BG) && (stopFlag == false)) {//BUTTON 6
    stopCar_BLUE_GREEN();
    stopFlag = true;
}

///////////////////////////////////////////////////////////////////////////
//BUMP INPUT CODES
///////////////////////////////////////////////////////////////////////////

    else if ((results.value == BUMP_LEFT) && (stopFlag == false)) {//BUMP RIGHT
    goRight();
    delay(500);
    stopFlag = true;
    results.value = ACTIVATION;
}
  else if ((results.value == STALL) && (stopFlag == false)) {//BUMP LEFT
    goLeft();
    delay(500);
    stopFlag = true;
    results.value = ACTIVATION;
}
  else if ((results.value == BUMP_RIGHT) && (stopFlag == false)) {//STALL
    goBack();
    delay(500);
    stopFlag = true;
    results.value = ACTIVATION;
  }
}
