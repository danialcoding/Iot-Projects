#include <Servo.h>
#include "HX711.h"

#define LOADCELL_DOUT_PIN 2
#define LOADCELL_SCK_PIN 3
#define SERVO_PIN 9 
#define GREEN_LED_PIN 10 
#define RED_LED_PIN 11 
#define BUZZER_PIN 4 

Servo servoMotor;
int servoOpenAngle = 180; 
int servoClosedAngle = 90;

int previousTime = 0; 
//int interval = 4 * 3600 * 1000; 
int interval = 6000;

bool foodAvailable = false;
bool foodTime = false;

HX711 scale;

void setup() {
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(36.059);
  scale.tare();

  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  servoMotor.attach(SERVO_PIN);
  
  servoMotor.write(servoClosedAngle);
  
  Serial.begin(9600);
}

void loop() {
  int currentTime = millis();

  if (currentTime - previousTime >= interval) {
    measureWeight();
    previousTime = currentTime;
    foodTime = true;
  }

  if (foodAvailable && foodTime) {
    openFoodContainer();
    //delay(300000); 
    delay(3000);
    closeFoodContainer();
    foodTime = false;
  } else if(!foodAvailable && foodTime) {
    measureWeight();
    beepAndBlink();
  }
  else {
    noTone(BUZZER_PIN); 
    digitalWrite(RED_LED_PIN, LOW);
  }
}

void measureWeight() {
  int weight = scale.get_units()/1000;
  if (weight > 5) {
    foodAvailable = true;
  } else {
    foodAvailable = false;
  }
}

void openFoodContainer() {
  servoMotor.write(servoOpenAngle); 
  digitalWrite(GREEN_LED_PIN, HIGH);
}

void closeFoodContainer() {
  servoMotor.write(servoClosedAngle); 
  digitalWrite(GREEN_LED_PIN, LOW);
}

void beepAndBlink() {
  digitalWrite(RED_LED_PIN, HIGH);
  tone(BUZZER_PIN, 1000);
  delay(500); 
  noTone(BUZZER_PIN);
  digitalWrite(RED_LED_PIN, LOW);
  delay(500);
}
