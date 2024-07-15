#define BLYNK_TEMPLATE_ID "TMPL6tbf_dx2N"
#define BLYNK_TEMPLATE_NAME "controler"
#define BLYNK_AUTH_TOKEN "cLqx2YdUMnmP2cXt0a5jMt5yb6mS5w-1"

#include <SoftwareSerial.h>
#include <BlynkSimpleStream.h>
#include <Servo.h>

#define BLYNK_PRINT SwSerial

SoftwareSerial SwSerial(10, 11); 
SoftwareSerial myTerminal(6,7);


int servoOn = 180;
int servoOff = 90;


Servo servoMotor;
int buzzerPin = 3;
int servoPin = 2;
bool motorStatus = false;
int overheatTime = -1;

BLYNK_WRITE(V1)
{
  motorStatus = param.asInt();
  myTerminal.println(motorStatus);
  if (motorStatus) {
    servoMotor.attach(servoPin);
    servoMotor.write(servoOn);
  } else {
    servoMotor.write(servoOff);
    digitalWrite(buzzerPin, LOW);
    overheatTime = -1;
  }
}
BLYNK_WRITE(V0)
{
  int power = param.asInt();
  myTerminal.println(power);
  if (motorStatus == 1) {
    if (power > 90) {
      overheatTime = millis();
    }
  }
}

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(servoPin, OUTPUT);
  Serial.begin(9600);
  myTerminal.begin(9600);
  SwSerial.begin(115200);

  Blynk.begin(Serial, BLYNK_AUTH_TOKEN);
}

void loop() {
  Blynk.run();
  if (overheatTime > 0 && (millis() - overheatTime > 5000)) {
    digitalWrite(buzzerPin, HIGH);
  }
}
