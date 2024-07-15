#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial myTerminal(6,7);
Servo doorServo;
int servoPin = 2;
unsigned long openTime = 0;

int opendegree = 180;
int closedegree = 90;

void setup() {
  doorServo.attach(servoPin);
  Serial.begin(9600);
  myTerminal.begin(9600);

  doorServo.write(closedegree);
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil("/n");
    myTerminal.println(command);
    if (command == "open") {
      doorServo.write(opendegree);
      openTime = millis();
    } else if (command == "close") {
      doorServo.write(closedegree);
      openTime = 0;
    }
  }else if(millis() - openTime >= 10000) {
    doorServo.write(closedegree);
    openTime = 0; 
  }
}
