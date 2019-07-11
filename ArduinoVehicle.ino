#include <SoftwareSerial.h>

SoftwareSerial BTserial(14,15); //RX - A0, TX - A1

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

  /*
  backwardRight(255);
  backwardLeft(255);
  delay(5000);
  brakeRight(255);
  brakeLeft(255);

  delay(2000);
  backwardRight(255);
  backwardLeft(255);
  delay(5000);
  brakeRight(0);
  brakeLeft(0);

  delay(2000);
  turnLeftBackward(255);
  delay(2000);
  brakeAll(255);
  */
}

void loop() {
  // put your main code here, to run repeatedly:
  if (BTserial.available() > 0){
    byte receivedChar = BTserial.read();
    if (receivedChar == lastCharFromBT){
      return;
    }
    lastCharFromBT = receivedChar;
    Serial.println(lastCharFromBT); 
  }
}

void forwardRight(byte speedPWM){
  analogWrite(ena, speedPWM);
  digitalWrite(n1, HIGH);
  digitalWrite(n2, LOW);
}

void forwardLeft(byte speedPWM){
  analogWrite(enb, speedPWM);
  digitalWrite(n3, LOW);
  digitalWrite(n4, HIGH);
}

void backwardRight(byte speedPWM){
  analogWrite(ena, speedPWM);
  digitalWrite(n1, LOW);
  digitalWrite(n2, HIGH);
}

void backwardLeft(byte speedPWM){
  analogWrite(enb, speedPWM);
  digitalWrite(n3, HIGH);
  digitalWrite(n4, LOW);
}

void brakeRight(byte speedPWM){
  analogWrite(ena, speedPWM);
  digitalWrite(n1, LOW);
  digitalWrite(n2, LOW); 
}

void brakeLeft(byte speedPWM){
  analogWrite(enb, speedPWM);
  digitalWrite(n3, LOW);
  digitalWrite(n4, LOW);
}

void brakeAll(byte speedPWM){
  brakeRight(speedPWM);
  brakeLeft(speedPWM);
}

void turnRightForward(byte speedPWM){
  brakeRight(255);
  forwardLeft(speedPWM);
}

void turnRightBackward(byte speedPWM){
  brakeRight(255);
  backwardLeft(speedPWM);
}

void turnLeftForward(byte speedPWM){
  brakeLeft(255);
  forwardRight(speedPWM);
}

void turnLeftBackward(byte speedPWM){
  brakeLeft(255);
  backwardRight(speedPWM);
}
