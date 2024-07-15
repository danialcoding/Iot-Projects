
int digit[10] = {0b0111111, 0b0000110, 0b1011011, 0b1001111, 0b1100110, 0b1101101, 0b1111101, 0b0000111, 0b1111111, 0b1101111};

int digit1, digit2; 

int sevdig[2] = {10,11};


const int redLED1 = 12;
const int yellowLED1 = 13;
const int greenLED1 = A0;

const int redLED2 = A1;
const int yellowLED2 = A2;
const int greenLED2 = A3; 


const int buzzer = A4; 
int time = 10;
int countDown = time;

int state = 1;

void setup() {
  for (int i = 2; i < 9; i++)
  {
    pinMode(i, OUTPUT);
  }
  pinMode(sevdig[0], OUTPUT);
  pinMode(sevdig[1], OUTPUT);


  pinMode(redLED1, OUTPUT);
  pinMode(yellowLED1, OUTPUT);
  pinMode(greenLED1, OUTPUT);

  pinMode(redLED2, OUTPUT);
  pinMode(yellowLED2, OUTPUT);
  pinMode(greenLED2, OUTPUT);

  pinMode(buzzer, OUTPUT);
}

void loop() {
  countDownfunc();

  if (countDown == 0) {
    digitalWrite(buzzer, HIGH);
    delay(300);
    digitalWrite(buzzer, LOW);
    countDown = time;
    if(state == 1) {
      state = 0;
    }
    else {
      state = 1;
    }
  }
}


void countDownfunc() {

  for (int j = countDown; j >= 0; j--)
    {
      digit2 = j / 10;
      digit1 = j % 10;
      for ( int k = 0; k < 20; k++)
      {
        digitalWrite(sevdig[0], HIGH);
        digitalWrite(sevdig[1], LOW);
        displayCountDown(digit2);
        delay(10);
        digitalWrite(sevdig[1], HIGH);
        digitalWrite(sevdig[0], LOW);
        displayCountDown(digit1);
        delay(10);
      }
      if(countDown == 0) {
        break;
      }
      countDown--;
      checkTrafficLights();
    }  
}


void displayCountDown(int num)
{
  for (int i = 2; i < 9; i++)
  {
    digitalWrite(i, bitRead(digit[num], i - 2));
  }
}

void checkTrafficLights() {
  if(state == 0) {
    displayTrafficLightsOpen(redLED1, yellowLED1, greenLED1);
    displayTrafficLightsClose(redLED2, yellowLED2, greenLED2);
  }
  else {
    displayTrafficLightsOpen(redLED2, yellowLED2, greenLED2);
    displayTrafficLightsClose(redLED1, yellowLED1, greenLED1);
  }
}

void displayTrafficLightsOpen(int redLED,int yellowLED,int greenLED) {
  if (countDown > 3) {
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, HIGH);
  } else if (countDown <= 3) {
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, LOW);
  }
}

void displayTrafficLightsClose(int redLED,int yellowLED,int greenLED) {
  if (countDown > 3) {
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, LOW); 
    digitalWrite(greenLED, LOW);
  } else if (countDown <= 1) {
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, LOW);
  }
}
