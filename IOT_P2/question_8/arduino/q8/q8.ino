#define BLYNK_TEMPLATE_ID "TMPL6z9Kuqr6J"
#define BLYNK_TEMPLATE_NAME "thermometer"
#define BLYNK_AUTH_TOKEN "9JEVg4ISW7GVh5puuSs8Kp_Zi79M-AGg"

#include <SoftwareSerial.h>
#include <BlynkSimpleStream.h>
#include <Servo.h>

#define BLYNK_PRINT SwSerial

SoftwareSerial SwSerial(10, 11); 
SoftwareSerial myTerminal(6, 7);

Servo servoMotor;
int tempSensorPin = A0;
int ledPin = 3;
int servoPin = 2;
float desiredTemp = 25.0;
float tolerance = 2.0;
BlynkTimer timer;
float currentTemp = 0;


BLYNK_WRITE(V0)
{
  desiredTemp = param.asFloat();
  myTerminal.println(desiredTemp);
  delay(200);
  servoMotor.write(map(desiredTemp, 0, 50, 0, 180));
  //servoMotor.write(90 + desiredTemp);
}
void myTimerEvent()
{
  Blynk.virtualWrite(V1, currentTemp);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(tempSensorPin, INPUT);
  servoMotor.attach(servoPin);
  Serial.begin(9600);
  myTerminal.begin(9600);
  SwSerial.begin(115200);

  Blynk.begin(Serial, BLYNK_AUTH_TOKEN);

  timer.setInterval(1000L, myTimerEvent);
}

void loop() {
  Blynk.run();
  timer.run();

  int temp_adc_val = analogRead(tempSensorPin);
  currentTemp = (temp_adc_val * 4.88);	
  currentTemp = (currentTemp/10);


  if (currentTemp < (desiredTemp - tolerance)) {
    digitalWrite(ledPin, HIGH); 
  } else if (currentTemp >= desiredTemp) {
    digitalWrite(ledPin, LOW); 
  }
}


