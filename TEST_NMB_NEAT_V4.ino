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
////////////////////////////////////////////
///////////////////////////////////////////
void setLEDs(int blue, int green, int red) {
  digitalWrite(LEDblue, blue);
  digitalWrite(LEDgreen, green);
  digitalWrite(LEDred, red);
}  
void setMotors(int forwardLeft, int backLeft, int forwardRight, int backRight) {
  digitalWrite(motorForwardLeft, forwardLeft);
  digitalWrite(motorBackLeft, backLeft);
  digitalWrite(motorForwardRight, forwardRight);
  digitalWrite(motorBackRight, backRight);
}
void analogWriteMotors(int left, int right) {
  analogWrite(motorEnableLeft, left);
  analogWrite(motorEnableRight, right);
}
void disableMotors() {
  analogWriteMotors(0, 0);
}
void enableMotors() {
  analogWriteMotors(leftMotorSpeed, rightMotorSpeed);
}
void stopMotors() {
  setMotors(LOW, LOW, LOW, LOW);
}
void stopCar_RED () {
  stopMotors();
  disableMotors();
  setLEDs(LOW, LOW, HIGH);
  digitalWrite(NEOIO, LOW);
}
void stopCar_GREEN () {
  stopMotors();
  disableMotors();
  setLEDs(LOW, HIGH, LOW);
  digitalWrite(NEOIO, LOW);
}
void stopCar_BLUE () {
  stopMotors();
  disableMotors();
  setLEDs(HIGH, LOW, LOW);
  digitalWrite(NEOIO, LOW);
}
void stopCar_RED_BLUE () {
  stopMotors();
  disableMotors();
  setLEDs(HIGH, LOW, HIGH);
  digitalWrite(NEOIO, LOW);
}
void stopCar_RED_GREEN () {
  stopMotors();
  disableMotors();
  setLEDs(LOW, HIGH, HIGH);
  digitalWrite(NEOIO, LOW);
}
void stopCar_BLUE_GREEN () {
  stopMotors();
  disableMotors();
  setLEDs(HIGH, HIGH, LOW);
  digitalWrite(NEOIO, LOW);
}
/////////////////////////////////////////////////
void goForwardFull () {
  setMotors(HIGH, LOW, HIGH, LOW);
  enableMotors();
  setLEDs(HIGH, HIGH, HIGH);
  digitalWrite(NEOIO, HIGH);
}
void goLeft () {
  setMotors(LOW, LOW, HIGH, LOW);
  analogWriteMotors(0, rightMotorSpeed);
  setLEDs(LOW, HIGH, LOW);
  digitalWrite(NEOIO, HIGH);
}
void goRight () {
  setMotors(HIGH, LOW, LOW, LOW);
  analogWriteMotors(leftMotorSpeed, 0);
  setLEDs(LOW, HIGH, LOW);
  digitalWrite(NEOIO, HIGH);
}
void goBack () {
  setMotors(LOW, HIGH, LOW, HIGH);
    enableMotors();
  setLEDs(HIGH, LOW, LOW);
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
  Serial.print("Left Sensor: ");
  Serial.println(distanceLeft);
  Serial.print("Right Sensor: ");
  Serial.println(distanceRight);
  Serial.print("Front Sensor: ");
  Serial.println(distanceFront);
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
void loop() {
  sensorRead();
  Serial.println(results.value);
  if (irrecv.decode(&results)) {
    irrecv.resume();
  }
  
  if (0xFFC23D == results.value) {  // BOT ACTIVATION
    do_bot_activation();
  }
  else {
    do_bump();
  }
}
void do_bot_activation() {
  Serial.println("inside do_bot_activation");
  stopFlag = false;
  if (!somethingTooClose()) {
    return ;
  }
  if (weAreStuck()) {
    goBack();
    delay(1.5*delayTime);
  }
  else if (everythingTooClose()) {
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
  goForwardFull();
}
boolean somethingTooClose() {
  return (distanceFront <= minFrontDistance) || (distanceLeft <= minSideDistance) || (distanceRight <= minSideDistance);
}
boolean weAreStuck() {
  return (distanceLeft < stuckDistance) || (distanceRight < stuckDistance) || (distanceFront < stuckDistance);
}
boolean everythingTooClose() {
  return (distanceFront <= minFrontDistance) && (distanceLeft <= minSideDistance) && (distanceRight <= minSideDistance);
}
void do_bump() {
  Serial.println("inside do_bump");
  if (stopFlag) {
    Serial.println("stopFlag is true, returning from do_bump early.");
    return ;
  }
  if (0xFF30CF == results.value) {//BUTTON 1
    stopCar_RED();
  }
  else if (0xFF18E7 == results.value) {//BUTTON 2
    stopCar_GREEN();
  }
  else if (0xFF7A85 == results.value ) {//BUTTON 3
    stopCar_BLUE();
  }
  else if (0xFF10EF == results.value) {//BUTTON 4
    stopCar_RED_BLUE();
  }
  else if (0xFF38C7 == results.value) {//BUTTON 5
    stopCar_RED_GREEN();
  }
  else if (0xFF5AA5 == results.value) {//BUTTON 6
    stopCar_BLUE_GREEN();
  }
  ///////////////////////////////////////////////////////////////////////////
  //BUMP INPUT CODES
  ///////////////////////////////////////////////////////////////////////////
  else if (0xFFE21D == results.value) {//BUMP RIGHT
    goRight();
    delay(250);
        results.value = 0xFFC23D;
  }
  else if (0xFFA25D == results.value) {//BUMP LEFT
    goLeft();
    delay(250);
        results.value = 0xFFC23D;
  }
  else if (0xFF629D == results.value) {//STALLy
    goBack();
    delay(500);
        results.value = 0xFFC23D;
  }
  stopFlag = true;
}
