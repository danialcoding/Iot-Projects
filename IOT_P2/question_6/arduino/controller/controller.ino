#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial xbee(6,7);
int buttonOpenPin = 4;
int buttonClosePin = 3;
int ledPin = 2;
bool doorOpened = false;
unsigned long openTime = 0;

void setup() {
  pinMode(buttonOpenPin, INPUT_PULLUP);
  pinMode(buttonClosePin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  xbee.begin(9600);
}

void loop() {
  if (digitalRead(buttonOpenPin) == LOW) {
    xbee.print("open");
    doorOpened = true;
    openTime = millis();
    delay(50);
    digitalWrite(ledPin, HIGH);
    delay(3000);
    digitalWrite(ledPin, LOW);
  }
  if (doorOpened && digitalRead(buttonClosePin) == LOW) {
    xbee.print("close");
    doorOpened = false;
    openTime = 0;
    delay(50);
    digitalWrite(ledPin, HIGH);
    delay(3000);
    digitalWrite(ledPin, LOW);
  }
  if (doorOpened && millis() - openTime > 10000) {
    doorOpened = false;
    openTime = 0;
    delay(50);
    digitalWrite(ledPin, HIGH);
    delay(3000);
    digitalWrite(ledPin, LOW);
  }
}
