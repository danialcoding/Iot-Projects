int LDR_pin = A0; 
int LED_pin = 13;
int threshold = 3;


void setup() {
  pinMode(LED_pin, OUTPUT); 
  pinMode(LDR_pin,  INPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(LDR_pin);

  if (sensorValue > threshold) {
    digitalWrite(LED_pin, HIGH); 
  } else {
    digitalWrite(LED_pin, LOW);
  }
  
  delay(1000);
}
