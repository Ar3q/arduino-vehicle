#include <SoftwareSerial.h>

SoftwareSerial BTserial(14,15); //RX - A0, TX - A1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start");
  BTserial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (BTserial.available() > 0){
    Serial.println(BTserial.read());
  }
} 
