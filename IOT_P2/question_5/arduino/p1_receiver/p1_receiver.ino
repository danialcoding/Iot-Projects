#include <SoftwareSerial.h>

SoftwareSerial myTerminal(6,7);

const int greenLED = 3;
const int redLED = 2;
const int buzzer = 4;
const String password = "code123";

void setup() {
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  digitalWrite(redLED, HIGH);

  myTerminal.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    String received = Serial.readStringUntil('\n');
    received.trim();
    myTerminal.println(received);


    if (received == password) {
      digitalWrite(greenLED, HIGH);
      digitalWrite(redLED, LOW);
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(greenLED, LOW);
      digitalWrite(buzzer, LOW);
      digitalWrite(redLED, HIGH); 
    } else {
      digitalWrite(redLED, HIGH);
    }
  }
}