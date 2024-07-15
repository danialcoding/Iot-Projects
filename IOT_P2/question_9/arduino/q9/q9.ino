#define BLYNK_TEMPLATE_ID "TMPL63r4tVDL2"
#define BLYNK_TEMPLATE_NAME "burglar alarm"
#define BLYNK_AUTH_TOKEN "dB6-6NlnZKBPpl01koCgci4K1DrXHQ9D"

#include <SoftwareSerial.h>
#include <BlynkSimpleStream.h>

#define BLYNK_PRINT SwSerial

SoftwareSerial SwSerial(10, 11); 
SoftwareSerial myTerminal(6, 7);


int ldrPin = A0;
int buzzerPin = 3;
bool alarmEnabled = false;
int sensitivity = 0;


BLYNK_WRITE(V0)
{
  alarmEnabled = param.asInt();
  if (!alarmEnabled) {
    digitalWrite(buzzerPin, LOW);
  }
}

BLYNK_WRITE(V1)
{
  sensitivity = param.asInt();
}

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  Serial.begin(9600);
  myTerminal.begin(9600);
  SwSerial.begin(115200);

  Blynk.begin(Serial, BLYNK_AUTH_TOKEN);
}

void loop() {
  Blynk.run();

  myTerminal.print("status: ");
  myTerminal.println(alarmEnabled);
  delay(300);

  if (alarmEnabled) {
    int ldrValue = analogRead(ldrPin);

    myTerminal.print("LDR Value: ");
    myTerminal.println(ldrValue);
    delay(300);
    
    if (sensitivity == 0 && ldrValue > 80) {
      digitalWrite(buzzerPin, HIGH);
    } else if (sensitivity == 1 && ldrValue > 40) {
      digitalWrite(buzzerPin, HIGH);
    }
  }
  else {
    digitalWrite(buzzerPin, LOW);
  }
}



