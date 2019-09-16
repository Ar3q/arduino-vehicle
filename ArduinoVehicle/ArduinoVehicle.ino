#include <SoftwareSerial.h>

SoftwareSerial BTserial(14, 15); //RX - A0, TX - A1

//A right
int n1 = 2; //dir
int n2 = 3; //dir
int ena = 9; //controll

//B left
int n3 = 4; //dir
int n4 = 5; //dir
int enb = 10; //controll

//for saving last character got via Bluetooth, in ASCII code
byte lastCharFromBT = -1;

const byte MAX_PWM_SPEED = 255;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start");
  BTserial.begin(9600);

  pinMode(n1, OUTPUT);
  pinMode(n2, OUTPUT);
  pinMode(ena, OUTPUT);

  pinMode(n3, OUTPUT);
  pinMode(n4, OUTPUT);
  pinMode(enb, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (BTserial.available() > 0) {
    byte receivedChar = BTserial.read();
    if (receivedChar == lastCharFromBT) {
      return;
    }
    lastCharFromBT = receivedChar;
    Serial.println((char)lastCharFromBT);

    move();
  }
}

void move() {
  switch ((char)lastCharFromBT) {
    case '1':
      Serial.println("Forward");
      forwardAll(MAX_PWM_SPEED);
      break;

    case '2':
      Serial.println("Backward");
      backwardAll(MAX_PWM_SPEED);
      break;

    case '3':
      Serial.println("Forward Left");
      forwardLeft(MAX_PWM_SPEED);
      brakeRight(MAX_PWM_SPEED);
      break;

    case '4':
      Serial.println("Forward Right");
      forwardRight(MAX_PWM_SPEED);
      brakeLeft(MAX_PWM_SPEED);
      break;

    case '5':
      Serial.println("Backward Left");
      backwardLeft(MAX_PWM_SPEED);
      brakeRight(MAX_PWM_SPEED);
      break;

    case '6':
      Serial.println("Backward Right");
      backwardRight(MAX_PWM_SPEED);
      brakeLeft(MAX_PWM_SPEED);
      break;

    case '9':
      Serial.println("Brake");
      brakeAll(MAX_PWM_SPEED);
      break;

    default:
      Serial.println("??????");
  }
}

void forwardRight(byte speedPWM) {
  analogWrite(ena, speedPWM);
  digitalWrite(n1, HIGH);
  digitalWrite(n2, LOW);
}

void forwardLeft(byte speedPWM) {
  analogWrite(enb, speedPWM);
  digitalWrite(n3, LOW);
  digitalWrite(n4, HIGH);
}

void forwardAll(byte speedPWM) {
  forwardRight(speedPWM);
  forwardLeft(speedPWM);
}

void backwardRight(byte speedPWM) {
  analogWrite(ena, speedPWM);
  digitalWrite(n1, LOW);
  digitalWrite(n2, HIGH);
}

void backwardLeft(byte speedPWM) {
  analogWrite(enb, speedPWM);
  digitalWrite(n3, HIGH);
  digitalWrite(n4, LOW);
}

void backwardAll(byte speedPWM) {
  backwardRight(speedPWM);
  backwardLeft(speedPWM);
}

void brakeRight(byte speedPWM) {
  analogWrite(ena, speedPWM);
  digitalWrite(n1, LOW);
  digitalWrite(n2, LOW);
}

void brakeLeft(byte speedPWM) {
  analogWrite(enb, speedPWM);
  digitalWrite(n3, LOW);
  digitalWrite(n4, LOW);
}

void brakeAll(byte speedPWM) {
  brakeRight(speedPWM);
  brakeLeft(speedPWM);
}

void turnRightForward(byte speedPWM) {
  brakeRight(255);
  forwardLeft(speedPWM);
}

void turnRightBackward(byte speedPWM) {
  brakeRight(255);
  backwardLeft(speedPWM);
}

void turnLeftForward(byte speedPWM) {
  brakeLeft(255);
  forwardRight(speedPWM);
}

void turnLeftBackward(byte speedPWM) {
  brakeLeft(255);
  backwardRight(speedPWM);
}
