#include <SoftwareSerial.h>

SoftwareSerial xbee(6, 7);

void setup() {
  Serial.begin(9600); 
  xbee.begin(9600);    
}


void loop() {
  if (Serial.available()) {
    String passwordInput = Serial.readStringUntil('\n');
    passwordInput.trim();
    xbee.println(passwordInput); 
    Serial.print("Password sent: "); 
    Serial.println(passwordInput);
  }
}
