#include <Keypad.h>
#include <Servo.h>

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3};


#define PASSWORD_LENGTH 4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

Servo servoMotor;
int servoPin = 10;

const int buzzerPin = 11;

const int greenLEDPin = 12;
const int redLEDPin = 13;

int defaultPassword = 1402;
int enteredPassword = 0;
bool isNewPassword = false;

int sevOpen = 180;
int sevClose = 90;

int changePass = false;

void setup() {

  servoMotor.attach(servoPin);
  pinMode(buzzerPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);

  servoMotor.write(sevClose);
}

void loop() {
  char key;
  if(changePass == false) {
    key = keypad.getKey();
  }

  if (key) {
    if (key == '*' || changePass == true) {
      digitalWrite(greenLEDPin, HIGH);
      delay(500);
      digitalWrite(greenLEDPin, LOW);



      changePass = false;
      enteredPassword = 0;
      for(int i = PASSWORD_LENGTH;i > 0;i--) {
        char key1 = keypad.getKey();
        while(!(key1 >= '0' && key1 <= '9')) {
          key1 = keypad.getKey();
        }
        int num = key1 - '0';
        enteredPassword = num + (enteredPassword * 10);
      }
      if (enteredPassword == defaultPassword) {
        digitalWrite(greenLEDPin, HIGH);
        delay(500);
        digitalWrite(greenLEDPin, LOW);



        enteredPassword = 0;
        for(int i = PASSWORD_LENGTH;i>0;i--) {
          char key1 = keypad.getKey();
          while(!(key1 >= '0' && key1 <= '9')) {
            key1 = keypad.getKey();
          }
          int num = key1 - '0';
          enteredPassword = num + (enteredPassword * 10);
        }

        defaultPassword = enteredPassword;

        digitalWrite(greenLEDPin, HIGH);
        delay(1000);
        digitalWrite(greenLEDPin, LOW);
        delay(500);
      } else {
        digitalWrite(redLEDPin, HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(1000);
        digitalWrite(redLEDPin, LOW);
        digitalWrite(buzzerPin, LOW);
        delay(500);
      }
    } else if (key >= '0' && key <= '9'){
      enteredPassword = 0;

      int num = key - '0';
      enteredPassword = num + (enteredPassword * 10);

      for(int i = PASSWORD_LENGTH - 1;i>0;i--) {
        key = keypad.getKey();

        while(!(key >= '0' && key <= '9')) {
          key = keypad.getKey();
          if(key == '*') {
            changePass = true;
            return;
          }
        }

        num = key - '0';
        enteredPassword = num + (enteredPassword * 10);
      }
      if (enteredPassword == defaultPassword) {
        digitalWrite(greenLEDPin, HIGH);
        servoMotor.write(sevOpen);
        delay(2000);
        servoMotor.write(sevClose);
        digitalWrite(greenLEDPin, LOW);
        delay(500);
      }
      else {
        digitalWrite(redLEDPin, HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(1000);
        digitalWrite(redLEDPin, LOW);
        digitalWrite(buzzerPin, LOW);
        delay(500);
      }
      enteredPassword = 0;
    }
  }
}
